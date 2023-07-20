#!/bin/bash
threshold=$1
infilename=$2
outfilename=$3
# gcc -g -Wall -o quadimage quadimage_test.c
gcc -g -Wall QuadImage.c QuadTree.c -o quadimage -lm
./quadimage $threshold ./img/$infilename.ppm ./img/$outfilename.ppm
python ./ppm2png.py ./img/$outfilename.ppm ./img/$outfilename.png