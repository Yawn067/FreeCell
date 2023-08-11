#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>

typedef struct noCarta{
    short numero;
    char nape;
    struct noCarta *prox;
}tCarta;

tCarta *primMonte = NULL;
tCarta *primMesa[] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
tCarta *primNape[] = {NULL,NULL,NULL,NULL};
tCarta *temp[] = {NULL,NULL,NULL,NULL};

bool ehVermelho(tCarta *carta){
    return ((carta->nape>=3) && (carta->nape<=4));
}//end ehVermelho

bool ehPreto(tCarta *carta){
    return ((carta->nape>=5)&&(carta->nape<=6));
}//end ehPreto

bool saoCoresDiferentes(tCarta *carta1, tCarta *carta2){
    return ((ehVermelho(carta1)&&ehPreto(carta2))||
             (ehPreto(carta1)&&ehVermelho(carta2)));
}//end saoCoresDiferentes

void gerarBaralho(){
    int i,j;
    tCarta *ult;

    //coracao=3, ouro=4, paus=5, espada=6
    for(i=0; i<4; i++){
        for(j=1; j<14; j++){
            if(primMonte==NULL){
                primMonte = (tCarta *)malloc(sizeof(tCarta));
                ult = primMonte;
            }//end if
            else{
                ult->prox=(tCarta *)malloc(sizeof(tCarta));
                ult=ult->prox;
            }//end else
            ult->nape=i+3;
            ult->numero=j;
            ult->prox=NULL;
        }//end for j
    }//end for i
}//end gerarBaralho

void embaralhaBaralho(){
    int i,j,sort;
    tCarta *ant, *atual;

    for(i=0; i<26; i++){
        //total de mudanca
        sort=rand()%52;
        ant=NULL;
        atual=primMonte;
        for(j=0; j<sort; j++){
            //localizar a carta no monte
            ant = atual;
            atual=atual->prox;
        }//end for j
        if(sort>0){
            ant->prox=atual->prox;
            atual->prox=primMonte;
            primMonte=atual;
        }//end if
    }//end for i
}//end embaralhaBaralho

void distribuirMesa(){
    int i=0;
    tCarta *auxMonte, *auxMesa;

    while(primMonte != NULL){
        auxMonte = primMonte;
        primMonte=primMonte->prox;

        if(primMesa[i]==NULL){
            primMesa[i]=auxMonte;
            primMesa[i]->prox=NULL;
        }//end if
        else{
            auxMesa=primMesa[i];
            primMesa[i]=auxMonte;
            primMesa[i]->prox=auxMesa;
        }//end else
        if(primMonte==NULL){
            break;
        }//end if
        i=(i+1)%8;
    }//end while
}//end distribuirMesa

void imprime(){
    int i;
    tCarta *atual;

    printf("[TEMP]=");
    for(i=0; i<4; i++){
        if(temp[i]!=NULL){
            printf("%d-[%02d/%c] ", i, temp[i]->numero,temp[i]->nape);
        }//end if
        else{
            printf("%d[    ] ", i);
        }//end else
    }//end for i
    printf("\n\n");
    for(i=0; i<4; i++){
        atual=primNape[i];
        printf("[NAPE %d(%c)]=", i, i+3);
        while(atual!=NULL){
            printf("[%02d/%c]", atual->numero,atual->nape);
            atual=atual->prox;
        }//end while
        printf("\n");
    }//end for i
    printf("\n");
    for(i=0; i<8; i++){
        atual=primMesa[i];
        printf("[MESA %d]=", i);
        while(atual!=NULL){
            printf("[%02d/%c]", atual->numero, atual->nape);
            atual=atual->prox;
        }//end while
        printf("\n");
    }//end for i
    printf("\n");
}//end imprime

void moveMesaNape(){
    int posMesa, posNape;
    tCarta *aux, *ant, *atual;

    printf("Posicao Pilha Mesa (0-7): ");
    scanf("%d", &posMesa);
    getchar();
    if((posMesa>=0)&&(posMesa<=7)&&(primMesa[posMesa]!=NULL)){
        printf("Posicao Nape (0-3): ");
        scanf("%d", &posNape);
        getchar();
        ant = NULL;
        atual=primMesa[posMesa];
        while(atual->prox!=NULL){
            ant=atual;
            atual=atual->prox;
        }//end while
        if(posNape>=0&&posNape<=3&&
           ((atual->numero==1 && primNape[posNape]==NULL && atual->nape==posNape+3)||
           ((primNape[posNape]!=NULL)&&(atual->nape==primNape[posNape]->nape)&&
            (atual->numero-1==primNape[posNape]->numero)))){
            if(ant==NULL){
                primMesa[posMesa]=NULL;
            }//end if
            else{
                ant->prox=NULL;
            }//end else
            if(primNape[posNape]==NULL){
                primNape[posNape]=atual;
            }//end if
            else{
                aux = primNape[posNape];
                primNape[posNape]=atual;
                primNape[posNape]->prox=aux;
            }//end else
        }//end if
        else{
            printf("Nao pode mover carta para nape\n");
        }//end else
    }//end if
    else{
        printf("Pilha invalida ou vazia\n");
    }//end else
}//end moveMesaNape

void moveMesaTemp(){
    int posMesa, posTemp;
    tCarta *ant, *atual, *aux;

    printf("Posicao Pilha Mesa (0-7): ");
    scanf("%d", &posMesa);
    getchar();
    if((posMesa>=0)&&(posMesa<=7)&&(primMesa[posMesa]!=NULL)){
        printf("Posicao Temp (0-3): ");
        scanf("%d", &posTemp);
        getchar();
        ant=NULL;
        atual=primMesa[posMesa];
        while(atual->prox!=NULL){
            ant=atual;
            atual=atual->prox;
        }//end while
        if((posTemp>=0)&&(posTemp<=3)&&(temp[posTemp]==NULL)){
           if(ant==NULL){
                primMesa[posMesa]=NULL;
           }//end if
           ant->prox=NULL;
           temp[posTemp]=atual;
        }//end if
        else{
            printf("Nao pode mover carta para temp\n");
        }//end else
    }//end if
    else{
        printf("Pilha invalida ou vazia\n");
    }//end else
}//end moveMesaTemp

void moveTempMesa(){
    int posTemp, posMesa;
    tCarta *atual;
    printf("Posicao Temp (0-3): ");
    scanf("%d",&posTemp);
    getchar();
    if((posTemp>=0)&&(posTemp<=3)&&(temp[posTemp]!=NULL)){
        printf("Posicao Pilha Mesa (0-7): ");
        scanf("%d", &posMesa);
        getchar();
        if((posMesa>=0)&&(posMesa<=7)){
            if(primMesa[posMesa]==NULL){
                primMesa[posMesa]=temp[posTemp];
                temp[posTemp]=NULL;
            }//end if
            else{
                atual=primMesa[posMesa];
                while(atual->prox!=NULL){
                    atual=atual->prox;
                }//end while
                if((saoCoresDiferentes(temp[posTemp],atual))&&
                   ((atual->numero-1==temp[posTemp]->numero))){
                    atual->prox=temp[posTemp];
                    temp[posTemp]=NULL;
                }//end if
                else{
                    printf("Nao pode mover temp para mesa\n");
                }//end else
            }//end else
        }//end if
    }//end if
    else{
        printf("Temp vazio\n");
    }//end else
}//end moveTempMesa

void moveNapeTemp(){
    int posNape, posTemp;
    tCarta *atual;
    printf("Posicao Nape (0-3): ");
    scanf("%d", &posNape);
    getchar();
    if((posNape>=0)&&(posNape<=3)&&primNape[posNape]!=NULL){
        printf("Posicao Temp (0-3): ");
        scanf("%d", &posTemp);
        getchar();
        if((posTemp>=0)&&(posTemp<=3)&&temp[posTemp]==NULL){
            if(primNape[posNape]->prox==NULL){
                temp[posTemp]=primNape[posNape];
                primNape[posNape]=NULL;
            }else{
                temp[posTemp]=primNape[posNape];
                primNape[posNape]=primNape[posNape]->prox;
            }//end else
        }else{
            printf("Posicao invalida ou ocupada\n");
        }//end else
    }else{
        printf("Posicao invalida ou vazia\n");
    }//end else
}//end moveNapeTemp

void moveTempNape(){
    int posTemp, posNape;
    tCarta *atual;

    printf("Posicao Temp (0-3): ");
    scanf("%d", &posTemp);
    getchar();
    if(posTemp>=0 && posTemp<=3 && temp[posTemp]!=NULL){
        printf("Posicao Nape (0-3): ");
        scanf("%d", &posNape);
        getchar();
        if((posNape>=0 && posNape<=3) && ((primNape[posNape]==NULL && temp[posTemp]->numero==1 && temp[posTemp]->nape==posNape+3)||
            ((primNape[posNape]!=NULL)&&(temp[posTemp]->nape==primNape[posNape]->nape)&&
            (temp[posTemp]->numero-1==primNape[posNape]->numero)))){
            if(primNape[posNape]==NULL){
                primNape[posNape]=temp[posTemp];
                temp[posTemp]=NULL;
            }else{
                temp[posTemp]->prox=primNape[posNape];
                primNape[posNape]=temp[posTemp];
                temp[posTemp]=NULL;
            }//end else
        }else{
            printf("Posicao invalida\n");
        }//end else
    }else{
        printf("Posicao vazia ou ocupada\n");
    }//end else
}

void moveNapeMesa(){
    int posNape, posMesa;
    tCarta *atual;

    printf("Posicao Nape (0-3): ");
    scanf("%d", &posNape);
    getchar();
    if(posNape>=0 && posNape<=3 && primNape[posNape]!=NULL){
        printf("Posicao Mesa (0-7): ");
        scanf("%d", &posMesa);
        getchar();
        if(posMesa>=0 && posMesa<=7){
            if(primMesa[posMesa]==NULL){
                primMesa[posMesa]=primNape[posNape];
                primNape[posNape]=primNape[posNape]->prox;
            }else{
                atual=primMesa[posMesa];
                while(atual->prox!=NULL){
                    atual=atual->prox;
                }//end while
                if((saoCoresDiferentes(primNape[posNape],atual))&&
                   ((atual->numero>primNape[posNape]->numero))){
                    atual->prox=primNape[posNape];
                    primNape[posNape]=primNape[posNape]->prox;
                }else{
                    printf("Movimento invalido\n");
                }//end else
            }//end else
        }else{
            printf("Posica invalida ou vazia\n");
        }
    }else{
        printf("Posica invalida ou vazia\n");
    }//end else
}//end moveNapeMesa

void moveMesaMesa(){
    int posIni, posFim, op, bloco;
    tCarta *atualIni, *atualFim, *antIni, *aux, *ant;

    printf("Posicao Mesa origem(0-7): ");
    scanf("%d", &posIni);
    getchar();
    printf("Posicao Mesa destino(0-7): ");
    scanf("%d", &posFim);
    getchar();
    if(posIni<0||posIni>7||posFim<0||posFim>7||primMesa[posIni]==NULL){
        printf("Posicao invalida ou nao ha cartas nessa mesa\n");
        return;
    }//end if
    printf("Deseja mover apenas uma carta(1) ou um bloco de cartas(2): ");
    scanf("%d", &op);
    getchar();
    switch(op){
        case 1:
            atualIni=primMesa[posIni];
            atualFim=primMesa[posFim];
            antIni=NULL;
            while(atualIni->prox!=NULL){
                antIni=atualIni;
                atualIni=atualIni->prox;
            }//end while
            if(atualFim==NULL){
                primMesa[posFim]=atualIni;
                if(antIni==NULL){
                    primMesa[posIni]=NULL;
                }else{
                    antIni->prox = NULL;
                }//end else
            }else{
                while(atualFim->prox!=NULL){
                    atualFim=atualFim->prox;
                }//end while
                if(atualFim->numero-1==atualIni->numero && saoCoresDiferentes(atualFim,atualIni)){
                    atualFim->prox=atualIni;
                    if(antIni==NULL){
                        primMesa[posIni]=NULL;
                    }else{
                        antIni->prox = NULL;
                    }//end else
                }else{
                    printf("Movimento invalido\n");
                }
            }//end else
            break;
        case 2:
            printf("Digite ate qual numero vai o bloco: ");
            scanf("%d", &bloco);
            getchar();
            atualIni=primMesa[posIni];
            atualFim=primMesa[posFim];
            aux=NULL;
            if(atualIni->numero==bloco){
                aux=atualIni;
                ant=NULL;
            }else{
                while(atualIni->prox!=NULL){
                    if(atualIni->prox->numero==bloco){
                        aux=atualIni->prox;
                        ant=atualIni;
                    }//end if
                    atualIni=atualIni->prox;
                }//end while
            }//end else
            if(bloco>=1 && bloco<=13 && aux!=NULL){
                atualIni=aux;
                while(atualIni->prox!=NULL){
                    if(atualIni->numero-1!=atualIni->prox->numero || saoCoresDiferentes(atualIni, atualIni->prox)==false){
                        printf("A sequencia desse bloco nao esta correta\n");
                        return;
                    }//end else
                    atualIni=atualIni->prox;
                }//end while
                if(atualFim==NULL){
                    primMesa[posFim]=aux;
                    while(aux!=NULL){
                        atualFim=aux;
                        aux=aux->prox;
                        atualFim->prox=aux;
                    }//end while
                    if(ant==NULL)
                            primMesa[posIni]=NULL;
                        else
                            ant->prox=NULL;
                }else{
                    while(atualFim->prox!=NULL){
                        atualFim=atualFim->prox;
                    }//end while
                    if(atualFim->numero-1==aux->numero&&saoCoresDiferentes(atualFim, aux)){
                        while(aux!=NULL){
                            atualFim->prox=aux;
                            aux=aux->prox;
                            atualFim=atualFim->prox;
                            atualFim->prox=aux;
                        }//end while
                        if(ant==NULL)
                            primMesa[posIni]=NULL;
                        else
                            ant->prox=NULL;
                    }else{
                        printf("Movimento invalido\n");
                    }
                }
            }else{
                printf("Esse numero nao existe\n");
            }//end else
            break;
        default:
            printf("Opcao invalida\n");
    }
}

void destroiPilha(){
    int i;
    tCarta *atual;
    for(i=0; i<=7; i++){
        atual=primMesa[i];
        while(atual!=NULL){
            atual=primMesa[i]->prox;
            free(primMesa[i]);
            primMesa[i]=atual;
        }//end while
    }//end for
    for(i=0;i<=3;i++){
        atual=primNape[i];
        while(atual!=NULL){
            atual=primNape[i]->prox;
            free(primNape[i]);
            primMesa[i]=atual;
        }//end while
        free(temp[i]);
    }//end for
}

int main(int argc, char **argv){
    int op=0;
    srand(time(NULL));
    gerarBaralho();
    embaralhaBaralho();
    distribuirMesa();

     while(op!=8){
        imprime();
        printf("(1)Move Mesa-Nape\n");
        printf("(2)Move Mesa-Temp\n");
        printf("(3)Move Temp-Mesa\n");
        printf("(4)Move Nape-Temp\n");
        printf("(5)Move Temp-Nape\n");
        printf("(6)Move Nape-Mesa\n");
        printf("(7)Move Mesa-Mesa\n");
        printf("(8)Sair\n");
        printf("Opcao: ");
        scanf("%d", &op);
        getchar();
        switch(op){
        case 1:
            moveMesaNape();
            break;
        case 2:
            moveMesaTemp();
            break;
        case 3:
            moveTempMesa();
            break;
        case 4:
            moveNapeTemp();
            break;
        case 5:
            moveTempNape();
            break;
        case 6:
            moveNapeMesa();
            break;
        case 7:
            moveMesaMesa();
            break;
        default:
            if(op!=8)
            printf("Opcao invalida\n");
            break;
        }//end switch
    }//end while
    destroiPilha();
    return 0;
}//end main
