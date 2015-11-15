#include "FGerais.c"

char mat[3][3];
char mapa[23][23];
char nome1[15],nome2[15];
int turno=0,vit=0;

int menu()
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

void escolha_simb(char *jog1, char *jog2 )
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
    *jog1 = 1;
    *jog2 = 4;
  }
  else{
    *jog1 = 4;
    *jog2 = 1;
  }
}
