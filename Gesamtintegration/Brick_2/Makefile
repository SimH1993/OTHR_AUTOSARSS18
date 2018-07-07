# Target specific macros
TARGET = brick_2
TARGET_SOURCES := master.c \
					../BSW/ADC/AdcIF.c \
					../BSW/ComHandler/ComHandler.c \
					../BSW/DIO/DioIF.c \
					../BSW/MotorHandler/MotorHandler.c \
					../BSW/SoundHandler/SoundHandler.c \
					../BSW/Utility/Utility.c 

TOPPERS_OSEK_OIL_SOURCE := ./master.oil
O_PATH ?= build
include ../../../../../../../nxtOSEK/ecrobot/ecrobot.mak 