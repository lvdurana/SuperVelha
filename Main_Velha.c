 #include <windows.h>
 #include "IA.c"

/*
Atualizar funções de cursor
*/

int velha();
void inicializa_velha(campo *p);
int verifica_ganhador(campo *p);
int mover_cursor(campo *p);


int decidir_jogada(campo *p){
  switch(p->jog[p->jog_atual].tipo){
    case 0:
      return mover_cursor(p);
    case 1:
    case 2:
    case 3:
      return IA(p);
    case 4:
      //Implementar Replay
      break;
  }

}

void inicializa_velha(campo *p)
{
  char a;
  for(a=0;a<9;a++)
    p->mat[a/3][a%3]=0;
  p->turno=0;
  p->cur=4;
}

int verifica_ganhador(campo *p)
{
  int i,j,a=0,b=0,c=0,d=0;
  for(i=0;i<=2;i++){
    for(j=0;j<=2;j++){
        a+=p->mat[i][j];
        b+=p->mat[j][i];
    }
    if((a==(p->jog[p->jog_atual].num*3))||(b==(p->jog[p->jog_atual].num*3)))
      return 1;
    a=b=0;
      c+=p->mat[i][i];
      d+=p->mat[i][2-i];
  }
  if((c==(p->jog[p->jog_atual].num*3))||(d==(p->jog[p->jog_atual].num*3)))
    return 1;
  return 0;
}

int mover_cursor(campo *p)
{
  //Interpretação da entrada do teclado
  for(;;){
    //desenhar_tela(p);
    switch(converter_entrada()){
      case 'A':
        if((p->cur%3)>0){
          cursor(p,0);
          p->cur-=1;
          cursor(p,1);
        }
        break;
      case 'S':
        if((p->cur/3)<2){
          cursor(p,0);
          p->cur+=3;
          cursor(p,1);
        }
        break;
      case 'D':
        if((p->cur%3)<2){
          cursor(p,0);
          p->cur+=1;
          cursor(p,1);
        }
        break;
      case 'W':
        if((p->cur/3)>0){
          cursor(p,0);
          p->cur-=3;
          cursor(p,1);
        }
        break;
      case 'P':
        final_do_jogo(1);
        break;
      case '\15':
        if(p->mat[p->cur/3][p->cur%3]==0){
          return p->cur;
        }
        break;
      case '\33':
        switch(menu_saida()){
          case 0:
            break;
          case 1:
            return 9;
          case 2:
            exit;
        }
      break;
    }
  }
}

int loop_velha(campo *p){
  char *c=p->mat;
  while(p->turno<9){
    *(c+atualizar_xo(p,decidir_jogada(p))) = p->jog[p->jog_atual].num;
    if(verifica_ganhador(p))
      break;
    p->turno++;
    p->jog_atual^=1;
  }

}

int velha() {
  int i;
  campo vl;

  vl.jog_atual=0;
  vl.jog[0].nome[0]='L';
  vl.jog[0].nome[1]='\0';
  vl.jog[0].num=1;
  vl.jog[0].simb=4;
  vl.jog[0].tipo=0;
  vl.jog[1].nome[0]='M';
  vl.jog[1].nome[1]='\0';
  vl.jog[1].num=4;
  vl.jog[1].simb=3;
  vl.jog[1].tipo=3;
  inicializa_velha(&vl);
  inicializar_mapa(&vl);
  //Desenhar tela
  desenhar_tela(&vl);
  //cursor(&vl,1);
  loop_velha(&vl);
  //final_do_jogo(vit);
  return 0;
}

void main() {
  int i=0;
  //for(i=200;i<=800;i+=10)
    //Beep(i,200);

  printf(" ####\n #  #\n # ##\n## ##\n##   \n\n");
  printf(" ### \n#####\n#####\n  #  \n  #  \n\n\16");
  Beep(NOTA_F3,75);
  Beep(NOTA_F3,75);
  Beep(NOTA_F3,75);
  Beep(NOTA_F3,500);
  Beep(NOTA_CS3,375);
  Beep(NOTA_DS3,375);
  Beep(NOTA_F3,250);
  //Sleep(100);
  Beep(NOTA_DS3,75);
  Beep(NOTA_F3,750);
  while(i==0){
    srand (time(NULL));
    i=velha();
  }
}
