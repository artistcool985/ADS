#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10

typedef struct Node {
    int key;
    int value;
    struct Node* next;
} Node;

typedef struct {
    Node** table;
} HashTable;

int hash_function(int key) {
    return key % TABLE_SIZE;
}

void insert(HashTable* table, int key, int value) {
    int index = hash_function(key);
    int collisions = 0;

    while (table->table[index]!= NULL) {
        collisions++;
        index = (index + 1) % TABLE_SIZE;
    }

    Node* node = (Node*) malloc(sizeof(Node));
    node->key = key;
    node->value = value;
    node->next = table->table[index];
    table->table[index] = node;

    printf("Inserted key %d with value %d at index %d with %d collisions\n", key, value, index, collisions);
}

void print_table(HashTable* table) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        Node* node = table->table[i];
        printf("%d: ", i);
        while (node!= NULL) {
            printf("(%d, %d) -> ", node->key, node->value);
            node = node->next;
        }
        printf("\n");
    }
}

int main() {
    HashTable table;
    table.table = (Node**) malloc(TABLE_SIZE * sizeof(Node*));
    for (int i = 0; i < TABLE_SIZE; i++) {
        table.table[i] = NULL;
    }

    insert(&table, 5, 10);
    insert(&table, 15, 20);
    insert(&table, 25, 30);
    insert(&table, 35, 40);
    insert(&table, 45, 50);

    print_table(&table);

    return 0;
}