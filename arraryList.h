#pragma once
struct arrayList
{
    int size;
    int count;
    char* pdata;
    int addcount;
};

//��ʼ�����飻
int initarrarylist(arrayList* arr, int size);

//�������Ԫ��
int addarrarylist(arrayList* arr, char* data, int size);

//��ȡ����Ԫ��    

char* getarrarylist(arrayList* arr);


//����Ԫ�ظ���
int getArraryListCnt(arrayList* pArrList);


//ɾ������Ԫ��
int removeArraryList(arrayList* pArrList, int pos, int size);