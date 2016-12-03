#include<stdio.h>


int main()
{
 int i,j,time,sum_bt=0, n;
 //char c;
 int p[20][7];

printf("enter the number of Processes:\n");
scanf(" %d",&n);

for(i = 0; i< n; i++)
  for(j = 0; j< 7; j++)
    p[i][j] = 0;


for(i=0;i<n;i++){ 
    printf("\nEnter Arrival Time and Burst Time for Process Process Number %d :\n",i+1); 
    scanf(" %d",&p[i][1]); 
    scanf(" %d",&p[i][2]);
    p[i][0] = i+1; 
    //rt[count]=bt[count]; 
  } 
 
for(i = 0; i < 5; i++)
  sum_bt+=p[i][2];

printf("time\tName\tArrival Time\tBurst Time\tWaiting Time\tTurnAround Time\n");
  for(time=p[0][1];time<sum_bt;){
   float hrr=0;
   int loc;
    for(i=0;i<5;i++){
      
      if(p[i][1]<=time && p[i][6]!=1){
        //printf("%d\n", p[i][0]);
        float temp=(1 + ((float)(time-p[i][4]))/p[i][2]);
        //printf("%f\n", temp);
        if(hrr < temp){
          hrr=temp;
          loc=i;
       }      
      }
    }
  //  printf("%f\n", hrr);
  //printf("%d\n", loc);
      printf("%d-%d\t", time, time+p[loc][2]);
     time+=p[loc][2];
     p[loc][3] = time;
     p[loc][4]=time-p[loc][1]-p[loc][2];
     p[loc][5]=time-p[loc][1];
   //  p[loc].ntt=((float)p[loc].tt/p[loc].bt);
     p[loc][6]=1;
   //  avgwt+=p[loc][4];
     printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n",p[loc][0],p[loc][1],p[loc][2],p[loc][4],p[loc][5]);
  }

//printf("\nAverage waiting time:%f\n",avgwt/n);
return 0;
}
