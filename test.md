# ǰ��
֮ǰ����һ���Ĺ������������������ֹ������Ѿ���ը�ˣ�����ҪȥѰ��һ��ȫ�µ��㷨�����ٹ���������ν���ѧϰ���㷨Ҳ����Ч�����Ƕ���û�м�����Դ������˵�������á�  
         
 ����ʵ��ͦϲ����ѧ�ģ����ܾ�����ѧ�ϵ�һЩ˼�뷽�����ܶ�д���������������������Ѿ�������ʶ���Լ��Ĵ��Բ��ʺ�ȥ������ѧ���⡣��ѧ�������Ǿ�ȷ�ģ���ѧ�鼮�������������˼Ҳ�������ģ����ڸ����̵����ܺ������������ߵ���˼�����Ƕ�������ôһ������һ�������˵�������о������������ʵ����˼���Լ�������˼��һ�����������൱ʹ�ࡣ�������һЩ�������ѧ����������ɺܶ��������ѧ������Ӷ��ɵģ������Ҫ���õļ��������ڶ�������ʱ�ܹ�ʮ������ļ�ס֮ǰ�����ĸ�����ҵļ������ܲ�����涨����¸�����Ҫ����֮ǰ�ĸ�����Ҿ�������֮ǰ�ĸ�������ݲ������д���һ������ĸ�������������������ͻ᲻֪���ơ�
     
��C����ȥ������ѧ���ܿ��Խ�����Ķ���ѧʱ������������������ʵ���������������ƫ���ֻ��Ҫdebugһ�£�ȥ׷�ٵ��״�����һ�и��Լ�����ⲻһ�����Ӷ������Լ��������⡣����һЩ�������ɺܶ�����������ɵģ���C��������Щ����������ɺ���������eclipse�����Ŀ��������������Ҳ����ĸ���ҿ�����ת�����������������ϸ�о���Ҳ���Ժܿ��֪�����ָ���֮����������ϵ��ֻҪ�Ƚ϶�Ӧ�������ʽ�����н���Ϳ���֪���ˡ�
             
Ϊ�˴���ļ򵥺ͷ��㣬�������Ե�һЩ��ѧ�ϵ��Ͻ��ԣ�Ҳ���Ǻ�ע��������̵���ƣ�Ŀ����Ҫ����ȡ��ѧ��˼�룬��һЩ����ĸ���ʵ�������Ӷ��ܸ��õ������ѧ�Ľṹ��ʹ��ѧ�����ܹ�ͨ�������Ĵ��벽����ֳ������Ҵ����о���������������ѧ�������߼�������������ݣ��ȴӳ��������ʼ���ο��Ľ̲���E.Artin�ġ�٤�޻����ۡ������������һ���������������������顣

# 1  �û�Ⱥ 
Ⱥ�Ǵ�����������ĸ�����û�Ⱥ��һ���������Ⱥ��Ⱥ�ĸ�����Ǵ��û��е����ģ����������о��û�Ⱥ��

## 1.1  �û�
���������û��ĸ�����ﲻ����ѧ��������ȷ���壬ֻ��ʵ�����Ӱ��������˵��������׾Ϳ����ˡ� 
          
������һ��5Ԫ���У�1 2 3 4 5�������ǰ��������е�5��Ԫ��������һ��˳��Ϳ��Եõ�����һ�������ˣ������2��4������1��3�����õ���һ�����У�3,4,1,2,5�������ǿ��԰��û���ӳ���ʾ          

$$ f=\left\{
\begin{aligned}
1  \rightarrow & 3\\
2  \rightarrow & 4 \\
3  \rightarrow & 1 \\
4  \rightarrow & 2 \\
5  \rightarrow & 5\\
\end{aligned}
\right.
$$
���Ϊ
$$
\begin{pmatrix}
1 & 2 &  3&4  &5 \\ 
 3&  4& 1 & 2 & 5
\end{pmatrix}
$$

����һ�ָ��򵥵ļǷ�������ѣ�1 2 3 4 5����������е�ÿ��Ԫ�ض������ƶ�һ��λ�õõ��û�       
$$
\begin{pmatrix}
1 & 2 &  3&4  &5 \\ 
 2&  3& 4 & 5 & 1
\end{pmatrix}
$$
�����û������ֻ�������ӳ�����Եõ�1->2->3->4->5->1,����ֱ�����ֻ��е���һ�����б�ʾ����1 2 3 4 5��       
ÿһ���û������Ա�ʾ��һЩ�ֻ�����ϣ�����     
$$
\begin{pmatrix}
1 & 2 &  3&4  &5 \\ 
 3&  4& 1 & 2 & 5
\end{pmatrix}
$$
���Ա�ʾΪ(1 3)(2 4)(5),��1��3�ֻ���2��4�ֻ���5���䣬Ѱ���ֻ��ķ�����:     
1->3->1,2->4->2,����ʼλ�ÿ�ʼ����ӳ�䣬�ص��������һ���ֻ���
## 1.2 Ⱥ
Ⱥ����һ�������е�Ԫ�ر��缯��A={a,b,c,d....}������{$\cdot$}��ɵģ�Ҫע����Ǽ����е�Ԫ�ز�һ�������֣�����Ҳ��һ���ǳ˷������Ϻ�����������ʲô��Ҫ���Լ����塣��ЩԪ�ص����������������4���������ܳ���Ⱥ     

 1. �����գ���$a\cdot b$�Ľ������A��
 2. ����ɣ���$(a\cdot b)\cdot  c =a\cdot (b\cdot  c)$
 3. �е�λԪe���� ���������a�����ڵ�λԪeʹ��  $e\cdot a= a$
 4. ������Ԫ�������������a������b����$b\cdot a= e$,��ôb����a������Ԫ
 
һ����˵Ⱥ��û�й涨����Ҫ���㽻���ɣ�������˵�����涨����û���Ⱥ�����ȶ����û�������{$\cdot$}���£����磨1 2 3 4 5��$\cdot$ (1 3)(2 4)(5)�ļ���������

 ![���������ͼƬ����](./1.png)    
 
��   
 
$$
\begin{pmatrix}
1 & 2 &  3&4  &5 \\ 
 2&  3& 4 & 5 & 1
\end{pmatrix}\cdot 
\begin{pmatrix}
1 & 2 &  3&4  &5 \\ 
 3& 4& 1 & 2 &5
\end{pmatrix} =
\begin{pmatrix}
1 & 2 &  3&4  &5 \\ 
 4&  5& 2 & 3 & 1
\end{pmatrix}
$$

���������ô���֤���û�����Ⱥ��4�����ʣ�֤����1������ʱ��Ҫ���û��ĸ�����һЩ�����˵������дһ�������ж����Ԫ���ǲ����û��������������Ȼ����ģ�����д�ɴ��벢�����������������ȥ��������Ҫ֤�����ǵ�2,3,4������
# 2  ����ʵ��
## 2.1 ���ݽṹ
������Ҫ����һ������ϵͳ�����ݽṹ��������������
```c
typedef struct OperateSys OperateSys;
struct OperateSys
{
    void *pBaseEle;//��λԪ
    int (*xIsEqual)(void *, void *);//�ж�2��Ԫ���Ƿ����
    void *(*xGen)(int iNum);//���ݸ�������Ȼ�����ɼ����е�Ԫ
    void *(*xInvEle)(void *);//����һ��Ԫ��������Ԫ
    void *(*xRecursiveGen)(void *pEle);//����һ��Ԫ�صݹ�������һ��Ԫ�أ���ʱ����
    void *(*xOperat)(void *, void *);//����
    void *(*xConjOperat)(void *, void *);//�������㣬�������������ر�˵��
};
```
��ʵ���û�Ⱥ�Ĵ���ϵͳʱ������Ҫ�����û�Ԫ�صĽṹ

```c
typedef struct FivePerm
{
    u8 aNum[5];
}FivePerm;
```

�������½�һ���û�Ⱥ��OperateSys�Ķ���
```c
 OperateSys *PermutationObj(void)
{
  //(1 2 3 4 5)��Ϊ��λԪ
    static FivePerm baseItem =
    {
        .aNum[0] = 1,
        .aNum[1] = 2,
        .aNum[2] = 3,
        .aNum[3] = 4,
        .aNum[4] = 5,
    };

    //�������Ͳ�ƥ�䣬��voidȥ����
    static OperateSys perm =
    {
        NULL,
        (void*)FivePermEqual,
        (void*)FivePermGen,
        (void*)FivePermInv,
        (void*)FivePermRec,
        (void*)FivePermOp,
        (void*)FivePermOp1,
    };
    perm.pBaseEle = &baseItem;
    return &perm;
}
```
## 2.2 �û�����
�û���һ�����ϣ�Ϊ��ʵ�������������ϵͳ����������Ҫ�����û�������Ԫ�أ���5��Ԫ�ص��û�Ϊ������ЩԪ�ؾ���(1 2 3 4 5)��һ��ȫ���У�ȫ�����ܹ���120�����������뷶Χ��0~119�������㷨���õ��ǵݹ��˼�룬��1�����ֿ��ܵ�ȡֵΪ1,2,3,4,5���֣�ȷ����1������֮��������еݹ�������ʣ��4�����ֵ�ȫ����

```c
//pPermΪ��ʼ����Ԫ��Ϊ(1 2 3 4 5)
//left��ʾ�û�������ߵ�һ��Ԫ�أ�
//right��ʾ�û������ұߵ�һ��Ԫ��
//Ҫ���ɵ�Ԫ�ص����
void FivePermTrav(FivePerm *pPerm, int left, int right, int num)
{
    static int cnt = 0;
    static int RecCnt = 0;
    int i;
    
    //cnt�Ǿ�̬��������һ�ε��õݹ�ʱ����0
    if( RecCnt==0 )
    {
        cnt = 0;
    }
    RecCnt++;
    //�ҵ�Ҫ���ɵ�Ԫ�غ󷵻�
    if( cnt>num )
    {
        RecCnt--;
        return;
    }
    //�ݹ�������ҵ�һ���û�
    if( left==right )
    {
        cnt++;
    }
    else
    {
        //�����û�������ߵ�Ԫ���������ұ�ÿ��Ԫ�ص��������ݹ�
        for(i=left; i<=right; i++)
        {
            SwapNum(&pPerm->aNum[i],&pPerm->aNum[left]);
            FivePermTrav(pPerm,left+1,right,num);
           // �Ѿ��ҵ�Ҫ���Ԫ�ؾͲ�Ҫ�����ݹ���
            if( cnt>num )
            {
                break;
            }
            //�ݹ���Ϻ󷵻ؽ�Ԫ�ػ����������ֳ�ʼ״̬����
            SwapNum(&pPerm->aNum[i],&pPerm->aNum[left]);
        }
    }
    RecCnt--;
}
 //
FivePerm *FivePermGen(int num)
{
    FivePerm *p;
    u8 aInit[5] = {1,2,3,4,5};
    num = num%120;
    p = malloc(sizeof(FivePerm));
    memcpy(p->aNum,aInit,sizeof(aInit));
    FivePermTrav(p,0,4,num);
    return p;
}
```

## 2.3 �û��˷�����
������ʵ��1.2�ڶ�����û��˷�����,����һ��ӳ�����㣬ֻҪ�ѵ�2������ӳ��Ľ����Ϊ��1���������±�õ�����������:

```c
FivePerm *FivePermOp(FivePerm *p1, FivePerm *p2)
{
    FivePerm *p;
    int i,j;
    p = malloc(sizeof(FivePerm));
    memset(p,0,sizeof(FivePerm));

    for(i=0; i<5; i++)
    {
        j = p2->aNum[i]-1;//��ȡp2��ӳ����
        p->aNum[i] = p1->aNum[j];//��j��Ϊp1���±�     
    }
    return p;
}
```
�����û����Ͽ����ٶ���һ����������{}������������ (1 3)(2 4)(5) $\circ$��1 2 3 4 5���������������£���д����Ԫ���û����ٰ���Ԫд���ֻ���ʽ����Ԫ�Ľ��������Ԫ�����ֻ�
<center>
![���������ͼƬ����](https://img-blog.csdnimg.cn/20190416112857603.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3BmeXN3,size_16,color_FFFFFF,t_70)
</center>
�������Ƿ������µ�ʽ��������Ϊ��ʽ(1)
$$
\begin{aligned}
&
\begin{pmatrix}
1 & 2 &  3&4  &5 \\ 
 2&  3& 4 & 5 & 1
\end{pmatrix}\cdot 
\begin{pmatrix}
1 & 2 &  3&4  &5 \\ 
 3& 4& 1 & 2 &5
\end{pmatrix} \\
=& \begin{pmatrix}
1 & 2 &  3&4  &5 \\ 
 3& 4& 1 & 2 &5
\end{pmatrix}\circ\begin{pmatrix}
1 & 2 &  3&4  &5 \\ 
 2&  3& 4 & 5 & 1
\end{pmatrix}\\
=&\begin{pmatrix}
1 & 2 &  3&4  &5 \\ 
 4&  5& 2 & 3 & 1
\end{pmatrix} 
\end{aligned} \tag{1}
$$
���û��ĳ˷���������2��Ԫ�ؽ�����Ĺ�����������ȵģ���ôΪʲô������أ��������ô�����ʵ�ֹ������㣬����ٵ��������׸�죬���پ�һ�����͵����ӣ�

![���������ͼƬ����](https://img-blog.csdnimg.cn/20190416120839733.PNG?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3BmeXN3,size_16,color_FFFFFF,t_70)


������ͼ�õ�����ľ���ʵ��
```c
FivePerm *FivePermOp1(FivePerm *p1, FivePerm *p2)
{
    FivePerm *p;
    int i,j;
    p = malloc(sizeof(FivePerm));
    memset(p,0,sizeof(FivePerm));
    for(i=0; i<5; i++)
    {
        //��������Ҫ��p2��Ԫ�ؽ����û�
        //p2���ĸ�Ԫ�ػỻ��i��λ����
        //����p1��ӳ�����Ϳ��Եõ�Ҫ�û���λ��
        //ע�⵽p2��p����1���ֻ���ʾ���û���
        j = p1->aNum[i]-1;
        p->aNum[i] = p2->aNum[j];
    }
    return p;
}
```
�Ա�FivePermOp��FivePermOp1�Ĵ�����Կ�����ʽ����ȫһ���ģ�ֻ����p1��p2������λ�ã��������ǿ�����ʽ��1���ǳ�����
 ##  2.4 �û�Ⱥ��������
 
���´����������Ԫ���㷨������Գ���дд������Ԫ�Ĵ��룬��ᷢ�ֺ�������Ԫ�Ĵ���һģһ������Ҳ��֤����**Ⱥ������Ԫ�ض�������Ԫ**
```c
FivePerm *FivePermInv(FivePerm *p1)
{
    FivePerm *p;
    int i,j;
    p = malloc(sizeof(FivePerm));
    memset(p,0,sizeof(FivePerm));

    //������������Ԫ��������Ԫ�ڴ����ϵ���ʽ����ͬ��
    for(i=0; i<5; i++)
    {
        j = p1->aNum[i];
        p->aNum[j-1] = i+1;
    }

    return p;
}
```
## 2.4 Ⱥ��֤��
����֤��Ⱥ����������:
�����

```c
int AssociativeLaw(OperateSys *pOpSys)
{
    int rc = 0;
    int i,j,k;
    void* pT[7];
    for(i=0; i<10; i++)
    {
        //�����������α�������������3���û�ԪpT[0]��pT[1]��pT[2]
        for(j=0; j<3; j++)
        {
            k = FakeRand(i+j*10);
            pT[j] = pOpSys->xGen(k);
        }
        //֤��(pT[0]*pT[1])*pT[2]=pT[0]*(pT[1]*pT[2])
        pT[3] = pOpSys->xOperat(pT[1],pT[2]);
        pT[4] = pOpSys->xOperat(pT[0],pT[1]);
        pT[5] = pOpSys->xOperat(pT[0],pT[3]);
        pT[6] = pOpSys->xOperat(pT[4],pT[2]);

        rc = pOpSys->xIsEqual(pT[5],pT[6]);

        for(j=0; j<7; j++)
        {
            free(pT[j]);
        }
        assert( rc );
    }

    loga("associative ok");
```
�е�λԪ

```c
int HasIdentityEle(OperateSys *pOpSys)
{
    int rc = 0;
    int i,k;
    void* pEle;
    void* pGen;
    //�������10���û�Ԫ
    for(i=0; i<10; i++)
    {
        k = FakeRand(i);
        pGen = pOpSys->xGen(k);
        pEle = pOpSys->xOperat(pOpSys->pBaseEle,pGen);
        //֤����λԪ��Ⱥ�е���һԪ�����Ȼ���ڸ�Ԫ
        rc = pOpSys->xIsEqual(pGen,pEle);
        free(pGen);
        free(pEle);
        assert( rc );
    }

    loga("identity ok %d",rc);
    return rc;
}
```
���ڿ���Ԫ

```c
int HasInvEle(OperateSys *pOpSys)
{
    int rc = 0;
    int i,k;
    void* pEle;
    void* pGen;
    void* pInv;
    for(i=0; i<10; i++)
    {
        k = FakeRand(i+2);
        pGen = pOpSys->xGen(k);
        //�������10��Ԫ������pOpSys->xInvEle���� pInv
        pInv = pOpSys->xInvEle(pGen);
        //֤��pInv���ǿ���Ԫ
        pEle = pOpSys->xOperat(pGen,pInv);
        rc = pOpSys->xIsEqual(pOpSys->pBaseEle,pEle);
        free(pGen);
        free(pEle);
        free(pInv);
        assert( rc );
    }

    loga("inv ok %d",rc);
    return rc;
}
```
# 3�ο�����
https://github.com/pfysw/CMath