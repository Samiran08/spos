#include<stdio.h>

void ptr_increment( int *p, int m){
	(*p)++;
	if(*p == m)
		*p = 0;
}

void disp(int arr[], int n){
	int i;
	for(i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");
}

int is_free(int arr[], int n){
	int i;
	for(i = 0; i < n; i++){
		if(arr[i]  == -1)
			return 1;
	}
	return 0;
}

int exist(int arr[], int n, int a){
	int i;
	for(i =0; i<n; i++){
		if(arr[i] == a)
			return i;
	}
	return -1;
}

int main(){
	int pages[20];
	int frame[10];
	int ref_bit[10];
	int i,j, *ptr, cur_frame = 0, n, m, hit = 0, pf=0;

	ptr = &cur_frame;
	//printf("afdf\n");

	printf("enter the number of pages \n");
	scanf(" %d", &n);
	printf("enter the pages\n");
	for(i = 0; i < n; i++){
		scanf(" %d", &pages[i]);
	}

	printf("enter the size of the frame\n");
	scanf(" %d", &m);
	
	for(i = 0; i< m; i++){
		frame[i] = -1;
		ref_bit[i] = -1;
	}


	for(i = 0; i < n; i++){
		printf("%d\t", pages[i]);

		if(is_free(frame, m)){
			//printf("in free\n");
			for(j = 0; j < m; j++){
				if(frame[j] == -1){
					frame[j] = pages[i];
					ref_bit[j] = 0;
					ptr = &j;
					break;
				}
			}
			//disp(frame, 3);
			//disp(ref_bit, 3);
		}

		else{
			if(exist(frame,m, pages[i]) != -1){
				ref_bit[exist(frame, m, pages[i])] = 1;
				hit++;
			}
			else{
				ptr_increment(ptr, m);
				while(1){
					if(ref_bit[*ptr] == 1){
						ref_bit[*ptr] = 0;
						ptr_increment(ptr, m);
					}
					if(ref_bit[*ptr] == 0){
						frame[*ptr] = pages[i];
						break;
					}
				}
			}
		}
		disp(frame, m);
		//printf("\t");
		//disp(ref_bit, m);
		//printf("%d\n", *ptr);
		//printf("\n\n\n");
	}
	pf = n - hit;
	printf("page faults: %d\t\t page hits: %d\n", pf, hit);
	return 0;
}