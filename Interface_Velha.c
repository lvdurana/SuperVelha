#include "Menu_Velha.c"

void inicializar_mapa(campo *p);
void desenhar_tela(campo *p, char pos_x, char pos_y, char partida);
void desenhar_info_tela(campo *p, char pos_x, char pos_y, char partida);
int atualizar_xo(campo *p, char pos, int pos_x, int pos_y);
void cursor(campo *p, char modo);
int tela_vitoria(campo *p, char resultado, char modo);


void inicializar_mapa(campo *p) {
  int a, b;

  //Inicializar mapa
  for(a=0;a<23;a++){
    for(b=0;b<23;b++){
      p->mapa[a][b].cor=BRANCO_B;
      if((b==7)||(b==15)||(a==7)||(a==15))
        p->mapa[a][b].c='\333';
      else
        p->mapa[a][b].c=' ';
    }
  }
}


void desenhar_tela(campo *p, char pos_x, char pos_y, char partida) {
  int a,b;
  char c=0;

  definir_cor(COR_FUNDO,COR_TEXTO);
  //Desenhar Caixa
  cursor_menu(pos_x,pos_y,60,25,1);
  //Desenhar Mapa
  for(a=0;a<23;a++){
    gotoxy(pos_x+18,pos_y+a+1);
    for(b=0;b<23;b++){
      if(p->mapa[a][b].cor!=c)
        definir_cor(COR_FUNDO,p->mapa[a][b].cor);
      putc(p->mapa[a][b].c,stdout);
      c=p->mapa[a][b].cor;

    }
    putc('\n',stdout);
  }

}

void desenhar_info_tela(campo *p, char pos_x, char pos_y, char partida){

  definir_cor(COR_FUNDO,COR_TEXTO);

    //Desenhar cursor no jogador atual
    cursor_menu(pos_x+3,pos_y+11,13,3,0);
    cursor_menu(pos_x+44,pos_y+11,13,3,0);
    cursor_menu(pos_x+3+(p->jog_atual*41),pos_y+11,13,3,1);

    //Escrever nomes dos jogadores
    gotoxy(pos_x+4,pos_y+12);
    printf("%11s",p->jog[0].nome);
    gotoxy(pos_x+45,pos_y+12);
    printf("%-11s",p->jog[1].nome);

    //Escrever símbolos
    gotoxy(pos_x+45+strlen(p->jog[1].nome),pos_y+12);
    definir_cor(COR_FUNDO,simb_cor[p->jog[1].simb]);
    putc(simb_char[p->jog[1].simb],stdout);
    gotoxy(pos_x+4+10-strlen(p->jog[0].nome),pos_y+12);
    definir_cor(COR_FUNDO,simb_cor[p->jog[0].simb]);
    putc(simb_char[p->jog[0].simb],stdout);

    //Limpar mensagens
    gotoxy(pos_x+4,pos_y+14);
    puts("            ");
    gotoxy(pos_x+45,pos_y+14);
    puts("            ");

  definir_cor(COR_FUNDO,COR_TEXTO);
  if(p->num_jogos>1){
    gotoxy(pos_x+2,pos_y+20);
    puts("Placar");
    gotoxy(pos_x+2,pos_y+22);
    printf("%2d x %2d",p->jog[0].placar,p->jog[1].placar);
    gotoxy(pos_x+44,pos_y+23);
    printf("Partida %d de %d",p->num_jogos-p->jog_faltando+1,p->num_jogos);
  }

}


int atualizar_xo(campo *p, char pos, int pos_x, int pos_y)
{
  char a,b,i,j,k;
  a=pos/3*8+1;
  b=pos%3*8+1;
  for(i=0;i<=simb_anim_tam[p->jog[p->jog_atual].simb];i++){
    for(j=0;j<5;j++){
      for(k=0;k<5;k++){
        if(simb_anim[p->jog[p->jog_atual].simb][k][j]==i){
          p->mapa[a+k][b+j].c='#';
          p->mapa[a+k][b+j].cor=simb_cor[p->jog[p->jog_atual].simb];
          gotoxy(pos_x+b+j,pos_y+a+k);
          definir_cor(COR_FUNDO,simb_cor[p->jog[p->jog_atual].simb]);
          printf("#");
          definir_cor(COR_FUNDO,COR_TEXTO);
        }
      }
    }
    Sleep(50);
  }
  return pos;
}


void cursor(campo *p, char modo) {
  int a, b, i;
  a=p->cur/3*8;
  b=p->cur%3*8;
  if(modo){
    //Atualizar mapa
    p->mapa[a][b].c='\332';
    p->mapa[a][6+b].c='\277';
    p->mapa[6+a][b].c='\300';
    p->mapa[6+a][b+6].c='\331';
    gotoxy(POS_VELHA_X+b,POS_VELHA_Y+a);printf("\332\304\304\304\304\304\277");
    gotoxy(POS_VELHA_X+b,POS_VELHA_Y+a+6);printf("\300\304\304\304\304\304\331");
    for(i=1;i<=5;i++){
      p->mapa[a+i][b].c='\263';
      p->mapa[a][b+i].c='\304';
      p->mapa[6+a][b+i].c='\304';
      p->mapa[a+i][b+6].c='\263';
      gotoxy(POS_VELHA_X+b,POS_VELHA_Y+a+i);printf("\263");
      gotoxy(POS_VELHA_X+b+i,POS_VELHA_Y+a);printf("\304");
      gotoxy(POS_VELHA_X+b+i,POS_VELHA_Y+a+6);printf("\304");
      gotoxy(POS_VELHA_X+b+6,POS_VELHA_Y+a+i);printf("\263");
    }

  }
  else{
    p->mapa[a][b].c=' ';
    p->mapa[a][6+b].c=' ';
    p->mapa[6+a][b].c=' ';
    p->mapa[6+a][b+6].c=' ';
    gotoxy(POS_VELHA_X+b,POS_VELHA_Y+a);printf("       ");
    gotoxy(POS_VELHA_X+b,POS_VELHA_Y+a+6);printf("       ");
    for(i=1;i<=5;i++){
      p->mapa[a+i][b].c=' ';
      p->mapa[a][b+i].c=' ';
      p->mapa[6+a][b+i].c=' ';
      p->mapa[a+i][b+6].c=' ';
      gotoxy(POS_VELHA_X+b,POS_VELHA_Y+a+i);printf(" ");
      gotoxy(POS_VELHA_X+b+i,POS_VELHA_Y+a);printf(" ");
      gotoxy(POS_VELHA_X+b+i,POS_VELHA_Y+a+6);printf(" ");
      gotoxy(POS_VELHA_X+b+6,POS_VELHA_Y+a+i);printf(" ");
    }
  }
}

int tela_vitoria(campo *p, char resultado, char modo)
{
  system("cls");
  desenhar_tela(p,0,0,0);
  menu_base();
  definir_cor(COR_MENU,BRANCO_B);
  if(modo){
    gotoxy(61,7);
    if(resultado<2){
      puts("     Vit\242ria!    ");
      gotoxy(70-(strlen(p->jog[resultado].nome)/2),9);
      definir_cor(COR_MENU,simb_cor[p->jog[resultado].simb]);
      printf("%s",p->jog[resultado].nome);
      gotoxy(61,10);
      definir_cor(COR_MENU,BRANCO_B);
      puts("      venceu o    ");
      gotoxy(61,11);
      puts("    campeonato!!  ");
    }
    else{
      puts("      Empate     ");
      gotoxy(61,9);
      puts("   O campeonato   ");
      gotoxy(61,10);
      puts("   acabou em um   ");
      gotoxy(61,11);
      puts("      empate.     ");
    }
    gotoxy(61,13);
    puts("   Placar final:  ");
    gotoxy(68,14);
    definir_cor(COR_MENU,simb_cor[p->jog[0].simb]);
    printf("%d",p->jog[0].placar);
    definir_cor(COR_MENU,BRANCO_B);
    printf(" x ");
    definir_cor(COR_MENU,simb_cor[p->jog[1].simb]);
    printf("%d",p->jog[1].placar);
    gotoxy(61,21);
    definir_cor(COR_MENU,BRANCO_B);
    puts(" Aperte qualquer  ");
    gotoxy(61,22);
    puts("    bot\306o para    ");
    gotoxy(61,23);
    puts("    continuar.    ");


  }
  else{

    gotoxy(61,7);
    if(resultado<2){
      puts("     Vit\242ria!    ");
      gotoxy(70-(strlen(p->jog[resultado].nome)/2),9);
      definir_cor(COR_MENU,simb_cor[p->jog[resultado].simb]);
      printf("%s",p->jog[resultado].nome);
      gotoxy(61,10);
      definir_cor(COR_MENU,BRANCO_B);
      puts(" venceu a partida!");
    }
    else
    puts("      Empate     ");
    gotoxy(61,21);
    puts(" Aperte qualquer  ");
    gotoxy(61,22);
    puts("    bot\306o para    ");
    gotoxy(61,23);
    puts("    continuar.    ");
  }
  gotoxy(0,0);
  getch();
}
