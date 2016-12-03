#include<stdio.h>
void fifo(int nf, int np, int*page);
int optimal(int *, int *, int, int);
int search_opti(int, int, int *, int);
int display(int);
void lru(int nf, int np, int*page);
void lfu(int nf, int np, int*page);
void mfu(int nf, int np, int*page);
void secondchance(int nf, int np, int*page);
void enhanced(int nf, int np, int*page);
int np, nf, page[100], pages, i, choice;
	int  frame[20],j, fault = 0, tot_fault = 0;
	int full=0, ref[10], f[10]={0}, repptr= 0, count=0;
int main(){

	

	printf("Enter number of frames\n");
	scanf("%d", &nf);
	printf("Enter number of pages\n");	
	scanf("%d", &np);
	printf("Enter reference string\n");

	for(i = 0; i < np; i++) {
		printf("%d:",i + 1);
		scanf("%d", &pages);
		page[i] = pages;
		
	}
	printf("\n");
	do{
	printf(" *******MENU**************\n");
	printf("1 FIFO\n");
	printf("2 OPTIMAL\n");
	printf("3 LRU\n");
	printf("4 LFU\n");
	printf("5 MFU\n");
	printf("6 SECOND CHANCE\n");
	//printf("7 ---- ENHANCED SECOND CHANCE\n");
	printf("8 EXIT\n");
	printf("Reference string is as follows:\n");
	for(i = 0; i < np; i++) {
		printf("%d ", page[i]);
	}
	printf("\n\n");
	scanf("%d", &choice);

	switch(choice) {
		case 1:
			fifo(nf, np, page);
			break;
		case 2:
			
			tot_fault = 0;
				tot_fault = optimal(page,frame,np,nf);
				printf("\n\n\t\tTotal page fault is =  %d\n",tot_fault);
			break;
		case 3:
			lru(nf, np, page);
			break;
		case 4:
			lfu(nf, np, page);
			break;
		case 5:
			mfu(nf, np, page);
			break;
		case 6:
			secondchance(nf, np, page);
			break;
		case 7:
			enhanced(nf, np, page);
			break;
		case 8:
			return;
		default :
			printf("Please enter correct choice\n");
	}
}while(choice<=8);


	return 0;
}
void fifo(int nf, int np, int*page){
	int frame[nf];
	int i, j, k = 0;
	int flag = 0; //checking if page is already present
	int pf = 0;//page fault
	for(i = 0; i < nf; i++){
		frame[i] = -1;
	}
	for(j = 0; j < np; j++){
		flag = 0;
		for(i = 0; i < nf; i++) {
			if(frame[i] == page[j]) {
				flag = 1;
				break;
			}
		}
		if(flag == 0) {
			frame[k] = page[j];
			k = (k + 1) % nf;
			pf = pf + 1;
		}
		for(i = 0; i < nf; i++){
			printf("|\t%d\t|",frame[i]);
		}
		printf("\n\n");
		}
		printf("The page fault is %d\n", pf);
	
}
void lru(int nf, int np, int*page){
	int frame[nf];
	int i, j, k;
	int flag = 0;
	int r = 0;//if any of frame is empty
	int pf = 0;
	int dist[nf], max;
	int index = 0;
	int num;
	for(i = 0; i < nf; i++) {
		frame[i] = -1;
	}
	for(j = 0; j < np; j++){
		num = page[j];
		flag = 0;
		for(i = 0; i < nf; i++) {
			if(frame[i] == num){
				flag = 1;
			}
		}
		if(flag == 0 && r < nf) {
			frame[r] = num;
			r = r + 1;
			pf = pf + 1;
			if(r == nf) {
				goto end;
			}
		}
		if(flag == 0 && r == nf) {
			for(i = 0; i < nf; i++) {
				for(k = j - 1; k > -1; k--) {
					if(frame[i] == page[k]) {
						dist[i] = j - k;
						break;
					}
				}
	
			}
			max = dist[0];
			index = 0;
		
			for(i = 1; i < nf; i++) {
					
				if(dist[i] > max) {
					max = dist[i];
					index = i;
				}
			

			}
			
			frame[index] = num;
			pf = pf + 1;
		}
		end:
		for(i = 0; i < nf; i++) {
		
			printf("|\t%d\t|", frame[i]);
		}
		printf("\n\n");
		}
		printf("page fault is %d\n", pf);
	
	

}

void lfu(int nf, int np, int*page){
	typedef struct block{
		int value;
		int freq;
		int hist;
	}block1;
	block1 block[nf];
	int i, j,k,l,  flag = 0, num, pf = 0;
	for(i = 0; i < nf; i++){
		block[i].value = -1;
		block[i].freq = -1;
		block[i].hist = -1;
	}
	for(j = 0; j < np; j++){
			
		num = page[j];
		flag = 0;
		
		for(i = 0; i < nf; i++){
			
			if(block[i].value == -1) { 
				block[i].value = num;
				block[i].freq = 1;
				block[i].hist = 1;
				flag = 1;
				pf = pf + 1;
				break;
			}
			block[i].hist += 1;
		}
		if(flag == 0) {
			for(i = 0; i < nf; i++){
				if(block[i].value == num) {
					block[i].freq += 1;
					flag = 1;		
					break;
				}	

			}
		}
		if(flag == 0) {
			l = 0;
			k = 1;
			while(k < nf ){
		
			if(block[l].freq < block[k].freq) {
				
				k = k + 1;
				
				
			}

			else if (block[l].freq == block[k].freq) {
			
				if(block[l].hist > block[k].hist){
					

					k = k + 1;
				}
				else{ 
					
					l = k;
					k = k + 1;
				}
			}
			else{
				l = k;
				k = k + 1;
			}
			}
			
			
		block[l].value = num;
		block[l].freq = 1;
		block[l].hist = 1;
		pf = pf + 1;
		}
		for(i = 0; i < nf; i ++) {
			printf("|\t%d\t|", block[i].value);
			
		}

		printf("\n\n");
	}
	printf("page fault is %d\n", pf);
}

void mfu(int nf, int np, int*page){
	typedef struct block{
		int value;
		int freq;
		int hist;
	}block1;
	block1 block[nf];
	int i, j,k,l,  flag = 0, num, pf = 0;
	for(i = 0; i < nf; i++){
		block[i].value = -1;
		block[i].freq = -1;
		block[i].hist = -1;
	}
	for(j = 0; j < np; j++){
			
		num = page[j];
		flag = 0;
		
		for(i = 0; i < nf; i++){
			
			if(block[i].value == -1) { 
				block[i].value = num;
				block[i].freq = 1;
				block[i].hist = 1;
				flag = 1;
				pf = pf + 1;
				break;
			}
			block[i].hist += 1;
		}
		if(flag == 0) {
			for(i = 0; i < nf; i++){
				if(block[i].value == num) {
					block[i].freq += 1;
					flag = 1;		
					break;
				}	

			}
		}
		if(flag == 0) {
			l = 0;
			k = 1;
			while(k < nf ){
		
			if(block[l].freq > block[k].freq) {
				
				k = k + 1;
				
				
			}

			else if (block[l].freq == block[k].freq) {
				
				if(block[l].hist > block[k].hist){
					

					k = k + 1;
				}
				else{ 
					
					l = k;
					k = k + 1;
				}
			}
			else{
				l = k;
				k = k + 1;
			}
			}
			
			
		block[l].value = num;
		block[l].freq = 1;
		block[l].hist = 1;
		pf = pf + 1;
		}
		for(i = 0; i < nf; i ++) {
			printf("|\t%d\t|", block[i].value);
			
		}

		printf("\n\n");
	}
		printf("page fault is %d\n",pf);
}

int search_opti(int no, int k, int *page, int np){
	int flag = 0, q = 0;
	//printf("\nno = %d, k = %d", no, k);
	for(q = k; q < np; q++){
			if(page[q] == no){
				flag = q;
				//printf("\n\tflag = %d", flag);
				break;
			}
	}
	if(flag == 0)
		return 0;
	else
		return flag;
}
int optimal(int *page, int *frame, int np, int nf){
	for(j = 0; j < nf; j++)
		frame[j] = -1;
	int l = 0, m , n, o, p = 0, z = 0,y =0, c, fault = 0, r;
	int index[nf], pos = 0, largest = 0, k, flag = 0, flag1 = 0, flag2 = 0;
	i = 0;
	
	while(i < np){
		printf("\n\t");
		while(p <= nf){
			if(frame[p] == -1){
				fault++;
				frame[p] = page[i];
				
				flag = 1;
				p++;
				break;
			}
			if(p == nf){
				flag = 0;
				break;
			}
		}
		if(flag == 0){
			flag = 1;
			for(j = 0; j < nf; j++){
				flag1 = 0;
				if(frame[j] == page[i]){
					//printf("\nEnetered if...");
					flag1 = 1;
					break;
				}
			}
			if(flag1 == 0){
				flag1 = 1;
				
				y = i;
				z = y + 1;
				for(r = 0 ; r < nf; r++){
				index[r] = search_opti(frame[r],z,page,np);
				}
				
				flag2 = 0;
				for(j = 0; j < nf; j++){
						if(index[j] == 0){
							
							frame[j] = page[i];
							
							fault++;
							flag2 = 1;
							break;
						}
				}
				if(flag2 == 0){
						
						n = 0;
						largest = index[0];
						for(o = 1; o < nf; o++){
							if(largest <= index[o]){
								largest = index[o];
								n = o;
							}
						}
						
						frame[n] = page[i];
						fault++;
						
				}
			}
		}
		i++;
		for(c = 0; c < nf; c++)
			printf("|\t%d\t|", frame[c]);
		//printf("\t%d",fault);
	}
	
	return fault;
}









void secondchance(int nf, int np, int*page){
	system("cc secondchance.c");
	system("./a.out");
	
}

void enhanced(int nf, int np, int*page){}
