#include"main.h"

// ���ļ��������ļ�ָ��
FILE* open(const char* fileName, const char* mode)
{
	return fopen(fileName, mode);
 
}

// д�����ݵ��ļ�
size_t write(FILE* fp, char* data, int size)
{
	if (fp == NULL)
	{
		return -1;
	}

	return fwrite(data, size, 1, fp);
}

// ���ļ��ж�ȡ���ݲ�����ָ��
char* read(FILE* fp, long* cnt)
{
	if (fp == NULL)
	{
		return NULL;
	}

	// �ƶ��ļ�ָ�뵽�ļ�ĩβ�Ի�ȡ�ļ���С
	fseek(fp, 0, SEEK_END);
	*cnt = ftell(fp);

	// �����ڴ��Դ洢�ļ�����
	char* p = (char*)malloc(*cnt);
	if (!p)
	{
		return NULL;
	}

	// ���¶�λ�ļ�ָ�룬����ȡ���ݵ��ڴ���
	fseek(fp, 0, SEEK_SET);
	fread(p, *cnt, 1, fp);

	return p;
}

// �ر��ļ�
int close(FILE* fp)
{
	return fclose(fp);
}


//����id���ļ����Ƿ����
int findid(const char* fp, int id)
{
	// ���ļ�����ֻ����ʽ��ȡ
	FILE* file = fopen(fp, "r");
	if (file == NULL) {
		printf("Error opening file!\n");
		exit(1);
	}
    int userid;
    userid=id;
    // �����ļ����ҵ�Ҫ��ѯ��ѧ����Ϣ������ӡ
    char line[100];
    int found = 0; // ��־�Ƿ��ҵ�Ŀ����
    while (fgets(line, 100, file) != NULL)
    {
        int sid;
        char sclass[20];
        char sname[20];
        char gender[10];
        int age;
        char telephone[100];
        float math;
        float english;
        float chinese;
        char username[20];
        char password[20];
        char roles[20];
        // �����ļ���ʽΪ��ѧ�� �༶ ���� �Ա� ���� �绰 ��ѧ Ӣ�� ���� �û��� ���� ��ɫ

        if (sscanf(line, "%d %s %s %s %d %s %f %f %f %s %s %s", &sid, sclass, sname, gender, &age, telephone,
            &math, &english, &chinese, username, password, roles) != EOF)
        {

            if (sid == userid)
            {
                found = 1;
            }
        }
    }
    // ���û���ҵ�Ŀ���У��������ʾ��Ϣ
    if (!found) {
        system("cls");
        printf("δ�ҵ�IDΪ %d ����Ϣ��\n", userid);
        Sleep(2000);
    }

    // �ر��ļ�
    fclose(file);
	return found;
}

//���ļ�
void openfile(const char* fp, const char* mode)
{
    FILE* file = fopen(fp, mode);
    if (file == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    return;
}