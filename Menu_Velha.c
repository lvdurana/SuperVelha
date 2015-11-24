#include "FGerais.c"

#define POS_VELHA_X 28
#define POS_VELHA_Y 1
#define COR_FUNDO PRETO_A
#define COR_TEXTO BRANCO_B
#define COR_MENU PRETO_B
#define COR_OPCOES_MENU AZUL_A
#define COR_CURSOR_REPLAY BRANCO_B


typedef struct controle {
  int num_max;
  int num_c_max;
}controle;

typedef struct jogador {
  char tipo; //0=jogador/1,2,3=computador f,m,d/4=replay
  char num; //1,4
  char simb; //0=o/1=x
  char nome[12];
} jogador;

typedef struct partida {
 int partida;
 char JogVelha[3][3];
 char resultado; //Primeiros 4 bits=jog_inicial, últimos 4 bits=vencedor(ou 2 se foi empate)
 char turno[9];

} partida;

typedef struct mapa {
  char c;
  char cor;
} inter;

typedef struct menu{
  char cur;
  char tam;
  char opcoes[3][18];
  char saida[3];
}menu;

typedef struct campo {
  inter mapa[23][23];
  char cur;
  char mat[3][3];
  char turno;
  char jog_atual; //0 e 1
  partida rec;
  jogador jog[2];
} campo;

//Definir símbolos
unsigned char simb_anim[][5][5]={
    {{0,1,2,3,0},{3,255,255,255,1},{2,255,255,255,2},{1,255,255,255,3},{0,3,2,1,0}},
    {{5,255,255,255,0},{255,6,255,1,255},{255,255,2,255,255},{255,3,255,8,255},{4,255,255,255,9}},
    {{255,4,255,4,255},{3,255,5,255,3},{2,255,255,255,2},{255,1,255,1,255},{255,255,0,255,255}},
    {{255,255,2,255,255},{255,2,1,2,255},{2,1,0,1,2},{255,2,1,2,255},{255,255,2,255,255}},
    {{255,6,5,4,0},{255,7,255,255,1},{255,8,255,2,2},{9,9,255,3,3},{10,10,255,255,255}},
    {{255,5,4,5,255},{5,4,3,4,5},{4,3,2,3,4},{255,255,1,255,255},{255,255,0,255,255}}

};
char simb_anim_tam[]={4,10,6,3,11,6};
char simb_cor[]={AZUL_B,VERMELHO_B,ROSA_B,AMARELO_B,CIANO_B,VERDE_B};
char simb_char[]={'o','x','\3','\4','\16','\5'};

char menu_inic[][18]={"Novo jogo","Replay","Sair"};
char menu_tipo_jogo[][18]={"Partida R\240pida","Campeonato","Voltar"};


//Definir músicas



int registrar_partida(partida *p, char *string){
  FILE *f;
  if((f=fopen(string,"a"))==NULL)
    return 0;
  fwrite(p,sizeof(partida),1,f);
  fclose(f);
  return 1;
}

int registrar_cabecalho(campo *p, int num_rodadas, int posicao){
  FILE *f;
  if((f=fopen("reg.txt","a"))==NULL)
    return 0;
  fprintf(f,"%s;%d;%s;%d;%d;%d\n",p->jog[0].nome,p->jog[0].simb,p->jog[1].nome,p->jog[1].simb,num_rodadas,posicao);
  fclose(f);
  return 1;

}

void cursor_menu(int x_pos, int y_pos, int x_tam, int y_tam, char modo){
  char i,j=x_pos+x_tam-1;
  switch(modo){
    case 0:
      gotoxy(x_pos,y_pos);
      for(i=0;i<x_tam;i++)
        putc(' ',stdout);
      for(i=1;i<y_tam-1;i++){
        gotoxy(x_pos,y_pos+i);
        putc(' ',stdout);
        gotoxy(j,y_pos+i);
        putc(' ',stdout);
      }
      gotoxy(x_pos,y_pos+y_tam-1);
      for(i=0;i<x_tam;i++)
        putc(' ',stdout);
      break;
    case 1:
      gotoxy(x_pos,y_pos);
      putc('\332',stdout);
      for(i=1;i<x_tam-1;i++)
        putc('\304',stdout);
      putc('\277',stdout);
      for(i=1;i<y_tam-1;i++){
        gotoxy(x_pos,y_pos+i);
        putc('\263',stdout);
        gotoxy(j,y_pos+i);
        putc('\263',stdout);
      }
      gotoxy(x_pos,y_pos+y_tam-1);
      putc('\300',stdout);
      for(i=1;i<x_tam-1;i++)
        putc('\304',stdout);
      putc('\331',stdout);
      gotoxy(0,0);
      break;
  }
}

void menu_base(){
  char i=0;
  definir_cor(COR_MENU,BRANCO_B);
  for(i=0;i<=24;i++){
    gotoxy(60,i);
    puts("                    ");
  }
  cursor_menu(60,0,20,25,1);
  gotoxy(60,5);
  puts("\303\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\264");
  gotoxy(65,2);
  definir_cor(COR_MENU,VERMELHO_A);
  puts("Super");
  gotoxy(70,3);
  definir_cor(COR_MENU,AZUL_B);
  puts("Velha");

}

int menu_inicial(){
  char i,cur=0;

  menu_base();
  //Desenhar menu
  definir_cor(CIANO_A,BRANCO_B);
  gotoxy(61,7);
  printf("%18s",menu_inic[0]);
  gotoxy(61,8);
  definir_cor(COR_MENU,AZUL_A);
  printf("%18s",menu_inic[1]);
  gotoxy(61,9);
  printf("%18s",menu_inic[2]);

  //Receber entrada do teclado
  for(;;){
    switch(converter_entrada()){
      case 'W':
        if(cur>0){
          gotoxy(61,7+cur);
          definir_cor(COR_MENU,AZUL_A);
          printf("%18s",menu_inic[cur]);
          cur--;
          gotoxy(61,7+cur);
          definir_cor(CIANO_A,BRANCO_B);
          printf("%18s",menu_inic[cur]);
        }
        break;
      case 'S':
        if(cur<2){
          gotoxy(61,7+cur);
          definir_cor(COR_MENU,AZUL_A);
          printf("%18s",menu_inic[cur]);
          cur++;
          gotoxy(61,7+cur);
          definir_cor(CIANO_A,BRANCO_B);
          printf("%18s",menu_inic[cur]);
        }
        break;
      case '\15':
        definir_cor(COR_FUNDO,COR_TEXTO) ;
        return cur;
    }


  }
}

int menu_t_jogo(){
  char i,cur=0;

  //Desenhar menu
  menu_base();

  definir_cor(CIANO_A,BRANCO_B);
  gotoxy(61,7);
  printf("%18s",menu_tipo_jogo[0]);
  gotoxy(61,8);
  definir_cor(COR_MENU,AZUL_A);
  printf("%18s",menu_tipo_jogo[1]);

  //Receber entrada do teclado
  for(;;){
    switch(converter_entrada()){
      case 'W':
        if(cur>0){
          gotoxy(61,7+cur);
          definir_cor(COR_MENU,AZUL_A);
          printf("%18s",menu_tipo_jogo[cur]);
          cur--;
          gotoxy(61,7+cur);
          definir_cor(CIANO_A,BRANCO_B);
          printf("%18s",menu_tipo_jogo[cur]);
        }
        break;
      case 'S':
        if(cur<2){
          gotoxy(61,7+cur);
          definir_cor(COR_MENU,AZUL_A);
          printf("%18s",menu_tipo_jogo[cur]);
          cur++;
          gotoxy(61,7+cur);
          definir_cor(CIANO_A,BRANCO_B);
          printf("%18s",menu_tipo_jogo[cur]);
        }
        break;
      case '\15':
        definir_cor(COR_FUNDO,COR_TEXTO) ;
        return cur;
      case '\33':
        return 2;
    }


  }
}

int desenhar_dados_arq(int ind, int ind_max){
  FILE *f, *g;
  char nome[2][12],i,j,k,a,b;
  int simb[2],num_jogos=0,posicao;
  partida part;

  if((f=fopen("reg.dat","rb"))==NULL)
    return 0;
  if((g=fopen("reg.txt","r"))==NULL){
    fclose(f);
    return 0;
  }
  //Verificar índice
  for(i=0;i<ind;i++){
    fscanf(g,"%[^;];%d;%[^;];%d;%d;%d\n",nome[0],&simb[0],nome[1],&simb[1],&num_jogos,&posicao);
    fscanf(g,"%[^;];%d;%[^;];%d;%d;%d\n",nome[0],&simb[0],nome[1],&simb[1],&num_jogos,&posicao);
  }
  menu_base();
  definir_cor(COR_MENU,BRANCO_B);
  for(i=0;i<2;i++){
    if(feof(f)||feof(g))
      break;
    fscanf(g,"%[^;];%d;%[^;];%d;%d;%d\n",nome[0],&simb[0],nome[1],&simb[1],&num_jogos,&posicao);
    fseek(f,posicao*sizeof(partida),SEEK_SET);
    if(num_jogos>1){
      gotoxy(62,8+i*7);
      definir_cor(COR_MENU,BRANCO_B);
      printf("  Campeonato(%d) ",num_jogos);
      gotoxy(62,9+i*7);
      definir_cor(COR_MENU,simb_cor[simb[0]]);
      printf(" %-15s",nome[0]);
      gotoxy(62,11+i*7);
      definir_cor(COR_MENU,simb_cor[simb[1]]);
      printf("%15s ",nome[1]);
      definir_cor(COR_MENU,BRANCO_B);
      gotoxy(62,10+i*7);
      printf("       vs       ");
      gotoxy(62,12+i*7);
      printf("data");
    }
    else{
      fread(&part,sizeof(partida),1,f);
      gotoxy(62,8+i*7);
      printf(" \263 \263 ");
      definir_cor(COR_MENU,simb_cor[simb[0]]);
      printf("%11s",nome[0]);
      gotoxy(62,9+i*7);
      definir_cor(COR_MENU,BRANCO_B);
      printf("\304\305\304\305\304");
      definir_cor(COR_MENU,simb_cor[simb[1]]);
      printf("%11s",nome[1]);
      gotoxy(62,10+i*7);
      definir_cor(COR_MENU,BRANCO_B);
      printf(" \263 \263 %d",simb[0]);
      gotoxy(62,11+i*7);
      printf("\304\305\304\305\304%d",simb[1]);
      gotoxy(62,12+i*7);
      printf(" \263 \263 %d",num_jogos);
      //Desenhar símbolos
      j=0;
      k=part.resultado>>4;
      while(j<9&&part.turno[j]!=9){
        b=part.turno[j]/3;
        a=part.turno[j]%3;
        gotoxy(62+a*2,8+i*7+b*2);
        definir_cor(COR_MENU,simb_cor[simb[k]]);
        printf("%c",simb_char[simb[k]]);
        k^=1;
        j++;
      }
    }
  }
  fclose(f);
  fclose(g);
  gotoxy(67,23);
  definir_cor(COR_MENU,BRANCO_B);
  printf("Pag %d/%d",ind,ind_max);

  return 1;
}

int menu_replay(int num_max){
  char cur=0,ind=0,ind_max;

  ind_max=(num_max-1)/2;
  if(!desenhar_dados_arq(ind,ind_max))
    return -1;
  //gotoxy(61,6);
  //puts(" Partidas salvas: ");
  cursor_menu(61,7,18,7,1);
  //Movimentação do cursor
  for(;;){
    switch(converter_entrada()){
      case 'W':
        if(cur>0){
          definir_cor(COR_MENU,COR_CURSOR_REPLAY);
          cursor_menu(61,7+cur*7,18,7,0);
          cur--;
          cursor_menu(61,7+cur*7,18,7,1);
        }
        else
          if(ind>0){
            ind--;
            cur=1;
            desenhar_dados_arq(ind,ind_max);
            definir_cor(COR_MENU,COR_CURSOR_REPLAY);
            cursor_menu(61,7+cur*7,18,7,1);
          }
        break;
      case 'S':
        if(cur<1&&cur+ind*2<num_max-1){
          definir_cor(COR_MENU,COR_CURSOR_REPLAY);
          cursor_menu(61,7+cur*7,18,7,0);
          cur++;
          cursor_menu(61,7+cur*7,18,7,1);
        }
        else
          if(ind<ind_max){
            ind++;
            cur=0;
            desenhar_dados_arq(ind,ind_max);
            definir_cor(COR_MENU,COR_CURSOR_REPLAY);
            cursor_menu(61,7+cur*7,18,7,1);
          }
        break;
      case '\15':
        definir_cor(COR_FUNDO,COR_TEXTO);
        return ind*2+cur;
      case '\33':
        return -1;
    }


  }


}

int menu_campeonato(){
  char cur=3;
  menu_base();
  definir_cor(COR_MENU,BRANCO_B);
  gotoxy(61,7);
  puts(" Quantas partidas ");
  gotoxy(61,8);
  puts(" v\306o ser jogadas? ");
  gotoxy(61,10);
  puts("       \332\304\304\277");
  gotoxy(61,11);
  puts("       \263 3\263\31");
  gotoxy(61,12);
  puts("       \300\304\304\331");

  //Entrada do teclado
  for(;;){
    switch(converter_entrada()){
      case 'W':
        if(cur>3){
          gotoxy(69,11);
          cur-=2;
          if(cur>3)
            printf("%2d\263\22",cur);
          else
            printf("%2d\263\31",cur);
        }

        break;
      case 'S':
        if(cur<11){
          gotoxy(69,11);
          cur+=2;
          if(cur<11)
            printf("%2d\263\22",cur);
          else
            printf("%2d\263\30",cur);
        }
        break;
      case '\15':
        return cur;
    }
  }
}

int determinar_jogadores(jogador *j,char num){
  char i,cur=0,cont=0;
  char msg[3][8]={" F\240cil "," M\202dio ","Dif\241cil"};

  menu_base();
  definir_cor(COR_MENU,BRANCO_B);
  gotoxy(61,6);
  printf("    Jogador %d",num>5?1:2);
  gotoxy(61,9);
  puts("  Insira o Nome");
  gotoxy(61,10);
  puts(" \332\304\304\304\304\304\304\304\304\304\304\304\304\304\277");
  gotoxy(61,11);
  puts(" \263             \263");
  gotoxy(61,12);
  puts(" \300\304\304\304\304\304\304\304\304\304\304\304\304\304\331");
  gotoxy(61,14);
  puts("  Usu\240rio");
  gotoxy(61,17);
  puts(" Computador");
  definir_cor(COR_MENU,BRANCO_A);
  gotoxy(71,19);
  puts(" F\240cil ");
  //Escrever símbolos
  for(i=0;i<6;i++){
    gotoxy(62+i*3,22);
    if(i==num)
      definir_cor(COR_MENU,BRANCO_A);
    else
      definir_cor(COR_MENU,simb_cor[i]);
    printf("%c",simb_char[i]);
  }
  definir_cor(COR_MENU,BRANCO_B);
  while(entrada(12,j->nome,&cur,1)){
    gotoxy(64,11);
    printf("%s",j->nome);
  }
  cur=0;
  gotoxy(61,8);
  puts(" Escolha quem vai ");
  gotoxy(61,9);
  puts("   controlar(\22)   ");
  cursor_menu(61,13,12,3,1);
  while(!cont){
    switch(converter_entrada()){
      case 'W':
        if(cur){
          cursor_menu(61,13+cur*3,12,3,0);
          cur--;
          cursor_menu(61,13+cur*3,12,3,1);
        }
        break;
      case 'S':
        if(!cur){
          cursor_menu(61,13+cur*3,12,3,0);
          cur++;
          cursor_menu(61,13+cur*3,12,3,1);
        }
        break;
      case '\15':
        if(cur){
          cur=0;
          gotoxy(61,8);
          puts("     Escolha a    ");
          gotoxy(61,9);
          puts("   dificuldade(\35) ");
          gotoxy(71,19);
          puts(" F\240cil ");
          while(!cont){
            switch(converter_entrada()){
              case 'A':
                if(cur){
                  cur--;
                  gotoxy(71,19);
                  printf("%s",msg[cur]);
                }
                break;
              case 'D':
                if(cur<2){
                  cur++;
                  gotoxy(71,19);
                  printf("%s",msg[cur]);
                }
                break;
              case '\15':
                j->tipo=cur+1;
                cont=1;
                break;
            }
          }
        }
        else
          j->tipo=0;
        cont=1;
    }
  }
  cur=0;
  cont=0;
  gotoxy(61,8);
  puts("     Escolha o    ");
  gotoxy(61,9);
  puts("     s\241mbolo(\35)   ");
  cursor_menu(61,21,3,3,1);
  while(!cont){
    switch(converter_entrada()){
      case 'A':
        if(cur){
          cursor_menu(61+cur*3,21,3,3,0);
          cur--;
          cursor_menu(61+cur*3,21,3,3,1);
        }
        break;
      case 'D':
        if(cur<5){
          cursor_menu(61+cur*3,21,3,3,0);
          cur++;
          cursor_menu(61+cur*3,21,3,3,1);
        }
        break;
      case '\15':
        if(cur!=num){
          j->simb=cur;
          cont=1;
        }
        break;
    }


  }

}



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
