#ifndef SORTS_H
#define SORTS_H

// todas as funções utilizadas no código
void *readDataFromFile(const char *filename, int *rows, int *cols);
void selection(int n, float *v, int *pag);
void insertion (int n, float *v, int *pag);
void merge(int p, int r, float *v, int *pag);
void intercala(int p, int q, int r, float *v, int *pag);
void quick(int p, int r, float *v, int *pag);
int separa (int p, int r, float *v, int *pag);
void shell(int n, float *v, int *pag);
float **distancia(float **m, int n, float **x, int p, float **vet);
float avalia(int n, int i, int **pag, int **Ay);
void reinicia(int n, int l, int **pag, int **Y);
float **matriz_d(int n, int l);
int **matriz_p(int n, int l, int **Y);
void inicial(int n, float **X, int l, float **Ax, int **Y, float ***dis, int ***pag, int num);
void libera(int l, float **dis, int **pag);


#endif
