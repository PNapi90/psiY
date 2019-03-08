#!bin/bash

for i in {1..10}
do
    en=$(($i*25))
    ./psiY -t 5 -E $en
    echo $en processed
done