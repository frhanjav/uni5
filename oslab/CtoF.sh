echo -e "input temp in C: "
read cel

echo
echo "Temp in F: "
echo $cel*9/5+32 | bc -l