#include "Interface_Velha.c"

//  Atualizar:
//  Entradas dif de 0/1 pra 1/2/3
//  Converter menções à p->mat pra p->p->mat

int IA(campo *p)
{
  int simb,simb_op=0,i,j,a;

  simb=p->jog[p->jog_atual].num;
  simb_op=p->jog[p->jog_atual].num^5;

  //Jogada Inicial
  for(j=0;j<=2;j++)
    for(i=0;i<=2;i++)
      a+=p->mat[i][j];
  if(!a)
    switch(rand()%4){
      case 0:
        return 0;
      case 1:
        return 2;
      case 2:
        return 6;
      case 3:
        return 8;
    }

  switch(p->jog[p->jog_atual].tipo){
    case 3:
    //printf("p1");Sleep(500);
    i=ganhar(p, simb);
    if(i==9){
      //printf("p2");Sleep(500);
      i=ganhar(p, simb_op);
      if(i==9){
        //printf("p3");Sleep(500);
        i=gerar_vantagem(p, simb);
        if(i==9){
          //printf("p4");Sleep(500);
          i=bloquear_vantagem(p, simb, simb_op);
          if(i==9){
            //printf("p5");Sleep(500);
            i=jogar_centro(p, simb);
            if(i==9){
              //printf("p6");Sleep(500);
              i=verificar_canto(p, simb_op);
              if(i==9){
                //printf("p7");Sleep(500);
                i=jogar_canto(p, simb);
                if(i==9){
                  //printf("p8");Sleep(500);
                  i=jogar_lados(p, simb);
                }
              }
            }
          }
        }
      }
    }
    break;
  case 2:
    i=ganhar(p, simb);
    if(i==9){
      i=ganhar(p, simb_op);
      if(i==9){
        i=jogar_centro(p, simb);
        if(i==9){
          i=jogar_canto(p, simb);
          if(i==9){
            i=jogar_lados(p, simb);
          }
        }
      }
    }
    break;
  case 1:
    for(;;){
      i=rand()%3;
      j=rand()%3;
      if(!p->mat[i][j]){
        i=i*3+j;
        break;
      }
    }
    break;
  }
  return i;
}



int ganhar(campo *p, int simb){
  char a, b, c, line_h=0, line_v=0;

  for(a=0;a<=2;a++)
    for(b=0;b<=2;b++)
      if(p->mat[a][b]==0){
        for(c=0;c<=2;c++){
          line_h+=p->mat[a][c];
          line_v+=p->mat[c][b];
        }
        if((line_h==(simb*2))||(line_v==(simb*2)))
          return a*3+b;
        line_h=0;
        line_v=0;
      }
  //Verificar Diagonais
  if((p->mat[0][0]+p->mat[1][1]+p->mat[2][2])==simb*2){
    if(p->mat[0][0]==0)
      return 0;
    if(p->mat[1][1]==0)
      return 4;
    if(p->mat[2][2]==0)
      return 8;
  }
  if((p->mat[0][2]+p->mat[1][1]+p->mat[2][0])==simb*2){
    if(p->mat[0][2]==0)
      return 2;
    if(p->mat[1][1]==0)
      return 4;
    if(p->mat[2][0]==0)
      return 6;
  }

  return 9;
}

int gerar_vantagem(campo *p, int simb){
  char a, b, c, line_h=0, line_v=0,d1,d2, cont=0;
  d1=p->mat[0][0]+p->mat[1][1]+p->mat[2][2];
  d2=p->mat[0][2]+p->mat[1][1]+p->mat[2][0];

  //Verificar se uma jogada pode causar um fork
  for(a=0;a<=2;a++)
    for(b=0;b<=2;b++)
      if(p->mat[a][b]==0){
        for(c=0;c<=2;c++){
          line_h+=p->mat[a][c];
          line_v+=p->mat[c][b];
        }
        if((((a==0)&&(b==0))||((a==1)&&(b==1))||((a==2)&&(b==2)))&&(d1==simb))
          cont++;
        if((((a==0)&&(b==2))||((a==1)&&(b==1))||((a==2)&&(b==0)))&&(d2==simb))
          cont++;
        if(line_h==simb)
          cont++;
        if(line_v==simb)
          cont++;
        if(cont>1)
          return a*3+b;
        line_h=0;
        line_v=0;
        cont=0;
      }
  return 9;
}

int bloquear_vantagem(campo *p, int simb, int simb_op){
  char a, b, c, d, line_h=0, line_v=0, d1, d2, cont_d=0, cont=0, pos[2],e=0;
  int f;
  d1=(p->mat[0][0]+p->mat[1][1]+p->mat[2][2]);
  d2=(p->mat[0][2]+p->mat[1][1]+p->mat[2][0]);

  //Verificar se uma jogada pode causar um fork
  for(a=0;a<=2;a++)
    for(b=0;b<=2;b++)
      if(p->mat[a][b]==0){
        for(c=0;c<=2;c++){
          line_h+=p->mat[a][c];
          line_v+=p->mat[c][b];
        }
        if((((a==0)&&(b==0))||((a==1)&&(b==1))||((a==2)&&(b==2)))&&(d1==simb_op))
          cont_d++;
        if((((a==0)&&(b==2))||((a==1)&&(b==1))||((a==2)&&(b==0)))&&(d2==simb_op))
          cont_d++;
        if(line_h==simb_op)
          cont_d++;
        if(line_v==simb_op)
          cont_d++;
        if(cont_d>1){
          pos[cont]=(a*3+b);
          cont++;
        }
        line_h=0;
        line_v=0;
        cont_d=0;
      }

  //Avaliar se é possível forçar o oponente a se defender
  if(cont){
    for(a=0;a<=2;a++)
      for(b=0;b<=2;b++)
        if(p->mat[a][b]==0){
          for(c=0;c<=2;c++){
            line_h+=p->mat[a][c];
            line_v+=p->mat[c][b];
          }
        if((((a==0)&&(b==0))||((a==1)&&(b==1))||((a==2)&&(b==2)))&&(d1==simb))
          cont_d++;
        if((((a==0)&&(b==2))||((a==1)&&(b==1))||((a==2)&&(b==0)))&&(d2==simb))
          cont_d++;
        if(line_h==simb)
          cont_d++;
        if(line_v==simb)
          cont_d++;
        if(cont_d>0){
            for(d=0;d<cont;d++)
              if((pos[d]==8-(a*3+b))||(pos[d]==4))
                e=1;
            if(e==0)
              return a*3+b;
            e=0;
          }
        line_h=0;
        line_v=0;
        cont_d=0;
        }
    return pos[0];
  }

  return 9;
}


int jogar_centro(campo *p, int simb){
  if(p->mat[1][1]==0)
    return 4;
  return 9;
}

int verificar_canto(campo *p, int simb){
  int v[4],a=0;
  if((p->mat[0][0]==simb)&&(p->mat[2][2]==0)){
    v[a]=8;
    a++;
  }
  if((p->mat[0][2]==simb)&&(p->mat[2][0]==0)){
    v[a]=6;
    a++;
  }
  if((p->mat[2][0]==simb)&&(p->mat[0][2]==0)){
    v[a]=2;
    a++;
  }
  if((p->mat[2][2]==simb)&&(p->mat[0][0]==0)){
    v[a]=0;
    a++;
  }
  if (a)
    return v[rand()%a];
  return 9;
}

int jogar_canto(campo *p, int simb){
  int v[4],a=0;
  if(p->mat[0][0]==0){
    v[a]=0;
    a++;
  }
  if(p->mat[0][2]==0){
    v[a]=2;
    a++;
  }
  if(p->mat[2][0]==0){
    v[a]=6;
    a++;
  }
  if(p->mat[2][2]==0){
    v[a]=8;
    a++;
  }
  if (a)
    return v[rand()%a];
  return 9;
}

int jogar_lados(campo *p, int simb){
  int v[4],a=0;
  if(p->mat[0][1]==0){
    v[a]=1;
    a++;
  }
  if(p->mat[1][0]==0){
    v[a]=3;
    a++;
  }
  if(p->mat[1][2]==0){
    v[a]=5;
    a++;
  }
  if(p->mat[2][1]==0){
    v[a]=7;
    a++;
  }
  if (a)
    return v[rand()%a];
  return 9;
}

