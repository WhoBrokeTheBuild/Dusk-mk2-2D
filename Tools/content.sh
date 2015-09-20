#!/bin/sh

ACTION=$1
CONF=$2

SCRIPTS_DIR=Scripts
OUT_SCRIPTS_DIR=../Build/$CONF/Scripts

TEXTURES_DIR=Textures
OUT_TEXTURES_DIR=../Build/$CONF/Textures

mkdir -p $OUT_SCRIPTS_DIR
mkdir -p $OUT_TEXTURES_DIR

if [ $ACTION = "build" ]; then
    for dir in $SCRIPTS_DIR/*/; do
        test -d "$dir" || continue

        dir=`basename $dir`
        luac -o $OUT_SCRIPTS_DIR/$dir $SCRIPTS_DIR/$dir/*.lua
        echo luac -o $OUT_SCRIPTS_DIR/$dir $SCRIPTS_DIR/$dir/*.lua
    done

    for file in $SCRIPTS_DIR/*.lua; do
        test -f "$file" || continue

        file=`basename $file`
        echo luac -o $OUT_SCRIPTS_DIR/${file%.*} $SCRIPTS_DIR/$file
        luac -o $OUT_SCRIPTS_DIR/${file%.*} $SCRIPTS_DIR/$file
    done

    if [ -d $TEXTURES_DIR ]; then
        echo cp $TEXTURES_DIR/* -t $OUT_TEXTURES_DIR/
        cp $TEXTURES_DIR/* -t $OUT_TEXTURES_DIR/
    fi

elif [ $ACTION = "clean" ]; then
    rm -rf $OUT_SCRIPTS_DIR
    rm -rf $OUT_TEXTURES_DIR
fi
