/*String Concatenation*/
#include <stdio.h>

//return the length of a string
int strleng(char *s){
    int i = 0;
    for(;*s++ != '\0';i++);
    return i;
}

//string concatenation
void strcatt(char *s, char *t, char *sum){
    char *ptr = sum;
    for(;*s != '\0';*ptr++ = *s++);
    for(;*t != '\0';*ptr++ = *t++);
    *ptr = '\0';
}

int main(void){
    //testing with 2 strings. mess1 + mess2 = sum
    char mess1[10] = "abcdefghi";
    char mess2[10] = "kjlmnopqx";
    int tl = strleng(mess1) + strleng(mess2) + 1;
    char sum[tl];
    strcatt(mess1, mess2, sum);
    char *p = sum;
    while(*p != '\0'){
        printf("%c", *p++);
    }
    printf("\n");
    return 0;
}
