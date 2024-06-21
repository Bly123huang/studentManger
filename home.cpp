#include"main.h"

int home()
{
   
    printf("*****************欢迎登录学生管理系统*****************\n");
    printf("1.教师注册\n");
    printf("2.学生注册\n");
    printf("3.登录\n");
    printf("4.退出\n");
    printf("请输入您的选择：");
    int choice;
    scanf_s("%d", &choice);

    switch (choice) {
    case 1:
        registerUser("teacher");
        break;
    case 2:
        registerUser("student");
        break;
    case 3:
        loginUser();
        break;
    case 4:
        printf("Exiting...\n");
        break;
    default:
        printf("无效的选项！\n");
    }
    return 0;
   
}

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
