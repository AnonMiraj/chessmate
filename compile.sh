#!/bin/bash

g++ main.cpp board.cpp -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 && ./a.out
