#include<stdio.h>
#include<string.h>
struct data {
	char name[10];
	int pno;
}record[100];
int main() {
	int i = 0, j, k,tmppno,counter,new,flag = 0;
	char tmpname[100];
	FILE *fp = fopen("sp2.txt","r");
	if(!fp)
		printf("FIle not found");
	while(!feof(fp)) {
		fscanf(fp,"%s %d",record[i].name, &record[i].pno);
		i++;
	}
	counter = i - 1;
	while( 1 ) {
		printf("1. to check name from phone number\n2.To check phone number from name\n3.Change mobile number\n4.to exit\n");
		scanf("%d",&k);
		switch(k) {
			case 1: printf("Enter a phone number\t");
				scanf("%d",&tmppno);
				for(i = 0;i < counter;i++) {
					if(tmppno == record[i].pno) 
						printf("%s\n",record[i].name);
				}
				break;
			case 2: printf("Enter a name\t");
				scanf("%s",tmpname);
				for(i = 0;i < counter;i++) {
					if(strcmp(tmpname,record[i].name) == 0) 
						printf("\n%d\n",record[i].pno);
				}
				break;
			case 3: printf("Enter the name whos mobile number you want to change");
				scanf("%s",tmpname);
				for(i = 0;i < counter;i++) {
					if(strcmp(tmpname,record[i].name) == 0) {
						printf("\nRecord found\n");
						printf("\nEnter new mobile number\n");
						scanf("%d",&new);
						record[i].pno = new;
						flag = 1;
					}
				}
				if(flag == 1) {
					fp = fopen("sp2.txt","w");
					rewind(fp);
					for(i = 0; i < counter; i++) {
						fprintf(fp,"%s %d \n",record[i].name,record[i].pno);
					}
					//fclose(fp);
				}	
				break;
		
			default: return;
		}
	}
	fclose(fp);
	return 0;
}
