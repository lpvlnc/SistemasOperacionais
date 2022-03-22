/*
** Multiplicação de Matrizes Quadradas (N x N)
** Prof. Filipo Mór - filipomor.com
** 24 de março de 2021
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define ITERACOES 3
#define QTD_VALORES 8

void SalvaMatriz(int Altura, int Largura, int* M, char* Titulo, char* NomeArquivo)
{
	int L, C; //Linha e Coluna
	
	FILE *fp = fopen(NomeArquivo, "w");
	if( fp == NULL)
	{
		printf("\n::: Erro abrindo arquivo '%s''!\n", NomeArquivo);
		exit(EXIT_FAILURE);
	}

    fprintf(fp, " %s \n", Titulo);
    for(L = 0; L < Altura; L++)
    {
        for(C = 0; C < Largura; C++)
        {
            fprintf(fp, " %2d ", M[L * Altura + C]);
        }
        fprintf(fp, "\n");
    }	
    
    fclose(fp);
	
}

void MostraMatriz(int Altura, int Largura, int* M, char* Titulo)
{
    int L, C; //Linha e Coluna

    printf(" %s \n", Titulo);
    for(L = 0; L < Altura; L++)
    {
        for(C = 0; C < Largura; C++)
        {
            printf(" %2d ", M[L * Altura + C]);
        }
        printf("\n");
    }
}

void PreencheMatriz(int Altura, int Largura, int* M, int Valor)
{
    int L, C; //Linha e Coluna

    for(L = 0; L < Altura; L++)
    {
        for(C = 0; C < Largura; C++)
        {
            M[L * Altura + C] = Valor;
        }
    }

}

int main()
{
	int i = 0;
	int valores[QTD_VALORES] = { 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000 };
	double vetorMedia[QTD_VALORES];
	int N = 0;
	for(i = 0; i < QTD_VALORES; i++)
	{
		N = valores[i];
		int* Ma = (int*)malloc(sizeof(int) * N * N);
	    if ( Ma == NULL )
	    {
	        printf("\nErro alocando memoria! \n");
	        exit( EXIT_FAILURE );
	    }
	
	    int* Mb = (int*)malloc(sizeof(int) * N * N);
	    if ( Mb == NULL )
	    {
	        printf("\nErro alocando memoria! \n");
	        exit( EXIT_FAILURE );
	    }
	
	    int* Mc = (int*)malloc(sizeof(int) * N * N);
	    if ( Mc == NULL )
	    {
	        printf("\nErro alocando memoria! \n");
	        exit( EXIT_FAILURE );
	    }
	
		printf("\n###############################################################\n");
		printf("::: Matrix Multiplication                                   ::: \n");
		printf("::: Width: %d | Height: %d | Total Size: %d       :::\n", N, N, N*N);
		printf("::: Preenchendo as matrizes...                              :::\n");
	
	    PreencheMatriz(N, N, Ma, 1);
	    PreencheMatriz(N, N, Mb, 3);
	    PreencheMatriz(N, N, Mc, 0);
	
		printf("::: Done! Now calculating...                                :::");
	    //MostraMatriz(N, N, Ma, " Matriz A ");
	    //MostraMatriz(N, N, Mb, " Matriz B ");
	    //MostraMatriz(N, N, Mc, " Matriz C ");
	
		double vetorTempoProcessamento[ITERACOES];
		int j = 0;
		for (j = 0; j < ITERACOES; j++)
		{
			int L, C, K;
	
		    // conta o tempo de processamento
		    clock_t tempo;
		    tempo = clock();
		
		    //C = A . B
		    for(L=0; L<N; L++)
		    {
		        for(C=0; C<N; C++)
		        {
		            for(K=0; K<N; K++)
		            {
		                Mc[L * N + C] += Ma[L * N + K] * Mb[K * N + C];
		                //Mc[L * N + C] += Ma[C * N + K] * Mb[K * N + L];
		            }
		        }
		    }
		
			clock_t final = clock();
			double tempoProcessamento = ((double)(final-tempo)) / (double)(CLOCKS_PER_SEC);
			vetorTempoProcessamento[j] = tempoProcessamento;
			printf("\n:::---------------------------------------------------------:::\n");
			printf("::: Iteracao: %d                                            :::\n", j);
			printf("::: Tempo de processamento: %f segundos.              :::", tempoProcessamento);
		}
		printf("\n:::---------------------------------------------------------:::\n");
		
		double media = 0;
		for(j = 0; j < ITERACOES; j++)
		{
			media += vetorTempoProcessamento[j];
		}
		media = media / ITERACOES;
		vetorMedia[i] = media;
		printf("::: Media: %f                                         :::\n", media);
		printf("###############################################################\n");
		/*
		printf("Calculation is done! Now saving data on the disc...\n");
	    //MostraMatriz(N, N, Mc, " Matriz C ");
	    printf("Saving Matriz A on disc...\n");
		//SalvaMatriz(N, N, Ma, "::: Matriz A :::", "matrizA.txt");
	    printf("Saving Matriz B on disc...\n");
		//SalvaMatriz(N, N, Mb, "::: Matriz B :::", "matrizB.txt");
	    printf("Saving Matriz C on disc...\n");
		//SalvaMatriz(N, N, Mc, "::: Matriz C :::", "matrizC.txt");
	    
	    printf("\nAll done! Tempo de processamento: %f segundos.\n", tempoProcessamento);
	    */
	}
	
	printf("\n+-------------------------------+");
	printf("\n| Resultados finais:            |");
	for(i = 0; i < QTD_VALORES; i++)
	{
		printf("\n+-------------------------------+");
		printf("\n| VALOR: %d - MEDIA: %f |", valores[i], vetorMedia[i]);
	}
	printf("\n+-------------------------------+");
    
    return 0;
}

