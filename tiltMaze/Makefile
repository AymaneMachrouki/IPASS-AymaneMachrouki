#############################################################################
#
# Project Makefile
#
# (c) Wouter van Ooijen (www.voti.nl) 2016
#
# This file is in the public domain.
# 
#############################################################################

# source & header files in this project (main.cpp is automatically assumed)

HEADERS := MPU6050.hpp gameObjects.hpp

SOURCES := MPU6050.cpp gameObjects.cpp

# other places to look for files for this project
SEARCH  := ../MPU6050Library
SERIAL_PORT := /dev/ttyACM0
# set REATIVE to the next higher directory 
# and defer to the Makefile.due there
RELATIVE := $(RELATIVE)../
include $(RELATIVE)Makefile.due
