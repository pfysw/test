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

// ������Ծ����ά��  
int const M = 8192;
int const N = M;

extern void printMatrix(float* m_Matrix, int W, int H);

int main()
{
	// ����״̬����  
	cublasStatus_t status;
	
	// �� �ڴ� ��Ϊ��Ҫ����ľ��󿪱ٿռ�  
	float *h_A = (float*)malloc(N*M * sizeof(float));
	float *h_B = (float*)malloc(N*M * sizeof(float));

	// �� �ڴ� ��Ϊ��Ҫ����������ľ��󿪱ٿռ�  
	float *h_C = (float*)malloc(M*M * sizeof(float));



	// Ϊ����������Ԫ�ظ��� 0-10 ��Χ�ڵ������  
	for (int i = 0; i < N*M; i++) {
		h_A[i] = i%3;
		h_B[i] = i%2;

	}

	printMatrix(h_A,2,2);
	cout << endl;
	printMatrix(h_B,2,2);
	cudaSetDevice(0);
	/*
	** GPU ����������
	*/

	// ��������ʼ�� CUBLAS �����  
	cublasHandle_t handle;
	status = cublasCreate(&handle);

	if (status != CUBLAS_STATUS_SUCCESS)
	{
		if (status == CUBLAS_STATUS_NOT_INITIALIZED) {
			cout << "CUBLAS ����ʵ��������" << endl;
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

	// ͬ������  
	cudaThreadSynchronize();

	// ���ݽ�������˺����еĲ��������庬����ο������ֲᡣ  
	float a = 1; float b = 0;
	// ������ˡ��ú�����Ȼ���������������������  
	cublasSgemm(
		handle,    // blas �����   
		CUBLAS_OP_T,    // ���� A ���Բ���  
		CUBLAS_OP_T,    // ���� B ���Բ���  
		M,    // A, C ������   
		M,    // B, C ������  
		N,    // A �������� B ������  
		&a,    // ����ʽ�� �� ֵ  
		d_A,    // A ���Դ��еĵ�ַ  
		N,    // lda  
		d_B,    // B ���Դ��еĵ�ַ  
		M,    // ldb  
		&b,    // ����ʽ�� �� ֵ  
		d_C,    // C ���Դ��еĵ�ַ(�������)  
		M    // ldc  
	);

	// ͬ������  
	cudaThreadSynchronize();
	// �� �Դ� ��ȡ���������� �ڴ���ȥ  
	cublasGetVector(
		M*M,    //  Ҫȡ��Ԫ�صĸ���  
		sizeof(float),    // ÿ��Ԫ�ش�С  
		d_C,    // GPU ����ʼ��ַ
		1,    // ����Ԫ��֮��Ĵ洢���  
		h_C,    // ��������ʼ��ַ  
		1    // ����Ԫ��֮��Ĵ洢���  
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

	// �����ʹ�ù����ڴ�  
	free(h_A);
	free(h_B);
	free(h_C);
	cudaFree(d_A);
	cudaFree(d_B);
	cudaFree(d_C);

	// �ͷ� CUBLAS �����  
	cublasDestroy(handle);
	time_t z2 = time(NULL);
	printf("t2 %d\n", z2);
	printf("time %d\n", z2-z1);
	getchar();

	return 0;
}
