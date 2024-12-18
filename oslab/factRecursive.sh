fact()
{
	local n=$1
	if [ $n -le 1 ]
	then
		echo 1
	else
		local prev=$(fact $((n - 1)))
		echo $((n * prev))
	fi
}
echo "gimme num: "
read num
fact $num
