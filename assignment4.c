#include <stdio.h>
#include <stdlib.h>

int rows = 8;
int cols = 8;

typedef struct TreeNode {
    int x, y;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

typedef struct QueueNode {
    TreeNode *treeNode;
    struct QueueNode *next;
} QueueNode;

typedef struct Queue {
    QueueNode *front, *rear;
} Queue;

TreeNode* createNode(int x, int y) {
    TreeNode *newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->x = x;
    newNode->y = y;
    newNode->left=NULL;
    newNode->right=NULL;
    return newNode;
}

Queue* createQueue() {
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

int isQueueEmpty(Queue *q) {
    return q->front == NULL;
}

void enqueue(Queue *q, TreeNode *node) {
    QueueNode *temp = (QueueNode*)malloc(sizeof(QueueNode));
    temp->treeNode = node;
    temp->next = NULL;
    if (q->rear == NULL) {
        q->front = q->rear = temp;
        return;
    }
    q->rear->next = temp;
    q->rear = temp;
}

TreeNode* dequeue(Queue *q) {
    if (isQueueEmpty(q)) {
        return NULL;
    }
    QueueNode *temp = q->front;
    TreeNode *node = temp->treeNode;
    q->front = q->front->next;
    if (q->front == NULL) {
        q->rear = NULL;
    }
    free(temp);
    return node;
}

//=========================================================================================================================

// 트리 노드 만들고 상태값 0(길)으로 바꿔주는 함수
TreeNode* createTreeNode(int x, int y, int status[][8]) {
    TreeNode *newNode = createNode(x, y);
    status[x][y] = '0';
    return newNode;
}

//미로를 트리로 변환하는 함수
TreeNode* convertTree(int maze[][cols], int startX, int startY, int status[][cols]){

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    Queue *tree_q = createQueue();
    TreeNode *root = createTreeNode(startX, startY, status);
    enqueue(tree_q, root);
    status[startX][startY] = 2;

    printf("Root Node : (%d, %d)\n", startX, startY);

    while (!isQueueEmpty(tree_q)) {
        TreeNode *node = dequeue(tree_q);
        int x = node->x;
        int y = node->y;

        for (int i = 0; i < 4; i++) {
            int newX = x + dx[i];
            int newY = y + dy[i];

            if (newX >= 0 && newX < rows && newY >= 0 && newY < cols && maze[newX][newY] == 0 && status[newX][newY] == 0) {
                TreeNode *childNode = createTreeNode(newX, newY, status);
                if (node->left == NULL) {
                    node->left = childNode;
                    printf("adding node : (%d, %d) as a child of node : (%d, %d)\n", node->left->x, node->left->y, node->x, node->y);
                } 
                else if (node->left != NULL && node->right == NULL) {
                    node->right = childNode;
                    printf("adding node : (%d, %d) as a child of node : (%d, %d)\n", node->right->x, node->right->y, node->x, node->y);
                } 
                else {
                    TreeNode *current = node->left;
                    while (current->left != NULL) {
                        current = current->left;
                    }
                    current->left = childNode;
                }
                enqueue(tree_q, childNode);
                status[newX][newY] = 2;
            }
        }
    }
    free(tree_q);
    return root;
}

//현재 상태 출력 함수
void printStatus(int status[][cols]){
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            if(status[i][j]==2){        //길 == 2
                printf("0 ");
            }
            else if(status[i][j]==0){   //벽 == 0
                printf("# ");
            }
            else if(status[i][j]==3){   //현재 위치 == 3
                printf("C ");
            }
            else{                       //갔던 길 == 1
                printf(". ");
            }
        }
        printf("\n");
    }
}

//길 찾기 함수
void searchPath(TreeNode *root, int status[][cols], int startX, int startY, int endX, int endY){
    int iflag = 0;
    int x = startX;
    int y = startY;
    Queue *search_q = createQueue();
    if(root==NULL) return;
    enqueue(search_q, root);
    
    while(!isQueueEmpty(search_q)){
        root = dequeue(search_q);
        x = root->x;
        y = root->y;
        status[x][y] = 3;   //현재 위치로 표시

        printf("\ncurrent point : (%d, %d)\n", x, y);
        printStatus(status);    //미로 현재 상태 출력
        status[x][y] = 1;   //갔던 길로 변경

        if(x==endX && y==endY) {
            iflag = 1;
            break;
        }
        if(root->left) enqueue(search_q, root->left);
        if(root->right) enqueue(search_q, root->right);
    }
    if(iflag == 0) printf("no path! \n\n");
    else printf("path found! \n\n");
}

int main() {
    int maze[8][8] = {
        {0, 1, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 1, 1, 0, 1, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 1, 1, 1, 0, 1, 1, 1},
        {0, 1, 0, 0, 0, 1, 0, 0},
        {0, 1, 0, 1, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0},
        {1, 1, 1, 1, 1, 0, 0, 0}
    };

    int startX = 0;
    int startY = 0;

    int endX = 7;
    int endY = 7;

    int status[8][8] = { 0, };

    TreeNode *root = convertTree(maze, startX, startY, status); //트리로 변경

    searchPath(root, status, startX, startY, endX, endY);   //길 찾기
}