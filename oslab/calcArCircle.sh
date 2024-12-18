echo enter radius
read rad

# expr 3.141 \* $rad

echo "3.141*$rad*$rad" | bc
# echo area = $ar