#!/bin/bash

# Set the app name
APP_NAME="WarehousePlus"

rm -f $APP_NAME

# Print a message indicating the build process has started
echo "Building $APP_NAME..."

g++ -std=c++17 main.cpp -o $APP_NAME

if [ $? -eq 0 ]; then
    ./$APP_NAME
fi
