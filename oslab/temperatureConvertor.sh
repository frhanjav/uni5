# temp along with scale as input and convert to other

echo "Enter temp Value"
read temp

echo "Enter temp Unit ( C, F, K)"
read unit

if [ "$unit" = "C" ];
then
    echo $temp*9/5+32 | bc -l
    echo $temp+273.15 | bc -l
elif [ "$unit" = "C" ]; then
    echo "scale=2; ($value - 32) * 5 / 9" | bc -l
# else 
#     # convert to c and f
fi
