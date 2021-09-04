#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* biphase_l__decode(char*);
char* biphase_s__decode(char*);

int main() {
    FILE *fp = fopen("decode-input.txt", "r");
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
            output=biphase_s__decode(line);
            printf("%s\n", output);
            free(output);
        } else {
            output=biphase_l__decode(line);
            printf("%s\n", output);
            free(output);
        }
        count++;
    }

    fclose(fp);
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