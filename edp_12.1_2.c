#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>

#define L 4
#define C 5
#define h 0.33333333
#define ERRO 1e-10

void contorno(double **M)
{	int i, j;
	double x = 1, y = 0;

	for(i=0;i<L;i++)
	{	M[i][0] = 2.0*log(x);	
		M[i][C-1] = log(pow(x,2)+1.0);
		x+=h;
	}

	for(i=0;i<C;i++)
	{	M[0][i] = pow(y,2);	
		M[L-1][i] = pow(y-1,2);
		y+=h;
	}
}

double f(double x)
{	return 0;
}

double relax(double **M)
{	int i, j;
	double aux, a = 0;

	for(i=1;i<L-1;i++)
	{	for(j=1;j<C;j++)
		{		aux = M[i][j];
				M[i][j] = (M[i-1][j] + M[i+1][j] + M[i][j-1] + M[i][j+1] - pow(h,2)*f(0))/4.0;
				aux = fabs(aux - M[i][j]);
				
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
	
	p = fopen("12.1_2.dat", "w+");
	
	for(i=0;i<L;i++)
	{	for(j=0;j<C;j++)
			fprintf(p, "%lf\t", M[i][j]);
		fprintf(p,"\n");
	}
	
	fclose(p);
}
		
void main()
{	double **M, erro;
	int i, j, cont = 0;
 
	M = malloc(L*sizeof(double*));
	for(i=0;i<C;i++)
		M[i] = malloc(C*sizeof(double));
		
	contorno(M);
		
	do
	{	erro = relax(M);
		cont+=1;
	}while(erro>ERRO);
	
	imprime(M);
	salva(M);
}
