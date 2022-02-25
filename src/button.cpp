#include "button.hpp"

Button::Button(int x, int y, int w, int h, std::string l, TPixel bcolor, void (*f)(void*)){
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
    this->label = l;
    this->buttonColor = bcolor;
    this->onPressAction = f;
}

void Button::checkForClick(Tigr *screen, void* arg1){
    int mx, my, buttons;
    tigrMouse(screen, &mx, &my, &buttons);
    if ((x < mx && mx < x+w) && (y < my && my < y+h)){
        if ((buttons & 1) && !wasPressed){ // LEFT MOUSE CLICKED
            wasPressed = true;
            onPressAction(arg1);
        } else if (!(buttons & 1)) wasPressed = false; // LEFT MOUSE RELEASED
    }
}

void Button::draw(Tigr* screen){
    tigrFill(screen, x, y, w, h, buttonColor);
    tigrPrint(screen, tfont, x+w/4, y+h/4, TEXT_COLOR, label.c_str());
}