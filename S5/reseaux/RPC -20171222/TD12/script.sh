#!/bin/bash

for a in $(ls | grep -E "^.*. [^cohx]$")
do
	if test -x $a
	then
		echo $a
	fi
done
