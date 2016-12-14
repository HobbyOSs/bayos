#include "../bayos.h"

IDEDriver::IDEDriver(int irq_primary, int irq_secondary) {
    this->controllers[PRIMARY].registers[ATA_DTR] = 0x1f0;
    this->controllers[PRIMARY].registers[ATA_ERR] = 0x1f1;
    this->controllers[PRIMARY].registers[ATA_SCR] = 0x1f2;
    this->controllers[PRIMARY].registers[ATA_SNR] = 0x1f3;
    this->controllers[PRIMARY].registers[ATA_CLR] = 0x1f4;
    this->controllers[PRIMARY].registers[ATA_CHR] = 0x1f5;
    this->controllers[PRIMARY].registers[ATA_DHR] = 0x1f6;
    this->controllers[PRIMARY].registers[ATA_STR] = 0x1f7;
    this->controllers[PRIMARY].registers[ATA_ASR] = 0x3f6;
    this->controllers[PRIMARY].irq = irq_primary;
    this->controllers[PRIMARY].selectedDevice = NULL;

    this->controllers[SECONDARY].registers[ATA_DTR] = 0x170;
    this->controllers[SECONDARY].registers[ATA_ERR] = 0x171;
    this->controllers[SECONDARY].registers[ATA_SCR] = 0x172;
    this->controllers[SECONDARY].registers[ATA_SNR] = 0x173;
    this->controllers[SECONDARY].registers[ATA_CLR] = 0x174;
    this->controllers[SECONDARY].registers[ATA_CHR] = 0x175;
    this->controllers[SECONDARY].registers[ATA_DHR] = 0x176;
    this->controllers[SECONDARY].registers[ATA_STR] = 0x177;
    this->controllers[SECONDARY].registers[ATA_ASR] = 0x376;
    this->controllers[SECONDARY].irq = irq_secondary;
    this->controllers[SECONDARY].selectedDevice = NULL;

    initialize(&controllers[PRIMARY]);
    initialize(&controllers[SECONDARY]);

    this->whichController = NULL;
    this->atapiBuffer     = NULL;
    this->atapiReadDone   = true;
}

//IDEDriver::~IDEDriver() {}

bool IDEDriver::selectDevice(int controller, int deviceNo) {
    if (controller != PRIMARY && controller != SECONDARY) return false;
    if (deviceNo != MASTER && deviceNo != SLAVE) return false;

    IDEDevice* device = &controllers[controller].devices[deviceNo];

    if (device->type == DEVICE_NONE || device->type == DEVICE_UNKNOWN) return false;

    controllers[controller].selectedDevice = device;
    whichController = &controllers[controller];
    return true;
}

bool IDEDriver::findDevice(int type, int detail, int* controller, int* deviceNo) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            IDEDevice* device = &controllers[i].devices[j];

            if (type != device->type || detail != device->typeDetail) continue;

            *controller = i;
            *deviceNo = j;
            return true;
        }
    }

    return false;
}

int IDEDriver::read(unsigned int lba, void* buffer, int size) {
    if (this->whichController == NULL) return 1;

    if (this->whichController->selectedDevice->type == DEVICE_ATAPI) {
        int count = (size + 0xf800 - 1) / 0xf800;

        for (int i = 0; i < count; i++) {
            int readSize;
            bool readResult;
            if (i == count - 1) {
                readSize = size - 0xf800 * i;
            } else {
                readSize = 0xf800;
            }

            for (int j = 0; j < 20; j++) {
                readResult = commandRead10(this->whichController, lba + 0xf800 * i / 2048, buffer, readSize);
                if (readResult) break;
            }

            buffer = (void*)((unsigned char*)buffer + readSize);

            if (!readResult) {
                return this->lastError;
            }
        }
        return 0;
    } else if (this->whichController->selectedDevice->type == DEVICE_ATA) {
        return 4;
    } else {
        return 5;
    }
}

void IDEDriver::outp8(IDEController* controller, int reg, unsigned char value) {
    io_out8(controller->registers[reg], value);
}

unsigned char IDEDriver::inp8(IDEController* controller, int reg) {
    return io_in8(controller->registers[reg]);
}

unsigned short IDEDriver::inp16(IDEController* controller, int reg) {
    return io_in16(controller->registers[reg]);
}

void IDEDriver::outp16(IDEController* controller, int reg, unsigned short value) {
    io_out16(controller->registers[reg], value);
}

void IDEDriver::outp16(IDEController* controller, unsigned short* data, int length) {
    for (int i=0; i < length; i++) {
        outp16(controller, ATA_DTR, *data);
        data++;
    }
}

void IDEDriver::inp16(IDEController* controller, unsigned short* data, int size) {
    int length = size / 2;

    if (data == NULL) {
        for (int i = 0; i < length; i++) {
            inp16(controller, ATA_DTR);
        }
    } else {
        for (int i = 0; i < length; i++) {
            *data = inp16(controller, ATA_DTR);
            data++;
        }
    }
}

bool IDEDriver::waitBusyAndDataRequestBothClear(IDEController* controller) {
    unsigned int i;
    for (i = 0; i < ATA_TIMEOUT; i++) {
        unsigned char status = inp8(controller, ATA_ASR);
        if ((status & BIT_BSY) == 0 && (status & BIT_DRQ) == 0) break;
    }
    return (i != ATA_TIMEOUT);
}

bool IDEDriver::waitBusyClear(IDEController* controller) {
    unsigned int i;
    for (i = 0; i < ATA_TIMEOUT; i++) {
        unsigned char status = inp8(controller, ATA_ASR);
        if ((status & BIT_BSY) == 0) break;
    }
    return (i != ATA_TIMEOUT);
}

bool IDEDriver::waitDrdySet(IDEController* controller) {
    unsigned int i;

    for (i = 0; i < ATA_TIMEOUT; i++) {
        unsigned char status = inp8(controller, ATA_ASR);
        if (status & BIT_DRDY) break;
    }

    return (i != ATA_TIMEOUT);
}

bool IDEDriver::protocolPacket(IDEController* controller, ATAPICommand* command) {
    outp8(controller, ATA_DCR, 0x8);

    atapiBuffer = command->buffer;
    atapiReadDone = false;
    atapiTotalReadSize = command->limit;

    if (!selectDevice(controller, command->deviceNo)) {
        this->lastError = SELECTION_ERROR;
        return false;
    }

    outp8(controller, ATA_FTR, command->feature);
    outp8(controller, ATA_SCR, 0);
    outp8(controller, ATA_BLR, (unsigned char)(command->limit & 0xff));
    outp8(controller, ATA_BHR, (unsigned char)(command->limit >> 8));
    outp8(controller, ATA_CMR, 0xa0);
    sleep(1);

    unsigned int i;
    for (i = 0; i < ATA_TIMEOUT; i++) {
        unsigned char status = inp8(controller, ATA_ASR);

        if ((status & BIT_BSY) != 0) continue;
        if ((status & BIT_CHK) != 0) {
            atapiBuffer = NULL;
            inp8(controller, ATA_ERR);
            this->lastError = STATUS_ERROR;
            return false;
        }

        unsigned char reason = inp8(controller, ATA_IRR);
        if (((status & BIT_DRQ) != 0) && ((reason & BIT_IO) == 0) && ((reason & BIT_CD) != 0)) break;
    }

    if (i == ATA_TIMEOUT) {
        atapiBuffer = NULL;
        this->lastError = BUSY_TIMEOUT_ERROR;
        return false;
    }

    outp16(controller, (unsigned short*)command->packet, 6);
    for (i = 0; i < ATA_TIMEOUT; i++) {
        protocolInterrupt();
        unsigned char status = inp8(controller, ATA_ASR);
        if ((status & BIT_BSY) != 0) continue;
        if ((status & BIT_CHK) != 0) {
            atapiBuffer = NULL;
            this->lastError = STATUS_ERROR;
            return false;
        }
        if (atapiReadDone) break;
    }

    inp8(controller, ATA_STR);

    if (i == ATA_TIMEOUT) {
        atapiBuffer = NULL;
        this->lastError = BUSY_TIMEOUT_ERROR;
        return false;
    }

    return true;
}

bool IDEDriver::protocolPioDataIn(IDEController* controller, ATACommand* command, unsigned short count, void* buf) {
    unsigned short* p = (unsigned short*)buf;

    if (!selectDevice(controller, command->deviceNo)) {

        this->lastError = SELECTION_ERROR;
        return false;
    }

    outp8(controller, ATA_DCR, 0x02);
    outp8(controller, ATA_FTR, command->feature);
    outp8(controller, ATA_SCR, command->sectorCount);
    outp8(controller, ATA_SNR, command->sectorNumber);
    outp8(controller, ATA_CLR, command->cylinderLow);
    outp8(controller, ATA_CHR, command->cylinderHigh);

    if (command->drdyCheck && !waitDrdySet(controller)) {
        this->lastError = DATA_READY_CHECK_ERROR;
        return false;
    }

    outp8(controller, ATA_CMR, command->command);
    sleep(1);

    inp8(controller, ATA_ASR);

    for (int i = 0; i < count; i++, p+=256) {
        if (!waitBusyClear(controller)) {
            this->lastError = BUSY_TIMEOUT_ERROR;
            return false;
        }

        unsigned char status = inp8(controller, ATA_STR);

        if ((status & BIT_ERR) != 0) {
            this->lastError = STATUS_ERROR;
            return false;
        }

        if ((status & BIT_DRQ) == 0) {
            this->lastError = DATA_READY_CHECK_ERROR;
            return false;
        }

        inp16(controller, p, 512);
    }

    inp8(controller, ATA_ASR);
    unsigned char status = inp8(controller, ATA_STR);

    if (status & BIT_ERR) {
        inp8(controller, ATA_ERR);
        this->lastError = STATUS_ERROR;
        return false;
    }
    return true;
}

void IDEDriver::protocolInterrupt() {
    for (;;) {
        //if (!MONAPI_WAIT_INTERRUPT(1000, whichController->irq)) {
        //    return;
        //}

        unsigned char status = inp8(whichController, ATA_STR);
        unsigned char reason = inp8(whichController, ATA_IRR);

        if (((reason & BIT_IO) != 0) && ((reason & BIT_CD) == 0) && ((status & BIT_DRQ) != 0)) {
            unsigned short transferSize = (inp8(whichController, ATA_BHR) << 8) | inp8(whichController, ATA_BLR);
            atapiTransferSize += transferSize;

            if (atapiTransferSize > atapiTotalReadSize) {
                inp16(whichController, NULL, transferSize);
            } else {
                inp16(whichController, (unsigned short*)atapiBuffer, transferSize);
                atapiBuffer = (void*)((unsigned char*)atapiBuffer + transferSize);
            }
        }

        if (((reason & BIT_IO)!=0) && ((reason & BIT_CD) != 0) && ((status & BIT_DRQ) == 0)) {
            atapiReadDone = true;
            return;
        }
    }
}

bool IDEDriver::commandRead10(IDEController* controller, unsigned int lba, void* buffer, int size) {
    ATAPICommand command;
    memset(&command, 0, sizeof(command));

    int count = (size + ATAPI_SECTOR_SIZE - 1) / ATAPI_SECTOR_SIZE;

    command.feature = 0;
    command.deviceNo = controller->selectedDevice->deviceNo;
    command.packet[0] = 0x28;
    command.packet[2] = (lba >> 24) & 0xff;
    command.packet[3] = (lba >> 16) & 0xff;
    command.packet[4] = (lba >> 8) & 0xff;
    command.packet[5] = (lba ) & 0xff;
    command.packet[7] = (count >> 8) & 0xff;
    command.packet[8] = (count ) & 0xff;
    command.limit = ATAPI_SECTOR_SIZE * count;
    command.buffer = buffer;
    atapiTransferSize = 0;

    return protocolPacket(controller, &command);
}

bool IDEDriver::commandIdentify(IDEController* controller, int deviceNo, unsigned short* buffer) {
    ATACommand command;
    memset(&command, 0, sizeof(command));

    IDEDevice* device = &controller->devices[deviceNo];

    command.deviceNo = deviceNo;
    if (device->type == DEVICE_ATA) {
        command.drdyCheck = true;
        command.command = 0xec;
    } else {
        command.drdyCheck = false;
        command.command = 0xa1;
    }

    bool commandOK = protocolPioDataIn(controller, &command, 1, buffer);

    if (!commandOK) return false;

    unsigned short* p = buffer;
    for (int i = 0; i < 256; i++) {
        unsigned short value = *p;
        *p = ((value >> 8) & 0xff) | ((value << 8) & 0xff00);
        p++;
    }

    return true;
}

void IDEDriver::sleep(unsigned int ms) {
    while (0 < ms--) {
        __asm__ __volatile__ ("outb %%al, $0x80" ::: "%eax");
    }
}

void IDEDriver::initialize(IDEController* controller) {
    outp8(controller, ATA_DCR, 0x06);
    sleep(5);

    outp8(controller, ATA_DCR, 0x02);
    sleep(5);

    setDeviceTypeFirst(controller, MASTER);
    setDeviceTypeSecond(controller, MASTER);

    setDeviceTypeFirst(controller, SLAVE);
    setDeviceTypeSecond(controller, SLAVE);
}

void IDEDriver::setDeviceTypeFirst(IDEController* controller, int deviceNo) {
    unsigned int l;
    unsigned char c;
    unsigned char c1 = 0xff;
    unsigned char c2 = 0xff;
    bool timeout;

    IDEDevice* device = &controller->devices[deviceNo];
    device->deviceNo = deviceNo;

    for (l = 0; l < RETRY_MAX; l++) {

        outp8(controller, ATA_DHR, deviceValue(deviceNo));
        sleep(10);

        c = inp8(controller, ATA_STR);
        if (c == 0xff) break;

        timeout = !waitBusyClear(controller);
        if (timeout) break;


        unsigned char error = inp8(controller, ATA_ERR);
        if (deviceNo == MASTER && (error & 0x7f) != 1) {
            device->type = DEVICE_UNKNOWN;
            return;
        } else if (deviceNo == SLAVE && error != 1) {
            device->type = DEVICE_UNKNOWN;
            return;
        }

        c = inp8(controller, ATA_DHR);
        if ((c & (deviceNo << 4)) == (deviceNo << 4)) {
            c1 = inp8(controller, ATA_CLR);
            c2 = inp8(controller, ATA_CHR);
            break;
        }
    }

    switch (c1 | (c2 << 8)) {
    case 0xEB14:
        device->type = DEVICE_ATAPI;
        break;
    case 0:
        device->type = DEVICE_ATA;
        break;
    default:
        device->type = DEVICE_NONE;
        break;
    }
}

void IDEDriver::setDeviceTypeSecond(IDEController* controller, int deviceNo) {
    unsigned short buffer[256];
    IDEDevice* device = &(controller->devices[deviceNo]);

    if (!waitBusyClear(controller)) {
        device->type = DEVICE_NONE;
        return;
    }

    unsigned char l;
    for (l = 0; l < RETRY_MAX; l++) {
        bool firstResult = commandIdentify(controller, deviceNo, buffer);
        int firstError = this->lastError;
        sleep(5);
        bool secondResult = commandIdentify(controller, deviceNo, buffer);
        int secondError = this->lastError;

        if (firstResult && secondResult) {
            break;
        } else if (!firstResult && !secondResult) {
            if (firstError != secondError) continue;
            if (firstError == SELECTION_ERROR || firstError == BUSY_TIMEOUT_ERROR || firstError == DATA_READY_CHECK_ERROR) {
                device->type = DEVICE_NONE;
                break;
            }
        }
    }

    if (l == RETRY_MAX) {
        device->type = DEVICE_UNKNOWN;
    }

    switch (device->type) {
    case DEVICE_ATA:
        device->typeDetail = -1;
        device->sectorSize = ATA_SECTOR_SIZE;
        break;

    case DEVICE_ATAPI:
        device->typeDetail = buffer[0] & 0x1f;
        device->sectorSize = ATAPI_SECTOR_SIZE;
        break;

    case DEVICE_NONE:
        device->typeDetail = -1;
        break;

    case DEVICE_UNKNOWN:
        device->typeDetail = -1;
        break;
    }
}

bool IDEDriver::selectDevice(IDEController* controller, int deviceNo) {
    if (whichController != NULL) {
        IDEDevice* device = whichController->selectedDevice;
        if (whichController == controller && device->deviceNo == deviceNo) {
            outp8(controller, ATA_DHR, deviceValue(deviceNo));
            sleep(10);
            return true;
        }
    }

    if (!waitBusyAndDataRequestBothClear(controller)) return false;

    outp8(controller, ATA_DHR, deviceValue(deviceNo));
    sleep(10);

    if (!waitBusyAndDataRequestBothClear(controller)) return false;

    whichController = controller;
    whichController->selectedDevice = &controller->devices[deviceNo];
    whichController->selectedDevice->deviceNo = deviceNo;

    return true;
}

unsigned char IDEDriver::deviceValue(int deviceNo) const {
    return (unsigned char)(DEV_HEAD_OBS | (deviceNo << 4));
}
