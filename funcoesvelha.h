#ifndef FUNCOESVELHA_H_INCLUDED
#define FUNCOESVELHA_H_INCLUDED
#include <stdio.h>
#include <windows.h> //usado para a funcao beep, no programa usada como aviso sonoro para erros
#include <time.h> //usado para gerar uma seed "aleatoria" para a funcao rand
//====Prototipos de Funcoes====//
int padrao();
int zera_elemento(char mat[][3]);
int status(char mat[][3]);
int escolha_operador ();
int operador_restante(char op_user);
int jogada_usuario (char mat[][3], char *op_usuario);
int jogada_maquina (char mat[][3], char op_user);
int avalia_jogada(char mat[][3], int jog);
int avalia_status(char mat[][3],char op_user, char op_maq);


#endif // FUNCOESVELHA_H_INCLUDED
