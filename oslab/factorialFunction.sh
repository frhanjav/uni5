echo "Enter value :"
read num
ans=1
fact()
{
	for (( var=1;var<=$1;var++ ))
	{
		ans=$(echo "$ans * $var" | bc)
	}
}

fact $num
echo "$num ! = $ans"

