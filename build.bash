#!/bin/bash

# 1. THE SEATBELT FLAGS (Fail-Fast)
# -e: Exit immediately if any command fails
# -u: Exit immediately if an unassigned variable is used
set -eu

# 2. PIN THE WORKING DIRECTORY
# Ensures this script ALWAYS executes from the folder it lives in, 
# no matter where you call it from in the terminal.
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

# Configuration Variables
APP_NAME="WarehousePlus"
COMPILER="g++" # Or clang++ depending on your preference

# 3. AUTOMATICALLY LINK ALL CPP FILES
# Instead of hardcoding main.cpp, this dynamically finds your source files
# so you never get an "Undefined symbols" linker error again!
SOURCE_FILES=$(find . -maxdepth 2 -name "*.cpp" ! -name "*_test.cpp")

# Clean up old build binaries cleanly
rm -f "$APP_NAME"

echo "========================================="
echo " Building $APP_NAME..."
echo "========================================="

# 4. COMPILE USING SECURE QUOTING
# Adding Wall and Wextra will warn you about hidden type mismatches (like %s vs %u!)
$COMPILER -std=c++17 $SOURCE_FILES -Wall -Wextra -o "$APP_NAME"

# Because of 'set -e', the script ONLY reaches this line if compilation succeeded.
echo " Build successful! Launching application..."
echo "----------------------------------------="

./"$APP_NAME"