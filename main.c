#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "dicionario.h"


bool youWin(char []);//determina se o usuario venceu
void drawWord(char []);//sorteia a palavra do usuario
void showVector(int []);//mostra um vetor unidimensional, debug
bool dictionaryHas(char []);//ver se a palavra ta dentro do dicionario
bool verificaDentro(int,int []);//
void guardaPalavras(int , char *[][6], char []);//guarda as palavras do user dentro de um array bidimensional                    
void vetorCores(int [], char [], char [], int);//emite um vetor 0 = n existe 1 = existe e lugar errado 2 = existe e lugar certo
void guardaVetorCores(int [], int [][5], int);

char mainWord[6];



int main(void)
{
    int  menuOption;
    bool isPlaying;


    while(1){
        printf(AZUL_COR "Bem vindo ao jogo Wordle, logo abaixo estao as instrucoes.\n\n");
        printf(VERMELHO_COR "->" AZUL_COR " Em cada uma das seis rodadas, voce precisa inserir uma nova palavra de cinco digitos.\n");
        printf(VERMELHO_COR "->" AZUL_COR " Se voce acertar a letra e a posicao dela, o caractere fica em verde.\n");
        printf(VERMELHO_COR "->" AZUL_COR " Caso acerte a presenca dela, mas nao o posicionamento, ela fica em amarelo.\n");
        printf(VERMELHO_COR "->" AZUL_COR " Letras incorretas e ausentes ganham um tom Branco.\n\n" RESET_COR);
        isPlaying = 1;


        while(isPlaying){
            printf(BRANCO_COR "Menu:\n");
            printf("|1| Sortear uma palavra\n");
            printf("|2| Instrucoes\n");
            printf("|3| Sair\n");
            printf("Digite aqui: " VERMELHO_COR);
            scanf("%d", &menuOption);
            fflush(stdin);
            printf(RESET_COR "\n");


            if(menuOption > 3 && menuOption < 1){printf(VERMELHO_COR "Entrada Invalida!" RESET_COR);}
            //quando a opção 1 é escolhida
            if(menuOption == 1 ){
                // mainWord[0] = 'r';
                // mainWord[1] = 'a';
                // mainWord[2] = 'j';
                // mainWord[3] = 'a';
                // mainWord[4] = 's';
                // mainWord[5] = '\0';
                drawWord(mainWord);             //sorteia
                bool isGaming = true;
                int attempts = 6;  
                int userCount = 0;          //numero de tentativas restantes, inicia o jogo com 6

                char userOpinion[6];            //palpite do usuario
                //este vetor possui as letras da palavra e os espaços 
                char *chart[7][6];
                int  colors[5];                 //vetor de indicação de cores para 
                int allColors[6][5];

                //aqui entra no loop das tentativas do jogo
                while(isGaming){
                    printf(BRANCO_COR "\nTentativas restantes: " VERMELHO_COR "%d\n", attempts);
                    //printf("Palavra certa para teste: %s", mainWord);
                    printf("\n" BRANCO_COR);
                    printf("Digite aqui seu palpite: " VERMELHO_COR);
                    scanf("%s", &userOpinion);
                    printf(BRANCO_COR "\n");
                    fflush(stdin);

                    
                    //verifica se a palavra existe no dicionario
                    if(dictionaryHas(userOpinion)){
                        if(youWin(userOpinion)){
                            printf(VERDE_COR "Voce venceu, parabens!\n \n" RESET_COR);
                            isGaming = false;
                        }else{
                            if(attempts > 1){//entra aqui se ainda n venceu e se tem tentativa sobrando
                                guardaPalavras(attempts, &chart, userOpinion);//imprime as palavras válidas que o usuário ja digitou
                                vetorCores(colors, userOpinion, mainWord, attempts);
                                guardaVetorCores(colors, allColors, userCount);

                                for(int l=0; l <= userCount; l++){
                                    printf("        ");
                                    for(int n = 0;n < 5;n++){
                                        if(allColors[l][n] == 1){//printa na cor
                                            printf(AMARELO_COR "%c ", chart[l][n]);
                                            printf(BRANCO_COR);
                                        }else if(allColors[l][n] == 2){//printa na cor
                                            printf(VERDE_COR "%c ", chart[l][n]);
                                            printf(BRANCO_COR);
                                        }else{//printa branco
                                            printf(BRANCO_COR "%c ", chart[l][n]);
                                        }
                                        
                                    }
                                    printf("\n");
                                }
                                userCount += 1;
                                attempts--; // diminui uma tentativa
                                

                            }else{
                                printf(VERMELHO_COR "\nVoce perdeu!\n" BRANCO_COR);
                                printf(CIANO_CLARO_COR "A palavra sorteada era:\n" BRANCO_COR);
                                printf(VERDE_COR);
                                for(int i=0;i < 5;i++){
                                    printf("%c ", mainWord[i]);
                                }
                                printf("\n\n");
                                printf(BRANCO_COR);
                                isGaming = false;
                            }
                        }
                    }else{
                        printf(VERMELHO_COR "\nEsta palavra nao existe no dicionario!\n\n" BRANCO_COR);
                    }
                    
                }
                }
            if(menuOption == 2 ){isPlaying = 0;}
            if(menuOption == 3 ){exit(0);}
        }
    } 
}

//guarda os vetores dentro de um array bidimensional
void guardaVetorCores(int colors[], int allColors[][5], int attempt){
    //basicamente vai guardar o vetor cores dentro de uma matriz usando o argumento attempt para se localizar no indice
    for(int l=0;l<5;l++){
        allColors[attempt][l] = colors[l];
    }
}


//função que emite um vetor com indicações de cores
void vetorCores(int colors[], char userWord[], char mainWord[], int attempt){   
    //usa partes de codigos abaixo para basicamente ler a palavra do usuario e fazer comparações com a palavra sorteada
    //dependendo de como a letra esta posicionada na palavra sorteada e se existe ou nao 
    //libera um vetor indicando 0, 1 ou 2 0 = nao existe 1 = existe e esta no lugar errado 2 = existe e esta no lugar certo
    //ok
    for(int i = 0; i < 5; i++){
        if(userWord[i] == mainWord[i]){
            colors[i] = 2;
        }else{
            colors[i] = 0;
        }
    }
    // a c a t a => escolhida[i]
    // a m o r a => usuario[l]
    //(2,0,0,0,2)
    //(2,0,0,0,2)
    //verde branco branco branco verde

    for(int i=0;i<5;i++){
        for(int l=0;l < 5;l++){
            if(mainWord[i] == userWord[l] && i != l && colors[l] != 2 && colors[i] != 2 && colors[l] != 1){
                colors[l] = 1;
                l = 5;
            }else{
                continue;
            }
        }
    }

}


//guarda as palavras que o usuário ja digitou
                    //tentativas      palavras tentadas      palavra do usuario
void guardaPalavras(int attempt, char *wordAttempts[][6], char userWord[]){
    //basicamente guarda as palavras do usuario dentro de um array e usa o argumento attempt para se localizar no indice da matriz
    //printf("Palavra do usuario: %s\n", userWord);
    //printf("Tentativas restantes: %d\n", attempt);
    // 6 - attempt
    // 6 - 6 = 0
    // 6 - 5 = 1
    // 6 - 4 = 2
    // 6 - 3 = 3
    // 6 - 2 = 4
    // 6 tentativas sobrando
    //digitei errado
    //5 tentativas sobrando
    //errou
    //4
    //digitou errado
    for(int i = 0; i <= 5; i++){
        if(i >= 0 && i < 5){
            wordAttempts[6 - attempt][i] = userWord[i];
            //printf("Caractere [%d][%d]: %c \n", 6 - attempt,i, wordAttempts[6 - attempt][i]);
        }else{
            wordAttempts[6 - attempt][5] = '\0';
        }    
    }
    
}


//verifica se o usuário já venceu
bool youWin(char userWord[]){
    //compara cada caractere se estiver igual true senao false
    if(
        userWord[0] == mainWord[0]  &&
        userWord[1] == mainWord[1]  &&
        userWord[2] == mainWord[2]  &&
        userWord[3] == mainWord[3]  &&
        userWord[4] == mainWord[4]  &&
        userWord[5] == mainWord[5]
    ){
        return true;
    }else{
        return false;
    }
}


//verifica se a palavra existe no dicionário
bool dictionaryHas(char userWord[6]){
    int escopoInicial = 0;
    int escopoFinal = DICIONARIO_TAM-1;

    //usa o método de gargalo para verificar se a palavra existe
    //basicamente inicia procurando o escopo do caractere inicial(de onde até onde vai)
    //depois procura o próximo caractere apenas naquele escopoInicial
    //vai afunilando o escopo até encontrar o ultimo  caractere igual

    
    for(int a = 0;a <= 5;a++){//até chegar no '\0' que garante o tamanho adequado da palavra e evita bugs com palavras maiores ou menores
        //serve para encontrar a primeira posição(escopo inicial)
        for(int b=escopoInicial; b <= escopoFinal; b++){
            if(userWord[a] == dicionario[b][a]){
                escopoInicial = b;
                b = escopoFinal + 1;
            }
            if(b == escopoFinal && userWord[a] != dicionario[b][a]){
                return false;
            }
        }

//serve para encontrar a ultima posição(escopo final)
        for(int c=escopoInicial; c <= escopoFinal; c++){
            if(userWord[a] != dicionario[c][a]){
                escopoFinal = c-1;
                c = escopoFinal+1;
                c = escopoFinal + 1;
            }
            if(escopoInicial == escopoFinal && a == 5 && userWord[a] == dicionario[c][a]){
                return true;
            }
        }
    }
}


//sorteia a palavra e adiciona a um vetor
void drawWord(char hasWord[]){
int i = 0;
int index = 0;

srand( (unsigned)time(NULL) );//usa a função time para alimentar a função rand de sorteio
index = 0 + rand() % (DICIONARIO_TAM - 0);//a função time é a semente

for (i = 0; dicionario[index][i] != '\0'; i++){
    hasWord[i] = dicionario[index][i];//percorre os indices do dicionario e seleciona uma palavra aleatoria
}
    hasWord[i]='\0';
}


//verifica se n esta dentro de box
bool verificaDentro(int n, int box[]){
    //apenas verifica se um inteiro esta dentro daquele vetor uni especificado
        for(int i = 0;i < 5;i++){
            if(n == box[i]){
                return true;
            }if(i == 4 && n != box[i]){
                return false;
            }
        }
    }


//imprime um vetor na tela
void showVector(int vet[]){
    //apenas mostra um vetor uni na tela para teste e debug
    for(int i=0;i<5;i++){
        printf("vet[%d]: %d  ",i, vet[i]);
    }
    printf("\n\n");
}