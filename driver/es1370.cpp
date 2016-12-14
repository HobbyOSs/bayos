#include "../bayos.h"

PciInf* ES1370::pciinfo = NULL;
dword   ES1370::baseIO  = 0;

typedef struct {
    unsigned short buffersize;
    unsigned short currentcount;
}
FrameRegister2;

bool ES1370::existDevice() {
    if (ES1370::pciinfo == NULL) {
        ES1370::pciinfo = new PciInf();
    }

    Pci::CheckPciExist(ES1370_VENDOR_ID, ES1370_DEVICE_ID, pciinfo);
    if ( pciinfo->Exist != 0 ) {
        return false;
    }

    Console::printf("ES1370 is exist.\n");
    Console::printf("DeviceNo = %x\n",    pciinfo->DeviceNo);
    Console::printf("Vendor = %x\n",      pciinfo->Vendor);
    Console::printf("Device = %x\n",      pciinfo->Device);
    Console::printf("BaseAddress = %x\n", pciinfo->BaseAd);
    Console::printf("IrqLine = %x\n",     pciinfo->IrqLine);

    baseIO = pciinfo->BaseAd&~1;

    return true;
}

void ES1370::setIRQ() {
    io_out8(PIC1_IMR, 0xed);
    //syscall_set_irq_receiver(pciinfo->IrqLine, false);
}

void ES1370::unsetIRQ() {
    io_out8(PIC1_IMR, 0xef);
    //syscall_remove_irq_receiver(pciinfo->IrqLine);
}

void ES1370::readConf() {
    dword result;
    result = Pci::ReadConfig(0, pciinfo->DeviceNo, 0, 0x00, 2);
    Console::printf("Vendor: %x\n", result);
    result = Pci::ReadConfig(0, pciinfo->DeviceNo, 0, 0x04, 2);
    result = Pci::ReadConfig(0, pciinfo->DeviceNo, 0, 0x04, 2);
    Console::printf("Command: %x\n", result);
    result = Pci::ReadConfig(0, pciinfo->DeviceNo, 0, 0x06, 2);
    Console::printf("Status: %x\n", result);
    result = Pci::ReadConfig(0, pciinfo->DeviceNo, 0, 0x08, 4);
    Console::printf("Class Code & Revision ID: %x\n", result);
    result = Pci::ReadConfig(0, pciinfo->DeviceNo, 0, 0x0D, 1);
    Console::printf("Latency Timer: %x\n", result);
    result = Pci::ReadConfig(0, pciinfo->DeviceNo, 0, 0x10, 4);
    Console::printf("BaseAddress: %x\n", result);
}

void ES1370::dumpRegisters() {
    dword result;

    result = io_in32(baseIO+ES1370_REG_CONTROL);
    Console::printf("Control: %x\n", result);

    result = io_in32(baseIO+ES1370_REG_STATUS);
    Console::printf("Status: %x\n", result);

    result = io_in8(baseIO+ES1370_REG_UART_DATA);
    Console::printf("UART Data: %x\n", result);

    result = io_in8(baseIO+ES1370_REG_UART_STATUS);
    Console::printf("UART Status: %x\n", result);

    result = io_in32(baseIO+ES1370_REG_MEMPAGE);
    Console::printf("Memory Page: %x\n", result);

    result = io_in32(baseIO+ES1370_REG_SERIAL_CONTROL);
    Console::printf("Serial Interface Control: %x\n", result);

    result = io_in32(baseIO+ES1370_REG_DAC1_FRAMEADR);
    Console::printf("DAC1 Frame Address: %x\n", result);

    result = io_in32(baseIO+ES1370_REG_DAC1_FRAMECNT);
    Console::printf("DAC1 Frame Count & Size: %x\n", result);
}

void ES1370::setMempage(int p) {
    io_out32(baseIO+ES1370_REG_MEMPAGE, (dword)p);
}

void ES1370::enableDAC1Channel() {
    io_out32(baseIO+ES1370_REG_CONTROL,io_in32(baseIO+ES1370_REG_CONTROL)|ES1370_DAC1_EN);
}

void ES1370::disableDAC1Channel() {
    io_out32(baseIO+ES1370_REG_CONTROL,io_in32(baseIO+ES1370_REG_CONTROL)&~ES1370_DAC1_EN);
}

void ES1370::setSampleRate(int rate) {
    int bit = 0;
    dword n;
    switch (rate) {
    case 5512:
        bit = 0;
        break;
    case 11025:
        bit = 1;
        break;
    case 22050:
        bit = 2;
        break;
    case 44100:
        bit = 3;
        break;
    default:
        break;
    }
    n = io_in32(baseIO+ES1370_REG_CONTROL);
    n = n & ~0x3000;
    n |= bit;
    io_out32(baseIO+ES1370_REG_CONTROL, n);
}

void ES1370::startDAC1() {
    SerialControlRegister(SerialControlRegister()&~ES1370_P1_PAUSE);
}

void ES1370::stopDAC1() {
    SerialControlRegister(SerialControlRegister()|ES1370_P1_PAUSE);
}

void ES1370::playData(void* pm, size_t size) {
    //byte *dmabuf;

    //Console::printf("%x\n", (dword) pm);
    //dmabuf = new byte[size];//monapi_allocate_dma_memory(size);
    //Console::printf("DMA Address = %x\n", (dword) dmabuf);

    //memcpy(dmabuf, pm, size);

    disableDAC1Channel();
    writeControlRegister(readControlRegister()&~1);
    setMempage(ES1370_PAGE_DAC&0x0f);
    setSampleRate(44100);
//  setMonoMode(DAC1, 8);
    setStereoMode(DAC1, 8);
    setLoopMode(DAC1);
//  setStopMode(DAC1);
    Console::printf("size = %d\n", size);
    DAC1FrameRegister((byte *) pm, size);
    SerialControlRegister(SerialControlRegister()&~(ES1370_P1_LOOP_SEL|ES1370_P1_PAUSE|ES1370_P1_SCT_RLD|ES1370_P1_S_EB|ES1370_P1_S_MB));
//  SCT_RLD();
    startDAC1();
    enableInterrupt(DAC1);
    enableDAC1Channel();
    Console::printf("playing...\n");

    //sleep(1000);

    stopDAC1();
    dumpRegisters();

    //delete [] dmabuf;
    //monapi_deallocate_dma_memory(dmabuf, size);
}

dword ES1370::readControlRegister() {
    return io_in32(baseIO+ES1370_REG_CONTROL);
}

void ES1370::writeControlRegister(dword n) {
    io_out32(baseIO+ES1370_REG_CONTROL, n);
}

dword ES1370::SerialControlRegister() {
    return io_in32(baseIO+ES1370_REG_SERIAL_CONTROL);
}

void ES1370::SerialControlRegister(dword n) {
    io_out32(baseIO+ES1370_REG_SERIAL_CONTROL, n);
}

void ES1370::DAC1FrameRegister(void *p, size_t size) {
    int n;
    FrameRegister2 fr;
    fr.currentcount = 0;
    fr.buffersize = (unsigned short)size;
    memcpy(&n, &fr, sizeof(int));
    io_out32(baseIO+ES1370_REG_DAC1_FRAMEADR, (dword)p);
    io_out32(baseIO+ES1370_REG_DAC1_FRAMECNT, (dword)n);
}

void ES1370::setStereoMode(Channel ch, int bits) {
    if ( bits == 16 ) {
        switch (ch) {
        case DAC1:
            SerialControlRegister(SerialControlRegister()|ES1370_P1_S_EB|ES1370_P1_S_MB);
            break;
        case DAC2:
            SerialControlRegister(SerialControlRegister()|ES1370_P2_S_EB|ES1370_P2_S_MB);
            break;
        case ADC:
            break;
        }
    } else if ( bits == 8 ) {
        switch (ch) {
        case DAC1:
            SerialControlRegister(SerialControlRegister()|ES1370_P1_S_MB);
            break;
        case DAC2:
            SerialControlRegister(SerialControlRegister()|ES1370_P2_S_MB);
            break;
        case ADC:
            break;
        }
    }
}

void ES1370::setMonoMode(Channel ch, int bits) {
    if ( bits == 16 ) {
        switch (ch) {
        case DAC1:
            SerialControlRegister(SerialControlRegister()|ES1370_P1_S_EB);
            break;
        case DAC2:
            SerialControlRegister(SerialControlRegister()|ES1370_P2_S_EB);
            break;
        case ADC:
            break;
        }
    } else if ( bits == 8 ) {
        switch (ch) {
        case DAC1:
            SerialControlRegister(SerialControlRegister()&~(ES1370_P1_S_MB|ES1370_P1_S_EB));
            break;
        case DAC2:
            SerialControlRegister(SerialControlRegister()&~(ES1370_P2_S_MB|ES1370_P2_S_EB));
            break;
        case ADC:
            break;
        }
    }
}

void ES1370::setLoopMode(Channel ch) {
    switch (ch) {
    case DAC1:
        SerialControlRegister(SerialControlRegister()&~ES1370_P1_LOOP_SEL);
        break;
    case DAC2:
        break;
    case ADC:
        break;
    }
}

void ES1370::setStopMode(Channel ch) {
    switch (ch) {
    case DAC1:
        SerialControlRegister(SerialControlRegister()|ES1370_P1_LOOP_SEL);
        break;
    case DAC2:
        break;
    case ADC:
        break;
    }
}

void ES1370::enableInterrupt(Channel ch) {
    switch (ch) {
    case DAC1:
        SerialControlRegister(SerialControlRegister()|ES1370_P1_INTR_EN);
        break;
    case DAC2:
        SerialControlRegister(SerialControlRegister()|ES1370_P2_INTR_EN);
        break;
    case ADC:
        break;
    }
}

void ES1370::SCT_RLD() {
    SerialControlRegister(SerialControlRegister()|ES1370_P1_SCT_RLD);
}

/* サウンドタスク */
void task_sound(void) {
    if ( !ES1370::existDevice() ) {
        Console::printf("Couldn't find device `ES1370`\n");
    } else {
        ES1370::setIRQ();
        ES1370::readConf();
        ES1370::dumpRegisters();

        /* サイン波 */
        char* buf = new char[44100];
        for( int i = 0 ; i < 44100 ; i++ ) {
            if( i % 20 < 10 ) {
                buf[i] = 200;
            } else {
                buf[i] = -200;
            }
        }

        ES1370::playData(buf, 44100);

        delete [] buf;
    }

    for (;;) {
        io_hlt();
    }
}

/* サウンドハンドラ */
void inthandler29(int *esp) {
    io_out8(PIC1_OCW2, 0x61);   /* IRQ-09受付完了をPIC1に通知 */
    io_out8(PIC0_OCW2, 0x62);   /* IRQ-02受付完了をPIC0に通知 */
    return;
}
