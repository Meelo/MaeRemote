#!/bin/bash

accelo="in.txt"

while true;
do
    x=`cat /dev/urandom | tr -cd '[:digit:]' | fold -w 8 | head -n 1`
    y=`cat /dev/urandom | tr -cd '[:digit:]' | fold -w 8 | head -n 1`
    z=`cat /dev/urandom | tr -cd '[:digit:]' | fold -w 8 | head -n 1`

    x=`echo "($x % 2000) - 1000" | bc`
    y=`echo "($y % 2000) - 1000" | bc`
    z=`echo "($z % 2000) - 1000" | bc`

    echo "$x $y $z" > "$accelo"
    echo "$x $y $z"
    sleep 0.3s
done
