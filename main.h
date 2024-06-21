#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<windows.h>
#include<time.h>
#include <stdlib.h>


#include"login.h"
#include"home.h"
#include"arraryList.h"
#include"scoreManagement.h"
#include"log.h"
#include"file.h"
#include"studentManagement.h"
#include"teacherManage.h"
#include"class.h"


#define Log(logType, ...) \
if (logType == info)\
{\
	Write(info, __LINE__, __FUNCTION__, __VA_ARGS__);\
}\
else if (logType == wran)\
{\
	Write(wran, __LINE__, __FUNCTION__, __VA_ARGS__);\
}\
else if (logType == err)\
{\
	Write(err, __LINE__, __FUNCTION__, __VA_ARGS__);\
}\
else if (logType == cInfo)\
{\
	Write(cInfo, __LINE__, __FUNCTION__, __VA_ARGS__);\
}\
else if (logType == cWran)\
{\
	Write(cWran, __LINE__, __FUNCTION__, __VA_ARGS__);\
}\
else if (logType == cErr)\
{\
	Write(cErr, __LINE__, __FUNCTION__, __VA_ARGS__);\
}\
else\
{\
	Write(cErr, __LINE__, __FUNCTION__, __VA_ARGS__);\
}
