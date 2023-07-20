#!/bin/bash
outfile="res1"
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

g++ -g -Wall drugstore.cpp -o drugstore

for i in {1..10}
do
  echo "data$i" >> $outfile
  ./drugstore -m ../test2/data$i/medicine.txt -s ../test2/data$i/my_strategy.txt -d ../test2/data$i/my_delete.txt >> $outfile
done
