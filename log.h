#pragma once
enum loglevel
{
	info,		    // 提示
	wran,			// 警告信息
	err,			// 错误信息
	cInfo,			// 打印到控制台和文件当中
	cWran,          // 打印警告到控制台和文件当中
	cErr,           // 打印错误到控制台和文件当中
};

void Write(loglevel logle, int line, const char* pFuncName, const char* pBuf, ...);