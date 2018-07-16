#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>

#define L 3
#define C 5
#define h 0.5
#define ERRO 1e-10

void contorno(double **M)
{	int i, j;
	double x = 0, y = 0;

	for(i=0;i<L;i++)
	{	M[i][0] = pow(x,2);	
		M[i][C-1] = pow(x-2,2);
		x+=h;
	}

	for(i=0;i<C;i++)
	{	M[0][i] = pow(y,2);	
		M[L-1][i] = pow(y-1,2);
		y+=h;
	}
}

double f(double x)
{	return 4;
}

double relax(double **M, double **A)
{	int i, j;
	double aux, a = 0;

	for(i=1;i<L-1;i++)
	{	for(j=1;j<C;j++)
		{		if(A[i][j]==0)
				{	aux = M[i][j];
					M[i][j] = (M[i-1][j] + M[i+1][j] + M[i][j-1] + M[i][j+1] - pow(h,2)*f(0))/4.0;
					aux = fabs(aux - M[i][j]);
				}
				
				if(aux>a)
					a = aux;
		}
	}
	
	return a;	
}

void imprime(double **M)
{	int i, j;

	for(i=0;i<L;i++)
	{	for(j=0;j<C;j++)
			printf("%lf\t",M[i][j]);  
		puts("");
	}	
}

void salva(double **M)
{	int i, j;
	FILE *p;
	
	p = fopen("12.1_1.dat", "w+");
	
	for(i=0;i<L;i++)
	{	for(j=0;j<C;j++)
			fprintf(p, "%lf\t", M[i][j]);
		fprintf(p,"\n");
	}
	
	fclose(p);
}

void mascara(double **B)
{	int i, j;

	for(i=0;i<L;i++)
	{	B[i][0] = 1;	
		B[i][C-1] = 1;
	}
	
	for(i=0;i<C;i++)
	{	B[0][i] = 1;	
		B[L-1][i] = 1;
	}
}	
void main()
{	double **M, **A, erro;
	int i, j, cont = 0;
 
	M = (double**)malloc(L*sizeof(double*));
	for(i=0;i<C;i++)
		M[i] = malloc(C*sizeof(double));
		
	A = (double**)malloc(L*sizeof(double*));
	for(i=0;i<C;i++)
		A[i] = malloc(C*sizeof(double));
			
	contorno(M);
	mascara(A);
		
	do
	{	erro = relax(M,A);
		cont+=1;
	}while(erro>ERRO);
	
	imprime(M);
	salva(M);
}
