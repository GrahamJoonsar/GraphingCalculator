#pragma once
#include "tigr.h"
#include <string>
#include <vector>

class EquationPanel{
    private:
        int x, y, w, h;
        bool selected = false;
        std::string equation = "";
        std::vector<std::string> reversePolishEquation;
        TPixel BACKGROUND;
        const TPixel FOREGROUND = tigrRGB(180, 180, 190);
        const TPixel TEXT_COLOR = tigrRGB(255, 255, 255);
        const int BORDER_WIDTH = 2;

        void updateEquation();
    public:
        EquationPanel(int x, int y, int w, int h);
        void draw(Tigr * screen);
        void update(Tigr * screen, int button_num);
        float getYAt(float xnum);
        bool isValidEquation();
};