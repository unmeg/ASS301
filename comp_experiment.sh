#!/bin/bash

for i in `seq 1 1000`; # array size 1 to 1000
        do
                # n=$(($i%10000))
                # if [ "$n" -eq "0" ]; then
                #     echo $i;
                #     ./median-comps 1 $i
                # fi
                echo $i
                ./comps 1 $i
        done  