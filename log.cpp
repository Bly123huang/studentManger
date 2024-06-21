#include"main.h"
const char* LogLevel[] = { "[INFO]", "[WARN]", "[ERR]","[CINFO]", "[CWARN]","[CERR]" };
void Write(loglevel logle, int line, const char* pFuncName, const char* pBuf, ...)
{
	char buf[1024] = "";
	// 获取当前时间
	SYSTEMTIME sysTime;
	GetLocalTime(&sysTime);
	snprintf(buf, sizeof(buf), "[%04d-%02d-%02d %02d:%02d:%02d] %s ",
		sysTime.wYear, sysTime.wMonth, sysTime.wDay,
		sysTime.wHour, sysTime.wMinute, sysTime.wSecond,
		LogLevel[logle]);
	// 格式化日志内容
	va_list args;
	va_start(args, pBuf);
	vsnprintf(buf + strlen(buf), sizeof(buf) - strlen(buf), pBuf, args);
	va_end(args);
	snprintf(buf + strlen(buf), sizeof(buf) - strlen(buf), " {%s:%d}\n", pFuncName, line);
	// 打印到控制台和文件
	if (logle >= cInfo && logle <= cErr)
	{
		printf("%s", buf);
	}
	char buf1[64] = { 0 };
	snprintf(buf1, sizeof(buf1), "%04d-%02d-%02d-%02d.log", sysTime.wYear, sysTime.wMonth, sysTime.wDay, sysTime.wHour);
	FILE* fp = fopen(buf1, "a+");
	if (fp)
	{
		fprintf(fp, "%s", buf);
		fclose(fp);
	}
	return;
}