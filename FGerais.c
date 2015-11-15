#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <ctype.h>
#include <string.h>

int entrada(char limite, char* string, char* cont, char modo);
int verificar_char(char a,char modo);
void tela_entrada(char* text, char *input, char tam_input,char modo);
void transferir_string(char* src, char*dst);
void limpar_string(char* string, char tam);
char converter_entrada();


int entrada(char limite, char* string, char* cont, char modo)
{
  char a;

  a=getch();//56,54
  if(*cont<(limite-1))
    if(verificar_char(a,modo)){
      string[*cont]=a;
      (*cont)++;
    }
  if(*cont>0){
  //Interpretar Enter
    if(a=='\15'){
      string[*cont]='\0';
      (*cont)=0;
      return 0;
    }
    //Interpretar Backspace
    if(a=='\10'){
      (*cont)--;
      string[*cont]=' ';
    }
  }
  return 1;
}

int verificar_char(char a,char modo)
{
  /*Modo 0: Todos os caracteres válidos ASCII
    Modo 1: Alfanumérico(letras,numeros,ponto,espaço e vírgula)
    Modo 2: Números 0-9
  */
  switch(modo){
    case 0:
      if(a!=8)
        return 1;
      return 0;
    case 1:
      if(((a>64)&&(a<91))||((a>96)&&(a<123))||((a>47)&&(a<58))||(a=='\40')||(a=='\54')||(a=='\56'))
        return 1;
      return 0;
    case 2:
      if((a>47)&&(a<58))
        return 1;
      return 0;
  }
  return 0;
}

void tela_entrada(char* text, char *input, char tam_input,char modo)
{
  char cont=0,i;
  do{
    system("cls");
    printf("%s\n",text);
    printf("   \332\304");for(i=0;i<tam_input;i++) printf("\304");printf("\304\277\n");
    printf("   \263 ");for(i=0;i<tam_input;i++) printf("%c",input[i]);printf(" \263\n");
    printf("   \300\304");for(i=0;i<tam_input;i++) printf("\304");printf("\304\331\n");
  }while(entrada(tam_input,input,&cont,modo));

}

void transferir_string(char* src, char*dst)
{
  int a=-1;
  do{
    a++;
    dst[a]=src[a];
  }while(src[a]!='\0');

}

void limpar_string(char* string, char tam)
{
  char a=0;
  for(;a<tam;a++)
    string[a]=' ';
}

char converter_entrada()
{
char a;

//Interpretar entrada do teclado
a=toupper(getch());
  //Converter setas do teclado
if(a=='\340'){
  switch(getch()){
    case 72:
      a='W';
      break;
    case 75:
      a='A';
      break;
    case 77:
      a='D';
      break;
    case 80:
      a='S';
      break;
  }
}
return a;
}

int menu_saida(){
  char cursor=0;
  while(1){
    system("cls");
    printf("\n\n\n\n\n");
    printf("                            \n");
    printf("                            \332\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\277\n");
    printf("                            \263                      \263\n");
    if(cursor==0){
      printf("                            \263  \311\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\273  \263\n");
      printf("                            \263  \272     Voltar     \272  \263\n");
      printf("                            \263  \310\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\274  \263\n");
    }
    else{
      printf("                            \263  \332\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\277  \263\n");
      printf("                            \263  \263     Voltar     \263  \263\n");
      printf("                            \263  \300\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\331  \263\n");
    }
    if(cursor==1){
      printf("                            \263  \311\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\273  \263\n");
      printf("                            \263  \272 Menu Principal \272  \263\n");
      printf("                            \263  \310\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\274  \263\n");
    }
    else{
      printf("                            \263  \332\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\277  \263\n");
      printf("                            \263  \263 Menu Principal \263  \263\n");
      printf("                            \263  \300\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\331  \263\n");
    }
    if(cursor==2){
      printf("                            \263  \311\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\273  \263\n");
      printf("                            \263  \272      Sair      \272  \263\n");
      printf("                            \263  \310\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\315\274  \263\n");
    }
    else{
      printf("                            \263  \332\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\277  \263\n");
      printf("                            \263  \263      Sair      \263  \263\n");
      printf("                            \263  \300\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\331  \263\n");
    }
    printf("                            \263                      \263\n");
    printf("                            \300\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\304\331\n");
    switch(converter_entrada()){
      case 'W':
        if(cursor>0)
          cursor--;
        break;
      case 'S':
        if(cursor<2)
          cursor++;
        break;
      case '\15':
        return cursor;
        break;
      case '\33':
        return 0;
        break;
    }
  }
}

