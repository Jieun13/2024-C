#include<stdio.h> //최종 제출본
#include<stdlib.h>
#include<math.h>
#define MAX_STACK_SIZE 100
#define SIZE 100

typedef int element;
typedef struct {
    element data[MAX_STACK_SIZE];
    int top;
} StackType;

void initStack(StackType *s){
    s->top = -1;
}
int isEmpty(StackType *s){
    return (s->top == -1);
}
int isFull(StackType *s){
    return (s->top==(MAX_STACK_SIZE -1));
}
void push (StackType *s, element item){
    if(isFull(s)){
        fprintf(stderr, "error\n");
        return;
    }
    else {
        s->top++;
        s->data[s->top] = item;
    }
}
element pop (StackType *s){
    if(isEmpty(s)){
        fprintf(stderr, "error\n");
        exit(1);
    }
    else{
        return s->data[s->top--];
    }
}
// ========================================================================

int isNumber(char c){ 
    c = c - '\0';
    if((c>47) && (c<58)) return 1; 
    else return 0; 
}

int caculate(int a, int c, int b){
    int result = 0;
    switch(c){
        case 43 : // '+'
            result = a + b;
            break;
        case 45 : // '-'
            result = a - b;
            break; 
        case 42 : // '*'
            result = a * b;
            break; 
        case 47 : // '/'
            result = a / b;
            break; 
    }
    return result;
}

void stackToArray(StackType *s, int *array) {
    int cnt = 0;
    int top = s->top;

    if(top != -1){
        for (int i = 0; i<=top; i++) {
            array[cnt++] = s->data[i]+48;
        }
    }
}

void prnStack(int array[][SIZE], int index, char pos){
    int i, j;
    int maxSize[SIZE] = {0, };

    for(i=0; i<index; i++){
        for(j=0; j<SIZE; j++){
            if(array[i][j] != '\0') {
                maxSize[i]++;
            }
        }
        if(maxSize[i]>maxSize[0]) maxSize[0] = maxSize[i];
    }

    for (i=maxSize[0]; i>=0; i--) {
        for(j=0; j<index; j++){
            if(array[j][i]=='\0'){
                printf("     ");
            }
            else{
                if(pos=='i'){
                    printf("%5d", array[j][i]-48);
                }
                else{
                    printf("%5c", array[j][i]-48);
                }
            }
        }
        printf("\n");
    }
    printf("-----------------------------------------------------------------\n");
}

int main(){
    StackType operator, number;
    char input[100];   
    int i = 0, j = 0;
    int midValue = 0, value = 0, inputSize = 0;
    int a, b, c;
    int cnt = 0, index = 0;
    int maxSize[SIZE] = {0, };

    int number_array[SIZE][SIZE];
    for(i=0; i<SIZE; i++){
        for(j=0; j<SIZE; j++){
            number_array[i][j]='\0';
        }
    }
    int (*pNumArray)[SIZE] = number_array;

    int operator_array[SIZE][SIZE];
    for(i=0; i<SIZE; i++){
        for(j=0; j<SIZE; j++){
            operator_array[i][j]='\0';
        }
    }
    int (*pOpArray)[SIZE] = operator_array;

    initStack(&number);
    initStack(&operator);

    printf("Input : ");
    while(1){
        scanf("%c", &input[inputSize]);
        if(input[inputSize]=='\n') break;
        inputSize++;
    }

    for(i=0; i<inputSize; i++){
        int *array = {0, };
        if ((input[i]== '(') || (input[i]== ')')){
            if(input[i]==')') {
                b = pop(&number);
                c = pop(&operator);
                a = pop(&number);
                midValue = caculate(a, c, b);

                push(&number, midValue);
                printf("Next char is ')'. So pop and caculate -> %d %c %d\n", a, c, b);
                printf("push mid Result Value %d\n", midValue);
                stackToArray(&number, *pNumArray++);
                stackToArray(&operator, *pOpArray++);
                index++;
                
            }
        }
        else if((input[i] == '+') || (input[i]=='-') || (input[i]=='*') || (input[i]=='/')){
            value = input[i]-'\0';
            push(&operator, value);
            printf("push %c\n", input[i]);
            stackToArray(&number, *pNumArray++);
            stackToArray(&operator, *pOpArray++);
            index++;
        }
        else if(input[i]=='\n'){
            break;
        }
        else {
            char temp[10];
            cnt = 0;
            while(1){  
                if(isNumber(input[i]) == 0) {
                    i--;
                    break; 
                }
                temp[cnt++] = input[i]; 
                i++;
            }
            temp[cnt]='\0';
            value = atoi(temp);
            push(&number, value);
            printf("push %d\n", value);
            stackToArray(&number, *pNumArray++);
            stackToArray(&operator, *pOpArray++);
            index++;
        }
    }
    printf("\nnumber stack : \n");
    char pos = 'i';
    prnStack(number_array, index, pos);

    printf("operator stack : \n");
    pos = 'c';
    prnStack(operator_array, index, pos);

    printf("result : %d\n", pop(&number));
}