#include "jogo.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <windows.h>
#include <fstream>
#include <iostream>
#include <string.h>
#include<ios> //used to get stream size
#include<limits> //used to get numeric limits
#include<iomanip>

const int sizePal = 20;
const int sizeAlf = 30;


int Cjogo::numJog = 0;
//-----------------------------------------------------------------------------------

// Função que retorna a struct tema do tema a adivinhar
struct Ttemas EscolherTema(struct Ttemas t[], int size,bool randT){

    if(randT == false){
        char op;
        do{
            cout << "Escolha um dos seguintes temas:" << endl;
            for(int i = 0; i < size; i++){
                cout <<i+1<<"."<<t[i].nome << endl;
            }
            cout << "Escolha a opcao pretendida: ";
            cin >> op;

            if(op<49 || op>51){
                cout << "Erro: Introduza um numero valido! " << endl;
            }

        }while(op<49 || op>51);

        int aux = op - '0';
        return t[aux-1];
    }
    else{
        srand(time(0));
        int aux = rand() % size + 0;
        return t[aux];
    }
}

//-----------------------------------------------------------------------------------

string getPal(struct Ttemas t,int n){
    // Escolha random da palavra
    srand (time(0));
    int aux = rand() % n + 0;
    char pal[sizePal];
    strcpy(pal,t.p[aux]);
    string palavra;
    palavra=pal;

    return palavra;
}

//-----------------------------------------------------------------------------------

//Função que converte a palavra a adivinhar em '_'
string palavraEscondida(string aux){
    string str = aux.c_str();
    for(int i = 0; i < aux.size(); i++){
        str[i] = '_';
    }
    return str;
}
//-----------------------------------------------------------------------------------

void criaFichaJogadores(){
    ofstream file("FichaJogadores.txt");

    string nome = "jogador";
    int score = 0;
    int vidas = 9;
    string tema = "NONE";
    string palavra = "NONE";
    string escondida = "NONE";
    bool cron = false;
    int tempo = 0;
    int dif = 1;

    file << nome << ' ' << score << ' ' << vidas << ' ' << tema << ' ' << palavra << ' ' << escondida << ' ' << cron << ' ' << tempo << ' ' << dif << endl;
    file.close();
}

//-----------------------------------------------------------------------------------

void Cjogo::desenhaForca(int v){

    if (v == 8){
        cout <<"           " << endl;
        cout <<"          |" << endl;
        cout <<"          |" << endl;
        cout <<"          |" << endl;
        cout <<"          |" << endl;
        cout <<"          |" << endl;
        cout <<"          |" << endl;
        cout <<"          |" << endl;
        cout <<"          |" << endl;
        cout << "----------" << endl;
    }

    if (v == 7){
        cout <<"     _____.     " << endl;
        cout <<"          |" << endl;
        cout <<"          |" << endl;
        cout <<"          |" << endl;
        cout <<"          |" << endl;
        cout <<"          |" << endl;
        cout <<"          |" << endl;
        cout <<"          |" << endl;
        cout <<"          |" << endl;
        cout << "----------" << endl;
    }

    if (v == 6){
        cout <<"     _____.     " << endl;
        cout <<"     |    |" << endl;
        cout <<"     |    |" << endl;
        cout <<"          |" << endl;
        cout <<"          |" << endl;
        cout <<"          |" << endl;
        cout <<"          |" << endl;
        cout <<"          |" << endl;
        cout <<"          |" << endl;
        cout << "----------" << endl;
    }

    if (v == 5){
        cout <<"     _____.     " << endl;
        cout <<"     |    |" << endl;
        cout <<"     |    |" << endl;
        cout <<"     O    |" << endl;
        cout <<"          |" << endl;
        cout <<"          |" << endl;
        cout <<"          |" << endl;
        cout <<"          |" << endl;
        cout <<"          |" << endl;
        cout << "----------" << endl;
    }

    if (v == 4){
        cout <<"     _____.     " << endl;
        cout <<"     |    |" << endl;
        cout <<"     |    |" << endl;
        cout <<"     O    |" << endl;
        cout <<"     |    |" << endl;
        cout <<"     |    |" << endl;
        cout <<"     |    |" << endl;
        cout <<"          |" << endl;
        cout <<"          |" << endl;
        cout << "----------" << endl;
    }

    if (v == 3){
        cout <<"     _____.     " << endl;
        cout <<"     |    |" << endl;
        cout <<"     |    |" << endl;
        cout <<"     O    |" << endl;
        cout <<"    /|    |" << endl;
        cout <<"   / |    |" << endl;
        cout <<"     |    |" << endl;
        cout <<"          |" << endl;
        cout <<"          |" << endl;
        cout << "----------" << endl;
    }

    if (v == 2){
        cout <<"     _____.     " << endl;
        cout <<"     |    |" << endl;
        cout <<"     |    |" << endl;
        cout <<"     O    |" << endl;
        cout <<"    /|\\   |" << endl;
        cout <<"   / | \\  |" << endl;
        cout <<"     |    |" << endl;
        cout <<"          |" << endl;
        cout <<"          |" << endl;
        cout << "----------" << endl;
    }

    if (v == 1){
        cout <<"     _____.     " << endl;
        cout <<"     |    |" << endl;
        cout <<"     |    |" << endl;
        cout <<"     O    |" << endl;
        cout <<"    /|\\   |" << endl;
        cout <<"   / | \\  |" << endl;
        cout <<"     |    |" << endl;
        cout <<"      \\   |" << endl;
        cout <<"       \\  |" << endl;
        cout << "----------" << endl;
    }

    if (v == 0){
        cout <<"     _____.     " << endl;
        cout <<"     |    |" << endl;
        cout <<"     |    |" << endl;
        cout <<"     O    |" << endl;
        cout <<"    /|\\   |" << endl;
        cout <<"   / | \\  |" << endl;
        cout <<"     |    |" << endl;
        cout <<"    / \\   |" << endl;
        cout <<"   /   \\  |" << endl;
        cout << "----------" << endl;
        cout << "GAME OVER" << endl;
    }

}

//-----------------------------------------------------------------------------------

// Função que contem essencialmente o jogo da forca

void Cjogo::jogoForca(bool novo, Cfunciona f){
    char *arrayLetra = new char[sizeAlf]; //array dinamico para guardar as letras escolhidas pelo utilizador
    char l; // letra escolhida pelo utilizador
    int x = 0; // variavel auxiliar para guardar a letra introduzida num array
    bool acertou = false; // variavel auxiliar para saber se o jogador acertou na letra
    // variavel auxiliar para para saber se a letra introduzida pelo jogador já tinha sido introduzida anteriormente
    bool encontrou = false;

    //Variáveis para executar o cronometro
    time_t start = 0;
    time_t finish = 0;
    int soma = 0;
    int tempmax = 30;


    // caso a var novo seja false, significa que vai ser um jogo não terminado portanto vai chamar esta função que vai
    //alterar o arrayLetra com as letras introduzidas no jogo que ficou a meio e x com o tamanho desse array
    if(!novo){
        LoadArrayLetras(arrayLetra,x);
        f.mudaFuncionalidade(false,verificaCronometro(nome),verificaDificuldade(nome));
        if(f.tempo == true){
            tempmax = tempo;
            cout << "Tem " << tempmax << " segundos para descobrir a palavra!" << endl;
        }
    }
    else{
        remove("FichaLetras.txt"); //Caso seja um jogo novo apaga o ficheiro que continha as letras
        if(f.tempo == true){
            tempmax = (4-f.dificuldade)*palavra.size()*5; //Calculo do tempo que vai ter para descobrir a palavra
            cout << "Tem " << tempmax << " segundos para descobrir a palavra!" << endl;
        }

    }

    do{
        cout << "Tema: " << tema << endl;
        cout << palavraEscondida << endl;

        do{
            cout << "Se a qualquer altura quiser sair do jogo pressione e" << endl;
            cout << "Escolha uma letra maiuscula: "<< endl;
            time(&start);
            cin >> l;
            time(&finish);
            cin.ignore();

            //Verifica se a letra ja tinha sido escolhida anteriormente
            encontrou = false;
            for(int j = 0; j < x; j++){
                if(l == arrayLetra[j] && x > 0){
                    encontrou = true;
                    cout << "Ja escolheu essa letra" << endl;
                    break;
                }
            }

            if(l == 'e') break; //caso o utilizador queira sair do jogo

            if(l < 'A' || l > 'Z'){

                cout << "Erro: Nao introduziu uma letra maiuscula " << endl;
            }

            //Se a letra é válida e nunca foi escolhida é introduzida num array
            if(encontrou == false && (l >= 'A' && l <= 'Z' )){
                arrayLetra[x] = l;
                guardaFichaLetras(arrayLetra[x]);
                x++;
            }
            //system("cls");

        }while( (l < 'A' || l > 'Z') || encontrou == true);

        //Calculo do tempo restante para descobrir a palavra
        if(f.tempo == true){
            int time = difftime(finish, start);
            soma += time;
            int sobra = tempmax-soma;

            //Verifica se o jogador ainda tem tempo para adivinhar a palavra
            if (soma > tempmax){
                system ("cls");
                cout << "Perdeu o jogo! Esgotou o tempo!" << endl;
                vidas = 0;
                system("pause");
                system("cls");
                break;
            }
            else{
                system("cls");
                cout << "Tem " << sobra <<" segundos restantes!" << endl;
            }
            tempo = sobra;
        }

        if(l == 'e'){
            system("cls");
            break;
        }

        //Verifica se a letra introduzida esta contida na palavra a adivinhar
        acertou = false;
        for( int i = 0; i < palavra.size(); i++){
            //se a letra estiver contida na palavra desvenda a mesma
            if (l == palavra[i]){
                acertou = true;
                palavraEscondida[i] = l;
            }
        }

        if(f.tempo == false) system("cls");

        // Caso o jogador erre retira lhe uma vida
        if(acertou == false){
            cout << "ERROU!! Tente outra vez" << endl;
            vidas--;
        }

        cout << "vidas: " << vidas << endl;

        // Sai do ciclo caso o utilizador tenha acertado a palavra e não esgotado as vidas
        if(palavra.compare(palavraEscondida) == 0){
            break;
        }

        desenhaForca(vidas); // Desenho da forca

        //Vai imprimir as letras que o utilizador selecionou e que não pertencem à palavra
        cout << "Letras erradas: ";
        for(int i = 0; i < x;i++){ //Percorre o arrayLetra
            int errada = 0;
            for(int j = 0; j < palavra.size(); j++){ //Percorre todas as letras da palavra
                if(arrayLetra[i] != palavra[j]){
                    errada++;
                }
            }
            //Só vai imprimir caso essa letra seja diferente de todas as letras da palavra
            if(errada == palavra.size()) cout << arrayLetra[i] << " ";
        }
        cout << endl;


    }while(vidas>0);

    if(vidas == 0 && f.tempo == false){
        system("pause");
        system("cls");
    }

    if(vidas > 0 && l != 'e'){
        cout << "Parabens! Acertou a palavra" << endl;

        // Calculo da pontuação consoante a dificuldade, o tempo e as vidas restantes
        if(f.tempo == false){
            score = 2*palavra.size() + 5*vidas;
        }
        else{
            if((tempmax-soma) < tempmax/6){
                score = f.dificuldade*10 + 2*palavra.size() + 5*f.dificuldade + 5*vidas;
            }
            else if((tempmax-soma)>tempmax/6 && (tempmax-soma)<tempmax/4){
                score = f.dificuldade*10 + 2*palavra.size() + 10*f.dificuldade + 5*vidas;
            }
            else if((tempmax-soma)>tempmax/4 && (tempmax-soma)<tempmax/2){
                score = f.dificuldade*10 + 2*palavra.size() + 15*f.dificuldade + 5*vidas;
            }
            else{
                score = f.dificuldade*10 + 2*palavra.size() + 20*f.dificuldade + 5*vidas;
            }
        }
        cout << "Ganhou " << score << " pontos!" << endl;
        system("pause");
        system("cls");
    }

    delete [] arrayLetra;

};

//-----------------------------------------------------------------------------------

// Guarda jogo num ficheiro
int Cjogo::guardaFicha(Cfunciona f){

    ofstream file("FichaJogadores.txt",ios::app);

    if(!file.is_open()){
        cerr << "Erro: Nao foi possivel abrir o ficheiro!" << endl;
        return -1;
    }

    file << nome << ' ' << score << ' ' << vidas << ' ' << tema << ' ' << palavra << ' ' << palavraEscondida << ' ' << f.tempo << ' ' << tempo << ' ' << f.dificuldade << endl;
    file.close();

    return 0;
}

//-----------------------------------------------------------------------------------

// Função que verifica se o jogador tem jogo não terminado
bool Cjogo::verificaFicha(string jog){

    char op;
    bool verifica = false;

    ifstream file("FichaJogadores.txt");

    if(!file.is_open()){
        cerr << "Erro: Nao foi possivel abrir o ficheiro!";
        return false;
    }

    string nomeJ;
    int scoreJ;
    int vidasJ;
    string temaJ;
    string palavraJ;
    string escondidaJ;
    bool randTempJ;
    int tempoJ;
    int difJ;

    while(file >> nomeJ >> scoreJ >> vidasJ >> temaJ >> palavraJ >> escondidaJ >> randTempJ >> tempoJ >> difJ){ //Percorre ficheiro
        //confirma se o jogo corresponde ao jogador a pesquisar e se o jogo está a meio (palavra diferente de palavra escondida)
        if(nomeJ.compare(jog) == 0 && palavraJ != escondidaJ && vidasJ > 0){
            do{
                cout << "Tem um jogo a meio. Pretende continuar? (s/n)" << endl;
                cin >> op;
                cin.ignore();

                if(op!=115 && op!=110){
                    cout << "Erro: Introduza um opcao valida!" << endl;
                }
            }while(op!=115 && op!=110);

            //Se o utilizador pressionar 's' altera os parametros da classe para os do jogo não terminado
            if(op == 115){
                verifica = true;
                mudaParametros(nomeJ,scoreJ,vidasJ,temaJ,palavraJ,escondidaJ,tempoJ);
            }
        }
    }

    return verifica;
}

//-----------------------------------------------------------------------------------

// Esta função vai servir para caso o utilizador não querer continuar um jogo terminar este, ou seja, igualar palavra escondida e palavra
void Cjogo::updateFichaDone(string n){

    ofstream tempFile("temp.txt");
    ifstream file("FichaJogadores.txt");

    if(!tempFile.is_open()){
        cerr << "Erro: Nao foi possivel abrir o ficheiro!" << endl;
    }

    if(!file.is_open()){
        cerr << "Erro: Nao foi possivel abrir o ficheiro!" << endl;
    }

    string nomeJ;
    int scoreJ;
    int vidasJ;
    string temaJ;
    string palavraJ;
    string escondidaJ;
    bool randTempJ;
    int tempJ;
    int difJ;

    string newPalavra = "DONE";
    string newEscondida = "DONE";

    while(file >> nomeJ >> scoreJ >> vidasJ >> temaJ >> palavraJ >> escondidaJ >> randTempJ >> tempJ >> difJ){
        if(nomeJ.compare(n) == 0){
            tempFile << nomeJ << ' ' << scoreJ << ' ' << vidasJ << ' ' << temaJ << ' ' << newPalavra << ' ' << newEscondida << ' ' << randTempJ << ' ' << tempJ << ' ' << difJ << endl;

        }
        else{
            tempFile << nomeJ << ' ' << scoreJ << ' ' << vidasJ << ' ' << temaJ << ' ' << ' ' << palavraJ << ' ' << escondidaJ << ' ' << randTempJ << ' ' << tempJ << ' ' << difJ  << endl;
        }
    }

    tempFile.close();
    file.close();
    remove("FichaJogadores.txt");
    rename("temp.txt","FichaJogadores.txt");
}

//-----------------------------------------------------------------------------------

//Esta função atualiza o ficheiro caso o jogador continue um jogo que tinha a meio
void Cjogo::updateFichaClass(string n){

    ofstream tempFile("temp.txt");
    ifstream file("FichaJogadores.txt");

    if(!tempFile.is_open()){
        cerr << "Erro: Nao foi possivel abrir o ficheiro!" << endl;
    }

    if(!file.is_open()){
        cerr << "Erro: Nao foi possivel abrir o ficheiro!" << endl;
    }

    string nomeJ;
    int scoreJ;
    int vidasJ;
    string temaJ;
    string palavraJ;
    string escondidaJ;
    bool randTempJ;
    int tempJ;
    int difJ;

    while(file >> nomeJ >> scoreJ >> vidasJ >> temaJ >> palavraJ >> escondidaJ >> randTempJ >> tempJ >> difJ){
        if(nomeJ.compare(n) == 0){
            tempFile << nome << ' ' << score << ' ' << vidas << ' ' << tema << ' ' << palavra << ' ' << palavraEscondida << ' ' << randTempJ << ' ' << tempo << ' ' << difJ << endl;

        }
        else{
            tempFile << nomeJ << ' ' << scoreJ << ' ' << vidasJ << ' ' << temaJ << ' ' << palavraJ << ' ' << escondidaJ << ' ' << randTempJ << ' ' << tempJ << ' ' << difJ << endl;
        }
    }

    tempFile.close();
    file.close();
    remove("FichaJogadores.txt");
    rename("temp.txt","FichaJogadores.txt");
}

//-----------------------------------------------------------------------------------

//Função que guarda no final do ficheiro a letra introduzida
int guardaFichaLetras(char c){
    ofstream file("FichaLetras.txt",ios::app);

    if(!file.is_open()){
        cerr << "Erro: Nao foi possivel abrir o ficheiro!" << endl;
        return -1;
    }
    file << c << endl;
    file.close();
    return 0;
}

//-----------------------------------------------------------------------------------

// Função para guardar no array letras que estão no ficheiro
int LoadArrayLetras(char *array,int &size){
    ifstream file("FichaLetras.txt");

    if(!file.is_open()){
        cerr << "Erro1: Nao foi possivel abrir o ficheiro!" << endl;
        return -1;
    }

    char c;
    size = 0;

    while(file >> c){
        array[size] = c;
        size ++;
    }

    file.close();
    return 0;
}

//-----------------------------------------------------------------------------------

//Função para guardar modos de funcionamento em ficheiros

int Cfunciona::guardaFunc(){
    ofstream file("FichaFunc.txt",ios::app);

    if(!file.is_open()){
        cerr << "Erro: Nao foi possivel abrir o ficheiro!" << endl;
        return -1;
    }
    file << randTema << " " << tempo << " " << dificuldade << endl;
    file.close();
    return 0;
}

//-----------------------------------------------------------------------------------

//Fazer load do ultimo modo de funcionameto do ficheiro
int Cfunciona::LoadFunc(){
    ifstream file("FichaFunc.txt");

    if(!file.is_open()){
        cerr << "Erro: Nao foi possivel abrir o ficheiro!" << endl;
        return -1;
    }

    bool r;
    bool t;
    int d;

    while(file >> r >> t >> d){
        //Lê o ficheiro
    }
    mudaFuncionalidade(r,t,d); //Altera o modo de funcionamento consoante o que ficou guardado na ultima linha do ficheiro
    file.close();

    return 0;
}

//-----------------------------------------------------------------------------------

void Cfunciona::funcionamento(){
    char opt; // variável auxilar para saber se o jogador pretende tema aleatorio
    char opc; // variável auxilar para saber se o jogador pretende cronometro
    char opd; // variável auxilar para saber que dificuldade pretende o jogador

    cout << "******* Modo funcionamento *******" << endl;

    do{
        cout << "Pretende temas aleatorios? (s/n)" << endl;
        cin >> opt;
        cin.ignore();

        if(opt!=115 && opt!=110){
            cout << "Erro: Introduziu um caracter invalido!" << endl;
        }

    }while(opt!=115 && opt!=110);

    if(opt == 115){
        randTema = true;
    }
    else{
        randTema = false;
    }

    do{
        cout << "Pretende cronometro? (s/n)" << endl;
        cin >> opc;
        cin.ignore();

        if(opc!=115 && opc!=110){
            cout << "Erro: Introduziu um caracter invalido!" << endl;
        }

    }while(opc!=115 && opc!=110);

    if(opc == 115){
        tempo = true;
    }
    else{
        tempo = false;
    }

    do{
        cout << "Dificuldade: 1.Facil 2.Medio 3.Dificil" << endl;
        cin >> opd;
        cin.ignore();

        if(opd != '1' && opd != '2' && opd != '3'){
            cout << "Erro: Introduza um numero valido!" << endl;
        }

    }while(opd != '1' && opd != '2' && opd != '3');

    if(opd == '1'){
        dificuldade = 1;
    }
    else if(opd == '2'){
        dificuldade = 2;
    }
    else{
        dificuldade = 3;
    }
}

//-----------------------------------------------------------------------------------

//Verifica se o jogo que ficou a meio tinha cronómetro ativo
bool Cjogo::verificaCronometro(string n){

    bool verifica = false;

    ifstream file("FichaJogadores.txt");

    if(!file.is_open()){
        cerr << "Erro: Nao foi possivel abrir o ficheiro!";
        return false;
    }

    string nomeJ;
    int scoreJ;
    int vidasJ;
    string temaJ;
    string palavraJ;
    string escondidaJ;
    bool randTempJ;
    int tempoJ;
    int difJ;

    while(file >> nomeJ >> scoreJ >> vidasJ >> temaJ >> palavraJ >> escondidaJ >> randTempJ >> tempoJ >> difJ){ //Percorre ficheiro
        //confirma se o jogo corresponde ao jogador a pesquisar e se o jogo está a meio (palavra diferente de palavra escondida)
        if(nomeJ.compare(n) == 0 && palavraJ != escondidaJ && vidasJ > 0){
            verifica = randTempJ;
        }
    }

    return verifica;
}

//-----------------------------------------------------------------------------------

// Função que devolve a dificuldade c/ que o jogo que ficou a meio estava a ser jogada
int Cjogo::verificaDificuldade(string n){
    int verifica = 0;

    ifstream file("FichaJogadores.txt");

    if(!file.is_open()){
        cerr << "Erro: Nao foi possivel abrir o ficheiro!";
        return 0;
    }

    string nomeJ;
    int scoreJ;
    int vidasJ;
    string temaJ;
    string palavraJ;
    string escondidaJ;
    bool randTempJ;
    int tempoJ;
    int difJ;

    while(file >> nomeJ >> scoreJ >> vidasJ >> temaJ >> palavraJ >> escondidaJ >> randTempJ >> tempoJ >> difJ){ //Percorre ficheiro
        //confirma se o jogo corresponde ao jogador a pesquisar e se o jogo está a meio (palavra diferente de palavra escondida)
        if(nomeJ.compare(n) == 0 && palavraJ != escondidaJ && vidasJ > 0){
            verifica = difJ;
        }
    }
    return verifica;
}

//-----------------------------------------------------------------------------------

//Função que guarda num ficheiro a pontuação total de cada jogador
void fichaScore(){

    Tscore *score = new Tscore[100];
    int aux = 0;

    ifstream file("FichaJogadores.txt");

    if(!file.is_open()){
        cerr << "Erro: Nao foi possivel abrir o ficheiro!" << endl;
    }

    string nomeJ;
    int scoreJ;
    int vidasJ;
    string temaJ;
    string palavraJ;
    string escondidaJ;
    bool randTempJ;
    int tempJ;
    int difJ;

    while(file >> nomeJ >> scoreJ >> vidasJ >> temaJ >> palavraJ >> escondidaJ >> randTempJ >> tempJ >> difJ){
        bool encontrou = false;
        for(int i = 0; i < aux; i++){
            char auxNome[20];
            strcpy(auxNome,nomeJ.c_str());
            if(strcmp(auxNome,score[i].nome)==0){
                score[i].pontos += scoreJ;
                encontrou = true;
            }
        }
        if(encontrou == false){
            strcpy(score[aux].nome, nomeJ.c_str());
            //score[aux].nome = nomeJ;
            score[aux].pontos = scoreJ;
            aux++;
        }
    }
    file.close();

    ofstream scoreFile("FichaScores.txt",ios::trunc);

    if(!scoreFile.is_open()){
        cerr << "Erro: Nao foi possivel abrir o ficheiro!" << endl;
    }

    for(int j = 0; j < aux; j++){
        scoreFile << score[j].nome << ' ' << score[j].pontos << endl;
    }

    scoreFile.close();

    delete[] score;
}

//-----------------------------------------------------------------------------------

int comparaScore(const void *ficha1, const void *ficha2){
    return(((Tscore *)ficha2)->pontos - ((Tscore *)ficha1)->pontos );
}

//-----------------------------------------------------------------------------------

void ordenaFichaScore(){
    Tscore *tab = new Tscore[100];
    int aux = 0;

    ifstream file("FichaScores.txt");

    if(!file.is_open()){
        cerr << "Erro: Nao foi possivel abrir o ficheiro!" << endl;
    }

    string nome1;
    int score1;

    while(file >> nome1 >> score1){
        strcpy(tab[aux].nome, nome1.c_str());
        //tab[aux].nome = nome1;
        tab[aux].pontos = score1;
        aux++;
    }

    file.close();

    qsort(tab, aux, sizeof(Tscore), comparaScore); //Ordena a struct

    ofstream scoreFile("FichaScores.txt",ios::trunc);

    if(!scoreFile.is_open()){
        cerr << "Erro: Nao foi possivel abrir o ficheiro!" << endl;
    }

    for(int j = 0; j < aux; j++){
        scoreFile << tab[j].nome << ' ' << tab[j].pontos << endl;
    }

    scoreFile.close();

    delete [] tab;
}

//-----------------------------------------------------------------------------------

void imprimeScore(){

    ifstream file("FichaScores.txt");

    if(!file.is_open()){
        cerr << "Erro: Nao foi possivel abrir o ficheiro!" << endl;
    }

    char nome[20];
    int score;

    cout << "*****Nomes*****||*****Score*****" << endl;
    while(file >> nome >> score){
        cout << left << setw(18) << nome << score << endl;
    }

    file.close();
}
