#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define $         { /* fprintf(stderr, ">>> ty zapostil cringe on %d, %10s\n",     __LINE__, __PRETTY_FUNCTION__); */ }
#define $$(code)  { /* fprintf(stderr, ">>> ty zapostil cringe on %d, %10s: %s\n", __LINE__, __PRETTY_FUNCTION__, #code); */ code; }

#define HashSize 10

typedef struct Node {
    const char* data;
    struct Node* next;
    struct Node* prev;
} Node ;

Node* Insert(const char* new_data, Node* elem);
const char* DelNode(Node* elem);
void NodeDump(Node* elem);
void ListDump(Node* head);
Node* ListSearch(Node* head, const char* str);

typedef struct HashTable {
    Node* Table[HashSize];
} HashTable ;

void Hash_Ctor(HashTable* Hash){

    for(int i = 0; i < HashSize; i++){

        Hash->Table[i] = Insert("*",NULL);
        fprintf(stderr, "Hash -> Table[%d]: 0x%p\n", i, Hash->Table[i]);

    }
}

unsigned int Hash_Func(const char* str){

    return strlen(str);
}

void Hash_Insert(HashTable* Hash, const char* str){

    unsigned int Hash_Num = Hash_Func(str);
    fprintf(stderr, "Hash function returned: %d\n", Hash_Num);
    Hash_Num = Hash_Num % HashSize;
    fprintf(stderr, "New hash number: %d\n", Hash_Num);

    Node* SearchNum = ListSearch(Hash -> Table[Hash_Num], str);
    fprintf(stderr, "SearchNum: 0x%p\n", SearchNum);

    Node* new_str = NULL;
    if(SearchNum == NULL)
        new_str = Insert(str, Hash -> Table[Hash_Num]);

    fprintf(stderr, "new_str: 0x%p\n", new_str);
}

Node* ListSearch(Node* head, const char* str){
    Node* elem = head;
    fprintf(stderr, "Search elem: 0x%p\n", elem);

    while (elem != NULL){
        fprintf(stderr, "Searching elem: 0x%p, Sring: (%s), elem -> data: (%s)\n", elem, str, elem -> data);

        if(strcmp(str, elem -> data) == 0) {
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
    $$( new_elem = calloc(sizeof(Node), 1) );
    $$ (assert(new_elem != 0));

    $$ (new_elem -> data = new_data );

    $$ (if(elem == NULL)
            return new_elem;)

    $$ (new_elem -> next = elem -> next;)
    $$ (new_elem -> prev = elem;)

    if(elem -> next != NULL) {
        $$ (elem->next->prev = new_elem;)
    }

    $$ (elem -> next = new_elem;)

    $ fprintf(stderr, "new_elem: 0x%p\n", new_elem);

    fprintf(stderr, "*** INSERTED SUCCESSFULLY\n");

    $$ (return new_elem;)
}

const char* DelNode(Node* elem){
    const char* SaveData = elem -> data;

    if(elem -> prev != NULL)
        elem -> prev -> next = elem -> next;

    if(elem -> next != NULL)
        elem -> next -> prev = elem -> prev;

    free(elem);
    return SaveData;
}

void NodeDump(Node* elem){
    fprintf(stderr, "Node [0x%p] {\n", elem);
    if(elem != 0) {
        fprintf(stderr, "Data: %s\n", elem->data);
        fprintf(stderr, "Next: 0x%p\n", elem->next);
        fprintf(stderr, "Prev: 0x%p\n", elem->prev);
    }
    fprintf(stderr,"}\n\n");
}

void ListDump(Node* head){
    fprintf(stderr, "List [0x%p] {\n", head);
    Node* elem = head;
    int i = 0;
    while (elem != NULL){
        fprintf(stderr, "Number: %d is: ", i);
        NodeDump(elem);
        elem = elem -> next;
        i++;
    }
    fprintf(stderr, "}\n\n");
}

int main() {
    $ HashTable Hash = {};
    $$(Hash_Ctor(&Hash); )
    $$(Hash_Insert(&Hash, "Dima"); )
    $$(Hash_Insert(&Hash, "Dima"); )
    $$(Hash_Insert(&Hash, "Anton"); )
    $$(Hash_Insert(&Hash, "Ded"); )
    return 0;
}
