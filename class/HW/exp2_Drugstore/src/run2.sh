#!/bin/bash
outfile="res2"
while getopts ":o:" opt; do
  case $opt in
    o)
      outfile=$OPTARG
      ;;
    \?)
      echo "无效的选项: -$OPTARG" >&2
      exit 1
      ;;
    :)
      echo "选项 -$OPTARG 需要参数值" >&2
      exit 1
      ;;
  esac
done

if [ -f $outfile ]; then
    rm $outfile
fi

touch $outfile

g++ -g -Wall drugstore2.cpp -o drugstore2

for i in {1..10}
do
  echo "data$i" >> $outfile
  ./drugstore2 -m ../test/data$i/medicine.txt -ws ../test/data$i/out_strategy.txt -wd ../test/data$i/out_delete.txt >> $outfile
done
