#!/bin/bash

echo "Compiling University Management System..."

g++ -o university src/main.cpp \
    -I./include \
    -std=c++11 \
    -Wall

if [ $? -eq 0 ]; then
    echo "✓ Compilation successful!"
    echo "Run with: ./university"
else
    echo "✗ Compilation failed!"
fi