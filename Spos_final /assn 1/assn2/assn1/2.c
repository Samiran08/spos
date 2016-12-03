#include <stdio.h>
#include <string.h>
int main(){
	int length[16], length1[16], i = 0, swap, j, z, poi[20];
	char number[20], name[50];
	FILE *fp1;
	fp1 = fopen("tele.txt", "r");
	
	if(fp1 == NULL)
		printf("Unable to open");
	
	
	while((fscanf(fp1, " %s\t%s", name, number)) != EOF){
		printf("%s", name);

		j = 0;
		while(j < (20 - (strlen(name)))){
			printf(" ");
			j++;
		}
		printf("\t");
		j = 0;
		while(j < (20 - (strlen(number)))){
			printf(" ");
			j++;
		}
		printf("%s\n", number);
	}
	
	
	fclose(fp1);

	return 0;
}
