#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 128
#define	IS 11	
#define	AD 5
#define	DS 2
#define	REG 5
#define CC 6	

int main()
{
	FILE *fp,*fsym,*flit,*ic;
	char *label,*ims,*op1,*op2;
	int f,f2,opindreg = 0,opindcc = 0,op2indreg, symin = 0;
	int unknownlit = 0,unknown = 0,unknown2 = 0,unknowncc = 0;
	int opind = 0,lblind = 0,cnt = 0,counter =0,flg = 0,ind = 0,ind2 = 0,sym1 = 1;
	int glflg = 0,liti = 0,k,j,val,index = 0,i,ltind = 0,flag = 0,isind = 0;
	char *is[IS] = {"STOP","ADD","SUB","MULT","MOVER","MOVEM","COMP","BC","DIV","READ","PRINT"};
	char *ad[AD] = {"START","END","ORIGIN","EQU","LTORG"};
	char *ds[DS] = {"DC","DS"};
	char *reg[REG] = {"","AREG","BREG","CREG","DREG"};
	char *cc[CC] = {"LT","LE","EQ","GT","GE","ANY"};
	
	char lit[128],ch,origin_val[128],origin_afterval[128],temp[128];
	struct symbol_literal
	{
		char *lt[MAX],*alabel[MAX];
		int location,lt_location;
		int constant;	
	}s[100];

	label = (char *)malloc(sizeof(char) * 64);
	ims  = (char *)malloc(sizeof(char) * 64);
	op1  = (char *)malloc(sizeof(char) * 64);
	op2  = (char *)malloc(sizeof(char) * 64);

	fp = fopen("asm_input.txt","r");
	fsym = fopen("symbol.txt","w");
	flit = fopen("literal.txt","w");
	ic = fopen("IC.txt","w");
	
	if(!fp)
	{		
		printf("err");
		exit(1);
	}
	val = fscanf(fp,"%s%s%s%s\n",label,ims,op1,op2);
	if(strcmp(ims,"START")==0)
	{	
		if(atoi(op1)==0)
		{
			printf("Err on Op1....");
			exit(0);
		}
		else
		{
			counter = atoi(op1);
			printf("%d\t%s\t(%s,%d)\t%s\n",-1,"(AD,1)","c",counter,"#");
			fprintf(ic,"%d\t%s\t(%s,%d)\t%s\n",-1,"(AD,1)","c",counter,"#");
		}	
	}
	else
		exit(1);
	//if(counter==0)
	//	exit(0);	
	while(1)
	{
			
		val = fscanf(fp,"%s%s%s%s\n",label,ims,op1,op2);
		ch = op2[0];
		s[index].alabel[index] = (char *)malloc(sizeof(char)*64);
		if(strcmp(label,"#")!=0)
		{
			f = 5;									//set f = 5 if it isnt label isnt empty
			for(i = 0; i < index; i++)						//calculate index of label encountered
			{
				if(strcmp(s[i].alabel[i],label)==0)
				{
					f = 3;							//set f = 3 if you find the label
					lblind = i;
					break;
				}
				else
					f = 5;
			}	
			if(f==5)								//if label not found in the structure then add it
			{
				strcpy(s[index].alabel[index],label);
				s[index].location = counter;
				index++;
			}
			
					
		}
		if(strcmp(ims,"DS")==0)						//check if its a DS statement, if yes store the value 
		{
			val = atoi(op1);
			cnt = counter;
			//counter = counter + val - 1;
		}
		
		k = 2;j = 0;
		if(ch=='=')							// operation if you find a literal in assembly code
		{
			unknownlit = 7;						//unknownlit = 7 if its a literal
			while(op2[k]!='"')
			{
				lit[j] = op2[k];				//go on reading next character till "
				j++;k++;  
			}
			lit[j] = '\0';						
			liti = atoi(lit);					//convert it to integer and store it to the structure
			s[ltind].constant = liti;
			ltind++;
		}
		if(strcmp(ims,"LTORG")==0)
		{
			counter -= 1;	
			if(ltind==0)
			{
				flag = 1;				//flag = 1 if you havent encounterd any literal yet
			}
			else
			{
				for(i = 0 ; i < ltind; i++)
				{
					s[i].lt_location = counter + 1; //add the lit to the structure
					counter++;
				}
			}
			for(i = 0;i < ltind;i++)
				fprintf(flit,"%d\t%d\n",s[i].constant,s[i].lt_location);	//add the literal from structure to the literal file
			ltind = 0;
			fclose(flit);
		}
		if(strcmp(ims,"ORIGIN")==0)
		{
			counter -= 1;
			for(i = 0; op1[i]!='\0';i++)
			{
				if(op1[i]=='+')
				{
					flg = 1;					//flg = 1 if its forward reference
					continue;
				}
				if(op1[i]=='-')
				{
					flg = 2;					//flg = 2 if its backward reference
					continue;
				}	
				if(flg==0)
				{
					origin_val[ind] = op1[i];			//add it tot origin val till you get any displacement 
					ind++;
				}
				else
				{
					origin_afterval[ind2] = op1[i];
					ind2++;
				}
			}
			origin_val[ind] = '\0';
			ind++;
			origin_afterval[ind2] = '\0';
			ind2++;
			int originval = atoi(origin_afterval);
			printf("%d",originval);
			for(i = 0; i < index;i++)
			{
				if(strcmp(s[i].alabel[i],origin_val)==0)			//calculate LC after origin statement
				{
					if(flg==1)
						counter = s[i].location + originval;
					else if(flg==2)
						counter = s[i].location - originval;
					else
						counter = s[i].location;
				}
			}
			ind2 = 0;
			flg = 0;
		}
		if(strcmp(ims,"EQU")==0)					
		{
			counter -= 1;
		
			for(i = 0; i < index;i++)				//index is the number of entries in structure
			{
				if(strcmp(s[i].alabel[i],op1)==0)
				{
					opind = i;
					f2 = 7;					//set f2 = 7 when you find the label in the symbol stucture
					break;
				}	
			
			}
			if(f==5)
			{
				s[index-1].location = s[i].location;
					
			}
			else if(f==3)
			{
				s[lblind].location = s[opind].location;
			}		
	
		}
		/* IC code*/
		for(i = 0;i < IS; i++)						//check for the index of imperative statement in IS array
		{
			if(strcmp(ims,is[i])==0)
			{
				isind = i;
				glflg = 1;					//glflag = 1 if its a IS
				break;
			}
		}
		for(i = 0;i < AD; i++)						//check for the index of assembler directive in AD array
		{
			if(strcmp(ims,ad[i])==0)
			{
				isind = i;
				glflg = 2;					//glflg = 2 if its a AD
				break;
			}
		}
		for(i = 0;i < DS; i++)						//check for the index of declaratice statement in ds array
		{
			if(strcmp(ims,ds[i])==0)
			{
				isind = i;
				glflg = 3;					//glflg = 3 if its a DS
				break;
			}
		}
		for(i = 0;i < REG; i++)						//check for register number for op1
		{
			if(strcmp(op1,reg[i])==0)
			{
				opindreg = i;
				unknown = 1;					//set unknown = 1 if op1 is register
				break;
			}
			else
				unknown = 4;					//set unknown = 4 if op1 is not a register
		}
		for(i = 0;i < REG; i++)						//check for register number for op2
		{
			if(strcmp(op2,reg[i])==0)
			{
				op2indreg = i;
				unknown2 = 1; 					//set unknown2 = 1 if op2 is a register
				break;
			}
			else
				unknown2 = 4; 					// set unknown2 = 4 if op2 is not the register		
		}
		for(i = 0;i < CC; i++)						//comparison eg LE LT
		{
			if(strcmp(op1,cc[i])==0)
			{
				opindcc = i;
				unknowncc = 5;					//set unknowncc = 5 if you find the comparison operator 
			}
		}
		
		if(glflg==0)							//error for no opcode 
		{
			printf("No Opcode present..");
			exit(0);
		}
		else if(glflg==1)						//its a IS
		{
			
			if(strcmp(op1,"#")==0 && strcmp(op2,"#")==0){									//for stop end
				printf("%d\t(%s,%d)\t%s\t%s\n",counter,"IS",isind,"#","#");
				fprintf(ic,"%d\t(%s,%d)\t%s\t%s\n",counter,"IS",isind,"#","#");
			}
			else if(unknown==4 && strcmp(op2,"#")==0){	// label # op1 is not a register and op2 = # eg READ A
				printf("%d\t(%s,%d)\t(%s,%s)\t%s\n",counter,"IS",isind,"S",op1,"#");
				fprintf(ic,"%d\t(%s,%d)\t(%s,%s)\t%s\n",counter,"IS",isind,"S",op1,"#");
			}
			else if(unknown==1 && unknown2==1){	// reg reg both op1 and op2 are registers eg add areg,breg
				printf("%d\t(%s,%d)\t(%s,%d)\t(%s,%d)\n",counter,"IS",isind,"R",opindreg,"R",op2indreg);
				fprintf(ic,"%d\t(%s,%d)\t(%s,%d)\t(%s,%d)\n",counter,"IS",isind,"R",opindreg,"R",op2indreg);
			}
			else if(unknowncc==5 && unknown2==1){	//op1 is cc and op2 is register
				printf("%d\t(%s,%d)\t%d\t(%s,%d)\n",counter,"IS",isind,opindcc,"R",op2indreg);
				fprintf(ic,"%d\t(%s,%d)\t%d\t(%s,%d)\n",counter,"IS",isind,opindcc,"R",op2indreg);
			}
			else if(unknowncc==5 && unknown2==4 && unknownlit==0){	//cc label
				printf("%d\t(%s,%d)\t%d\t(%s,%s)\n",counter,"IS",isind,opindcc,"S",op2);
				fprintf(ic,"%d\t(%s,%d)\t%d\t(%s,%s)\n",counter,"IS",isind,opindcc,"S",op2);
			}
			else if(unknown==1 && unknown2==4 && unknownlit==0){	//reg label
				printf("%d\t(%s,%d)\t(%s,%d)\t(%s,%s)\n",counter,"IS",isind,"R",opindreg,"S",op2);
				fprintf(ic,"%d\t(%s,%d)\t(%s,%d)\t(%s,%s)\n",counter,"IS",isind,"R",opindreg,"S",op2);
			}
			else if(unknown==1 && unknownlit==7){	//reg literal
				printf("%d\t(%s,%d)\t(%s,%d)\t(%s,%d)\n",counter,"IS",isind,"R",opindreg,"L",liti);
				fprintf(ic,"%d\t(%s,%d)\t(%s,%d)\t(%s,%d)\n",counter,"IS",isind,"R",opindreg,"L",liti);
			}
		}	
		else if(glflg==2)						//its a assembler directive
		{
			if(strcmp(op1,"#")==0 && strcmp(op2,"#")==0){		// END # & LTORG # #
				fprintf(ic,"%d\t(%s,%d)\t%s\t%s\n",-1,"AD",isind,"#","#");
				printf("%d\t(%s,%d)\t%s\t%s\n",-1,"AD",isind,"#","#");
			}
			else if(unknown==4){	//END label
				fprintf(ic,"%d\t(%s,%d)\t(%s,%s)\t%s\n",-1,"AD",isind,"S",op1,"#");
				printf("%d\t(%s,%d)\t(%s,%s)\t%s\n",-1,"AD",isind,"S",op1,"#");
			}
		}		
		else if(glflg==3)
		{
			fprintf(ic,"%d\t(%s,%d)\t(%s,%s)\t%s\n",cnt,"DS",isind,"c",op1,"#");
			printf("%d\t(%s,%d)\t(%s,%s)\t%s\n",cnt,"DS",isind,"c",op1,"#");	
			cnt = counter+1;
		}	
		if(!strcmp(ims,"END"))
		{
			counter -= 1;
			break;
		}	
		counter++;
	}
	if(ltind!=0)
	{
		for(i = 0 ; i < ltind; i++)
		{
			s[i].lt_location = counter+1;
			counter++;
		}
		flit = fopen("literal.txt","a+");
		for(i = 0;i<ltind;i++){
			fprintf(flit,"%d\t%d\n",s[i].constant,s[i].lt_location);
			//printf("%d\t%d\n",s[i].constant,s[i].lt_location);
		}
	}
	fprintf(fsym,"%s\t%s\t%s\n","Name","Address","Length");
	
	for(i = 0;i<index;i++){
		fprintf(fsym,"%s\t%d\t%s\n",s[i].alabel[i],s[i].location,"1");
		//printf("%s\t%d\n",s[i].alabel[i],s[i].location);
	}
	return 0;	
}	
