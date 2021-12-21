#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#define $         { /* fprintf(stderr, ">>> ty zapostil cringe on %d, %10s\n",     __LINE__, __PRETTY_FUNCTION__); */ }
#define $$(code)  { /* fprintf(stderr, ">>> ty zapostil cringe on %d, %10s: %s\n", __LINE__, __PRETTY_FUNCTION__, #code); */ code; }

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
void NodeDump(Node* elem);
void ListDump(Node* head);
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


void Hash_Ctor(HashTable* Hash, int HashSize){
    Hash -> HashSize = HashSize;
    Hash -> Table = calloc(Hash -> HashSize, sizeof(Node*));
}

void Hash_Resize(HashTable* Hash){

    fprintf(stderr, "WE WILL RESIZE HASH TABLE ----------\n");
    fprintf(stderr, "Old size: %d\n", Hash -> HashSize);

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

    fprintf(stderr, "HASH TABLE RESIZED SUCCESSFULLY, NEW SIZE: %d\n", NewSize);

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
    fprintf(stderr, "Hash function returned: %d\n", Hash_Num);
    Hash_Num = Hash_Num % Hash -> HashSize;
    fprintf(stderr, "New hash number: %d\n", Hash_Num);

    Node* SearchNum = ListSearch(Hash -> Table[Hash_Num], str);
    fprintf(stderr, "SearchNum: 0x%p\n", SearchNum);

    if(SearchNum == NULL) {
        Hash -> Table[Hash_Num] = Insert(str, Hash->Table[Hash_Num]);
        Hash -> Table[Hash_Num] -> data.counter = counter;
        Hash -> NumOfNodes++;
    }

    else {
        SearchNum -> data.counter += counter;
        fprintf(stderr, "We FOUND (%s) as (%s), Counter NOW = %d\n", str, SearchNum->data.str, SearchNum->data.counter);
    }

    fprintf(stderr, "new_str: 0x%p\n", Insert(str, Hash->Table[Hash_Num]));
}

Node* ListSearch(Node* head, const char* str){
    Node* elem = head;
    fprintf(stderr, "Search elem: 0x%p\n", elem);

    while (elem != NULL){
        fprintf(stderr, "Searching elem: 0x%p, Sring: (%s), elem -> data: (%s), counter = %d\n",
                elem, str, elem -> data.str, elem -> data.counter);

        if(strcmp(str, elem -> data.str) == 0) {
            fprintf(stderr, "Found: (%s)\n", str);
            return elem;
        }

        elem = elem -> next;
    }

    fprintf(stderr, "NOT Found: (%s)\n", str);
    return NULL;
}

Node* Insert(const char* new_data, Node* elem){

    fprintf(stderr, "*** WE WILL INSERT ELEMENT\n");
    fprintf(stderr, "new_data: %s\n", new_data);
    fprintf(stderr, "elem: 0x%p\n", elem);
    //NodeDump(elem);

    $ Node* new_elem = NULL;
    $$( new_elem = calloc(sizeof(Node), 1); )
    $$ (assert(new_elem != 0); )

    $$ (new_elem -> data.str = new_data );
    $$ (new_elem -> data.counter = 1 );

    $$ (if(elem == NULL)
            return new_elem;)

    $$ (new_elem -> next = elem; )

    $ fprintf(stderr, "new_elem: 0x%p\n", new_elem);

    fprintf(stderr, "*** INSERTED SUCCESSFULLY\n");

    $$ (return new_elem;)
}

const char* DelNode(Node* elem){
    const char* SaveData = elem -> data.str;

    if(elem -> next != NULL)
        elem -> next = elem -> next -> next;

    return SaveData;
}

void NodeDump(Node* elem){
    fprintf(stderr, "Node [0x%p] {\n", elem);
    if(elem != 0) {
        fprintf(stderr, "        Data: %s, Counter: %d\n", elem->data.str, elem -> data.counter);
        fprintf(stderr, "        Next: 0x%p\n", elem->next);
    }
    fprintf(stderr,"        }\n\n");
}

void ListDump(Node* head){
    fprintf(stderr, "    List [0x%p] {\n", head);
    Node* elem = head;
    int i = 0;
    while (elem != NULL){
        fprintf(stderr, "    Number: %d is: ", i);
        NodeDump(elem);
        elem = elem -> next;
        i++;
    }
    fprintf(stderr, "    }\n\n");
}

void Print_Hash_Data(Node* head){
    Node* elem = head;
    int i = 0;
    while (elem != NULL){
        if(strcmp(elem -> data.str, "*") != 0) {
            fprintf(stderr, "Data: %s, Counter: %d\n", elem->data.str, elem -> data.counter);
        }
        elem = elem -> next;
        i++;
    }
}

void Print_Unique(Node* head){
    Node* elem = head;
    int i = 0;
    while (elem != NULL){
        if(strcmp(elem -> data.str, "*") != 0 && elem->data.counter == 1) {
            fprintf(stderr, "Data: %s, Counter: %d\n", elem->data.str, elem -> data.counter);
        }
        elem = elem -> next;
        i++;
    }
}

void Print_Hash_Table(HashTable* Hash){

    fprintf(stderr, "\nBegin print ----------------\n");
    for(int i = 0; i < Hash -> HashSize; i++){
        Print_Unique(Hash -> Table[i]);
    }
    fprintf(stderr, "End print ----------------\n");
}

void Dump_Hash_Table(HashTable* Hash){

    fprintf(stderr, "\nHash table: [0x%p] {\n", Hash);
    fprintf(stderr, "Hash table size: %d\n", Hash -> HashSize);
    fprintf(stderr, "Number of nodes: %d\n\n", Hash -> NumOfNodes);

    for (int i = 0; i < Hash -> HashSize; i++){
        fprintf(stderr, "List number: %d\n", i);
        ListDump(Hash -> Table[i]);
    }

    fprintf(stderr, "}\n\n");
}

#define $NOVIN

void Del_Hash_Table(HashTable* Hash){

    for (int i = 0; i < Hash -> HashSize; i++) {
        Node* elem = Hash -> Table[i];
        while (elem!= NULL){
            Node* SaveNext = elem -> next;

            $NOVIN
            elem -> next = NULL;
            elem -> data.str = NULL;
            elem -> data.counter = NAN;
            $NOVIN

            free(elem);
            elem = SaveNext;
        }
    }

    free(Hash -> Table);
    Hash -> Table = NULL;
}

int main() {
    $ HashTable Hash = {};
    $$(Hash_Ctor(&Hash, 3); )
    $$(Hash_Insert(&Hash, "Dima", 1); )
    $$(Hash_Insert(&Hash, "Dima", 1); )
    $$(Hash_Insert(&Hash, "Dima", 1); )
    $$(Hash_Insert(&Hash, "Anton", 1); )
    $$(Hash_Insert(&Hash, "Ded", 1); )
    $$(Hash_Insert(&Hash, "Serega", 1); )
    $$(Hash_Insert(&Hash, "Ded", 1); )
    $$(Hash_Insert(&Hash, "Lexa", 1); )
    $$(Hash_Insert(&Hash, "Serega", 1); )
    $$(Hash_Insert(&Hash, "Ded", 1); )
    $$(Hash_Insert(&Hash, "Ilya", 1); )
    $$(Hash_Insert(&Hash, "Vasya", 1); )
    $$(Hash_Insert(&Hash, "Poltorashka", 1); )
    $$(Hash_Insert(&Hash, "Ovchos", 1); )
    $$(Hash_Insert(&Hash, "Petrovich", 1); )
    $$(Hash_Insert(&Hash, "Kris", 1); )
    $$(Hash_Insert(&Hash, "Vitalya", 1); )
    $$(Hash_Insert(&Hash, "Boris", 1); )

    $$(Dump_Hash_Table(&Hash);)

    //$$(Print_Hash_Table(&Hash);)

    $$(Del_Hash_Table(&Hash); )
    return 0;
}
