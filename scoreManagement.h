#pragma once
int scoreManage();
//���ѧ���ɼ�
void addStudentScore();
//��ѯѧ���ɼ�������ѧ�ţ�
void queryStudent(int id);
//�޸�ѧ���ɼ�������ѧ�ţ�
void modifyStudent();
//����ƽ���ɼ�
void printAverageScore();
//����ɼ�����
void rankScores();
typedef struct {
	int id;
	char name[20];
	double chinese;
	double math;
	double english;
} Score;