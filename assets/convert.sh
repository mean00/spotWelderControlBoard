#!/bin/sh
convGif()
{
rm -f converted/$1*
convert  $1.gif   -monochrome -flatten generated/$1_preview.png
python3 convert.py generated/$1_preview.png generated/$1_compressed.h generated/$1_decl.h $1
}
convGif2()
{
rm -f converted/$1*
python3 convert.py $1.gif generated/$1_compressed.h generated/$1_decl.h $1
}
conv()
{
rm -f converted/$1*
convert  $1.png   -monochrome -flatten generated/$1_preview.png
python3 convert.py generated/$1_preview.png generated/$1_compressed.h generated/$1_decl.h $1
}
conv2()
{
rm -f converted/$1*
python3 convert.py $1.png generated/$1_compressed.h generated/$1_decl.h $1
}
convGif c1
convGif c2
convGif c3
convGif c4
convGif splash
convGif2 sp0001
convGif2 sp0002
convGif2 sp0003
convGif2 sp0004
convGif2 sp0005
convGif2 sp0006
convGif2 sp0007
convGif2 sp0008
convGif2 sp0009
