#include"main.h"
char adminPassword1[MAX_PASSWORD_LEN];
void teacherManage()
{
	int choice;
	do {
		system("cls");
		printf("\n��ӭ�����ʦ��Ϣ����\n");
		printf("1. �½���ʦ��Ϣ\n");
		printf("2. ¼���ʦ��Ϣ\n");
		printf("3. ��ѯ��ʦ��Ϣ\n");
		printf("4. �޸Ľ�ʦ��Ϣ\n");
		printf("5. ɾ����ʦ��Ϣ\n");
		printf("0.  Exit\n");
		printf("���������ѡ��: ");
		scanf_s("%d", &choice);
		switch (choice) {
			
		case 1:
			createTeacher();
			break;

		case 2:
		{
			// ����Ƿ��ǹ���Ա
			if (strcmp(getCurrentUserRole(), "admin") != 0) {
				printf("�ǹ���Ա��\n");
				return;
			}
			inputTeacher();
			break;
		}
		case 3:
		{

			printf("������Ҫ��ѯ�Ľ�ʦ����: ");
			char names[10];
			scanf("%s", names);
			system("cls");
			queryTeacher(names);
			break;

		}

		case 4:
		{
			// ����Ƿ��ǹ���Ա
			if (strcmp(getCurrentUserRole(), "admin") != 0) {
				printf("�ǹ���Ա��\n");
				return;
			}
			const char name[10] = "";
			printf("������Ҫ�޸ĵĽ�ʦ����: ");
			scanf("%s", name);
			system("cls");
			modifyTeacher(name);
			break;
		}
		case 5:
		{
			
			// ����Ƿ��ǹ���Ա
			if (strcmp(getCurrentUserRole(), "admin") != 0) {
				printf("�ǹ���Ա��\n");
				return;
			}
			const char name[10] = "";
			printf("������Ҫɾ���Ľ�ʦ����: ");
			scanf("%s", name);
			system("cls");
			char confirm1;
			printf("ȷ��Ҫɾ������Ϊ %s��ѧ����Ϣ��(Y/N) ", name);
			while (getchar() != '\n');
			scanf("%c", &confirm1);

			if (confirm1 == 'Y' || confirm1 == 'y')
			{
				deleteTeacher(name);
			}
			else
			{
				printf("ȡ��ɾ����\n");
				system("pause");
			}

			
			break;
		}
		case 0:
			exit(0);
			break;
		default:
			printf("Invalid choice. Please try again.\n");

		}
	} while (choice !=5);

	return;
}


//�½���ʦ��Ϣ
void createTeacher()
{
	// ����Ƿ��ǹ���Ա
	if (strcmp(getCurrentUserRole(), "admin") != 0) {
		printf("�ǹ���Ա�����ע��ʧ�ܣ�\n");
		Sleep(1000);
		return;
	}
	STUDENT_INFOEMATION stuinformation = {};
	printf("������ID��");
	scanf("%d", &stuinformation.id);
	printf("������༶��");
	scanf("%s", &stuinformation.classs);
	printf("������������");
	scanf("%s", &stuinformation.name);
	printf("�������Ա�");
	scanf("%s", &stuinformation.gender);
	printf("���������䣺");
	scanf("%d", &stuinformation.age);
	printf("������绰��");
	scanf("%s", &stuinformation.telephone);
	stuinformation.stuScore.chinese = 0;
	stuinformation.stuScore.math = 0;
	stuinformation.stuScore.english = 0;
	stuinformation.stuScore.id = 0;

	strcpy(stuinformation.user.username, "0");
	strcpy(stuinformation.user.password, "0");
	strcpy(stuinformation.user.role, "teacher");
	addStudent_Information(stuinformation.id, stuinformation.classs,
		stuinformation.name, stuinformation.gender, stuinformation.age,
		stuinformation.telephone, stuinformation.stuScore.math, stuinformation.stuScore.english,
		stuinformation.stuScore.chinese, stuinformation.user.username, stuinformation.user.password,
		stuinformation.user.role);
	return;

}




//¼���ʦ��Ϣ
TEACHER teacher_information;
void inputTeacher()
{
	printf("�������ʦID:\n");
	int id;
	scanf("%d",&id);
	if (findid("Stu_information.txt", id) == 0)//�����Ƿ����ļ�����¼���id
	{
		printf("δ���ҵ��ý�ʦ��Ϣ��\n");
		return;
	}
	system("cls");
	printf("�������ʦ��Ϣ:\n");
	printf("�������ʦ����: ");
	int m=scanf("%s", teacher_information.name);
	printf("�������ʦ�Ա�: ");
	m = scanf("%s", teacher_information.gender);
	printf("�������ʦ����: ");
	m = scanf("%d", &teacher_information.age);
	printf("�������ʦѧ��: ");
	m = scanf("%s", teacher_information.subject);
	printf("�������ʦ�绰: ");
	m = scanf("%s", teacher_information.phone);
	printf("�������ʦ��ַ: ");
	m = scanf("%s", teacher_information.address);
	FILE* fp = fopen("teacher.txt", "ab+");
	fprintf(fp, "%s %s %d %s %s %s\n", teacher_information.name, teacher_information.gender, teacher_information.age, teacher_information.subject, teacher_information.phone, teacher_information.address);
	fclose(fp);	
	printf("��ʦ��Ϣ¼��ɹ�!\n");
	Sleep(2000);
	return;
}

//��ѯ��ʦ��Ϣ
void queryTeacher(char name[10]) {
	// ���ļ�����ֻ����ʽ��ȡ
	FILE* fp = fopen("teacher.txt", "r");
	if (fp == NULL) {
		printf("Error opening file!\n");
		exit(1);
	}
	// ��ȡ�ļ����ݣ�����ӡ����Ļ��
	char sname[20];
	char sgender[10];
	int sage;
	char ssubject[20];
	char sphone[20];
	char saddress[50];
	int found = 0;
	while (fscanf(fp, "%s %s %d %s %s %s", sname, sgender, &sage, ssubject, sphone, saddress) != EOF) {
		if (strcmp(sname, name) == 0) {
			printf("����: %s\n", sname);
			printf("�Ա�: %s\n", sgender);
			printf("����: %d\n", sage);
			printf("ѧ��: %s\n", ssubject);
			printf("�绰: %s\n", sphone);
			printf("��ַ: %s\n", saddress);
			found = 1;
			break;
		}
	}
	fclose(fp);
	if (!found) {
		printf("û���ҵ��ý�ʦ��Ϣ!\n");
	}
	system("pause");
	return;
}

void modifyTeacher(const char* name) 
{
	// ���ļ����Զ�д��ʽ��
	FILE* file = fopen("teacher.txt", "r+");
	if (file == NULL) {
		printf("Error opening file!\n");
		exit(1);
	}

	// ������ʱ�ļ����洢���º������
	FILE* tempFile = fopen("temp.txt", "w");
	if (tempFile == NULL) {
		printf("Error opening temporary file!\n");
		fclose(file);
		exit(1);
	}
	// ��ȡ�ļ����ݣ�����ӡ����Ļ��
	char line[100];
	int found = 0; // ��־�Ƿ��ҵ�Ŀ����
	while (fgets(line, 100, file) != NULL) {
		char sname[20];
		char sgender[10];
		int sage;
		char ssubject[20];
		char sphone[100];
		char saddress[50];
		if (sscanf(line, "%s %s %d %s %s %s", sname, sgender, &sage, ssubject, sphone, saddress) == 6) {
			if (strcmp(sname, name) == 0) {
				found = 1; // �ҵ�Ŀ����
				printf("����: %s\n", sname);
				printf("�Ա�: %s\n", sgender);
				printf("����: %d\n", sage);
				printf("ѧ��: %s\n", ssubject);
				printf("�绰: %s\n", sphone);
				printf("��ַ: %s\n", saddress);
				printf("�������µ��Ա�: ");
				int m = scanf("%s", sgender);
				printf("�������µ�����: ");
				m = scanf("%d", &sage);
				printf("�������µ�ѧ��: ");
				m = scanf("%s", ssubject);
				printf("�������µĵ绰: ");
				m = scanf("%s", sphone);
				printf("�������µĵ�ַ: ");
				m = scanf("%s", saddress);
				// ���µ���Ϣд�뵽��ʱ�ļ���
				fprintf(tempFile, "%s %s %d %s %s %s\n", sname, sgender, sage, ssubject, sphone, saddress);
				printf("��ʦ��Ϣ�޸ĳɹ���\n");
				Sleep(2000);
			}
			else {
				// ��ԭʼ����д����ʱ�ļ�
				fputs(line, tempFile);
			}
		}
	}

	// ���û���ҵ�Ŀ���У��������ʾ��Ϣ
	if (!found) {
		printf("δ�ҵ�����Ϊ %s �Ľ�ʦ��Ϣ��\n", name);
	}

	// �ر��ļ�
	fclose(file);
	fclose(tempFile);

	// ɾ��ԭʼ�ļ�����������ʱ�ļ�
	remove("teacher.txt");
	rename("temp.txt", "teacher.txt");

	return;
}

void deleteTeacher(const char* name) {
	// ��ԭʼ�ļ�
	FILE* file = fopen("teacher.txt", "r");
	if (file == NULL) {
		printf("Error opening file!\n");
		exit(1);
	}

	// ������ʱ�ļ�
	FILE* tempFile = fopen("temp.txt", "w");
	if (tempFile == NULL) {
		printf("Error opening temporary file!\n");
		fclose(file);
		exit(1);
	}

	// ��ȡԭʼ�ļ����ݣ�������ƥ����д����ʱ�ļ�
	char line[100];
	int found = 0;
	while (fgets(line, sizeof(line), file) != NULL) {
		char sname[20];
		if (sscanf(line, "%s", sname) == 1) {
			if (strcmp(sname, name) == 0) {
				found = 1; // �ҵ�Ŀ���У����Ϊ���ҵ�
			}
			else {
				fprintf(tempFile, "%s", line); // ����ƥ����д����ʱ�ļ�
			}
		}
	}

	fclose(file);
	fclose(tempFile);

	// ɾ��ԭʼ�ļ�����������ʱ�ļ�
	remove("teacher.txt");
	rename("temp.txt", "teacher.txt");

	if (found) {
		printf("��ʦ %s ����Ϣɾ���ɹ���\n", name);
	}
	else {
		printf("δ�ҵ�����Ϊ %s �Ľ�ʦ��Ϣ��\n", name);
	}
}