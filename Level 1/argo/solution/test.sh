#!/bin/bash

# Compile the program
cc main.c argo.c -o argo || exit 1

# Colors
GREEN='\033[32m'
RED='\033[31m'
BLUE='\033[34m'
NC='\033[0m'  # No Color

# Function to run a test case
run_test() {
    local input=$1
    local expected_output=$2
    
    actual_output=$(echo -n "$input" | ./argo /dev/stdin | cat -e)
    
    if [ "$actual_output" = "$expected_output" ]; then
        echo -e "${GREEN}✓${NC} Test '$input' -> '$actual_output'"
    else
        echo -e "${RED}✗${NC} Test '$input' -> got '$actual_output', expected '$expected_output'"
    fi
}

run_test '1' "1\$"
run_test '"bonjour"' '"bonjour"$'
run_test '"escape! \" "' '"escape! \" "$'
run_test '{"tomatoes":42,"potatoes":234}' '{"tomatoes":42,"potatoes":234}$'
run_test '{"recursion":{"recursion":{"recursion":{"recursion":"recursion"}}}}' '{"recursion":{"recursion":{"recursion":{"recursion":"recursion"}}}}$'
run_test '"unfinished string' "unexpected end of input$"
run_test '"unfinished string 2\"' "unexpected end of input$"
run_test '{"no value?":}' "unexpected token '}'$"

# echo -e "\n${BLUE}=== Testing Integer Values ===${NC}"
# run_test "2" "2\$"
# run_test "42" "42\$"
# run_test "42.5" "unexpected token '.'$"
# run_test "42 42" "unexpected token ' '$"

# echo -e "\n${BLUE}=== Testing String Values ===${NC}"
# run_test '"hello"' '"hello"$'
# run_test '"test \" \\"' '"test \" \\"$'
# run_test '"escape! \" "' '"escape! \" "$'
# run_test '"unfinished' "unexpected end of input$"

# echo -e "\n${BLUE}=== Testing Simple Maps ===${NC}"
# run_test '{"key":42}' '{"key":42}$'
# run_test '{"str":"val"}' '{"str":"val"}$'
# run_test '{42:"val"}' "unexpected token '4'$"
# run_test '{"key"}' "unexpected token '}'$"
# run_test '{"key":}' "unexpected token '}'$"
# run_test '{"key": 42}' "unexpected token ' '$"

# echo -e "\n${BLUE}=== Testing Nested Maps ===${NC}"
# run_test '{"a":{"b":42}}' '{"a":{"b":42}}$'
# run_test '{"a":{"b":{"c":"d"}}}' '{"a":{"b":{"c":"d"}}}$'
# run_test '{"a":{42:42}}' "unexpected token '4'$"
# run_test '{"a":{"b":{"c"}}' "unexpected token '}'$"

# echo -e "\n${BLUE}=== Testing Multiple Values in Maps ===${NC}"
# run_test '{"a":1,"b":2}' '{"a":1,"b":2}$'
# run_test '{"a":"1","b":"2"}' '{"a":"1","b":"2"}$'
# run_test '{"a":1,"b":{"c":3}}' '{"a":1,"b":{"c":3}}$'
# run_test '{"a":1,}' "unexpected token '}'$"

# # Additional edge cases
# echo -e "\n${BLUE}=== Testing Edge Cases ===${NC}"
# run_test '""' '""$'                    # Empty string
# run_test '{"":""}' '{"":""}$'          # Empty key and value
# run_test '{"a":{"":"":{}}}' '{"a":{"":"":{}}}$'  # Nested empty stuff

# Cleanup
rm -f argo