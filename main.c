/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: dmitriy
 *
 * Created on September 29, 2017, 6:32 PM
 */
#include "Files.h"

int main(int argc, char** argv) {
    char *fileName = "test.txt";
    char command;
    char *tempWord = malloc(128);
    char *tempDesc = malloc(900);
    if (tempWord == NULL || tempDesc == NULL){
        perror("Can't allocate memory");
        return -1;
    }
    struct Hash *cache = (struct Hash *)malloc(sizeof(struct Hash));
    if (cache == NULL){
        perror("Error create cache!");
        return -1;
    }
    init(cache);    
    if (argc > 1){
        read_file(argv[1], cache);
    } else {
        read_file(fileName, cache);
    }    
    do {
        printf("\n1. %s\n2. %s\n3. %s\n4. %s\n",
        "Search word.", "Add word.", "Delete word.","Exit");
        command = getchar();
        while (getchar() != '\n');        
        switch (command){
            case '1': scanf("%s",tempWord);
                while (getchar() != '\n'); 
                hash_get(cache,tempWord);                
                break;
            case '2': 
                scanf("%s",tempWord);  
                while (getchar() != '\n'); 
                scanf("%s",tempDesc); 
                while (getchar() != '\n');
                strcat(tempDesc, "\n");
                hash_put(cache,tempWord,tempDesc);                
                break;
            case '3': 
                scanf(" %s",tempWord);  
                while (getchar() != '\n');
                remove_word(cache,tempWord);
                break;
            case '4':
                break;
            default: 
                printf("No such command");
        }
    } while(command != '4');
    //show(cache);
    if (argc > 1){
        write_file(argv[1], cache);
    } else {
        write_file(fileName, cache);
    }    
    hash_remove(cache);
    return (EXIT_SUCCESS);
}

