//FIFO - First in, First out

//Dependências de libs do C
#include <stdio.h>
#include <stdlib.h>

//Se o sistema for Windows adiciona determinada biblioteca, e definindo comandos de limpar e esperar
#ifdef WIN32
    #include <windows.h>
    #define LIMPAR system("cls")
//Senão for Windows (se for Linux)
#else
    #include <unistd.h>
    #define LIMPAR system("/usr/bin/clear")
#endif

//Mensagens
#define MENSAGEM_FINALIZANDO "\nFinalizando o programa!\n"
#define FILA_VAZIA "\nA Fila está vazia!\n"

//Aguardando 3 segundos
#define AGUARDA sleep(3)

//Estrutura da lista que será criada
typedef struct Fila {
    int valor;
    struct Fila *proximo;
} Dados;

//Funções com operações a serem realizadas
void inserindo();
void excluindo();
void mostrando();
void mostra_mensagem_de_erro();

//Inicializando os dados da lista
Dados *principal = NULL;
Dados *final = NULL;

main(){
    //Opção selecionada pelo usuário
    char escolha;
    //Laço para mostrar o menu com opções opção (char)
    do {
        //Limpando a tela para mostrar as opções de menu
        LIMPAR;
        printf("\nFILA\n\n");
        printf("Escolha: \n");
        printf("\t1 - Adicionar valor na Fila\n");
        printf("\t2 - Excluir valor da Fila\n");
        printf("\t3 - Listar os valores da Fila\n");
        printf("\t9 - Finalizar\n\n");
        printf("Sua Opção: ");
        scanf("%c", &escolha);
        switch(escolha) {
            //Adicionando
            case '1':
                inserindo();
                break;
            //Excluindo
            case '2':
                if(principal!=NULL){
                    excluindo();
                }
                else{
                    printf(FILA_VAZIA);
                    getchar();
                }
                break;
            //Listando
            case '3':
                if(principal!=NULL){
                    mostrando();
                }
                else{
                    printf(FILA_VAZIA);
                    getchar();
                }
                break;
            case '9':
                printf(MENSAGEM_FINALIZANDO);
                AGUARDA;
                exit(0);
                break;
            //Valor inválido
            default:
                mostra_mensagem_de_erro(MENSAGEM_FINALIZANDO);
                break;
        }
        //Impedindo sujeira na gravação da escolha
        getchar();
    }
    while (escolha > 0); //Loop Infinito
}

//Adicionando
void inserindo(){
    int val;
    LIMPAR;
    printf("\nInserção: \n");
    printf("--------------------------------------\n");
    printf("Insira o valor a ser inserido: ");
    scanf("%d",&val);
    Dados *atual = (Dados*)malloc(sizeof(Dados));
    atual -> valor = val;
    atual -> proximo = NULL;

    //se o principal estiver vazio, será o atual
    if(principal == NULL){
        principal = final = atual;
    }
    //senão, o próximo valor que será o atual
    else{
        final->proximo=atual;
        final=atual;
    }

    printf("\nValor inserido!\n");
    printf("--------------------------------------");
    getchar();
}

//Exclusão
void excluindo(){
    Dados *auxiliar;
    printf("\nExclusão: \n");
    printf("--------------------------------------\n");
    //o auxiliar será o próximo da principal
    auxiliar=principal->proximo;
    //limpando a principal
    free(principal);
    //a principal será a auxiliar
    principal=auxiliar;
    printf("\nValor excluido!\n");
    printf("--------------------------------------");
    getchar();
}

//Mostrando
void mostrando(){
    int posicao=0;
    Dados *nova=principal;
    LIMPAR;
    printf("\nMostrando valores: \n");
    printf("--------------------------------------\n");
    //laço de repetição para mostrar os valores
    for (; nova != NULL; nova = nova->proximo) {
        posicao++;
        printf("Posição %d, contém o valor %d\n", posicao, nova->valor);
    }
    printf("--------------------------------------");
    getchar();
}

//Mostrando erro de digitação
void mostra_mensagem_de_erro(){
    LIMPAR;
    printf("\nErro de Digitação: \n");
    printf("--------------------------------------\n");
    printf("\nDigite uma opção válida (pressione -Enter- p/ continuar)!\n\n");
    printf("--------------------------------------");
    getchar();
}
