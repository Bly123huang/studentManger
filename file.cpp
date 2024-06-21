#include"main.h"

// 打开文件并返回文件指针
FILE* open(const char* fileName, const char* mode)
{
	return fopen(fileName, mode);
 
}

// 写入数据到文件
size_t write(FILE* fp, char* data, int size)
{
	if (fp == NULL)
	{
		return -1;
	}

	return fwrite(data, size, 1, fp);
}

// 从文件中读取数据并返回指针
char* read(FILE* fp, long* cnt)
{
	if (fp == NULL)
	{
		return NULL;
	}

	// 移动文件指针到文件末尾以获取文件大小
	fseek(fp, 0, SEEK_END);
	*cnt = ftell(fp);

	// 分配内存以存储文件数据
	char* p = (char*)malloc(*cnt);
	if (!p)
	{
		return NULL;
	}

	// 重新定位文件指针，并读取数据到内存中
	fseek(fp, 0, SEEK_SET);
	fread(p, *cnt, 1, fp);

	return p;
}

// 关闭文件
int close(FILE* fp)
{
	return fclose(fp);
}


//检索id在文件中是否存在
int findid(const char* fp, int id)
{
	// 打开文件，以只读方式读取
	FILE* file = fopen(fp, "r");
	if (file == NULL) {
		printf("Error opening file!\n");
		exit(1);
	}
    int userid;
    userid=id;
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
                found = 1;
            }
        }
    }
    // 如果没有找到目标行，则输出提示信息
    if (!found) {
        system("cls");
        printf("未找到ID为 %d 的信息！\n", userid);
        Sleep(2000);
    }

    // 关闭文件
    fclose(file);
	return found;
}

//打开文件
void openfile(const char* fp, const char* mode)
{
    FILE* file = fopen(fp, mode);
    if (file == NULL)
    {
        printf("Error opening file!\n");
        exit(1);
    }

    return;
}