#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

typedef struct Array
{
    int row;               //行号
    int col;               //列号
}Array;

typedef struct Stack
{
    Array data[64];
    int top;
}Stack;                 //栈结构体类型定义

int a[9][9]={0};        //显示棋盘，没有用到0行0列
int count=0;            //全局变量  用于计数  记录步号
Stack *s;               //栈的定义
int rol=0;              //计算回溯次数

                /*栈操作函数声明*/
void InitStack(Stack *s);
int Push(Stack *s,Array p);
int Pop(Stack *s,Array *p);
int Gettop(Stack *s,Array *p);
int IsEmpty(Stack *s);
int selecty(int row,int col,int *m,int *n,Array r);

int main()
{
    system("title 任自强");//设置标题


    int i,j,flag;
    Array p,q,r;

    s=(Stack *)malloc(sizeof(Stack));
    InitStack(s);


    printf("请输入一个起始点的坐标:");
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

  if(flag==0) //flag=0表示有可走的点,入栈
  {
      q.row=i;
      q.col=j;
      Push(s,q);
      count++;
      a[i][j]=count;
      r.row=0;
      r.col=0;
  }
  else  //flag=1表示没有可走的点,(row col)退栈
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
 printf("\n\n一共回溯了%d次\n\n",rol);
 printf("按任意数字键并回车查看动态演示\n");
 int g;
 scanf("%d",&g);
 system("cls");
 printf("\n\n\n                         演示开始\n");
 Sleep(1000);
 system("cls");
                /*动态演示*/
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
    printf("\n\n\n                     演示完成！\n\n\n");

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

int cal_count(Array q,int row,int col) //统计可走的出口
{
 Array p[8];
 int i,result=0;

 p[0].row=q.row-2;p[0].col=q.col+1;  //一个点的八个可能方向
 p[1].row=q.row-1;p[1].col=q.col+2;
 p[2].row=q.row+1;p[2].col=q.col+2;
 p[3].row=q.row+2;p[3].col=q.col+1;
 p[4].row=q.row+2;p[4].col=q.col-1;
 p[5].row=q.row+1;p[5].col=q.col-2;
 p[6].row=q.row-1;p[6].col=q.col-2;
 p[7].row=q.row-2;p[7].col=q.col-1;

 for(i=0;i<8;i++)  //走出棋盘以及(row,col)本身不计
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

void sort(Array p[8],int row,int col)//对(row,col)的可能方向做出口数从小到大的排序
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

  for(i=0;i<7;i++)//选择排序
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

int selecty(int row,int col,int *m,int *n,Array r)  //判断是否有可走路径
{
 Array p[8];
 int i,j=-1,flag=1;

 p[0].row=row-2;p[0].col=col+1;  //一个点的八个可能方向
 p[1].row=row-1;p[1].col=col+2;
 p[2].row=row+1;p[2].col=col+2;
 p[3].row=row+2;p[3].col=col+1;
 p[4].row=row+2;p[4].col=col-1;
 p[5].row=row+1;p[5].col=col-2;
 p[6].row=row-1;p[6].col=col-2;
 p[7].row=row-2;p[7].col=col-1;

 sort(p,row,col);//对八个可能方向的下一步出口排序 递增排序

 for(i=0;i<8;i++)  //如果已经出了棋盘,则给指针赋值为空
 {
  if(p[i].row>8||p[i].col>8||p[i].row<1||p[i].col<1)
  {p[i].row=0;p[i].col=0;}
 }

 if(r.row!=0&&r.col!=0)  //r记录了退栈的那个点,下次搜索要从r的下一个开始
  for(i=0;i<8;i++)
  {
   if(p[i].row==0&&p[i].col==0) continue;
   if(p[i].row==r.row&&p[i].col==r.col)
   {j=i;break;}
  }

  for(i=j+1;i<8;i++)  //按顺序搜索方向
  {
   if(p[i].row==0&&p[i].col==0)  continue;
            if(a[p[i].row][p[i].col]==0)
   {
    *m=p[i].row;  //*m  *n返回可走的横纵序号
    *n=p[i].col;
    flag=0;
    break;
   }
  }
  return flag;
}


