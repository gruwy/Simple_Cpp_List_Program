//  Source: http://www.tud.ttu.ee/im/Vladimir.Viies/materials/PROGRAMMEERIMINE/PR2/Progra_II/Pr2_kodu_I/K-4.doc
//  Programming II
//  Homework I
//  Based on K-4.doc
//  [IALB27, 142944] Vladimir Bednoi

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct A
	{
	 char Name[21];
	 struct Address 
		{
		 char City[21];
		 char Street[21];
		 int Index;
		}
        Add;
	int H;
	char Hobby[10][21];
	}
    X[15];

int InputData(void);
int AllOut(int n);
int Search(int F[15], char Huvi[21], int n);
void Processing(int k, int F[15]);
void Output(int k, int F[15], char Huvi[21]);

int main(void)
{
 int i, j, n, k;
 char Huvi[21];
 int F[15];

n=InputData();
AllOut(n);
k=Search(F, Huvi, n);
Processing(k, F);
Output(k, F, Huvi);

getchar();
getchar();
return 0;    
}

//                      AllOut
int AllOut(int n)

{
 int i, j, x=0;
 char in[4];

do
	{
	 printf("[System] Show list of all members? yes/no: ");
	 scanf("%s", in);
	if(strcmp(in, "yes")==0)
		{
		 x=1;
		}
	else if(strcmp(in, "no")==0)
		{
		 x=-1;
		}
	}
while(x != -1 && x != 1);

if(x == 1)
	{
	printf("\n\n[System] Full list of members: \n\n");
	for(i = 0; i < n; i++)
		{
		 printf("Name:		%s \nAddress:	%s.%d.%s \nHobbies:	", X[i].Name, X[i].Add.Street, X[i].Add.City, X[i].Add.Index);
		 for(j = 0; j < X[i].H; j++)
			{
              printf("%s ", X[i].Hobby[j]);
			}
		printf("%\n\n");
		}
	}
}

//						InputData
int InputData(void)
{
 FILE *file;
 file=fopen("F1.txt", "r");
 int i, j, n=0;
 char str[100];

if(file==NULL)
	{
	 printf("\n[Error] File F1.txt not found.\n");
	 getchar();
	 getchar();
	 exit(1);
	}
	
while(!feof(file))
	{
	if(fgets(str, 100, file)) 
		{
		 n++;
		}	
	}

if(n>15)
	{
	 printf("\n[System] %d people found. Using results from 1 to 15.\n\n", n);
	 n=15;
	}
else if(n==0)
	{
	 printf("\n[System] File F1.txt is empty.\n\n", n);
	 fclose(file);
	 getchar();
	 getchar();
	 exit(1);
	}
	
rewind(file);

for(i=0; i<n; i++)
	{
	 fscanf(file, "%s %s %s %d %d", X[i].Name, X[i].Add.City, X[i].Add.Street, &X[i].Add.Index, &X[i].H);
	
	 if(X[i].H<0)
		{
		 X[i].H=0;
		}
	 else if(X[i].H>10)
		{
		 X[i].H=10;
		}
		
	 for(j=0; j<X[i].H; j++)
		{
		 fscanf(file, "%s", X[i].Hobby[j]);
		}
	}

fclose(file);
return n;
}

//						Search
int Search(int F[15], char Huvi[21], int n)
{
 int i, j, k=0;

 printf("\n[System] Enter your hobby: ");
 scanf("%s", Huvi);

 for(i=0; i<n; i++)
	{
	 for(j=0; j<X[i].H; j++)
		{
		 if(strcmp(Huvi, X[i].Hobby[j])==0)
			{
			 F[k]=i;
			 k++;
			}
		}
	}

if(k==0)
	{
	 printf("\n\n[System] Interested in %s not found. \n", Huvi);
	 getchar();
	 getchar();
	 exit(1); 
	}
return k;
}

//						Processing
void Processing(int k, int F[15])
{
 int i, j, p, q, ch;	

 for(i=0; i<k-1; i++)
	{
	 for(j=0; j<k-1; j++)
		{
		 p=F[j];
		 q=F[j+1];
		 if(_stricmp(X[p].Name, X[q].Name)>0)
			{
			 ch=F[j];
			 F[j]=F[j+1];
			 F[j+1]=ch;
			}
		}
	}
}

//						Output
void Output(int k, int F[15], char Huvi[21])
{
 FILE *file;
 file=fopen("F2.txt", "w");
 int i, j, p;
 printf("\n\n[System] Fan's of %s also are:\n", Huvi);
 for(i=0; i<k; i++)
	{
	 p=F[i];
	 fprintf(file ,"[System] Name: %s	Address: %s.%s.%d", X[p].Name, X[p].Add.City, X[p].Add.Street, X[p].Add.Index);
	 printf("\n[System] Name:		%s \nAddress:	%s.%s.%d ", X[p].Name, X[p].Add.City, X[p].Add.Street, X[p].Add.Index);
	 fprintf(file ,"\n");
	 printf("\n");
	}
fclose(file);
}
