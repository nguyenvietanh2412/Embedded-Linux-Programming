#! /usr/bin/bash



input_number(){

declare -a array

while true;do
	read -p "Enter number of elements:" num
	if [[ ! "$num" =~ ^[1-9][0-9]*$ ]];then
		echo "Invalid number!"
		continue
	fi
	break
done

for (( i=0; i<($num); i++ ))
do
	read -p "Enter element[$i]:" element
	array+=($element)
done

echo ${array[@]}
}

find_once_element(){

	is_any=0;
	array=($@)
	declare -a count

	for (( i=0; i<${#array[@]}; i++ ))
	do
		count[$i]=0
	done

	for (( i=0; i<${#array[@]}; i++ ))
	do
		for (( j=0; j<${#array[@]}; j++ ))
		do
			if [ ${array[$i]} -eq ${array[$j]} ];then
				count[$i]=$((count[$i]+1))
			fi
		done
	done

	for (( i=0; i<${#count[@]}; i++ ))
	do
		if [ ${count[$i]} -eq 1 ];then
			echo "Elements that appear once: ${array[$i]}"
			is_any=1
		fi
	done

	if [[ is_any -eq 0 ]];then
		echo "There's no element that appear once"
	fi
}

result=$(input_number)
find_once_element $result