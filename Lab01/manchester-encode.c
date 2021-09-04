#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* biphase_l(char*);
char* biphase_s(char*, int);


int main() {
    FILE *fp = fopen("encode-input.txt", "r");
    if (fp==NULL) {
        perror("Cannot open file\n");
        exit(1);
    }

    char line[256];
    int option;
    int count=0;
    char *output;
    
    while (fgets(line, sizeof(line)-1, fp)!=NULL) {
        line[strcspn(line, "\n")] = 0;
        
        if (count%2==0) {
            sscanf(line, "%d", &option);
        } else if (option) {
            output=biphase_s(line, 0);
            printf("%s\n", output);
            free(output);
        } else {
            output=biphase_l(line);
            printf("%s\n", output);
            free(output);
        }
        count++;
    }

    fclose(fp);
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