/*!
    \file  IDEDriver.h
    \brief IDEDriver

    Copyright (c) 2004 HigePon
    WITHOUT ANY WARRANTY

    \author  HigePon
    \version $Revision: 3344 $
    \date   create:2004/07/04 update:$Date: 2006-07-21 03:03:17 +0900 (Fri, 21 Jul 2006) $
*/
#ifndef _DRIVER_IDE_H_INCLUDED_
#define _DRIVER_IDE_H_INCLUDED_

namespace driver {
    enum {
        PRIMARY   = 0,
        SECONDARY = 1,
        MASTER    = 0,
        SLAVE     = 1,
        DEVICE_UNKNOWN,
        DEVICE_NONE,
        DEVICE_ATA,
        DEVICE_ATAPI
    };

    enum {
        SELECTION_ERROR = 1,
        DATA_READY_CHECK_ERROR,
        BUSY_TIMEOUT_ERROR,
        STATUS_ERROR
    };

    enum {
        ATA_DTR        = 0,
        ATA_ERR        = 1,
        ATA_FTR        = 1,
        ATA_SCR        = 2,
        ATA_IRR        = 2,
        ATA_SNR        = 3,
        ATA_CLR        = 4,
        ATA_BLR        = 4,
        ATA_CHR        = 5,
        ATA_BHR        = 5,
        ATA_DHR        = 6,
        ATA_STR        = 7,
        ATA_CMR        = 7,
        ATA_ASR        = 8,
        ATA_DCR        = 8,
        ATA_TIMEOUT    = 100000, // for Virtual PC changed from 100000 -> 10000
        BIT_BSY        = 0x80,
        BIT_DRDY       = 0x40,
        BIT_DRQ        = 8,
        BIT_ABRT       = 4,
        BIT_CHK        = 1,
        BIT_ERR        = 1,
        BIT_IO         = 2,
        BIT_CD         = 1,
        RETRY_MAX      = 2,
        DEV_HEAD_OBS   = 0xa0,
        LBA_FLG        = 0x40,
        REQUEST_SENSE_BUFFER_SIZE = 18,

        ATAPI_SECTOR_SIZE = 2048,
        ATA_SECTOR_SIZE   = 512
    };

    typedef struct {
        int  type;
        int  typeDetail;
        int  deviceNo;
        word sectorSize;
    } IDEDevice;

    typedef struct {
        byte irq;
        int registers[10];
        IDEDevice devices[2];
        IDEDevice* selectedDevice;
    } IDEController;

    typedef struct {
        byte feature;
        byte sectorCount;
        byte sectorNumber;
        byte cylinderLow;
        byte cylinderHigh;
        byte deviceNo;
        byte command;
        bool drdyCheck;
    } ATACommand;

    typedef struct {
        byte  feature;
        byte  deviceNo;
        byte  packet[12];
        word  limit;
        void* buffer;
    } ATAPICommand;

    /*----------------------------------------------------------------------
        IDEDriver
    ----------------------------------------------------------------------*/
    class IDEDriver {
    public:
        IDEDriver(int irq_primary, int irq_secondary);
        //virtual ~IDEDriver();

    public:
        int read(dword lba, void* buf, int size);

    public:
        void protocolInterrupt();
        bool selectDevice(int controller, int deviceNo);
        bool findDevice(int type, int detail, int* controller, int* deviceNo);

    private:
        /* I/O */
        void outp8(IDEController* controller, int reg, byte value);
        byte inp8(IDEController* controller, int reg);
        void inp16(IDEController* controller, word* data, int length);
        word inp16(IDEController* controller, int reg);
        void outp16(IDEController* controller, int reg, word value);
        void outp16(IDEController* controller, word* data, int length);

        /* flag utilities */
        bool waitBusyClear(IDEController* controller);
        bool waitBusyAndDataRequestBothClear(IDEController* controller);
        bool waitDrdySet(IDEController* controller);

        /* protocol: param IDEController. this layer returns error code */
        bool protocolPacket(IDEController* controller, ATAPICommand* command);
        bool protocolPioDataIn(IDEController* controller, ATACommand* command, word count, void* buf);

        /* command : execute command using protocol function */
        bool commandRead10(IDEController* controller, dword lba, void* buffer, int size);
        bool commandIdentify(IDEController* controller, int deviceNo, word* buffer);

        /* private : functions */
        void sleep(dword ms);
        void initialize(IDEController* controller);
        void setDeviceTypeFirst(IDEController* controller, int deviceNo);
        void setDeviceTypeSecond(IDEController* controller, int deviceNo);
        bool selectDevice(IDEController* controller, int deviceNo);
        byte deviceValue(int deviceNo) const;

    private:
        IDEController controllers[2];
        IDEController* whichController;
        volatile void* atapiBuffer;
        volatile int atapiReadDone;
        volatile dword atapiTransferSize;
        volatile dword atapiTotalReadSize;
        byte requestSenseBuffer[REQUEST_SENSE_BUFFER_SIZE];
        int lastError;
    };
}

#endif
