/*
Using your Student:
struct Student *make_students(int count, ...);
Each argument is:
name1, score1, name2, score2, ...
Example:
make_students(2, "Tom", 7.5, "Bob", 9.0);
*/
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>

struct Student{
    char *name;
    float score;
};

struct Student *make_students(int count, ...){
    va_list ap;
    va_start(ap, count);
    struct Student *st = malloc(count * sizeof(struct Student));
    for(int i=0; i<count; i++){
        st[i].name = va_arg(ap, char*);
        st[i].score = va_arg(ap, double);
    }
    return st;
    va_end(ap);
}

int main(void){
    int count = 2;
    struct Student *s = make_students(count, "Tom", 7.5, "Bob", 9.0);
    for(int i=0; i<count;i++){
        fprintf(stdout, "==========================\n");
        fprintf(stdout, "Student %i info:\n", i+1);
        fprintf(stdout, "Name: %s\n", s[i].name);
        fprintf(stdout, "Score: %.2f\n", s[i].score);
    }
    fprintf(stdout, "==========================\n");
    return 0;
}
