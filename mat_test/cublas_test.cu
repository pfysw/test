#include "cuda_runtime.h"  
#include "cublas_v2.h"  
#include <time.h>
#include <windows.h>
#include <iostream>  

using namespace std;

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

// 定义测试矩阵的维度  
int const M = 8192;
int const N = M;

extern void printMatrix(float* m_Matrix, int W, int H);

int main()
{
	// 定义状态变量  
	cublasStatus_t status;
	
	// 在 内存 中为将要计算的矩阵开辟空间  
	float *h_A = (float*)malloc(N*M * sizeof(float));
	float *h_B = (float*)malloc(N*M * sizeof(float));

	// 在 内存 中为将要存放运算结果的矩阵开辟空间  
	float *h_C = (float*)malloc(M*M * sizeof(float));



	// 为待运算矩阵的元素赋予 0-10 范围内的随机数  
	for (int i = 0; i < N*M; i++) {
		h_A[i] = i%3;
		h_B[i] = i%2;

	}

	printMatrix(h_A,2,2);
	cout << endl;
	printMatrix(h_B,2,2);
	cudaSetDevice(0);
	/*
	** GPU 计算矩阵相乘
	*/

	// 创建并初始化 CUBLAS 库对象  
	cublasHandle_t handle;
	status = cublasCreate(&handle);

	if (status != CUBLAS_STATUS_SUCCESS)
	{
		if (status == CUBLAS_STATUS_NOT_INITIALIZED) {
			cout << "CUBLAS 对象实例化出错" << endl;
		}
		getchar();
		return EXIT_FAILURE;
	}

    struct timeval t1, t2;
    gettimeofday(&t1, NULL);
    double timeuse;

	time_t z1 = time(NULL);
	printf("t1 %d\n", z1);

	cudaEvent_t start_device, stop_device;
	float time_device;
	cudaEventCreate(&start_device);
	cudaEventCreate(&stop_device);
	cudaEventRecord(start_device, 0);
	clock_t start_devence = clock();

	float *d_A, *d_B, *d_C, *d_D;
	cudaMalloc((void**)&d_A, N*M * sizeof(float));
	cudaMalloc((void**)&d_B, N*M * sizeof(float));
	cudaMalloc((void**)&d_C, N*M * sizeof(float));
	cudaMalloc((void**)&d_D, N*M * sizeof(float));

	cublasSetVector(N*M,sizeof(float),h_A,1,d_A,1);
	cublasSetVector(N*M,sizeof(float),h_B,1,d_B,1);

	// 同步函数  
	cudaThreadSynchronize();

	// 传递进矩阵相乘函数中的参数，具体含义请参考函数手册。  
	float a = 1; float b = 0;
	// 矩阵相乘。该函数必然将数组解析成列优先数组  
	cublasSgemm(
		handle,    // blas 库对象   
		CUBLAS_OP_T,    // 矩阵 A 属性参数  
		CUBLAS_OP_T,    // 矩阵 B 属性参数  
		M,    // A, C 的行数   
		M,    // B, C 的列数  
		N,    // A 的列数和 B 的行数  
		&a,    // 运算式的 α 值  
		d_A,    // A 在显存中的地址  
		N,    // lda  
		d_B,    // B 在显存中的地址  
		M,    // ldb  
		&b,    // 运算式的 β 值  
		d_C,    // C 在显存中的地址(结果矩阵)  
		M    // ldc  
	);

	// 同步函数  
	cudaThreadSynchronize();
	// 从 显存 中取出运算结果至 内存中去  
	cublasGetVector(
		M*M,    //  要取出元素的个数  
		sizeof(float),    // 每个元素大小  
		d_C,    // GPU 端起始地址
		1,    // 连续元素之间的存储间隔  
		h_C,    // 主机端起始地址  
		1    // 连续元素之间的存储间隔  
	);

	for (int i = 0; i < 4; i++) {
		h_C[i] = h_C[i*M];
	}
	printMatrix(h_C,2,2);


	cudaEventRecord(stop_device, 0);
	cudaEventSynchronize(stop_device);
	cudaEventElapsedTime(&time_device, start_device, stop_device);
	cudaEventDestroy(start_device);
	cudaEventDestroy(stop_device);
	cout << "gputime=" << time_device << "ms" << endl;
	cout << "devence=" << (double)(clock() - start_devence) / 1 << "ms" << endl;

    gettimeofday(&t2, NULL);
    timeuse = t2.tv_sec - t1.tv_sec + (t2.tv_usec - t1.tv_usec) / 1000000.0;
    printf("Use Time:%f\n", timeuse);

	// 清理掉使用过的内存  
	free(h_A);
	free(h_B);
	free(h_C);
	cudaFree(d_A);
	cudaFree(d_B);
	cudaFree(d_C);

	// 释放 CUBLAS 库对象  
	cublasDestroy(handle);
	time_t z2 = time(NULL);
	printf("t2 %d\n", z2);
	printf("time %d\n", z2-z1);
	getchar();

	return 0;
}
