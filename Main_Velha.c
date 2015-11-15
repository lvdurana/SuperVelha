 #include <windows.h>
 #include "IA.c"

int velha();
void inicializa_velha();
int jogada_usuario(int lin, int col, char jog);
void jogada_computador(char jog, int nivel);
int verifica_ganhador(char jog);
int mover_cursor(int *cur, int nivel, int simb);


void main() {
  int i=0;
  for(i=200;i<=800;i+=10)
    Beep(i,200);
  printf(" # # \n# # #\n#   #\n # # \n  #  \n\n");
  printf("  #  \n # # \n#   #\n # # \n  #  \n");
  Sleep(4000);
  while(i==0){
    srand (time(NULL));
    i=velha();
  }
}

int velha() {
  char jog1, jog2;
  int i, cur=4, nivel;

  nivel=menu();
  escolha_simb(&jog1,&jog2);
  inicializa_velha();
  inicializar_mapa();
  //Desenhar cursor
  cursor(cur,1);

  if(1)//rand()%2)
  while(1){
    turno=0;
    desenhar_tela(nivel,jog1);
    i=mover_cursor(&cur, nivel, jog1);
    if(i)
      return 0;
    if(verifica_ganhador(jog1))
      vit=10;
    if(vit>=9)
      break;

    turno=1;
    if(nivel==1){
      i=mover_cursor(&cur, nivel,jog2);
      if(i)
        return 0;
    }
    else{
      jogada_computador(jog2,nivel);
      vit++;
    }
    if(verifica_ganhador(jog2))
      vit=20;
    if(vit>=9)
      break;

  }

  else
  while(1){
    turno=1;
    if(nivel==1){
      i=mover_cursor(&cur, nivel,jog2);
      if(i)
        return 0;
    }
    else{
      jogada_computador(jog2,nivel);
      vit++;
    }
    if(verifica_ganhador(jog2))
      vit=20;
    if(vit>=9)
      break;

    turno=0;
    desenhar_tela(nivel,jog1);
    i=mover_cursor(&cur, nivel, jog1);
    if(i)
      return 0;
    if(verifica_ganhador(jog1))
      vit=10;
    if(vit>=9)
      break;
  }
  final_do_jogo(vit);
  return 0;
}

void inicializa_velha()
{
  char a;
  for(a=0;a<9;a++)
    mat[a/3][a%3]=0;
  vit=0;
}

int jogada_usuario(int lin, int col, char jog)
{
  if((col<0)||(col>2)||(lin<0)||(lin>2))
    return 1;
  if(mat[col][lin]==0){
    mat[col][lin]=jog;
    return 0;
  }
  return 2;
}

void jogada_computador(char jog, int nivel)
{
  int a,b;
  desenhar_tela(nivel,jog);
  switch(nivel){
    case 4:
      a=AI(jog,1);
      mat[a/3][a%3]=jog;
      printf("\n                                 Pensando...");
      Sleep(2000);
      atualizar_xo(a,jog,nivel);
      break;
    case 3:
      a=AI(jog,0);
      mat[a/3][a%3]=jog;
      printf("\n                                 Pensando...");
      Sleep(2000);
      atualizar_xo(a,jog,nivel);
      break;
    case 2:
      do{
        a=rand()%3;
        b=rand()%3;
        if(mat[a][b]==0){
          mat[a][b]=jog;
          printf("\n                                 Pensando...");
          Sleep(2000);
          atualizar_xo((a*3+b),jog,nivel);
          break;
        }
      }while(1);
      break;
  }

}

int verifica_ganhador(char jog)
{
  int i,j,a=0,b=0,c=0,d=0;
  for(i=0;i<=2;i++){
    for(j=0;j<=2;j++){
        a+=mat[i][j];
        b+=mat[j][i];
    }
    if((a==(jog*3))||(b==(jog*3)))
      return 1;
    a=b=0;
      c+=mat[i][i];
      d+=mat[i][2-i];
  }
  if((c==(jog*3))||(d==(jog*3)))
    return 1;
  return 0;
}

int mover_cursor(int *cur, int nivel, int simb)
{
  //Interpretação da entrada do teclado
  while(1){
    desenhar_tela(nivel,simb);
    switch(converter_entrada()){
      case 'A':
        if((*cur%3)>0){
          cursor(*cur,0);
          *cur-=1;
          cursor(*cur,1);
        }
        break;
      case 'S':
        if((*cur/3)<2){
          cursor(*cur,0);
          *cur+=3;
          cursor(*cur,1);
        }
        break;
      case 'D':
        if((*cur%3)<2){
          cursor(*cur,0);
          *cur+=1;
          cursor(*cur,1);
        }
        break;
      case 'W':
        if((*cur/3)>0){
          cursor(*cur,0);
          *cur-=3;
          cursor(*cur,1);
        }
        break;
      case 'P':
        final_do_jogo(1);
        break;
      case '\15':
        if(jogada_usuario((*cur%3),(*cur/3),simb)==0){
          atualizar_xo(*cur,simb,nivel);
          vit++;
          return 0;
        }
        break;
      case '\33':
        switch(menu_saida()){
          case 0:
            break;
          case 1:
            return 1;
          case 2:
            exit;
        }
      break;
    }
  }
}
