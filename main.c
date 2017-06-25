#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct Array
{
    int row;               //�к�
    int col;               //�к�
}Array;

typedef struct Stack
{
    Array data[64];
    int top;
}Stack;                 //ջ�ṹ�����Ͷ���

int a[9][9]={0};        //��ʾ���̣�û���õ�0��0��
int count=0;            //ȫ�ֱ���  ���ڼ���  ��¼����
Stack *s;               //ջ�Ķ���
int rol=0;              //������ݴ���

                /*ջ������������*/
void InitStack(Stack *s);
int Push(Stack *s,Array p);
int Pop(Stack *s,Array *p);
int Gettop(Stack *s,Array *p);
int IsEmpty(Stack *s);
int selecty(int row,int col,int *m,int *n,Array r);

int main()
{
    system("title ����ǿ");//���ñ���


    int i,j,flag;
    Array p,q,r;

    s=(Stack *)malloc(sizeof(Stack));
    InitStack(s);


    printf("������һ����ʼ�������:");
    scanf("%d,%d",&i,&j);
    if(i>=1&&i<=8&&j>=1&&j<=8)
    {
        p.row=i;
        p.col=j;

        count++;
        a[p.row][p.col]=count;

        Push(s,p);
        r.row=0;
        r.col=0;
    }

 while(count<64&&!IsEmpty(s))
 {
     Gettop(s,&p);
     flag=selecty(p.row,p.col,&i,&j,r);

  if(flag==0) //flag=0��ʾ�п��ߵĵ�,��ջ
  {
      q.row=i;
      q.col=j;
      Push(s,q);
      count++;
      a[i][j]=count;
      r.row=0;
      r.col=0;
  }
  else  //flag=1��ʾû�п��ߵĵ�,(row col)��ջ
  {
      Pop(s,&r);
      count--;
      rol++;
      a[r.row][r.col]=0;
  }

 }

 if(IsEmpty(s))
 {
     printf("no road\n");
 }


     printf("the result is :\n");
 for(i=1;i<=8;i++)
    {
        for(j=1;j<=8;j++)
        {printf("%3d ",a[i][j]);
        }
        printf("\n");
    }
    Sleep(100);
 printf("\n\nһ��������%d��\n\n",rol);
 printf("���������ּ����س��鿴��̬��ʾ\n");
 int g;
 scanf("%d",&g);
 system("cls");
 printf("\n\n\n                         ��ʾ��ʼ\n");
 Sleep(1000);
 system("cls");
                /*��̬��ʾ*/
 int s,b,step;
 int n=1;
 for(step=1;step<65;step++)
 {
     for(s=1;s<9;s++)
     {
         for(b=1;b<9;b++)
         {
             if(a[s][b]<=step)
                {
//                    for(n=1;n<s;n++)
//                        printf("\n");
//                    for(n=1;n<b;n++)
//                        printf("   ");
//                    printf("%4d",a[s][b]);
//                    Sleep(500);
//                    system(" cls ");
                      printf("%3d",a[s][b]);
                }
                else
                    printf("   ");


         }
         printf("\n");
     }
     Sleep(500);
     system("cls");
 }
    printf("\n\n\n                     ��ʾ��ɣ�\n\n\n");

}

void InitStack(Stack *s)//
{s->top=-1;}

int Push(Stack *s,Array p)
{
 if(s->top>=64)  return 0;
 s->top++;
 s->data[s->top].row=p.row;
 s->data[s->top].col=p.col;
 return 1;
}

int Pop(Stack *s,Array *p)
{
 if(s->top==-1) return 0;
    p->row=s->data[s->top].row;
 p->col=s->data[s->top].col;
 s->top--;
 return 1;
}

int Gettop(Stack *s,Array *p)
{
 if(s->top==-1)  return 0;
    p->row=s->data[s->top].row;
 p->col=s->data[s->top].col;
 return 1;
}

int IsEmpty(Stack *s)
{
 if(s->top==-1)  return 1;
 else return 0;
}

int cal_count(Array q,int row,int col) //ͳ�ƿ��ߵĳ���
{
 Array p[8];
 int i,result=0;

 p[0].row=q.row-2;p[0].col=q.col+1;  //һ����İ˸����ܷ���
 p[1].row=q.row-1;p[1].col=q.col+2;
 p[2].row=q.row+1;p[2].col=q.col+2;
 p[3].row=q.row+2;p[3].col=q.col+1;
 p[4].row=q.row+2;p[4].col=q.col-1;
 p[5].row=q.row+1;p[5].col=q.col-2;
 p[6].row=q.row-1;p[6].col=q.col-2;
 p[7].row=q.row-2;p[7].col=q.col-1;

 for(i=0;i<8;i++)  //�߳������Լ�(row,col)������
 {
  if(p[i].row>8||p[i].col>8||p[i].row<1||p[i].col<1)
  {p[i].row=0;p[i].col=0;}
  if(p[i].row==row&&p[i].col==col)
  {p[i].row=0;p[i].col=0;}
 }

 for(i=0;i<8;i++)
  if(p[i].row!=0&&p[i].col!=0)
   result++;

  return result;
}

void sort(Array p[8],int row,int col)//��(row,col)�Ŀ��ܷ�������������С���������
{
 int result[8],t;
 int i,k,j;
 int flag;
 Array temp;

 for(i=0;i<8;i++)
  result[i]=-1;

 for(i=0;i<8;i++)
  if(p[i].row!=0&&p[i].col!=0)
           result[i]=cal_count(p[i],row,col);

  for(i=0;i<7;i++)//ѡ������
  {
   if(result[i]!=-1)
   {
    k=i;
    for(j=i+1;j<8;j++)
     if(result[j]<result[k])  k=j;

     if(k!=i)
     {
      t=result[k];
      result[k]=result[i];
      result[i]=t;
      temp=p[k];
      p[k]=p[i];
      p[i]=temp;
     }
   }
  }



}

int selecty(int row,int col,int *m,int *n,Array r)  //�ж��Ƿ��п���·��
{
 Array p[8];
 int i,j=-1,flag=1;

 p[0].row=row-2;p[0].col=col+1;  //һ����İ˸����ܷ���
 p[1].row=row-1;p[1].col=col+2;
 p[2].row=row+1;p[2].col=col+2;
 p[3].row=row+2;p[3].col=col+1;
 p[4].row=row+2;p[4].col=col-1;
 p[5].row=row+1;p[5].col=col-2;
 p[6].row=row-1;p[6].col=col-2;
 p[7].row=row-2;p[7].col=col-1;

 sort(p,row,col);//�԰˸����ܷ������һ���������� ��������

 for(i=0;i<8;i++)  //����Ѿ���������,���ָ�븳ֵΪ��
 {
  if(p[i].row>8||p[i].col>8||p[i].row<1||p[i].col<1)
  {p[i].row=0;p[i].col=0;}
 }

 if(r.row!=0&&r.col!=0)  //r��¼����ջ���Ǹ���,�´�����Ҫ��r����һ����ʼ
  for(i=0;i<8;i++)
  {
   if(p[i].row==0&&p[i].col==0) continue;
   if(p[i].row==r.row&&p[i].col==r.col)
   {j=i;break;}
  }

  for(i=j+1;i<8;i++)  //��˳����������
  {
   if(p[i].row==0&&p[i].col==0)  continue;
            if(a[p[i].row][p[i].col]==0)
   {
    *m=p[i].row;  //*m  *n���ؿ��ߵĺ������
    *n=p[i].col;
    flag=0;
    break;
   }
  }
  return flag;
}


