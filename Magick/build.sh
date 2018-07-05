#!/usr/bin/bash
g++ -Wall -g -O3 `Magick++-config --cflags --libs` main.cpp -o magick++
