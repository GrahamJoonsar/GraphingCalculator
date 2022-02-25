#pragma once
#include "tigr.h"
#include <string>

class Button{
    private:
        int x, y, w, h;
        bool wasPressed = false;
        std::string label;
        void (*onPressAction)(void* arg1);
        const TPixel TEXT_COLOR = tigrRGB(255, 255, 255);
        TPixel buttonColor;

    public:
        Button(int x, int y, int w, int h, std::string l, TPixel bcolor, void (*f)(void*));
        void checkForClick(Tigr *screen, void* arg1);
        void draw(Tigr* screen);
};