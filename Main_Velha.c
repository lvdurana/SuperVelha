#include "IA.c"


int decidir_jogada(campo *p);
void inicializa_velha(campo *p);
int tela_replay(int pos_cab, int pos_jog);
int escolha_replay(int pos_cab);
int verifica_ganhador(campo *p);
int mover_cursor(campo *p);
int loop_velha(campo *p);
int registrar_dados(campo *p);
controle carregar_controle();
int velha();

int decidir_jogada(campo *p){
  switch(p->jog[p->jog_atual].tipo){
    case 0:
      return mover_cursor(p);
    case 1:
    case 2:
    case 3:
      return IA(p);
    case 4:
      //Replay
      break;
  }

}

void inicializa_velha(campo *p){
  char a;
  for(a=0;a<9;a++){
    p->mat[a/3][a%3]=0;
    p->rec.turno[a]=9;
  }
  p->turno=0;
  p->cur=4;
  p->rec.resultado=0;
  p->jog_atual=rand()%2;
  p->jog[0].num=1;
  p->jog[1].num=4;
}

int tela_replay(int pos_cab, int pos_jog){
  FILE *f, *g;
  partida part;
  campo p;
  char nome[2][12],jogo_atual=0,i,j;
  int simb[2],num_jogos=0,posicao,placar;

  f=fopen("reg.dat","rb");
  g=fopen("reg.txt","r");

  //Inicializar dados
  inicializar_mapa(&p);
  inicializa_velha(&p);
  //Ler dados do cabeçalho
  for(i=0;i<=pos_cab;i++)
    fscanf(g,"%[^;];%d;%[^;];%d;%d;%d;%d\n",nome[0],&simb[0],nome[1],&simb[1],&num_jogos,&posicao,&placar);
  fseek(f,pos_jog*sizeof(partida),SEEK_SET);
  fread(&part,sizeof(partida),1,f);
  p.jog_atual=part.resultado>>4;
  p.jog_faltando=1;
  p.num_jogos=1;
  p.jog[0].placar=0;
  p.jog[1].placar=0;
  strcpy(p.jog[0].nome,nome[0]);
  strcpy(p.jog[1].nome,nome[1]);
  p.jog[0].simb=simb[0];
  p.jog[1].simb=simb[1];
  p.jog[0].num=1;
  p.jog[1].num=4;
  p.jog[0].tipo=(p.jog[1].tipo=4);
  //Replay do jogo
  desenhar_tela(&p,0,0,0);
  for(i=0;(part.turno[i]!=9&&i<9);i++){
    desenhar_info_tela(&p,0,0,0);
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
  int simb[2],num_jogos,posicao,placar;


  menu_base();
  f=fopen("reg.txt","r");
  for(i=0;i<=pos_cab;i++)
    fscanf(f,"%[^;];%d;%[^;];%d;%d;%d;%d\n",nome[0],&simb[0],nome[1],&simb[1],&num_jogos,&posicao,&placar);
  fclose(f);
  definir_cor(CIANO_A,BRANCO_B);
  gotoxy(61,7);
  printf("%18s","Partida 1");
  definir_cor(COR_MENU,COR_OPCOES_MENU);
  for(i=2;i<=num_jogos;i++){
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
      case '\33':
        return 0;
    }
  }
}


int verifica_ganhador(campo *p){
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

int mover_cursor(campo *p){
  //Interpretação da entrada do teclado
  for(;;){
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
      case '\15':
        if(p->mat[p->cur/3][p->cur%3]==0){
          return p->cur;
        }
        break;
      break;
    }
  }
}

int loop_velha(campo *p){
  char a;
  while(p->turno<9){
    desenhar_info_tela(p,10,0,0);
    //Mostrar mensagem na tela de "pensando"
    if(p->jog[p->jog_atual].tipo){
      gotoxy(14+(41*p->jog_atual),14);
      puts("Pensando...");
      Sleep(1500);
    }
    a=decidir_jogada(p);
    p->rec.turno[p->turno]=a;
    atualizar_xo(p,a,28,1);
    p->mat[a/3][a%3] = p->jog[p->jog_atual].num;
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
  int i=1,resultado,j=0;
  campo vl;
  FILE *f;
  controle control;

  //Carregar informações do arquivo de controle
  control=carregar_controle();
  limpar_string(vl.jog[0].nome,12);
  limpar_string(vl.jog[1].nome,12);
  vl.jog_faltando=1;
  vl.jog[0].placar=0;
  vl.jog[1].placar=0;
  inicializa_velha(&vl);
  inicializar_mapa(&vl);
  //Desenhar tela
  system("cls");
  desenhar_tela(&vl,0,0,0);
  //Escolher menus
  while(i){
    switch(i){
      case 1:
        switch(menu_inicial()){
          case 0:i=2;break;
          case 1:i=3;break;
          case 2:return 1;
        }
        break;
      case 2:
        switch(menu_t_jogo()){
          case 1:vl.jog_faltando=menu_campeonato();
          case 0:determinar_jogadores(&(vl.jog[0]),10);determinar_jogadores(&(vl.jog[1]),vl.jog[0].simb);i=0;break;
          case 2:i=1;break;
        }
        break;
      case 3:
        j=menu_replay(control.num_c_max);
        if(j>=0){
          escolha_replay(j);
          break;
        }
        i=1;
        break;
    }
  }

  //Loop principal e registro da jogada inicial e vencedor
  vl.num_jogos=vl.jog_faltando;
  while(vl.jog_faltando){
    i=0;
    inicializa_velha(&vl);
    inicializar_mapa(&vl);
    definir_cor(COR_FUNDO,COR_TEXTO);
    system("cls");
    desenhar_tela(&vl,10,0,0);
    desenhar_info_tela(&vl,10,0,0);
    if(!(vl.jog[0].tipo&&vl.jog[1].tipo))
      cursor(&vl,1);
    vl.rec.partida=control.num_max+(vl.num_jogos-vl.jog_faltando);
    vl.rec.resultado+=(vl.jog_atual<<4);
    i=loop_velha(&vl);
    vl.rec.resultado+=i;
    //Atualizar placar
    if(i<2)
      vl.jog[i].placar++;
    registrar_dados(&vl);
    vl.jog_faltando--;
    if(vl.num_jogos>1&&!vl.jog_faltando){
      if(vl.jog[0].placar>vl.jog[1].placar)
        tela_vitoria(&vl,0,1);
      if(vl.jog[1].placar>vl.jog[0].placar)
        tela_vitoria(&vl,1,1);
      if(vl.jog[0].placar==vl.jog[1].placar)
        tela_vitoria(&vl,2,1);
    }
    else
      tela_vitoria(&vl,i,0);
    definir_cor(COR_FUNDO,COR_TEXTO);
  }

  //Atualizar dados
  registrar_cabecalho(&vl,vl.num_jogos,control.num_max);
  control.num_max+=vl.num_jogos;
  control.num_c_max+=1;
  f=fopen("controle.dat","wb");
  fwrite(&control,sizeof(controle),1,f);
  fclose(f);

  return 0;
}

void main() {
  int i=0;
  while(!i){
    srand (time(NULL));
    i=velha();
  }
}
