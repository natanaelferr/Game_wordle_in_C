#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include "dicionario.h"


void drawWord(char hasWord[]);
bool dictionaryHas(char userWord[]);
bool youWin(char userWord[]);
void mostraPalavras(int attempt, char* wordAttempts[][6], char userWord[]);


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
        printf(VERMELHO_COR "->" AZUL_COR " Letras incorretas e ausentes ganham um tom cinza escurecido.\n\n" RESET_COR);
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
                
                drawWord(mainWord);             //sorteia
                bool isGaming = true;
                int attempts = 6;               //numero de tentativas restantes, inicia o jogo com 6

                char userOpinion[6];            //palpite do usuario
                //este vetor possui as letras da palavra e os espaços 
                char *chart[7][6];
                int  colors[5];                 //vetor de indicação de cores para 
                
                //aqui entra no loop das tentativas do jogo
                while(isGaming){
                    printf(BRANCO_COR "\nTentativas restantes: " VERMELHO_COR "%d\n", attempts);
                    printf("\n");
                    printf("Palavra certa para teste: %s", mainWord);
                    printf("\n" BRANCO_COR);
                    printf("\n");
                    printf("Digite aqui seu palpite: " VERMELHO_COR);
                    scanf("%s", &userOpinion);
                    fflush(stdin);
                    


                    //verifica se a palavra existe no dicionario
                    if(dictionaryHas(userOpinion)){
                        if(youWin(userOpinion)){
                            printf(VERDE_COR "Voce venceu, parabens!\n \n" RESET_COR);
                            isGaming = false;
                        }else{
                            if(attempts > 1){//entra aqui se ainda n venceu e se tem tentativa sobrando
                                attempts--; //entrou já diminui uma tentativa
                                mostraPalavras(attempts, chart, userOpinion);//imprime as palavras válidas que o usuário ja digitou


                            }else{
                                printf("\nVoce perdeu!\n");
                                isGaming = false;
                            }
                        }
                    }else{
                        printf("\nEsta palavra nao existe no dicionario!\n\n");
                    }
                    
                }
                }
            if(menuOption == 2 ){isPlaying = 0;}
            if(menuOption == 3 ){exit(0);}
        }
    } 
}

//imprime na tela as palavras que o usuário ja digitou
                    //tentativas      palavras tentadas      palavra do usuario
void mostraPalavras(int attempt, char *wordAttempts[][6], char userWord[]){
    printf("Palavra do usuario: %s\n", userWord);
    printf("Tentativas restantes: %d\n", attempt);
    for(int i = 0; i <= 5; i++){
        if(i >= 0 && i < 5){
            wordAttempts[6 - attempt][i] = userWord[i];
            printf("Caractere %d: %c  ", i, wordAttempts[6 - attempt][i]);
        }else{
            wordAttempts[6 - attempt][i] = '\0';
        }    
    }

    for(int i = 0; i < 6; i++){
        printf("%s\n", wordAttempts[i][0]);
    }
    
}


//verifica se o usuário já venceu
bool youWin(char userWord[]){
    for(int i = 0; i <= 5; i++){
        if(userWord[i] == mainWord[i]){
            i += 1;
            if(mainWord[i] == userWord[i] && i == 5){
                return true;
            }
        }else{
            return false;
        }
    } 
}


//verifica se a palavra existe no dicionário
bool dictionaryHas(char userWord[6]){
    int escopoInicial = 0;
    int escopoFinal = DICIONARIO_TAM-1;

    for(int a = 0;a <= 5;a++){
        for(int b=escopoInicial; b <= escopoFinal; b++){
            if(userWord[a] == dicionario[b][a]){
                escopoInicial = b;
                b = escopoFinal + 1;
            }
            if(b == escopoFinal && userWord[a] != dicionario[b][a]){
                return false;
            }
        }

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

srand( (unsigned)time(NULL) );
index = 0 + rand() % (DICIONARIO_TAM - 0);

for (i = 0; dicionario[index][i] != '\0'; i++){
    hasWord[i] = dicionario[index][i];
}
    hasWord[i]='\0';
}