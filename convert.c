#include <stdio.h>
#include <string.h>
/*Converting signed or unsigned decimal number to its binary and hexdecimal forms, by Colonel Bee*/
/*For octal conversion, the code is the same idea as hexadecimal conversion*/

/*number of bits needed to represent both signed and unsigned version of an integer*/
int bit_needed(int num){
    if(num < 0) num = -num;                        
    int i = 1;
    int j, k;
    for(j = 0; (k = i << j) <= num; j++);
    return ++j;
}

/*reverse string (I should've used the built-in reverse function:))*/
void rv_str(char st[]){
    int i, j, tmp;
    for(i = 0, j = strlen(st) - 1; i < j; i++, j--){
        tmp = st[i];
        st[i] = st[j];
        st[j] = tmp;
    }
}

/*finding 2's complement to represent negative decimal*/
void two_comp(char comp[]){
    int x, y;
    int ln = strlen(comp);
    /*1's complement*/
    for(x = 0; x < ln; x++){
        if(comp[x] == '0'){
            comp[x] = '1';
            continue;
        }
        if(comp[x] == '1'){
            comp[x] = '0';
            continue;
        }
    }
    /*adding 1 to 1's complement --> 2's complement*/
    if(comp[ln - 1] == '0') comp[ln - 1] = '1';
    else{
        comp[ln - 1] = '0';
        for(y = ln - 2; y > 0; y--){
            if(comp[y] == '0'){
                comp[y] = '1';
                break;
            }
            else{
                comp[y] = '0';
            }
        }
    }  
    
}

/*converting positive decimal to binary*/
void bin_change(int dec, char bin[]){
    int i = 0;
    int fl = bit_needed(dec); 
    while(fl > 0){ /*loop through the number of bits needed*/
        bin[i++] = (dec % 2) + '0';  
        dec /= 2;        
        --fl;
    }
    bin[i] = '\0';
    rv_str(bin);
}

/*converting any decimal to binary*/
void dec_to_bin(int dec, char a[]){
    if(dec <= 0){
        dec *= (-1);
        bin_change(dec, a); /*fisrt convert from positive dec to bin*/
        two_comp(a);        /*then use the 2's complement*/
    }
    else bin_change(dec, a);
    for(int i = 0; i < strlen(a); i++){
        printf("%c", a[i]);
    }
    printf("\n");
}

/*converting positive decimal to hexadecimal*/
void hex_change(int dec, char hex[]){
    int i = 0;
    int fh = bit_needed(dec)/4 + 1; 
    while(fh > 0){ /*loop through the number of bits needed*/
        hex[i] = (dec % 16) + '0';
        /*change to ASCII symbol*/
        if(hex[i] >= 10 + '0' && hex[i] <= 15 + '0') hex[i] = (hex[i] - '0' - 10) + 'A';
        dec /= 16;        
        --fh; ++i;
    }
    hex[i] = '\0';
    rv_str(hex);
}

/*2's complement of hexadecimal = subtract each number by 15 first then add 1*/
void two_hex(char th[]){
    /*taking the 1's complement first*/
    for(int k = 0; k < strlen(th); k++){
        /*represent characters with numbers*/
        if(th[k] >= '0' && th[k] <= '9') th[k] -= '0';
        /*represent A, B, C, D, E, and F with numbers*/
        if(th[k] >= 'A' && th[k] <= 'F') th[k] -= 55;
        th[k] = 15 - th[k]; /*subtract each number by 15 first*/
    }
    /*change back to ASCII symbols*/
    for(int k = 0; k < strlen(th); k++){
        if(th[k] >= 0 && th[k] <= 9) th[k] += '0';
        if(th[k] >= 10 && th[k] <= 15) th[k] += 55;
    }
    /*then add 1 --> 2's complement*/
    int last_index = strlen(th) - 1;
    if((th[last_index] >= '0' && th[last_index] <= '8') || (th[last_index] >= 'A' && th[last_index] <= 'E')){
        th[last_index] += 1;
    }
    else if(th[last_index] == '9') th[last_index] = 'A';
    else if(th[last_index] == 'F'){
        th[last_index] = '0';
        for(int l = last_index - 2; l >= 0; l--){
            if(th[l] == 'F') th[l] = '0';
            else if(th[l] == '9'){
                th[l] = 'A';
                break;
            }
            else if((th[l] >= '0' && th[l] <= '8')|| (th[l] >= 'A' && th[l] <= 'E')){
                ++th[l];
                break;
            }
        }
    }
    for(int k = 0; k < strlen(th); k++){
        printf("%c", th[k]);
    }
}

/*converting any decimal to hexadecimal*/
void dec_to_hex(int dec, char b[]){
    if(dec >= 0){
        hex_change(dec, b);
        for(int i = 0; i < strlen(b); i++){
            printf("%c", b[i]);
        }
    }
    else{
        dec *= (-1);
        hex_change(dec, b);
        printf("F"); /*for sign representation*/
        two_hex(b);
    }
    printf("\n");
}

int main(){
    int n = 1000; /*any decimal number*/
    char arr_bin[bit_needed(n) + 1];
    char arr_hex[bit_needed(n)/4 + 1];
    printf("The binary form of %d is ", n);
    dec_to_bin(n, arr_bin);
    printf("The hexadecimal form of %d is ", n);
    dec_to_hex(n, arr_hex);
    return 0;
}