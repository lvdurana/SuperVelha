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
  for(a=0;a<9;a++){
    p->mat[a/3][a%3]=0;
    p->rec.turno[a]=9;
  }
  p->turno=0;
  p->cur=4;
  p->rec.resultado=0;
}

int tela_replay(int pos_cab, int pos_jog){
  FILE *f, *g;
  partida part;
  campo p;
  char nome[2][12],jogo_atual=0,i,j;
  int simb[2],num_jogos=0,posicao;

  f=fopen("reg.dat","rb");
  g=fopen("reg.txt","r");

  //Inicializar dados
  inicializar_mapa(&p);
  inicializa_velha(&p);
  //Ler dados do cabeçalho
  for(i=0;i<=pos_cab;i++)
    fscanf(g,"%[^;];%d;%[^;];%d;%d;%d\n",nome[0],&simb[0],nome[1],&simb[1],&num_jogos,&posicao);
  fseek(f,pos_jog*sizeof(partida),SEEK_SET);
  fread(&part,sizeof(partida),1,f);
  p.jog_atual=part.resultado>>4;
  strcpy(p.jog[0].nome,nome[0]);
  strcpy(p.jog[1].nome,nome[1]);
  p.jog[0].simb=simb[0];
  p.jog[1].simb=simb[1];
  p.jog[0].num=1;
  p.jog[1].num=4;
  p.jog[0].tipo=(p.jog[1].tipo=4);
  //Replay do jogo
  desenhar_tela(&p,18,1);
  for(i=0;(part.turno[i]!=9&&i<9);i++){
    atualizar_xo(&p,part.turno[i],18,1);
    Sleep(500);
    p.jog_atual^=1;
  }
  fclose(f);
  fclose(g);
  return 1;


}

int escolha_replay(int pos_cab){
  FILE *f;
  char nome[2][12],cur=0,i;
  int simb[2],num_jogos,posicao;

  menu_base();
  f=fopen("reg.txt","r");
  for(i=0;i<=pos_cab;i++)
    fscanf(f,"%[^;];%d;%[^;];%d;%d;%d\n",nome[0],&simb[0],nome[1],&simb[1],&num_jogos,&posicao);
  fclose(f);
  definir_cor(COR_MENU,COR_OPCOES_MENU);
  for(i=1;i<=num_jogos;i++){
    gotoxy(61,6+i);
    sprintf(nome[0],"Partida %d",i);
    printf("%18s",nome[0]);
  }
  for(;;){
    switch(converter_entrada()){
      case 'W':
        if(cur>0){
          gotoxy(61,7+cur);
          definir_cor(COR_MENU,COR_OPCOES_MENU);
          sprintf(nome[0],"Partida %d",cur+1);
          printf("%18s",nome[0]);
          cur--;
          gotoxy(61,7+cur);
          definir_cor(CIANO_A,BRANCO_B);
          sprintf(nome[0],"Partida %d",cur+1);
          printf("%18s",nome[0]);
        }
        break;
      case 'S':
        if(cur<num_jogos-1){
          gotoxy(61,7+cur);
          definir_cor(COR_MENU,COR_OPCOES_MENU);
          sprintf(nome[0],"Partida %d",cur+1);
          printf("%18s",nome[0]);
          cur++;
          gotoxy(61,7+cur);
          definir_cor(CIANO_A,BRANCO_B);
          sprintf(nome[0],"Partida %d",cur+1);
          printf("%18s",nome[0]);
        }
        break;
      case '\15':
        tela_replay(pos_cab,posicao+cur);
        break;
    }
  }
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
    *(c+atualizar_xo(p,(p->rec.turno[p->turno] = decidir_jogada(p)),28,1)) = p->jog[p->jog_atual].num;
    if(verifica_ganhador(p))
      return p->jog_atual;
    p->turno++;
    p->jog_atual^=1;
  }
  return 2;
}

int registrar_dados(campo *p){
  char a,b;
  for(a=0;a<=2;a++)
    for(b=0;b<=2;b++)
      p->rec.JogVelha[a][b]=p->mat[a][b];
  //p->rec.resultado|=p->turno<<4;
  registrar_partida(&(p->rec),"reg.dat");

}

controle carregar_controle(){
  controle c;
  FILE *f;
  if((f=fopen("controle.dat","rb"))==NULL){
    c.num_max=0;
    c.num_c_max=0;
    f=fopen("controle.dat","ab");
    fwrite(&c,sizeof(controle),1,f);
  }
  fread(&c,sizeof(controle),1,f);
  fclose(f);
  return c;


}

int velha() {
  int i,resultado, jog_faltando=1,num_jogos;
  campo vl[8];
  FILE *f;
  controle control;

  //Carregar informações do arquivo de controle
  control=carregar_controle();
  vl[0].jog_atual=0;
  vl[0].rec.partida=1;
  vl[0].jog[0].nome[0]='L';
  vl[0].jog[0].nome[1]='\0';
  vl[0].jog[0].num=1;
  vl[0].jog[0].simb=4;
  vl[0].jog[0].tipo=0;
  vl[0].jog[1].nome[0]='M';
  vl[0].jog[1].nome[1]='\0';
  vl[0].jog[1].num=4;
  vl[0].jog[1].simb=3;
  vl[0].jog[1].tipo=3;
  inicializa_velha(&vl);
  inicializar_mapa(&vl);
  //Desenhar tela
  system("cls");
  desenhar_tela(&vl,18,1);
  //printf("%d",control.num_c_max);
  //Sleep(2000);
  //tela_replay(4,4);
  escolha_replay(4);
  menu_replay(control.num_c_max);
  printf("oi");
  menu_inicial();

  menu_t_jogo();
  system("cls");
  desenhar_tela(&vl,28,1);
  //cursor(&vl,1);

  //Loop principal e registro da jogada inicial e vencedor

  num_jogos=jog_faltando;
  while(jog_faltando){

    inicializa_velha(&vl);
    inicializar_mapa(&vl);
    desenhar_tela(&vl,28,1);
    vl[0].rec.partida=control.num_max+(num_jogos-jog_faltando);
    vl[0].rec.resultado|=(vl[0].jog_atual<<4);
    vl[0].rec.resultado|=loop_velha(&vl);
    registrar_dados(&vl);
    jog_faltando--;
  }
  //final_do_jogo(vit);
  //Atualizar dados
  registrar_cabecalho(&vl,num_jogos,control.num_max);
  control.num_max+=num_jogos;
  control.num_c_max+=1;
  f=fopen("controle.dat","wb");
  fwrite(&control,sizeof(controle),1,f);
  fclose(f);
  return 0;
}

void main() {
  int i=0;
  FILE *f;
  partida p;
  //for(i=200;i<=800;i+=10)
    //Beep(i,200);
  /*f=fopen("reg.dat","rb");
  while(!feof(f)){
    fread(&p,sizeof(partida),1,f);
    printf("|%d|%d|\n",p.partida,p.JogVelha[1][1]);
  }
  fclose(f);
  Sleep(500);
  printf(" ####\n #  #\n # ##\n## ##\n##   \n\n");
  printf(" ### \n#####\n#####\n  #  \n  #  \n\n\16");
  cursor_menu(5,5,3,3,1);

  cursor_menu(5,5,3,3,0);
  /*Beep(NOTA_F3,75);
  Beep(NOTA_F3,75);
  Beep(NOTA_F3,75);
  Beep(NOTA_F3,500);
  Beep(NOTA_CS3,375);
  Beep(NOTA_DS3,375);
  Beep(NOTA_F3,250);
  //Sleep(100);
  Beep(NOTA_DS3,75);
  Beep(NOTA_F3,750);*/
  while(i==0){
    srand (time(NULL));
    i=velha();
  }
}
