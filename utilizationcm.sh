ps aux | awk 'BEGIN {a=0; b=0;} NR!=1{a+=$3; b+=$4;} END {print "CPU:","%"a;print "MEM:","%"b;}'
