#pragma once
#include "tigr.h"

class GraphingPanel{
    private:
        int x, y, w, h;
        const TPixel WHITE = tigrRGB(255, 255, 255);
        int xoffset = 0;
        int yoffset = 0;
    public:
        float scale = 10;
        GraphingPanel(int x, int y, int w, int h);
        void draw(Tigr * screen, void * epanels);
        void update(Tigr * screen);
};