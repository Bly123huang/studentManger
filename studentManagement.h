#define STUDENT_INFORMATION_FILE_NAME "studentInformation"
#pragma once
int studentManage();
struct Student {
	char role[10];
	int id;
	char name[50];
	int age;
	char gender[10];
	char telephone[20];
	char email[50];
	char Class[50];  // 学生所属的班级
};

//
typedef struct {
	int id;
	char name[20];
	char classs[50];
	int age;
	char gender[10];
	char telephone[100];
	Score stuScore;
	User user;
}STUDENT_INFOEMATION;
void addStudent_Information(int id, const char* sclass, const char* sname, const char* gender,
	int age, const char* telephone, double smath, double senglish, double schinese, char username[20],
	char password[20], char role[20]);//添加学生信息
void queryStudent_Information(int id);//查询学生信息
void modifyStudent_Information(); //修改学生信息
void deleteStudent_Information(int id);//删除学生信息