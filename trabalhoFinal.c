#include <stdio.h>
#include <math.h>

int leia(FILE *arquivo, int matriz[][20])
{
    int numero1, numero2, numero3;
    int resultado = fscanf(arquivo, "%d,%d,%d", &numero1, &numero2, &numero3); // le as informações do arquivo
    if (resultado == 3)
    {
        matriz[numero1][numero2] = numero3; // passa os valores lidos para uma matriz
        leia(arquivo, matriz);
    }
    return 0;
}

int trocaCasa(int custo[][20], int custoSalvo[][20], int rota[], int menorRota[])
{
    int menor = 999999, i = 0, menorCaminho = i, menorSalvo = 99999999;
    for (int h = 0; h < 20; h++) // Testa cada início para uma rota, sendo que 20 inícios diferentes serão testados.
    {
        menorCaminho = h;                                 // Atribui o valor do indice inicial de cada rota, sendo esse colocado como indice 0 do vetor da rota.
        int somaMenor = 0;                                // Reseta a soma dos caminhos da rota.
        for (int contador = 0; contador < 20; contador++) // Cria um contador para garantir que a rota não passará de 20 termos.
        {
            i = menorCaminho;   // Coloca o inidice i como a cidade que teve o menor caminho medido.
            menor = 999999;     // Reseta o valor do menor custo.
            rota[contador] = i; // Cria a rota usando as cidades pelas quais já se passou
            for (int j = 0; j < 20; j++)
            {
                if (custo[i][j] < menor && custo[i][j] != -1) // Compara o custo da viagem entre duas cidades em relação a uma mesma origem, excluindo as cidades pelas quais já se passou.
                {
                    menor = custo[j][i];
                    menorCaminho = j; // Atribui o indice j como a proxima cidade de origem.
                }else if(j == 19 && contador != 19 && menor == 999999){
                    return -1;
                }
            }
            for (int m = 0; m < 20; m++)
            {
                custo[m][i] = custo[i][m] = -1; // Apaga da matriz as cidades pelas quais já se passou.
            }

            if (contador != 19) // Evita que o valor da ultima rota seja adicionado, já que esse não apresenta rota disponível.
            {
                somaMenor += menor; // Faz a soma dos menores caminhos, resultando no custo total.
            }
        }
        for (int f = 0; f < 20; f++)
        {
            for (int y = 0; y < 20; y++)
            {
                custo[f][y] = custoSalvo[f][y]; // Reseta a matriz original, já que ela havia sido completamente apagada.
            }
        }
        if (somaMenor < menorSalvo) // Compara o valor da menor rota com a atual.
        {
            // Caso seja menor muda o custo e o valor dos indices da menor rota.
            menorSalvo = somaMenor;
            for (int j = 0; j < 20; j++)
            {
                menorRota[j] = rota[j];
            }
        }
    }
    return menorSalvo; // Retorna o menor custo.
}

int main()
{

    FILE *arquivo;
    int transito[20][20], criminalidade[20][20], distancia[20][20], custo[20][20], rota[20], menorRota[20], custoSalvo[20][20];
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            // Coloca as matrizes com um valor inicial de 0, para caso não haja rota entre as cidades.
            transito[i][j] = -1;
            criminalidade[i][j] = -1;
            distancia[i][j] = -1;
        }
    }

    // armazena dados dos arquivos nas matrizes
    arquivo = fopen("transito.txt", "r");
    leia(arquivo, transito);
    fclose(arquivo);

    arquivo = fopen("criminalidade.txt", "r");
    leia(arquivo, criminalidade);
    fclose(arquivo);

    arquivo = fopen("distancia.txt", "r");
    leia(arquivo, distancia);
    fclose(arquivo);

    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            custo[i][j] = (distancia[i][j]) + (distancia[i][j] * transito[i][j]) + (criminalidade[i][j] * criminalidade[i][j]); // fórmula que calcula o custo geral das rotas envolvendo trânsito, criminalidade e distância
            if (distancia[i][j] == -1)
            {
                custo[i][j] = -1; // Caso não haja rota coloca o custo como inexistente.
            }
            custoSalvo[i][j] = custo[i][j]; // Cria uma matriz identica a original.
        }
    }

    int resultado = trocaCasa(custo, custoSalvo, rota, menorRota); // Calcula a menor rota.
    
    if(resultado == -1){
        printf("Rota invalida");
    }else{   
        printf("A menor rota eh:\n");
        for (int i = 0; i < 20; i++)
        { // Imprime a menor rota e o menor custo.
            printf("%d,", menorRota[i]);
        }
        printf("\nO menor custo eh: %d", resultado);
            return 0;
    }
}