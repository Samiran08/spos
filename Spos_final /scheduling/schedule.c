#include<stdio.h>
#include<stdlib.h>
#include <string.h>
typedef struct cpu{
	int processid;
	int burst;
	int arrival;
	int priority;
}cpu;
struct data{
	char pn[3];
	int a,b,p,t;
}d[20];
cpu cpu1[20];

void accept(int ch,int num);
void fcfs(cpu cpu1[], int num);
void swap ( int k, int l);
void sjf(cpu cpu1[], int num );
void srtf(cpu cpu1[], int num);
void rr(cpu cpu1[], int num);
void hrrn();
void pno(cpu cpu1[], int num);
void pyes(cpu cpu1[], int num);
int main() {
	
	int ch, num, i = 1;
	do{
	printf("\t\t\t\t********************MENU**************************\n");
	printf("\t\t\t\t\t\t1 FCFS\n \n");
	printf("\t\t\t\t\t\t2 SJF \n\n");
	printf("\t\t\t\t\t\t3 SRTF \n\n");
	printf("\t\t\t\t\t\t4 ROUND ROBIN\n\n");
	printf("\t\t\t\t\t\t5 HRRN\n\n");
	printf("\t\t\t\t\t\t6 PRIORITY NON PREEMPTIVE\n\n");
	printf("\t\t\t\t\t\t7 PRIORITY PREEMPTIVE\n\n");
	scanf("%d", &ch);
	switch(ch) {
		case 1:printf("\nenter number of processes: ");
			scanf("%d",&num);
			accept(ch,num);
			fcfs(cpu1, num);
			break;
		case 2:printf("\nenter number of processes: ");
			scanf("%d",&num);
			accept(ch,num);	
			sjf(cpu1, num);
			break;
		case 3:printf("\nenter number of processes: ");
			scanf("%d",&num);
			accept(ch,num);
			srtf(cpu1, num);
			break;
		case 4: printf("\nenter number of processes: ");
			scanf("%d",&num);
			
			accept(ch,num);
			rr(cpu1, num);
			break;
		case 5: hrrn();
			break;
		case 6:printf("\nenter number of processes: ");
			scanf("%d",&num);
			accept(ch,num);
			pno(cpu1, num);
			break;
		case 7:printf("\nenter number of processes: ");
			scanf("%d",&num);
			accept(ch,num);
			pyes(cpu1, num);
			break;
		default:
			printf("enter correct choice\n");

		}
		}while(ch<=7);
		return 0;
}
void accept(int ch,int num)
{
	int i;
	
	printf("Enter the values\n");
	if(ch==1 || ch==2 || ch==3)
	{
		printf("\nArrival Time and Burst Time\n");
		for(i=1;i<=num;i++)
		{
			printf("\tP%d  :",i);
			scanf("%d%d",&cpu1[i].arrival,&cpu1[i].burst);
			cpu1[i].processid=i;
		}
	}
	if(ch==5 || ch == 6 || ch==7)
	{
		printf("\nArrival Time , Burst Time and Priority\n");
		for(i=1;i<=num;i++)
		{
			printf("\tP%d  :",i);
			scanf("%d%d%d",&cpu1[i].arrival,&cpu1[i].burst,&cpu1[i].priority);
			cpu1[i].processid=i;
		}
	}
	if(ch==4)
	{
		printf("\nArrival Time and  Burst Time\n");
		for(i=1;i<=num;i++)
		{
			printf("\tP%d  :",i);
			scanf("%d%d",&cpu1[i].arrival,&cpu1[i].burst);
			cpu1[i].processid=i;
		}
	}
}


//in all the problems turn around time is completion time - arrival time 
//and waiting time is tat - burst time 
void fcfs(cpu cpu1[], int num){
	int i, j;
	int totaltat = 0;
	int totalwaiting = 0;
	cpu temp;
	int totaltime[20]  ={ 0 };
	int waiting[20]= {0};
	int tat[20]={ 0} ;
	//first the process are sorted according to burst time for processes with same arrival time 
	for(j = 1; j < num ; j++) {
		for(i = 1; i <= num - j; i++){
			if(cpu1[i].burst > cpu1[i + 1].burst) {
				temp = cpu1[i];
				cpu1[i] = cpu1[i + 1];
				cpu1[i + 1] = temp; 
			}
		}
	}
	//then the process are allocated depending on first come basis
	for(j = 1; j < num ; j++) {
		for(i = 1; i <= num - j; i++){
			if(cpu1[i].arrival > cpu1[i + 1].arrival) {
				temp = cpu1[i];
				cpu1[i] = cpu1[i + 1];
				cpu1[i + 1] = temp; 
			}
		}
	}
	printf("Gantt Chart:  \n");
	//then the process are allocated depending on first come basis
	for(i = 1; i <= num; i ++) {
		totaltime[i] = totaltime[i - 1] + cpu1[i].burst;
		tat[i] = totaltime[i] - cpu1[i].arrival;
		waiting[i] = tat[i] - cpu1[i].burst;
		totaltat += tat[i];
		totalwaiting += waiting[i];
		
		printf("|P%d|\t", cpu1[i].processid);
		
		}
		printf("\n");
		for(i = 1; i <= num; i ++)
			printf("  %d\t",totaltime[i]);
	printf("\n");
	printf("\n");
	printf("[processid]\t[turn around time]\t[waiting time]\t\n\n");
	for(i = 1; i <= num ; i++) {
		printf("%d\t|\t%d\t\t|\t%d\t\t|\t\t\n",cpu1[i].processid, tat[i], waiting[i]);
	}
	printf("average waiting time is %d\n", totalwaiting/num);
	printf("average turn around time is %d\n", totaltat/num);
	printf("throughput is %d\n", totaltime[num]/num);
}
void sjf(cpu cpu1[], int num){

	int i , j, min, temp1, temp2;
	int totaltat = 0, tt = 0;
	int totalwaiting = 0;
	cpu temp;
	int totaltime[20]  ={ 0 };
	int waiting[20]= {0};
	int tat[20]={ 0} ;
	int newindex = 1 , index = 1;
	int flag[20] = { 0 };
	//first sorted according to arrival time 
	//because for same priority processes the one with lower arrival time should be econsidered
	for(j = 1; j < num ; j++) {
		for(i = 1; i <= num - j; i++){
			if(cpu1[i].arrival > cpu1[i + 1].arrival) {
				temp = cpu1[i];
				cpu1[i] = cpu1[i + 1];
				cpu1[i + 1] = temp; 
			}
		}
	}
	/*for(i = 1; i <= num; i++) {
		
		printf("%d %d %d %d\n", cpu1[i].processid, cpu1[i].burst, cpu1[i].arrival, cpu1[i].priority);
	}*/
	//as for first arrival time first process will be allocated
	totaltime[1] = cpu1[1].burst;
	tt = totaltime[1];
	printf("Gantt Chart:  \n");
	printf("|P%d|%d    ",cpu1[1].processid, totaltime[1]);
	tat[1] = totaltime[1] - cpu1[1].arrival;
	waiting[1] = tat[1] - cpu1[1].burst;
	totaltat += tat[1];
	totalwaiting +=  waiting[1];
	temp = cpu1[1];
	temp1 = tat[1];
	temp2 = waiting[1];

	for(i = 1; i <= num; i++) {
		cpu1[i] = cpu1[i+1];
	}
	num = num - 1;
	//sorting according to burst time 
	for(j = 1; j < num ; j++) {
		for(i = 1; i <= num - j; i++){
			if(cpu1[i].burst > cpu1[i + 1].burst) {
				temp = cpu1[i];
				cpu1[i] = cpu1[i + 1];
				cpu1[i + 1] = temp; 
			}
		}
	}

	for(j = 1; j <= num ; j ++) {
		
		for(i = 1; i <= num ; i++) {
		
			if(flag[i] == 0 && cpu1[i].arrival <= tt) {
					
				totaltime[i] = tt + cpu1[i].burst;
				tt = totaltime[i];
				tat[i] = totaltime[i] - cpu1[i].arrival;
				waiting[i] = tat[i] - cpu1[i].burst;
				totaltat += tat[i];
				totalwaiting += waiting[i];
				flag[i] = 1;
				printf("|P%d|%d  ", cpu1[i].processid, totaltime[i]);
				break;
				}
			}
		
		}
		
	totaltat += temp1;
	totalwaiting += temp2;
	printf("\n");
		
	printf("tat of %d  :%d\n",temp.processid, temp1);
	printf("wait of %d :%d\n",temp.processid, temp2);
	printf("\n");
	printf("[processid]\t[turn around time]\t[waiting time]\t\n\n");
	for(i = 1; i <= num ; i++) {
		printf("%d\t|\t%d\t\t|\t%d\t\t|\t\t\n",cpu1[i].processid, tat[i], waiting[i]);
	}
	printf("average waiting time is %d\n", totalwaiting/num);
	printf("average turn around time is %d\n", totaltat/num);
	printf("throughput is %d\n", totaltime[num]/num);
}
void srtf(cpu cpu1[], int num){
	int rt[num + 1],endTime,i,smallest;
    	int remain = 0,time,sum_wait=0,sum_turnaround=0;
    	for(i = 0; i <= num; i++)
    	{
        	rt[i] = cpu1[i].burst;
    	}
    	
    	rt[num + 1] = 99;
	printf("Gantt Chart:  \n");
    	for(time = 0; remain != num; time++)
	    	{
		smallest = num + 1;
	//	printf("%d is smallest\n", rt[smallest]);
		for(i = 0; i <= num; i++)
		{
		    if(cpu1[i].arrival <= time && rt[i] < rt[smallest] && rt[i] > 0)
		    {
		        smallest = i;
		
		    }
		}
		
		printf("|P%d|%d  ", cpu1[smallest].processid, time + 1);
		rt[smallest]--;
		if(rt[smallest] == 0)
		{
		    remain++;
		    endTime = time + 1;
		}
	    }
	printf("\n\n[Pid]\t[Turnaround Time] [Waiting Time]\n\n");	
	for(i = 0;i < num;i++){
		 printf("\nP%d\t|\t%d\t|\t%d",i   +1,endTime -cpu1[i].arrival,endTime - cpu1[i].burst-cpu1[i].arrival);
	    sum_wait += endTime - cpu1[i].burst - cpu1[i].arrival;
	    sum_turnaround += endTime - cpu1[i].arrival;
	}
	    printf("\n\nAverage waiting time = %f\n",sum_wait*1.0/num);
	    printf("Average Turnaround time = %f",sum_turnaround*1.0/5);
	    printf("\n");
}
void rr(cpu cpu1[], int num){
	int tq, count = 0;
	int i, j;
	cpu temp;
	int tt = 0;
	int waiting[20] = {0};
	int tat[20] = {0};
	int totaltat = 0, totalwait = 0;	
	printf("enter time quantum\n");
	scanf("%d", &tq);
	//sorting according to arrival time for process with same burst time fcfs should be considered
	for(j = 1; j < num ; j++) {
		for(i = 1; i <= num - j; i++){
			if(cpu1[i].arrival > cpu1[i + 1].arrival) {
				temp = cpu1[i];
				cpu1[i] = cpu1[i + 1];
				cpu1[i + 1] = temp; 
			}
		}
	}
	i = 1;
	//this loop will end when all the processes will be allocated 
	// this is maintained with count variable
	printf("Gantt Chart:  \n");
	while(1){
		if(cpu1[i].burst == 0) {
		//	the process is allocated 
			count++;
			goto end;

		}
		if(cpu1[i].burst <= tq){
		//	burst time is less than time quantum
			tt = tt + cpu1[i].burst;
			tat[i] = tt - cpu1[i].arrival;
			waiting[i] = tat[i] - cpu1[i].burst;
			totaltat += tat[i];
			totalwait += waiting[i];
		//thus the excecution of process is complete so burst = 0
			cpu1[i].burst = 0;
			printf("P%d|%d\t|",cpu1[i].processid,tt);
			goto end;
		}
		if(cpu1[i].burst > tq){
		//	burst time is greater than time quantum
			cpu1[i].burst  = cpu1[i].burst - tq;
			tt = tt + tq;
			
			printf("P%d|%d\t|",cpu1[i].processid,tt);
			goto end;
		}
		end:
		if(count == num) {
			break;
		}
		//if i = 3 ie if one loop is over we need to check all over again for all processes
		i = i + 1;	
		if(i == (num + 1)) {
			i = 1;
		}
	}
	printf("\n");	
	printf("\n");
	printf("[processid]\t[turn around time]\t[waiting time]\t\n\n");
	for(i = 1; i <= num ; i++) {
		printf("%d\t|\t%d\t\t|\t%d\t\t|\t\t\n",cpu1[i].processid, tat[i], waiting[i]);
	}
	printf("average waiting time is %d\n", totalwait/num);
	printf("average turn around time is %d\n", totaltat/num);
	printf("throughput is %d\n", tt/num);
}
//void hrrn(cpu cpu1[], int num){}
void pno(cpu cpu1[], int num){
	int i = 1, j;
	cpu temp;
	int tt = cpu1[i].arrival;
	int count = 0;
	int tat[20] = {0};
	int wait[20] = {0};
	int totalwait = 0;
	int totaltat = 0;
	for(i = 2; i <= num; i++) {
		if(cpu1[i].arrival < tt){
			tt =cpu1[i].arrival;
		}	
	
	}
	//sorting according to arrival time 
	for(j = 1; j < num ; j++) {
		for(i = 1; i <= num - j; i++){
			if(cpu1[i].arrival > cpu1[i + 1].arrival) {
				temp = cpu1[i];
				cpu1[i] = cpu1[i + 1];
				cpu1[i + 1] = temp; 
			}
		}
	}
	//sorting according to priority
	for(j = 1; j < num ; j++) {
		for(i = 1; i <= num - j; i++){
			if(cpu1[i].priority > cpu1[i + 1].priority) {
				temp = cpu1[i];
				cpu1[i] = cpu1[i + 1];
				cpu1[i + 1] = temp; 
			}
		}
	}
	/*printf("sorted according to priority\n");
	for(i = 1; i <= num; i++) {
			printf("%d %d %d %d\n", cpu1[i].processid, cpu1[i].burst, cpu1[i].arrival, cpu1[i].priority);

	}*/	
	printf("Gantt Chart:  \n");
	while(count < num) {

		for(i = 1; i <= num; i++) {
			if(cpu1[i].arrival <= tt && cpu1[i].burst != 0) {
				printf(" ");
			
				tt = tt + cpu1[i].burst;
				tat[i] = tt - cpu1[i].arrival;
				wait[i] = tat[i] - cpu1[i].burst;
				totalwait += wait[i];
				totaltat += tat[i];
			
				cpu1[i].burst = 0;
				count = count + 1;
				printf("|P%d|%d  ", cpu1[i].processid, tt);
			
				break;
			}
		}

	}
		
	printf("\n");
	printf("\n");
	printf("[processid]\t[turn around time]\t[waiting time]\t\n\n");

	for(i = 1; i <= num ; i++) {
		printf("%d\t|\t%d\t\t|\t%d\t\t|\t\t\n",cpu1[i].processid, tat[i], wait[i]);
	}
	printf("average waiting time is %d\n", totalwait/num);
	printf("average turn around time is %d\n", totaltat/num);
	printf("throughput is %d\n", tt/num);
}
void pyes(cpu cpu1[], int num){
int i = 1, j;
	cpu temp;
	int tt = cpu1[i].arrival;
	int count = 0;
	int tat[20] = {0};
	int wait[20] = {0};
	int totalwait = 0;
	int totaltat = 0;
	for(i = 2; i <= num; i++) {
		if(cpu1[i].arrival < tt){
			tt =cpu1[i].arrival;
		}	
	
	}

	for(j = 1; j < num ; j++) {
		for(i = 1; i <= num - j; i++){
			if(cpu1[i].arrival > cpu1[i + 1].arrival) {
				temp = cpu1[i];
				cpu1[i] = cpu1[i + 1];
				cpu1[i + 1] = temp; 
			}
		}
	}
	for(j = 1; j < num ; j++) {
		for(i = 1; i <= num - j; i++){
			if(cpu1[i].priority > cpu1[i + 1].priority) {
				temp = cpu1[i];
				cpu1[i] = cpu1[i + 1];
				cpu1[i + 1] = temp; 
			}
		}
	}
	/*printf("sorted according to priority\n");
	for(i = 1; i <= num; i++) {
			printf("%d %d %d %d\n", cpu1[i].processid, cpu1[i].burst, cpu1[i].arrival, cpu1[i].priority);

	}*/	
	printf("Gantt Chart:  \n");
	while(count < num) {

		for(i = 1; i <= num; i++) {
			if(cpu1[i].arrival <= tt && cpu1[i].burst != 0) {
			
			
				tt = tt + 1;
				cpu1[i].burst = cpu1[i].burst - 1;
				
				if(cpu1[i].burst == 0) {

					tat[i] = tt - cpu1[i].arrival;
					wait[i] = tat[i] - cpu1[i].burst;
					totalwait += wait[i];
					totaltat += tat[i];
					count = count + 1;
				}
	
				printf("|P%d|%d   ", cpu1[i].processid, tt);
			
				break;
			}
		}

	}
		
	printf("\n");
	printf("\n");
	printf("[processid]\t[turn around time]\t[waiting time]\t\n\n");

	for(i = 1; i <= num ; i++) {
		printf("%d\t|\t%d\t\t|\t%d\t\t|\t\t\n",cpu1[i].processid, tat[i], wait[i]);
	}
	printf("average waiting time is %d\n", totalwait/num);
	printf("average turn around time is %d\n", totaltat/num);
	printf("throughput is %d\n", tt/num);

}
void swap ( int k, int l){
	struct data a;
	strcpy(a.pn,d[k].pn);
	a.a = d[k].a;
	a.b = d[k].b;
	a.p = d[k].p;
	a.t = d[k].t;
	strcpy(d[k].pn,d[l].pn);
	d[k].a = d[l].a;
	d[k].b = d[l].b;
	d[k].p = d[l].p;
	d[k].t = d[l].t;
	strcpy(d[l].pn,a.pn);
	d[l].a = a.a;
	d[l].b = a.b;
	d[l].p = a.p;
	d[l].t = a.t;
}
void hrrn(){

	
	char *pn[20];
	int data[20][4];
	int i,ch = 0,num;
	printf("\nenter number of processes: ");
			scanf("%d",&num);
	

	for(i = 0; i < num; i++){
		pn[i] = (char*)malloc(sizeof(char) * 3);
		printf("Enter process no.");
		scanf("%s",d[i].pn);
		printf("Enter arrival time and burst time");
		scanf("%d",&d[i].a);
		scanf("%d",&d[i].b);
		
	}
	int j, restm, nextprocess;
	float avgwait, avgta, throughput;
	float wait, fwait;

	for(i = 0; i < num; i++){
		for(j = 0; j < i; j++){
			if(d[j].a > d[i].a){
			       swap(i,j);
			}
		}
	}

	restm = i = 0;
	printf("P. NO\tRes.time\n");
	printf("%s\t%d\n",d[i].pn,restm);
	restm  = restm + d[i].b;
	d[i].b = 0;

	for(i = 1; i < num; i++){
		wait = fwait = 0;
		j = 0;
		while(d[j].a < restm && j < num){
			if(d[j].b != 0){
				wait = (restm - d[j].a + d[j].b)/d[j].b;
				if(wait > fwait){
					fwait = wait;
					nextprocess = j;
				}
			}
			j++;
		}
		printf("%s\t%d\n",d[nextprocess].pn,restm);
		avgwait = avgwait + restm;
		restm = restm + d[nextprocess].b;
		avgta = avgta + restm;
		d[nextprocess].b = 0;

	}

 	throughput = restm / num;
	avgwait = avgwait / num;
	avgta = avgta / num;

	printf("Average waiting time = %f\n",avgwait);
	printf("Average turn around time = %f\n",avgta);
	printf("Throughput = %f\n",throughput);


 }
