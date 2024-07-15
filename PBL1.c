#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>

#define MAX_SIZE 100
#define MAX_REPE 80
#define esp 0.0005

struct Node
{
    float data;
    struct Node *next;
    struct Node *prev;
};
typedef struct Node *List;
typedef struct Node *Position;

struct ArrayList
{
    int max_size;
    List *PointToHeaderNode;
};
typedef struct ArrayList *Matrix;

Matrix createMatrix(int max_size);                          // Tạo ma trận
List createNode(float data);                                // Tạo Node
List createHeaderNode();                                    // Tạo HeaderNode
List addNodetoList(int n);                                  // Thêm Node vào List
void addListtoMatrix(Matrix A, int n);                      // Thêm List vào Matrix
List createList(int n);                                     // Tạo List kích thước n
List createListZero(int n);                                 // Tạo List kích thước n chứa các phần tử 0
void createMatrixZero(Matrix Temp, int n);                  // Tạo Ma trận kích thước nxn chứa các phần tử 0
void copyMatrix(Matrix Temp, Matrix A, int n);              // Copy Ma trận Temp từ Ma trận A
void copyList(List Temp, List B, int n);                    // Copy List Temp từ List B
void deleteMiddle(Matrix A, int n);                         // Xóa cột giữa Ma trận
List getNodeFromMarix(Matrix A, int x, int y);              // Lấy Node ở vị trí (x, y) trong ma trận
List getNodeFromList(List headerNode, int x);               // Lấy Node ở vị trí x tring List
void displayMatrix(Matrix A, int n);                        // In ra ma trận
void displayList(List headerNode, int n);                   // In ra List
void displayEquations(Matrix A, List B, int n);             // In ra hệ phương trình Ax = B
void displayN0(List N0, int n);                             // In ra nghiệm phương trình
void Swap(float *a, float *b);                              // Hoán vị 2 biến
void Swap_row(Matrix A, List B, int n, int row1, int row2); // Hoán vị 2 hàng
bool is_square_matrix(Matrix A, int n);                     // Kiểm tra có phải ma trận vuông không

// Các phương pháp giải hệ phương trình

bool check_Matrix(Matrix A, List B, int n);                // Kiểm tra điều kiện hội tụ trong phương pháp Gauss_Siedel
bool Gauss_Siedel(int n, Matrix A, List B, List N0);       // Phương pháp Gauss_Siedel
int Gauss(int n, Matrix A, List B, List N0);               // Phương pháp Gauss
float det(int n, Matrix A);                                // Tính định thức ma trận
void Krame(int n, Matrix A, Matrix Temp, List B, List N0); // Phương pháp Krame
void change_Matrix(Matrix A, List B, int n);               // Biến đổi ma trận phù hợp với điều kiện giảm dư
bool Giam_du(int n, Matrix A, List B, List N0);            // Phương pháp giảm dư
void displayStep_Giamdu(List N0, List r);                  // In ra các bước thực hiện của phương pháp giảm dư

void addListtoMatrixfromfile(Matrix A, int n, char *filename); // Đọc file
bool createListfromFile(List B, int n, char *filename);        // Đọc file
void outputResults(List N0, int n, char *filename);            // Ghi file
void outputMatrix(Matrix A, int n, char *filename);            // Ghi file

// Danh sách MENU
void MENU1();
void MENU2();
void MENU3();
void MENU4();
void MENU5();
void MENU6();

void setColor(int textColor); // Thiết lập màu
void INTRO();

int main()
{
    // Giới thiệu
    INTRO();

    remove("RESULT1.OUT");
    remove("RESULT2.OUT");

    Matrix A = createMatrix(MAX_SIZE);
    List B;
    bool have_matrix_B = false;
    int n; // So an cua phuong trinh

    setColor(11);
    printf("==========================================================\n");
    setColor(11);
    printf("============ ");
    setColor(5);
    printf("<< GIAI HE PHUONG TRINH AX = B >>");
    setColor(11);
    printf(" ===========\n");
    setColor(11);
    printf("==========================================================\n\n");
Repeat: // Nhap lai ma tran A
    have_matrix_B = false;

    MENU1();
    setColor(14);
    printf("Nhap lua chon cua ban: ");
    int select;
    scanf("%d", &select);
    printf("\n");
    setColor(8);
    if (select == 1)
    {
        printf("Nhap so an cua cua phuong trinh: ");
        scanf("%d", &n);
        printf("Nhap Ma Tran %dx%d:\n", n, n + 1);
        addListtoMatrix(A, n);
        printf("Ma tran A ban nhap da duoc luu!!\n");
    }
    else if (select == 2)
    {
        char filename[20];
        // Đưa ra MENU
        MENU2();

        setColor(14);
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &select);
        printf("\n");
        setColor(8);
        if (select == 1)
        {
            strcpy(filename, "DAYSO1.IN");
        }
        else if (select == 2)
        {
            strcpy(filename, "DAYSO2.IN");
        }
        else if (select == 3)
        {
            strcpy(filename, "DAYSO3.IN");
        }
        else
        {
            printf("Nhap ten file (.IN): ");
            scanf("%s", filename);
            strcat(filename, ".IN");
        }
        FILE *file;
        file = fopen(filename, "r");
        if (file != NULL)
        {
            fscanf(file, "%d", &n);
            addListtoMatrixfromfile(A, n, filename);
            printf("Du lieu file %s:\n", filename);
            displayMatrix(A, n);
            printf("Ma tran da duoc luu vao A\n");
            fclose(file);
        }
    }

    while (1)
    {
        // Đưa ra MENU
        MENU3();

        setColor(14);
        printf("Nhap lua chon cua ban: ");
        scanf("%d", &select);
        printf("\n");
        setColor(8);
        if (select == 1)
        {
            goto Repeat;
        }
        else if (select == 2)
        {
            displayMatrix(A, n);
        }
        else if (select == 3)
        {
            deleteMiddle(A, n);
            displayMatrix(A, n);
            FILE *file = fopen("RESULT1.OUT", "a");
            fprintf(file, "Ma tran A sau khi xoa cot o vi tri gua ma tran!!\n");
            fclose(file);
            outputMatrix(A, n, "RESULT1.OUT");
        }
        else if (select == 4)
        {
            // Đưa ra MENU
            MENU5();

            setColor(14);
            printf("Nhap lua chon cua ban: ");
            scanf("%d", &select);
            printf("\n");
            setColor(8);
            if (select == 1)
            {
                have_matrix_B = true;
                printf("Nhap ma tran B 1x%d:\n", n);
                B = createList(n);
            }
            else
            {
                char filename[20];
                // Đưa ra MENU
                MENU4();
                setColor(14);
                printf("Nhap lua chon cua ban: ");
                scanf("%d", &select);
                printf("\n");
                setColor(8);

                if (select == 1)
                {
                    strcpy(filename, "DAYSO_B1.IN");
                }
                else if (select == 2)
                {
                    strcpy(filename, "DAYSO_B2.IN");
                }
                else if (select == 3)
                {
                    strcpy(filename, "DAYSO_B3.IN");
                }
                else
                {
                    printf("Nhap ten file (.IN): ");
                    scanf("%s", filename);
                    strcat(filename, ".IN");
                }
                B = createHeaderNode();
                bool check = createListfromFile(B, n, filename);
                if (check)
                {
                    have_matrix_B = true;
                    displayList(B, n);
                    printf("Ma tran da duoc luu vao B\n");
                }
            }
        }
        else if (select == 5 || select == 6)
        {
            if (!is_square_matrix(A, n))
                printf("!! Ma tran A chua phai ma tran vuong (nhan phim 3 de xoa cot)\n");
            if (!have_matrix_B)
                printf("!! Ban chua nhap ma tran B (nhan phim 4 de nhap ma tran B)\n");
            if (have_matrix_B && is_square_matrix(A, n))
            {
                if (select == 5)
                {
                    displayEquations(A, B, n);
                }
                else if (select == 6)
                {
                    Matrix TempMatrix = createMatrix(MAX_SIZE); // Matrix temporary
                    createMatrixZero(TempMatrix, n);            // Tạo ma trận chứa các phần tử bằng không
                    List TempList = createListZero(n);          // // Tạo list tepmorary chứa các phần tử bằng không
                    // Đưa ra MENU
                    MENU6();

                    setColor(14);
                    printf("Nhap lua chon cua ban: ");
                    scanf("%d", &select);
                    printf("\n");
                    setColor(8);
                    if (select == 1)
                    {
                        FILE *file = fopen("RESULT2.OUT", "a");
                        fprintf(file, "\nPHUONG PHAP KRAME:\n");
                        fclose(file);
                        List N0 = createListZero(n);
                        Krame(n, A, TempMatrix, B, N0);
                    }
                    else if (select == 2)
                    {
                        FILE *file = fopen("RESULT2.OUT", "a");
                        fprintf(file, "\nPHUONG PHAP GAUSS:\n");
                        fclose(file);
                        List N0 = createListZero(n);
                        copyMatrix(TempMatrix, A, n);
                        copyList(TempList, B, n);
                        int check = Gauss(n, TempMatrix, TempList, N0);
                        if (check == 2)
                        {
                            printf("Nghiem cua he phuong trinh:\n");
                            displayN0(N0, n);
                            FILE *file = fopen("RESULT2.OUT", "a");
                            fprintf(file, "Nghiem cua he phuong trinh:\n");
                            fclose(file);
                            outputResults(N0, n, "RESULT2.OUT");
                        }
                        else if (check == 0)
                        {
                            printf("He phuong trinh vo nghiem!!\n");
                            FILE *file = fopen("RESULT2.OUT", "a");
                            fprintf(file, "He phuong trinh vo nghiem!!\n");
                            fclose(file);
                        }
                        else
                        {
                            printf("He phuong trinh vo so nghiem!!\n");
                            FILE *file = fopen("RESULT2.OUT", "a");
                            fprintf(file, "He phuong trinh vo so nghiem!!\n");
                            fclose(file);
                        }
                        fclose(file);
                    }
                    else if (select == 3)
                    {
                        FILE *file = fopen("RESULT2.OUT", "a");
                        fprintf(file, "\nPHUONG PHAP GAUSS-SIEDEL:\n");
                        fclose(file);
                        copyMatrix(TempMatrix, A, n); // Sao chép ma trận A cho ma trận TempMatrix
                        copyList(TempList, B, n);     // Sao chép ma trận B cho ma trận TempList
                        printf("Nhap nghiem ban dau:\n");
                        List N0 = createList(n);
                        bool check = check_Matrix(TempMatrix, TempList, n);
                        if (check)
                        {
                            if (Gauss_Siedel(n, TempMatrix, TempList, N0))
                            {
                                printf("Nghiem cua he phuong trinh:\n");
                                displayN0(N0, n);
                                FILE *file = fopen("RESULT2.OUT", "a");
                                fprintf(file, "Nghiem cua he phuong trinh:\n");
                                fclose(file);
                                outputResults(N0, n, "RESULT2.OUT");
                            }
                            else
                            {
                                printf("He phuong trinh khong the giai bang phuong phap Gauss_Siedel!\n");
                                FILE *file = fopen("RESULT2.OUT", "a");
                                fprintf(file, "He phuong trinh khong the giai bang phuong phap Gauss_Siedel!\n");
                                fclose(file);
                            }
                        }
                        else
                        {
                            printf("He phuong trinh khong the giai bang phuong phap Gauss_Siedel!\n");
                            FILE *file = fopen("RESULT2.OUT", "a");
                            fprintf(file, "He phuong trinh khong the giai bang phuong phap Gauss_Siedel!\n");
                            fclose(file);
                        }
                    }
                    else if (select == 4)
                    {
                        FILE *file = fopen("RESULT2.OUT", "a");
                        fprintf(file, "\nPHUONG PHAP GIAM DU:\n");
                        fclose(file);
                        printf("Nhap nghiem ban dau:\n");
                        List N0 = createList(n);
                        copyMatrix(TempMatrix, A, n);
                        copyList(TempList, B, n);
                        change_Matrix(TempMatrix, TempList, n);
                        if (Giam_du(n, TempMatrix, TempList, N0))
                        {
                            printf("Nghiem cua he phuong trinh:\n");
                            displayN0(N0, n);
                            FILE *file = fopen("RESULT2.OUT", "a");
                            fprintf(file, "Nghiem cua he phuong trinh:\n");
                            fclose(file);
                            outputResults(N0, n, "RESULT2.OUT");
                        }
                        else
                        {
                            printf("Phuong trinh khong the giai bang phuong phap Giam Du!");
                            FILE *file = fopen("RESULT2.OUT", "a");
                            fprintf(file, "Phuong trinh khong the giai bang phuong phap Giam Du!\n");
                            fclose(file);
                        }
                    }
                }
            }
        }
        else if (select == 7)
        {
            printf("Da thoat chuong trinh!!\n");
            break;
        }
        else
        {
            printf("Lua chon cua ban khong hop le!!\n");
        }
    }
    return 0;
}

Matrix createMatrix(int max_size)
{ // Tạo ma trận
    Matrix mt = malloc(sizeof(struct ArrayList));
    mt->max_size = max_size;
    mt->PointToHeaderNode = malloc((max_size + 1) * sizeof(struct Node));
    return mt;
}

List createNode(float data)
{ // Tạo Node
    List lt = malloc(sizeof(struct Node));
    lt->data = data;
    lt->next = NULL;
    lt->prev = NULL;
    return lt;
}

List createHeaderNode()
{ // Tạo HeaderNode
    List headerNode = malloc(sizeof(struct Node));
    headerNode->next = NULL;
    headerNode->prev = NULL;
    return headerNode;
}

List addNodetoList(int n)
{ // Thêm Node vào List
    List headerNode = createHeaderNode();
    Position p = headerNode;
    for (int i = 1; i <= n + 1; i++)
    {
        float x;
        scanf("%f", &x);
        List newNode = createNode(x);
        newNode->next = p->next;
        newNode->prev = p;
        p->next = newNode;
        if (newNode->next != NULL)
        {
            newNode->next->prev = newNode;
        }
        p = p->next;
    }
    return headerNode;
}

void addListtoMatrix(Matrix A, int n)
{ // Thêm list vào Matrix
    for (int i = 1; i <= n; i++)
    {
        List headerNode = createHeaderNode();
        headerNode = addNodetoList(n);
        A->PointToHeaderNode[i] = headerNode;
    }
}

List createList(int n)
{
    return addNodetoList(n - 1);
}

List createListZero(int n)
{
    List headerNode = createHeaderNode();
    Position p = headerNode;
    for (int i = 1; i <= n; i++)
    {
        List newNode = createNode(0);
        newNode->next = p->next;
        newNode->prev = p;
        p->next = newNode;
        if (newNode->next != NULL)
        {
            newNode->next->prev = newNode;
        }
        p = p->next;
    }
    return headerNode;
}

void createMatrixZero(Matrix Temp, int n)
{
    for (int i = 1; i <= n; i++)
    {
        List headerNode = createHeaderNode();
        headerNode = createListZero(n);
        Temp->PointToHeaderNode[i] = headerNode;
    }
}

void copyMatrix(Matrix Temp, Matrix A, int n)
{
    for (int i = 1; i <= n; i++)
    {
        Position p = A->PointToHeaderNode[i]->next;
        Position q = Temp->PointToHeaderNode[i]->next;
        while (p != NULL)
        {
            q->data = p->data;
            p = p->next;
            q = q->next;
        }
    }
}

void copyList(List Temp, List B, int n)
{
    Position p = B->next;
    Position q = Temp->next;
    while (p != NULL)
    {
        q->data = p->data;
        p = p->next;
        q = q->next;
    }
}

void deleteMiddle(Matrix A, int n)
{
    if (is_square_matrix(A, n))
    {
        printf("Ban khong the xoa, ma tran A da la ma tran vuong!\n");
        return;
    }
    for (int i = 1; i <= n; i++)
    {
        Position p = A->PointToHeaderNode[i];
        for (int j = 1; j <= (n + 1) / 2 + 1; j++)
        {
            p = p->next;
        }
        p->prev->next = p->next;
        p->next->prev = p->prev;
        free(p);
    }
    printf("Ma tran A sau khi xoa cot o vi tri gua ma tran!!\n");
}

List getNodeFromMarix(Matrix A, int x, int y)
{
    Position p = A->PointToHeaderNode[x];
    for (int i = 1; i <= y; i++)
    {
        p = p->next;
    }
    return p;
}

List getNodeFromList(List headerNode, int x)
{
    for (int i = 1; i <= x; i++)
    {
        headerNode = headerNode->next;
    }
    return headerNode;
}

void displayMatrix(Matrix A, int n)
{
    int m = n;
    printf("Ma tran A:\n");
    if (!is_square_matrix(A, n))
        m = n + 1;
    printf("//");
    for (int i = 1; i <= m; i++)
        printf("===========");
    printf("\\\\\n");

    for (int i = 1; i <= n; i++)
    {
        printf("||");
        Position p = A->PointToHeaderNode[i]->next;
        while (p != NULL)
        {
            printf("%10.3f ", p->data);
            p = p->next;
        }
        printf("||\n");
    }

    printf("\\\\");
    for (int i = 1; i <= m; i++)
        printf("===========");
    printf("//\n");
}

void displayList(List headerNode, int n)
{
    printf("//");
    for (int i = 1; i <= n; i++)
        printf("===========");
    printf("\\\\\n");

    printf("||");
    headerNode = headerNode->next;
    while (headerNode != NULL)
    {
        printf("%10.3f ", headerNode->data);
        headerNode = headerNode->next;
    }
    printf("||\n");

    printf("\\\\");
    for (int i = 1; i <= n; i++)
        printf("===========");
    printf("//\n");
}

void displayEquations(Matrix A, List B, int n)
{
    printf("//");
    for (int i = 1; i <= n + 1; i++)
        printf("===========");
    printf("\\\\\n");

    Position q = B->next;
    for (int i = 1; i <= n; i++)
    {
        printf("||");
        Position p = A->PointToHeaderNode[i]->next;
        while (p != NULL)
        {
            printf("%10.3f ", p->data);
            p = p->next;
        }
        printf("|%9.3f ||\n", q->data);
        q = q->next;
    }

    printf("\\\\");
    for (int i = 1; i <= n + 1; i++)
        printf("===========");
    printf("//\n");
}

void displayStep_Giamdu(List N0, List r)
{
    N0 = N0->next;
    while (N0 != NULL)
    {
        printf("%.3f\t", N0->data);
        N0 = N0->next;
    }
    printf("|\t");
    r = r->next;
    while (r != NULL)
    {
        printf("%.3f\t", r->data);
        r = r->next;
    }
    printf("\n");
}

void displayN0(List N0, int n)
{ // In ra nghiệm của phương trình
    printf("    //");
    for (int i = 1; i <= n; i++)
        printf("===========");
    printf("\\\\\n");

    printf("X = ||");
    N0 = N0->next;
    while (N0 != NULL)
    {
        printf("%10.3f ", N0->data);
        N0 = N0->next;
    }
    printf("||\n");

    printf("    \\\\");
    for (int i = 1; i <= n; i++)
        printf("===========");
    printf("//\n");
}

void Swap(float *a, float *b)
{
    float t = *a;
    *a = *b;
    *b = t;
}

void Swap_row(Matrix A, List B, int n, int row1, int row2)
{
    List t = A->PointToHeaderNode[row1];
    A->PointToHeaderNode[row1] = A->PointToHeaderNode[row2];
    A->PointToHeaderNode[row2] = t;

    Swap(&getNodeFromList(B, row1)->data, &getNodeFromList(B, row2)->data);
}

bool check_Matrix(Matrix A, List B, int n)
{
    List idx = createListZero(n);
    List maxidx = createListZero(n);
    List pointList_idx = idx->next;
    List pointList_maxidx = maxidx->next;
    for (int i = 1; i <= n; i++)
    {
        pointList_maxidx->data = fabs(getNodeFromMarix(A, i, 1)->data);
        pointList_idx->data = 1;
        for (int j = 2; j <= n; j++)
        {
            if (pointList_maxidx->data < fabs(getNodeFromMarix(A, i, j)->data))
            {
                pointList_maxidx->data = fabs(getNodeFromMarix(A, i, j)->data);
                pointList_idx->data = j;
            }
        }
        pointList_maxidx = pointList_maxidx->next;
        pointList_idx = pointList_idx->next;
    }
    pointList_idx = idx->next;
    for (int i = 1; i <= n; i++)
    {
        if (pointList_idx->data != i)
        {
            Swap_row(A, B, n, i, pointList_idx->data);
            if (pointList_idx->data == getNodeFromList(idx, pointList_idx->data)->data)
                return 0;
            Swap(&pointList_idx->data, &getNodeFromList(idx, pointList_idx->data)->data);
        }
        pointList_idx = pointList_idx->next;
    }
    return 1;
}

bool Gauss_Siedel(int n, Matrix A, List B, List N0)
{
    List N1 = createListZero(n);
    bool check;
    int res = 0;
    do
    {
        check = false;
        res++;
        List pointList_N1 = N1->next;
        List pointList_B = B->next;
        List pointList_N0 = N0->next;
        for (int i = 1; i <= n; i++)
        {
            float s = 0;
            List pointListTemp_N0 = N0->next;
            for (int j = 1; j <= n; j++)
            {
                if (i != j)
                {
                    s += getNodeFromMarix(A, i, j)->data * pointListTemp_N0->data;
                }
                pointListTemp_N0 = pointListTemp_N0->next;
            }
            pointList_N1->data = (pointList_B->data - s) / getNodeFromMarix(A, i, i)->data;
            if (fabs(pointList_N1->data - pointList_N0->data) >= esp)
                check = true;
            if (res == MAX_REPE)
                return 0;
            pointList_N1 = pointList_N1->next;
            pointList_B = pointList_B->next;
            pointList_N0 = pointList_N0->next;
        }
        pointList_N1 = N1->next;
        pointList_N0 = N0->next;
        printf("Buoc %d: \t", res);
        for (int i = 1; i <= n; i++)
        {
            pointList_N0->data = pointList_N1->data;
            printf("%10.3f", pointList_N0->data);
            pointList_N1 = pointList_N1->next;
            pointList_N0 = pointList_N0->next;
        }
        printf("\n");
    } while (check);
    return true;
}

int Gauss(int n, Matrix A, List B, List N0)
{
    printf("Phuong trinh ban dau:\n");
    displayEquations(A, B, n);
    printf("Cac buoc thuc hien:\n");
    for (int i = 1; i <= n - 1; i++)
    {
        if (getNodeFromMarix(A, i, i)->data == 0)
        {
            int check = 0;
            for (int j = i + 1; j <= n; j++)
            {
                if (getNodeFromMarix(A, j, i)->data != 0)
                {
                    for (int k = 1; k <= n; k++)
                    {
                        Swap(&getNodeFromMarix(A, i, j)->data, &getNodeFromMarix(A, j, k)->data);
                    }
                    Swap(&getNodeFromList(B, i)->data, &getNodeFromList(B, j)->data);

                    check++;
                    break;
                }
            }
            if (check == 0)
                return 0;
        }
        for (int j = i + 1; j <= n; j++)
        {
            float h = -getNodeFromMarix(A, j, i)->data / getNodeFromMarix(A, i, i)->data;
            for (int k = i; k <= n; k++)
                getNodeFromMarix(A, j, k)->data += h * getNodeFromMarix(A, i, k)->data;
            getNodeFromList(B, j)->data += h * getNodeFromList(B, i)->data;
        }
        printf("\nBuoc %d\n", i);
        displayEquations(A, B, n);
    }

    for (int i = n; i > 0; i--)
    {
        float s = 0;
        if (getNodeFromMarix(A, i, i)->data == 0)
        {
            if (getNodeFromList(B, i)->data == 0)
                return 1;
            else
                return 0;
        }
        for (int j = i; j <= n; j++)
            s += getNodeFromMarix(A, i, j)->data * getNodeFromList(N0, j)->data;
        getNodeFromList(N0, i)->data = (getNodeFromList(B, i)->data - s) / getNodeFromMarix(A, i, i)->data;
    }
    return 2;
}

float det(int n, Matrix A)
{
    float res = 1;
    int count = 0;
    for (int i = 1; i <= n - 1; i++)
    {
        if (getNodeFromMarix(A, i, i)->data == 0)
        {
            int check = 0;
            for (int j = i + 1; j <= n; j++)
            {
                if (getNodeFromMarix(A, j, i)->data != 0)
                {
                    for (int k = 1; k <= n; k++)
                    {
                        Swap(&getNodeFromMarix(A, i, j)->data, &getNodeFromMarix(A, j, k)->data);
                    }
                    count++;
                    check++;
                    break;
                }
            }
            if (check == 0)
                return 0;
        }
        for (int j = i + 1; j <= n; j++)
        {
            float h = -getNodeFromMarix(A, j, i)->data / getNodeFromMarix(A, i, i)->data;
            for (int k = i; k <= n; k++)
                getNodeFromMarix(A, j, k)->data += h * getNodeFromMarix(A, i, k)->data;
        }
        res *= getNodeFromMarix(A, i, i)->data;
    }
    if (count % 2 == 0)
        return res * getNodeFromMarix(A, n, n)->data;
    else
        return -res * getNodeFromMarix(A, n, n)->data;
}

void Krame(int n, Matrix A, Matrix Temp, List B, List N0)
{
    copyMatrix(Temp, A, n);
    float d = det(n, Temp);
    if (d == 0)
    {
        printf("Phuong trinh khong the giai bang phuong phap Krame\n");
        FILE *file = fopen("RESULT2.OUT", "a");
        fprintf(file, "Phuong trinh khong the giai bang phuong phap Krame\n");
        fclose(file);
        return;
    }

    List pointList_N0 = N0->next;
    for (int i = 1; i <= n; i++)
    {
        copyMatrix(Temp, A, n);
        List pointList_B = B->next;
        for (int j = 1; j <= n; j++)
        {
            getNodeFromMarix(Temp, j, i)->data = pointList_B->data;
            pointList_B = pointList_B->next;
        }

        pointList_N0->data = det(n, Temp) / d;
        pointList_N0 = pointList_N0->next;
    }
    // In ra nghiệm hệ phương trinh
    printf("Nghiem cua he phuong trinh:\n");
    displayN0(N0, n);
    FILE *file = fopen("RESULT2.OUT", "a");
    fprintf(file, "Nghiem cua he phuong trinh:\n");
    fclose(file);
    outputResults(N0, n, "RESULT2.OUT");
}

void change_Matrix(Matrix A, List B, int n)
{
    List idx = createListZero(n);
    List maxidx = createListZero(n);
    List pointList_idx = idx->next;
    List pointList_maxidx = maxidx->next;
    for (int i = 1; i <= n; i++)
    {
        pointList_maxidx->data = fabs(getNodeFromMarix(A, i, 1)->data);
        pointList_idx->data = 1;
        for (int j = 2; j <= n; j++)
        {
            if (pointList_maxidx->data < fabs(getNodeFromMarix(A, i, j)->data))
            {
                pointList_maxidx->data = fabs(getNodeFromMarix(A, i, j)->data);
                pointList_idx->data = j;
            }
        }
        pointList_maxidx = pointList_maxidx->next;
        pointList_idx = pointList_idx->next;
    }
    pointList_idx = idx->next;
    for (int i = 1; i <= n; i++)
    {
        if (pointList_idx->data != i)
        {
            Swap_row(A, B, n, i, pointList_idx->data);
            Swap(&pointList_idx->data, &getNodeFromList(idx, pointList_idx->data)->data);
        }
        pointList_idx = pointList_idx->next;
    }
}

bool Giam_du(int n, Matrix A, List B, List N0)
{
    List pointList_B;
    List pointList_r;
    List pointList_N0;
    pointList_B = B->next;
    for (int i = 1; i <= n; i++)
    {
        float t = getNodeFromMarix(A, i, i)->data;
        if (t == 0)
            return 0;
        for (int j = 1; j <= n; j++)
        {
            getNodeFromMarix(A, i, j)->data /= t;
        }
        pointList_B->data /= t;
        pointList_B = pointList_B->next;
    }

    List r = createListZero(n);
    pointList_r = r->next;
    pointList_B = B->next;
    // Tinh so du ban dau
    for (int i = 1; i <= n; i++)
    {
        pointList_r->data = pointList_B->data;
        pointList_N0 = N0->next;
        for (int j = 1; j <= n; j++)
        {
            pointList_r->data -= getNodeFromMarix(A, i, j)->data * pointList_N0->data;
            pointList_N0 = pointList_N0->next;
        }
        pointList_B = pointList_B->next;
        pointList_r = pointList_r->next;
    }
    // In ra các bước thực hiện
    printf("Cac buoc thuc hien:\n");
    printf("Buoc 0: \t");
    displayStep_Giamdu(N0, r);

    int res = 0;
    bool check;
    do
    {
        pointList_r = r->next;
        res++;
        check = false; // Dieu kien lap
        // Tim max {|r[i]|}
        float max = fabs(getNodeFromList(r, 1)->data);
        pointList_r = pointList_r->next;
        int idx = 1;
        for (int i = 2; i <= n; i++)
        {
            if (max < fabs(pointList_r->data))
            {
                max = fabs(pointList_r->data);
                idx = i;
            }
            pointList_r = pointList_r->next;
        }
        getNodeFromList(N0, idx)->data += getNodeFromList(r, idx)->data;
        // Tinh lai r[i] kiem tra kha nang lap tiep theo
        pointList_r = r->next;
        float d = getNodeFromList(r, idx)->data;
        for (int i = 1; i <= n; i++)
        {
            pointList_r->data -= getNodeFromMarix(A, i, idx)->data * d;
            if (fabs(pointList_r->data) >= esp)
                check = true;
            pointList_r = pointList_r->next;
        }
        if (res == MAX_REPE)
            return 0;
        // In ra các bước thực hiện
        printf("Buoc %d: \t", res);
        displayStep_Giamdu(N0, r);
    } while (check);
    return 1;
}

void addListtoMatrixfromfile(Matrix A, int n, char *filename)
{
    FILE *file;
    file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("File khong ton tai!\n");
        return;
    }
    fscanf(file, "%d", &n);
    for (int i = 1; i <= n; i++)
    {
        List headerNode = createHeaderNode();
        Position p = headerNode;
        for (int j = 1; j <= n + 1; j++)
        {
            float x;
            fscanf(file, "%f", &x);
            List newNode = createNode(x);
            newNode->next = p->next;
            newNode->prev = p;
            p->next = newNode;
            if (newNode->next != NULL)
            {
                newNode->next->prev = newNode;
            }
            p = p->next;
        }
        A->PointToHeaderNode[i] = headerNode;
    }
    fclose(file);
}

bool createListfromFile(List B, int n, char *filename)
{
    FILE *file;
    file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("File khong ton tai!\n");
        return 0;
    }
    int check;
    fscanf(file, "%d", &check);
    if (check != n)
    {
        printf("Ma tran B khong hop le!\n");
        return 0;
    }
    Position p = B;
    for (int i = 1; i <= n; i++)
    {
        float x;
        fscanf(file, "%f", &x);
        List newNode = createNode(x);
        newNode->next = p->next;
        newNode->prev = p;
        p->next = newNode;
        if (newNode->next != NULL)
        {
            newNode->next->prev = newNode;
        }
        p = p->next;
    }
    fclose(file);
    return 1;
}

void outputResults(List N0, int n, char *filename)
{
    FILE *file;
    file = fopen(filename, "a");
    if (file == NULL)
    {
        printf("File khong ton tai!\n");
        return;
    }
    fprintf(file, "    //");
    for (int i = 1; i <= n; i++)
        fprintf(file, "===========");
    fprintf(file, "\\\\\n");

    fprintf(file, "X = ||");
    N0 = N0->next;
    while (N0 != NULL)
    {
        fprintf(file, "%10.3f ", N0->data);
        N0 = N0->next;
    }
    fprintf(file, "||\n");

    fprintf(file, "    \\\\");
    for (int i = 1; i <= n; i++)
        fprintf(file, "===========");
    fprintf(file, "//\n");
    fclose(file);
}

void outputMatrix(Matrix A, int n, char *filename)
{
    int m = n;
    FILE *file = fopen("RESULT1.OUT", "a");
    fprintf(file, "Ma tran A:\n");
    if (!is_square_matrix(A, n))
        m = n + 1;
    fprintf(file, "//");
    for (int i = 1; i <= m; i++)
        fprintf(file, "===========");
    fprintf(file, "\\\\\n");

    for (int i = 1; i <= n; i++)
    {
        fprintf(file, "||");
        Position p = A->PointToHeaderNode[i]->next;
        while (p != NULL)
        {
            fprintf(file, "%10.3f ", p->data);
            p = p->next;
        }
        fprintf(file, "||\n");
    }

    fprintf(file, "\\\\");
    for (int i = 1; i <= m; i++)
        fprintf(file, "===========");
    fprintf(file, "//\n");
    fclose(file);
}

bool is_square_matrix(Matrix A, int n)
{
    Position p = A->PointToHeaderNode[1]->next;
    int res = 0;
    while (p != NULL)
    {
        res++;
        p = p->next;
    }
    return res == n;
}

void setColor(int textColor)
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, textColor);
}

void INTRO()
{
    // Đặt màu sắc thông tin
    setColor(11);
    printf("\t//======================================================\\\\ \n");
    setColor(11);
    printf("\t||");
    setColor(10);
    printf("\t\tTRUONG DAI HOC BACH KHOA\t\t");
    setColor(11);
    printf("||\n");
    setColor(11);
    printf("\t||");
    setColor(10);
    printf("\t\tKHOA CONG NGHE THONG TIN\t\t");
    setColor(11);
    printf("||\n");
    setColor(11);
    printf("\t||======================================================||\n");
    setColor(11);
    printf("\t||");
    setColor(5);
    printf("\t\tDE TAI LAP TRINH TINH TOAN\t\t");
    setColor(11);
    printf("||\n");
    setColor(11);
    printf("\t||======================================================||\n");
    setColor(11);
    printf("\t||");
    setColor(10);
    printf("\tTen de tai: Giai he phuong trinh AX = B\t\t");
    setColor(11);
    printf("||\n");
    setColor(11);
    printf("\t||");
    setColor(10);
    printf("\tNguoi huong dan: Nguyen Van Hieu\t\t");
    setColor(11);
    printf("||\n");
    setColor(11);
    printf("\t||");
    setColor(10);
    printf("\tSinh vien thuc hien:\t\t\t\t");
    setColor(11);
    printf("||\n");
    setColor(11);
    printf("\t||");
    setColor(10);
    printf("\tTen sinh vien 1: Ngo Van Loc\t\t\t");
    setColor(11);
    printf("||\n");
    setColor(11);
    printf("\t||");
    setColor(10);
    printf("\tTen sinh vien 2: Ha Duc Kien\t\t\t");
    setColor(11);
    printf("||\n");
    setColor(11);
    printf("\t||");
    setColor(10);
    printf("\tLop: 23T_DT1\t\t\t\t\t");
    setColor(11);
    printf("||\n");
    setColor(11);
    printf("\t||");
    setColor(10);
    printf("\tLop hoc phan: 23.16A\t\t\t\t");
    setColor(11);
    printf("||\n");
    setColor(11);
    printf("\t\\\\======================================================//\n");
    printf("\n\n");

    // Đặt lại màu sắc về mặc định
    setColor(7); // Màu trắng mặc định
}

void MENU1()
{
    setColor(11);
    printf("=======================");
    setColor(5);
    printf(" << MENU >> ");
    setColor(11);
    printf("=======================\n");
    setColor(8);
    printf("1. Nhap ma tran A thu cong\n");
    printf("2. Nhap ma tran A bang file\n");
    setColor(11);
    printf("==========================================================\n");
}

void MENU2()
{
    setColor(11);
    printf("============= ");
    setColor(5);
    printf("<< FILE >>");
    setColor(11);
    printf(" =============\n");
    setColor(8);
    printf("File co san:\n");
    printf("1. DAYSO1.IN\n");
    printf("2. DAYSO2.IN\n");
    printf("3. DAYSO3.IN\n");
    printf("File tu nhap:\n");
    printf("4. Nhap ten file (.IN)\n");
    setColor(11);
    printf("======================================\n");
}

void MENU3()
{
    setColor(11);
    printf("\n======================= ");
    setColor(5);
    printf("<< MENU >>");
    setColor(11);
    printf(" =======================\n");
    setColor(8);
    printf("1. Nhap lai ma tran A\n");
    printf("2. In ra ma tran A\n");
    printf("3. Xoa 1 cot o vi tri giua ma tran A\n");
    printf("4. Nhap ma tran B \n");
    printf("5. In ra he phuong trinh Ax = B\n");
    printf("6. Giai he phuong trinh Ax = B\n");
    printf("7. Thoat chuong trinh!!\n");
    setColor(11);
    printf("==========================================================\n");
}

void MENU4()
{
    setColor(11);
    printf("============= ");
    setColor(5);
    printf("<< FILE >>");
    setColor(11);
    printf(" =============\n");
    setColor(8);
    printf("File co san:\n");
    printf("1. DAYSO_B1.IN\n");
    printf("2. DAYSO_B2.IN\n");
    printf("3. DAYSO_B3.IN\n");
    printf("File tu nhap:\n");
    printf("4. Nhap ten file (.IN)\n");
    setColor(11);
    printf("======================================\n");
}

void MENU5()
{
    setColor(11);
    printf("\n======================= ");
    setColor(5);
    printf("<< MENU >>");
    setColor(11);
    printf(" =======================\n");
    setColor(8);
    printf("1. Nhap ma tran B thu cong\n");
    printf("2. Nhap ma tran B bang file\n");
    setColor(11);
    printf("==========================================================\n");
}

void MENU6()
{
    setColor(11);
    printf("\n======================= ");
    setColor(5);
    printf("<< MENU >>");
    setColor(11);
    printf(" =======================\n");
    setColor(8);
    printf("Cac phuong phap giai he phuong trinh Ax = B\n");
    printf("1. Phuong phap Krame\n");
    printf("2. Phuong phap Gauss\n");
    printf("3. Phuong phap Gauss_Siedel\n");
    printf("4. Phuong phap Giam du\n");
    setColor(11);
    printf("==========================================================\n");
}