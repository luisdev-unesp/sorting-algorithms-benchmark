#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "sorts.h"

/*
OBS: em todos os sorts a única mudança feita foi: a criação de no máximo uma ou duas variáveis para a mudança sincrona das informações de credito / bom pagador.
Usado para garantir que nenhuma informação da matriz-p (pagadores / crédito)  perdesse sua conexão com o cliente de referencia .
Ao mesmo tempo que a distancia do cliente de referencia muda de posição, sua informação de crédito (diz se é bom pagador ou não) muda.
*/

// essa função faz a leitura dos dados de referência, ela também é usada para ler os dados de avaliação
void *readDataFromFile(const char *filename, int *rows, int *cols)
{
	FILE *file = fopen(filename, "rb");
	if (!file)
	{
		printf("N~ao foi possıvel abrir o arquivo %s\n", filename);
		return NULL;
	}
	void *data = NULL;
	// Ler o cabe ̧calho: n ́umero de linhas e colunas
	fread(rows, sizeof(int), 1, file);
	fread(cols, sizeof(int), 1, file);
	printf("Matriz %s - Linhas: %d, Colunas: %d\n", filename, *rows, *cols);
	// Verifica se  ́e uma matriz com uma coluna (nesse caso, trata como int) ou uma matriz com m ́ultiplas colunas (trata como float)
	if (*cols == 1)
	{
		// Tratar como matriz de uma coluna de inteiros
		data = (int **)malloc(*rows * sizeof(int *));
		for (int i = 0; i < *rows; i++)
		{
			((int **)data)[i] = (int *)malloc(sizeof(int));
			fread(((int **)data)[i], sizeof(int), 1, file); // Ler cada elemento como int
		}
	}
	else
	{
		// Tratar como matriz de m ́ultiplas colunas de floats
		data = (float **)malloc(*rows * sizeof(float *));
		for (int i = 0; i < *rows; i++)
		{
			((float **)data)[i] = (float *)malloc(*cols * sizeof(float));
			fread(((float **)data)[i], sizeof(float), *cols, file); // Ler linha por linha como float
		}
	}
	fclose(file);
	return data;
}



void selection(int n, float *v, int *pag)
{
	      // procedimento padrão do selection sort
		int i, j, min, x;
		float w;
		for (i = 0; i < n - 1; i++)
		{
			min = i;
			for (j = i + 1; j < n; j++)
			{
				if (v[j] < v[min])
				{
					min = j;
				}
			}
			w = v[i];
			v[i] = v[min];
			v[min] = w;
			
			x = pag[i];
			pag[i] = pag[min];
			pag[min] = x;
		}
	
}


void insertion (int n, float *v, int *pag) {
      
	  int i, j, y;
	  float x;
	  for (j = 1;  j < n; j++) {
		  x = v[j];
		  y = pag[j];
		  for (i = j-1; i >= 0 && v[i] > x; i--){
			  v[i+1] = v[i];
			  pag[i+1] = pag[i];
		  }
		  v[i+1] = x;
		  pag[i+1] = y;
	  }
      
}

void merge(int p, int r, float *v, int *pag) {
    if (p < r - 1) {
        int q = (p + r) / 2;
        merge(p, q, v, pag);
        merge(q, r, v, pag);
        intercala(p, q, r, v, pag);
    }
}

void intercala(int p, int q, int r, float *v, int *pag) {
    int i, j, k;
    int *z;
    float *w;
    w = malloc((r - p) * sizeof(float));
    z = malloc((r - p) * sizeof(int));
    if (w == NULL || z == NULL) {
        if (w != NULL) free(w); 
        if (z != NULL) free(z);
        return; 
    }
    i = p;
    j = q;
    k = 0;
    while (i < q && j < r) {
        if (v[i] <= v[j]){ 
            w[k] = v[i];
            z[k] = pag[i];
            k++;
            i++;
        }else{ 
            w[k] = v[j];
            z[k] = pag[j];
            k++;
            j++;
        }
    }
    while (i < q){ 
        w[k] = v[i];
        z[k] = pag[i];
        k++;
        i++;
    }
    while (j < r){
        w[k] = v[j];
        z[k] = pag[j];
        k++;
        j++;
    }
    for (i = p; i < r; i++){ 
        v[i] = w[i - p];
        pag[i] = z[i - p];
    }   
    free(w);
    free(z);
}

void quick(int p, int r, float *v, int *pag) {
    int j;
    if (p < r) { 
        j = separa (p, r, v, pag); 
        quick(p, j - 1, v, pag);
        quick(j + 1, r, v, pag);
    }
}

int separa (int p, int r, float *v, int *pag) {
    float pivo = v[r];
    int pivo_p = pag[r];
    int t = r - p + 1;
    float *aux = malloc(t * sizeof(float));
    int *outro = malloc(t * sizeof(int));
    if (aux == NULL || outro == NULL) {
        if (aux != NULL) free(aux); 
        if (outro != NULL) free(outro);
        return -1; 
    }
    int menor = 0;
    int maior = r - p;
    for (int k = p; k <= r; k++) {
        if (k == r){ 
          continue; 
        }
        if (v[k] < pivo || (v[k] == pivo && pag[k] < pivo_p)) {
            aux[menor] = v[k];
            outro[menor] = pag[k];
            menor++;
        } 
        else {
            aux[maior] = v[k];
            outro[maior] = pag[k];
            maior--;
        }
    }
    int posicao = p + menor;
    int atual = p;
    for (int i = 0; i < menor; i++) {
        v[atual] = aux[i];
        pag[atual] = outro[i];
        atual++;
    }
    v[posicao] = pivo;
    pag[posicao] = pivo_p;
    atual++;
    for (int i = maior + 1; i < t; i++) {
        v[atual] = aux[i];
        pag[atual] = outro[i];
        atual++;
    }
    free(aux);
    free(outro);
    return posicao;
}

void shell(int n, float *v, int *pag) {
     
        for (int gap = n/2; gap > 0; gap /= 2){
            for (int i = gap; i < n; i += 1){
                float temp = v[i];
                int bin = pag[i];
                int j;
                for (j = i; j >= gap && v[j - gap] > temp; j -= gap){
                    v[j] = v[j - gap];
                    pag[j] = pag[j - gap];
                }
                v[j] = temp;
                pag[j] = bin;
            }
        }
    
}

// essa função cria a matriz distância, a distancia é calculada pela distancia euclidiana de cada cliente de avaliação ao cliente de referencia
float **distancia(float **m, int n, float **x, int p, float **vet)
{ 
// m = matriz de referencia
//n = quantidade de clientes referencia
//x = matriz de ava
//p = quantidades ava
//vet = matriz distancia
	for (int k = 0; k < p; k++)
	{
		for (int i = 0; i < n; i++)
		{
			float aux = 0;
			for (int j = 0; j < 6; j++)
			{
				aux += pow(x[k][j] - m[i][j], 2);
			}
			vet[k][i] = sqrt(aux);
		}
	}
	return vet;
}

// essa função devolve a main a quantidade de acertos
float avalia(int n, int i, int **pag, int **Ay){
// inicia -se a quantidade de acertos com 0
  float acerto=0;
  
  for(int j=0;j<n;j++){
  // crio uma variável bom para armazenar a quantidade de clientes com crédito 1 (bom pagador) e a variável mau faz a contagem de quantos tem um crédito ruim 
    int bom=0;
    int mau=0;
    
    for(int k=0;k<i;k++){ // percorro a matriz i vezes, esse (i) vem da main e ele diz  a quantidade de clientes de referência que precisam ser analisados
      if(pag[j][k] == 1){
        bom++;
      }else{
        mau++;
      }
    }
    if((bom > mau && Ay[j][0] == 1) || (mau > bom && Ay[j][0] == 0)){ // esse if verifica a moda, ou seja, o que mais aparece é levado como resultado, se entrar no if significa que obteve um acerto
      acerto += 1;
    }
  }
  return acerto; // retorno a quantidade de acertos a main
}

void reinicia(int n, int l, int **pag, int **Y){ // reinicia a matriz de pagador, essa função é usada para sempre que o usuário quiser escolher diversas ordenações, as matrizes não estejam organizadas
        for (int i = 0; i < l; i++)
	{
		for (int j = 0; j < n; j++)
		{
			pag[i][j] = Y[j][0];
		}
	}
}

float **matriz_d(int n, int l){ // aloca a matriz de distancias e devolve para a main
        float **dis = malloc(sizeof(float *) * l); 
	for (int i = 0; i < l; i++)
	{
		dis[i] = malloc(sizeof(float) * n);
	}
  return dis;
}

int **matriz_p(int n, int l, int **Y){  // aloca a matriz de pagadores (credito) e reinicia seus valores para depois devolver para a main
        int **pag = malloc(sizeof(int *) * l); 
	for (int i = 0; i < l; i++)
	{
		pag[i] = malloc(sizeof(int) * n);
	}
	reinicia(n,l,pag,Y);
  return pag;
}

void inicial(int n, float **X, int l, float **Ax, int **Y, float ***dis, int ***pag, int num){ // chama todas as outras funções que inicializam as matrizes e depois calcula as distancias
  printf("\n\n---------- ref (%d) --------------\n\n",num);
  *dis = matriz_d(n,l);
  *pag = matriz_p(n,l,Y);
  distancia(X,n,Ax,l,*dis);
}

void libera(int l, float **dis, int **pag){ // libera a memória reservada a matriz-d (distancia) e a matriz-p (pagador / credito)
  for (int i = 0; i < l; i++){
    free(dis[i]);
  }
  free(dis);
  for (int i = 0; i < l; i++){
    free(pag[i]);
  }
  free(pag);
}
