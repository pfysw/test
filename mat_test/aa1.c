/*
 * aa1.c
 *
 *  Created on: Sep 29, 2020
 *      Author: Administrator
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <windows.h>
#include <omp.h>


int gettimeofday(struct timeval *tp, void *tzp)
{
    time_t clock;
    struct tm tm;
    SYSTEMTIME wtm;
    GetLocalTime(&wtm);
    tm.tm_year = wtm.wYear - 1900;
    tm.tm_mon = wtm.wMonth - 1;
    tm.tm_mday = wtm.wDay;
    tm.tm_hour = wtm.wHour;
    tm.tm_min = wtm.wMinute;
    tm.tm_sec = wtm.wSecond;
    tm.tm_isdst = -1;
    clock = mktime(&tm);
    tp->tv_sec = clock;
    tp->tv_usec = wtm.wMilliseconds * 1000;
    return (0);
}

#define w 1024

struct Matrix
{
    int width;
    int height;
    float *elements;
};

void matMul(float * M, float * N, float * P, int width) {
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < width; j++) {
            float sum = 0;
            for (int k = 0; k < width; k++) {
                float a = M[i * width + k];
                float b = N[k * width + j];
                sum += a * b;
            }
            P[i * width + j] = sum;
        }
    }
}

int mainsds() {
    int width = w;
    int height = w;

    float * m = (float *)malloc(width * height * sizeof(float));
    float * n = (float *)malloc(width * height * sizeof(float));
    float * p = (float *)malloc(width * height * sizeof(float));

    for (int i = 0; i < width * height; i++) {
        m[i] = 1.0;
        n[i] = 2.0;
    }

    struct timeval t1, t2;
    gettimeofday(&t1, NULL);
    double timeuse;

    matMul(m, n, p, w);

    gettimeofday(&t2, NULL);
    timeuse = t2.tv_sec - t1.tv_sec + (t2.tv_usec - t1.tv_usec) / 1000000.0;
    printf("Use1 Time:%f\n", timeuse);

    return 0;
}

void printMatrix(float* m_Matrix, int W, int H)
{
    for (int i = 0; i < W * H; ++i)
    {
        printf("%e ", m_Matrix[i]);
        if ((i+1) % W == 0 ) printf("\n");
    }
    printf("\n");
}

void main(void)
{
    int m_size = 8192;
//    int *mat1, *mat2;
//    int *result;
    // 用一位数组表示二维矩阵
//    mat1 = (int*)malloc(m_size * m_size * sizeof(int));
//    mat2 = (int*)malloc(m_size * m_size * sizeof(int));
//    result = (int*)malloc(m_size * m_size * sizeof(int));

    int width = m_size;
    int height = m_size;


    float *mat1 = (float *)malloc(width * height * sizeof(float));
    float * mat2 = (float *)malloc(width * height * sizeof(float));
    float * result = (float *)malloc(width * height * sizeof(float));

    // initialize
    for (int i = 0; i < m_size * m_size; i++) {
        mat1[i] = i%3;
    }
    for (int i = 0; i < m_size * m_size; i++) {
        int a = i/m_size;
        int b = i%m_size;
        mat2[b*m_size+a] = (float)(i%2);
    }
    printMatrix(mat1,2,2);
    printMatrix(mat2,2,2);

    struct timeval t1, t2;
    gettimeofday(&t1, NULL);
    double timeuse;

#pragma omp parallel for
    for (int r = 0; r < m_size; r++) {
        for (int c = 0; c < m_size; c++) {
            for (int n = 0; n < m_size; n++) {
               // result[r*m_size + c] += mat1[r*m_size + n] * mat2[n*m_size + c];
                result[r*m_size + c] += mat1[r*m_size + n] * mat2[c*m_size + n];
            }
        }
    }
    //matMul(mat1, mat2, result, w);
    printMatrix(result,2,2);
    gettimeofday(&t2, NULL);
    timeuse = t2.tv_sec - t1.tv_sec + (t2.tv_usec - t1.tv_usec) / 1000000.0;
    printf("Use Time:%fs\n", timeuse);
}
