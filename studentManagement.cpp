#include"main.h"
char adminPassword[MAX_PASSWORD_LEN];
int studentManage()
{
	int choice;

	do {
		system("cls");
		printf("\n欢迎进入学生信息管理\n");
		printf("1. 添加学生信息\n");
		printf("2. 删除学生信息\n");
		printf("3. 修改学生信息\n");
		printf("4. 查询学生信息\n");
		printf("0. Exit\n");
		printf("请输入你的选择: ");
		int start;
		start:
		scanf("%d", &choice);

		switch (choice) {
		case 1:
		{

			// 检查是否是管理员
			if (strcmp(getCurrentUserRole(), "admin") != 0) {
				printf("非管理员，添加注册失败！\n");
				return -1;
			}
			int start3;
		     start3:
			STUDENT_INFOEMATION stuinformation = {};
			
			printf("请输入ID：");
			scanf("%d", &stuinformation.id);
			if (findid("Stu_information.txt", stuinformation.id) == 1)
			{
				printf("此id已经注册过，请勿重复注册！\n");
				Sleep(1000);
				system("cls");
				goto start3;
			}
			printf("请继续注册学生信息：\n");
			printf("请输入班级：");
			scanf("%s", &stuinformation.classs);
			printf("请输入姓名：");
			scanf("%s",&stuinformation.name);
			printf("请输入性别：");
			scanf("%s",&stuinformation.gender);
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
					printf("你没有权限删除学生信息！\n");
					system("pause");
					break;
				}
				printf("请输入要删除的学生ID: ");
				int id;
				scanf_s("%d", &id);
				char confirm1;
				printf("确认要删除ID为 %d 的学生信息吗？(Y/N) ", id);
				while (getchar() != '\n');
				scanf("%c", &confirm1);

				if (confirm1 == 'Y' || confirm1 == 'y')
				{
					deleteStudent_Information(id);
				}
				else 
				{
					printf("取消删除！\n");
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
			printf("请输入要查询的学生ID: ");
			scanf("%d", &id);
			if (getCurrentUserId() == id ||strcmp(getCurrentUserRole(),"teacher")==0||strcmp(getCurrentUserRole(),"admin")==0)
			{
				queryStudent_Information(id);
			}
			else
			{
				printf("你没有权限查询其他人的学生信息！\n");
				system("pause");
			}
				break;
		}
		case 0:
			printf("Exiting...\n");
			exit(0);
			break;
		default:
			printf("无效的选择！请重新输入！\n");
			goto start;
		}
	} while (choice != 8);
	
	return 0;
	system("pause");
}



 /// <summary>
 
 /// </summary>

 //导入学生信息
 STUDENT_INFOEMATION Stu_information;
 void addStudent_Information(int id ,const char* sclass,const char* sname,const char* gender,
	 int age,const char* telephone,double smath, double senglish,double schinese,char username[20],
	 char password[20],char role[20])
 {
	 // 创建一个 Score 结构体变量，并将参数值保存到结构体中
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

	 // 打开文件，以追加方式写入
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
	 printf("信息录入成功！\n");
	 fclose(file);
	 system("pause");
	 return;
 }

 //删除学生信息
 void deleteStudent_Information(int id)
 {
	


	 // 打开原始文件
	 FILE* file = fopen("Stu_information.txt", "r");
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
		 // 假设文件格式为：学号 班级 姓名 性别 年龄 电话 数学 英语 语文 用户名 密码 角色

		 if (sscanf(line, "%d %s %s %s %d %s %f %f %f %s %s %s", &sid, sclass, sname, gender, &age, telephone,
			 &math, &english, &chinese, username, password, roles) != EOF)

		 {
			 char sname[20];
			 if (sscanf(line, "%s", sname) == 1)
			 {
				 if (sid == id)
				 {
					 found = 1; // 找到目标行，标记为已找到
				 }
				 else
				 {
					 fprintf(tempFile, "%s", line); // 将非匹配行写入临时文件
				 }
			 }
		 }
		
	 }

	 fclose(file);
	 fclose(tempFile);

	 // 删除原始文件并重命名临时文件
	 remove("Stu_information.txt");
	 rename("temp.txt", "Stu_information.txt");

	 if (found) 
	 {
		 printf("id %d 的信息删除成功！\n",id);
	 }
	 else 
	 {
		 printf("未找到id为 %d 的学生信息！\n",id);
	 }
	 fclose(file);
	 system("pause");
	 return;
 }

 //查询学生信息
 void queryStudent_Information(int id)
 {
	 // 打开文件，以只读方式读取
	 FILE* file = fopen("Stu_information.txt", "r");
	 if (file == NULL) {
		 printf("Error opening file!\n");
		 exit(1);
	 }
	 int found = 0;
	 // 遍历文件，找到要查询的学生信息，并打印
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
		
		 // 假设文件格式为：学号 班级 姓名 性别 年龄 电话 数学 英语 语文 用户名 密码 角色

		 if (sscanf(line, "%d %s %s %s %d %s %f %f %f %s %s %s", &sid, sclass, sname, gender, &age, telephone,
			 &math, &english, &chinese, username, password, role) != EOF)
		 {
			 
			 if (sid == id)
			 {
				 // 找到要查询的学生信息，打印该行
				 printf("学号: %d\n", sid);
				 printf("班级: %s\n", sclass);
				 printf("姓名: %s\n", sname);
				 printf("性别: %s\n", gender);
				 printf("年龄: %d\n", age);
				 printf("电话: %s\n", telephone);
				 found = 1;
				 // 检查是否是管理员
				 if (strcmp(getCurrentUserRole(), "admin") == 0)
				 {
					 printf("用户名: %s\n",username);
					 printf("密码: %s\n", password);
					 printf("角色: %s\n",role);
				 }
				 fclose(file);
				 system("pause");
				 return;
			 }

		 }
	 }

	 if (found==0) 
	 {
		 printf("未找到ID为 %d 的学生信息！\n", id);
		
	 }
	 fclose(file);
	 system("pause");
	 return;
 }

 void modifyStudent_Information()
 {
	 Student stu_information = {""};
	 // 打开文件，以只读方式读取
	 FILE* file = fopen("Stu_information.txt", "r");
	 if (file == NULL) {
		 printf("Error opening file!\n");
		 exit(1);
	 }

	 // 创建临时文件来存储更新后的内容
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

	 // 创建一个 Score 结构体变量，并将参数值保存到结构体中
	 //studentScore.id = id;
	

	 // 在这里可以将学生成绩保存到文件或者数据库中，或者进行其他操作
	  // 打开文件，以追加方式写入


	 printf("请输入用户名（id）:  ");
	 int userid;
	 scanf("%d", &userid);
	 int user_ing = getCurrentUserId();
	 char* user_role= getCurrentUserRole();
	 if (user_ing!= userid&&strcmp(user_role, "student") == 0 )
	 {
		 printf("您没有权限修改此信息！\n");
		 Sleep(2000);
		 return;
	 }
	 // 遍历文件，找到要查询的学生信息，并打印
	 char line[100];
	 int found = 0; // 标志是否找到目标行
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
		 // 假设文件格式为：学号 班级 姓名 性别 年龄 电话 数学 英语 语文 用户名 密码 角色

		 if (sscanf(line, "%d %s %s %s %d %s %f %f %f %s %s %s", &sid, sclass, sname, gender, &age, telephone,
			 &math, &english, &chinese, username, password, roles) != EOF)
		 {

			 if (sid == userid)
			 {
				 printf("学号：%d\n", sid);
				 printf("班级：%s\n", sclass);

				 printf("姓名：%s\n", sname);
				 printf("性别：%s\n", gender);
				 printf("年龄：%d\n", age);
				 printf("电话：%s\n", telephone);
				 found = 1;
				 printf("请输入新的班级：");
				 scanf("%s", class_new);
				 printf("\n请输入新的姓名：");
				 scanf("%s", name_new);
				 printf("\n请输入新的性别：");
				 scanf("%s", gender_new);
				 printf("\n请输入新的年龄：");
				 scanf("%d", &age_new);
				 printf("\n请输入新的电话：");
				 scanf("%s", telephone_new);
	
				 fprintf(tempFile, "%d %s %s %s %d %s %f %f %f %s %s %s\n", userid, class_new, name_new, gender_new, age_new, telephone_new,
					 math,english, chinese, username, password, roles);
				 printf("信息更新成功！\n");
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
		 printf("未找到ID为 %d 的学生信息！\n", userid);
		 Sleep(2000);
	 }

	 // 关闭文件
	 fclose(file);
	 fclose(tempFile);

	 // 删除原始文件并重命名临时文件
	 remove("Stu_information.txt");
	 rename("temp.txt", "Stu_information.txt");

	 return;
 }