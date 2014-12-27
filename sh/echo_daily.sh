#!/bin/bash

date_beg=$1
date_end=$2

beg_s=`date -d "$date_beg" +%s`
end_s=`date -d "$date_end" +%s`

while [ "$beg_s" -le "$end_s" ]
do
    var=`date -d @$beg_s +"%Y%m%d"`
    beg_s=$((beg_s+86400))
    echo $var
done
