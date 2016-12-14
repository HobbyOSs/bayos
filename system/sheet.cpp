#include "../bayos.h"

int     SheetCtl::xsize    = 0;
int     SheetCtl::ysize    = 0;
int     SheetCtl::top      = 0;
byte*   SheetCtl::map      = NULL;
word*   SheetCtl::vram     = NULL;
Sheet** SheetCtl::sheets   = NULL;
Sheet*  SheetCtl::sheets0  = NULL;
Sheet*  SheetCtl::back     = NULL;
byte*   SheetCtl::zenkaku  = NULL;
int*    SheetCtl::offsets  = NULL;
WSTR_INFO* SheetCtl::wstrinfo = NULL;

#define inGetUInt16(b) (word)((word)((b)[1]) << 8 | (word)((b)[0]))

/* 初期化 */
void SheetCtl::init() {
    /* 画面のパラメータ */
    BOOT_PARAM* boot_param = (BOOT_PARAM *) ADR_BOOTINFO;

    /* 下敷き一覧の初期化 */
    SheetCtl::xsize = boot_param->screen_x;
    SheetCtl::ysize = boot_param->screen_y;
    SheetCtl::top   = -1; /* シートは一枚もない */
    SheetCtl::map   = (byte *) malloc(SheetCtl::xsize * SheetCtl::ysize);
    SheetCtl::vram  = (word *) boot_param->vram;
    SheetCtl::sheets  = new Sheet*[MAX_SHEETS];
    SheetCtl::sheets0 = new Sheet[MAX_SHEETS];
    for (int i = 0; i < MAX_SHEETS; i++) {
        SheetCtl::sheets0[i].flags = 0; /* 未使用マーク */
    }

    /* 壁紙 */
    back = SheetCtl::allocate();
    word* buffer = (word *) malloc(SheetCtl::xsize * SheetCtl::ysize * sizeof(short));
    SheetCtl::setbuf(back, buffer, SheetCtl::xsize, SheetCtl::ysize, -1);
    #if 0
    for (int i = 0; i < SheetCtl::ysize; i++) {
        for (int j = 0; j < SheetCtl::xsize; j++) {
            back->buffer[i * SheetCtl::xsize + j] = 0xDF1F;
        }
    }
    #endif
    #if 1
    FileEntry* entry = File::load("BAYOS.BM5");
    if (entry != NULL) {
        byte* aData = entry->data;
        /* 壁紙を２枚左右対称に貼る */
        for (int i = 0; i < WALLPAPER_HEIGHT; i++) {
            for (int j = 0; j < WALLPAPER_WIDTH; j++) {
                int offset = 0x36 + i * WALLPAPER_WIDTH * 3 + j * 3;
                byte b = aData[offset];
                byte g = aData[offset + 1];
                byte r = aData[offset + 2];
                word color = (word)(((r << 8) & 0xf800) | ((g << 3) & 0x07e0) | (b >> 3));
                back->buffer[(SheetCtl::ysize - 1 - i) * SheetCtl::xsize + j] = color;
                back->buffer[(WALLPAPER_HEIGHT - i - 1) * SheetCtl::xsize + j] = color;
            }
        }
    }
    #endif
    #if 0
    FileEntry* entry = File::load("BAYOS.JPG");
    if (entry != NULL) {
        CJPEGLS* cjpegls = new CJPEGLS();
        cjpegls->Open(entry->data, entry->size);
        int w, h;
        cjpegls->GetInfo(&w, &h);
        byte* buffer = new byte[w * h * 3];
        cjpegls->Decode(buffer);
        delete(cjpegls);
        for (int i = 0; i < h; i++) {
            for (int j = 0; j < w; j++) {
                int I = (i * w + j) * 3;
                byte r = buffer[I + 0];
                byte g = buffer[I + 1];
                byte b = buffer[I + 2];
                word color = (word)(((r << 8) & 0xf800) | ((g << 3) & 0x07e0) | (b >> 3));
                back->buffer[i * w + j] = color;
            }
        }
        delete(buffer);
    }
    #endif
    SheetCtl::updown(back, 0);

    /* 全角フォントの読み込み */
    FileEntry* font = File::load("SHGOTH12.UF5");
    if (font->size > 0) {
        SheetCtl::zenkaku = font->data;
        SheetCtl::offsets = new int[65536];
        int num = inGetUInt16(&SheetCtl::zenkaku[0]);
        int pos = 4;
        for (int i = 0; i < num; i++) {
            int fcode = inGetUInt16(&SheetCtl::zenkaku[pos]);
            offsets[fcode] = pos;
            pos += 4;
            byte fw = SheetCtl::zenkaku[pos++];
            byte fh = SheetCtl::zenkaku[pos++];
            pos += (int)((fw * fh + 7) / 8);
        }
    }
    SheetCtl::wstrinfo = new WSTR_INFO();
}

/* 下敷きを取得する */
Sheet *SheetCtl::allocate() {
    Sheet *sht;
    for (int i = 0; i < MAX_SHEETS; i++) {
        if (SheetCtl::sheets0[i].flags == 0) {
            sht = &SheetCtl::sheets0[i];
            sht->flags =  1; /* 使用中マーク */
            sht->depth = -1; /* 非表示中 */
            sht->task  = Scheduler::current;
            return sht;
        }
    }
    return 0; /* 全てのシートが使用中だった */
}

/* 下敷きのサイズとバッファを設定する */
void SheetCtl::setbuf(Sheet* sht, word* buf, int xsize, int ysize, int transparent) {
    sht->buffer      = buf;
    sht->width       = xsize;
    sht->height      = ysize;
    sht->transparent = transparent;
}

/* マップ更新（内部関数）*/
void SheetCtl::refreshmap(int vx0, int vy0, int vx1, int vy1, int h0) {
    int h, bx, by, vx, vy, bx0, by0, bx1, by1, sid4, *p;
    byte sid, *map = SheetCtl::map;
    word *buf;
    Sheet *sht;
    if (vx0 < 0) {
        vx0 = 0;
    }
    if (vy0 < 0) {
        vy0 = 0;
    }
    if (vx1 > SheetCtl::xsize) {
        vx1 = SheetCtl::xsize;
    }
    if (vy1 > SheetCtl::ysize) {
        vy1 = SheetCtl::ysize;
    }
    for (h = h0; h <= SheetCtl::top; h++) {
        sht = SheetCtl::sheets[h];
        sid = sht - SheetCtl::sheets0; /* 番地を引き算してそれを下じき番号として利用 */
        buf = sht->buffer;
        bx0 = vx0 - sht->vx0;
        by0 = vy0 - sht->vy0;
        bx1 = vx1 - sht->vx0;
        by1 = vy1 - sht->vy0;
        if (bx0 < 0) {
            bx0 = 0;
        }
        if (by0 < 0) {
            by0 = 0;
        }
        if (bx1 > sht->width) {
            bx1 = sht->width;
        }
        if (by1 > sht->height) {
            by1 = sht->height;
        }
        if (sht->transparent == -1) {
            if ((sht->vx0 & 3) == 0 && (bx0 & 3) == 0 && (bx1 & 3) == 0) {
                /* 透明色なし専用の高速版（4バイト型） */
                bx1 = (bx1 - bx0) / 4; /* MOV回数 */
                sid4 = sid | sid << 8 | sid << 16 | sid << 24;
                for (by = by0; by < by1; by++) {
                    vy = sht->vy0 + by;
                    vx = sht->vx0 + bx0;
                    p = (int *) &map[vy * SheetCtl::xsize + vx];
                    for (bx = 0; bx < bx1; bx++) {
                        p[bx] = sid4;
                    }
                }
            } else {
                /* 透明色なし専用の低速版（1バイト型） */
                for (by = by0; by < by1; by++) {
                    vy = sht->vy0 + by;
                    for (bx = bx0; bx < bx1; bx++) {
                        vx = sht->vx0 + bx;
                        map[vy * SheetCtl::xsize + vx] = sid;
                    }
                }
            }
        } else {
            /* 透明色ありの一般版 */
            for (by = by0; by < by1; by++) {
                vy = sht->vy0 + by;
                for (bx = bx0; bx < bx1; bx++) {
                    vx = sht->vx0 + bx;
                    if (buf[by * sht->width + bx] != sht->transparent) {
                        map[vy * SheetCtl::xsize + vx] = sid;
                    }
                }
            }
        }
    }
}

/* 画面更新（内部関数）*/
void SheetCtl::refreshsub(int vx0, int vy0, int vx1, int vy1, int h0, int h1) {
    int h, bx, by, vx, vy, bx0, by0, bx1, by1, bx2, i, i1, *q, *r;
    byte *map = SheetCtl::map, sid;
    word *vram = SheetCtl::vram, *buf, sid2, *p;
    Sheet *sht;
    /* refresh範囲が画面外にはみ出していたら補正 */
    if (vx0 < 0) {
        vx0 = 0;
    }
    if (vy0 < 0) {
        vy0 = 0;
    }
    if (vx1 > SheetCtl::xsize) {
        vx1 = SheetCtl::xsize;
    }
    if (vy1 > SheetCtl::ysize) {
        vy1 = SheetCtl::ysize;
    }
    for (h = h0; h <= h1; h++) {
        sht = SheetCtl::sheets[h];
        buf = sht->buffer;
        sid = sht - SheetCtl::sheets0;
        /* vx0～vy1を使って、bx0～by1を逆算する */
        bx0 = vx0 - sht->vx0;
        by0 = vy0 - sht->vy0;
        bx1 = vx1 - sht->vx0;
        by1 = vy1 - sht->vy0;
        if (bx0 < 0) {
            bx0 = 0;
        }
        if (by0 < 0) {
            by0 = 0;
        }
        if (bx1 > sht->width) {
            bx1 = sht->width;
        }
        if (by1 > sht->height) {
            by1 = sht->height;
        }
        if ((sht->vx0 & 2) == 0) {
            /* 4バイト型 */
            i  = (bx0 + 1) / 2; /* bx0を2で割ったもの（端数切り上げ） */
            i1 =  bx1      / 2; /* bx1を2で割ったもの（端数切り捨て） */
            i1 = i1 - i;
            sid2 = sid | sid << 8;
            for (by = by0; by < by1; by++) {
                vy = sht->vy0 + by;
                for (bx = bx0; bx < bx1 && (bx & 1) != 0; bx++) {
                    /* 前の端数を1バイトずつ */
                    vx = sht->vx0 + bx;
                    if (map[vy * SheetCtl::xsize + vx] == sid) {
                        vram[vy * SheetCtl::xsize + vx] = buf[by * sht->width + bx];
                    }
                }
                vx = sht->vx0 + bx;
                p = (word *) &map[vy * SheetCtl::xsize + vx];
                q = (int  *) &vram[vy * SheetCtl::xsize + vx];
                r = (int  *) &buf[by * sht->width + bx];
                for (i = 0; i < i1; i++) {
                    /* 2の倍数部分 */
                    if (p[i] == sid2) {
                        q[i] = r[i];
                    } else {
                        bx2 = bx + i * 2;
                        vx = sht->vx0 + bx2;
                        if (map[vy * SheetCtl::xsize + vx + 0] == sid) {
                            vram[vy * SheetCtl::xsize + vx + 0] = buf[by * sht->width + bx2 + 0];
                        }
                        if (map[vy * SheetCtl::xsize + vx + 1] == sid) {
                            vram[vy * SheetCtl::xsize + vx + 1] = buf[by * sht->width + bx2 + 1];
                        }
                    }
                }
                for (bx += i1 * 2; bx < bx1; bx++) {
                    /* 後ろの端数を1バイトずつ */
                    vx = sht->vx0 + bx;
                    if (map[vy * SheetCtl::xsize + vx] == sid) {
                        vram[vy * SheetCtl::xsize + vx] = buf[by * sht->width + bx];
                    }
                }
            }
        } else {
            /* 2バイト型 */
            for (by = by0; by < by1; by++) {
                vy = sht->vy0 + by;
                for (bx = bx0; bx < bx1; bx++) {
                    vx = sht->vx0 + bx;
                    if (map[vy * SheetCtl::xsize + vx] == sid) {
                        vram[vy * SheetCtl::xsize + vx] = buf[by * sht->width + bx];
                    }
                }
            }
        }
    }
}

/* 下敷きの深さ更新 */
void SheetCtl::updown(Sheet* sht, int depth) {
    int h, old = sht->depth; /* 設定前の高さを記憶する */

    /* 指定が低すぎや高すぎだったら、修正する */
    if (depth > SheetCtl::top + 1) {
        depth = SheetCtl::top + 1;
    }
    if (depth < -1) {
        depth = -1;
    }
    sht->depth = depth; /* 高さを設定 */

    /* 以下は主にsheets[]の並べ替え */
    if (old > depth) {
        /* 以前よりも低くなる */
        if (depth >= 0) {
            /* 間のものを引き上げる */
            for (h = old; h > depth; h--) {
                SheetCtl::sheets[h] = SheetCtl::sheets[h - 1];
                SheetCtl::sheets[h]->depth = h;
            }
            SheetCtl::sheets[depth] = sht;
            SheetCtl::refreshmap(sht->vx0, sht->vy0, sht->vx0 + sht->width, sht->vy0 + sht->height, depth + 1);
            SheetCtl::refreshsub(sht->vx0, sht->vy0, sht->vx0 + sht->width, sht->vy0 + sht->height, depth + 1, old);
        } else {
            /* 非表示化 */
            if (SheetCtl::top > old) {
                /* 上になっているものをおろす */
                for (h = old; h < SheetCtl::top; h++) {
                    SheetCtl::sheets[h] = SheetCtl::sheets[h + 1];
                    SheetCtl::sheets[h]->depth = h;
                }
            }
            SheetCtl::top--; /* 表示中の下じきが一つ減るので、一番上の高さが減る */
            SheetCtl::refreshmap(sht->vx0, sht->vy0, sht->vx0 + sht->width, sht->vy0 + sht->height, 0);
            SheetCtl::refreshsub(sht->vx0, sht->vy0, sht->vx0 + sht->width, sht->vy0 + sht->height, 0, old - 1);
        }
    } else if (old < depth) {
        /* 以前よりも高くなる */
        if (old >= 0) {
            /* 間のものを押し下げる */
            for (h = old; h < depth; h++) {
                SheetCtl::sheets[h] = SheetCtl::sheets[h + 1];
                SheetCtl::sheets[h]->depth = h;
            }
            SheetCtl::sheets[depth] = sht;
        } else {
            /* 非表示状態から表示状態へ */
            /* 上になるものを持ち上げる */
            for (h = SheetCtl::top; h >= depth; h--) {
                SheetCtl::sheets[h + 1] = SheetCtl::sheets[h];
                SheetCtl::sheets[h + 1]->depth = h + 1;
            }
            SheetCtl::sheets[depth] = sht;
            SheetCtl::top++; /* 表示中の下じきが一つ増えるので、一番上の高さが増える */
        }
        SheetCtl::refreshmap(sht->vx0, sht->vy0, sht->vx0 + sht->width, sht->vy0 + sht->height, depth);
        SheetCtl::refreshsub(sht->vx0, sht->vy0, sht->vx0 + sht->width, sht->vy0 + sht->height, depth, depth);
    }
}

/* 下敷きの部分再描画 */
void SheetCtl::refresh(Sheet* sht, int bx0, int by0, int bx1, int by1) {
    if (sht->depth >= 0) {
        /* もしも表示中なら、新しい下じきの情報に沿って画面を描き直す */
        SheetCtl::refreshsub(sht->vx0 + bx0, sht->vy0 + by0, sht->vx0 + bx1, sht->vy0 + by1, sht->depth, sht->depth);
    }
}

/* 下敷きの移動 */
void SheetCtl::slide(Sheet* sht, int vx0, int vy0) {
    int old_vx0 = sht->vx0, old_vy0 = sht->vy0;
    vx0 = (vx0 + 2) & ~3; /* 4ドットずつしか動かせない */
    vy0 = (vy0 + 2) & ~3; /* 4ドットずつしか動かせない */
    sht->vx0 = vx0;
    sht->vy0 = vy0;
    if (sht->depth >= 0) {
        /* もしも表示中なら、新しい下じきの情報に沿って画面を描き直す */
        SheetCtl::refreshmap(old_vx0, old_vy0, old_vx0 + sht->width, old_vy0 + sht->height, 0);
        SheetCtl::refreshmap(vx0, vy0, vx0 + sht->width, vy0 + sht->height, sht->depth);
        SheetCtl::refreshsub(old_vx0, old_vy0, old_vx0 + sht->width, old_vy0 + sht->height, 0, sht->depth - 1);
        SheetCtl::refreshsub(vx0, vy0, vx0 + sht->width, vy0 + sht->height, sht->depth, sht->depth);
    }
}

/* 下敷きの破棄 */
void SheetCtl::dispose(Sheet* sht) {
    if (sht->depth >= 0) {
        SheetCtl::updown(sht, -1); /* 表示中ならまず非表示にする */
    }
    sht->flags = 0; /* 未使用マーク */
}

/* 点を打つ */
void SheetCtl::drawPixel(Sheet* sht, int x, int y, word col) {
    int tx = 0;
    int ty = 0;
    int cw = sht->width;

    sht->buffer[(tx + x) + cw * (ty + y)] = col;
}

/* 線を引く */
void SheetCtl::drawLine(Sheet* sht, int x0, int y0, int x1, int y1, word col) {
    int tx = 0;
    int ty = 0;
    int cw = sht->width;
    int dx = (x0 > x1) ? (x0 - x1) : (x1 - x0);
    int dy = (y0 > y1) ? (y0 - y1) : (y1 - y0);

    if (dx == 0 && dy == 0) {
        sht->buffer[(tx + x0) + cw * (ty + y0)] = col;
    } else if (dx >= dy) {
        if (x0 > x1) {
            int tx = x0;
            x0 = x1;
            x1 = tx;
            int ty = y0;
            y0 = y1;
            y1 = ty;
        }
        for (int x = x0; x <= x1; x++) {
            sht->buffer[(tx + x) + cw * (ty + ((2 * y0 + 2 * (y1 - y0) * (x - x0) / (x1 - x0)) + 1) / 2)] = col;
        }
    } else {
        if (y0 > y1) {
            int tx = x0;
            x0 = x1;
            x1 = tx;
            int ty = y0;
            y0 = y1;
            y1 = ty;
        }
        for (int y = y0; y <= y1; y++) {
            sht->buffer[(tx + (2 * x0 + 2 * (x1 - x0) * (y - y0) / (y1 - y0) + 1) / 2) + cw * (ty + y)] = col;
        }
    }
}

/* 矩形を描く */
void SheetCtl::drawRect(Sheet* sht, int x, int y, int width, int height, word col) {
    int tx = 0;
    int ty = 0;
    int cw = sht->width;
    int xw = x + width  - 1;
    int yh = y + height - 1;

    for (int xx = x; xx <= xw; xx++) {
        sht->buffer[(tx + xx) + cw * (ty + y)]  = col;
        sht->buffer[(tx + xx) + cw * (ty + yh)] = col;
    }
    for (int yy = y + 1; yy <= yh - 1; yy++) {
        sht->buffer[(tx + x)  + cw * (ty + yy)] = col;
        sht->buffer[(tx + xw) + cw * (ty + yy)] = col;
    }
}

/* 矩形を塗りつぶす */
void SheetCtl::fillRect(Sheet* sht, int x0, int y0, int x1, int y1, word col) {
    int tx = 0;
    int ty = 0;
    int cw = sht->width;

    for (int y = y0; y < y0 + y1; y++) {
        for (int x = x0; x < x0 + x1; x++) {
            sht->buffer[(tx + x) + cw * (ty + y)] = col;
        }
    }
}

/* 文字列を描画する */
void SheetCtl::drawString(Sheet* sht, char* title, int x0, int y0, word col) {
    int bw = 0, bh = FONT_H, length = 0;
    int sw = sht != NULL ? sht->width : 0;
    int I  = strlen(title);

    for (int i = 0; i < I;) {
        word ucs2 = 0;
        byte c = title[i] & 0xe0;
        if (c < 0x80) {
            ucs2 = (word) title[i];
            i++;
        } else if (c < 0xe0) {
            ucs2 = (word) title[i] & 0x1f;
            i++;
            ucs2 = ucs2 << 6;
            ucs2 = ucs2 | ((word) title[i] & 0x3f);
            i++;
        } else if (c < 0xf0) {
            ucs2 = (word) title[i] & 0x0f;
            i++;
            ucs2 = ucs2 << 6;
            ucs2 = ucs2 | ((word) title[i] & 0x3f);
            i++;
            ucs2 = ucs2 << 6;
            ucs2 = ucs2 | ((word) title[i] & 0x3f);
            i++;
        }

        int offset = offsets[ucs2] + 4;
        if (offset != 0) {
            byte fw = SheetCtl::zenkaku[offset++];
            byte fh = SheetCtl::zenkaku[offset++];
            if (sw > 0) {
                int bit = 1;
                for (int y = 0; y < fh; y++) {
                    for (int x = 0; x < fw; x++) {
                        if ((SheetCtl::zenkaku[offset] & bit) != 0) {
                            sht->buffer[(x0 + x + bw) + sw * (y0 + y)] = col;
                        }
                        bit <<= 1;
                        if (bit == 256) {
                            offset++;
                            bit = 1;
                        }
                    }
                }
            }
            bw += fw;
            length++;
        }
    }
    SheetCtl::wstrinfo->width  = bw;
    SheetCtl::wstrinfo->height = bh;
    SheetCtl::wstrinfo->length = length;
}

/* 枠を描く */
void SheetCtl::drawFrame(Sheet* sht, char* title) {
    int w = sht->width;
    int h = sht->height;

    /* 背景塗りつぶし */
    fillRect(sht, 0, 0, w, h, LIGHT_GRAY);

    /* 閉じるボタン */
    static byte icon_close_data [] = {
                                         0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x2,
                                         0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x8,
                                         0x1,0x0,0x8,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x2,0x0,0x8,
                                         0x1,0x0,0x2,0x5,0x5,0x3,0x3,0x7,0x7,0x2,0x1,0x0,0x8,
                                         0x1,0x0,0x2,0x5,0x3,0x3,0x7,0x7,0x2,0x2,0x1,0x0,0x8,
                                         0x1,0x0,0x2,0x3,0x3,0x7,0x7,0x2,0x2,0x6,0x1,0x0,0x8,
                                         0x1,0x0,0x2,0x3,0x7,0x7,0x2,0x2,0x6,0x6,0x1,0x0,0x8,
                                         0x1,0x0,0x2,0x7,0x7,0x2,0x2,0x6,0x6,0x4,0x1,0x0,0x8,
                                         0x1,0x0,0x2,0x7,0x2,0x2,0x6,0x6,0x4,0x4,0x1,0x0,0x8,
                                         0x1,0x0,0x2,0x2,0x2,0x6,0x6,0x4,0x4,0x8,0x1,0x0,0x8,
                                         0x1,0x0,0x2,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x1,0x0,0x8,
                                         0x1,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x8,
                                         0x2,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,0x8,
                                     };
    static word icon_close_pallete [] = {
                                            0x18c3,
                                            0x8c71,
                                            0xce79,
                                            0xad75,
                                            0xef7d,
                                            0x9cf3,
                                            0xdefb,
                                            0xbdf7,
                                            0xffff,
                                        };

    for (int y = 0; y < 13; y++) {
        for (int x = 0; x < 13; x++) {
            sht->buffer[(y + 4) * w + (x + 4)] =
                icon_close_pallete[icon_close_data[y * 13 + x]];
        }
    }

    /* 外枠 */
    drawRect(sht, 0, 0, w, h, BLACK);

    /* 内枠 */
    drawRect(sht, 5, 21, w - 10, h - 26, BLACK);

    /* 縁線 */
    drawLine(sht, 4, 20, 4, h - 6,  DARK_GRAY);
    drawLine(sht, 4, 20, w - 6, 20, DARK_GRAY);
    drawLine(sht, w - 5, 21, w - 5, h - 6, WHITE);
    drawLine(sht, 4, h - 5,  w - 5, h - 5, WHITE);
    drawLine(sht, 1, 1, 1, h - 3, WHITE);
    drawLine(sht, 1, 1, w - 3, 1, WHITE);
    drawLine(sht, w - 2, 2, w - 2, h - 2, DARK_GRAY);
    drawLine(sht, 2, h - 2, w - 3, h - 2, DARK_GRAY);

    /* タイトル幅 */
    drawString(NULL, title, 0, 0, 0);
    int L = SheetCtl::wstrinfo->width + FONT_W;
    int W = (w - L) / 2;

    /* タイトル線 */
    for (int y = 4; y <= 14; y += 2) {
        drawLine(sht, 21, y, W - 1, y, WHITE);
        drawLine(sht, 22, y + 1, W, y + 1, DARK_GRAY);
        drawLine(sht, W + L, y, w - 6, y, WHITE);
        drawLine(sht, W + L + 1, y + 1, w - 5, y + 1, DARK_GRAY);
    }

    /* タイトル */
    drawString(sht, title, W + FONT_W / 2, ((22 - FONT_H) / 2), BLACK);
    drawString(sht, title, W + FONT_W / 2 + 1, ((22 - FONT_H) / 2), BLACK);
}
