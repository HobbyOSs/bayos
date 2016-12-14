#include "../bayos.h"

void Pci::CheckPciExist(word ChkVendor, word ChkDevice, PciInf* RetPciInf) {
    byte  DeviceNo;
    dword Vendor_Dev;
    word  Vendor;
    word  Device;
    dword BaseAd;
    dword IrqLine;

    RetPciInf->Exist = 1;
    for (DeviceNo = 0; DeviceNo < 32 ; DeviceNo++ ) {
        Vendor = ReadConfig(0, DeviceNo, 0, PCI_VENDOR_ID, 2);
        if (Vendor != 0xFFFF) {
            Device = ReadConfig(0, DeviceNo, 0, PCI_DEVICE_ID, 2);
            if (Device != 0xFFFF && ChkVendor == Vendor && ChkDevice == Device) {
                Vendor_Dev = Vendor + (dword)(Device << 16);
                BaseAd = ReadConfig(0, DeviceNo, 0, PCI_BASE_ADDRESS1, 4);
                IrqLine = ReadConfig(0, DeviceNo, 0, PCI_IRQ_LINE, 1);
                RetPciInf->Exist = 0;
                RetPciInf->DeviceNo = DeviceNo;
                RetPciInf->Vendor = Vendor;
                RetPciInf->Device = Device;
                RetPciInf->BaseAd = BaseAd;
                RetPciInf->IrqLine = IrqLine;
                break;
            }
        }
    }
}

dword Pci::ReadConfig(byte bus, byte device, byte function, byte reg, byte readSize) {
    dword result;
    PciPacket packet;

    packet.p.enabled = 1;
    packet.p.bus = bus;
    packet.p.device = device;
    packet.p.function = function;

    packet.p.reg = (reg & ~3) >> 2;
    packet.p.reserved1 = 0;
    packet.p.reserved2 = 0;

    //Console::printf(" packet.command = %x \n" , packet.command);

    io_out32(REG_CONFIG_ADDRESS, packet.command);

    switch (readSize) {
    case 1:
        result = io_in8(REG_CONFIG_DATA + (reg & 3));
        break;

    case 2:
        result = io_in16(REG_CONFIG_DATA + (reg & 3));
        break;

    case 4:
        result = io_in32(REG_CONFIG_DATA);
        break;

    default:
        result = 0xFFFFFFFF;
        break;
    }

    packet.p.enabled = 0;

    io_out32(REG_CONFIG_ADDRESS, packet.command);

    //Console::printf(" result = %x \n" , result);

    return result;
}
