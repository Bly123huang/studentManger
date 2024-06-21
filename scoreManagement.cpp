#include"main.h"

int scoreManage()
{
	char* currentRole = getCurrentUserRole();
	

	if (currentRole == NULL)
	{
		Log(cErr, "getCurrentUserRole() failed");
	}
	int choice;
	do {
		system("cls");
		printf("\n��ӭ����ɼ���Ϣ����\n");
		printf("1. ¼��ѧ���ɼ�\n");
		printf("2. ��ѯѧ���ɼ�\n");
		printf("3. �޸�ѧ���ɼ�\n");
		printf("4. ����ƽ���ɼ�\n");
		printf("5. �ܷ�����\n");
		printf("6. Exit\n");
		printf("���������ѡ��: ");
		int start;
		start:
		scanf_s("%d", &choice);

		switch (choice) {
		case 1:
		{
			if (strcmp(currentRole, "student") == 0)
			{
				printf("��û��Ȩ������ѧ���ɼ���\n");
				Sleep(3000);
				break;
			}
			addStudentScore();
				break;
		}
		case 2:
		{
			printf("������ѧ��: ");
			int id;
			scanf_s("%d", &id);
			int cur_id=getCurrentUserId();
			if (strcmp(currentRole, "student") == 0 && cur_id != id)
			{
				printf("��û��Ȩ�޲�ѯ�����˵�ѧ���ɼ���\n");
				Sleep(3000);
				goto start;
			}
			queryStudent(id);
			break;
		}

		case 3:

		{
			if (strcmp(currentRole, "student") == 0)
			{
				printf("��û��Ȩ���޸�ѧ���ɼ���\n");
				Sleep(3000);
				break;
			}
			modifyStudent();
			break;
		}
		case 4:
		{
			printAverageScore();
			break;
		}
		case 5:
		{
			rankScores();
			break;
		}
			
	
		case 6:
			exit(0);
			break;
		default:
			printf("Invalid choice. Please try again.\n");
			goto start;
		}
	} while (choice != 6);

	return 0;
}


//¼��ѧ���ɼ�
Score studentScore;
void addStudentScore()
{

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

	int id=0;
	float chinese=0; 
	float math=0;
	float english=0;

	// ����һ�� Score �ṹ���������������ֵ���浽�ṹ����
	studentScore.id = id;
	studentScore.chinese = chinese;
	studentScore.math = math;
	studentScore.english = english;

	// ��������Խ�ѧ���ɼ����浽�ļ��������ݿ��У����߽�����������
	 // ���ļ�����׷�ӷ�ʽд��


	printf("�������û�����id��:  ");
	int userid;
	scanf("%d", &userid);
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
	
	if (sscanf(line, "%d %s %s %s %d %s %f %f %f %s %s %s", &sid, sclass, sname, gender, &age, telephone, &math, &english, &chinese, username, password, roles) != EOF)
	{

		if (sid == userid)
		{
			found = 1;
			printf("��������ѧ�ɼ�: ");
			scanf("%lf", &studentScore.math);
			printf("������Ӣ��ɼ�: ");
			scanf("%lf", &studentScore.english);
			printf("���������ĳɼ�: ");
			scanf("%lf", &studentScore.chinese);
			// ���µĳɼ�д�뵽��ʱ�ļ���
			fprintf(tempFile, "%d %s %s %s %d %s %f %f %f %s %s %s\n", userid, sclass, sname, gender, age, telephone, studentScore.math, studentScore.english, studentScore.chinese, username,password, roles);
			printf("�ɼ�¼��ɹ���\n");
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

//��ѯѧ���ɼ�
void queryStudent(int id)
{
	// ���ļ�����ֻ����ʽ��ȡ
	FILE* file = fopen("Stu_information.txt", "r");
	if (file == NULL) {
		printf("Error opening file!\n");
		exit(1);
	}
	// ��ȡ�ļ����ݣ�����ӡ����Ļ��
	char line[100];
	while (fgets(line, 100, file)!= NULL) 
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
		if (sscanf(line, "%d %s %s %s %d %s %f %f %f %s %s %s", &sid, sclass, sname, gender, &age, telephone, &math, &english, &chinese, username, password, roles) != EOF)
		{

			if (sid == id)
			{
				int found = 1;
				printf("ѧ��: %d\n", sid);
				printf("����: %s\n", sname);
				printf("����: %.2f\n", chinese);
				printf("��ѧ: %.2f\n", math);
				printf("Ӣ��: %.2f\n", english);
				Sleep(2000);
			}
		}
	}
	fclose(file);
	system("pause");
	return;
}

//�޸�ѧ���ɼ�
void modifyStudent()
{

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
	//int id = 0;
	float chinese = 0;
	float math = 0;
	float english = 0;

	// ����һ�� Score �ṹ���������������ֵ���浽�ṹ����
	//studentScore.id = id;
	studentScore.chinese = chinese;
	studentScore.math = math;
	studentScore.english = english;

	// ��������Խ�ѧ���ɼ����浽�ļ��������ݿ��У����߽�����������
	 // ���ļ�����׷�ӷ�ʽд��


	printf("�������û�����id��:  ");
	int userid;
	scanf("%d", &userid);
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

		if (sscanf(line, "%d %s %s %s %d %s %f %f %f %s %s %s", &sid, sclass, sname, gender, &age, telephone, &math, &english, &chinese, username, password, roles) != EOF)
		{

			if (sid == userid)
			{
				printf("�û�ID��%d\n", userid);
				printf("������%s\n", sname);
				printf("���ģ�%.2f\n", chinese);
				printf("��ѧ��%.2f\n", math);
				printf("Ӣ�%.2f\n", english);
				found = 1;
				printf("�������µ���ѧ�ɼ�: ");
				scanf("%lf", &studentScore.math);
				printf("�������µ�Ӣ��ɼ�: ");
				scanf("%lf", &studentScore.english);
				printf("�������µ����ĳɼ�: ");
				scanf("%lf", &studentScore.chinese);
				// ���µĳɼ�д�뵽��ʱ�ļ���
				fprintf(tempFile, "%d %s %s %s %d %s %f %f %f %s %s %s\n", userid, sclass, sname, gender, age, telephone, studentScore.math, studentScore.english, studentScore.chinese, username, password, roles);
				printf("�ɼ�¼��ɹ���\n");
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

// ���㲢��ӡƽ���ɼ�����
void printAverageScore()
{
	FILE* file = fopen("Stu_information.txt", "r"); // ���ļ�
	if (file == NULL) {
		printf("Error opening file!\n"); // ���������Ϣ
		exit(1); // �˳�����
	}
	float sumChinese = 0.0; // ��ʼ�������ܳɼ�
	float sumMath = 0.0; // ��ʼ����ѧ�ܳɼ�
	float sumEnglish = 0.0; // ��ʼ��Ӣ���ܳɼ�

	float sumChinese_class = 0.0; // ��ʼ�������ܳɼ�
	float sumMath_class = 0.0; // ��ʼ����ѧ�ܳɼ�
	float sumEnglish_class = 0.0; // ��ʼ��Ӣ���ܳɼ�

	int count_class = 0; // ��ʼ���༶ѧ������
	int count_school = 0; // ��ʼ��ѧУѧ������
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

		if (sscanf(line, "%d %s %s %s %d %s %f %f %f %s %s %s", &sid, sclass, sname, gender, &age, telephone, &math, &english, &chinese, username, password, roles) != EOF)
		{
			if (strcmp(roles, "student")==0)
			{
				count_school++;
				sumChinese+=chinese;
				sumMath+=math;
				sumEnglish+=english;
			}
		if (strcmp(sclass, getCurrentUserClass()) == 0)
		{

			count_class++;
			sumChinese_class += chinese;
			sumMath_class += math;
			sumEnglish_class += english;
			found = 1;
			}

		}
	}
	fclose(file); // �ر��ļ�
	if (count_school == 0) {
		printf("û���κ�ѧ���ĳɼ���\n"); // �����ѧ���ɼ���Ϣ
	}
	else {
		float averageChinese = sumChinese / count_school; // ��������ƽ���ɼ�
		float averageMath = sumMath / count_school; // ������ѧƽ���ɼ�
		float averageEnglish = sumEnglish / count_school; // ����Ӣ��ƽ���ɼ�

		printf("ȫУƽ���ɼ���");
		printf("ƽ�����ĳɼ�: %.2f ", averageChinese); // �������ƽ���ɼ�
		printf("ƽ����ѧ�ɼ�: %.2f ", averageMath); // �����ѧƽ���ɼ�
		printf("ƽ��Ӣ��ɼ�: %.2f ", averageEnglish); // ���Ӣ��ƽ���ɼ�


	}
	if (count_class == 0) {
		printf("û���κΰ༶��ѧ���ĳɼ���\n"); // ����ް༶ѧ����Ϣ
	}
	else {
		float averageChinese_class = sumChinese_class / count_class; // ��������ƽ���ɼ�
		float averageMath_class = sumMath_class / count_class; // ������ѧƽ���ɼ�
		float averageEnglish_class = sumEnglish_class / count_class; // ����Ӣ��ƽ���ɼ�

		printf("\n�༶ƽ���ɼ���");
		printf("ƽ�����ĳɼ�: %.2f ", averageChinese_class); // �������ƽ���ɼ�
		printf("ƽ����ѧ�ɼ�: %.2f ", averageMath_class); // �����ѧƽ���ɼ�
		printf("ƽ��Ӣ��ɼ�: %.2f \n", averageEnglish_class); // ���Ӣ��ƽ���ɼ�
	}
	system("pause"); // ��ͣ�����Բ鿴���
	fclose(file);
	return; // ����
}

// �ɼ���������
void rankScores()
{
	FILE* file = fopen("Stu_information.txt", "r");
	if (file == NULL) {
		printf("Error opening file!\n");
		exit(1);
	}

	// ����һ���ṹ���������洢ѧ������Ϣ
	struct Score {
		int id;
		char name[20];
		float chinese;
		float math;
		float english;
	} scores[100]; // ��������� 100 ��ѧ��

	int count = 0; // ѧ������


	// ����һ���ṹ���������洢�༶ѧ������Ϣ
	struct Score_class {
		int id;
		char name[20];
		float chinese;
		float math;
		float english;
	} scores_class[100]; // ��������� 100 ��ѧ��

	int countclass = 0; // ѧ������
	// ��ȡ�ļ����ݣ�����ѧ����Ϣ���浽�ṹ��������
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
		char roles[20];
		// �����ļ���ʽΪ��ѧ�� �༶ ���� �Ա� ���� �绰 ��ѧ Ӣ�� ���� �û��� ���� ��ɫ
		if (sscanf(line, "%d %s %s %s %d %s %f %f %f %s %s %s", &sid, sclass, sname, gender, &age, telephone,
			&math, &english, &chinese, username, password, roles) != EOF) 
		{
			if (strcmp(roles, "student") == 0) 
			{
				scores[count].id = sid;
				strcpy(scores[count].name, sname);
				scores[count].chinese = chinese;
				scores[count].math = math;
				scores[count].english = english;
				count++;
			}
			char* currentClass = getCurrentUserClass();
			if (strcmp(sclass, currentClass) == 0&&strcmp(roles, "student")==0)
			{
				scores_class[countclass].id = sid;
				strcpy(scores_class[countclass].name, sname);
				scores_class[countclass].chinese = chinese;
				scores_class[countclass].math = math;
				scores_class[countclass].english = english;
				countclass++;
				
			}
			
		}
	}
	fclose(file);

	// �����ֽܷ�������
	for (int i = 0; i < count - 1; i++)
	{
		for (int j = 0; j < count - i - 1; j++) 
		{
			float total1 = scores[j].chinese + scores[j].math + scores[j].english;
			float total2 = scores[j + 1].chinese + scores[j + 1].math + scores[j + 1].english;
			if (total1 < total2) 
			{
				// ��������ѧ������Ϣ
				struct Score temp = scores[j];
				scores[j] = scores[j + 1];
				scores[j + 1] = temp;
			}
		}
	}for (int i = 0; i < countclass - 1; i++)
	{
		for (int j = 0; j < countclass - i - 1; j++)
		{
			float total1 = scores_class[j].chinese + scores_class[j].math + scores_class[j].english;
			float total2 = scores_class[j + 1].chinese + scores_class[j + 1].math + scores_class[j + 1].english;
			if (total1 < total2)
			{
				// ��������ѧ������Ϣ
				struct Score_class temp = scores_class[j];
				scores_class[j] = scores_class[j + 1];
				scores_class[j + 1] = temp;
			}
		}
	}
	system("cls"); // ����
	// ��ӡѧУ�������
	printf("ѧУ����\t%-10s\t%-8s\t%-6s\t%-6s\t%-6s\t%-6s\n", "ѧ��", "����", "����", "��ѧ", "Ӣ��", "�ܷ�");

	for (int i = 0; i < count; i++) {
		float total = scores[i].chinese + scores[i].math + scores[i].english;
		printf("%-10d\t%-10d\t%-8s\t%-6.2f\t%-6.2f\t%-6.2f\t%-6.2f\n", i + 1, scores[i].id, scores[i].name, scores[i].chinese, scores[i].math, scores[i].english, total);
	}

	printf("\n");

	// ��ӡ�༶�������
	printf("�༶����\t%-10s\t%-8s\t%-6s\t%-6s\t%-6s\t%-6s\n", "ѧ��", "����", "����", "��ѧ", "Ӣ��", "�ܷ�");

	for (int i = 0; i < countclass; i++) {
		float total_class = scores_class[i].chinese + scores_class[i].math + scores_class[i].english;
		printf("%-10d\t%-8d\t%-8s\t%-6.2f\t%-6.2f\t%-6.2f\t%-6.2f\n", i + 1, scores_class[i].id, scores_class[i].name, scores_class[i].chinese, scores_class[i].math, scores_class[i].english, total_class);
	}

	system("pause");
	return;
}

