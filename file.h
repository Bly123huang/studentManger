#pragma once
FILE* open(const char* fileName, const char* mode);
char* read(FILE* fp, long* cnt);
size_t write(FILE* fp, char* data, int size);
int close(FILE* fp);
int findid(const char* fp,int id);
void openfile(const char* fp, const char* mode);