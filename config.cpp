# include "SFML/Graphics.hpp"
# include <iostream>
# include <fstream>
# include <string>
# include <chrono>
# include <thread>

using namespace std;
using namespace sf;

int main(int argc, char * argv[]) {
    int get_CC, controller = (argc > 1 ? stoi(argv[1]) : 0);
    cout << "Connecting to joystick\n";
    Joystick::update();
    if (!Joystick::isConnected(controller)) { exit(1); }
    cout << "Accessing ./controls.txt\n";
    ofstream controls_F;
    controls_F.open("./controls.txt", ios::in | ios::trunc);
    string controls[12] = {"L", "R", "UP", "DOWN", "LEFT", "RIGHT", "X", "A", "B", "Y", "- || SELECT", "+ || START" };
    for (int i = 0; i < 12; i++) {
        this_thread::sleep_for(chrono::milliseconds(1000));
        cout << "Press button to map to [" + controls[i] + "]\n";
        get_CC = 1;
        while (get_CC) {
            for (int l = 0; l < 20; l++) {
                Joystick::update();
                if (Joystick::isButtonPressed(controller, l)) {
                    cout << "Pressed button " << l << "\n";
                    controls_F << l << "\n";
                    get_CC = 0;
                    break;
                }
            }
        }
    }
    return 0;
}
