#!/bin/bash
echo 'compiling'
g++ testing.cpp
echo 'executing'
./a.out
echo 'running new_visual'
python3 new_visual.py
echo ''
echo ''
echo 'Successfull!!!'
echo ''
echo 'Check the current directory to find the gifs'
echo 'You can change the input by changing the number in the main.cpp file on line 11.'