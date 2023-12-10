#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 해시 테이블의 크기 정의
#define HASH_TABLE_SIZE 100003

// 해시 노드 구조체 정의
typedef struct Node {
    char name[21];
    struct Node* next;
} Node;

// 해시 테이블 구조체 정의
typedef struct HashTable {
    Node* table[HASH_TABLE_SIZE];
} HashTable;

// 해시 함수 정의
unsigned long hash(const char* str) {
    unsigned long hash = 5381;
    int c;

    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c; // hash * 33 + c
    }

    return hash % HASH_TABLE_SIZE;
}

// 해시 테이블 초기화 함수
void initHashTable(HashTable* ht) {
    for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
        ht->table[i] = NULL;
    }
}

// 해시 테이블에 값 추가 함수
void addToHashTable(HashTable* ht, const char* name) {
    unsigned long index = hash(name);

    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    newNode->next = NULL;

    if (ht->table[index] == NULL) {
        ht->table[index] = newNode;
    } else {
        newNode->next = ht->table[index];
        ht->table[index] = newNode;
    }
}

// 완주하지 못한 선수 찾는 함수
char* findUnfinishedPlayer(HashTable* ht, char** participant, char** completion, int participantSize) {
    // 참가자 명단을 해시 테이블에 추가
    for (int i = 0; i < participantSize; ++i) {
        addToHashTable(ht, participant[i]);
    }

    // 완주자 명단을 해시 테이블에서 제거
    for (int i = 0; i < participantSize - 1; ++i) {
        unsigned long index = hash(completion[i]);
        Node* currentNode = ht->table[index];
        Node* prevNode = NULL;

        while (currentNode != NULL && strcmp(currentNode->name, completion[i]) != 0) {
            prevNode = currentNode;
            currentNode = currentNode->next;
        }

        if (currentNode != NULL) {
            if (prevNode == NULL) {
                ht->table[index] = currentNode->next;
            } else {
                prevNode->next = currentNode->next;
            }

            free(currentNode);
        }
    }

    // 해시 테이블에서 남아 있는 선수 찾기
    for (int i = 0; i < HASH_TABLE_SIZE; ++i) {
        if (ht->table[i] != NULL) {
            return ht->table[i]->name;
        }
    }

    return NULL; // 완주하지 못한 선수가 없는 경우
}

int main() {
    // 예제 입력 데이터
    char* participant1[] = {"leo", "kiki", "eden"};
    char* completion1[] = {"eden", "kiki"};

    char* participant2[] = {"marina", "josipa", "nikola", "vinko", "filipa"};
    char* completion2[] = {"josipa", "filipa", "marina", "nikola"};

    char* participant3[] = {"mislav", "stanko", "mislav", "ana"};
    char* completion3[] = {"stanko", "ana", "mislav"};

    // 해시 테이블 초기화
    HashTable ht;
    initHashTable(&ht);

    // 각 예제에 대해 완주하지 못한 선수 찾기
    char* result1 = findUnfinishedPlayer(&ht, participant1, completion1, 3);
    char* result2 = findUnfinishedPlayer(&ht, participant2, completion2, 5);
    char* result3 = findUnfinishedPlayer(&ht, participant3, completion3, 4);

    // 결과 출력
    printf("Result 1: %s\n", result1);
    printf("Result 2: %s\n", result2);
    printf("Result 3: %s\n", result3);

    return 0;
}
