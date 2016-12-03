#include<stdio.h>

int main(int argc,char *argv[]) {
	FILE *fp = fopen(argv[1],"r");
	FILE *fp1 = fopen(argv[2],"r");
	FILE *fp2 = fopen(argv[3],"w");
	int a[100];
	int i = 0,j,k = 0,value = 0,c,counter = 0;	
	if(!fp) {
		printf("File not found");
	}
	if(!fp1) {
		printf("File not found");
	}
	if(!fp2) {
		printf("File not found");
	}
	do {
		while((c = fgetc(fp)) != ' ' && c != EOF) {
			value = value * 10 + (c - 48);
			
		}
		a[i++] = value;
		value = 0;
		counter++;
	}while(c != EOF);
	i--;
	do {
		while((c = fgetc(fp1)) != ' '&& c != EOF) {
			value = value * 10 + (c - 48);
			
		}
		a[i++] = value;
		value = 0;
		counter++;
	}while(c != EOF);
	counter -= 2;
	/*for(k = 0;k < counter; k++){
		printf("%d\t",a[k]);
	}*/ 
	printf("\n");
	for(i = 0;i < counter;i++) {
		for(j = i;j < counter;j++) {
			if(a[i] > a[j]) {
				int temp = a[i];
				a[i] = a[j];
				a[j] = temp;
			}
		}
	}

	for(k = 0;k < counter; k++){
		fprintf(fp2,"%d\t",a[k]);
	} 
	printf("\n");
	return 0;
}	 
