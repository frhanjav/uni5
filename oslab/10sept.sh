maxOfThree()
{
	val1=$1
	val2=$2
	val3=$3
	# echo "The values are $val1 $val2 $val3"
	if [ $val1 -ge $val2 ] && [ $val1 -ge $val3 ]
	then
		max=$val1
	elif [ $val2 -ge $val1 ] && [ $val2 -ge $val3 ]
 	then
		max=$val2
	else
		max=$val3
	fi
	echo "Max of $val1 $val2 $val3: $max"
}

maxOfThree 110 5 89
