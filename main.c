/*
 * main.c
 *
 *  Created on: 2017Äê10ÔÂ29ÈÕ
 *      Author: Administrator
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct Bitvec Bitvec;
//²âÊÔ²âÊÔ
void bittest(void)
{
	Bitvec *testBit;
	testBit = (Bitvec *)sqlite3BitvecCreate(1000000);
	sqlite3BitvecSet(testBit, 36);
	printf("hasbit? %d\n",sqlite3BitvecTestNotNull(testBit, 31));
	printf("hasbit? %d\n",sqlite3BitvecTestNotNull(testBit, 36));
	sqlite3BitvecDestroy(testBit);
}
int main()
{

	setbuf(stdout, NULL);
//	int a = 20;
//	int b = 5;
//	double c = 100.123456789;
//	printf("c: %*.*f\n",a,b,c);
//	printf("c: %*.*e\n",a,b,c);
//	printf("c: %*.*g\n",a,b,c);
	int a=123456789;
	a = a
			//dsafsf
			+1;
	char *b = "dfsf\n";
	printf("a: %,d\n",a);
	printf(b);
	bittest();
	//SequenceTest();
	BtreeTest();

	//my_printf("%d %d",a,b);
	//memtest();
	//Splitting_A_Linked_List();

}

