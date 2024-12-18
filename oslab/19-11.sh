# 1 - 100 var decl before loop print after loop
i=$2
str="1 "
while ((i<100)); do
    str="${str} ${i}"
    i=$i+1
done

echo $str