#include"main.h"
// �����û�������û��������롢��ɫ
char usernames[MAX_USERNAME_LEN];
char passwords[MAX_PASSWORD_LEN];
char role1[MAX_ROLE_LEN];
// �����ļ��д洢���û��������롢��ɫ
int fileUsername[MAX_USERNAME_LEN];
char filePassword[MAX_PASSWORD_LEN];
char fileRole[MAX_ROLE_LEN];
char user_class[50];//��ȡ��½�߰༶
int user_now_id;

void registerUser(const char* role) {
    User newUser;
    char adminPassword[MAX_PASSWORD_LEN];
    // ���ļ�����ֻ����ʽ��ȡ
    FILE* file = fopen("Stu_information.txt", "r");
    if (file == NULL) 
    {
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

    printf("�������û�����id��:  ");
    int userid;
    scanf("%d",&userid);
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
                if (strcmp(password,"0") != 0&&strcmp(role,"teacher")!=0&&strcmp(password,"(null)")!=0)
                {
                    printf("������ԭ����:(δע��Ĭ������Ϊ0) ");
                    scanf("%s", newUser.password);
                    if (strcmp(newUser.password, password) != 0) 
                    {
                        printf("ԭ�������\n");
                        return;
                    }   
                }
                found = 1;
                printf("����������: ");
                scanf("%s", newUser.password);
                fprintf(tempFile, "%d %s %s %s %d %s %f %f %f %d %s %s\n", userid, sclass, sname, gender, age, telephone,
                    math, english, chinese, userid, newUser.password, role);
                printf("Registration successful! Role: %s\n", role);
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
        system("cls");
        printf("δ�ҵ�IDΪ %d ��%s��Ϣ��\n", userid,role);
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


// �û���¼

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
    // �����ļ���ʽΪ��ѧ�� �༶ ���� �Ա� ���� �绰 ��ѧ Ӣ�� ���� �û��� ���� ��ɫ
    

    int found = 0;
    FILE* file;
    printf("Enter username: ");
    scanf("%s", usernames);
    
    printf("Enter password: ");
    scanf("%s", passwords);

    // ���ļ����Զ�ȡ��ʽ��
    file = fopen("Stu_information.txt", "r");
    if (file == NULL) {
      Log(cErr,"Error opening file!\n")
        exit(1);
    }

    // ���ж�ȡ�ļ����Ƚ��û���������ͽ�ɫ
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
        printf("��¼�ɹ�����Ľ�ɫ��: %s\n", role1);
        Sleep(1000);
        system("cls");
        function1_home();//��½��ҳ�溯��
        system("pause");
    }
    else {
        printf("��Ч���û��������룡\n");
    }
    return;
}

//��ȡ��ǰ��¼�û���ɫ
char* getCurrentUserRole() {
    char* currentRole = (char*)malloc(MAX_ROLE_LEN * sizeof(char));
    if (currentRole == NULL) {
        // �����ڴ����ʧ�ܵ����
        // ���� NULL ��������������ʽ
        Log(cErr,"Memory allocation failed!\n")
    }
    strcpy(currentRole, role1);
    return currentRole;
}

//��ȡ��ǰ��¼�û��༶
char* getCurrentUserClass() {
    char* currentClass = (char*)malloc(MAX_ROLE_LEN * sizeof(char));
    if (currentClass == NULL) {
        // �����ڴ����ʧ�ܵ����
        // ���� NULL ��������������ʽ
        Log(cErr,"Memory allocation failed!\n")
    }
    strcpy(currentClass, user_class);
    return currentClass;
}

//��ȡ��ǰ��¼�û�id
int getCurrentUserId()
{
    return user_now_id;
}