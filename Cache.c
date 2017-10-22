#include "Cache.h"

int init(struct Hash *hash){    
    hash->size = 0;
    hash->head = (struct Node *)malloc(sizeof(struct Node *)); 
    if (hash->head == NULL){
        perror("Error create hash!");
        return -1;
    }
    hash->head->before = 0;
    for (int i = 0; i < DEF_BASKETS;++i){
        hash->array[i] = (struct Node *)malloc(sizeof(struct Node*));
        if (hash->array[i] == NULL){
            perror("Error create hash!");
            return -1;
        }
        hash->array[i] = 0;
    }
    return 0;
}

int hashCode(char* word){
    int result = 0;
    int len = strlen(word);
    for (int i = 0; i < len;++i){
        result += word[i]+len;
    }    
    result <<= ((len%10)+1);    
    return result%DEF_BASKETS;
}

int hash_put(struct Hash* hash, char* word, char* description){    
    if (strlen(word) > 128){    
        printf("Word too long. Maximum length is 128.\n");
        return -1;
    }
    if (hash->size == MAX_SIZE){
        int hash_code = hashCode(hash->head->before->word);
        check_basket(hash->array[hash_code]);
        node_remove(hash->head->before);       
        hash->size -= 1;
    }
    int hash_code = hashCode(word);       
    newNode(hash->head,&hash->array[hash_code],word,description);  
    hash->size += 1;
    return 1;
}

int newNode(struct Node* head,struct Node** node,char *word,char *description){    
    int word_len = strlen(word);
    int desc_len = strlen(description);
    struct Node* tmp = malloc(sizeof(struct Node));
    if (tmp == NULL){
        perror("Error create Node!");
        return -1;
    }
    tmp->next = NULL;
    strncpy(tmp->word,word,word_len);
    strncpy(tmp->description,description,desc_len); 
    tmp->a = 1;     
    if (head->before == NULL){         
        tmp->after = head;
        tmp->before = head;
        head->after = tmp;
        head->before = tmp;        
    } else {             
        tmp->after = head->after;
        tmp->before = head;
        head->after->before = tmp;
        head->after = tmp;
    }
    if(*node == NULL){   
        *node = tmp;        
    } else {                
        struct Node *element = *node;        
        *node = tmp;
        tmp = element;
        (*node)->next = tmp;    
    }    
}

int check_basket(struct Node *node){    
    struct Node *element = node;      
    while(element->next && element->next->next){        
        element = element->next;
    }   
    element->next = NULL;    
    return 1;
}

int node_remove(struct Node* node){    
    struct Node *element = node;    
    element->after->before = node->before;
    element->before->after = node->after;   
    free(node);
    return 1;
}

int hash_remove(struct Hash* hash){
    struct Node *tmp = hash->head;
    while(tmp != NULL && tmp->next != NULL){
        struct Node *remove = tmp;
        tmp = tmp->next;
        free(tmp);
    }
    free(hash);
    return 1;
}

int hash_get(struct Hash* hash, char* word){
    int hash_code = hashCode(word);
    struct Node *element = hash->array[hash_code];  
    struct Node *last = NULL; //for NULL next
    struct Node **first_basket = &hash->array[hash_code];   //first element in basket     
    if (element == NULL){
        printf("NOT FOUND!\n");
        return 0;
    }
    while(strcmp(element->word,word) && element->next != NULL){     //while before element->word != word and next != NULL
        last = element;
        element = element->next;
    }    
    if (strcmp(element->word,word)){
        printf("NOT FOUND!\n");
        return 0;
    }
    printf("%s",element->description);
    //remove from list
    element->before->after = element->after;
    element->after->before = element->before;
    //insert element after head
    element->before = hash->head;
    element->after = hash->head->after;
    hash->head->after->before = element;
    hash->head->after = element;
    if (last != NULL){ //change element next in basket, swap array[element_number] and element1
        if (element->next == NULL){            
            last->next = NULL;
        } else {            
            last->next = element->next;
        }
        /*printf("%s\n",(*first_basket)->description);
        printf("%s\n",element->description);
        printf("\n");*/
        struct Node *exc = *first_basket;        
        *first_basket = element;
        element = exc;
        (*first_basket)->next = element;
       /* printf("%s\n",(*first_basket)->description);
        printf("%s\n",element->description);*/        
    }           
    return 1;    
}

int remove_word(struct Hash* hash, char* word){
    int hash_code = hashCode(word);
    struct Node *element = hash->array[hash_code];  
    struct Node *last = NULL; //for NULL next
    struct Node **first_basket = &hash->array[hash_code];   //first element in basket     
    if (element == NULL){
        printf("NOT FOUND!\n");
        return 0;
    }
    while(strcmp(element->word,word) && element->next != NULL){     //while before element->word != word and next != NULL
        last = element;
        element = element->next;
    }    
    if (strcmp(element->word,word)){
        printf("NOT FOUND!\n");
        return 0;
    }
    printf("Deleted!");
    //remove from list
    element->before->after = element->after;
    element->after->before = element->before;
    if (last != NULL){
        if (element->next == NULL){            
            last->next = NULL;
        } else {            
            last->next = element->next;
        }        
    }
    free(element);
    return 1;
}

void show(struct Hash* hash){
    struct Node *tmp = hash->head->after;   
    while(tmp != hash->head){
        printf("%s ",tmp->description);
        tmp = tmp->after;
    }
}