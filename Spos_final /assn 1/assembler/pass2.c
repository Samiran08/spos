#include<stdio.h>
#include<stdlib.h>
#define MAX 128
#define REG 4

int main()
{	
	FILE *ic,*final,*fsym,*flit;
	char *label,*ims,*op1,*op2;
	char *sym1;
	int flg = 0,i = 0,j,k,l,lt,ltflg = 0,index = 0,index2 = 0,pflg = 0,errflg = 0,ccpflg = 0;
	int temp;
	char imsbe[4],arris[2],op1be[2],op1af[3],*caddress[4],op2be[2],op2af[3];
	char *reg[REG] = {"AREG","BREG","CREG","DREG"};
	int add,ccaddress = 0,address = 0,address2 = 0,ladd;
	label = (char *)malloc(sizeof(char) * 64);
	ims  = (char *)malloc(sizeof(char) * 64);
	op1  = (char *)malloc(sizeof(char) * 64);
	op2  = (char *)malloc(sizeof(char) * 64);
	sym1  = (char *)malloc(sizeof(char) * 64);
	ic = fopen("IC.txt","r");
	final = fopen("Final.txt","w");
	fsym = fopen("symbol.txt","r");
	flit = fopen("literal.txt","r");
	
	struct symbol_literal
	{
		char *alabel[MAX];
		char *location[MAX],*lt_location[MAX],*constant[MAX];
		
	}s[100];
	
	while(!feof(fsym))											//take it in symbol structure 
	{
		//temp = (int *)malloc(sizeof(int)*64);
		s[index].alabel[index] = (char *)malloc(sizeof(char)*64);
		s[index].location[index] = (char *)malloc(sizeof(char)*64);
		fscanf(fsym,"%s\t%s\t%s\n",s[index].alabel[index],s[index].location[index],sym1);
		index++;
	}
	while(!feof(flit))								//take in literal structure						
	{
		s[index2].constant[index2] = (char *)malloc(sizeof(char)*64);
		s[index2].lt_location[index2] = (char *)malloc(sizeof(char)*64);
		fscanf(flit,"%s\t%s\n",s[index2].constant[index2],s[index2].lt_location[index2]);
		index2++;
	}
	fclose(fsym);
	fclose(flit);	
	if(!ic)
	{
		printf("Error on Opening File\n");
		exit(0);
	}
	while(!feof(ic))
	{
		fscanf(ic,"%s\t%s\t%s\t%s",label,ims,op1,op2);
		
		if(atoi(label)!=-1)    // this is for ims or decl.stat..
		{
			ladd = atoi(label);
			k =j = 0;
			for(i = 0;ims[i]!='\0';i++)   // split ims at , , ( ,) this char
			{
				if(ims[i]==',')
				{
					flg = 1;
					continue;
				}
				else if(ims[i]==')' || ims[i]=='(')
					continue;
				else if(flg==1)
				{
					arris[k] = ims[i];
					k++;
				}
				else
				{
					imsbe[j] = ims[i];
					j++;
				}
				
			}
			arris[k] = '\0';
			k++;
			imsbe[j] = '\0';
			j++;
			flg = 0;
			k = j = 0;
			for(i = 0;op1[i]!='\0';i++)  //spilt op1 at , , (,) this char
			{
				if(op1[i]==',')
				{
					flg = 1;
					continue;
				}
				else if(op1[i]=='(' || op1[i]==')')
				{
					continue;
				}	
				else if(flg==1)
				{
					op1af[k] = op1[i];
					k++;
				}
				else
				{
					op1be[j] = op1[i];
					j++;
				}	
			}
			op1af[k] = '\0';
			k++;
			op1be[j] = '\0';
			j++;
			flg = 0;
			k = j = 0;
			
			for(i = 0;op2[i]!='\0';i++) // split op2 at , , (,) this char
			{
				
				if(op2[i]==',')
				{
					flg = 1;
					continue;
				}
				else if(op2[i]=='(' || op2[i]==')')
				{
					continue;
				}	
				else if(flg==1)
				{
					op2af[k] = op2[i];
					k++;
				}
				else
				{
					op2be[j] = op2[i];
					j++;
				}	
			}
			op2af[k] = '\0';
			k++;
			op2be[j] = '\0';
			j++;
			k = j = 0;						//till here get whether any label is used and find its location


			if(strcmp(op1be,"S")==0 && strcmp(op2,"#")==0)		//It is Symbol and #
			{
				pflg = 1;
				for(i = 0; i < index; i++)
				{
					if(strcmp(s[i].alabel[i],op1af)==0)
					{
						l = i;
						errflg = 0;
						break;
					}
					else
						errflg = 1;
				}
			}
			else if(strcmp(op1be,"R")==0 && strcmp(op2,"#")==0)	//Its Reg and #
			{
				pflg = 2;
				address = atoi(op1af);
			}
			else if(strcmp(op1,"#")==0 &&strcmp(op2,"#")==0)	//# # (there is neither symbol nor register)
			{
				pflg = 3;
			}	
			else if(strcmp(imsbe,"DS")==0 && strcmp(op2,"#")==0)    //its a DS and #
			{
				pflg = 4;
				if(strcmp(arris,"1")==0)//Data storage
				{
					for(i = 0;i < atoi(op1af);i++){
						fprintf(final,"%d\t%s\t%s\t%s\n",atoi(label) + i,"--","--","--");
						printf("%d\t%s\t%s\t%s\n",atoi(label) + i,"--","--","--");
					}
				}
				else{//Declare Constant
					fprintf(final,"%s\t%s\t%s\t%s\n","+","00","00",op1af);
					printf("%s\t%s\t%s\t%s\n","+","00","00",op1af);
				}
			}
			else if(strcmp(op1be,"R")==0 && strcmp(op2be,"R")==0)	//its a Reg Reg
			{
				pflg = 6;
				address = atoi(op1af);
				printf("%d\n",address);
				address2 = atoi(op2af);
			}
			else if(strcmp(op1be,"R")==0 && strcmp(op2be,"S")==0)	//its a Reg and symbol
			{
				pflg = 7;
				for(i = 0; i < REG; i++)
				{
					address = atoi(op1af);
					break;
				}
				for(i = 0; i < index; i++)
				{
					if(strcmp(s[i].alabel[i],op2af)==0)
					{
						l = i;
						errflg = 0;
						break;
					}
					else
						errflg = 1;
				}

			}
			else if(strcmp(op2be,"R")==0 && strcmp(op1be,"S")==0)	//its a symbol and Reg 
			{
				pflg = 8;
				address = atoi(op2af);
				for(i = 0; i < index; i++)
				{
					if(strcmp(s[i].alabel[i],op1af)==0)
					{
						l = i;
						errflg = 0;
						break;
					}
					else
						errflg = 1;
				}

			}
			else if(strcmp(op1be,"R")==0 && strcmp(op2be,"L")==0)	//its Reg and literal
			{
				pflg = 9;
				address = atoi(op1af);
				for(i =0 ; i < index2; i++)
				{
					if(strcmp(s[i].constant[i],op2af)==0)
					{
						lt = i;
						break;
					}	
				}
			}
			else if(strcmp(op1be,"S")==0 && strcmp(op2be,"L")==0)//Symbol Literal
			{
				pflg = 10;
				for(i = 0; i < index; i++)
				{
					if(strcmp(s[i].alabel[i],op1af)==0)
					{
						l = i;
						errflg = 0;
						break;
					}
					else
						errflg = 1;
				}
				for(i =0 ; i < index2; i++)
				{
					if(strcmp(s[i].constant[i],op2af)==0)
					{
						lt = i;
						break;
					}	
				}
			}
			else 						//Constant Condition code in only op1 
				pflg = 5;
			if(strcmp(op2be,"S")==0)			//Symbol
			{
				ccpflg = 1;
				for(i = 0; i < index; i++)
				{
					if(strcmp(s[i].alabel[i],op2af)==0)
					{
						l = i;
						errflg = 0;
						break;
					}
					else
						errflg = 1;
				}
			}
			else if(strcmp(op2be,"R")==0)			//Reg
			{
				ccpflg = 2;
				ccaddress = atoi(op2af);
			}			
			if(errflg ==1)
			{
				printf("No Symbol Define : %s\n",op1af);
				exit(0);
			}
			if(pflg==1){										//symbol #
				fprintf(final,"%s\t%s\t%s\t%s\n","+",arris,"--",s[l].location[l]);
				printf("%s\t%s\t%s\t%s\n","+",arris,"--",s[l].location[l]);
			}
			else if(pflg==2){									//reg #
				fprintf(final,"%s\t%s\t%d\t%s\n","+",arris,address,"--");
				printf("%s\t%s\t%d\t%s\n","+",arris,address,"--");
			}
			else if(pflg==3){									//# #
				fprintf(final,"%s\t%s\t%s\t%s\n","+",arris,"--","--");
				printf("%s\t%s\t%s\t%s\n","+",arris,"--","--");	
			}
			else if(pflg==5 && ccpflg==1){								// cc symbol
				fprintf(final,"%s\t%s\t0%s\t%s\n","+",arris,op1be,s[l].location[l]);	
				printf("%s\t%s\t0%s\t%s\n","+",arris,op1be,s[l].location[l]);	
			}	
			else if(pflg==5 && ccpflg==2){								// cc reg
				fprintf(final,"%s\t%s\t0%s\t%d\n","+",arris,op1be,ccaddress);
				printf("%s\t%s\t0%s\t%d\n",label,arris,op1be,ccaddress);		
			}	
			else if(pflg==6){									//reg reg
				fprintf(final,"%s\t%s\t%d\t%d\n","+",arris,address,address2);	
				printf("%s\t%s\t%d\t%d\n","+",arris,address,address2);
			}		
			else if(pflg==7){									//reg symbol
				fprintf(final,"%s\t%s\t%d\t%s\n","+",arris,address,s[l].location[l]);
				printf("%s\t%s\t%d\t%s\n","+",arris,address,s[l].location[l]);
			}
			else if(pflg==8){									//symbol reg 
				fprintf(final,"%s\t%s\t%s\t%d\n","+",arris,s[l].location[l],address);
				printf("%s\t%s\t%s\t%d\n","+",arris,s[l].location[l],address);
			}
			else if(pflg==9){										//reg literal
				fprintf(final,"%s\t%s\t%d\t%s\n","+",arris,address,s[lt].lt_location[lt]);
				printf("%s\t%s\t%d\t%s\n","+",arris,address,s[lt].lt_location[lt]);
			}		
			else if(pflg==10){									//symbol literal 
				fprintf(final,"%s\t%s\t%s\t%s\n","+",arris,s[l].location[l],s[lt].lt_location[lt]);
				printf("%s\t%s\t%s\t%s\n","+",arris,s[l].location[l],s[lt].lt_location[lt]);
			}
			
			for(i = 0 ; i < index2 ; i++)
			{
				if(atoi(s[i].lt_location[i])==ladd+1)
				{
					fprintf(final,"%s\t%s\t%s\t%s\n","+","--","--",s[i].constant[i]);
					printf("%s\t%s\t%s\t%s\n","+","--","--",s[i].constant[i]);
					ladd +=1;
				}
			}		
			flg = 0;
			pflg = 0;
			add  = atoi(label);
		}
	}
	fclose(final);
	fclose(ic);	
	return 0;
}
