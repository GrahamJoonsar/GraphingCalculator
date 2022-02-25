#include "GraphingPanel.hpp"
#include "EquationPanel.hpp"
#include <vector>
#include <iostream>
#include <math.h>

GraphingPanel::GraphingPanel(int x, int y, int w, int h){
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

std::vector<TPixel> graph_colors = {
    tigrRGB(255, 0, 0),
    tigrRGB(255, 128, 0),
    tigrRGB(255, 255, 0),
    tigrRGB(128, 255, 0),
    tigrRGB(0, 255, 0),
    tigrRGB(0, 255, 128),
    tigrRGB(0, 255, 255),
    tigrRGB(0, 0, 255),
    tigrRGB(127, 0, 255),
    tigrRGB(255, 0, 255),
    tigrRGB(255, 0, 127),
    tigrRGB(200, 200, 200),
    tigrRGB(128, 128, 128),
    tigrRGB(0, 0, 0)
};

void GraphingPanel::draw(Tigr * screen, void * epanels){
    tigrFill(screen, x, y, w, h, WHITE);
    std::vector<EquationPanel>* epanelsptr = static_cast<std::vector<EquationPanel>*>(epanels);
    int i = 0;
    for (auto epanel : *epanelsptr){
        if (epanel.isValidEquation()){
            bool wrong = false;
            int pasty = ((-(epanel.getYAt(((-(w/2.0))/w)*scale + (xoffset * (scale/10))) + (yoffset) * (scale/10))/scale)*h)+h/2.0;
            if (!isnormal(pasty)) wrong = true;
            for (int xval = 1; xval < w; xval++){
                float truex = ((xval-(w/2.0))/w)*scale;
                float truey = epanel.getYAt(truex + (xoffset * (scale/10)));
                if (!isnormal(truey) && truey!=0) {wrong = true; continue;}
                int currenty = ((-(truey + (yoffset) * (scale/10))/scale)*h)+h/2.0;
                tigrLine(screen, x+xval, currenty, x+xval-1, wrong ? currenty : pasty, graph_colors[i]);
                pasty = currenty;
                wrong = false;
            }
        }
        i++;
    }
}

void GraphingPanel::update(Tigr * screen){
    if (tigrKeyDown(screen, TK_UP)) yoffset--;
    if (tigrKeyDown(screen, TK_DOWN)) yoffset++;
    if (tigrKeyDown(screen, TK_LEFT)) xoffset--;
    if (tigrKeyDown(screen, TK_RIGHT)) xoffset++;
}