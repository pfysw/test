﻿#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <assert.h>
#include "test.h"

#define BLOCK_NUM 10
#define KEY_SIZE 1000000
#define PAGE_SIZE 4096
#define MAX_FREE 1000
#define MAX_SUB_NUM ((PAGE_SIZE-sizeof(NodeHdr))/sizeof(BtreeRecord))
#define RIGHT_NODE 0
#define LEFT_NODE 1

typedef struct SeqTable SeqTable;
typedef struct Record Record;
typedef struct Btree Btree;
typedef struct Node Node;


int SeqFind(SeqTable *pSeqTable, int key);

typedef struct BtreeRecord
{
	int key;
	u8 aMagic[4];
	u8 aData[8];
	u32 iSub;
}BtreeRecord;

struct Record
{
	int key;
	u8 aMagic[4];
	u8 aData[8];
};

typedef struct FreeSlot FreeSlot;
typedef struct FreeSlot
{
	int iPage;
	FreeSlot *pNext;
}FreeSlot;

struct SeqTable
{
	int fd;
	u16 maxPage;
	u16 pageSize;
	int freeSlot;
	u32 nFreeSlot;
	u32 iRecord;
	u16 maxRecord;
	Record *pRecord;
	u8 iBufOffst;
	Record insert_buf[10];
	Bitvec **paBlock;
	u32 nBlock;
};

struct Btree
{
	int fd;
	Node *pNode;
	Node *pRoot;
	BtreeRecord record;
	u32 iPage;
	u32 iParent;
	u32 iNeighbor;
	u32 iRecord;
	u32 mxRecord;
	u8 getFlag;
	int nFree;
	FreeSlot* pFree;
	u32 aFind[10];
	u32 iFind;

};

typedef struct NodeHdr
{
	u32 nPage;
	u32 reserve;
	u8  aMagic[4];
	u16 nRecord;
	u8  isLeaf;
	u8  isRoot;

}NodeHdr;



struct Node
{
	NodeHdr nodeHdr;
	BtreeRecord aRecord[MAX_SUB_NUM];
};



static const unsigned char aMagic[] = {
  0xd9, 0xd5, 0x05, 0xf9,
};
u32 random_()
{
	static u32 x = 0;
	static u8 isInit = 0;
	if(!isInit)
	{
		isInit =1;
		int t = (unsigned int)time(NULL);
		printf("t %d\n",t);
		srand(t);
	}
    for(int i=0; i<20; i++)
    {
    	x ^= (rand()&1)<<i;
    }
    x++;
    return x%KEY_SIZE;
}

int OsRead(
  int fd,
  void *zBuf,
  int iAmt,
  long iOfst
){
  off_t ofst;
  int nRead;

  ofst = lseek(fd, iOfst, SEEK_SET);
  if( ofst!=iOfst ){
    return 0;
  }
  nRead = read(fd, zBuf, iAmt);

  return nRead;
}

int OsWrite(
  int fd,
  void *zBuf,
  int iAmt,
  long iOfst
){
  off_t ofst;
  int nWrite;

  ofst = lseek(fd, iOfst, SEEK_SET);
  if( ofst!=iOfst ){
    return 0;
  }
  nWrite = write(fd, zBuf, iAmt);

  return nWrite;
}


int SequenceFind(SeqTable *pSeqTable, int key)
{
	int i,j;
	int cnt = 1;
	int szRecord = sizeof(Record);
	u16 szPage = pSeqTable->pageSize;
	int iOffset;
	u8 aBuf[4096];
	Record *pBuf;
	int fd = pSeqTable->fd;
	for(i=0; i<=pSeqTable->maxPage; i++)
	{
		iOffset = i*szPage;
		OsRead(fd, aBuf, szPage, iOffset);
		for(j=0; j<256; j++)
		{
			if(cnt > pSeqTable->maxRecord) return 0;
			cnt++;
			pBuf = (Record*)(&aBuf[j*szRecord]);
			if(memcmp(pBuf->aMagic, aMagic, 4) == 0)
			{
				if(pBuf->key == key)
				{
					pSeqTable->iRecord = i*256+j;
					memcpy(pSeqTable->pRecord,pBuf,szRecord);
					//printf("find:%d\n",i*256+j);
					return 1;
				}

			}
			else if(pSeqTable->freeSlot<0)
			{
				pSeqTable->freeSlot = i*256+j;
				//printf("getfree %d\n",pSeqTable->freeSlot*szRecord);
			}
		}
	}
	printf("not find:%d\n",key);
	return 0;
}

void SequenceInsert(SeqTable *pSeqTable, int key)
{
	Record record,result;
	int iOffset;
	int szRecord = sizeof(Record);
	if(!SequenceFind(pSeqTable,key))
	{
	    record.key = key;
	    memcpy(record.aMagic,aMagic,4);
	    for(int i=0; i<8; i++)
	    {
	    	record.aData[i] = i;
	    }
	    if(pSeqTable->freeSlot>=0)
	    {
	    	iOffset = pSeqTable->freeSlot*szRecord;
	    	pSeqTable->freeSlot = -1;
	    }
	    else
	    {
	    	iOffset = pSeqTable->maxRecord*szRecord;
	    	pSeqTable->maxRecord++;
	    	pSeqTable->maxPage = (iOffset+szRecord)/4096;
	    }
	    OsWrite(pSeqTable->fd,&record,szRecord,iOffset);
	    OsRead(pSeqTable->fd,&result,szRecord,iOffset);//用这条代替flush操作
	    if(memcmp(&record,&result,16))
	    {
	    	pSeqTable->maxRecord--;
	    	pSeqTable->maxPage = (pSeqTable->maxRecord*szRecord)/4096;
	    	return;
	    }
	    //printf("insert %d\n",iOffset);
	}
	else
	{
		//printf("collision\n");
	}

}
void SequenceDelete(SeqTable *pSeqTable, int key)
{
	u8 aBuf[16] = {0};
	int iOffset;
	int szRecord = sizeof(Record);
	if(SequenceFind(pSeqTable,key))
	{
		iOffset = pSeqTable->iRecord*szRecord;
		OsWrite(pSeqTable->fd,aBuf,szRecord,iOffset);
		pSeqTable->freeSlot = pSeqTable->iRecord;
		//printf("delete %d\n",iOffset);
	}
}

void SeqTest1(SeqTable *pSeqTable)
{
	int key;
	int i,j;
	Record record;
	int szRecord = sizeof(Record);
	int iOffset;

	for(i=0; i<1000; i++)
	{
		for(j =0;j<10;j++)
		{
			key = random_();
			SequenceInsert(pSeqTable,key);
			//assert(SequenceFind(pSeqTable,key));
		}
		for(j =0;j<100;j++)
		{
			iOffset = (random_()%pSeqTable->maxRecord)*szRecord;
			OsRead(pSeqTable->fd, &record, szRecord, iOffset);
			key = record.key;
			SequenceFind(pSeqTable,key);
		}
		for(j=0;j<2;j++)
		{
			iOffset = (random_()%pSeqTable->maxRecord)*szRecord;
			OsRead(pSeqTable->fd, &record, szRecord, iOffset);
			key = record.key;
			//printf("want to delete %d\n",iOffset);
			SequenceDelete(pSeqTable,key);
			//assert(!SequenceFind(pSeqTable,key));
		}
	}
}
SeqTable *OpenSeqTable(char *zName)
{
	int szRecord = sizeof(Record);
	remove(zName);
	SeqTable *pSeqTable = (SeqTable*)malloc(sizeof(SeqTable));
	memset(pSeqTable,0,sizeof(SeqTable));
	pSeqTable->pageSize = 4096;
	pSeqTable->freeSlot = -1;
	pSeqTable->pRecord = (Record*)malloc(sizeof(Record));
	pSeqTable->paBlock = (Bitvec**)malloc(sizeof(Bitvec*));
	pSeqTable->paBlock[0] = sqlite3BitvecCreate(KEY_SIZE);
	pSeqTable->nBlock++;
	pSeqTable->fd = open(zName, O_RDWR|O_CREAT, 0600);
	return pSeqTable;
}

void CloseSeqTable(SeqTable *pSeqTable)
{
	int i;
	for( i=0; i<pSeqTable->nBlock; i++)
	{
		sqlite3BitvecDestroy(pSeqTable->paBlock[i]);
	}
	close(pSeqTable->fd);
	free(pSeqTable->paBlock);
	free(pSeqTable->pRecord);
	free(pSeqTable);
}


//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

void SeqMoveSlot(SeqTable *pSeq)
{
	int fd = pSeq->fd;
	u8 aBuf[4096];
	u8 aMaxPageBuf[4096];
	u16 szPage = pSeq->pageSize;
	int szRecord = sizeof(Record);
	int iOfst;
	int cnt = 1;
	int i,j;
	Record *pBuf,*tmp;
	u8 aTmpSpace[512];
	int endOffset = 0;
	int iBlock,nBlock;
	int mxOffset;

	OsRead(fd, aBuf, szPage, 0);
	for(i=0; i<=pSeq->maxPage; i++)
	{

		iOfst = i*szPage;
		OsRead(fd, aBuf, szPage, iOfst);

		for(j=0; j<256; j++)
		{
			if( cnt>pSeq->maxRecord ) return;
			cnt++;
			pBuf = (Record*)(&aBuf[j*szRecord]);
			if(memcmp(pBuf->aMagic,aMagic,4)!=0)
			{
				if( endOffset==0 )
				{
					mxOffset = pSeq->maxPage*szPage;
					OsRead(fd, aMaxPageBuf, szPage, mxOffset);
					endOffset = pSeq->maxRecord*szRecord-mxOffset;
				}
				while( endOffset>0 )
				{
					endOffset -= szRecord;
					tmp = (Record*)&aMaxPageBuf[endOffset];
					if( memcmp(tmp->aMagic,aMagic,4)==0 )
					{
						OsWrite(fd, tmp, szRecord, iOfst+j*szRecord);
						OsRead(fd, pBuf, szRecord, iOfst+j*szRecord);
						if( memcmp(tmp, pBuf,szRecord)==0 )
						{
							nBlock = (mxOffset+endOffset)/(szPage*BLOCK_NUM);
							assert( sqlite3BitvecTest(pSeq->paBlock[nBlock], tmp->key) != 0 );
							sqlite3BitvecClear(pSeq->paBlock[nBlock], tmp->key, aTmpSpace);
							assert( sqlite3BitvecTest(pSeq->paBlock[nBlock], tmp->key) == 0 );
							iBlock = (iOfst+j*szRecord)/(szPage*BLOCK_NUM);
							sqlite3BitvecSet(pSeq->paBlock[iBlock], tmp->key);
							pSeq->maxRecord = (mxOffset+endOffset-szRecord)/szRecord;
							pSeq->maxPage = (mxOffset+endOffset-szRecord)/szPage;
							pSeq->nBlock = pSeq->maxPage/BLOCK_NUM + 1;
							pSeq->nFreeSlot--;
							log_a("move %d to %d",mxOffset+endOffset,iOfst+j*szRecord);
							log_a("nFreeSlot %d maxRecord %d maxPage%d nBlock%d",
									pSeq->nFreeSlot,pSeq->maxRecord,pSeq->maxPage,pSeq->nBlock);

						}
						else
						{
							endOffset += szRecord;
						}
						break;
					}
				}
			}
		}
	}
}

void SeqInsertFlush(SeqTable *pSeq)
{
	Record *paBuf = pSeq->insert_buf;
	Record result[10];
	int szRecord = sizeof(Record);
	int iAmt = pSeq->iBufOffst*szRecord;
	int iOfst = pSeq->maxRecord*szRecord;
	int i;
	u16 szPage = pSeq->pageSize;
	int fd = pSeq->fd;
	int maxPage = pSeq->maxPage;
    int nBlock;
    Bitvec **paNew = pSeq->paBlock;
    int iBlock = pSeq->nBlock;
    int key = 0;


    log_a("flush %d %d",iOfst,iAmt);

	OsWrite(fd,paBuf,iAmt,iOfst);
	OsRead(fd,&result,iAmt,iOfst);

	if(memcmp(result,paBuf,iAmt)==0)
	{
		pSeq->maxRecord += pSeq->iBufOffst;
		pSeq->maxPage = (iOfst+iAmt)/szPage;
		log_a("maxPage %d offset %d",pSeq->maxPage,iOfst+iAmt);
		if( pSeq->maxPage%BLOCK_NUM==0 && pSeq->maxPage>maxPage )
		{
			nBlock = pSeq->maxPage/BLOCK_NUM+1;
			log_a("nBlock %d iBlock %d",nBlock,iBlock);
			if( nBlock>iBlock)
			{
				paNew = (Bitvec**)realloc(pSeq->paBlock, (nBlock)*sizeof(Bitvec*));
				memset(&paNew[iBlock], 0, (nBlock-iBlock)*sizeof(Bitvec*));
				pSeq->nBlock = nBlock;
				for(i=iBlock; i<nBlock; i++)
				{
					paNew[i] = sqlite3BitvecCreate(KEY_SIZE);
				}
				pSeq->paBlock = paNew;
			}
		}
		for(i=0; i<pSeq->iBufOffst; i++)
		{
			iBlock = (iOfst + i*szRecord)/(szPage*BLOCK_NUM);
			key = paBuf[i].key;
			if(!pSeq->paBlock[iBlock])
			{
				log_a("iBlock %d",iBlock);
				log_a("iOfst %d i %d",iOfst,i);
				assert(pSeq->paBlock[iBlock]);
			}

			sqlite3BitvecSet(pSeq->paBlock[iBlock], key);
			log_a("setbit block %d key %d",iBlock,key);
			assert(SeqFind(pSeq,result[i].key));
		}
	}
	memset(paBuf, 0 ,iAmt);
	pSeq->iBufOffst = 0;
	//////////////////////////////////////////
    if( pSeq->nFreeSlot>1000 )
    {
    	SeqMoveSlot(pSeq);
    }
}


void SeqInsertCache(SeqTable *pSeqTable, int key)
{

	int iOffst = pSeqTable->iBufOffst;
	Record *pBuf = (Record *)&pSeqTable->insert_buf[iOffst];
	if(SeqFind(pSeqTable,key))
	{
		//冲突
		return;
		printf("actul offset %d\n",(pSeqTable->maxRecord)*sizeof(Record));
		printf("colision key %d record %d\n",key,pSeqTable->iRecord);
	}
	if(iOffst==10)
	{
		SeqInsertFlush(pSeqTable);
	}
	pBuf->key = key;
	memcpy(pBuf->aMagic,aMagic,4);
	for(int i=0; i<8; i++)
	{
		pBuf->aData[i] = i;
	}
	log_a("insert %d ofst %d",key,pSeqTable->iBufOffst);
	pSeqTable->iBufOffst++;

}
int SeqFind(SeqTable *pSeqTable, int key)
{
	int i,j,k;
	int iOffset;
	int szPage = pSeqTable->pageSize;
	int szRecord = sizeof(Record);
	int fd = pSeqTable->fd;
	u8 aBuf[szPage];
	Record *pRecord;
	int nRecord = szPage/szRecord;
	for( i=0;i<pSeqTable->nBlock;i++ )
	{
		if(sqlite3BitvecTest(pSeqTable->paBlock[i],key))
		{
			for( k=0; k<10; k++)
			{
				iOffset = (i*BLOCK_NUM+k)*szPage;
				OsRead(fd, aBuf, szPage, iOffset);
				for(j=0; j<nRecord; j++)
				{
					pRecord = (Record*)(&aBuf[j*szRecord]);
					if( pRecord->key==key )
					{
						log_a("find %d iBlock %d",iOffset+j*szRecord,i);
						pSeqTable->iRecord = (iOffset+j*szRecord)/szRecord;
						memcpy(pSeqTable->pRecord,pRecord,szRecord);
						return 1;
					}
				}
			}
		}
	}
	log_a("not find %d",key);
	return 0;

}
void SeqDelete(SeqTable *pSeqTable, int key)
{
	u8 aBuf[16] = {0};
	int iOffset;
	int szRecord = sizeof(Record);
	u8 aTmp[512];
	int iBlock;
	if( SeqFind(pSeqTable,key) )
	{
		iOffset = pSeqTable->iRecord*szRecord;
		OsWrite(pSeqTable->fd,aBuf,szRecord,iOffset);
		pSeqTable->nFreeSlot++;
		iBlock = iOffset/(pSeqTable->pageSize*BLOCK_NUM);
		sqlite3BitvecClear(pSeqTable->paBlock[iBlock],key,aTmp);

		log_a("delete %d %d",iBlock,iOffset);
	}
}

void SeqTest2(SeqTable *pSeqTable)
{
	int key;
	int i,j;
	Record record;
	int szRecord = sizeof(Record);
	int iOffset;

	for(i=0; i<3000; i++)
	{
		for(j =0;j<10;j++)
		{
			key = random_();
			SeqInsertCache(pSeqTable,key);
		}
		SeqInsertFlush(pSeqTable);
		for(j =0;j<100;j++)
		{
			assert( pSeqTable->maxRecord != 0 );
			iOffset = (random_()%pSeqTable->maxRecord)*szRecord;
			OsRead(pSeqTable->fd, &record, szRecord, iOffset);
			key = record.key;
			log_a("key %d",key);
			SeqFind(pSeqTable,key);
		}
		for(j=0;j<2;j++)
		{
			iOffset = (random_()%pSeqTable->maxRecord)*szRecord;
			OsRead(pSeqTable->fd, &record, szRecord, iOffset);
			key = record.key;
			log_a("want to delete %d",iOffset);
			SeqDelete(pSeqTable,key);
			assert( !SeqFind(pSeqTable,key) );
		}
	}
}

void SequenceTest(void)
{
	char *zFileName = "testdata";
	SeqTable *pSeqTable = OpenSeqTable(zFileName);
	time_t t1,t2;
	t1 = time(NULL);
	SeqTest1(pSeqTable);
	//SeqTest2(pSeqTable);
	t2 = time(NULL);
	printf("time %ld\n",t2-t1);
    CloseSeqTable(pSeqTable);
	//remove(zFileName);
}

////////////////////////////////////////////////////
Btree *OpenBtree(char *zName)
{
	NodeHdr *pHdr;
	remove(zName);
	Btree *pBt=(Btree*)malloc(sizeof(Btree));
	memset(pBt,0,sizeof(Btree));
	pBt->pRoot = (Node *)malloc(PAGE_SIZE);
	pBt->fd = open(zName, O_RDWR|O_CREAT, 0600);
	OsRead(pBt->fd,pBt->pRoot,PAGE_SIZE,0);
	pHdr = &pBt->pRoot->nodeHdr;
	if( memcmp(pHdr->aMagic,aMagic,4)!=0 )
	{
		memset(pBt->pRoot,0,PAGE_SIZE);
		pHdr->nRecord = 0;
		pHdr->isRoot = 1;
		pHdr->isLeaf = 1;
		pHdr->nPage = 1;
		memcpy(pHdr->aMagic,aMagic,4);
	}
	OsWrite(pBt->fd,pBt->pRoot,PAGE_SIZE,0);
	return pBt;
}
void updateRoot(Btree *pBt, Node *p)
{
	log_fun("%s",__FUNCTION__ );
    if(p->nodeHdr.isRoot)
    {
    	memcpy(pBt->pRoot, p, PAGE_SIZE);
    }
}
void CloseBtree(Btree *pBt)
{
	close(pBt->fd);
	free(pBt->pRoot);
	free(pBt);
}

void addFreeSlot(Btree *pBt, u32 iPage)
{
    if(pBt->nFree<MAX_FREE && iPage!=0)
    {
		FreeSlot *p = (FreeSlot*)malloc(sizeof(FreeSlot));
		p->iPage = iPage;
		p->pNext = pBt->pFree;
		pBt->pFree = p;
		pBt->nFree++;
    }
}

u32 popFreeSlot(Btree *pBt)
{
	u32 iPage;
	FreeSlot *p = pBt->pFree;
	pBt->pFree = p->pNext;
	pBt->nFree--;
	assert( pBt->nFree>= 0);
	iPage = p->iPage;
	free(p);
	return iPage;
}


int searchRecord(Btree *pBt,Node *pNode,int key,int iParent)
{
	int i;
	u8 szRecord = sizeof(BtreeRecord);
	NodeHdr *pHdr;
	int rc = 0;

	pHdr = &pNode->nodeHdr;
	u8 tmp[PAGE_SIZE];
    OsRead(pBt->fd, &tmp, PAGE_SIZE, iParent*PAGE_SIZE);
    assert( memcmp(pNode,&tmp,PAGE_SIZE)==0 );
	assert( pHdr->nRecord < MAX_SUB_NUM );
    if( !((pHdr->nRecord>=(MAX_SUB_NUM+1)/2-1) || pHdr->isRoot) )
    {
    	assert(0);
    }
	for( i=0; i<pHdr->nRecord; i++)
	{
		if( pNode->aRecord[i].key>=key )
		{
			if( pNode->aRecord[i].key==key )
			{
				if( pBt->getFlag )
				{
					memcpy( pBt->pNode, pNode, PAGE_SIZE);
				}
				rc = 1;
			}
			break;
		}
	}
	pBt->iRecord = i;
	pBt->iPage = iParent;
	memcpy(&pBt->record, &pNode->aRecord[i], szRecord);

	return rc;
}

int BtreeFind(Btree *pBt, int key)
{
	Node *pNode =(Node *)malloc(PAGE_SIZE);
	int iPage = 0;
	int rc = 0;

	memcpy(pNode, pBt->pRoot, PAGE_SIZE);
	pBt->iFind = 0;

	while( 1 )
	{

		if( searchRecord(pBt,pNode,key,iPage) )
		{
			pBt->aFind[pBt->iFind++] = pBt->iPage;
			rc = 1;
			goto find_finish;
		}
		pBt->aFind[pBt->iFind++] = pBt->iPage;
		if( pNode->nodeHdr.isLeaf )
		{
			break;
		}
		iPage = pBt->record.iSub;
		assert(iPage);
		OsRead(pBt->fd, pNode, PAGE_SIZE, iPage*PAGE_SIZE);
	}
find_finish:
    free(pNode);
    return rc;
}

void addNewSub(Node *p,Node *pNew,int median)
{
	BtreeRecord *pDstBuf,*pSrcBuf;
	int iAmt;

	//为方便起见，p->nodeHdr.nRecord定为奇数
	assert( (p->nodeHdr.nRecord & 0x01)!=0 );
	p->nodeHdr.nRecord /= 2;
	assert( p->nodeHdr.nRecord >= ((MAX_SUB_NUM+1)/2-1) );
	memcpy(&pNew->nodeHdr,&p->nodeHdr,sizeof(NodeHdr));

    pDstBuf = &pNew->aRecord[0];
    pSrcBuf = &p->aRecord[median+1];
    iAmt = (pNew->nodeHdr.nRecord+1)*sizeof(BtreeRecord);
    memcpy(pDstBuf,pSrcBuf,iAmt);

    memset(&p->aRecord[median],0,sizeof(Record));
}

void BtreeSplite(Btree *pBt, Node *p, Node *pParent,int iOffset)
{
	int median = (p->nodeHdr.nRecord-1)/2;
	BtreeRecord *pDstBuf,*pSrcBuf;
	int iAmt;
	Node *pNew = (Node*)malloc(PAGE_SIZE);
	u32 tmp1,tmp2;
	int szRecord = sizeof(BtreeRecord);

	memset(pNew,0,PAGE_SIZE);

	if(p->nodeHdr.isRoot)
	{
		memset(pParent,0,PAGE_SIZE);
        memcpy(&pParent->nodeHdr,&p->nodeHdr,sizeof(NodeHdr));
        pParent->nodeHdr.isLeaf = 0;
        pParent->nodeHdr.nRecord = 1;
        pDstBuf = &pParent->aRecord[0];
        pSrcBuf = &p->aRecord[median];
        memcpy(pDstBuf,pSrcBuf,sizeof(Record));
        if( pBt->nFree>1 )
        {
        	pParent->aRecord[0].iSub = popFreeSlot(pBt);
        	pParent->aRecord[1].iSub = popFreeSlot(pBt);
        }
        else
        {
			pParent->aRecord[0].iSub = pParent->nodeHdr.nPage++;
			pParent->aRecord[1].iSub = pParent->nodeHdr.nPage++;
        }
        tmp1 = pParent->aRecord[0].iSub;
        tmp2 = pParent->aRecord[1].iSub;
        memcpy(pBt->pRoot, pParent, PAGE_SIZE);
        p->nodeHdr.isRoot = 0;
        addNewSub(p, pNew, median);

        OsWrite(pBt->fd,pBt->pRoot,PAGE_SIZE,0);
        OsWrite(pBt->fd,p,PAGE_SIZE,pParent->aRecord[0].iSub*PAGE_SIZE);
        OsWrite(pBt->fd,pNew,PAGE_SIZE,pParent->aRecord[1].iSub*PAGE_SIZE);
	}
	else
	{
        pDstBuf = &pParent->aRecord[iOffset+1];
        pSrcBuf = &pParent->aRecord[iOffset];
        iAmt = ((++pParent->nodeHdr.nRecord)-iOffset)*szRecord;
        memmove(pDstBuf,pSrcBuf,iAmt);
        memcpy(pSrcBuf, &p->aRecord[median], sizeof(Record));
        //assert( pDstBuf->key!=pSrcBuf->key );
        assert( pBt->iPage==pDstBuf->iSub );
        pSrcBuf->iSub = pBt->iPage;
        if( pBt->nFree>0 )
        {
        	pDstBuf->iSub = popFreeSlot(pBt);
        }
        else
        {
        	if(pParent->nodeHdr.isRoot)
        	{
        		pDstBuf->iSub = pParent->nodeHdr.nPage++;
        	}
        	else
        	{
				pDstBuf->iSub = pBt->pRoot->nodeHdr.nPage++;
				OsWrite(pBt->fd,pBt->pRoot,PAGE_SIZE,0);
        	}
        }

        addNewSub(p, pNew, median);

        if(pParent->nodeHdr.isRoot)
        {
        	memcpy(pBt->pRoot, pParent, PAGE_SIZE);
        }
        OsWrite(pBt->fd,pParent,PAGE_SIZE,pBt->iParent*PAGE_SIZE);
        OsWrite(pBt->fd,p,PAGE_SIZE,pSrcBuf->iSub*PAGE_SIZE);
        OsWrite(pBt->fd,pNew,PAGE_SIZE,pDstBuf->iSub*PAGE_SIZE);
        tmp1 = pSrcBuf->iSub;
        tmp2 = pDstBuf->iSub;
	}
	pBt->iPage = tmp1;
	assert(pBt->iPage);
	if( (pBt->iRecord>median) )
	{
		memcpy(p,pNew,PAGE_SIZE);
		pBt->iPage = tmp2;
	}
    free(pNew);
}

void BtreeInsert(Btree *pBt, int key)
{
	Node *pNode =(Node *)malloc(PAGE_SIZE);
	Node *pParent = (Node*)malloc(PAGE_SIZE);
	NodeHdr *pHdr;
	int iPage = 0;
	int iOffset = 0;
	BtreeRecord *pDstBuf,*pSrcBuf;
	int iAmt;

	memcpy(pNode, pBt->pRoot, PAGE_SIZE);
	OsRead(pBt->fd, pNode, PAGE_SIZE, 0);
	assert( memcmp(pNode,pBt->pRoot,PAGE_SIZE)==0 );
	int flag = 0;
    if(BtreeFind(pBt,key))
    {
    	flag = 1;
    }

	while( 1 )
	{
		pHdr = &pNode->nodeHdr;

		if( searchRecord(pBt,pNode,key,iPage) )
		{
			log_b("collision %d",key);
			flag=0;//冲突
			break;
		}
		if( pHdr->nRecord == MAX_SUB_NUM-1 )
		{
			assert( iPage==pBt->iPage );
			log_a("split %d",iPage);
			BtreeSplite(pBt,pNode,pParent,iOffset);

			if( pParent->nodeHdr.isRoot )
			{
				assert( memcmp(pParent,pBt->pRoot,PAGE_SIZE)==0 );
			}
			assert( !pNode->nodeHdr.isRoot );

			iPage = pBt->iPage;
            continue;
		}
		if(pHdr->isLeaf)
		{
			pDstBuf = &pNode->aRecord[pBt->iRecord+1];
			pSrcBuf = &pNode->aRecord[pBt->iRecord];
			iAmt = (++pHdr->nRecord - pBt->iRecord)*sizeof(BtreeRecord);
			if( iPage==pBt->pRoot->nodeHdr.nPage-1 )
			{
				pBt->mxRecord = pHdr->nRecord;
			}
			memmove(pDstBuf,pSrcBuf,iAmt);
			pNode->aRecord[pBt->iRecord].key = key;
			memcpy(pNode->aRecord[pBt->iRecord].aMagic, aMagic, 4);
			for(int i=0; i<8; i++)
			{
				pNode->aRecord[pBt->iRecord].aData[i] = i;
			}
			//assert( pDstBuf->key!=pSrcBuf->key );
			updateRoot(pBt,pNode);
			OsWrite(pBt->fd, pNode, PAGE_SIZE, iPage*PAGE_SIZE);

			break;
		}
		pBt->iParent = pBt->iPage;
		assert( iPage==pBt->iParent );
		iPage = pBt->record.iSub;
		iOffset = pBt->iRecord;
		memcpy(pParent, pNode, PAGE_SIZE);
		OsRead(pBt->fd, pNode, PAGE_SIZE, iPage*PAGE_SIZE);
	}

	OsRead(pBt->fd, pNode, PAGE_SIZE, 0);
	if( memcmp(pNode,pBt->pRoot,PAGE_SIZE)!=0 )
	{
		memout(pNode,16);
		memout(pBt->pRoot,16);
		assert( memcmp(pNode,pBt->pRoot,PAGE_SIZE)==0 );
	}
	assert(!flag);

    free(pNode);
    free(pParent);
}

void getNeighborKey(
		Node *p,
		Node *pNbr,
		Node *pParent,
		int flag,
		int iOffset)
{
	log_fun("%s",__FUNCTION__ );
	BtreeRecord *pDstBuf,*pSrcBuf;
	int iAmt;
	if(flag==RIGHT_NODE)
	{
		pDstBuf = &p->aRecord[p->nodeHdr.nRecord++];
		pSrcBuf = &pParent->aRecord[iOffset];
	}
	else
	{
		memmove(&p->aRecord[1],&p->aRecord[0],
				(++p->nodeHdr.nRecord)*sizeof(BtreeRecord));
		pDstBuf = &p->aRecord[0];
		pSrcBuf = &pParent->aRecord[iOffset];
	}
	memcpy(pDstBuf,pSrcBuf,sizeof(Record));
	//assert( p->aRecord[1].key!=p->aRecord[0].key );

	if(flag==RIGHT_NODE)
	{
		pSrcBuf = &pNbr->aRecord[0];
		(pDstBuf+1)->iSub = pSrcBuf->iSub;
	}
	else
	{
		pSrcBuf = &pNbr->aRecord[--pNbr->nodeHdr.nRecord];
		pDstBuf->iSub = (pSrcBuf+1)->iSub;
	}
	pDstBuf = &pParent->aRecord[iOffset];
	memcpy(pDstBuf,pSrcBuf,sizeof(Record));


	if(flag==RIGHT_NODE)
	{
		pDstBuf = &pNbr->aRecord[0];
		pSrcBuf = &pNbr->aRecord[1];
		iAmt = (pNbr->nodeHdr.nRecord--)*sizeof(BtreeRecord);
		memmove(pDstBuf,pSrcBuf,iAmt);
		//assert( pDstBuf->key!=pSrcBuf->key );
	}
	else
	{
		memset(&pNbr->aRecord[pNbr->nodeHdr.nRecord],0,sizeof(Record));
	}
}

u32 mergeBtree(
		Node *p,
		Node *pNbr,
		Node *pParent,
		int iOffset)
{
	log_fun("%s",__FUNCTION__ );
	u32 iDelete;
	BtreeRecord *pDstBuf,*pSrcBuf;
	int iAmt;
	int szRecord = sizeof(BtreeRecord);

	pDstBuf = &p->aRecord[p->nodeHdr.nRecord];
	pSrcBuf = &pParent->aRecord[iOffset];
	memcpy(pDstBuf,pSrcBuf,sizeof(Record));

	pDstBuf = &pParent->aRecord[iOffset];
	pSrcBuf = &pParent->aRecord[iOffset+1];
	iDelete = pSrcBuf->iSub;
	pSrcBuf->iSub = pDstBuf->iSub;
	iAmt = ((pParent->nodeHdr.nRecord--)-iOffset)*szRecord;
	memmove(pDstBuf,pSrcBuf,iAmt);
	//assert( pDstBuf->key!=pSrcBuf->key );
	pDstBuf = &p->aRecord[++p->nodeHdr.nRecord];
	pSrcBuf = &pNbr->aRecord[0];
	iAmt = (pNbr->nodeHdr.nRecord+1)*szRecord;
	p->nodeHdr.nRecord += pNbr->nodeHdr.nRecord;
	assert( p->nodeHdr.nRecord<MAX_SUB_NUM );
	memcpy(pDstBuf,pSrcBuf,iAmt);
	memset(pNbr, 0, PAGE_SIZE);

	return iDelete;
}

void adjustBtree(Btree *pBt, Node *p, Node *pParent, u32 iPage)
{
	log_fun("%s",__FUNCTION__ );
	Node *pRight = (Node*)malloc(PAGE_SIZE);
	Node *pLeft = (Node*)malloc(PAGE_SIZE);
	int i;
	int iLeft,iRight;
	int flag = 0;

	int iOffset;
	u32 iDelete = 0;

	assert( !p->nodeHdr.isRoot );
	pBt->iParent = pBt->aFind[--pBt->iFind];
	OsRead(pBt->fd, pParent, PAGE_SIZE, pBt->iParent*PAGE_SIZE);
	for(i=0; i<=pParent->nodeHdr.nRecord; i++)
	{
		if( pParent->aRecord[i].iSub==iPage )
		{
			iOffset = i;
			break;
		}
	}
    assert( i<=pParent->nodeHdr.nRecord );
	if( iOffset<pParent->nodeHdr.nRecord )
	{
		iRight = pParent->aRecord[iOffset+1].iSub;
		OsRead(pBt->fd, pRight, PAGE_SIZE, iRight*PAGE_SIZE);

		if( pRight->nodeHdr.nRecord>(MAX_SUB_NUM/2 - 1) )
		{
			getNeighborKey(p,pRight,pParent,RIGHT_NODE,iOffset);
		}
		else if( iOffset>0 )
		{
			iLeft = pParent->aRecord[iOffset-1].iSub;
			OsRead(pBt->fd, pLeft, PAGE_SIZE, iLeft*PAGE_SIZE);
			iOffset--;

			if( pLeft->nodeHdr.nRecord>(MAX_SUB_NUM/2 - 1) )
			{
				getNeighborKey(p,pLeft,pParent,LEFT_NODE,iOffset);
				flag = 1;
			}
			else
			{
				iDelete = mergeBtree(p,pRight,pParent,iOffset);
			}
		}
		else
		{
			iDelete = mergeBtree(p,pRight,pParent,iOffset);
		}
	}
	else
	{
		iLeft = pParent->aRecord[iOffset-1].iSub;
		OsRead(pBt->fd, pLeft, PAGE_SIZE, iLeft*PAGE_SIZE);
		iOffset--;
		if( pLeft->nodeHdr.nRecord>((MAX_SUB_NUM+1)/2 - 1) )
		{
			getNeighborKey(p,pLeft,pParent,LEFT_NODE,iOffset);
		}
		else
		{
			iDelete = mergeBtree(pLeft,p,pParent,iOffset);
		}
		flag = 1;
	}
	/////////////////////////////////////
	if(flag)
	{
		assert( iLeft!=0 );
		OsWrite(pBt->fd, pLeft, PAGE_SIZE, iLeft*PAGE_SIZE);
	}
	else
	{
		assert( iRight!=0 );
		OsWrite(pBt->fd, pRight, PAGE_SIZE, iRight*PAGE_SIZE);
	}
	OsWrite(pBt->fd, pParent, PAGE_SIZE, pBt->iParent*PAGE_SIZE);
	OsWrite(pBt->fd, p, PAGE_SIZE, iPage*PAGE_SIZE);
	///////////////////////////////
	assert( iDelete<pBt->pRoot->nodeHdr.nPage );
	if( iDelete==pBt->pRoot->nodeHdr.nPage-1 )
	{
		pBt->pRoot->nodeHdr.nPage--;
		OsWrite(pBt->fd, pBt->pRoot, PAGE_SIZE, 0);
	}
	else
	{
		addFreeSlot(pBt,iDelete);
	}
	free(pLeft);
	free(pRight);
}

void BtreeDeleteLeaf(Btree *pBt, Node *p)
{
	log_fun("%s",__FUNCTION__ );
	BtreeRecord *pDstBuf,*pSrcBuf;
	int iAmt;
	u8 test_tmp[4096];

	pDstBuf = &p->aRecord[pBt->iRecord];
	pSrcBuf = &p->aRecord[pBt->iRecord+1];
	assert(p->nodeHdr.nRecord>pBt->iRecord);
	log_a("Record %d %d",pBt->iRecord,p->nodeHdr.nRecord);
	assert( (pDstBuf->key!=pSrcBuf->key)
			||p->nodeHdr.nRecord==pBt->iRecord+1);
	iAmt = ((p->nodeHdr.nRecord--)-pBt->iRecord)*sizeof(BtreeRecord);

	memmove(pDstBuf,pSrcBuf,iAmt);
//	if( !( (pDstBuf->key!=pSrcBuf->key)|| pSrcBuf->key==0 ) )
//	{
//		log_a("key %d %d",pDstBuf->key,pSrcBuf->key);
//	}
//	assert( (pDstBuf->key!=pSrcBuf->key)|| pSrcBuf->key==0 );

	OsWrite(pBt->fd, p, PAGE_SIZE, pBt->iPage*PAGE_SIZE);
    if(p->nodeHdr.isRoot)
    {
    	memcpy(pBt->pRoot, p, PAGE_SIZE);
    }

    OsRead(pBt->fd, &test_tmp, PAGE_SIZE, pBt->iPage*PAGE_SIZE);

    assert( memcmp(&test_tmp,p,PAGE_SIZE)==0 );
}

int BtreeDeleteInside(Btree *pBt, Node *p)
{
	log_fun("%s",__FUNCTION__ );
	BtreeRecord *pDstBuf,*pSrcBuf;
	int iAmt;
	int iLeft,iRight;
	Node *pRight = (Node*)malloc(PAGE_SIZE);
	Node *pLeft = (Node*)malloc(PAGE_SIZE);
	int iPage = pBt->iPage;
	u32 iRecord = pBt->iRecord;
	u32 iDelete;
	int rc = 0;

	iLeft = p->aRecord[iRecord].iSub;
	OsRead(pBt->fd, pLeft, PAGE_SIZE, iLeft*PAGE_SIZE);
	while(!pLeft->nodeHdr.isLeaf)
	{
		iLeft = pLeft->aRecord[pLeft->nodeHdr.nRecord].iSub;
		OsRead(pBt->fd, pLeft, PAGE_SIZE, iLeft*PAGE_SIZE);
	}
	if( pLeft->nodeHdr.nRecord>(MAX_SUB_NUM/2-1) )
	{
		pSrcBuf = &pLeft->aRecord[--pLeft->nodeHdr.nRecord];
		pDstBuf = &p->aRecord[iRecord];
		memcpy(pDstBuf,pSrcBuf,sizeof(Record));
		updateRoot(pBt,p);
		OsWrite(pBt->fd, p, PAGE_SIZE, iPage*PAGE_SIZE);
		OsWrite(pBt->fd, pLeft, PAGE_SIZE, iLeft*PAGE_SIZE);
		rc = 1;

	}
	else
	{
		iRight = p->aRecord[iRecord+1].iSub;
		pBt->aFind[pBt->iFind++] = iRight;
		OsRead(pBt->fd, pRight, PAGE_SIZE, iRight*PAGE_SIZE);
		while(!pRight->nodeHdr.isLeaf)
		{
			iRight = pRight->aRecord[0].iSub;
			pBt->aFind[pBt->iFind++] = iRight;
			OsRead(pBt->fd, pRight, PAGE_SIZE, iRight*PAGE_SIZE);
		}

		//此时即使结点少于规定也上移
		//if( pRight->nodeHdr.nRecord>(MAX_SUB_NUM/2-1) )
		{
			pSrcBuf = &pRight->aRecord[0];
			pDstBuf = &p->aRecord[iRecord];
			memcpy(pDstBuf,pSrcBuf,sizeof(Record));
			updateRoot(pBt,p);
			OsWrite(pBt->fd, p, PAGE_SIZE, iPage*PAGE_SIZE);
			pSrcBuf = &pRight->aRecord[1];
			pDstBuf = &pRight->aRecord[0];
			iAmt = (pRight->nodeHdr.nRecord--)*sizeof(BtreeRecord);
			memmove(pDstBuf,pSrcBuf,iAmt);
			//assert( pDstBuf->key!=pSrcBuf->key );
			OsWrite(pBt->fd, pRight, PAGE_SIZE, iRight*PAGE_SIZE);
		}
		if( pRight->nodeHdr.nRecord>=((MAX_SUB_NUM+1)/2-1) )
		{
			rc = 1;
		}
		else  //结点已经小于最小值,需要再做调整
		{
			memcpy(p,pRight,PAGE_SIZE);
			pBt->iPage = iRight;
		}
	}


	free(pLeft);
	free(pRight);
	return rc;
}
void BtreeAdjust(Btree *pBt, Node* pNode,Node *pParent)
{
	u32 iPage;


	memcpy(pParent, pNode, PAGE_SIZE);
	assert( pBt->iFind>0 );
	iPage = pBt->aFind[--pBt->iFind];
	while(pParent->nodeHdr.nRecord<(MAX_SUB_NUM/2 - 1))
	{
		if( pParent->nodeHdr.isRoot )
		{
			assert( pBt->iFind==0 );
			break;
		}
		memcpy(pNode, pParent, PAGE_SIZE);
		adjustBtree(pBt, pNode, pParent, iPage);
		iPage = pBt->iParent;
	}
	updateRoot(pBt, pParent);
}
void BtreeDelete(Btree *pBt, int key)
{
	Node *pNode = (Node *)malloc(PAGE_SIZE);
	Node *pParent = (Node*)malloc(PAGE_SIZE);
	u32 iPage;

	pBt->pNode = pNode;
	pBt->getFlag = 1;
	if( BtreeFind(pBt, key) )
	{
		log_a("delete key %d page %d offset %d",key,pBt->iPage,pBt->iRecord);
		if( pNode->nodeHdr.isLeaf )
		{
			BtreeDeleteLeaf(pBt, pNode);
			BtreeAdjust(pBt, pNode, pParent);
		}
		else
		{
			if( !BtreeDeleteInside(pBt,pNode) )
			{
				//删除中间记录后，叶子结点的记录不满足最小值
				//此时已经把靠近key的叶子结点移到了key的位置上
				//pNode更新为叶子结点
				BtreeAdjust(pBt, pNode, pParent);
			}
		}
	}
	else
	{
		log_a("cannt find delete %d",key);
	}

	pBt->getFlag = 0;
    free(pNode);
    free(pParent);
}

typedef struct{
	int sum;
	int key;
	int flag;

}TestData;
TestData aData[100];
void test_case(Btree *pBt, int key ,int flag)
{
	static int k=0;
	static int i=0;
	static int isInit = 0;
	static int sum = 0;
	BtreeRecord temp;
	int j;

	if(!isInit)
	{
		memset(aData,0,sizeof(aData));
		isInit = 1;
	}
	if(flag)//添加
	{
		sum++;
		k++;
		if( k>random_()%10 )
		{
			k = 0;
			if(i<100)
			{
				i++;
				aData[i].key = key;
				aData[i].sum = sum;
				aData[i].flag = flag;
			}
			else
			{
				i = 0;
			}
		}
	}

	for(j=0;j<100;j++)
	{
		if(!flag)
		{
			if(aData[j].key == key)
			{
				aData[j].flag = flag;
			}
		}

		if(aData[j].flag)
		{
			if( !BtreeFind(pBt,aData[j].key) )
			{
				log_b("insert %d now %d key %d",aData[j].sum,sum,aData[j].key);
				log_a("page %d offset %d",pBt->iPage,pBt->iRecord);
				assert(0);
			}
			//log_a("insert %d now %d key %d",aData[j].sum,sum,aData[j].key);
			//log_a("page %d offset %d",pBt->iPage,pBt->iRecord);
			OsRead(pBt->fd,&temp,sizeof(BtreeRecord),
					pBt->iPage*PAGE_SIZE+16+
					pBt->iRecord*sizeof(BtreeRecord));
			assert(temp.key==aData[j].key);
		}
	}



	if(i==20)
	{
		for(j=0;j<20;j++)
		{
			if(aData[j].flag)
			{
				log_a("want to find abuf[%d] %d",j,aData[j].key);
				log_a("insert %d now %d",aData[j].sum,sum);
				assert( BtreeFind(pBt,aData[j].key) );
				log_a("find page %d",pBt->iPage);
				OsRead(pBt->fd,&temp,sizeof(BtreeRecord),
						pBt->iPage*PAGE_SIZE+16+
						pBt->iRecord*sizeof(BtreeRecord));
				assert(temp.key==aData[j].key);
			}
		}

	}
}

void btree_test(Btree *pBt)
{
	int key;
	int i,j;
	BtreeRecord record;
	int szRecord = sizeof(BtreeRecord);
	int iOffset;
	u32 maxRecord;
	Node *test1 = (Node*)malloc(PAGE_SIZE);
	Node *test2 = (Node*)malloc(PAGE_SIZE);

	for(i=0; i<1000; i++)
	{
		log_a("i %d",i);
		for(j =0;j<10;j++)
		{
			key = random_();
			log_a("want to insert key %d",key);
			BtreeInsert(pBt,key);
			assert(BtreeFind(pBt,key));
			test_case(pBt,key,1);
			//log_a("find page %d offset %d",pBt->iPage,pBt->iRecord);
		}

		for(j =0;j<100;j++)
		{
			maxRecord = (pBt->pRoot->nodeHdr.nPage-1)*
					(PAGE_SIZE-sizeof(NodeHdr))/szRecord+pBt->mxRecord;
			int tmp = random_()%maxRecord;
			iOffset = tmp*szRecord+(tmp/MAX_SUB_NUM+1)*sizeof(NodeHdr);
			OsRead(pBt->fd, &record, szRecord, iOffset);
			key = record.key;
			log_a("want to find %d key %d",iOffset,key);
			BtreeFind(pBt,key);
		}

		for(j=0;j<2;j++)
		{
			maxRecord = (pBt->pRoot->nodeHdr.nPage-1)*
					(PAGE_SIZE-sizeof(NodeHdr))/szRecord+pBt->mxRecord;
			int tmp = random_()%maxRecord;
			iOffset = tmp*szRecord+(tmp/MAX_SUB_NUM+1)*sizeof(NodeHdr);
			OsRead(pBt->fd, &record, szRecord, iOffset);
			key = record.key;
			log_a("want to delete %d",iOffset);
			OsRead(pBt->fd,test1,4096,(iOffset/4096)*4096);
			BtreeDelete(pBt,key);
			test_case(pBt,key,0);

			if(BtreeFind(pBt,key))
			{

				OsRead(pBt->fd,test2,4096,pBt->iPage*4096);
				BtreeFind(pBt,key);
				BtreeDelete(pBt,key);
				BtreeFind(pBt,key);
				log_a("find key %d page %d offset %d",key,pBt->iPage,pBt->iRecord);
				assert(0);
		     	assert( !BtreeFind(pBt,key) );
			}
		}
	}
}

void BtreeTest(void)
{
	char *zFileName = "testdata";
	Btree *pBt = OpenBtree(zFileName);
	time_t t1,t2;
	t1 = time(NULL);
	btree_test(pBt);
	t2 = time(NULL);
	printf("time %ld\n",t2-t1);
    CloseBtree(pBt);
	//remove(zFileName);
}
