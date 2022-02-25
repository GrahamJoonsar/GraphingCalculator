#include "EquationPanel.hpp"
#include <vector>
#include <iostream>
#include <cmath>

EquationPanel::EquationPanel(int x, int y, int w, int h){
    this->BACKGROUND = tigrRGB(80, 80, 90);
    this->x = x;
    this->y = y;
    this->w = w;
    this->h = h;
}

void EquationPanel::draw(Tigr * screen){
    tigrFill(screen, x, y, w, h, BACKGROUND);
    tigrFill(screen, x+BORDER_WIDTH, y+BORDER_WIDTH,
                    w-BORDER_WIDTH*2, h-BORDER_WIDTH*2, FOREGROUND);
    tigrPrint(screen, tfont, x+w/15, y+h/5, TEXT_COLOR, equation.c_str());
}

std::vector<TPixel> equation_colors = {
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

int getPrecedence(char op) {
    if(op == '^'){
        return 3;
    } else if(op == '/' || op=='*'){
        return 2;
    } else if(op == '-' || op == '+'){
        return 1;
    } else {
        return -1;
    }
}

inline bool isOp(char op){
    return  op == '+' ||
            op == '-' ||
            op == '*' ||
            op == '/' ||
            op == '^';
}

void EquationPanel::updateEquation(){
    // Convert to reverse polish
    std::vector<char> stack;
    std::vector<std::string> rpn;

    std::string token = "";

    for (int i = 0; i < equation.length(); i++){
        char c = equation[i];
        if (c == 'x' || ('0' <= c && c <= '9') || c == '.'){
            token += c;
        } else if (c == '('){
            if (token != ""){
                rpn.push_back(token);
                token = "";
            }
            stack.push_back('(');
        } else if (c == ')'){
            if (token != ""){
                rpn.push_back(token);
                token = "";
            }
            while (stack.back() != '('){
                rpn.push_back(std::string(1, stack.back()));
                stack.pop_back();
            }
            stack.pop_back();
        } else { // operator
            if (token != ""){
                rpn.push_back(token);
                token = "";
            }
            while (!stack.empty() && getPrecedence(c) <= getPrecedence(stack.back())){
                rpn.push_back(std::string(1, stack.back()));
                stack.pop_back();
            }
            stack.push_back(c);
        }
    }

    if (token != "") rpn.push_back(token);

    while (!stack.empty()){
        rpn.push_back(std::string(1, stack.back()));
        stack.pop_back();
    }
    reversePolishEquation = rpn;
}

bool EquationPanel::isValidEquation(){
    return reversePolishEquation.size() != 0;
}

float EquationPanel::getYAt(float x){
    std::vector<float> stack;
    for (auto t : reversePolishEquation){
        if (isOp(t[0])){
            float n1 = stack.back();
            stack.pop_back();
            float n2 = stack.back();
            stack.pop_back();
            switch(t[0]){
                case '+':
                    stack.push_back(n2 + n1);
                    break;
                case '-':
                    stack.push_back(n2 - n1);
                    break;
                case '*':
                    stack.push_back(n2 * n1);
                    break;
                case '/':
                    stack.push_back(n2 / n1);
                    break;
                case '^':
                    stack.push_back(powf(n2, n1));
                    break;
            }
        } else if (t[0] == 'x'){
            stack.push_back(x);
        } else {
            stack.push_back(std::stof(t));
        }
    }
    return stack.back();
}

void EquationPanel::update(Tigr * screen, int button_num){
    static unsigned int blinkingLineTime = 0;
    int mx, my, buttons;
    tigrMouse(screen, &mx, &my, &buttons);
    if (buttons & 1){
        if ((x < mx && mx < x+w) && (y < my && my < y+h)){
            selected = true;
            blinkingLineTime = 0;
            BACKGROUND = equation_colors[button_num];
        } else {
            BACKGROUND = tigrRGB(80, 80, 90);
            selected = false;
            updateEquation();
        }
    }
    // TYPING IN THE EQUATION PANEL
    if (selected){
        blinkingLineTime++;
        if (tigrKeyHeld(screen, TK_SHIFT)){
            if (tigrKeyDown(screen, '6')) equation += '^';
            if (tigrKeyDown(screen, '8')) equation += '*';
            if (tigrKeyDown(screen, '9')) equation += '(';
            if (tigrKeyDown(screen, '0')) equation += ')';
            if (tigrKeyDown(screen, TK_EQUALS)) equation += '+';
        } else {
            for (char c = '0'; c <= '9'; c++) 
            if (tigrKeyDown(screen, c)) equation += c;
        }
        if (tigrKeyDown(screen, TK_MINUS)) equation += '-';
        if (tigrKeyDown(screen, TK_SLASH)) equation += '/';
        if (tigrKeyDown(screen, TK_DOT)) equation += '.';
        if (tigrKeyDown(screen, TK_BACKSPACE) && equation.length() > 0) equation.pop_back();
        if (tigrKeyDown(screen, 'X')) equation += 'x';

        // BLINKING CURSOR
        if (blinkingLineTime > 50) tigrPrint(screen, tfont, (x+w/15) + equation.length()*7, y+h/5+1, TEXT_COLOR, "|");
        if (blinkingLineTime > 100) blinkingLineTime = 0;
    }
}