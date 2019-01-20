#include "dict.h"
#include <string.h>

#define END 1
#define RESIZE_FACTOR 8
#define RESIZE_THRESHOLD 10

void hash_init(dict* d);
int getHash(char* v, int mod);
void resizeHash(dict** d, int oldSize, int newSize);
void collision_insert(node** head, char* key, mydataType value);
node* node_init(char* key, mydataType value);
bool ifResize(node* n);
void node_free(node* n);
mydataType getValueByKey(dict* d, char* key);

dict* dictInit(void) {
    dict* d;
    d = (dict*) malloc(sizeof(dict));
    if(d == NULL){
        fprintf(stderr, "hash table created failed\n");
        exit(1);
    }
    hash_init(d);
    return d;
}

void hash_init(dict* d){
    int i;
    d->arr = (node**) malloc(hashLength*sizeof(node*));
    if(d->arr == NULL){
        fprintf(stderr, "hash table created failed\n");
        exit(1);
    }
    for (i = 0; i < hashLength; i++) {
        *(d->arr+i) = NULL;
    }
    d->size = hashLength;
}

void dictInsert(dict* d, char* key, mydataType value){
    int hashValue;
    if (key == NULL) {
        fprintf(stderr, "Cannot insert a null value\n");
        exit(1);
    }
    hashValue = getHash(key, d->size);
    if (*(d->arr + hashValue) != NULL) {
        collision_insert(&(*(d->arr + hashValue)), key, value);
        if (ifResize(*(d->arr + hashValue))) {
            resizeHash(&d, d->size, RESIZE_FACTOR*d->size);
            d->size = RESIZE_FACTOR*d->size;
        }
    }else{
        *(d->arr + hashValue) = node_init(key, value);
    }
}

bool ifResize(node* n){
    int i = 0;
    while(n != NULL){
        n = n->next;
        i++;
    }
    if (i >= RESIZE_THRESHOLD) {
        return TRUE;
    }
    return FALSE;
}

void collision_insert(node** head, char* key, mydataType value){
    node* h = *head;
    node* n = node_init(key, value);
    while (h ->next != NULL) {
        h = h->next;
    }
    h->next = n;
    h = NULL;
}

int getHash(char* v, int mod){
    int seed = 131;
    int hash = 0;
    if (v == NULL) {
        fprintf(stderr, "cannot calculate null hash\n");
    }
    while(*v){
        hash = (hash * seed + (*v++)) % mod;
    }
    return hash;
}

node* node_init(char* key, mydataType value){
    node* n;
    int keyLength = strlen(key) + END;
    n = (node*) malloc(sizeof(node));
    if (n == NULL) {
        fprintf(stderr, "Cannot allocate enough memory\n");
        exit(1);
    }
    n->key = (char*) malloc(keyLength*sizeof(char));
    if (n->key == NULL) {
        fprintf(stderr, "Cannot allocate enough memory\n");
        exit(1);
    }
    strcpy(n->key, key);
    n->value = value;
    n->next = NULL;
    return n;
}

void resizeHash(dict** d, int oldSize, int newSize){
    node** newHashArray;
    int i, newHashValue;
    node* head;
    newHashArray = (node**) malloc(newSize*sizeof(node*));
    if(newHashArray == NULL){
        fprintf(stderr, "New hash table create failed...\n");
        exit(1);
    }
    for(i = 0; i < newSize; i++){
        newHashArray[i] = NULL;
    }
    for(i = 0; i < oldSize; i++){
        /* If there is at least one node in the cell */
        if((*d)->arr[i] != NULL){
            /* head node */
            head = *((*d)->arr + i);
            /* recurrent insert */
            while(head != NULL){
                newHashValue = getHash(head->key, newSize);
                if(*(newHashArray+newHashValue) != NULL){
                    collision_insert(&(*(newHashArray+newHashValue)), head->key, head->value);
                }else{
                    *(newHashArray + newHashValue) = node_init(head->key, head->value);
                }
                /* move to the next node, if exists */
                head = head->next;
            }
        }
    }
    /* free the old hash table */
    for (i = 0; i < oldSize; i++) {
        node_free((*d)->arr[i]);
    }
    free((*d)->arr);
    (*d)->arr = newHashArray;
}

void freeDict(dict* d){
    int i;
    for (i = 0; i < d->size; i++) {
        node_free(d->arr[i]);
    }
    free(d->arr);
    free(d);
}

void node_free(node* n){
    node* _n = NULL;
    if (n == NULL) {
        return;
    }
    while (n != NULL) {
        _n = n->next;
        free(n->key);
        n->key = NULL;
        free(n);
        n = _n;
    }
}
bool isIn(dict* d, char* key){
    int hashVal = getHash(key, d->size);
    node* n = d->arr[hashVal];
    if(d == NULL){
        printf("Cannot use NULL as dict\n");
        exit(1);
    }
    for (; n != NULL; n = n->next) {
        if (strcmp(key, n->key) == 0) {
            return TRUE;
        }
    }
    return FALSE;
}

mydataType getValueByKey(dict* d, char* key){
    int hashVal = getHash(key, d->size);
    node* n = d->arr[hashVal];
    for (; n != NULL; n = n->next) {
        if (strcmp(key, n->key) == 0) {
            return n->value;
        }
    }
    return -1;
}

void updateValue(dict* d, char* key, mydataType value){
    int hashVal;
    node* head;
    if (isIn(d, key) != TRUE) {
        printf("Key does not exist\n");
        exit(1);
    }
    
    hashVal = getHash(key, d->size);
    head = d->arr[hashVal];
    while (head != NULL) {
        if (strcmp(head->key, key) == 0) {
            head->value = value;
            return;
        }
        head = head->next;
    }
}
