#!/bin/bash

cat /dev/urandom | tr -dc "0-1" | fold -w 80 | head -n 25 > "data.txt"