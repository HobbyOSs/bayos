#include "../bayos.h"

/* 記述子の初期化 */
void Descriptor::init(void) {
    SegmentDescriptor* gdt = (SegmentDescriptor *) ADDRESS_GDT;
    GateDescriptor*    idt = (GateDescriptor    *) ADDRESS_IDT;

    /*
      GDTの初期化
      0x00000000 - 0xffffffff -- カーネルデータセグメント (4GB)
      0x00280000 - 0x002fffff -- カーネルコードセグメント (512KB)
    */
    for (int i = 0; i <= LIMIT_GDT / 8; i++) {
        setSegmentDescriptor(gdt + i, 0, 0, 0);
    }
    setSegmentDescriptor(gdt + 1, 0xffffffff,   0x00000000,     AR_DATA32_RW);
    setSegmentDescriptor(gdt + 2, LIMIT_KERNEL, ADDRESS_KERNEL, AR_CODE32_ER);
    load_gdtr(LIMIT_GDT, ADDRESS_GDT);

    /* IDTの初期化 */
    for (int i = 0; i <= LIMIT_IDT / 8; i++) {
        setGateDescriptor(idt + i, 0, 0, 0);
    }
    load_idtr(LIMIT_IDT, ADDRESS_IDT);

    /*
      IDTの設定
      asm_inthandler0c -- スタック例外
      asm_inthandler0d -- 一般保護例外
      asm_inthandler20 -- タイマー割り込み
      asm_inthandler21 -- PS/2キーボード割り込み
      asm_inthandler27 -- PIC0からの不完全割り込み対策
      asm_inthandler29 -- サウンド割り込み
      asm_inthandler2c -- PS/2マウス割り込み
      asm_hrb_api      -- システムコール
    */
    setGateDescriptor(idt + 0x07, (int) asm_inthandler07, 2 * 8, AR_INTGATE32);
    setGateDescriptor(idt + 0x0c, (int) asm_inthandler0c, 2 * 8, AR_INTGATE32);
    setGateDescriptor(idt + 0x0d, (int) asm_inthandler0d, 2 * 8, AR_INTGATE32);
    setGateDescriptor(idt + 0x20, (int) asm_inthandler20, 2 * 8, AR_INTGATE32);
    setGateDescriptor(idt + 0x21, (int) asm_inthandler21, 2 * 8, AR_INTGATE32);
    setGateDescriptor(idt + 0x27, (int) asm_inthandler27, 2 * 8, AR_INTGATE32);
    setGateDescriptor(idt + 0x2c, (int) asm_inthandler2c, 2 * 8, AR_INTGATE32);
    setGateDescriptor(idt + 0x40, (int) asm_hrb_api,      2 * 8, AR_INTGATE32 + 0x60);

    return;
}

/* セグメント記述子を設定する */
void Descriptor::setSegmentDescriptor(SegmentDescriptor* sd, unsigned int limit, int base, int ar) {
    if (limit > 0xfffff) {
        ar |= 0x8000; /* G_bit = 1 */
        limit /= 0x1000;
    }

    sd->limit_low    = limit & 0xffff;
    sd->base_low     = base & 0xffff;
    sd->base_mid     = (base >> 16) & 0xff;
    sd->access_right = ar & 0xff;
    sd->limit_high   = ((limit >> 16) & 0x0f) | ((ar >> 8) & 0xf0);
    sd->base_high    = (base >> 24) & 0xff;

    return;
}

/* 割り込み記述子を設定する */
void Descriptor::setGateDescriptor(GateDescriptor* gd, int offset, int selector, int ar) {
    gd->offset_low   = offset & 0xffff;
    gd->selector     = selector;
    gd->dw_count     = (ar >> 8) & 0xff;
    gd->access_right = ar & 0xff;
    gd->offset_high  = (offset >> 16) & 0xffff;

    return;
}
