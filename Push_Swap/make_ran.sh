#!/bin/bash

i=$1
ARG=""

while [ $i -gt 0 ]
do
        random_num="$(($RANDOM% 20-9))"
        ARG="${ARG}$random_num "
        i=$(($i-1))
done

clear
make re
echo "========================"
echo "Arguments : $ARG"
echo "========================"
./push_swap $ARG

# ./push_swap $ARG
