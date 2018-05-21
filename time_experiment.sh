#!/bin/bash

for i in `seq 1 1000`; # array size 1 to 1000
        do
                echo $i
                ./times 1 $i
        done  