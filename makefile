#!/bin/make

make:
	g++ main.cpp -lncursesw -lsfml-window -o input-monitor 
	g++ config.cpp -lsfml-window -o config

keyboard-input:
	g++ keyboard.cpp -lncursesw -lsfml-window -o keyboard
