#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>

#define MAX_SIZE 100
#define esp 0.001

struct Node {
    float data;
    struct Node *next;
    struct Node *prev;
};

typedef struct Node *List;
typedef struct Node *Position;

struct ContansList {
    int max_size;
    List *PointToHeaderNode;
};

typedef struct ContansList *Matrix;



List createNode(float data) { // Tạo Node
    List lt = malloc(sizeof(struct Node));
    lt->data = data;
    lt->next = NULL;
    lt->prev = NULL;
    return lt;
}

List createHeaderNode() { // Tạo HeaderNode
    List headerNode = malloc(sizeof(struct Node));
    headerNode->next = NULL;
    headerNode->prev = NULL;
    return headerNode;
}

List addNodetoList(int n) { // Thêm Node vào List
    List headerNode = createHeaderNode();
    Position p = headerNode;
    for(int i = 1; i <= n + 1; i++) {
        float x; scanf("%f", &x);
        List newNode = createNode(x);
        newNode->next = p->next;
        newNode->prev = p;
        p->next = newNode;
        if(newNode->next != NULL){
            newNode->next->prev = newNode;
        }
        p = p->next;
    }
    return headerNode;
}

void addListtoMatrix(Matrix A, int n) {
    for(int i = 1; i <= n; i++) {
        List headerNode = createHeaderNode();
        headerNode = addNodetoList(n);
        A->PointToHeaderNode[i] = headerNode;
    }
}

Matrix createMatrix(int max_size) { // Tạo ma trận
    Matrix mt = malloc(sizeof(struct ContansList));
    mt->max_size = max_size;
    mt->PointToHeaderNode = malloc((max_size + 1)*sizeof(struct Node));
    return mt;
}

List createList(int n) {
    return addNodetoList(n - 1);
}

List createListZero(int n) {
    List headerNode = createHeaderNode();
    Position p = headerNode;
    for(int i = 1; i <= n+1; i++) {
        List newNode = createNode(0);
        newNode->next = p->next;
        newNode->prev = p;
        p->next = newNode;
        if(newNode->next != NULL) {
            newNode->next->prev = newNode;
        }
        p = p->next;
    }
    return headerNode;
}

void deleteColumn(Matrix A, int n) {
    for(int i = 1; i <= n; i++) {
        Position p = A->PointToHeaderNode[i];
        for(int j = 1; j <= (n/2)+1; j++) {
            p = p->next;
        }
        p->prev->next = p->next;
        p->next->prev = p->prev;
    }
}

List getNodeFromMatrix(Matrix A, int x, int y) {
    Position p = A->PointToHeaderNode[x];
    for(int i = 1; i <= y; i++){
        p = p->next;
    }
    return p;
}

List getNodeFromList(List headerNode, int x) {
    for(int i = 1; i <= x; i++){
        headerNode = headerNode->next;
    }
    return headerNode;
}

void displayMatrix(Matrix A, int n) {  
    for(int i = 1; i <= n; i++) {
        if (A->PointToHeaderNode[i] != NULL) { // Kiểm tra xem PointToHeaderNode[i] có tồn tại không
            Position p = A->PointToHeaderNode[i];
            while(p!= NULL) {
                printf("%.3f\t", p->data);
                p = p->next;
            }
            printf("\n");
        }
    }
}

void displayList(List headerNode) {
    headerNode = headerNode->next;
    while(headerNode != NULL) {
        printf("%.3f\t", headerNode->data);
        headerNode = headerNode->next;
    }
    printf("\n");
}

bool Gauss_Siedel(int n, Matrix A, List B, List N0) {
    List N1 = createListZero(n);
    bool dk;
    do{
        dk = false;
        for(int i = 1; i <= n; i++) {
            float s = 0, converg = 0;
            for(int j = 1; j <= n; j++)
                if(i != j){
                    s += getNodeFromMatrix(A, i, j)->data * getNodeFromList(N0,j)->data;
                    converg += (fabs(getNodeFromMatrix(A, i, j)->data));
                }
            if(converg >= getNodeFromMatrix(A, i, i)->data) return false;
            getNodeFromList(N1, i)->data = (getNodeFromList(B, i)->data - s) / getNodeFromMatrix(A, i, i)->data;
            if(fabs(getNodeFromList(N1, i)->data - getNodeFromList(N0, i)->data) >= esp) dk = true;
        }
        for(int i = 1; i <= n; i++) getNodeFromList(N0, i)->data = getNodeFromList(N1, i)->data;
    }while (dk);
    return true;
}

void swap(float *a, float *b);

int Gauss(int n, Matrix A, List B, List N0) {
    for(int i = 1; i <= n - 1; i++){
        if(getNodeFromMatrix(A, i, i)->data  == 0){
            int check = 0;
            for(int j = i + 1; j <= n; j++){
                if(getNodeFromMatrix(A, j, i)->data != 0){
                    for(int k = 1; k <= n; k++){
                        swap(&getNodeFromMatrix(A, i, j)->data, &getNodeFromMatrix(A, j, k)->data);
                    }
                    swap(&getNodeFromList(B, i)->data, &getNodeFromList(B, j)->data);
                    
                    check++;
                    break;
                }
            }
            if(check == 0) return 0;
        }
        for(int j = i + 1; j <= n; j++){
            float h = -getNodeFromMatrix(A, j, i)->data / getNodeFromMatrix(A, i, i)->data;
            for(int k = i; k <= n; k++) getNodeFromMatrix(A, j, k)->data += h * getNodeFromMatrix(A, i, k)->data;
            getNodeFromList(B, j)->data += h * getNodeFromList(B, i)->data;
        }
    }
    
	for(int i = n; i > 0; i--){
		float s = 0;
        if(getNodeFromMatrix(A, i, i)->data == 0) {
			if(getNodeFromList(B, i)->data == 0) return 1;
			else return 0;
		}
		for(int j = i; j <= n; j++) s += getNodeFromMatrix(A, i, j)->data * getNodeFromList(N0, j)->data;
		getNodeFromList(N0, i)->data = (getNodeFromList(B, i)->data - s) / getNodeFromMatrix(A, i, i)->data;
	}
	return 2;
}

void writeMatrixToFile(Matrix A, int n, char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Khong the mo file.\n");
        exit(1);
    }
    fprintf(file, "Ma tran %dx%d:\n",n,n+1);
    for (int i = 1; i <= n; i++) {
        Position p = A->PointToHeaderNode[i];
        while (p != NULL) {
            fprintf(file, "%.3f ", p->data);
            p = p->next;
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

void addListtoMatrixfromfile(Matrix A, char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Khong the mo file.\n");
        exit(1);
    }
    int n;
    fscanf(file, "%d", &n);
    for(int i = 1; i <= n; i++) {
        List headerNode = createHeaderNode();
        Position p = headerNode;
        for(int j = 0; j <= n ; j++) {
            float x;
            fscanf(file, "%f", &x);
            List newNode = createNode(x);
            p->next = newNode;
            newNode->prev = p;
            p = p->next;
        }
        A->PointToHeaderNode[i] = headerNode->next;
    }
    fclose(file);
}
int main() {
    Matrix A = createMatrix(MAX_SIZE);
    List B;
    int n;

    printf("----------------------------------------------------------\n");
    printf("----------------GIAI HE PHUONG TRINH Ax = B---------------\n");
    printf("----------------------------------------------------------\n");
    printf("1. Nhap ma tran A thu cong\n");
    printf("2. Nhap ma tran A bang file\n");
    printf("----------------------------------------------------------\n");
    printf("Nhap lua chon:");

    int select; scanf("%d", &select);
    if(select == 1) {
        printf("Nhap so an:\n"); scanf("%d", &n);
        printf("Nhap Ma Tran %dx%d:\n", n, n + 1);
        addListtoMatrix(A, n);
    } else if(select == 2) {
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        printf("Khong the mo file.\n");
    } else {
        fscanf(file, "%d", &n);
        addListtoMatrixfromfile(A, "input.txt");
        displayMatrix(A, n);
        writeMatrixToFile(A, n, "output.txt");
        printf("%d", n);
    }
    fclose(file);
}

    while(1) {
        printf("----------------------------------------------------------\n");
        printf("1.  In ra ma tran A\n");
        printf("2.  Xoa 1 cot o giua ma tran A\n");
        printf("3.  Nhap ma tran B\n");
        printf("4.  Giai he phuong trinh bang phuong phap Gauss-Siedel\n");
        printf("5. Giai he phuong trinh bang phuong phap Gauss\n");//-----------------------------
        printf("6. Thoat chuong trinh!!\n");
        printf("----------------------------------------------------------\n");
        printf("Nhap lua chon:\n");
        int selection; scanf("%d", &selection);
        if(selection == 1) {
            displayMatrix(A, n);
            writeMatrixToFile(A, n, "output.txt");
            printf("Ma tran A da duoc luu!!\n");
        }else if(selection == 2) {
            deleteColumn(A, n);
        } else if(selection == 3) {
            printf("Nhap List B:\n");
            B = createList(n); 
        } else if(selection == 4) {
           printf("Nhap nghiem ban dau:\n");
            List N0 = createList(n);
            if(Gauss_Siedel(n, A, B, N0)) {
                printf("Nghiem he phuong trinh:\n");
                displayList(N0);
            }
            else printf("Ma tran nhap vao khong thoa man dieu kien hoi tu\n");
        } else if(selection == 5) {
            List N0 = createListZero(n);
            int check = Gauss(n, A, B, N0);
            if(check == 2){
                displayList(N0);
            } else if(check == 0){
                printf("Phuong trinh vo nghiem!!\n");
            } else {
                printf("Phuong trinh vo so nghiem!!\n");
            }
        } else if(selection == 6) {
            printf("Da thoat chuong trinh!!\n");
            break;
        }

    }    
    return 0;
}

void swap(float *a, float *b) {
    float t = *a;
    *a = *b;
    *b = t;
}
