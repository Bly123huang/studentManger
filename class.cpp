#include"main.h"

void classManage()
{
	int choice;
	do 
	{
		int start = 0;
	start:
		system("cls");
		printf("\n��ӭ����༶����\n");
		printf("1. �༶��Ա��Ϣ��ѯ\n");
	
		printf("0.  Exit\n");
		printf("���������ѡ��: ");
		scanf_s("%d", &choice);
		char* currentRole = getCurrentUserRole();
		char* currentClass = getCurrentUserClass();
		switch (choice)
		{
			
		case 1:
		{
			// ����Ƿ��ǽ�ʦ
			if (strcmp(currentRole, "student") == 0)
			{
				printf("ѧ���û�����Ȩ���ʴ˹��ܣ�\n");
				Sleep(1000);
				return;
			}
			classMemberInfoQuery();

			break;
		}
		case 0:
			exit(0);
			return;
		default:
			printf("����������������룡\n");
		while (choice >1 && choice < 1)
		{
			goto start;
			break;
		}
		}
	}
	while (choice!= 5);
}

//�༶��Ա��Ϣ��ѯ
void classMemberInfoQuery()
{

	char* currentRole = getCurrentUserRole();
	char* currentClass = getCurrentUserClass();
	FILE* file = fopen("Stu_information.txt", "r");
	if (file == NULL)
	{
		printf("Error opening file!\n");
		exit(1);
	}
	char line[100];
	printf("%-6s %-10s %-10s %-6s %-10s\n", "ѧ��", "����", "�Ա�", "����", "�绰");
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
		int classMemberCount = 0;
		// �����ļ���ʽΪ��ѧ�� �༶ ���� �Ա� ���� �绰 ��ѧ Ӣ�� ���� �û��� ���� ��ɫ
		if (sscanf(line, "%d %s %s %s %d %s %f %f %f %s %s %s", &sid, sclass, sname, gender, &age, telephone,
			&math, &english, &chinese, username, password, roles) != EOF)
		{
			
			if (strcmp(sclass, currentClass) == 0&&strcmp(roles, "student") == 0)
			{
				classMemberCount++;
				printf("%-6d %-10s %-10s %-6d %-10s\n", sid, sname, gender, age, telephone);
			}
		}
		
	}
	fclose(file);
	system("pause");
	return;
}