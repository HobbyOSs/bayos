#ifndef _DRIVER_PCI_H_INCLUDED_
#define _DRIVER_PCI_H_INCLUDED_

//#include <sys/types.h>
//#include <monapi/CString.h>

typedef unsigned char  byte;
typedef unsigned short word;
typedef unsigned int   dword;

/* PCI パケット構造体 */
typedef union
{
    dword command;
    struct {
        unsigned reserved1 : 2;
        unsigned reg       : 6;
        unsigned function  : 3;
        unsigned device    : 5;
        unsigned bus       : 8;
        unsigned reserved2 : 7;
        unsigned enabled   : 1;
    } p;
} PciPacket;

/* PCI 用定数 */
enum {
    REG_CONFIG_ADDRESS = 0x0CF8,
    REG_CONFIG_DATA    = 0x0CFC,

    PCI_VENDOR_ID      = 0x00,
    PCI_DEVICE_ID      = 0x02,
    PCI_COMMAND        = 0x04,
    PCI_STATUS         = 0x06,
    PCI_REVISION       = 0x08,
    PCI_API            = 0x09,
    PCI_SUBCLASS       = 0x0a,
    PCI_BASECLASS      = 0x0b,
    PCI_HEADER         = 0x0e,
    PCI_BASE_ADDRESS1  = 0x10,
    PCI_BASE_ADDRESS2  = 0x14,
    PCI_BASE_ADDRESS3  = 0x18,
    PCI_BASE_ADDRESS4  = 0x1C,
    PCI_BASE_ADDRESS5  = 0x20,
    PCI_IRQ_LINE       = 0x3C,
    PCI_IRQ_PIN        = 0x3D
};

/* PCI 情報構造体 */
typedef struct {
    int   Exist;
    byte  DeviceNo;
    word  Vendor;
    word  Device;
    dword BaseAd;
    dword IrqLine;
} PciInf;

/* PCI ドライバー */
class Pci {
public:
    static void  CheckPciExist(word ChkVendor, word ChkDevice, PciInf* RetPciInf);
    static dword ReadConfig(byte bus, byte device, byte function, byte reg, byte readSize);
};

#endif
