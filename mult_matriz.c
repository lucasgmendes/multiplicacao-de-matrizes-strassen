#include<stdio.h>
#include<math.h>
#include<time.h>

int preenche_matriz(int *, int);
int mult_matriz(int *, int *, int *, int);
int strassen(int *, int *, int *, int, int);

//Preenche a matriz com números aleatórios entre 0 a 10
int preenche_matriz(int *M, int n){
    int i=0, j=0;
    for (i = 0; i<n; i++){
        for(j=0; j<n; j++){
            M[i*n+j] = rand()%10;
        }
    }
}

//Multiplicação de Matrizes tradicional
int mult_matriz(int *A, int *B, int *C, int n){
    int i=0, j=0, k=0;
    for(i=0; i<n; i++){
        for(j = 0; j < n; j++){
            C[i*n+j]=0;
            for(k=0; k < n; k++){
                    C[i*n+j] = C[i*n+j] + A[i*n+k] * B[k*n+j];
            }
        }
    }
}

//Multiplicação de Matrizes versão de Strassen
int strassen(int *A, int *B, int *C, int m, int n){
    if(m==2){
        int A1, A2, A3, A4, B1, B2, B3, B4, *C1, *C2, *C3, *C4;
        //Valor dos 4 elementos de A
        A1 = *(A);
        A2 = *(A+1);
        A3 = *(A + n);
        A4 = *(A +  n + 1);

        //Valor dos 4 elementos de B
        B1 = *(B);
        B2 = *(B+1);
        B3 = *(B + n);
        B4 = *(B + n+1);

        //Posição de memória do Início dos 4 elementos de C
        C1 = C;
        C2 = C + 1;
        C3 = C + n;
        C4 = C + n+1;

        int P1 = (A1)*(B2-B4);
        int P2 = (A1+A2)*(B4);
        int P3 = (A3+A4)*(B1);
        int P4 = (A4)*(B3-B1);
        int P5 = (A1+A4)*(B1+B4);
        int P6 = (A2-A4)*(B3+B4);
        int P7= (A1-A3)*(B1+B2);

        *(C1) = *(C1) + P5 + P4 - P2 + P6;
        *(C2) = *(C2) + P1 + P2;
        *(C3) = *(C3) + P3 + P4;
        *(C4) = *(C4) + P1 + P5 - P3 - P7;
    }
    else{
        m=m/2;
        int A1, A2, A3, A4, B1, B2, B3, B4, C1, C2, C3, C4;

        //Posição de memória do Início dos 4 quadrantes de A
        A1 = A;
        A2 = A+m;
        A3 = A + m*n;
        A4 = A + m*(n+1);

        //Posição de memória do Início dos 4 quadrantes de B
        B1 = B;
        B2 = B+m;
        B3 = B + m*n;
        B4 = B + m*(n+1);

        //Posição de memória do Início dos 4 quadrantes de C
        C1 = C;
        C2 = C + m;
        C3 = C + m*n;
        C4 = C + m*(n+1);

        //1º e 2º quadrantes de A  x  1º e 3º quadrantes de B
        strassen(A1, B1, C1, m, n);
        strassen(A2, B3, C1, m, n);

        //1º e 2º quadrantes de A  x  2º e 4º quadrantes de B
        strassen(A1, B2, C2, m, n);
        strassen(A2, B4, C2, m, n);

        //3º e 4º quadrantes de A  x  1º e 3º quadrantes de B
        strassen(A3, B1, C3, m, n);
        strassen(A4, B3, C3, m, n);

        //3º e 4º quadrantes de A  x  2º e 4º quadrantes de B
        strassen(A3, B2, C4, m, n);
        strassen(A4, B4, C4, m, n);
    }
}

int main()
{
int n, qtd, m;

    printf("Digite a dimensao da matriz (potencia de 2):");
    scanf("%d",&n);

    printf("Digite a quantidade de repeticoes para os testes:");
    scanf("%d",&qtd);

    for (m = 0; m<qtd; m++){
        int i,j,k;
        clock_t t;

        int *A;
        int *B;
        int *C;

        A = (int *) malloc((n*n) * sizeof(int));
        if(A == NULL){
            printf("Erro de memória!");
        }

        B = (int *) malloc((n*n) * sizeof(int));
        if(B == NULL){
            printf("Erro de memória!");
        }

        C = (int *) malloc((n*n) * sizeof(int));
        if(B == NULL){
            printf("Erro de memória!");
        }

        preenche_matriz(A,n);
        preenche_matriz(B,n);


        //Imprime a matriz A
        printf("\nMatriz A:");
        for(i = 0; i < n; i++){
            printf("\n\n\n");
            for(j = 0; j < n; j++)
                printf("\t%d",A[i*n+j]);
        }

        //Imprime a matriz B
        printf("\n\nMatriz B:");
        for(i=0;i<n;i++){
            printf("\n\n\n");
            for(j=0;j<n;j++)
                printf("\t%d",B[i*n+j]);
        }

        //Inicialização da matriz resultante
        for(i = 0; i < n; i++)
            for(j = 0; j < n; j++)
                C[i*n+j]=0;

        t = clock();
        mult_matriz(A, B, C, n);
        t = clock() - t;
        printf("\n\nTempo algoritmo original: %d",t);

        //Imprime a matriz resultante
        printf("\nMatriz Resultante:");
        for(i = 0; i < n; i++){
            printf("\n\n\n");
            for(j = 0; j < n; j++)
                printf("\t%d",C[i*n+j]);
        }
        //Reinicialização da matriz resultante para segundo teste
        for(i = 0; i < n; i++)
            for(j = 0; j < n; j++)
                C[i*n+j]=0;

        t = clock();
        strassen(A, B, C, n, n);
        t = clock() - t;
        printf("\n\nTempo algoritmo Strassen: %d",t);

        //Imprime a matriz resultante
        printf("\nMatriz Resultante (Strassen):");
        for(i = 0; i < n; i++){
            printf("\n\n\n");
            for(j = 0; j < n; j++)
                printf("\t%d",C[i*n+j]);
        }

        free(A);
        free(B);
        free(C);
    }
}


