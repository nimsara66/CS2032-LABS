#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* biphase_l(char*);
char* biphase_l__decode(char*);
char* biphase_s(char*, int);
char* biphase_s__decode(char*);

int main() {
    // char input[30]="01001100011";
    char input[30]="1011010100110101010011";
    char* output=biphase_s__decode(input);
    printf("%s\n", input);
    printf("%s\n", output);
    return 0;
}

char* biphase_l(char* input) {
    int bit_size=(int)strlen(input);
    char *output=(char*)malloc((2*bit_size+1)*sizeof(char));
    for (int i = 0; i < bit_size; i++) {
        if (input[i]=='1') {
            output[2*i]='0';
            output[2*i+1]='1';
        } else if (input[i]=='0') {
            output[2*i]='1';
            output[2*i+1]='0';
        }
    }
    
    output[2*bit_size]='\0';
    return output;
}

char* biphase_l__decode(char* input) {
    int bit_size=(int)strlen(input);
    char *output=(char*)malloc((bit_size/2+1)*sizeof(char));
    for (int i = 0; i < bit_size/2; i++) {
        if (input[2*i+1]=='1') {
            output[i]='1';
        } else if (input[2*i+1]=='0') {
            output[i]='0';
        }
    }
    
    output[bit_size/2]='\0';
    return output;
}

char* biphase_s(char* input, int last_bit) {
    int bit_size=(int)strlen(input);
    char *output=(char*)malloc((2*bit_size+1)*sizeof(char));
    for (int i = 0; i < bit_size; i++) {
        if (!last_bit && input[i]=='0') {
            output[2*i]='1';
            output[2*i+1]='0';
        } else if (!last_bit && input[i]=='1') {
            output[2*i]='1';
            output[2*i+1]='1';
            last_bit=1;
        } else if (last_bit && input[i]=='0') {
            output[2*i]='0';
            output[2*i+1]='1';
        } else if (last_bit && input[i]=='1') {
            output[2*i]='0';
            output[2*i+1]='0';
            last_bit=0;
        }
    }
    
    output[2*bit_size]='\0';
    return output;
}

char* biphase_s__decode(char* input) {
    int bit_size=(int)strlen(input);
    char *output=(char*)malloc((bit_size/2+1)*sizeof(char));
    for (int i = 0; i < bit_size/2; i++) {
        if (input[2*i]==input[2*i+1]) {
            output[i]='1';
        } else {
            output[i]='0';
        }
    }
    
    output[bit_size/2]='\0';
    return output;
}