#!/bin/bash

# Generate data for initial state
cat /dev/urandom | tr -dc "0-1" | fold -w 80 | head -n 25 > "data.txt"
# spaced, if needed
# sed -i 's/\(.\{1\}\)/\1 /g' "data.txt"

# Compile
gcc -std=c11 -Wall -Werror -Wextra -g game_of_life.c -o game_of_life
# Run
./game_of_life
