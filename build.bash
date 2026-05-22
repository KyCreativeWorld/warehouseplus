#!/bin/bash

# Set the app name
APP_NAME="WarehousePlus"

rm -f $APP_NAME

# Print a message indicating the build process has started
echo "Building $APP_NAME..."

g++ main.cpp -o main

if [ $? -eq 0 ]; then
    ./$APP_NAME
fi
