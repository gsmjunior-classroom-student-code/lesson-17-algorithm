#include <stdio.h>
#include <string.h>

char* solution(char* participant[], char* completion[], int n) {
    // participant와 completion은 각각 n과 n-1의 길이를 가진 문자열 배열이다.
    // n은 1 이상 100,000 이하이다.
    // 참가자의 이름은 1개 이상 20개 이하의 알파벳 소문자로 이루어져 있다.
    // 참가자 중에는 동명이인이 있을 수 있다.
    // 완주하지 못한 선수의 이름을 반환한다.

    // participant 배열을 정렬한다. (버블 정렬 사용)
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(participant[j], participant[j + 1]) > 0) {
                // participant[j]가 participant[j + 1]보다 사전순으로 뒤에 있으면 교환한다.
                char* temp = participant[j];
                participant[j] = participant[j + 1];
                participant[j + 1] = temp;
            }
        }
    }

    // completion 배열을 정렬한다. (버블 정렬 사용)
    for (int i = 0; i < n - 2; i++) {
        for (int j = 0; j < n - i - 2; j++) {
            if (strcmp(completion[j], completion[j + 1]) > 0) {
                // completion[j]가 completion[j + 1]보다 사전순으로 뒤에 있으면 교환한다.
                char* temp = completion[j];
                completion[j] = completion[j + 1];
                completion[j + 1] = temp;
            }
        }
    }

    // participant와 completion을 비교한다.
    for (int i = 0; i < n - 1; i++) {
        if (strcmp(participant[i], completion[i]) != 0) {
            // participant[i]와 completion[i]가 다르면 participant[i]가 완주하지 못한 선수이다.
            return participant[i];
        }
    }

    // 모든 completion[i]와 일치하는 participant[i]가 있으면 participant[n - 1]이 완주하지 못한 선수이다.
    return participant[n - 1];
}

int main() {
    // 입출력 예 1
    char* participant1[] = {"leo", "kiki", "eden"};
    char* completion1[] = {"eden", "kiki"};
    int n1 = 3;
    printf("%s\n", solution(participant1, completion1, n1)); // leo

    // 입출력 예 2
    char* participant2[] = {"marina", "josipa", "nikola", "vinko", "filipa"};
    char* completion2[] = {"josipa", "filipa", "marina", "nikola"};
    int n2 = 5;
    printf("%s\n", solution(participant2, completion2, n2)); // vinko

    // 입출력 예 3
    char* participant3[] = {"mislav", "stanko", "mislav", "ana"};
    char* completion3[] = {"stanko", "ana", "mislav"};
    int n3 = 4;
    printf("%s\n", solution(participant3, completion3, n3)); // mislav
}
