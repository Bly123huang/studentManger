#pragma once
enum loglevel
{
	info,		    // ��ʾ
	wran,			// ������Ϣ
	err,			// ������Ϣ
	cInfo,			// ��ӡ������̨���ļ�����
	cWran,          // ��ӡ���浽����̨���ļ�����
	cErr,           // ��ӡ���󵽿���̨���ļ�����
};

void Write(loglevel logle, int line, const char* pFuncName, const char* pBuf, ...);