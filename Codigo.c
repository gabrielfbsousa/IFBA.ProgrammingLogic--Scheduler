#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <graphics.h>
#include <locale.h>

#define ppg 50 // padrao de pixels para o grafico

typedef struct processos //struct que recebe nome e custo dos processos
{
    char nome[80];
    int custo;
}caracteristicas;

int cont=0; //contador dos processos escalonados
int total; //total de processos escalonados

int insertionSort(int tamanho, caracteristicas proc[20]) {//insertionsort, que ordena os processos segundo o custo
    int i, j, chave;// uso de variaveis para fazer a ordenacao
    char tempnome[80];//variavel temporaria para armazenas a string do nome do processo
    for (j = 1; j < tamanho-1; j++) {//faz a varredura dos processos
        chave=proc[j].custo;//armazenamento do custo em uma variavel chave
        strcpy(tempnome, proc[j].nome);//faz-se o mesmo com a string
        i=j-1;
        
        while (i >= 0 && proc[i].custo > chave) {//Condicao para que se faca a ordenacao
            proc[i+1].qtd=proc[i].custo;//
            strcpy(proc[i+1].nome, proc[i].nome);
            i--;
        }
        proc[i+1].custo=chave;
        strcpy(proc[i+1].nome, tempnome);
    }
    return 0;
}


int resultados(int contador, caracteristicas proc[20])//funcao que mostra os resultados da ordenacao
{
    int i, acm=0;
    
    printf("\nOs processos foram escalonados com sucesso e est„o na fila de pronto.\nEssa ser· a ordem de execu√Å‚Äûo:");//Mostra-se os resultados da ordenacao feita anteriormente
    
    for(i=0; i<=contador-1; i++){
        
        printf("\nO %d´ a executar ser·∑ %s, pois tem custo %d ", i+1, proc[i].nome, proc[i].custo);
        
    }
    
    printf("\n\nTempos de resposta obtidos:");//Demonstra-se os resultados para os tempos de resposta
    for(i=0;i<=contador-1; i++)
    {
        acm=acm+proc[i].qtd;
        printf("\nO tempo de resposta do processo %s foi %d", proc[i].nome, acm);
    }
    
    printf("\n\nO tempo de resposta mÈdio foi %d\n", acm/contador);//Mostra-se o tempo medio de resposta
    return 0;
}

int menu()
{
    setlocale (LC_ALL, "Portuguese");
    caracteristicas processo[20];
    int i=0, escolha2, escolha1;
    int gd = DETECT, gm;
    printf("1 - Entrar um processo\n");//Menu de opcoes
    printf("2 - Sair\n");
    scanf("%d", &escolha1);
    if(escolha1==1){//Caso se escolha a op‚àö√ü‚àö¬£o 1 no menu
        while(i>=0){
            
            printf("\nDigite o nome do processo\n");
            scanf("%s", &processo[i].nome);
            printf("Digite o custo\n");
            scanf("%d", &processo[i].custo);
            
            cont++;
            
            printf("\nO processo foi %s,  e o custo foi %d\n\n", processo[i].nome, processo[i].qtd);
            //confirmacao do que foi digitado pelo usuario
            printf("Deseja incluir mais algum processo? \n1 - Sim\n0-Processar\n");
            scanf("%d", &escolha2);
            switch(escolha2){
                case 0: i=-2; break;//Comeca a ordenacao
                case 1: i=i; break;//Loop continua
            }
            i++;//manutencao do loop
        }
    }
    
    printf("\nOs processos est„o sendo ordenados pelo escalonador Shortest Job First");
    
    insertionSort(cont,processo);//chamada da ordenacao
    
    resultados(cont,processo);//chamada dos resultados
    
    
    system ("pause");
}

int grafdesign(caracteristicas carac[20])
{
    setcolor(WHITE);
    rectangle(0,30,639,450);
    settextstyle(SANS_SERIF_FONT,HORIZ_DIR,2);
    setcolor(YELLOW);
    outtextxy(250,0,"Escala de ExecuÁ„o");
    
    setlinestyle(SOLID_LINE,0,2);
    
    line(100,420,100,60);
    line(100,420,600,420);
    line(90,70,100,60);
    line(110,70,100,60);
    line(590,410,600,420);
    line(590,430,600,420);
    
    outtextxy(95,35,"Y");
    outtextxy(610,405,"X");
    outtextxy(85,415,"O");
}

main()
{
    caracteristicas proc[20];
    int gd=DETECT, gm;
    initgraph(&gd, &gm, "C:\\TC\\BGI");
    int i, xy, acm; //i para o loop, b para a entrada de dados das barras, xy como padr‚Äûo de tamanho
    menu();//
    grafdesign(proc);
    
    for (i=0;i<6;i++)
    {
        acm=acm+proc[i].qtd;
        xy=ppg*i;
        line(155+xy,430,155+xy,420); // linhas marcadoras
        //outtextxy(10,375-xy ,proc[i].nome); Faz o nome do processo ficar ao lado do grafico. A implementacao ocorreu,mas nao funcionou como deveria
        setfillstyle(1,i+1);
        bar(105+xy,369-xy,155+xy*proc[i].qtd,419-xy);
    }
    
    getch();
}
