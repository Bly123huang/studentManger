# C语言学生管理系统

## 主要功能模块

## 主界面

#### ![image-20240621095531953](C:\Users\Jie\AppData\Roaming\Typora\typora-user-images\image-20240621095531953.png)

其中教师注册和学生注册使用id（学号注册），由管理员录入id信息，若未查询到id被录入，则无法注册

![image-20240621095820250](C:\Users\Jie\AppData\Roaming\Typora\typora-user-images\image-20240621095820250.png)

![image-20240621095836775](C:\Users\Jie\AppData\Roaming\Typora\typora-user-images\image-20240621095836775.png)

支持修改密码，若已经设置过密码，则验证原来密码后，可以修改密码

![image-20240621100745917](C:\Users\Jie\AppData\Roaming\Typora\typora-user-images\image-20240621100745917.png)



#### 注册函数代码



```c
void registerUser(const char* role) {
    User newUser;
    char adminPassword[MAX_PASSWORD_LEN];
    // 打开文件，以只读方式读取
    FILE* file = fopen("Stu_information.txt", "r");
    if (file == NULL) 
    {
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

printf
    "请输入用户名（id）:  ");
int userid;
scanf("%d",&userid);
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
            if (strcmp(password,"0") != 0&&strcmp(role,"teacher")!=0&&strcmp(password,"(null)")!=0)
            {
                printf("请输入原密码:(未注册默认密码为0) ");
                scanf("%s", newUser.password);
                if (strcmp(newUser.password, password) != 0) 
                {
                    printf("原密码错误！\n");
                    return;
                }   
            }
            found = 1;
            printf("请输入密码: ");
            scanf("%s", newUser.password);
            fprintf(tempFile, "%d %s %s %s %d %s %f %f %f %d %s %s\n", userid, sclass, sname, gender, age, telephone,
                math, english, chinese, userid, newUser.password, role);
            printf("Registration successful! Role: %s\n", role);
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
    system("cls");
    printf("未找到ID为 %d 的%s信息！\n", userid,role);
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
```
#### 登录函数代码

###### 登录成功后进入function1_home()函数    

```c
// 用户登录

void loginUser() {
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
int found = 0;
FILE* file;
printf("Enter username: ");
scanf("%s", usernames);

printf("Enter password: ");
scanf("%s", passwords);

// 打开文件，以读取方式打开
file = fopen("Stu_information.txt", "r");
if (file == NULL) {
  Log(cErr,"Error opening file!\n")
    exit(1);
}

// 逐行读取文件，比较用户名、密码和角色
while (fscanf(file, "%d %s %s %s %d %s %f %f %f %s %s %s", &sid, sclass, sname, gender, &age, telephone, &math, &english, &chinese, username, password, roles) != EOF) {
    if (strcmp(usernames, username) == 0 && strcmp(passwords, password) == 0) {
        found = 1;
        strcpy(role1, roles);
        strcpy(user_class, sclass);
        user_now_id = sid;
        break;
    }
}

fclose(file);

if (found) {
    printf("登录成功！你的角色是: %s\n", role1);
    Sleep(1000);
    system("cls");
    function1_home();//登陆后页面函数
    system("pause");
}
else {
    printf("无效的用户名或密码！\n");
}
return;
}
```
#### 后面需要用到的返回登录用户ID,角色，班级的函数



```c
//获取当前登录用户角色
char* getCurrentUserRole() {
    char* currentRole = (char*)malloc(MAX_ROLE_LEN * sizeof(char));
    if (currentRole == NULL) {
        // 处理内存分配失败的情况
        // 返回 NULL 或者其他错误处理方式
        Log(cErr,"Memory allocation failed!\n")
    }
    strcpy(currentRole, role1);
    return currentRole;
}

//获取当前登录用户班级
char* getCurrentUserClass() {
    char* currentClass = (char*)malloc(MAX_ROLE_LEN * sizeof(char));
    if (currentClass == NULL) {
        // 处理内存分配失败的情况
        // 返回 NULL 或者其他错误处理方式
        Log(cErr,"Memory allocation failed!\n")
    }
    strcpy(currentClass, user_class);
    return currentClass;
}

//获取当前登录用户id
int getCurrentUserId()
{
    return user_now_id;
}
```









## 登录后主菜单

![image-20240621101533660](C:\Users\Jie\AppData\Roaming\Typora\typora-user-images\image-20240621101533660.png)





```c
   
int function1_home()
{
    int choice;
    do {
    printf("*****************欢迎进入学生管理系统*****************\n");
    printf("1. 学生信息管理\n");
    printf("2. 成绩管理\n");
    printf("3. 教师管理\n");
    printf("4. 班级管理\n");
    printf("0. 退出\n");
    printf("请输入您的选择：");
    int start = 0;
    start:
    scanf_s("%d", &choice);
    switch (choice) {
    case 1:
        studentManage();
        break;
    case 2:
        scoreManage();
        break;
        case 3:
        {
            char* currentRole = getCurrentUserRole();
            if (currentRole == NULL)
            {
                Log(cErr, "getCurrentUserRole() failed");
            }
            if (strcmp(currentRole, "student") == 0)
            {
                printf("你没有权限进入教师系统！\n");
                system("pause");
                break;
            }
            teacherManage();
            break;
        }  
        case 4:
            classManage();
            break;
        case 0:
            printf("Exiting...\n");
            exit(0);
            break;
    default:
        printf("无效的选项！请重新输入！\n");
        goto start;
    }
}
   while (choice != 6);
    return 0;
}
```
## 学生信息管理页面

这里面是对学生信息的增删改查，其中对不同的角色给予了不同的权限。

admin管理员的权限最高，老师其次，学生只能查询信息和修改信息，而且只能查询和修改本人的信息。

里面的权限就是根据前面的登录那块给的几个函数。

![image-20240621104913970](C:\Users\Jie\AppData\Roaming\Typora\typora-user-images\image-20240621104913970.png)

#### 学生信息管理主页面代码

```c
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
```
#### 添加学生信息代码

```c
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

```



#### 删除学生信息代码

```c
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

```



#### 修改学生信息代码

```c
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
```



#### 查找学生信息代码

```c
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
```

在查询信息中，管理员会显示用户账号密码，其他用户则不会显示

![image-20240621110526194](C:\Users\Jie\AppData\Roaming\Typora\typora-user-images\image-20240621110526194.png)

## 成绩信息管理

![image-20240621110629505](C:\Users\Jie\AppData\Roaming\Typora\typora-user-images\image-20240621110629505.png)

其中，录入学生信息、修改学生成绩只能由老师和管理员录入

学生进入会显示没权限

![image-20240621110844947](C:\Users\Jie\AppData\Roaming\Typora\typora-user-images\image-20240621110844947.png)

查询学生成绩，若登录身份为学生，则只能查看本人成绩

![image-20240621111010419](C:\Users\Jie\AppData\Roaming\Typora\typora-user-images\image-20240621111010419.png)

总分排名分为学校排名和班级排名，班级会通过登录时获取的班级信息，读取相印的班级的排名

![image-20240621111143195](C:\Users\Jie\AppData\Roaming\Typora\typora-user-images\image-20240621111143195.png)



### 上代码

#### 成绩管理主页面

```c
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
```



#### 录入成绩

```c
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
```



#### 查询成绩

```c
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

```



#### 修改成绩

```c
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
```





#### 计算并打印平均成绩

```c
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
```





#### 成绩排名函数

这里采用，生成一个新的结构体，存储不同班级的学生信息，再分别排序

```c
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
```



### 教师管理

教师信息文件和学生信息文件按分开了

#### 主页面

![image-20240621111857362](C:\Users\Jie\AppData\Roaming\Typora\typora-user-images\image-20240621111857362.png)

![image-20240621112209354](C:\Users\Jie\AppData\Roaming\Typora\typora-user-images\image-20240621112209354.png)

新建教师录入教师，删除教师都只能管理员进入,学生直接不能进入主界面



#### 主页面代码

```c
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
```



#### 新建教师信息

```c
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
```



#### 录入教师信息

如果要录入教师名没有在文件中检索到，会禁止录入

```
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
```



#### 查询教师信息

```
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
```



#### 修改教师信息

```c

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
```



#### 删除教师信息

```c
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
```



### 班级管理

班级管理我只写了一个查看班级成员信息的功能

![image-20240621114114606](C:\Users\Jie\AppData\Roaming\Typora\typora-user-images\image-20240621114114606.png)

也是会通过获取登录教师账号的班级，会得到相印班级成员的信息

#### 页面主代码

```c
void classManage()
{
	int choice;
	do 
	{
		int start = 0;
	start:
		system("cls");
		printf("\n欢迎进入班级管理\n");
		printf("1. 班级成员信息查询\n");
	
		printf("0.  Exit\n");
		printf("请输入你的选择: ");
		scanf_s("%d", &choice);
		char* currentRole = getCurrentUserRole();
		char* currentClass = getCurrentUserClass();
		switch (choice)
		{
			
		case 1:
		{
			// 检查是否是教师
			if (strcmp(currentRole, "student") == 0)
			{
				printf("学生用户，无权访问此功能！\n");
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
			printf("输入错误，请重新输入！\n");
		while (choice >1 && choice < 1)
		{
			goto start;
			break;
		}
		}
	}
	while (choice!= 5);
}
```



#### 班级成员信息查询代码

```c
//班级成员信息查询
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
	printf("%-6s %-10s %-10s %-6s %-10s\n", "学号", "姓名", "性别", "年龄", "电话");
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
		// 假设文件格式为：学号 班级 姓名 性别 年龄 电话 数学 英语 语文 用户名 密码 角色
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
```



学习c语言第一个小项目！



