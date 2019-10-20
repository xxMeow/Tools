//
//  main.cpp
//  MatrixOperations
//
//  Created by Mingxian Xiao on 20/10/2019.
//  Copyright © 2019 XMX. All rights reserved.
//

#include <iostream>

void errPrint(std::string s) { printf("ERR: %s\n", s.c_str()); }
int** matrixInit(int* values, int r, int c);
void matrixPrint(int** matrix, int r, int c);
int matrixDet(int** m, int r, int c);
int** matrixProduct(int** a, int aR, int aC, int** b, int bR, int bC);
    
int main(int argc, const char * argv[])
{
    /** Test Matrix: A **/
    int aR = 2;
    int aC = 3;
    int aValues[] = {
        1, 0, 2,
        -1, 3, 1
    };
    int** aMatrix = matrixInit(aValues, aR, aC);
    /** Test Matrix: B **/
    int bR = 3;
    int bC = 2;
    int bValues[] = {
        3, 1,
        2, 1,
        1, 0
    };
    int** bMatrix = matrixInit(bValues, bR, bC);
    /** Test Matrix: C **/
    int cR = 2;
    int cC = 2;
    int cValues[] = {
        2, 6,
        1, 4
    };
    int** cMatrix = matrixInit(cValues, cR, cC);
    /** Test Matrix: D **/
    int dR = 3;
    int dC = 3;
    int dValues[] = {
        2, 6, 3,
        1, 0, 2,
        5, 8, 4
    };
    int** dMatrix = matrixInit(dValues, dR, dC);
    
    /** Operation Choice **/
    int opNo = 1;
    switch (opNo)
    {
        case 1: /** Production **/
        {
            printf("A x B:\n");
            int** result = matrixProduct(aMatrix, aR, aC, bMatrix, bR, bC);
            matrixPrint(result, aR, bC);
        }
        break;
        case 2: /** Determinant **/
        {
            printf("det(C) = %d\n", matrixDet(cMatrix, cR, cC));
            printf("det(D) = %d\n", matrixDet(dMatrix, dR, dC));
        }
        break;
        case 3:
        {
            ;
        }
        break;
        default: /** Undefined Choices **/
        {
            errPrint("Undefined Operation No.");
        }
        break;
    }
    
    return 0;
}

int** matrixInit(int* values, int r, int c)
{
    int** m = (int**)malloc(sizeof(int*) * r);
    for (int i = 0; i < r; i ++) {
        *(m + i) = (int*)malloc(sizeof(int) * c);
    }
    
    int valueIndex = 0;
    for (int i = 0; i < r; i ++) {
        for (int j = 0; j < c; j ++) {
            m[i][j] = values[valueIndex];
            valueIndex ++;
        }
    }
    
    return m;
}

void matrixPrint(int** m, int r, int c)
{
    if (m == NULL) {
        errPrint("Null Matrix.");
        return;
    }
    
    for (int i = 0; i < r; i ++) {
        for (int j = 0; j < c; j ++) {
            printf(" %d ", m[i][j]);
        }
        printf("\n");
    }
}

int matrixDet(int** m, int r, int c)
{
    int n = r;
    if (c != n || (n != 2 && n != 3)) {
        errPrint("This Program Only Deals with 2x2 and 3x3 Matrixes.");
        return -1;
    }
    
    int det = 0;
    
    if (n == 2) {
        det += m[0][0] * m[1][1];
        det -= m[0][1] * m[1][0];
    }
    
    if (n == 3) {
        det += m[0][0] * m[1][1] * m[2][2];
        det += m[0][1] * m[1][2] * m[2][0];
        det += m[0][2] * m[1][0] * m[2][1];
        det -= m[0][0] * m[1][2] * m[2][1];
        det -= m[0][1] * m[1][0] * m[2][2];
        det -= m[0][2] * m[1][1] * m[2][0];
    }
    
    return det;
}

int** matrixProduct(int** a, int aR, int aC, int** b, int bR, int bC)
{
    if (aC != bR) {
        errPrint("Invalid Inputs.");
        return NULL;
    }
    int prodTimes = aC;
    
    int r = aR;
    int c = bC;
    
    int** result = (int**)malloc(sizeof(int*) * r);
    for (int i = 0; i < c; i ++) {
        *(result + i) = (int*)malloc(sizeof(int) * c);
    }
    
    for (int i = 0; i < r; i ++) {
        for (int j = 0; j < c; j ++) {
            *(*(result + i) + j) = 0;
            for (int k = 0; k < prodTimes; k ++) {
                *(*(result + i) + j) += a[i][k] * b[k][j];
            }
        }
    }
    
    return result;
}
