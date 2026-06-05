#!/bin/bash

# Exit immediately if a command fails
set -e

# Pin the script to its own directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

APP_NAME="WarehousePlus"

echo "========================================="
echo " Building $APP_NAME..."
echo "========================================="

# Explicitly list your files so there are no surprises with relative paths
g++ -std=c++17 \
    main.cpp \
    backend/inb_outb_sim.cpp \
    -Wall -Wextra \
    -o $APP_NAME

echo " Build successful! Launching application..."
echo "----------------------------------------="

./$APP_NAME