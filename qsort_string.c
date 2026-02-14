/*
Sort words alphabetically
User enters several words (each stored as a string).
Tasks:
Store them in a 2D char array OR array of char*
Sort alphabetically (A → Z)
Then reverse (Z → A)
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp_as(const void* a, const void* b){
    char** ptr1 = (char**) a;
    char** ptr2 = (char**) b;
    return strcmp(*ptr1, *ptr2);
}

int cmp_des(const void* a, const void* b){
    char** ptr1 = (char**) a;
    char** ptr2 = (char**) b;
    return strcmp(*ptr2, *ptr1);
}

int main(void){

    int num_word;
    fprintf(stdout, "Enter the number of words: ");
    fscanf(stdin, "%i", &num_word);
    if(num_word <= 0) return 1;
    getchar(); // the leftover '\n' from fscanf().
    char words[100]; // length of a word.
    char** ptr = malloc(num_word * sizeof(char*)); // or sizeof(*ptr).
    if(ptr == NULL) return 1;
    for(int i = 0; i < num_word; i++){
        fgets(words, sizeof(words), stdin);
        ptr[i] = strdup(words);
    }
    fprintf(stdout, "============================================\n");
    fprintf(stdout, "Ascending sort order:\n");
    qsort(ptr, num_word, sizeof(char*), cmp_as); // we can replace sizeof(char*) with sizeof(*ptr).
    for(int i = 0; i < num_word; i++) fprintf(stdout, "%s", ptr[i]);
    fprintf(stdout, "============================================\n");
    fprintf(stdout, "Descending sort order:\n");
    qsort(ptr, num_word, sizeof(char*), cmp_des);
    for(int i = 0; i < num_word; i++) fprintf(stdout, "%s", ptr[i]);
    // free after allocation.
    for(int i = 0; i < num_word; i++) free(ptr[i]);
    free(ptr);
    fprintf(stdout, "============================================\n");
    return 0;
}
