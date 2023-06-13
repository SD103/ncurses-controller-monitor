# include "SFML/Graphics.hpp"
# include <ncurses.h>
# include <iostream>
# include <locale.h>
# include <string.h>
# include <stdlib.h>
# include <menu.h>
# include <string>
# include <chrono>
# include <thread>

using namespace std;
using namespace sf;

WINDOW * makeMenu();
int * getControls();

int main(int argc, char * argv[]) {
    int * controls = getControls(),
    controller = (argc > 1 ? stoi(argv[1]) : 0);
    setlocale(LC_ALL, "");
    Joystick::update();
    if (!Joystick::isConnected(controller)) { exit(1); }
    WINDOW * menu = makeMenu();
    box(menu, 0, 0);
    curs_set(0);
    refresh();
    wrefresh(menu);
    keypad(menu, true);
    //The grid is 29x6
    int coordinates[12][2] = {
        {1, 1},
        {1, 26},
        {3, 6},
        {5, 6},
        {4, 4},
        {4, 8},
        {3, 23},
        {4, 26},
        {5, 23},
        {4, 20},
        {5, 13},
        {5, 17}
    };
    string buttons[12] = {
        "[L]",
        "[R]",
        "\u2591\u2591",
        "\u2591\u2591",
        "\u2591\u2591",
        "\u2591\u2591",
        "[X]",
        "[A]",
        "[B]",
        "[Y]",
        "-",
        "+"
    };
    while (true) {
        Joystick::update();
        for (int i = 0; i < 12; i++) {
            if (Joystick::isButtonPressed(controller, controls[i])
            || (i == 2 && Joystick::getAxisPosition(controller, Joystick::Y) < -9)
            || (i == 3 && Joystick::getAxisPosition(controller, Joystick::Y) > 50)
            || (i == 4 && Joystick::getAxisPosition(controller, Joystick::X) < -9)
            || (i == 5 && Joystick::getAxisPosition(controller, Joystick::X) > 50)) {
                wattron(menu, A_REVERSE);
            } else {
                wattroff(menu, A_REVERSE);
            }
            mvwprintw(menu, coordinates[i][0], coordinates[i][1], buttons[i].c_str());
        }
        wrefresh(menu);
        this_thread::sleep_for(chrono::milliseconds(50));
    }
    return 0;
}

int * getControls() {
    static int contentsArray[12];
    FILE * controls_F = fopen("./controls.txt", "r");
    char fileContents[255], * splitter = NULL;
    fseek(controls_F, 0, SEEK_SET);
    fread(fileContents, 255, 1, controls_F);
    splitter = strtok(fileContents, "\r\n");
    for (int i = 0; splitter != NULL; i++) {
        contentsArray[i] = atoi(splitter);
        splitter = strtok(NULL, "\r\n");
    }
    return contentsArray;
}

WINDOW * makeMenu() {
    int xMax, yMax;
      clear();
      initscr();
      noecho();
      cbreak();
      getmaxyx(stdscr, yMax, xMax);
     WINDOW * menu = newwin(8, 30, 6, 1);
    box(menu, 0, 0);
   return menu;
}
