#!/bin/bash

# Color codes
GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m' # No Color

# Initialize counters
total_tests=0
passed_tests=0

# Check if valgrind flag is present
use_valgrind=0
if [ "$1" = "--valgrind" ]; then
    use_valgrind=1
fi

# Function to test expression and check result
test_expr() {
    local expr="$1"
    local expected="$2"
    local should_fail=${3:-0}

    ((total_tests++))
    
    if [ "$use_valgrind" -eq 1 ]; then
        result=$(valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes -q ./vbc "$expr" 2>&1)
    else
        result=$(./vbc "$expr" 2>&1)
    fi
    exit_code=$?

    if [ "$should_fail" -eq 1 ]; then
        if [ "$exit_code" -eq 1 ] && [ "$result" == "$expected" ]; then
            printf "${GREEN}[OK]${NC} %-25s | %-25s | %-25s\n" \
                "'$expr'" "'$expected'" "'$result'"
            ((passed_tests++))
        else
            printf "${RED}[KO]${NC} %-25s | %-25s | %-25s\n" \
                "'$expr'" "'$expected'" "'$result'"
        fi
    else
        if [ "$exit_code" -eq 0 ] && [ "$result" == "$expected" ]; then
            printf "${GREEN}[OK]${NC} %-25s | %-25s | %-25s\n" \
                "'$expr'" "'$expected'" "'$result'"
            ((passed_tests++))
        else
            printf "${RED}[KO]${NC} %-25s | %-25s | %-25s\n" \
                "'$expr'" "'$expected'" "'$result'"
        fi
    fi
}

# Compile the program
cc -Wall -Werror -Wextra -o vbc main.c || exit 1

# Print header
printf "%s\n" "----------EXPRESSION-----------|--------EXPECTED-----------|-----------RESULT-----------"

# Basic operations
test_expr "1" "1"
test_expr "1+2" "3"
test_expr "2*3" "6"
test_expr "1+2*3" "7"

# Simple parentheses
test_expr "(1+2)*3" "9"
test_expr "((3+4)*5)+(5*5+(7+7*5))" "102"

# Complex nested expressions
test_expr "(9+(8+7+6)*5+4+3+2+1)" "124"
test_expr "((((9))))*((((9))))" "81"
test_expr "(1+1)*(2+2)*(3+3)" "48"
test_expr "(1+2*3)*(4+5*6)" "238"

# Long operations
test_expr "1+2+3+4+5+6+7+8+9" "45"
test_expr "9*8*7*6*5*4*3*2*1" "362880"
test_expr "1+2*3+4*5+6*7+8*9" "141"

# Deep nesting
test_expr "(((((((((1+1))))))*2)))" "4"
test_expr "(((1+(2+(3+(4+5))))))" "15"
test_expr "(1*(2*(3*(4*(5)))))" "120"

# Mixed operations with priority tests
test_expr "1+2*3+4*5+6" "33"
test_expr "(1+2)*(3+4)*(5+6)" "231"
test_expr "9*(8+7*(6+5)*4+3)*2+1" "5743"

# Error cases - Invalid syntax
test_expr "1+" "Unexpected end of input" 1
test_expr "1)" "Unexpected token ')'" 1
test_expr "(1" "Unexpected end of input" 1
test_expr "1**2" "Unexpected token '*'" 1
test_expr "()" "Unexpected token ')'" 1
test_expr "(*2)" "Unexpected token '*'" 1
test_expr "1++2" "Unexpected token '+'" 1
test_expr "1+)" "Unexpected token ')'" 1
test_expr "(1+)" "Unexpected token ')'" 1

# Error cases - Invalid characters
test_expr "a+b" "Unexpected token 'a'" 1
test_expr "1+a" "Unexpected token 'a'" 1
test_expr "a*b" "Unexpected token 'a'" 1
test_expr "1.2+3" "Unexpected token '.'" 1
test_expr "@#$" "Unexpected token '@'" 1

# Error cases - Malformed parentheses
test_expr "((1+2)" "Unexpected end of input" 1
test_expr "(1+2))" "Unexpected token ')'" 1
test_expr "((1+2)*3))" "Unexpected token ')'" 1
test_expr "(((())))" "Unexpected token ')'" 1

# Boundary cases
test_expr "(0+0)" "0"
test_expr "0*0" "0"
test_expr "((((0))))" "0"
test_expr "0+0+0+0+0" "0"
test_expr "1*1*1*1*1" "1"
test_expr "(((1*1)*(1*1)))" "1"

# Empty/whitespace cases
test_expr "" "Unexpected end of input" 1
test_expr "   " "Unexpected token ' '" 1

# Maximum values (with single digits)
test_expr "9*9*9*9" "6561"
test_expr "9+9+9+9+9+9+9+9+9" "81"
test_expr "(9*(9+(9*9)))" "810"

# Zero handling
test_expr "0+1" "1"
test_expr "1+0" "1"
test_expr "0*1" "0"
test_expr "1*0" "0"
test_expr "(0)" "0"
test_expr "((0))" "0"

# Print summary at the end
echo -e "\n---------------------------------------------------------------------------------------"
if [ $passed_tests -eq $total_tests ]; then
    echo -e "${GREEN}All tests passed! 🎉${NC}"
else
    echo -e "${RED}Some tests failed 😕${NC}"
fi
echo -e "${GREEN}Tests passed: $passed_tests${NC}"
echo -e "${RED}Tests failed: $((total_tests - passed_tests))${NC}"
echo -e "Use flag --valgrind to check for memory leaks"
echo "---------------------------------------------------------------------------------------"