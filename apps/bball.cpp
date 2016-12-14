#include "../baygui.h"
//#include <math.h>

#define SCREEN_W 200
#define SCREEN_H 200

static int color4bit[16][3] = {
    {   0,   0,   0 }, { 128,  0,   0 }, {  0, 128,   0 }, { 128, 128,   0},
    {   0,   0, 128 }, { 128,  0, 128 }, {  0, 128, 128 }, { 192, 192, 192},
    { 128, 128, 128 }, { 255,  0,   0 }, {  0, 255,   0 }, { 255, 255,   0},
    {   0,   0, 255 }, { 255,  0, 255 }, {  0, 255, 255 }, { 255, 255, 255}
};

static int point[16][2] = {
    { 196, 100 }, { 187,  61 }, { 164,  29 }, { 129,   9 }, {  90,   5 },
    {  53,  17 }, {  23,  44 }, {   7,  81 }, {   7, 119 }, {  23, 156 },
    {  53, 183 }, {  90, 195 }, { 129, 191 }, { 164, 171 }, { 187, 139 },
    { 196, 100 }
};

class BBall : public Frame {
public:
    BBall()
    {
        setTitle("bball");
        setBounds(0, 0, SCREEN_W + INSETS_LEFT + INSETS_RIGHT, SCREEN_H + INSETS_TOP + INSETS_BOTTOM);
    }

#if 1
    virtual void paint(Graphics* g)
    {
        g->setColor(0, 0, 0);
        g->fillRect(0, 0, SCREEN_W, SCREEN_H);
        for (int i = 0; i <= 14; i++) {
            int x0 = point[i][0];
            int y0 = point[i][1];
            for (int j = i + 1; j <= 15; j++) {
                int dis = j - i; /* 2‚Â‚Ì“_‚Ì‹——£ */
                if (dis >= 8)
                dis = 15 - dis; /* ‹t‰ñ‚è‚É”‚¦‚é */
                if (dis != 0) {
                g->setColor(color4bit[16 - dis][0],color4bit[16 - dis][1],color4bit[16 - dis][2]);
                g->drawLine(x0, y0, point[j][0], point[j][1]);
                }
            }
        }
    }
#endif
#if 0
    virtual void paint(Graphics* g)
    {
        g->setColor(0, 0, 0);
        g->fillRect(0, 0, SCREEN_W, SCREEN_H);
        for (int i = 0; i < 360; i++) {
            double rd = 3.14159 * i / 180;
            for (int j = 1; j < 8; j++) {
                g->setColor(color4bit[16 - j][0],color4bit[16 - j][1],color4bit[16 - j][2]);
                g->drawPixel(
                    cos(rd)  * cos(6 * rd) * (j + 1) * 10 + 100,
                    -sin(rd) * cos(6 * rd) * (j + 1) * 10 + 110
                );
            }
        }
    }
#endif
};

void HariMain(void)
{
    BBall* bball = new BBall();
    bball->run();
}
