#!/bin/sh

c++ -oDemo *.cpp -I/usr/local/include -L/usr/local/lib/ -lallegro -lallegro_acodec -lallegro_audio -lallegro_color -lallegro_font -lallegro_primitives -lallegro_ttf -lallegro_main
