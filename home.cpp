#include"main.h"

int home()
{
   
    printf("*****************��ӭ��¼ѧ������ϵͳ*****************\n");
    printf("1.��ʦע��\n");
    printf("2.ѧ��ע��\n");
    printf("3.��¼\n");
    printf("4.�˳�\n");
    printf("����������ѡ��");
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
        printf("��Ч��ѡ�\n");
    }
    return 0;
   
}

int function1_home()
{
    int choice;
    do {

        printf("*****************��ӭ����ѧ������ϵͳ*****************\n");
        printf("1. ѧ����Ϣ����\n");
        printf("2. �ɼ�����\n");
        printf("3. ��ʦ����\n");
        printf("4. �༶����\n");
        printf("0. �˳�\n");
        printf("����������ѡ��");
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
                    printf("��û��Ȩ�޽����ʦϵͳ��\n");
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
            printf("��Ч��ѡ����������룡\n");
            goto start;
        }
    }
   while (choice != 6);
    return 0;
}
