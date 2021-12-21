#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct String{

    const char* str;
    int counter;
}String;

typedef struct Node {
    String data;
    struct Node* next;
} Node ;

Node* Insert(const char* new_data, Node* elem);
const char* DelNode(Node* elem);
Node* ListSearch(Node* head, const char* str);

typedef struct HashTable {
    Node** Table;
    int HashSize;
    int NumOfNodes;
} HashTable ;

void Hash_Ctor(HashTable* Hash, int HashSize);
unsigned int Hash_Func(const char* str);
void Hash_Resize(HashTable* Hash);
void Hash_Insert(HashTable* Hash, const char* str, int counter);
void Del_Hash_Table(HashTable* Hash);
void Print_Hash_Table(HashTable* Hash);


void Hash_Ctor(HashTable* Hash, int HashSize){
    Hash -> HashSize = HashSize;
    Hash -> Table = calloc(Hash -> HashSize, sizeof(Node*));
}

void ReadFile(FILE* input, HashTable* Hash){

    char str[100];
    while (1){
        char* estr = fgets(str, sizeof(str), input);
        if (estr == NULL)
            break;
        char* SaveChar = strchr(str, '\n');
        if (SaveChar != NULL)
            *SaveChar = '\0';

        printf("%s:\n", str);
        Hash_Insert(Hash, str, 1);

    }
}

void Hash_Resize(HashTable* Hash){

    int NewSize = (Hash -> HashSize) * 2;
    Node** NewTable = calloc(NewSize, sizeof(Node*));
    HashTable TmpHash = {NewTable, NewSize};

    for (int i = 0; i < Hash -> HashSize; i++) {
        Node* elem = Hash -> Table[i];
        while (elem!= NULL){
            Hash_Insert(&TmpHash, elem -> data.str, elem -> data.counter);

            elem = elem -> next;
        }
    }

    Del_Hash_Table(Hash);

    Hash -> Table = NewTable;
    Hash -> HashSize = NewSize;
}

unsigned int Hash_Func(const char* str){
    unsigned int h = 0;
    while (*str){
        h += (unsigned char)(*str);
        h -= (h >> 19) | (h << 13);
        str++;
    }
    return h;
}

void Hash_Insert(HashTable* Hash, const char* str, int counter){

    if(Hash -> NumOfNodes >= Hash -> HashSize * 2)
        Hash_Resize(Hash);

    unsigned int Hash_Num = Hash_Func(str);
    Hash_Num = Hash_Num % Hash -> HashSize;

    Node* SearchNum = ListSearch(Hash -> Table[Hash_Num], str);

    if(SearchNum == NULL) {
        const char* copystr = strdup(str);
        Hash -> Table[Hash_Num] = Insert(copystr, Hash->Table[Hash_Num]);
        Hash -> Table[Hash_Num] -> data.counter = counter;
        Hash -> NumOfNodes++;
    }

    else {
        SearchNum -> data.counter += counter;
    }

}

Node* ListSearch(Node* head, const char* str){
    Node* elem = head;

    while (elem != NULL){

        if(strcmp(str, elem -> data.str) == 0) {
            return elem;
        }

        elem = elem -> next;
    }

    return NULL;
}

Node* Insert(const char* new_data, Node* elem){

     Node* new_elem = NULL;
     new_elem = calloc(sizeof(Node), 1);
     if (new_elem == NULL)
         abort();

     new_elem -> data.str = new_data;
     new_elem -> data.counter = 1;

     if(elem == NULL)
            return new_elem;

     new_elem -> next = elem;

     return new_elem;
}

const char* DelNode(Node* elem){
    const char* SaveData = elem -> data.str;

    if(elem -> next != NULL)
        elem -> next = elem -> next -> next;

    return SaveData;
}

void Print_Unique(Node* head){
    Node* elem = head;
    int i = 0;
    while (elem != NULL){
        if(elem->data.counter == 1) {
            printf("%s\n", elem->data.str);
        }
        elem = elem -> next;
        i++;
    }
}

void Print_Hash_Table(HashTable* Hash){

    for(int i = 0; i < Hash -> HashSize; i++){
        Print_Unique(Hash -> Table[i]);
    }
}

void Del_Hash_Table(HashTable* Hash){

    for (int i = 0; i < Hash -> HashSize; i++) {
        Node* elem = Hash -> Table[i];
        while (elem!= NULL){
            Node* SaveNext = elem -> next;
            free ((void*) elem -> data.str);
            free (elem);
            elem = SaveNext;
        }
    }

    free (Hash -> Table);
}

int main() {
    HashTable Hash = {};
    Hash_Ctor(&Hash, 100);
    /* Hash_Insert(&Hash, "Dima", 1);
    Hash_Insert(&Hash, "Dima", 1);
    Hash_Insert(&Hash, "Dima", 1); 
    Hash_Insert(&Hash, "Anton", 1); 
    Hash_Insert(&Hash, "Vlad", 1);
    Hash_Insert(&Hash, "Serega", 1); 
    Hash_Insert(&Hash, "Vlad", 1);
    Hash_Insert(&Hash, "Lexa", 1); 
    Hash_Insert(&Hash, "Serega", 1); 
    Hash_Insert(&Hash, "Vlad", 1);
    Hash_Insert(&Hash, "Ilya", 1); 
    Hash_Insert(&Hash, "Vasya", 1); 
    Hash_Insert(&Hash, "Poltorashka", 1); 
    Hash_Insert(&Hash, "Ovchos", 1); 
    Hash_Insert(&Hash, "Petrovich", 1); 
    Hash_Insert(&Hash, "Kris", 1); 
    Hash_Insert(&Hash, "Vitalya", 1); 
    Hash_Insert(&Hash, "Boris", 1);*/

    FILE* HashFile = fopen("C:\\Users\\globi\\Desktop\\Inf Zad 1\\HashTable\\Strings.txt", "r");
    ReadFile(HashFile, &Hash);
    fclose(HashFile);

    Print_Hash_Table(&Hash);
    Del_Hash_Table(&Hash);


    return 0;
}
