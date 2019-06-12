#!/bin/bash
# create multiresolution windows icon
ICON_SRC=../../src/qt/res/icons/aliencoin.png
ICON_DST=../../src/qt/res/icons/aliencoin.ico
convert ${ICON_SRC} -resize 16x16 aliencoin-16.png
convert ${ICON_SRC} -resize 32x32 aliencoin-32.png
convert ${ICON_SRC} -resize 48x48 aliencoin-48.png
convert aliencoin-16.png aliencoin-32.png aliencoin-48.png ${ICON_DST}

