
#include <stdio.h>
# include <stdlib.h>

#define N 4

int main()


{

    const int colum=4;
    const int row=4;
    int a[N][N];
    int x,y,value=1;
    for (int diag=0; diag<colum;diag++){
        if (diag%2==0){
            x=0;
            y=diag;
            while (y>=0){
                a[x][y]=value;
                value++;
                x++;
                y--;
            }
        }
        else{
            x=diag;
            y=0;
            while (x>=0){
                a[x][y]=value;
                value++;
                x-=1;
                y+=1;
            }
        }
    }
    for (int diag=1; diag<colum; diag++){
        if (diag%2==0){
            x=N-1;
            y=diag;
            while (y<=N-1){
                a[x][y]=value;
                value++;
                x--;
                y++;
            }
        }
        else{
            x=diag;
            y=N-1;
            while (x<=N-1){
                a[x][y]=value;
                value++;
                x++;
                y--;
            }
        }
    }
    for (int ix=0; ix<row;ix++){
        for (int jx=0;jx< colum;jx++){
            printf("%d",a[ix][jx]);
        }
        printf("\n");
    }
    return 0;
}
