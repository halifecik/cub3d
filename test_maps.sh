#!/bin/bash

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

echo -e "${BLUE}================================${NC}"
echo -e "${BLUE}     CUB3D MAP TESTING SCRIPT   ${NC}"
echo -e "${BLUE}================================${NC}"
echo

# Check if cub3d executable exists
if [ ! -f "./cub3d" ]; then
    echo -e "${RED}Error: cub3d executable not found. Please compile first.${NC}"
    exit 1
fi

# Function to test a single map
test_map() {
    local map_path="$1"
    local map_name=$(basename "$map_path")
    
    echo -e "${YELLOW}Testing: $map_path${NC}"
    echo "Command: valgrind ./cub3d $map_path"
    echo "----------------------------------------"
    
    # Run valgrind with the map
    timeout 10s valgrind ./cub3d "$map_path" 2>&1
    exit_code=$?
    
    if [ $exit_code -eq 0 ]; then
        echo -e "${GREEN}✓ PASSED${NC}"
    elif [ $exit_code -eq 124 ]; then
        echo -e "${YELLOW}⚠ TIMEOUT (10s)${NC}"
    else
        echo -e "${RED}✗ FAILED (Exit code: $exit_code)${NC}"
    fi
    
    echo
    echo "========================================"
    echo
}

# Test main maps
echo -e "${BLUE}TESTING MAIN MAPS${NC}"
echo "=================="
for map in maps/*.cub; do
    if [ -f "$map" ]; then
        test_map "$map"
    fi
done

# Test valid maps
echo -e "${BLUE}TESTING VALID MAPS${NC}"
echo "=================="
for map in maps/valid/*.cub; do
    if [ -f "$map" ]; then
        test_map "$map"
    fi
done

# Test invalid maps
echo -e "${BLUE}TESTING INVALID MAPS${NC}"
echo "===================="
for map in maps/invalid/*.cub; do
    if [ -f "$map" ]; then
        test_map "$map"
    fi
done

# Test bonus maps
echo -e "${BLUE}TESTING BONUS MAPS${NC}"
echo "=================="
for map in maps/bonus/*.cub; do
    if [ -f "$map" ]; then
        test_map "$map"
    fi
done

echo -e "${GREEN}Testing completed!${NC}"