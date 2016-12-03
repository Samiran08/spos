#include <stdio.h>
#include<string.h>
struct Sym {
		char lb[10];
		int val;
};
	
	
int main(){
	char names[80][80],p[10],l[10];
	FILE *fp1;
	FILE *fp = fopen("sy1.txt", "rw+");
	int n,ch=0,i,n1,count=0,arr[10],flag=0;
	struct Sym t;
	if(!fp) {
		printf("File not found");
	}

	while(fscanf(fp,"%s %d",t.lb,&t.val) != EOF)
	{	
		strcpy(names[count],t.lb);
		arr[count] = t.val;
		count++;
		
	}
	  printf("\n\t1.INSERT\n\t2.MODIFY VALUE\n\t3.SEARCH\n\t4.DISPLAY\n");
	  printf("\n\tEnter your choice : ");
	  scanf("%d",&ch);
	  switch(ch)
	  {
	   case 1:
	      	printf("\n\tEnter the label : ");
 		scanf("%s",l);
		printf("Enter the value");
		scanf("%d",&n1);
 		for(i = 0; i < count ; i++)
			{
				if(strcmp(names[i], l) == 0 || arr[i]==n1)
				{
					printf("\n already present and duplicates are not allowed\n");
					return 0;
				}
		}
		for(i = 0; i < count ; i++){
			arr[i]=n1;
			strcpy(names[i],l);
			fp = fopen("sy1.txt", "a+");
			fprintf(fp,"%s \t %d \n",l,n1);
			break;
		}
		break;

	   case 2:
	      printf("Enter the symbol whose value is to be changed :\n");
			scanf("%s", p);
			printf("Enter new value :\n");
			scanf("%d", &n);
			for(i = 0; i < count; i++)
			{
				if(n == arr[i])
				{
					printf("Same value already assign to another symbol\n");
					return 0;
				}
			}
		 	for(i = 0; i < count ; i++)
			{
				if(strcmp(names[i], p) == 0)
				{
					arr[i] = n;
					fp = fopen("sy1.txt", "w");
					for(i = 0; i < count; i++)
						fprintf(fp,"%s \t %d \n",names[i],arr[i]);
					break;
				}
				
			}
			printf("Done\n");
			
	      break;
	   case 3:
	      	     	printf("\n Enter the symbol :");
			scanf("%s",p);
			for(i = 0; i < count ; i++)
			{
				if(strcmp(names[i], p) == 0)
				{
					printf("\n Value no is : %d\n",arr[i]);
					flag = 1;
					break;
				}
			}
			if(flag == 0)
				printf("Symbol not present \n");
		
	      break;
	  
	 case 4:
		for(i = 0; i < count; i++)
			printf("%s \t %d \n",names[i],arr[i]);
		break;

	 default:
			printf("Invalid Choice");
			break;
	 }

	
	

	
/*void insert(){}
void modify(){}
void display(){}*/
	fclose(fp);	
	return 0;	


}	



