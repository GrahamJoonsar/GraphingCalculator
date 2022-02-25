@echo off
echo Build Start
g++ src/graphing.cpp src/tigr.c src/EquationPanel.cpp src/GraphingPanel.cpp src/button.cpp -o GraphingCalculator -lopengl32 -lgdi32 -lWinmm
echo Build End