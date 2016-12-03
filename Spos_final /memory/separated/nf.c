#include<stdio.h>
void main()
{
 int i,j,npart,prs,partsize[50],current;
 printf("enter no.of partitions");
 scanf("%d",&npart);
 printf("enter process size:");
 scanf("%d",&prs);
 for(i=1;i<=npart;i++)
 {
  printf("enter size of %d partition",i);
  scanf("%d",&partsize[i]);
 }
 printf("\n enter current position:");
 scanf("%d",&current);
 for(j=current+1;j<=npart;j++)
 {
  if(prs<=partsize[j])
  {
   partsize[j]=partsize[j]-prs;
   printf("\n process fits in %d position\n",j);
   printf("fragmentation is %d",partsize[j]);
   break;
  }
 }

}
