#pragma once
#define MAX_USERNAME_LEN 20
#define MAX_PASSWORD_LEN 20
#define MAX_ROLE_LEN 10

// �û��ṹ��
typedef struct {
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
    char role[MAX_ROLE_LEN];
} User;

// ��������
void registerUser(const char* role);
void loginUser();
char* getCurrentUserRole();
char* getCurrentUserClass();
int getCurrentUserId();