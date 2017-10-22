#include "Files.h"

int read_file(char *fname, struct Hash *hash){
    char *tempWord = malloc(128);
    char *tempDesc = malloc(900);
    if (tempWord == NULL || tempDesc == NULL){
        perror("Can't allocate memory");
        return -1;
    }
    FILE *desc = fopen(fname,"r");
    if (desc == NULL){
        perror("Can't open file");
        exit(-1);
    }
    while (1){
        if (fscanf(desc, "%s", tempWord) != 1){            
            return 1;        // file finished or there was an error
        }
        //printf("%s\n",tempWord);
        fseek (desc, 1, SEEK_CUR);
        if (!fgets(tempDesc, 900, desc)){
            perror("Reading error");
            break;        // file finished or there was an error
        }
        //printf("%s", tempDesc);
        hash_put(hash,tempWord,tempDesc);
    }
    fclose(desc);
    free(tempWord);
    free(tempDesc);
    return 1;
}

int write_file(char *fname, struct Hash* hash){
    FILE *f = fopen(fname, "w+");
    if (f == NULL){
        printf("Error opening file!\n");
        exit(1);
    }
    struct Node *tmp = hash->head->after;    
    while (tmp != hash->head){
        fprintf(f, "%s ", tmp->word);
        fprintf(f, "%s", tmp->description);
        tmp = tmp->after;
    }
    fclose(f);
    return 1;
}
