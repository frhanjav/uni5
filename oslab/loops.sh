for i in 1 2 3 4 5 6 7 8 9
do
    echo loop $i
done

k=0

while [ $k -ne 5 ]
do
    echo "Kth $k"
    k=$(($k + 1))
done