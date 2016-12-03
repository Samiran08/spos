#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>
#define MAX 20

//structure for symbol table
struct sym_tab{
	char sym[MAX];
	int adr,l;
}s[MAX];
int sc,loc;//sym,location counter

//structure for literal table
struct lit_tab{
	char lit[MAX];
	int adr;
}l[MAX];

int lc;//literal counter
int pt[MAX]={0},pc;//pool table

//structure for mnemonic opcode table
struct mne_op_tab{
	char mne[MAX],clas[MAX];
	int op,l;
}m[MAX]={{"START","AD",1,0},
	{"END","AD",2,0},
	{"ORIGIN","AD",3,0},
	{"EQU","AD",4,0},
	{"LTORG","DL",5,0},
	{"DC","DL",1,0},
	{"DS","DL",2,0},
	{"STOP","IS",0,1},
	{"ADD","IS",1,1},
	{"SUB","IS",2,1},
	{"MULT","IS",3,2},
	{"MOVER","IS",4,1},
	{"MOVEM","IS",5,1},
	{"BC","IS",6,1},
	{"COMP","IS",7,1},	
	{"DIV","IS",8,2},
	{"READ","IS",9,1},
	{"PRINT","IS",10,1},
	};
	
//structure for register	
struct regs{
	char reg[MAX];
	int val;
}r[4]={{"AREG",1},
	{"BREG",2},
	{"CREG",3},
	{"DREG",4}};
//display code
void disp(char fname[MAX]){
	char s[80];
	FILE *fp;
	fp=fopen(fname,"r");
	while(fgets(s,80,fp))
	printf("%s",s);
	fclose(fp);
}

//performing pass1
void pass1(){
	FILE *fp1,*fp2;
	int i,j,k=0,n;
	char s1[80],w1[80],w2[80],w3[80],w4[80],str[80],temp[80];
	fp1=fopen("src1.asm","r");
	fp2=fopen("ic.asm","w");

	while(fgets(s1,80,fp1)){

		n=sscanf(s1,"%s%s%s%s",w1,w2,w3,w4);
		if(n==4){
			strcpy(s[sc].sym,w1);//copy symbol into symbol table
			s[sc].adr=loc;
			s[sc++].l=1;
			n--;
			strcpy(w1,w2);
			strcpy(w2,w3);
			strcpy(w3,w4);
		}

		if(n==3){
			if(strcmp(w2,"EQU")==0){
				strcpy(s[sc].sym,w1);//copying symbol //w1 is sym
				for(i=0;i<sc;i++)
					if(strcmp(w3,s[i].sym)==0)//ckecking  w3 is it present in symbol table
						break;
			
				s[sc].adr=s[i].adr;//assign address to new symbol
				s[sc].l=1;
				for(i=0;i<MAX;i++)
					if(strcmp(w2,m[i].mne)==0)
						break;
				sc++;
				//eg:-  200 (IS,4) 1 (L,0)
				sprintf(str,"%d (%s,%d) - (S,%d)\n",loc,m[i].clas,m[i].op,sc);
				
			}

			else if(strcmp(w2,"DS")==0 || strcmp(w2,"DC")==0){
				for(i=0;i<sc;i++){
					if(strcmp(w1,s[i].sym)==0)//comparing symbol with sym table
						break;
				}		
				s[i].adr=loc;
				for(j=0;j<MAX;j++)
					if(strcmp(w2,m[j].mne)==0)//comparing mnemonic operation with table 
						break;
				sprintf(str,"%d (%s,%d) - (C,%s)\n",loc,m[j].clas,m[j].op,w3);


 				//setting length and location counter accor. to operation
 				//if DC then  set to 1 and increase by 1 otherwise acc. to w3
 				
				if(strcmp(w2,"DS")==0){
					s[i].l=atoi(w3);
					loc+=atoi(w3);
				}
				else{
					s[i].l=1;
					loc+=1;
				}
			}

			else{
				for(i=0;i<MAX;i++)
					if(strcmp(w1,m[i].mne)==0)//comparing mnemonic operation with table 
					break;
				w2[4]='\0'; // register 

				for(j=0;j<4;j++)
					if(strcmp(w2,r[j].reg)==0)
					break;
				sprintf(str,"%d (%s,%d) %d ", loc, m[i].clas, m[i].op, r[j].val);
				loc+=m[i].l;
				if(w3[0]=='=')
				{
					for(i=pt[pc];i<lc;i++)
						if(strcmp(w3,l[i].lit)==0)
							break;
					if(i==lc){
						strcpy(l[lc].lit,w3);
						lc++;
						sprintf(temp,"(L,%d)\n",lc-pt[pc]);

					}
					else{
						sprintf(temp,"(L,%d)\n",i-pt[pc]);
					}
				}
	
				else{
					//checking symbol ,if not then add 
					for(i=0;i<sc;i++)
						if(strcmp(w3,s[i].sym)==0)
						break;
					if(i==sc){
						strcpy(s[sc].sym,w3);
						sprintf(temp,"(S,%d)\n",sc);
						sc++;
					}
					else
					sprintf(temp,"(S,%d)\n",sc);
				}
			strcat(str,temp);
			}
		}


		if(n==2){
			if(strcmp(w1,"START")==0){
				for(i=0;i<MAX;i++)
					if(strcmp(m[i].mne,w1)==0)
					break;
				sprintf(str,"%d (%s,%d) - (C,%s)\n",loc,m[i].clas,m[i].op,w2);
				loc=atoi(w2);	//intialization of location counter
			}
			if(strcmp(w1,"ORIGIN")==0){
				for(i=0;i<MAX;i++)
					if(strcmp(m[i].mne,w1)==0)
					break;
				j=k=0;
				sprintf(str,"%d (%s,%d) - ",loc-1,m[i].clas,m[i].op);
				while(!ispunct(w2[j]))
					temp[k++]=w2[j++];//taking symbol into temp not offset i,e LOOP e,g ORIGIN LOOP+1
				temp[k]='\0';


				for(k=0;k<sc;k++)
					if(strcmp(temp,s[k].sym)==0)//comparing symbol
						break;
				loc=s[k].adr;//setting locaton counter to address of symbol

				//getting offset 
				if(w2[j]=='+'){
					k=0;
					while(w2[j]!='\0')
						temp[k++]=w2[j++];
						temp[k]='\0';
						loc+=atoi(temp);
				}
				if(w2[j]=='-'){
					k=0;
					while(w2[j]!='\0')
						temp[k++]=w2[j++];
						temp[k]='\0';
						loc-=atoi(temp);
				}
				sprintf(temp,"(C,%d)\n",loc);
				strcat(str,temp);
			}
		}

		if(n==1){
			char mm[5],temp1[5],ss[5];
			int mn,abc,jj;
			if(strcmp(w1,"LTORG")==0 || strcmp(w1,"END")==0){
				for(i=0;i<MAX;i++)
					if(strcmp(m[i].mne,w1)==0)
					break;
					
				strcpy(ss,m[i].clas);
				mn=m[i].op;	
				sprintf(str,"%d (%s,%d) - ",loc,m[i].clas,m[i].op);
				for(i=pt[pc];i<lc;i++){
					l[i].adr=loc;	//assigning address to literal
					strcpy(mm,l[i].lit);
					jj=strlen(mm);
					abc=0;
					j=0;
					temp1[jj];
					while(mm[j]!='\0'){
						if(mm[j]!='=' && (isdigit(mm[j]))){
							temp1[abc]=mm[j];
							abc++;
						}
						j++;
					}	
					
					temp1[abc]='\0';	
					printf("****%d\n",atoi(temp1));
					sprintf(temp,"(C,%d)\n",atoi(temp1));
					strcat(str,temp);
					fputs(str,fp2);
					loc++;
					sprintf(str,"%d (%s,%d) -  ",loc,ss,mn);
				}
				if(strcmp(w1,"LTORG")==0)
					pt[++pc]=lc;//assigning literal count to pool table 
			}
			continue;
		}
		fputs(str,fp2);
	}
	fclose(fp1);
	fclose(fp2);	
}

void show_tab(){
	int i;
	printf("\n------------SYMTAB------------------\n");
	printf("Symbol\tAddress\tLength\n");
	for(i=0;i<sc;i++)printf("%s\t%d\t%d\n",s[i].sym,s[i].adr,s[i].l);
		printf("\n------------LITTAB------------------\n");
		printf("Literal\tAddress\n");
	for(i=0;i<lc;i++)
		printf("%s\t%d\n",l[i].lit,l[i].adr);
		printf("\n------------POOLTAB------------------\n");
		printf("LITTAB_PTR\n");
	for(i=0;i<=pc;i++)
		printf("%d\n",pt[i]);
}
void pass2(){
	struct mne_op_tab1{
	char mne[MAX],clas[MAX];
	int op,l;
}m1[MAX]={
	{"START","AD",1,0},
	{"END","AD",2,0},
	{"ORIGIN","AD",3,0},
	{"EQU","AD",4,0},
	{"LTORG","AD",5,0},
	{"DC","DL",1,0},
	{"DS","DL",2,0},
	{"STOP","IS",0,1},
	{"ADD","IS",1,1},
	{"SUB","IS",2,1},
	{"MULT","IS",3,2},{"MOVER","IS",4,1},
	{"MOVEM","IS",5,1},
	{"BC","IS",6,1},
	{"DIV","IS",7,2},
	{"READ","IS",8,1},
	{"PRINT","IS",9,1},
	};

	int i,j;
	char s1[80],temp[80],str[80],w1[80],w2[80],w3[80],w4[80];
	FILE *fp1,*fp2;
	pc=0;
	fp1=fopen("ic.asm","r");
	fp2=fopen("trgt.asm","w");
	while(fgets(s1,80,fp1)){
		sscanf(s1,"%s%s%s%s",w1,w2,w3,w4);
		sprintf(str,"%s ",w1);
		//assembler directive for START,ORIGIN,EQU
		if(strcmp(w2,"(AD,1)")==0 || strcmp(w2,"(AD,3)")==0 || strcmp(w2,"(AD,4)")==0){
			strcpy(str,"\0");
			continue;
		}
		//assembler directive for LTORG,END
		else if(strcmp(w2,"(AD,2)")==0 || strcmp(w2,"-")==0|| strcmp(w2,"(AD,5)")==0){
			i=0;
			j=2;
			while(w4[j]!='\0')
				temp[i++]=w4[j++];
				temp[i]='\0';
				strcat(str,temp);
				strcat(str,"\n");
			if(strcmp(w2,"(AD,5)")==0)
				pc++;
		}
		else if(strstr(w2,"IS")!=NULL){
			if(w4[1]=='L')
				i=l[w4[3]-48+pt[pc]].adr;
			else
				i=s[w4[3]-48].adr;
			sprintf(temp,"%c %s %d\n",w2[4],w3,i);
			strcat(str,temp);
		}
		else
			continue;
		fputs(str,fp2);
		strcpy(str,"\0");
	}
	fclose(fp1);
	fclose(fp2);	
}
void main()
{
	disp("src1.asm");
	pass1();
	show_tab();
	printf("\nIntermediate Code:\n");
	disp("ic.asm");
	pass2();
	printf("\nTarget Code:\n");
	disp("trgt.asm");
}
