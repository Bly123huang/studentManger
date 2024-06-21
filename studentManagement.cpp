#include"main.h"
char adminPassword[MAX_PASSWORD_LEN];
int studentManage()
{
	int choice;

	do {
		system("cls");
		printf("\n��ӭ����ѧ����Ϣ����\n");
		printf("1. ���ѧ����Ϣ\n");
		printf("2. ɾ��ѧ����Ϣ\n");
		printf("3. �޸�ѧ����Ϣ\n");
		printf("4. ��ѯѧ����Ϣ\n");
		printf("0. Exit\n");
		printf("���������ѡ��: ");
		int start;
		start:
		scanf("%d", &choice);

		switch (choice) {
		case 1:
		{

			// ����Ƿ��ǹ���Ա
			if (strcmp(getCurrentUserRole(), "admin") != 0) {
				printf("�ǹ���Ա�����ע��ʧ�ܣ�\n");
				return -1;
			}
			int start3;
		     start3:
			STUDENT_INFOEMATION stuinformation = {};
			
			printf("������ID��");
			scanf("%d", &stuinformation.id);
			if (findid("Stu_information.txt", stuinformation.id) == 1)
			{
				printf("��id�Ѿ�ע����������ظ�ע�ᣡ\n");
				Sleep(1000);
				system("cls");
				goto start3;
			}
			printf("�����ע��ѧ����Ϣ��\n");
			printf("������༶��");
			scanf("%s", &stuinformation.classs);
			printf("������������");
			scanf("%s",&stuinformation.name);
			printf("�������Ա�");
			scanf("%s",&stuinformation.gender);
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
			strcpy(stuinformation.user.role, "student");
		addStudent_Information(stuinformation.id,stuinformation.classs, 
			stuinformation.name, stuinformation.gender, stuinformation.age,
			stuinformation.telephone,stuinformation.stuScore.math,stuinformation.stuScore.english,
			stuinformation.stuScore.chinese,stuinformation.user.username,stuinformation.user.password,
			stuinformation.user.role);
			break;
		}
			
		case 2:
		{
			char* currentRole = getCurrentUserRole();
			if(currentRole==NULL)
			{
				Log(cErr, "getCurrentUserRole() failed");
				break;
			}

				if(strcmp(currentRole,"student")==0)
				{
					printf("��û��Ȩ��ɾ��ѧ����Ϣ��\n");
					system("pause");
					break;
				}
				printf("������Ҫɾ����ѧ��ID: ");
				int id;
				scanf_s("%d", &id);
				char confirm1;
				printf("ȷ��Ҫɾ��IDΪ %d ��ѧ����Ϣ��(Y/N) ", id);
				while (getchar() != '\n');
				scanf("%c", &confirm1);

				if (confirm1 == 'Y' || confirm1 == 'y')
				{
					deleteStudent_Information(id);
				}
				else 
				{
					printf("ȡ��ɾ����\n");
					system("pause");
				}
				
			    break;
		}

		case 3:
		{
		
			modifyStudent_Information();
			break;
		}
			
		case 4:
		{
			int id;
			system("cls");
			printf("������Ҫ��ѯ��ѧ��ID: ");
			scanf("%d", &id);
			if (getCurrentUserId() == id ||strcmp(getCurrentUserRole(),"teacher")==0||strcmp(getCurrentUserRole(),"admin")==0)
			{
				queryStudent_Information(id);
			}
			else
			{
				printf("��û��Ȩ�޲�ѯ�����˵�ѧ����Ϣ��\n");
				system("pause");
			}
				break;
		}
		case 0:
			printf("Exiting...\n");
			exit(0);
			break;
		default:
			printf("��Ч��ѡ�����������룡\n");
			goto start;
		}
	} while (choice != 8);
	
	return 0;
	system("pause");
}



 /// <summary>
 
 /// </summary>

 //����ѧ����Ϣ
 STUDENT_INFOEMATION Stu_information;
 void addStudent_Information(int id ,const char* sclass,const char* sname,const char* gender,
	 int age,const char* telephone,double smath, double senglish,double schinese,char username[20],
	 char password[20],char role[20])
 {
	 // ����һ�� Score �ṹ���������������ֵ���浽�ṹ����
	 Stu_information.id = id;
	 strcpy(Stu_information.classs, sclass);
	 strcpy(Stu_information.name, sname);
	 strcpy(Stu_information.gender, gender);
	 Stu_information.age = age;
	 strcpy(Stu_information.telephone, telephone);
	 Stu_information.stuScore.math = smath;
	 Stu_information.stuScore.english = senglish;
	 Stu_information.stuScore.chinese = schinese;
	 strcpy(Stu_information.user.username, username);
	 strcpy(Stu_information.user.password, password);
	 strcpy(Stu_information.user.role, role);

	 // ���ļ�����׷�ӷ�ʽд��
	 FILE* file = fopen("Stu_information.txt", "a");
	 if (file == NULL) {
		 printf("Error opening file!\n");
		 exit(1);
	 }
	 fprintf(file, "%d %s %s %s %d %s %d %d %d %s %s %s\n",
		 Stu_information.id,
		 Stu_information.classs,
		 Stu_information.name,
		 Stu_information.gender,
		 Stu_information.age,
		 Stu_information.telephone,
		 Stu_information.stuScore.math,
		 Stu_information.stuScore.english,
		 Stu_information.stuScore.chinese,
		 Stu_information.user.username,
		 Stu_information.user.password,
		 Stu_information.user.role);
	 printf("��Ϣ¼��ɹ���\n");
	 fclose(file);
	 system("pause");
	 return;
 }

 //ɾ��ѧ����Ϣ
 void deleteStudent_Information(int id)
 {
	


	 // ��ԭʼ�ļ�
	 FILE* file = fopen("Stu_information.txt", "r");
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
	 while (fgets(line, sizeof(line), file) != NULL) 
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
			 char sname[20];
			 if (sscanf(line, "%s", sname) == 1)
			 {
				 if (sid == id)
				 {
					 found = 1; // �ҵ�Ŀ���У����Ϊ���ҵ�
				 }
				 else
				 {
					 fprintf(tempFile, "%s", line); // ����ƥ����д����ʱ�ļ�
				 }
			 }
		 }
		
	 }

	 fclose(file);
	 fclose(tempFile);

	 // ɾ��ԭʼ�ļ�����������ʱ�ļ�
	 remove("Stu_information.txt");
	 rename("temp.txt", "Stu_information.txt");

	 if (found) 
	 {
		 printf("id %d ����Ϣɾ���ɹ���\n",id);
	 }
	 else 
	 {
		 printf("δ�ҵ�idΪ %d ��ѧ����Ϣ��\n",id);
	 }
	 fclose(file);
	 system("pause");
	 return;
 }

 //��ѯѧ����Ϣ
 void queryStudent_Information(int id)
 {
	 // ���ļ�����ֻ����ʽ��ȡ
	 FILE* file = fopen("Stu_information.txt", "r");
	 if (file == NULL) {
		 printf("Error opening file!\n");
		 exit(1);
	 }
	 int found = 0;
	 // �����ļ����ҵ�Ҫ��ѯ��ѧ����Ϣ������ӡ
	 char line[100];
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
		 char role[20];
		
		 // �����ļ���ʽΪ��ѧ�� �༶ ���� �Ա� ���� �绰 ��ѧ Ӣ�� ���� �û��� ���� ��ɫ

		 if (sscanf(line, "%d %s %s %s %d %s %f %f %f %s %s %s", &sid, sclass, sname, gender, &age, telephone,
			 &math, &english, &chinese, username, password, role) != EOF)
		 {
			 
			 if (sid == id)
			 {
				 // �ҵ�Ҫ��ѯ��ѧ����Ϣ����ӡ����
				 printf("ѧ��: %d\n", sid);
				 printf("�༶: %s\n", sclass);
				 printf("����: %s\n", sname);
				 printf("�Ա�: %s\n", gender);
				 printf("����: %d\n", age);
				 printf("�绰: %s\n", telephone);
				 found = 1;
				 // ����Ƿ��ǹ���Ա
				 if (strcmp(getCurrentUserRole(), "admin") == 0)
				 {
					 printf("�û���: %s\n",username);
					 printf("����: %s\n", password);
					 printf("��ɫ: %s\n",role);
				 }
				 fclose(file);
				 system("pause");
				 return;
			 }

		 }
	 }

	 if (found==0) 
	 {
		 printf("δ�ҵ�IDΪ %d ��ѧ����Ϣ��\n", id);
		
	 }
	 fclose(file);
	 system("pause");
	 return;
 }

 void modifyStudent_Information()
 {
	 Student stu_information = {""};
	 // ���ļ�����ֻ����ʽ��ȡ
	 FILE* file = fopen("Stu_information.txt", "r");
	 if (file == NULL) {
		 printf("Error opening file!\n");
		 exit(1);
	 }

	 // ������ʱ�ļ����洢���º������
	 FILE* tempFile = fopen("temp.txt", "wb");
	 if (tempFile == NULL) {
		 printf("Error opening temporary file!\n");
		 fclose(file);
		 exit(1);
	 }
	 char class_new[20];
	char name_new[20];
	char gender_new[10];
	int age_new = 0;
	char telephone_new[100];

	 // ����һ�� Score �ṹ���������������ֵ���浽�ṹ����
	 //studentScore.id = id;
	

	 // ��������Խ�ѧ���ɼ����浽�ļ��������ݿ��У����߽�����������
	  // ���ļ�����׷�ӷ�ʽд��


	 printf("�������û�����id��:  ");
	 int userid;
	 scanf("%d", &userid);
	 int user_ing = getCurrentUserId();
	 char* user_role= getCurrentUserRole();
	 if (user_ing!= userid&&strcmp(user_role, "student") == 0 )
	 {
		 printf("��û��Ȩ���޸Ĵ���Ϣ��\n");
		 Sleep(2000);
		 return;
	 }
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
				 printf("ѧ�ţ�%d\n", sid);
				 printf("�༶��%s\n", sclass);

				 printf("������%s\n", sname);
				 printf("�Ա�%s\n", gender);
				 printf("���䣺%d\n", age);
				 printf("�绰��%s\n", telephone);
				 found = 1;
				 printf("�������µİ༶��");
				 scanf("%s", class_new);
				 printf("\n�������µ�������");
				 scanf("%s", name_new);
				 printf("\n�������µ��Ա�");
				 scanf("%s", gender_new);
				 printf("\n�������µ����䣺");
				 scanf("%d", &age_new);
				 printf("\n�������µĵ绰��");
				 scanf("%s", telephone_new);
	
				 fprintf(tempFile, "%d %s %s %s %d %s %f %f %f %s %s %s\n", userid, class_new, name_new, gender_new, age_new, telephone_new,
					 math,english, chinese, username, password, roles);
				 printf("��Ϣ���³ɹ���\n");
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
		 printf("δ�ҵ�IDΪ %d ��ѧ����Ϣ��\n", userid);
		 Sleep(2000);
	 }

	 // �ر��ļ�
	 fclose(file);
	 fclose(tempFile);

	 // ɾ��ԭʼ�ļ�����������ʱ�ļ�
	 remove("Stu_information.txt");
	 rename("temp.txt", "Stu_information.txt");

	 return;
 }