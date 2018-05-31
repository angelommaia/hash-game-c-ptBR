#include "funcoesvelha.h"

//====Funcao Padrao====//
int padrao( ){
char sair='1';

do{ //início do loop de repeticao do jogo

    char matrix[3][3], op_usuario='\0', op_maquina='\0';
    int conta_jogadas=0, fim=0; //variaveis simples são iniciadas como zero ou nulo na declaracao, a matriz possui uma funcao para tal

    do{
        op_usuario=escolha_operador();
    }while(op_usuario==0); //saimos do loop somente quando o usuario escolhe um operador valido
        op_maquina=operador_restante(op_usuario);
    printf("O operador escolhido foi: %c\n", op_usuario);

    zera_elemento(matrix); //aqui zeramos a  matriz para um novo jogo

    status(matrix); //antes do jogo iniciar de fato, o usuario verá o tabuleiro

    while(conta_jogadas<9){ //as jogadas internas aqui representam o esqueleto do jogo

        jogada_usuario(matrix, &op_usuario);
        status(matrix);
        fflush(stdin);
        fim=avalia_status(matrix, op_usuario, op_maquina);
        if (fim==1){
            printf("Ganhaste!\n");
            status(matrix);
            break;
        }
        conta_jogadas++;
        printf("Jogada numero: %d\n", conta_jogadas);

        if((conta_jogadas==9)&&(fim==0)){
            printf("Velha!\n");
        break;
        }
        jogada_maquina(matrix, op_maquina);
        status(matrix);
        fflush(stdin);
        fim=avalia_status(matrix, op_usuario, op_maquina);
        if (fim==2){
            printf("Perdeste!\n");
            status(matrix);
            break;
        }

        conta_jogadas++;
        printf("Jogada numero: %d\n", conta_jogadas);
    }

    //getc(stdin);//como ainda tem dado no buffer, podemos fazer uma leitura vazia ao inves de usar o fflush
    printf("Aperte qualquer tecla para jogar novamente ou 0 para sair.\n");
    fflush(stdin);//limpeza do buffer antes de usar o getc para evitar possiveis problemas
    sair=getc(stdin);

}while(sair!='0'); //fim do loop de repeticao do jogo
return 0;
 }

//====Funcao Zera Elementos====//
int zera_elemento(char mat[][3]){
int i,j;

for (i=0;i<3;i++){
    for (j=0;j<3;j++){
    *(*(mat)+i*3+j)='\0'; //atribui o caracter nulo para todos os elementos da matriz
    }
}
return 0;
}


//====Funcao Escolha de Operador====//
int escolha_operador (){
int dummy=0;

printf("Escolha  1 para jogar com X ou 2 para jogar com O\n");
scanf("%d", &dummy);
switch(dummy){
case 1:
    return 88; //88 eh 'X' na ascii
    break;
case 2:
    return 79;//79 eh 'O' na ascii
    break;
default:
    printf("Opcao invalida.\n");
    Beep(1000,300); //aviso sonoro caso o usuario cometa um erro
    return 0;
    break;
}
 }


//====Funcao Status====//
int status(char mat[][3]){
int i,j;

printf("STATUS\n");


for (i=0;i<3;i++){
        for(j=0;j<3;j++){
            if(*(*mat+j*3+i)=='\0'){
               printf("? ");
               } else{
            printf("%c ",*(*mat+j*3+i));
            }
}
    printf("\n");
}
return 0;
}


 //====Funcao Operador Restante====//
 int operador_restante(char op_user){

 if(op_user=='X'){
    return 79;
}
if(op_user=='O'){
    return 88;
}
return 0;
 }


//====Funcao Jogada da Maquina====//
int jogada_maquina (char mat[][3], char op_maq){
int jogada, poo=0;

srand (time(NULL)); //inicializando seed para o rand()


    printf("Jogada da maquina\n");
while (poo==0){
    jogada=rand()%9; //rand com alcance de 0 a 8
    if (*(*(mat)+jogada)=='\0'){
        *(*(mat)+jogada)=op_maq;
        poo=1;
    }else{
        poo=0;
        }

    }
return 0;
}


//====Funcao Jogada do Usuario====//
int jogada_usuario (char mat[][3], char *op_usuario){
int jogada, poo=0;

while (poo==0){
printf("Informe onde deseja realizar a jogada\n");
scanf("%d", &jogada);
poo=avalia_jogada(mat,jogada);
}
*(*(mat)+jogada)=*op_usuario;
return 0;
}


//====Funcao Avalia Jogada====//
int avalia_jogada(char mat[][3], int jog){
    if(jog>8||jog<0){
        printf("Jogada invalida! Numero negativo ou maior que 8. Escolha outra casa.\n");
        Beep(1000,300); //aviso sonoro caso o usuario cometa um erro
        return 0;
    }
    else if(*(*(mat)+jog)!='\0'){
        printf("Jogada ja feita. Escolha outra casa.\n");
        Beep(1000,300); //aviso sonoro caso o usuario cometa um erro
        return 0;
    }
    else{
        return 1; //o retorno 1 eh usado como confirmacao de jogada valida
    }
}


//====Funcao Avalia Status====//
int avalia_status(char mat[][3],char op_user, char op_maq){
int i=0;
printf("op_user: %c\n", op_user);

//===Checar Se o Usuario Venceu===//

//checagem de diagonais
if((mat[0][0]==op_user)&&(mat[1][1]==op_user)&&(mat[2][2]==op_user)){
        return 1;
}
if((mat[0][2]==op_user)&&(mat[1][1]==op_user)&&(mat[2][0]==op_user)){
        return 1;
}
//checagem de linhas
    for(i=0;i<3;i++){
        if((mat[i][0]==op_user)&&(mat[i][1]==op_user)&&(mat[i][2]==op_user)){
            return 1;
        }
    }
//checagem de colunas
    for(i=0;i<3;i++){
        if((mat[0][i]==op_user)&&(mat[1][i]==op_user)&&(mat[2][i]==op_user)){
            return 1;
        }
    }

//===Checar Se a Maquina Venceu===//

//checagem de diagonais
if((((mat[0][0]==op_maq)&&(mat[1][1]==op_maq)&&(mat[2][2]==op_maq)))||(((mat[0][2]==op_maq)&&(mat[1][1]==op_maq)&&(mat[2][0==op_maq])))){
        return 2;
}
//checagem de linhas e colunas
    for(i=0;i<3;i++){
        if(((mat[i][0]==op_maq)&&(mat[i][1]==op_maq)&&(mat[i][2]==op_maq))||(((mat[0][i]==op_maq)&&(mat[1][i]==op_maq)&&(mat[2][i]==op_maq)))){
            return 2;
        }
    }
return 0;
}

