#include <iostream>
#include <vector>
#include "tigr.h"
#include "EquationPanel.hpp"
#include "GraphingPanel.hpp"
#include "button.hpp"

constexpr int SCREEN_WIDTH = 640;
constexpr int SCREEN_HEIGHT = 320;
const TPixel SCREEN_BACKGROUND = tigrRGB(0, 0, 0);

int main(void){
    Tigr *screen = tigrWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Graphing Calculator", 0);

    std::vector<EquationPanel> epanels = {{0, 0, 100, 20}};

    Button addEQButton(0, SCREEN_HEIGHT-20, 50, 20, "ADD", tigrRGB(0, 255, 128),
        [](void* arg1){
            std::vector<EquationPanel>* epanels = static_cast<std::vector<EquationPanel>*>(arg1);
            if (epanels->size() < 14) epanels->push_back({0, (int)(epanels->size()) * 20, 100, 20});
        }
    );

    Button deleteEQButton(50, SCREEN_HEIGHT-20, 50, 20, "DEL", tigrRGB(255, 0, 0),
        [](void* arg1){
            std::vector<EquationPanel>* epanels = static_cast<std::vector<EquationPanel>*>(arg1);
            if (epanels->size() > 1) epanels->pop_back();
        }
    );

    Button enlargeButton(0, SCREEN_HEIGHT-40, 50, 20, " +", tigrRGB(180, 180, 190), 
        [](void* arg1){
            GraphingPanel* gp = static_cast<GraphingPanel*>(arg1);
            gp->scale/=1.1;
        }
    );

    Button shrinkButton(50, SCREEN_HEIGHT-40, 50, 20, " -", tigrRGB(180, 180, 190), 
        [](void* arg1){
            GraphingPanel* gp = static_cast<GraphingPanel*>(arg1);
            gp->scale*=1.1;
        }
    );
    
    GraphingPanel gpanel(100, 0, SCREEN_WIDTH-100, SCREEN_HEIGHT);
    
    while (!tigrClosed(screen)){
        // SETTING EVERYTHING TO BLACK
        tigrClear(screen, SCREEN_BACKGROUND);
        // DRAWING EQUATION PANELS
        int button_num = 0;
        for (int i = 0; i < epanels.size(); i++){
            epanels[i].draw(screen);
            epanels[i].update(screen, i);
        }
        // DRAWING BUTTONS
        addEQButton.draw(screen);
        deleteEQButton.draw(screen);
        enlargeButton.draw(screen);
        shrinkButton.draw(screen);
        // INTERACTION WITH BUTTONS
        addEQButton.checkForClick(screen, &epanels);
        deleteEQButton.checkForClick(screen, &epanels);
        enlargeButton.checkForClick(screen, &gpanel);
        shrinkButton.checkForClick(screen, &gpanel);
        // DRAWING THE GRAPH
        gpanel.draw(screen, &epanels);
        gpanel.update(screen);
        // DRAWING TO THE SCREEN
        tigrUpdate(screen);
    }
    
    tigrFree(screen);
    return 0;
}