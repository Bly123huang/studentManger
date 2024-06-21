#include"main.h"
char adminPassword1[MAX_PASSWORD_LEN];
void teacherManage()
{
	int choice;
	do {
		system("cls");
		printf("\n欢迎进入教师信息管理\n");
		printf("1. 新建教师信息\n");
		printf("2. 录入教师信息\n");
		printf("3. 查询教师信息\n");
		printf("4. 修改教师信息\n");
		printf("5. 删除教师信息\n");
		printf("0.  Exit\n");
		printf("请输入你的选择: ");
		scanf_s("%d", &choice);
		switch (choice) {
			
		case 1:
			createTeacher();
			break;

		case 2:
		{
			// 检查是否是管理员
			if (strcmp(getCurrentUserRole(), "admin") != 0) {
				printf("非管理员！\n");
				return;
			}
			inputTeacher();
			break;
		}
		case 3:
		{

			printf("请输入要查询的教师姓名: ");
			char names[10];
			scanf("%s", names);
			system("cls");
			queryTeacher(names);
			break;

		}

		case 4:
		{
			// 检查是否是管理员
			if (strcmp(getCurrentUserRole(), "admin") != 0) {
				printf("非管理员！\n");
				return;
			}
			const char name[10] = "";
			printf("请输入要修改的教师姓名: ");
			scanf("%s", name);
			system("cls");
			modifyTeacher(name);
			break;
		}
		case 5:
		{
			
			// 检查是否是管理员
			if (strcmp(getCurrentUserRole(), "admin") != 0) {
				printf("非管理员！\n");
				return;
			}
			const char name[10] = "";
			printf("请输入要删除的教师姓名: ");
			scanf("%s", name);
			system("cls");
			char confirm1;
			printf("确认要删除姓名为 %s的学生信息吗？(Y/N) ", name);
			while (getchar() != '\n');
			scanf("%c", &confirm1);

			if (confirm1 == 'Y' || confirm1 == 'y')
			{
				deleteTeacher(name);
			}
			else
			{
				printf("取消删除！\n");
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


//新建教师信息
void createTeacher()
{
	// 检查是否是管理员
	if (strcmp(getCurrentUserRole(), "admin") != 0) {
		printf("非管理员，添加注册失败！\n");
		Sleep(1000);
		return;
	}
	STUDENT_INFOEMATION stuinformation = {};
	printf("请输入ID：");
	scanf("%d", &stuinformation.id);
	printf("请输入班级：");
	scanf("%s", &stuinformation.classs);
	printf("请输入姓名：");
	scanf("%s", &stuinformation.name);
	printf("请输入性别：");
	scanf("%s", &stuinformation.gender);
	printf("请输入年龄：");
	scanf("%d", &stuinformation.age);
	printf("请输入电话：");
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




//录入教师信息
TEACHER teacher_information;
void inputTeacher()
{
	printf("请输入教师ID:\n");
	int id;
	scanf("%d",&id);
	if (findid("Stu_information.txt", id) == 0)//查找是否在文件中有录入该id
	{
		printf("未查找到该教师信息！\n");
		return;
	}
	system("cls");
	printf("请输入教师信息:\n");
	printf("请输入教师姓名: ");
	int m=scanf("%s", teacher_information.name);
	printf("请输入教师性别: ");
	m = scanf("%s", teacher_information.gender);
	printf("请输入教师年龄: ");
	m = scanf("%d", &teacher_information.age);
	printf("请输入教师学科: ");
	m = scanf("%s", teacher_information.subject);
	printf("请输入教师电话: ");
	m = scanf("%s", teacher_information.phone);
	printf("请输入教师地址: ");
	m = scanf("%s", teacher_information.address);
	FILE* fp = fopen("teacher.txt", "ab+");
	fprintf(fp, "%s %s %d %s %s %s\n", teacher_information.name, teacher_information.gender, teacher_information.age, teacher_information.subject, teacher_information.phone, teacher_information.address);
	fclose(fp);	
	printf("教师信息录入成功!\n");
	Sleep(2000);
	return;
}

//查询教师信息
void queryTeacher(char name[10]) {
	// 打开文件，以只读方式读取
	FILE* fp = fopen("teacher.txt", "r");
	if (fp == NULL) {
		printf("Error opening file!\n");
		exit(1);
	}
	// 读取文件内容，并打印到屏幕上
	char sname[20];
	char sgender[10];
	int sage;
	char ssubject[20];
	char sphone[20];
	char saddress[50];
	int found = 0;
	while (fscanf(fp, "%s %s %d %s %s %s", sname, sgender, &sage, ssubject, sphone, saddress) != EOF) {
		if (strcmp(sname, name) == 0) {
			printf("姓名: %s\n", sname);
			printf("性别: %s\n", sgender);
			printf("年龄: %d\n", sage);
			printf("学科: %s\n", ssubject);
			printf("电话: %s\n", sphone);
			printf("地址: %s\n", saddress);
			found = 1;
			break;
		}
	}
	fclose(fp);
	if (!found) {
		printf("没有找到该教师信息!\n");
	}
	system("pause");
	return;
}

void modifyTeacher(const char* name) 
{
	// 打开文件，以读写方式打开
	FILE* file = fopen("teacher.txt", "r+");
	if (file == NULL) {
		printf("Error opening file!\n");
		exit(1);
	}

	// 创建临时文件来存储更新后的内容
	FILE* tempFile = fopen("temp.txt", "w");
	if (tempFile == NULL) {
		printf("Error opening temporary file!\n");
		fclose(file);
		exit(1);
	}
	// 读取文件内容，并打印到屏幕上
	char line[100];
	int found = 0; // 标志是否找到目标行
	while (fgets(line, 100, file) != NULL) {
		char sname[20];
		char sgender[10];
		int sage;
		char ssubject[20];
		char sphone[100];
		char saddress[50];
		if (sscanf(line, "%s %s %d %s %s %s", sname, sgender, &sage, ssubject, sphone, saddress) == 6) {
			if (strcmp(sname, name) == 0) {
				found = 1; // 找到目标行
				printf("姓名: %s\n", sname);
				printf("性别: %s\n", sgender);
				printf("年龄: %d\n", sage);
				printf("学科: %s\n", ssubject);
				printf("电话: %s\n", sphone);
				printf("地址: %s\n", saddress);
				printf("请输入新的性别: ");
				int m = scanf("%s", sgender);
				printf("请输入新的年龄: ");
				m = scanf("%d", &sage);
				printf("请输入新的学科: ");
				m = scanf("%s", ssubject);
				printf("请输入新的电话: ");
				m = scanf("%s", sphone);
				printf("请输入新的地址: ");
				m = scanf("%s", saddress);
				// 将新的信息写入到临时文件中
				fprintf(tempFile, "%s %s %d %s %s %s\n", sname, sgender, sage, ssubject, sphone, saddress);
				printf("教师信息修改成功！\n");
				Sleep(2000);
			}
			else {
				// 将原始内容写入临时文件
				fputs(line, tempFile);
			}
		}
	}

	// 如果没有找到目标行，则输出提示信息
	if (!found) {
		printf("未找到姓名为 %s 的教师信息！\n", name);
	}

	// 关闭文件
	fclose(file);
	fclose(tempFile);

	// 删除原始文件并重命名临时文件
	remove("teacher.txt");
	rename("temp.txt", "teacher.txt");

	return;
}

void deleteTeacher(const char* name) {
	// 打开原始文件
	FILE* file = fopen("teacher.txt", "r");
	if (file == NULL) {
		printf("Error opening file!\n");
		exit(1);
	}

	// 创建临时文件
	FILE* tempFile = fopen("temp.txt", "w");
	if (tempFile == NULL) {
		printf("Error opening temporary file!\n");
		fclose(file);
		exit(1);
	}

	// 读取原始文件内容，并将非匹配行写入临时文件
	char line[100];
	int found = 0;
	while (fgets(line, sizeof(line), file) != NULL) {
		char sname[20];
		if (sscanf(line, "%s", sname) == 1) {
			if (strcmp(sname, name) == 0) {
				found = 1; // 找到目标行，标记为已找到
			}
			else {
				fprintf(tempFile, "%s", line); // 将非匹配行写入临时文件
			}
		}
	}

	fclose(file);
	fclose(tempFile);

	// 删除原始文件并重命名临时文件
	remove("teacher.txt");
	rename("temp.txt", "teacher.txt");

	if (found) {
		printf("教师 %s 的信息删除成功！\n", name);
	}
	else {
		printf("未找到姓名为 %s 的教师信息！\n", name);
	}
}