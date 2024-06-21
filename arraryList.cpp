#include"main.h"
//��ʼ������Ԫ�غ���ʵ��
int initarrarylist(arrayList* arr, int size)
{
    if (!arr)
    {
        return -1;
    }
    arr->pdata = (char*)malloc(size);
    if (!arr->pdata)
    {
        return -1;
    }
    arr->size = size;
    arr->count = 0;
    arr->addcount = 0;
    return 0;
}

//�������Ԫ�غ���ʵ��
int addarrarylist(arrayList* arr, char* data, int size)
{
    if (!arr || !data)
    {
        return -1;
    }
    if (!arr)
    {
        return -1;
    }
    if (arr->count >= arr->size)
    {
        char* p = arr->pdata;
        int newsize = arr->size * 2;
        arr->pdata = (char*)realloc(p, newsize);

        if (!arr->pdata)
        {
            return -1;
        }
        arr->size = newsize;
    }
    memcpy(arr->pdata + arr->count, data, size);
    arr->addcount++;
    arr->count += size;
    return 0;
}

//��ȡ����Ԫ�غ���ʵ��
char* getarrarylist(arrayList* arr)
{
    if (!arr)
    {
        return NULL;
    }
    return arr->pdata;
}

//��ȡ����Ԫ�ظ�������ʵ��
int getArraryListCnt(arrayList* pArrList)
{
    if (!pArrList)
    {
        return -1;
    }

    return pArrList->addcount;
}

//ɾ������Ԫ�غ���ʵ��
int removeArraryList(arrayList* pArrList, int pos, int size)
{
    if (!pArrList)
    {
        return -1;
    }
    if (pos > pArrList->addcount)
    {
        return -1;
    }

    // ɾ��Ԫ�ص��׵�ַ
    char* p = pArrList->pdata + ((pos - 1) * size);

    // ǰ���ж��ٸ��ֽ�
    int n = p - pArrList->pdata;

    // �ڴ����
    memcpy(p, p + size, pArrList->count - n - size);

    pArrList->addcount--;

    return 0;
}

