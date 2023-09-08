#! /usr/bin/bash

while true;do

	read -p "Enter an expression": num1 operator num2

    	if [[ $num1 == 'q' || $operator == 'q' || $num2 == 'q' ]]; then
        	echo "Exiting..."
        	exit 0
    	fi

	case $operator in
		"+")
			echo "$(($num1 + $num2))"
			;;
		"-")
			echo "$(($num1 - $num2))"
			;;
		"x")
			echo "$(($num1 * $num2))"
			;;
		"/")
			if [ $num2 -eq 0 ]; then
				echo "Cannot divide by 0"
			else
				echo "$(($num1 / $num2))"
			fi
			;;
		*)
			echo "Invalid!"
			;;
	esac
done