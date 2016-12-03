#include<stdio.h>
#include<stdlib.h>
#define MAX 25

void display(int ,int [MAX]);
void firstfit(int ,int [MAX],int [MAX],int);
void nextfit(int ,int [MAX],int [MAX],int);
void bestfit(int ,int [MAX],int [MAX],int);
void worstfit(int,int [MAX],int [MAX],int);
void fragmentation(int ,int [MAX]);
int main() {
	int npr,nb=0,i,j,k,pr[MAX],hol[MAX],choice,temp[MAX];
	printf("ENTER THE NUMBER OF PROCESSES AND BLOCKS AS REQUIRED TO INITIATE THE PROGRAM :) \n \n");
	printf("ENTER THE TOTAL NUMBER OF PROCESSES: \n");
	scanf("%d",&npr);
	printf("ENTER THE TOTAL NUMBER OF BLOCKS: \n");
	scanf("%d",&nb);
	for(i=0;i<npr;i++) {
		printf("Process %d: \n",i+1);   
		scanf("%d",&pr[i]);   
	}
	for(i=0;i<nb;i++){
		printf("BLOCK %d: \n",i+1);   
		scanf("%d",&hol[i]);   
		temp[i]=hol[i];
	}
	do {  
		printf("\n\n----------MENU------------\n");
		printf(" 1.FIRST-FIT\n 2.BEST FIT\n 3.NEXT FIT\n 4.WORST FIT\n 5.EXIT\n ENTER THE CHOICE: \n");
		scanf("%d",&choice);
		for(i=0;i<nb;i++){
			temp[i]=hol[i];
		}		
		switch(choice) {
			case 1:
				display(nb,hol);
				firstfit(npr,temp,pr,nb);
				break;
			case 2:
				display(nb,hol); 
				bestfit(npr,temp,pr,nb); 
				break;
			case 3:
				display(nb,hol);
				nextfit(npr,temp,pr,nb);
				break;
			case 4:
				display(nb,hol);
				worstfit(npr,temp,pr,nb);
				break;
			case 5:
				exit (0);
			default:
				printf("\n YOU ENTERED WORNG CHOICE\n");
			}
		}
		while(choice!=5);
		return 0;     
	}

//First Fit
void firstfit(int npr,int hol[MAX],int pr[MAX],int nb) {
	int i,j,k,flag=0,exter[nb];
	for(i = 0; i < npr; i++){
		for(j = 0; j < nb; j++){
			if(hol[j] >= pr[i]){
				hol[j] -= pr[i]; //remaining memory
				printf("\n Allocating process %d to memory %d\nSize remaining in it after allocation %d\n\n", i + 1, j + 1, hol[j]);
				exter[j] = 1;
				break;
			}
		}
		if(j == nb){
			printf("\n Not enough memory for process %d\n",i + 1);
			//break;
		}
		display(nb,hol);
	}	
	fragmentation(nb,hol);
}
//Best fit
void bestfit(int npr,int hol[MAX],int pr[MAX],int nb){
	int i,j,k,min,flag;
	for(i=0;i<nb;i++){
		for(j=i+1;j<nb;j++){
			if(hol[i]>hol[j]){
				int temp=hol[i];
				hol[i]=hol[j];
				hol[j]=temp;
			}
		}
	}
	for(i=0;i<npr;i++) {
		for(j=0;j<nb;j++) {
			if(pr[i]<=hol[j]) {
				flag=1;  
				min=j; 
				for(k=j;k<nb;k++) {
					if((hol[min]>hol[k])&&(pr[i]<=hol[k]))
						min=k;
				} 
				if(pr[i]<hol[min]) {
					printf("\n Allocating process %d to memory %d\nSize remaining in it after allocation %d\n\n", i + 1, j + 1, hol[j]);
					hol[min]=hol[min]-pr[i];
					break;              
				}
				else if(pr[i]==hol[min]) {
					printf("\n Allocating process %d to memory %d\nSize remaining in it after allocation %d\n\n", i + 1, j + 1, hol[j]);      
				for(k=min;k<nb-1;k++)
					hol[k]=hol[k+1];
					nb--;
					break;
				}       
			}      
		}        
		if(j == nb){
			printf("\n Not enough memory for process %d\n",i + 1);
			//break;
		}   
		display(nb,hol);   
	}
	fragmentation(nb,hol);
}

//Next Fit
void nextfit(int npr,int hol[MAX],int pr[MAX],int nb){
	int i,j=0,k,flag=0,exter[nb],ctr = 0;
		for(i = 0; i < npr; i++){
			for(j=ctr;j<=nb;j++){
 			 	if(pr[i]<=hol[j]) {
				//printf("\n Allocating process %d to memory %d\nSize remaining in it after allocation %d\n\n", i + 1, j + 1, hol[j]);
   					hol[j]=hol[j]-pr[i];	
					printf("\n Allocating process %d to memory %d\nSize remaining in it after allocation %d\n\n", i + 1, j + 1, hol[j]);								
					ctr = j;
   					break;
  				}
				if(ctr == nb)
					ctr = 0;
			}
			if(j == nb || j >= nb){
				printf("\n Not enough memory for process %d\n", i + 1);
				//break;
			}	
			display(nb,hol);  	
		}
		fragmentation(nb,hol);
	}
	   
//worst fit
void worstfit(int npr,int hol[10],int pr[10],int nb) {
	int i,j,k,max,flag;
		for(i=0;i<nb;i++) {
			for(j=i+1;j<nb;j++) {
				if(hol[i]<hol[j]) {
					int temp=hol[i];
					hol[i]=hol[j];
					hol[j]=temp;
				}
			}
		}
		for(i=0;i<npr;i++) {
			for(j=0;j<nb;j++) {
				if(pr[i]<=hol[j]) {
					printf("\n Allocating process %d to memory %d\nSize remaining in it after allocation %d\n\n", i + 1, j + 2, hol[j]);
	                		flag=1;  
					max=j; 
	                		for(k=j;k<nb;k++) {
	              				if((hol[max]<hol[k])&&(pr[i]<=hol[k]))
							max=k;
	  	             		} 
	               			if(pr[i]<hol[max]) {
	              					hol[max]=hol[max]-pr[i];
	               					break;              
	               			}
	              			else if(pr[i]==hol[max]) {
	                			for(k=max;k<nb-1;k++)
	                   				hol[k]=hol[k+1];
	                				nb--;
	                 				break;
	              			}        
				}
			}  
			if(j == nb){
				printf(" \n Not enough memory for process %d\n",i + 1);
				//break;
			} 
    			display(nb,hol);   
      		}
		fragmentation(nb,hol);	
	}	
void display(int nb,int hol[MAX]) {
	printf("\n REMAINING MEMORY BLOCKS ARE: \n");	
	int i=0,sum = 0;
	for(i=0;i<nb;i++){
		printf("%d\t",hol[i]);
		sum = sum + hol[i];
	}
	printf("\n");
	
}
void fragmentation(int nb,int hol[MAX]) {
		
	int i=0,sum = 0;
	for(i=0;i<nb;i++){
		printf("%d\t",hol[i]);
		sum = sum + hol[i];
	}
	printf(" \n \t THE TOTAL FRAGMENTATION = %d : \n",sum);
}
