#!/bin/bash

for i in `seq 2 1000`; # array size 2 to 100
        do
                # n=$(($i%10000))
                # if [ "$n" -eq "0" ]; then
                #     echo $i;
                #     ./ass 1 $i
                # fi
                echo $i
                ./brute-time 2 $i
        done  