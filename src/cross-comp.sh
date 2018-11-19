#!/bin/bash
 
#Using arm toolchain cross compiler
CC="arm-linux-gnueabi-g++" 

#Compiler flags
FLAGS="-std=gnu++11 -static-libstdc++"

#Dependencies (built controller)
DEP="MotorController/Class/MotorController.cpp"

TARGET=$1

$CC $FLAGS -o $TARGET.out $DEP $TARGET.cpp
