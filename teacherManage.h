#pragma once

void teacherManage();
void inputTeacher();
void queryTeacher(char name[10]);
void deleteTeacher(const char* name);
void modifyTeacher(const char* name);
void createTeacher();
struct TEACHER
{
    char name[50];
    char subject[50];
    char gender[10];
    int age;
    char address[100];
    char phone[50];
};