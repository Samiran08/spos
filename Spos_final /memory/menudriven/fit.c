#include <stdio.h>
#include <stdlib.h>
void input();
int sumexternal(int ,int [10]);
void firstfit(int ,int [10],int [10],int);
void nextfit(int ,int [10],int [10],int);
void bestfit(int ,int [10],int [10],int);
void worstfit(int,int [10],int [10],int);
void asort(int [10], int);
void dsort(int [10], int);
int main() {
	int npr,nh=0,i,j,k,pr[10],block[10],ch,temp[10],choice,l;
	while(1) {
		printf("\n\n\t\t-------Choose Your Option:---------\n\n");
		printf("\n\t\t1.INPUT\n");
		printf("\n\t\t2.FIRST FIT\n");
		printf("\n\t\t3.BEST FIT\n");
		printf("\n\t\t4.WORST FIT\n"); 
		printf("\n\t\t5.NEXT FIT\n"); 
		printf("\n\t\t6.EXIT\n");
		printf("\n\t\tEnter Your Choice:\n\t\t");
		scanf("%d",&choice);
		for(i=0;i<nh;i++) {            
                      	temp[i]=block[i];
                }
		switch(choice) {
			case 1:
				printf("\n Enter the number of processes:");
                		scanf("%d",&npr);
                		printf("\nNumber of blocks:");
                		scanf("%d",&nh);
                		for(i=0;i<npr;i++) {
                     			printf("\nProcess %d:",i+1);  
                     			scanf("%d",&pr[i]);  
                  		}
                		for(i=0;i<nh;i++) {
                     			printf("\nBlock %d:",i+1);  
                     			scanf("%d",&block[i]);  
                      			temp[i]=block[i];
                  		}
				break;
			case 2:
				firstfit(npr,temp,pr,nh);
				break;
				
			case 3:		
				bestfit(npr,temp,pr,nh);	
				break;
			case 4:
				worstfit(npr,temp,pr,nh);
				break;
			case 5:
				nextfit(npr,temp,pr,nh);
				break;
			case 6:
				printf("\n\nThank you.......... \n\n");
				exit(0);
				break;
			default:
				printf("\nYou enterd invalid choice,Plz enter valid choice\n");
				break;
		}		
	}
	return 0;
}
void firstfit(int npr,int block[10],int pr[10],int nh){
   	int i,j,k,flag=0,num,l,ff[10],frag[10],itot = 0;
	int temp[10],ext,sum,inter[10],s=0,fff[10],cc=0,sub=0;
	printf("\nPROCESS\t\tPROCESS SIZE\tBLOCK SIZE\tINTERNAL FRAG.\n");
	for(i =0; i<nh;i++)
			fff[i]=block[i];
   	for(i=0;i<npr;i++){
		flag=0;
      		for(j=0;j<nh;j++){
	     		temp[j] = block[j];
	                if(pr[i]<block[j]){
				inter[i] = pr[i];
				ff[j] = block[j];
			        block[j]=block[j]-pr[i];
				frag[j] = block[j];
                		flag=1;	
				break;             
              		}
            		else if(pr[i]==block[j]) {
				cc++;
				inter[i] =pr[i];
				fff[j] = block[j];
		 		ff[j] = block[j];
                 		flag=1;
	          		frag[j] = block[j]-pr[i];
		                for(k=j;k<nh-1;k++) {
                   			block[k]=block[k+1];
                 		}  
		 		nh--;
                 		break;
            		} 
       		}
       		if(flag==0) {
	   		printf("\n For this process, block is not Available…..\n");
			ff[j] = 0;
			frag[j] = 0;
			ext = 0;
			goto label;
    	   		//break;
       		}
	 	ext = sumexternal(nh,block);
		label: printf("\n%d\t\t%d\t\t%d\t\t%d\n",i+1,pr[i],ff[j],frag[j]);
		itot = itot + frag[j];
  	}
	for(i = 0; i< npr ;i++){
		s += inter[i];
		
	}
	for(j = 0;j < nh ; j++) {
		if(fff[j] != block[j])
			sub +=block[j];
	}
 	//printf("\nTotal Internal Fragmentation:%d",sub);
	sum = sumexternal(nh,block);
	printf("\nTotal External Fragmentation:%d",sum);	
}    
void bestfit(int npr,int block[10],int pr[10],int nh){
	int i,j,k,flag=0,num,l,ff[10],frag[10];
	int itot = 0,temp[10],ext,sum,inter[10],s=0,fff[10],cc=0,sub=0;
	printf("\nPROCESS\t\tPROCESS SIZE\tBLOCK SIZE\tINTERNAL FRAG.\n");
	asort(block, nh);
	for(i = 0; i < nh ; i++)
		fff[i]=block[i];
   	for(i=0;i<npr;i++){
      		flag=0;
      		for(j=0;j<nh;j++){
	     		temp[j] = block[j];
			if(pr[i]<block[j]){
				inter[i] = pr[i];
				ff[j] = block[j];
			        block[j]=block[j]-pr[i];
				frag[j] = block[j];
		                flag=1;	
				break;             
              		}
            		else if(pr[i]==block[j]) {
				cc++;
				inter[i] =pr[i];
				fff[j] = block[j];
				ff[j] = block[j];
                 		flag=1;
		 		frag[j] = block[j]-pr[i];
               			for(k=j;k<nh-1;k++) {
                   			block[k]=block[k+1];
                 		}  
		 		nh--;
                 		break;
            		} 
       		}
       		if(flag==0) {
	   		printf("\n For this process, block is not Available…..\n");
			ff[j] = 0;
			frag[j] = 0;
			ext = 0;
    	   		//break;
       		}
	 	ext = sumexternal(nh,block);
		printf("\n%d\t\t%d\t\t%d\t\t%d\n",i+1,pr[i],ff[j],frag[j]);
		itot = itot + frag[j];
   	}
	for(i = 0; i< npr ;i++){
		s +=inter[i];	
	}
	for(j = 0;j < nh ; j++) {
		if(fff[j] != block[j])
			sub +=block[j];
	} 	
	sum = sumexternal(nh,block);
	printf("\nTotal External Fragmentation:%d",sum);	
}    
void worstfit(int npr,int block[10],int pr[10],int nh) {
	int i,j,k,max,flag,wf[10],frag[10],itot=0,ext,sum,fff[10],sub = 0;
	printf("\nPROCESS\t\tPROCESS SIZE\tBLOCK SIZE\tINTERNAL FRAG\n");
	dsort(block, nh);
	for(j=0 ; j<nh ; j++)
			fff[j] = block[j];
	for(i=0;i<npr;i++){
     		flag=0;
       		for(j=0;j<nh;j++) {
            		if(pr[i]<=block[j]) {
				wf[j] = block[j];
				frag[j] = block[j]-pr[i];
                          	flag=1;  
				max=j;
                 		for(k=j;k<nh;k++) {
                   			if((block[max]<block[k])&&(pr[i]<=block[k]))
						max=k;
                 		}
              			if(pr[i]<block[max]) {
					wf[j] = block[max];
					frag[j] = block[max]-pr[i];
              				block[max]=block[max]-pr[i];
               				break;             
               			}
              			else if(pr[i]==block[max]) {
               				wf[j] = block[max];
					frag[j] = block[max]-pr[i];
                			for(k=max;k<nh-1;k++)
                   				block[k]=block[k+1];
                				nh--;
                 				break;
              				}         
            			}
          	} 
    		if(flag==0) {
			printf("\n For this process, block is not Available…..\n");
			wf[j] = 0;
			frag[j] = 0;
			ext = 0;
    			//break;
		}
		ext =  sumexternal(nh,block); 
		printf("\n%d\t\t%d\t\t%d\t\t%d\n",i+1,pr[i],wf[j],frag[j]);
		itot = itot + frag[j];
      	}
	for(j=0 ; j<nh ; j++){
		if(fff[j] != block[j])
			sub += block[j];
	}
	sum=sumexternal(nh,block);
	printf("\nTotal External Fragmentation:%d",sum);	
}

//Next Fit

void nextfit(int npr,int block[10],int pr[10],int nh){
   	int i,j,k,flag=0,num,l,ff[10],frag[10],itot = 0, count =0;
	int temp[10],ext,sum,inter[10],s=0,fff[10],cc=0,sub=0;
	printf("\nPROCESS\t\tPROCESS SIZE\tBLOCK SIZE\tINTERNAL FRAG.\n");
	for(i =0; i<nh;i++)
			fff[i]=block[i];
   	for(i=0;i<npr;i++){
		flag=0;
      		for(j=count;j<nh;j++){
	     		temp[j] = block[j];
	                if(pr[i]<block[j]){
				count = j;
				inter[i] = pr[i];
				ff[j] = block[j];
			        block[j]=block[j]-pr[i];
				frag[j] = block[j];
                		flag=1;	
				if(count == nh - 1){
					count = 0;
				}
				break;             
              		}
            		else if(pr[i]==block[j]) {
				cc++;
				inter[i] =pr[i];
				fff[j] = block[j];
		 		ff[j] = block[j];
                 		flag=1;
	          		frag[j] = block[j]-pr[i];
		                for(k=j;k<nh-1;k++) {
                   			block[k]=block[k+1];
                 		}  
		 		nh--;
				if(count == nh - 1){
					count = 0;
				}
                 		break;
            		} 
       		}
       		if(flag==0) {
	   		printf("\n For this process , block is not Available…..\n");
			ff[j] = 0;
			frag[j] = 0;
			ext = 0;
			goto label;
    	   		//break;
       		}
	 	ext = sumexternal(nh,block);
		label: printf("\n%d\t\t%d\t\t%d\t\t%d\n",i+1,pr[i],ff[j],frag[j]);
		itot = itot + frag[j];
  	}
	for(i = 0; i< npr ;i++){
		s += inter[i];
		
	}
	for(j = 0;j < nh ; j++) {
		if(fff[j] != block[j])
			sub +=block[j];
	} 	

	sum = sumexternal(nh,block);
	printf("\nTotal External Fragmentation:%d",sum);	
}    

int sumexternal(int nh,int block[10]){
	int sum = 0,i;
	for(i=0;i<nh;i++) {
  		sum = sum + block[i];
	}
	return sum;
}
void asort(int block[10], int nh){
	int swap, i, j;
	for(i = 0; i < nh - 1; i++){
		for(j = 0; j < nh - 1; j++){
			if(block[j] > block[j + 1]){
				swap= block[j];
				block[j] = block[j + 1];
				block[j + 1] = swap;
			}
		}
	}
}
void dsort(int block[10], int nh){
	int swap, i, j;
	for(i = 0; i < nh - 1; i++){
		for(j = 0; j < nh - 1; j++){
			if(block[j] < block[j + 1]){
				swap= block[j];
				block[j] = block[j + 1];
				block[j + 1] = swap;
			}
		}
	}
}  
	
