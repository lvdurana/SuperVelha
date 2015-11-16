#include "FGerais.c"

#define POS_VELHA_X 10
#define POS_VELHA_Y 1
#define COR_FUNDO PRETO_A<<4
#define COR_TEXTO BRANCO_B

typedef struct jogador {
  char tipo; //0=jogador/1,2,3=computador f,m,d/4=replay
  char num; //1,4
  char simb; //0=o/1=x
  char nome[15];
} jogador;

typedef struct partida {
 int partida;
 char JogVelha[3][3];
 char resultado;
 char turno[9];

} partida;

typedef struct campo {
  char mapa[23][23];
  char cur;
  char mat[3][3];
  char turno;
  char jog_atual; //0 e 1
  jogador jog[2];
} campo;

//Definir símbolos
unsigned char simb_anim[][5][5]={
    {{0,1,2,3,0},{3,255,255,255,1},{2,255,255,255,2},{1,255,255,255,3},{0,3,2,1,0}},
    {{5,255,255,255,0},{255,6,255,1,255},{255,255,2,255,255},{255,3,255,8,255},{4,255,255,255,9}},
    {{255,4,255,4,255},{3,255,5,255,3},{2,255,255,255,2},{255,1,255,1,255},{255,255,0,255,255}},
    {{255,255,0,255,255},{255,7,255,1,255},{3,255,255,255,6},{255,2,255,4,255},{255,255,5,255,255}},
    {{255,6,5,4,0},{255,7,255,255,1},{255,8,255,2,2},{9,9,255,3,3},{10,10,255,255,255}},
    {{255,5,4,5,255},{5,4,3,4,5},{4,3,2,3,4},{255,255,1,255,255},{255,255,0,255,255}}

};
char simb_anim_tam[]={4,10,6,8,11,6};
char simb_cor[]={AZUL_B,VERMELHO_B,ROSA_B,AMARELO_B,CIANO_B,VERDE_B};

//Definir músicas


/*int menu()
{
  int sel=1,go=0;

  //Tela inicial
  system("color 8F");
  system("cls");
  printf("\n\n\n                                                 \n   _                  _                _ _       \n  |_|___ ___ ___    _| |___    _ _ ___| | |_ ___ \n  | | . | . | . |  | . | .'|  | | | -_| |   | .'|\n _| |___|_  |___|  |___|__,|   \\_/|___|_|_|_|__,|\n|___|   |___|                                    \n");
  printf("\n\n\n\n\n\n\n\n\n\n\nAPERTE QUALQUER TECLA");
  getch();
  system("cls");
  //Escolher modo
  do{
    system("cls");
    printf("\n\n   Escolha um advers\240rio:\n\n\n");
    if (sel == 1){
      printf("   \332\304\304\304\304\304\304\304\304\304\304\304\304\304\304\277\n");
      printf("   \263    Humano    \263            ");printf ("   Computador\n");
      printf("   \300\304\304\304\304\304\304\304\304\304\304\304\304\304\304\331");
    }
    else{
      printf("                               ");printf("\332\304\304\304\304\304\304\304\304\304\304\304\304\304\304\277\n");
      printf("        Humano                 ");printf("\263  Computador  \263\n");
      printf("                               ");printf("\300\304\304\304\304\304\304\304\304\304\304\304\304\304\304\331");
    }
    switch (converter_entrada()){
      case ('A'):
      case ('D'):
        sel *= -1;
        break;
      case ('\15'):
        go = 10;
        break;
    }
  }while (go != 10);

  if(sel<1)
    sel=dificuldade();
  escolha_nome(sel);
  return(sel);
}


int dificuldade()
{
  int sel=2,hard;
  do{
    system("cls");
    printf("\n\n   Escolha um nivel de difilcudade\n\n\n");
    switch(sel){
      case 2:
        printf("   \332\304\304\304\304\304\304\304\304\304\304\304\304\304\304\277\n");
        printf("   \263    F\240cil     \263                 M\202dio                       Dif\241cil\n");
        printf("   \300\304\304\304\304\304\304\304\304\304\304\304\304\304\304\331");
        break;
      case 3:
        printf("                               \332\304\304\304\304\304\304\304\304\304\304\304\304\304\304\277\n");
        printf ("        F\240cil                  \263    M\202dio     \263                 Dif\241cil\n");
        printf("                               \300\304\304\304\304\304\304\304\304\304\304\304\304\304\304\331           ");
        break;
      case 4:
        printf("                                                           \332\304\304\304\304\304\304\304\304\304\304\304\304\304\304\277\n");
        printf ("        F\240cil                       M\202dio                  \263    Dif\241cil   \263\n");
        printf("                                                           \300\304\304\304\304\304\304\304\304\304\304\304\304\304\304\331");
    }

    switch (converter_entrada()){
      case ('A'):
        sel -= 1;
        break;
      case ('D'):
        sel += 1;
        break;
      case ('\15'):
        return(sel);
        break;
    }
    if (sel == 5)
      sel = 2;
    if (sel == 1)
      sel = 4;
    }while(1);
}

 void escolha_nome(int jogo){
  int sel=0,cont=0,i;
  char a;

  for(i=0;i<=10;i++){
    nome1[i]=' ';
    nome2[i]=' ';
  }

  do{
    system("cls");
    if(jogo==1)
      printf("\n\n   Escolha o nome dos jogadores");
    else
      printf("\n\n   Escolha o seu nome");
    printf("\n\n\n         Jogador 1");if(jogo==1) printf("                       Jogador 2\n");else printf("\n");
    printf("   \332\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\277");if(jogo==1) printf("           \332\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\277\n");else printf("\n");
    printf("   \263  ");for(i=0;i<=14;i++) printf("%c",nome1[i]);printf("  \263");    if(jogo==1){printf("           \263  ");for(i=0;i<=14;i++) printf("%c",nome2[i]);printf("  \263\n");}else printf("\n");
    printf("   \300\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\331");if(jogo==1) printf("           \300\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\331\n");
    //Ler entrada do teclado
    a=getch();
    if(cont<14)
      if(((a>64)&&(a<91))||((a>96)&&(a<123))){
        if(sel==0)
          nome1[cont]=a;
        else
          nome2[cont]=a;
        cont++;
      }
    if(cont>0){
      //Interpretar Enter
      if(a=='\15'){
        if(sel)
          nome2[cont]='\0';
        else
          nome1[cont]='\0';
        sel++;
        cont=0;
      }
      //Interpretar Backspace
      if(a=='\10'){
        cont--;
        if(sel==0)
          nome1[cont]=' ';
        else
          nome2[cont]=' ';
      }
    }

  }while ((sel < 1)||((sel<2)&&(jogo==1)));

  if(jogo>1){
    strcpy(nome2,"Computador");
  }

}

void escolha_simb(jogador *jog1, jogador *jog2 )
{
  int sel=1,go=1;

  do{
    system("cls");
    printf("\n\n       Escolha o s\241mbolo com o qual %s vai jogar:\n\n\n",nome1);
    if(sel>0){
      printf("       \332\304\304\304\304\304\304\304\277\n");
      printf("       \263 #   # \263              #####  \n");
      printf("       \263  # #  \263              #   #  \n");
      printf("       \263   #   \263              #   #  \n");
      printf("       \263  # #  \263              #   #  \n");
      printf("       \263 #   # \263              #####  \n");
      printf("       \300\304\304\304\304\304\304\304\331");
    }
    else{
      printf("                            \332\304\304\304\304\304\304\304\277\n");
      printf("         #   #              \263 ##### \263\n");
      printf("          # #               \263 #   # \263\n");
      printf("           #                \263 #   # \263\n");
      printf("          # #               \263 #   # \263\n");
      printf("         #   #              \263 ##### \263\n");
      printf("                            \300\304\304\304\304\304\304\304\331\n");
    }
    switch (converter_entrada()){
      case ('A'):
      case ('D'):
        sel *= -1;
        break;
      case ('\15'):
        go = 10;
        break;
    }
  }while (go != 10);
  if (sel == 1){
    jog1->simb = 1;
    *jog2 = 4;
  }
  else{
    *jog1 = 4;
    *jog2 = 1;
  }
}
*/
