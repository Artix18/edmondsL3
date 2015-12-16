#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int mat[1000][1000];

void gen(int N)
{
    int i,j;
    int M=0;
    char str[100];
    sprintf(str,"./tests/biparti/test-%d.in",N);
    freopen(str, "w", stdout);
    srand(time(NULL));
    
    printf("1\n");
    
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            mat[i][j]=0;
    
    for(int i = 0; i < N/2; i++)
    {
        for(int j = N/2; j < N; j++)
        {
            mat[j][i]=mat[i][j]=rand()%2;
            M += mat[i][j];
        }
    }
    
    printf("%d %d\n", N, M);
    
    for(int i = 0; i < N; i++)
    {
        int cnt=0;
        for(int j = 0; j < N; j++)
            cnt+=mat[i][j];
        printf("%d", cnt);
        for(int j = 0; j < N; j++)
        {
            if(mat[i][j])
                printf(" %d", j);
        }
        putchar('\n');
    }
    fclose(stdout);
}

int main()
{
    int N;
    for(N = 10; N <= 910; N+=100)
    {
        gen(N);
    }
    return 0;
}

