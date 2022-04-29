#include <iostream>
#include <string.h>
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <jogo.h>
#include<ios> //used to get stream size
#include<limits> //used to get numeric limits
#include <fstream>

using namespace std;

const int numPal = 8;

int main()
{
    char op;
    string jogNome;

    Cfunciona func;
    Cjogo jogo1;

    // Inicialização do array de struct com os temas e as respetivas palavras
    struct Ttemas tema[3];
    strcpy(tema[0].nome,"Carros");
    char *pa[numPal];
    pa[0] = "FERRARI";
    pa[1] = "FORD";
    pa[2] = "JAGUAR";
    pa[3] = "MASERATI";
    pa[4] = "LEXUS";
    pa[5] = "CHEVROLET";
    pa[6] = "PORSCHE";
    pa[7] = "BENTLEY";
    tema[0].p=pa;

    strcpy(tema[1].nome,"Paises");
    char *pa1[numPal];
    pa1[0] = "PORTUGAL";
    pa1[1] ="ESPANHA";
    pa1[2] = "JAMAICA";
    pa1[3] = "NICARAGUA";
    pa1[4] = "MALAWI";
    pa1[5] = "HAITI";
    pa1[6] = "HONDURAS";
    pa1[7] = "CUBA";
    tema[1].p=pa1;

    strcpy(tema[2].nome,"Nomes");
    char*pa2[numPal];
    pa2[0] = "JOANA";
    pa2[1] = "PEDRO";
    pa2[2] = "ADOLFO";
    pa2[3] = "GUSTAVO";
    pa2[4] = "EURICO";
    pa2[5] = "MARCELO";
    pa2[6] = "FERNANDO";
    pa2[7] = "CARLOS";
    tema[2].p=pa2;

    do{
        cout << "******* Menu *******" << endl;
        cout << "1.Novo jogo" << endl;
        cout << "2.Sair" << endl;
        cout << "3.Modo de funcionamento" << endl;
        cout << "4.Mostrar Pontuacoes" << endl;
        cout << "Escolha a opcao pretendida: ";
        cin >> op;
        cin.ignore();
        system("cls");

        switch(op){
        case '1':{
            //Vai buscar ao ficheiro o modo de funcionamento ativo
            func.LoadFunc();

            cout << "Indique o seu nome: ";
            cin >> jogNome;
            cin.ignore();

            // Verifica se o jogador tem algum jogo a meio e se o pretende continuar
            bool v = jogo1.verificaFicha(jogNome);

            //Caso o jogador não tenha jogos a meio, ou não queira continuar o que tinha
            if(!v){
                Ttemas teste = EscolherTema(tema,3,func.devolveRandTema());
                string p = getPal(teste,numPal);
                string pEsc = palavraEscondida(p);

                string temaNome = teste.nome;
                system("cls");
                jogo1.updateFichaDone(jogNome);
                jogo1.mudaParametros(jogNome,0,9,temaNome,p,pEsc,0);
                cout << "Foi criado um novo jogo!" << endl;
                //cout << "Tema da sua palavra: " << teste.nome <<endl;
            }

            jogo1.jogoForca(!v,func);

            //Se for um jogo que tinha a meio atualiza ficheiro, caso contrario adiciona o jogo ao ficheiro
            if(v){
                jogo1.updateFichaClass(jogNome);
            }
            else jogo1.guardaFicha(func);

            break;
        }
        case '2':{
            //Cria ficheiro onde se vai introduzir as informações dos jogadores e respetivos jogos
            //criaFichaJogadores();
            cout << "Ate uma proxima!" << endl;
            return 0;
            break;
        }
        case '3':{
            func.funcionamento(); //Pergunta ao utilizador que modo pertende
            func.guardaFunc(); //Guarda esse modo num ficheiro
            system("cls");
            break;
        }
        case '4':{
            system ("cls");
            fichaScore(); //Coloca num ficheiro os nomes dos jogadores e respetivas pontuações
            ordenaFichaScore(); //Ordena o ficheiro
            imprimeScore(); // Imprime o ficheiro
            system("pause");
            system("cls");
            break;
        }
        default:
            cout << "Erro: Introduza um numero inteiro de 1 a 4!" << endl;
        }
    }while(op != 1 && op != 2 && op != 3 && op != 4);
    return 0;
}
