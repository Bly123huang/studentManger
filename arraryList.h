#pragma once
struct arrayList
{
    int size;
    int count;
    char* pdata;
    int addcount;
};

//初始化数组；
int initarrarylist(arrayList* arr, int size);

//添加数组元素
int addarrarylist(arrayList* arr, char* data, int size);

//获取数组元素    

char* getarrarylist(arrayList* arr);


//数组元素个数
int getArraryListCnt(arrayList* pArrList);


//删除数组元素
int removeArraryList(arrayList* pArrList, int pos, int size);