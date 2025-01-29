#!/bin/bash

g++ main.cpp src/square.cpp src/board.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 && ./a.out
