#!/bin/bash

echo "Enter Value: "
read num
ans=1
for (( var=1;var<=$num;var++ ))
{
    ans=$(echo "$ans * $var" | bc)
}

echo "factorial of $num = $ans"
