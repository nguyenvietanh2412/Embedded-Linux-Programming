#! /usr/bin/bash

args=("$@")

result=${args[0]}

for ((i=1; i<$#; i+=2)); do
    operator=${args[$i]}
    num=${args[$((i+1))]}

    case $operator in
        "+")
            result=$(($result + $num))
            ;;
        "-")
            result=$(($result - $num))
            ;;
        "x")
            result=$(($result * $num))
            ;;
        "/")
            if [ $num -eq 0 ]; then
                echo "Cannot divide by 0"
                exit 1
            else
                result=$(($result / $num))
            fi
            ;;
        *)
            echo "Invalid: $operator"
            exit 1
            ;;
    esac
done

echo $result