#!/bin/bash

echo -e "Hello, what is your name? "
read name
echo "Hi $name"
if [ "$name" = "viraj" ]; then
    echo "ok"
fi
