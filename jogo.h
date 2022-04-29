#ifndef JOGO_H
#define JOGO_H
#include <string.h>
#include <cstring>
#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

// Struct para os temas c/ parametro para o nome do tema e array para as palavras do tema
struct Ttemas{
    char nome[20];
    char **p;
};

// Struct auxiliar para a manipulação do ficheiro relativo às pontuações totais
struct Tscore{
    char nome[20];
    int pontos;
};

// Classe para o modo de funcionameto c/ variáveis bool para saber se o utilizador pretende tema random e cronómetro
//tem tabém uma var. dificuldade que vai valer 1 caso a dificuldade seja dificil, 2-media e 3-facil
//que vai ser usada para multiplicar pelo tempo e pela pontuação
class Cfunciona{
private:
    bool randTema;
    bool tempo;
    int dificuldade;
public:
    //inicializa com modo elementar
    Cfunciona(){
        randTema = false;
        tempo = false;
        dificuldade = 1;
    };
    //altera os parametros private da class
    void mudaFuncionalidade(bool tema, bool time, int dif){
        randTema = tema;
        tempo = time;
        dificuldade = dif;
    };

    int guardaFunc(); //Guarda num ficheiro o modo de funcionamento
    int LoadFunc(); //Load do ultimo modo de funcionamento
    void funcionamento();
    void imprime(){
        cout << randTema << " " << tempo << " " << dificuldade << endl;
    }
    bool devolveRandTema(void){return randTema;}
    friend class Cjogo;
};

// class jogo com os parametros necessarios para cada jogo
class Cjogo
{
private:
    string nome;
    int score;
    int vidas;
    string tema;
    string palavra; //palavra a advinhar
    string palavraEscondida; //palavra a advinhar em convertida em '_'
    int tempo;

    static int numJog;
public:
    Cjogo(){
        numJog++;
    };

    //altera os parametros private da class
    void mudaParametros(string n,int s, int v, string tem, string pal, string palEsc, int t){
        nome = n;
        score = s;
        vidas = v;
        tema = tem;
        palavra = pal;
        palavraEscondida = palEsc;
        tempo = t;
    };

    int numJogadores(void){return this->numJog;}; //Numero de jogadores
    void desenhaForca(int v);
    void jogoForca(bool novo,Cfunciona f); //contem var bool para saber se é um jogo novo ou jogo que estava a meio
    int guardaFicha(Cfunciona f); //Guarda cada jogo num ficheiro
    bool verificaFicha(string jog); //verifica se o jogador tem algum jogo a meio
    void updateFichaClass(string n); //Atualiza o ficheiro se o jogador continuar algum jogo que tem a meio
    void updateFichaDone(string n); //Termina o jogo que ficou a meio caso o jogador não o queira continuar
    bool verificaCronometro(string n); // Verifica se o jogo que ficou a meio tinha cronometro ativo
    int verificaDificuldade(string n); // Verifica a dificuldade do jogo que ficou a meio
};

struct Ttemas EscolherTema(struct Ttemas t[], int size, bool randT); //Escolha do tema
string getPal(struct Ttemas t,int n); //Escolha random da palavra consoante o tema
string palavraEscondida(string aux); //Converte a palavra a advinhar em '_'
void criaFichaJogadores(); // Cria ficheiro para guardar jogos
int guardaFichaLetras(char c); //Guarda num ficheiro as letras introduzidas pelo utilizador
int LoadArrayLetras(char *array,int &size); //Adiciona ao array as letras que estão no ficheiro
void fichaScore(); //Guarda num ficheiro o nome dos jogadores e respetivas pontuações totais
void ordenaFichaScore(); //Ordena o ficheiro c/ as pontuações totais
int comparaScore(const void *ficha1, const void *ficha2);//Função auxiliar para ordenar o ficheiro por pontuação
void imprimeScore(); //Imprime o ficheiro c/ pontuações totais

#endif // JOGO_H
