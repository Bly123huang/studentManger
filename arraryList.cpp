#include"main.h"
//初始化数组元素函数实现
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

//添加数组元素函数实现
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

//获取数组元素函数实现
char* getarrarylist(arrayList* arr)
{
    if (!arr)
    {
        return NULL;
    }
    return arr->pdata;
}

//获取数组元素个数函数实现
int getArraryListCnt(arrayList* pArrList)
{
    if (!pArrList)
    {
        return -1;
    }

    return pArrList->addcount;
}

//删除数组元素函数实现
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

    // 删除元素的首地址
    char* p = pArrList->pdata + ((pos - 1) * size);

    // 前面有多少个字节
    int n = p - pArrList->pdata;

    // 内存搬移
    memcpy(p, p + size, pArrList->count - n - size);

    pArrList->addcount--;

    return 0;
}

