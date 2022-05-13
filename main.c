
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int** CreeMatrice(int size)
{
    int (**Mat) = (int**) malloc(size * sizeof (int*));
    for (int i=0;i<size;i++) {
        Mat[i] = (int *) malloc(size * sizeof(int));
    }
    for (int i =0;i<size;i++)
    {
        for (int j =0;j<size;j++)
        {
            Mat[i][j]=1;
        }
    }
    return Mat;
}

void afficherMat(int** M, int size)
{
    for (int i =0;i<size;i++)
    {
        for (int j =0;j<size;j++)
        {
            printf("%d\t ",M[i][j]);
        }
        printf("\n");
    }
}

void RenplireMatrice4(int** Mat)
{
    int MatS[4][4] = {{0,1,0,1},
                      {1,0,1,0},
                      {1,0,0,1},
                      {0,1,1,0}};
    for (int i =0;i<4;i++)
    {
        for (int j =0;j<4;j++)
        {
            Mat[i][j] = MatS[i][j];
        }
    }
    //afficherMat(Mat[4][4],4);
}

void RenplireMatrice8(int** Mat)
{
    int MatS[8][8] = {{1,0,1,1,0,1,0,0},
                      {1,0,1,0,1,0,0,1},
                      {0,1,0,1,1,0,1,0},
                      {0,1,0,1,0,1,1,0},
                      {1,0,1,0,0,1,0,1},
                      {0,1,0,0,1,0,1,1},
                      {0,0,1,1,0,1,1,0},
                      {1,1,0,0,1,0,0,1}};

    for (int i =0;i<8;i++)
    {
        for (int j =0;j<8;j++)
        {
            Mat[i][j] = MatS[i][j];
        }
    }
}

void CreeCalque(int** M,int size,int dif)
{
    int C,L;
    srand(clock());
    for (int i = 0;i<dif;i++)
    {
        C = rand() % size;
        L = rand() % size;
        M[C][L] = 0;
    }
}

void CreeMatJeux(int** Ms,int** Mc,int** Mj,int size)
{
    for (int i =0;i<size;i++)
    {
        for (int j =0;j<=size;j++)
        {
            if (Mc[i][j] == 1)
            {
                Mj[i][j] = Ms[i][j];
            }else
            {
                Mj[i][j] = -1;
            }
        }
    }
}

void regle3chiffre(int col, int lig, int** M, int val) {

    //Pour quand y'en a deux d'affiler
    if (M[lig+1][col] == val && M[lig+2][col] == val){
        printf("On ne peux pas aligner plus de 2 %d", &val);
    }
    if (M[lig-1][col] == val && M[lig-2][col] == val){
        printf("On ne peux pas aligner plus de 2 %d", &val);
    }
    if (M[lig][col+1] == val && M[lig][col+2] == val){
        printf("On ne peux pas aligner plus de 2 %d", &val);
    }
    if (M[lig][col-1] == val && M[lig][col-2] == val){
        printf("On ne peux pas aligner plus de 2 %d", &val);
    }
    //Pour quand il essaye d'en mettre un au milieu
    if (M[lig+1][col] == val && M[lig-1][col] == val){
        printf("On ne peux pas aligner plus de 2 %d", &val);
    }
    if (M[lig][col+1] == val && M[lig][col-1] == val){
        printf("On ne peux pas aligner plus de 2 %d", &val);
    }
}

void regleautant(int col, int lig, int** M, int val, int size) {
    int compteur1 = 0;
    int compteur2 = 0;
    if (val == 1){
        for (int i=0; i<size; i++) {
            if (M[lig][i] == 1) {
                compteur1++;
            }
            if (M[i][col] == 1) {
                compteur2++;
            }
        }
        if (compteur1 > size/2 || compteur2 > size/2){
           printf("trop de %d dans la ligne ou la colone", &val);
        }
    }
    if (val == 0){
        for (int i=0; i<size; i++) {
            if (M[lig][i] == 0) {
                compteur1++;
            }
            if (M[i][col] == 0) {
                compteur2++;
            }
        }
        if (compteur1 > size/2 || compteur2 > size/2){
            printf("trop de %d dans la ligne ou la colone", &val);
        }
    }
}

int main() {
    int col,lig;
    int val;
    int **Msol, **Mcal, **Mjeu;
    int size=0, dif=0;
    int vie=3;

    do {
    printf("choisisez la taille de votre grille de jeux :(4 ou 8)");
        scanf("%d", &size);
    }while(size != 4 && size !=8);

    do {
    printf("choisire votre difficulter:(1=facile, 2=moyen, 3=difficile)");
    scanf("%d",&dif);
    }while(dif != 1 && dif !=2 && dif !=3);


    Mcal = CreeMatrice(size);
    CreeCalque(Mcal,size,dif*size);
    printf("\n");

    Msol = CreeMatrice(size);
    if (size == 4)
        RenplireMatrice4(Msol);
    if (size == 8)
        RenplireMatrice8(Msol);

    Mjeu = CreeMatrice(size);
    CreeMatJeux(Msol,Mcal,Mjeu,size);


    afficherMat(Mjeu,size);
    printf("Choisissez une case en indicant la colone puis la ligne\n");

    do {
    printf("Colone :");
    scanf("%d",&col );
    }while(col<1 || col>size);
    col = col -1;

    do {
    printf("Ligne :");
    scanf("%d",&lig );
    }while(lig<1 || lig>size);
    lig = lig -1;

    do {
    printf("Souhaitez vous placer un 1 ou un 0 ?\n");
    scanf("%d",&val );
    }while(val<0 || val>1);

    if (Msol[lig][col] == val) {
        printf("cest carre");
    }
    else{
        printf("cest pas carre");
    }
}

