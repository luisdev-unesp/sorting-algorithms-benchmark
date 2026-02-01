
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sorts.h"
#include <time.h>

int main()
{
	// Nomes dos arquivos bin ́arios
	char *filename_cliente_dados = "clientes_dados_referencia.dat";
	char *filename_cliente_credito = "clientes_credito_referencia.dat";
	// Vari ́aveis para armazenar as dimens~oes
	int rows_X, cols_X, rows_Y, cols_Y;
	// Ler a matriz de dados do arquivo (float)
	float **X = (float **)readDataFromFile(filename_cliente_dados, &rows_X, &cols_X);
	// Ler a "matriz de uma coluna" de r ́otulos do arquivo (int)
	int **Y = (int **)readDataFromFile(filename_cliente_credito, &rows_Y, &cols_Y);

	// Nomes dos arquivos bin ́arios de checagem (avaliar)
	char *filename_cliente_dados_a = "clientes_dados_avaliar.dat";
	char *filename_cliente_credito_a = "clientes_credito_avaliar.dat";
	// Vari ́aveis para armazenar as dimens~oes
	int rows_Xa, cols_Xa, rows_Ya, cols_Ya;
	// Ler a matriz de dados do arquivo (float)
	float **Ax = (float **)readDataFromFile(filename_cliente_dados_a, &rows_Xa, &cols_Xa);
	// Ler a "matriz de uma coluna" de r ́otulos do arquivo (int)
	int **Ay = (int **)readDataFromFile(filename_cliente_credito_a, &rows_Ya, &cols_Ya);
        
        //declaração do ponteiro de ponteiro matriz de distância (matriz d)
        float **dis = NULL;
        
        // declaração do ponteiro de ponteiro da matriz de credito dos clientes de avaliação (matriz p)
        int **pag = NULL;
        
        // declaração do vetor que guarda a quantidade de clientes de referencia para avaliar
        int vet[5] = {100,1000,2000,5000,10000};
        
        char op;
        
        //flag usada para o while
        int flag = 0;
        
        // variáveis usadas para calcular o tempo de execução (time.h)
        clock_t inicio, fim;
        double tempo;
        
        
        printf("\n");
	while(flag != 1){
	      printf("1 - selection sort\n");
	      printf("2 - insertion sort\n");
	      printf("3 - merge sort\n");
	      printf("4 - quick sort\n");
	      printf("5 - shell sort\n");
	      printf("6 - sair\n");
	      printf("opção: ");
	      scanf(" %c",&op);
	    printf("\n");
	      int z=0;
	      
	      while(flag != 1 && z<5){ // termina ou quando o programa encerra ou quando percorre todo o vetor que guarda a quantidade de clientes de referencia que precisam ser usados na avaliação
	      
	        rows_X = vet[z]; // determina qual será a quantidade de clientes  
	        
	        switch(op){
	            case '1':  // opçoes de entrada
	            
	                    // chamada da função que inicia todas as matrizes (isso é feito toda vez que o algoritmo é chamado)
	                     // e já calcula a matriz distancia
	              inicial(rows_X,X,rows_Xa,Ax,Y,&dis,&pag,vet[z]);
	              
	                   // começa a contagem do tempo
	              inicio = clock();
	              
	                  // faz a ordenação da matriz distancia
	                   for(int k=0;k<rows_Xa;k++){
	                selection(rows_X, dis[k], pag[k]);
	              }
	              
	                // termina a contagem do tempo
	              fim = clock();
	              
	              break;
	            case '2': 
	              
	              inicial(rows_X,X,rows_Xa,Ax,Y,&dis,&pag,vet[z]);
	              inicio = clock();
	              for(int k=0;k<rows_Xa;k++){
	                insertion(rows_X, dis[k], pag[k]);
	              }
	              fim = clock();
	              
	              break;
	            case '3': 
	              
	              inicial(rows_X,X,rows_Xa,Ax,Y,&dis,&pag,vet[z]);
	              inicio = clock();
	                  for(int k=0;k<rows_Xa;k++){
	                merge(0, rows_X, dis[k], pag[k]);
	              }
	              fim = clock();
	              
	              break;
	            case '4': 
	              
	              inicial(rows_X,X,rows_Xa,Ax,Y,&dis,&pag,vet[z]);
	              inicio = clock();
	                  for(int k=0;k<rows_Xa;k++){
	                quick(0, rows_X-1, dis[k], pag[k]);
	              }
	              fim = clock();
	              
	              break;
	            case '5': 
	              
	              inicial(rows_X,X,rows_Xa,Ax,Y,&dis,&pag,vet[z]);
	              inicio = clock();
	                  for(int k=0;k<rows_Xa;k++){
	                shell(rows_X, dis[k], pag[k]);
	              }
	              fim = clock();
	              
	              break;
	            default:  // termina o programa
	              printf("programa encerrado\n");
	              flag = 1;
	              
	              break;
	        }
	        
	        // printa as informações principais para cada quantidade de dados (100, 1000, 2000, 5000, 10000), a forma de avaliação (k = 1, k = 3, ...), a quantidade de acertos (tanto numérico, quanto em porcentagem) e o tempo de execução
		// além disso também libera as matrizes reiniciando o processo na próxima chamada de algum sort
	        if(flag == 0){
	          for(int i=1;i<=11;i+=2){       
	              float num = avalia(rows_Xa, i, pag, Ay); // a chamada da função avalia é usada para encontrar a quantidade de acertos
	              printf("avaliaçao k = %d, acerto: %.0f | %.2f\n", i, num, (num / rows_Xa)*100);
	          }
	          tempo = ((double) (fim - inicio)) / CLOCKS_PER_SEC; 
	          printf("\no tempo de execução foi de: %.2f", tempo);
	          libera(rows_Xa, dis, pag); // libera as matrizes permitindo refazer todo o processo com qualquer outro algoritmo
	          z++; // é adicionado 1 para mudar a quantidade de dados que será usado como referencia
	        } 
	      }
	      printf("\n\n");
	}

  
  
  
  
	// Liberar memoria alocada
	for (int i = 0; i < rows_X; i++)
		free(X[i]);
	free(X);
	for (int i = 0; i < rows_Y; i++)
		free(Y[i]);
	free(Y);
	for (int i = 0; i < rows_Xa; i++)
		free(Ax[i]);
	free(Ax);
	for (int i = 0; i < rows_Ya; i++)
		free(Ay[i]);
	free(Ay);
	return 0;
}


