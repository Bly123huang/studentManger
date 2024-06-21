#pragma once
int scoreManage();
//添加学生成绩
void addStudentScore();
//查询学生成绩（根据学号）
void queryStudent(int id);
//修改学生成绩（根据学号）
void modifyStudent();
//计算平均成绩
void printAverageScore();
//计算成绩排名
void rankScores();
typedef struct {
	int id;
	char name[20];
	double chinese;
	double math;
	double english;
} Score;