#include<stdio.h>
#include<stdlib.h>
#define SIZE 30

typedef int element;

typedef struct ListNode{
    element data;
    struct ListNode *llink;
    struct ListNode *rlink;
}ListNode;

void init(ListNode *head){  //초기화 
    head->llink = head;
    head->rlink = head;
}

void insert(ListNode *before, element item){    //뒤에 삽입
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));
    p->data = item;
    p->llink = before;
    p->rlink = before->rlink;
    before->rlink->llink = p;
    before->rlink = p;
}

ListNode* removeNode(ListNode *head, ListNode *removed){
    if(removed==head) return NULL;
    removed->llink->rlink = removed->rlink;
    removed->rlink->llink = removed->llink;
    return removed;
}

void delete(ListNode *head){
    ListNode *p = head;
    while(p != head){
        ListNode *tmp = p;
        p = p->rlink;
        free(tmp);
    }
    init(head);
}

ListNode* search(ListNode *head, int index){
    ListNode *p = head->rlink;
    for(int i=0; i<index; i++){
        p=p->rlink;
    }
    return p;
}

void swap(ListNode *head, int index1, int index2){
    ListNode *a = search(head, index1);
    ListNode *b = search(head, index2);
    element tmp = a->data;
    a->data = b->data;
    b->data = tmp;
}

void print(ListNode *phead){
    ListNode *p;
    for(p=phead->rlink; p!=phead; p=p->rlink){
        printf("%d", p->data);
        if(p->rlink==phead) break;
        printf(" > ");
    }
    printf("\n");
}

int getInput(int arr[]){
    int cnt = 0;
    while(1){
        scanf("%d", &arr[cnt++]);
        if(arr[cnt]==-1) {
            --cnt;
            break;
        }
    }
    return cnt;
}

int isTrueInput(int arr[], int cnt){
    int res = 0;
    for(int i=0; i<cnt; i++){
        if (arr[i] < 0 || arr[i] != (int)arr[i]) {
            res = 0;
            break;
        }
        else res = 1;
    }
    return res;
}

int main(){
    int cnt;
    int i, input;
    int index1, index2;
    int arr[SIZE] = {0, };

    ListNode *head = (ListNode *)malloc(sizeof(ListNode));
    init(head);

    ListNode *p = head;

    do{
        printf("자연수 리스트 입력 : ");
        cnt = getInput(arr);
    }while(isTrueInput(arr, cnt)==0);

    for(i=0; i<cnt; i++){
        insert(p, arr[i]);
        p = p->rlink;
        if(cnt==19) break;
    }

    printf("cnt : %d\n", cnt);
    print(head);
    printf("\n");

    while (1) {
        char c;
        printf("숫자 두 개를 입력하세요 (띄어쓰기로 구분, q로 종료): ");
        if (scanf("%d %d", &index1, &index2) == 2) {
            if((index1<0 || index1>cnt) || (index2<0 || index2>cnt)){
                printf("Error: The specified index is out of range. Please enter a vaild index.\n");
            }
            else if(index1==index2) ;
            else{
                swap(head, index1, index2);
            }
        } 
        else {
            scanf("%c", &c);
            if (c == 'q'){
                break;
            }
        }
        print(head);
        printf("\n");
    }
    print(head);
    free(head);
}

//음수, 소수 입력시 값 재입력
//swap 함수 값을 바꾸는 게 아니라 노드 위치 변경
//동적 할당 해제 확인
//최종 종료 때도 프린트하기