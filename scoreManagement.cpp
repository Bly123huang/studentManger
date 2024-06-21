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
		printf("\n欢迎进入成绩信息管理\n");
		printf("1. 录入学生成绩\n");
		printf("2. 查询学生成绩\n");
		printf("3. 修改学生成绩\n");
		printf("4. 计算平均成绩\n");
		printf("5. 总分排名\n");
		printf("6. Exit\n");
		printf("请输入你的选择: ");
		int start;
		start:
		scanf_s("%d", &choice);

		switch (choice) {
		case 1:
		{
			if (strcmp(currentRole, "student") == 0)
			{
				printf("你没有权限新增学生成绩！\n");
				Sleep(3000);
				break;
			}
			addStudentScore();
				break;
		}
		case 2:
		{
			printf("请输入学号: ");
			int id;
			scanf_s("%d", &id);
			int cur_id=getCurrentUserId();
			if (strcmp(currentRole, "student") == 0 && cur_id != id)
			{
				printf("你没有权限查询其他人的学生成绩！\n");
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
				printf("你没有权限修改学生成绩！\n");
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


//录入学生成绩
Score studentScore;
void addStudentScore()
{

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

	int id=0;
	float chinese=0; 
	float math=0;
	float english=0;

	// 创建一个 Score 结构体变量，并将参数值保存到结构体中
	studentScore.id = id;
	studentScore.chinese = chinese;
	studentScore.math = math;
	studentScore.english = english;

	// 在这里可以将学生成绩保存到文件或者数据库中，或者进行其他操作
	 // 打开文件，以追加方式写入


	printf("请输入用户名（id）:  ");
	int userid;
	scanf("%d", &userid);
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
	
	if (sscanf(line, "%d %s %s %s %d %s %f %f %f %s %s %s", &sid, sclass, sname, gender, &age, telephone, &math, &english, &chinese, username, password, roles) != EOF)
	{

		if (sid == userid)
		{
			found = 1;
			printf("请输入数学成绩: ");
			scanf("%lf", &studentScore.math);
			printf("请输入英语成绩: ");
			scanf("%lf", &studentScore.english);
			printf("请输入语文成绩: ");
			scanf("%lf", &studentScore.chinese);
			// 将新的成绩写入到临时文件中
			fprintf(tempFile, "%d %s %s %s %d %s %f %f %f %s %s %s\n", userid, sclass, sname, gender, age, telephone, studentScore.math, studentScore.english, studentScore.chinese, username,password, roles);
			printf("成绩录入成功！\n");
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

//查询学生成绩
void queryStudent(int id)
{
	// 打开文件，以只读方式读取
	FILE* file = fopen("Stu_information.txt", "r");
	if (file == NULL) {
		printf("Error opening file!\n");
		exit(1);
	}
	// 读取文件内容，并打印到屏幕上
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
		// 假设文件格式为：学号 班级 姓名 性别 年龄 电话 数学 英语 语文 用户名 密码 角色
		if (sscanf(line, "%d %s %s %s %d %s %f %f %f %s %s %s", &sid, sclass, sname, gender, &age, telephone, &math, &english, &chinese, username, password, roles) != EOF)
		{

			if (sid == id)
			{
				int found = 1;
				printf("学号: %d\n", sid);
				printf("姓名: %s\n", sname);
				printf("语文: %.2f\n", chinese);
				printf("数学: %.2f\n", math);
				printf("英语: %.2f\n", english);
				Sleep(2000);
			}
		}
	}
	fclose(file);
	system("pause");
	return;
}

//修改学生成绩
void modifyStudent()
{

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
	//int id = 0;
	float chinese = 0;
	float math = 0;
	float english = 0;

	// 创建一个 Score 结构体变量，并将参数值保存到结构体中
	//studentScore.id = id;
	studentScore.chinese = chinese;
	studentScore.math = math;
	studentScore.english = english;

	// 在这里可以将学生成绩保存到文件或者数据库中，或者进行其他操作
	 // 打开文件，以追加方式写入


	printf("请输入用户名（id）:  ");
	int userid;
	scanf("%d", &userid);
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

		if (sscanf(line, "%d %s %s %s %d %s %f %f %f %s %s %s", &sid, sclass, sname, gender, &age, telephone, &math, &english, &chinese, username, password, roles) != EOF)
		{

			if (sid == userid)
			{
				printf("用户ID：%d\n", userid);
				printf("姓名：%s\n", sname);
				printf("语文：%.2f\n", chinese);
				printf("数学：%.2f\n", math);
				printf("英语：%.2f\n", english);
				found = 1;
				printf("请输入新的数学成绩: ");
				scanf("%lf", &studentScore.math);
				printf("请输入新的英语成绩: ");
				scanf("%lf", &studentScore.english);
				printf("请输入新的语文成绩: ");
				scanf("%lf", &studentScore.chinese);
				// 将新的成绩写入到临时文件中
				fprintf(tempFile, "%d %s %s %s %d %s %f %f %f %s %s %s\n", userid, sclass, sname, gender, age, telephone, studentScore.math, studentScore.english, studentScore.chinese, username, password, roles);
				printf("成绩录入成功！\n");
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

// 计算并打印平均成绩函数
void printAverageScore()
{
	FILE* file = fopen("Stu_information.txt", "r"); // 打开文件
	if (file == NULL) {
		printf("Error opening file!\n"); // 输出错误信息
		exit(1); // 退出程序
	}
	float sumChinese = 0.0; // 初始化语文总成绩
	float sumMath = 0.0; // 初始化数学总成绩
	float sumEnglish = 0.0; // 初始化英语总成绩

	float sumChinese_class = 0.0; // 初始化语文总成绩
	float sumMath_class = 0.0; // 初始化数学总成绩
	float sumEnglish_class = 0.0; // 初始化英语总成绩

	int count_class = 0; // 初始化班级学生数量
	int count_school = 0; // 初始化学校学生数量
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
	fclose(file); // 关闭文件
	if (count_school == 0) {
		printf("没有任何学生的成绩！\n"); // 输出无学生成绩信息
	}
	else {
		float averageChinese = sumChinese / count_school; // 计算语文平均成绩
		float averageMath = sumMath / count_school; // 计算数学平均成绩
		float averageEnglish = sumEnglish / count_school; // 计算英语平均成绩

		printf("全校平均成绩：");
		printf("平均语文成绩: %.2f ", averageChinese); // 输出语文平均成绩
		printf("平均数学成绩: %.2f ", averageMath); // 输出数学平均成绩
		printf("平均英语成绩: %.2f ", averageEnglish); // 输出英语平均成绩


	}
	if (count_class == 0) {
		printf("没有任何班级的学生的成绩！\n"); // 输出无班级学生信息
	}
	else {
		float averageChinese_class = sumChinese_class / count_class; // 计算语文平均成绩
		float averageMath_class = sumMath_class / count_class; // 计算数学平均成绩
		float averageEnglish_class = sumEnglish_class / count_class; // 计算英语平均成绩

		printf("\n班级平均成绩：");
		printf("平均语文成绩: %.2f ", averageChinese_class); // 输出语文平均成绩
		printf("平均数学成绩: %.2f ", averageMath_class); // 输出数学平均成绩
		printf("平均英语成绩: %.2f \n", averageEnglish_class); // 输出英语平均成绩
	}
	system("pause"); // 暂停程序以查看输出
	fclose(file);
	return; // 返回
}

// 成绩排名函数
void rankScores()
{
	FILE* file = fopen("Stu_information.txt", "r");
	if (file == NULL) {
		printf("Error opening file!\n");
		exit(1);
	}

	// 定义一个结构体数组来存储学生的信息
	struct Score {
		int id;
		char name[20];
		float chinese;
		float math;
		float english;
	} scores[100]; // 假设最多有 100 个学生

	int count = 0; // 学生数量


	// 定义一个结构体数组来存储班级学生的信息
	struct Score_class {
		int id;
		char name[20];
		float chinese;
		float math;
		float english;
	} scores_class[100]; // 假设最多有 100 个学生

	int countclass = 0; // 学生数量
	// 读取文件内容，并将学生信息保存到结构体数组中
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
		// 假设文件格式为：学号 班级 姓名 性别 年龄 电话 数学 英语 语文 用户名 密码 角色
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

	// 根据总分进行排名
	for (int i = 0; i < count - 1; i++)
	{
		for (int j = 0; j < count - i - 1; j++) 
		{
			float total1 = scores[j].chinese + scores[j].math + scores[j].english;
			float total2 = scores[j + 1].chinese + scores[j + 1].math + scores[j + 1].english;
			if (total1 < total2) 
			{
				// 交换两个学生的信息
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
				// 交换两个学生的信息
				struct Score_class temp = scores_class[j];
				scores_class[j] = scores_class[j + 1];
				scores_class[j + 1] = temp;
			}
		}
	}
	system("cls"); // 清屏
	// 打印学校排名结果
	printf("学校排名\t%-10s\t%-8s\t%-6s\t%-6s\t%-6s\t%-6s\n", "学号", "姓名", "语文", "数学", "英语", "总分");

	for (int i = 0; i < count; i++) {
		float total = scores[i].chinese + scores[i].math + scores[i].english;
		printf("%-10d\t%-10d\t%-8s\t%-6.2f\t%-6.2f\t%-6.2f\t%-6.2f\n", i + 1, scores[i].id, scores[i].name, scores[i].chinese, scores[i].math, scores[i].english, total);
	}

	printf("\n");

	// 打印班级排名结果
	printf("班级排名\t%-10s\t%-8s\t%-6s\t%-6s\t%-6s\t%-6s\n", "学号", "姓名", "语文", "数学", "英语", "总分");

	for (int i = 0; i < countclass; i++) {
		float total_class = scores_class[i].chinese + scores_class[i].math + scores_class[i].english;
		printf("%-10d\t%-8d\t%-8s\t%-6.2f\t%-6.2f\t%-6.2f\t%-6.2f\n", i + 1, scores_class[i].id, scores_class[i].name, scores_class[i].chinese, scores_class[i].math, scores_class[i].english, total_class);
	}

	system("pause");
	return;
}

