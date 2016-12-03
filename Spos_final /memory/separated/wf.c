/*#include<stdio.h>
int main(){
int i,j,temp,f[10],fp[10];int no,p[15],part[15],pno,pr[15],prmem[15];
//Input partition size
printf("\n*******************************************");
printf("\n IMPLEMENTATION OF WORST-FIT ALGORITHM");
printf("\n*******************************************");
printf("\n Enter the number of partitions");
scanf("%d",&no);
for(i=1;i<=no;i++){
p[i]=i;
printf("Enter the memory for partition %d:\t",i);
scanf("%d",&part[i]);
}//Arrange partitions in descending order
for(i=1;i<=no;i++){
for(j=1;j<=i;j++){
if(part[j]<part[i]){
temp=part[i];
part[i]=part[j];
part[j]=temp;
temp=p[i];
p[i]=p[j];
p[j]=temp;
}
}
}
printf("\nFree memory");
for(i=1;i<=no;i++){
printf("\n partition %d: \t %d",p[i],part[i]);
}
//Input process details
printf("\n Enter the number of process");
scanf("%d",&pno);
for(i=1;i<=pno;i++){pr[i]=i;
printf("Enter the size for process %d:\t",i);
scanf("%d",&prmem[i]);
}//Applying Worst-Fit Method
printf("\n----------------------------------------\n");
printf("PROCESS|\t PARTITION| \t FREE_MEMORY|\n");
printf("\n----------------------------------------\n"); 
j=1;
for(i=1;i<=no;i++){
f[i]=0;fp[j]=0;
}
while(j<=pno){
for(i=1;i<=no;i++){
if((part[i]>=prmem[j]) && (f[i]==0)){
part[i]=part[i]-prmem[j];
fp[j]=1;
//process alloted
f[i]=1;
//partition alloted
printf("%d \t\t %d \t\t %d \n",pr[j],p[i],part[i]);
goto l1;
}
}
l1: j++;
}
for(i=1;i<=no;i++){
if(f[i]==0){
printf(" \t %d \t %d \n",p[i],part[i]);
}
}
printf("The following process is not allocatted: \n");
for(i=1;i<=pno;i++){
if(fp[i]==0){
printf(" %d ",pr[i]);
}
}
return 0;
}*/



#include<stdio.h>
#define max 25

void main()
{
 int frag[max],b[max],f[max],i,j,nb,nf,temp,highest=0;
 static int bf[max],ff[max];

 printf("\n\tMemory Management Scheme - Worst Fit");
 printf("\nEnter the number of blocks:");
 scanf("%d",&nb);
 printf("Enter the number of files:");
 scanf("%d",&nf);
 printf("\nEnter the size of the blocks:-\n");
 for(i=1;i<=nb;i++) {printf("Block %d:",i);scanf("%d",&b[i]);}
 printf("Enter the size of the files :-\n");
 for(i=1;i<=nf;i++) {printf("File %d:",i);scanf("%d",&f[i]);}

 for(i=1;i<=nf;i++)
 {
  for(j=1;j<=nb;j++)
  {
   if(bf[j]!=1)    //if bf[j] is not allocated
   {
    temp=b[j]-f[i];
    if(temp>=0)
    if(highest<temp)
    {
     ff[i]=j;
     highest=temp;
    }
   }
  }
  frag[i]=highest;
  bf[ff[i]]=1;
  highest=0;
 }
 printf("\nFile_no:\tFile_size :\tBlock_no:\tBlock_size:\tFragement");
 for(i=1;i<=nf;i++)
 printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d",i,f[i],ff[i],b[ff[i]],frag[i]);
}

