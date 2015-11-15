#include "Interface_Velha.c"


int AI(int simb, char dif)
{
  int simb_op=0,i,j;

  //Jogada Inicial
  for(j=0;j<=2;j++)
    for(i=0;i<=2;i++)
      simb_op+=mat[i][j];
  if(!simb_op)
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

  if(simb==1)
    simb_op=4;
  else
    simb_op=1;

  if(dif){
  //printf("p1");Sleep(500);
  i=ganhar(simb);
  if(i==9){
    //printf("p2");Sleep(500);
    i=ganhar(simb_op);
    if(i==9){
      //printf("p3");Sleep(500);
      i=gerar_vantagem(simb);
      if(i==9){
        //printf("p4");Sleep(500);
        i=bloquear_vantagem(simb, simb_op);
        if(i==9){
          //printf("p5");Sleep(500);
          i=jogar_centro(simb);
          if(i==9){
            //printf("p6");Sleep(500);
            i=verificar_canto(simb_op);
            if(i==9){
              //printf("p7");Sleep(500);
              i=jogar_canto(simb);
              if(i==9){
                //printf("p8");Sleep(500);
                i=jogar_lados(simb);
              }
            }
          }
        }
      }
    }
  }
  }
  else{
    i=ganhar(simb);
    if(i==9){
      i=ganhar(simb_op);
      if(i==9){
        i=jogar_centro(simb);
        if(i==9){
          i=jogar_canto(simb);
          if(i==9){
            i=jogar_lados(simb);
          }
        }
      }
    }
  }
  return i;
}



int ganhar(int simb){
  char a, b, c, line_h=0, line_v=0;

  for(a=0;a<=2;a++)
    for(b=0;b<=2;b++)
      if(mat[a][b]==0){
        for(c=0;c<=2;c++){
          line_h+=mat[a][c];
          line_v+=mat[c][b];
        }
        if((line_h==(simb*2))||(line_v==(simb*2)))
          return a*3+b;
        line_h=0;
        line_v=0;
      }
  //Verificar Diagonais
  if((mat[0][0]+mat[1][1]+mat[2][2])==simb*2){
    if(mat[0][0]==0)
      return 0;
    if(mat[1][1]==0)
      return 4;
    if(mat[2][2]==0)
      return 8;
  }
  if((mat[0][2]+mat[1][1]+mat[2][0])==simb*2){
    if(mat[0][2]==0)
      return 2;
    if(mat[1][1]==0)
      return 4;
    if(mat[2][0]==0)
      return 6;
  }

  return 9;
}

int gerar_vantagem(int simb){
  char a, b, c, line_h=0, line_v=0,d1,d2, cont=0;
  d1=mat[0][0]+mat[1][1]+mat[2][2];
  d2=mat[0][2]+mat[1][1]+mat[2][0];

  //Verificar se uma jogada pode causar um fork
  for(a=0;a<=2;a++)
    for(b=0;b<=2;b++)
      if(mat[a][b]==0){
        for(c=0;c<=2;c++){
          line_h+=mat[a][c];
          line_v+=mat[c][b];
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

int bloquear_vantagem(int simb, int simb_op){
  char a, b, c, d, line_h=0, line_v=0, d1, d2, cont_d=0, cont=0, pos[2],e=0;
  int f;
  d1=(mat[0][0]+mat[1][1]+mat[2][2]);
  d2=(mat[0][2]+mat[1][1]+mat[2][0]);

  //Verificar se uma jogada pode causar um fork
  for(a=0;a<=2;a++)
    for(b=0;b<=2;b++)
      if(mat[a][b]==0){
        for(c=0;c<=2;c++){
          line_h+=mat[a][c];
          line_v+=mat[c][b];
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
        if(mat[a][b]==0){
          for(c=0;c<=2;c++){
            line_h+=mat[a][c];
            line_v+=mat[c][b];
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


int jogar_centro(int simb){
  if(mat[1][1]==0)
    return 4;
  return 9;
}

int verificar_canto(int simb){

  if((mat[0][0]==simb)&&(mat[2][2]==0))
    return 8;
  if((mat[0][2]==simb)&&(mat[2][0]==0))
    return 6;
  if((mat[2][0]==simb)&&(mat[0][2]==0))
    return 2;
  if((mat[2][2]==simb)&&(mat[0][0]==0))
    return 0;
  return 9;
}

int jogar_canto(int simb){

  if(mat[0][0]==0)
    return 0;
  if(mat[0][2]==0)
    return 2;
  if(mat[2][0]==0)
    return 6;
  if(mat[2][2]==0)
    return 8;
  return 9;
}

int jogar_lados(int simb){

  if(mat[0][1]==0)
    return 1;
  if(mat[1][0]==0)
    return 3;
  if(mat[1][2]==0)
    return 5;
  if(mat[2][1]==0)
    return 7;
  return 9;
}

