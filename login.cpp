#include"main.h"
// 定义用户输入的用户名、密码、角色
char usernames[MAX_USERNAME_LEN];
char passwords[MAX_PASSWORD_LEN];
char role1[MAX_ROLE_LEN];
// 定义文件中存储的用户名、密码、角色
int fileUsername[MAX_USERNAME_LEN];
char filePassword[MAX_PASSWORD_LEN];
char fileRole[MAX_ROLE_LEN];
char user_class[50];//获取登陆者班级
int user_now_id;

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

    printf("请输入用户名（id）:  ");
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