#include <stdlib.h>   //rand()
#include "Menu_Velha.c"



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


void desenhar_tela(campo *p, char pos_x, char pos_y) {
  int a,b;
  char c=0;

  //Limpar tela
  definir_cor(COR_FUNDO,COR_TEXTO);

  //Desenhar Caixa
  cursor_menu(pos_x-18,0,60,25,1);
  //Desenhar Mapa
  for(a=0;a<23;a++){
    gotoxy(pos_x,pos_y+a);
    for(b=0;b<23;b++){
      if(p->mapa[a][b].cor!=c)
        definir_cor(COR_FUNDO,p->mapa[a][b].cor);
      putc(p->mapa[a][b].c,stdout);
      c=p->mapa[a][b].cor;

    }
    putc('\n',stdout);
  }
  //Escrever Nomes
/*  if(!turno) {printf(" \332\304"); for(a=0;a<strlen(nome1);a++) printf("\304");printf("\304\277");for(a=0;a<=20-strlen(nome1);a++) printf(" ");} else printf("                          ");
  for(a=0;a<23;a++) printf("%c",mapa[20][a]);
  if(turno) {for(a=0;a<=24-strlen(nome2);a++) printf(" ");printf("\332\304"); for(a=0;a<strlen(nome2);a++) printf("\304");printf("\304\277\n");}else printf("\n");

  if(!turno) printf(" \263 %s \263",nome1); else printf("   %s  ",nome1); for(a=0;a<=20-strlen(nome1);a++) printf(" ");
  for(a=0;a<23;a++) printf("%c",mapa[21][a]);
  for(a=0;a<=24-strlen(nome2);a++) printf(" ");if(turno) printf("\263 %s \263\n",nome2);else printf("  %s  \n",nome2);

  if(!turno) {printf(" \300\304"); for(a=0;a<strlen(nome1);a++) printf("\304");printf("\304\331");for(a=0;a<=20-strlen(nome1);a++) printf(" ");} else printf("                          ");
  for(a=0;a<23;a++) printf("%c",mapa[22][a]);
  if(turno) {for(a=0;a<=24-strlen(nome2);a++) printf(" ");printf("\300\304"); for(a=0;a<strlen(nome2);a++) printf("\304");printf("\304\331\n");}else printf("\n");
*/
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

int final_do_jogo(int vit)
{
/*  switch(vit){
    case 9:
      printf("\n                                   Empate.\n\n                                       Aperte ENTER para voltar a tela inicial");
      while(getch()!='\15');
      break;
    case 10:
      //printf("\333\333\273   \333\333\273\333\333\273\333\333\333\333\333\333\333\333\273 \333\333\333\333\333\333\273 \333\333\333\333\333\333\273 \333\333\273 \333\333\333\333\333\273 \333\333\273\n\333\333\272   \333\333\272\333\333\272\310\315\315\333\333\311\315\315\274\333\333\311\315\315\315\333\333\273\333\333\311\315\315\333\333\273\333\333\272\333\333\311\315\315\333\333\273\333\333\272\n\333\333\272   \333\333\272\333\333\272   \333\333\272   \333\333\272   \333\333\272\333\333\333\333\333\333\311\274\333\333\272\333\333\333\333\333\333\333\272\333\333\272\n\310\333\333\273 \333\333\311\274\333\333\272   \333\333\272   \333\333\272   \333\333\272\333\333\311\315\315\333\333\273\333\333\272\333\333\311\315\315\333\333\272\310\315\274\n \310\333\333\333\333\311\274 \333\333\272   \333\333\272   \310\333\333\333\333\333\333\311\274\333\333\272  \333\333\272\333\333\272\333\333\272  \333\333\272\333\333\273\n  \310\315\315\315\274  \310\315\274   \310\315\274    \310\315\315\315\315\315\274 \310\315\274  \310\315\274\310\315\274\310\315\274  \310\315\274\310\315\274\n");
      printf("\n          \333\333\273   \333\333\273\333\333\273\333\333\333\333\333\333\333\333\273 \333\333\333\333\333\333\273 \333\333\333\333\333\333\273 \333\333\273 \333\333\333\333\333\273 \333\333\273\n          \333\333\272   \333\333\272\333\333\272\310\315\315\333\333\311\315\315\274\333\333\311\315\315\315\333\333\273\333\333\311\315\315\333\333\273\333\333\272\333\333\311\315\315\333\333\273\333\333\272\n          \333\333\272   \333\333\272\333\333\272   \333\333\272   \333\333\272   \333\333\272\333\333\333\333\333\333\311\274\333\333\272\333\333\333\333\333\333\333\272\333\333\272\n          \310\333\333\273 \333\333\311\274\333\333\272   \333\333\272   \333\333\272   \333\333\272\333\333\311\315\315\333\333\273\333\333\272\333\333\311\315\315\333\333\272\310\315\274\n           \310\333\333\333\333\311\274 \333\333\272   \333\333\272   \310\333\333\333\333\333\333\311\274\333\333\272  \333\333\272\333\333\272\333\333\272  \333\333\272\333\333\273\n            \310\315\315\315\274  \310\315\274   \310\315\274    \310\315\315\315\315\315\274 \310\315\274  \310\315\274\310\315\274\310\315\274  \310\315\274\310\315\274\n");
      printf("\n                      %s ganhou o jogo! Parab\202ns!\n\n                                       Aperte ENTER para voltar a tela inicial",nome1);
      while(getch()!='\15');
      break;
    case 20:
      printf("\n          \333\333\273   \333\333\273\333\333\273\333\333\333\333\333\333\333\333\273 \333\333\333\333\333\333\273 \333\333\333\333\333\333\273 \333\333\273 \333\333\333\333\333\273 \333\333\273\n          \333\333\272   \333\333\272\333\333\272\310\315\315\333\333\311\315\315\274\333\333\311\315\315\315\333\333\273\333\333\311\315\315\333\333\273\333\333\272\333\333\311\315\315\333\333\273\333\333\272\n          \333\333\272   \333\333\272\333\333\272   \333\333\272   \333\333\272   \333\333\272\333\333\333\333\333\333\311\274\333\333\272\333\333\333\333\333\333\333\272\333\333\272\n          \310\333\333\273 \333\333\311\274\333\333\272   \333\333\272   \333\333\272   \333\333\272\333\333\311\315\315\333\333\273\333\333\272\333\333\311\315\315\333\333\272\310\315\274\n           \310\333\333\333\333\311\274 \333\333\272   \333\333\272   \310\333\333\333\333\333\333\311\274\333\333\272  \333\333\272\333\333\272\333\333\272  \333\333\272\333\333\273\n            \310\315\315\315\274  \310\315\274   \310\315\274    \310\315\315\315\315\315\274 \310\315\274  \310\315\274\310\315\274\310\315\274  \310\315\274\310\315\274\n");
      printf("\n                      %s ganhou o jogo! Parab\202ns!\n\n                                       Aperte ENTER para voltar a tela inicial",nome2);
      while(getch()!='\15');
      break;
  }
*/
}
