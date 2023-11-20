#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <vector>

#define NOME_TAMANHO 50

using namespace std;

struct Jogador {
    char nome[NOME_TAMANHO];
    int pontuacao;
};

void adicionaAoRanking(vector<Jogador>& ranking, const char nome[], int pontuacao) {
    Jogador jogador;
    strncpy(jogador.nome, nome, NOME_TAMANHO - 1);
    jogador.nome[NOME_TAMANHO - 1] = '\0';
    jogador.pontuacao = pontuacao;
    ranking.push_back(jogador);
}

void exibeRanking(vector<Jogador>& ranking) {
    cout << "\n=== RANKING ===\n";
    for (size_t i = 0; i < ranking.size(); ++i) {
        cout << ranking[i].nome << ": " << ranking[i].pontuacao << " ponto(s)\n";
    }
}

void menuInicial(vector<Jogador>& ranking);

void limpaTela() {
    system("CLS");
}

void iniciaTabuleiro(char tabuleiro[3][3]) {
    int linha, coluna;
    for (linha = 0; linha < 3; linha++) {
        for (coluna = 0; coluna < 3; coluna++) {
            tabuleiro[linha][coluna] = '-';
        }
    }
}

void exibeTabuleiro(char tabuleiro[3][3]) {
    int linha, coluna;
    cout << "\n";
    for (linha = 0; linha < 3; linha++) {
        for (coluna = 0; coluna < 3; coluna++) {
            cout << tabuleiro[linha][coluna];
        }
        cout << "\n";
    }
}

int confereTabuleiro(char tabuleiro[3][3]) {
    int linha, coluna;

    for (linha = 0; linha < 3; linha++) {
        if (tabuleiro[linha][0] == 'X' && tabuleiro[linha][0] == tabuleiro[linha][1] && tabuleiro[linha][1] == tabuleiro[linha][2]) {
            return 1;
        } else if (tabuleiro[linha][0] == 'O' && tabuleiro[linha][0] == tabuleiro[linha][1] && tabuleiro[linha][1] == tabuleiro[linha][2]) {
            return 2;
        }
    }

    for (coluna = 0; coluna < 3; coluna++) {
        if (tabuleiro[0][coluna] == 'X' && tabuleiro[0][coluna] == tabuleiro[1][coluna] && tabuleiro[1][coluna] == tabuleiro[2][coluna]) {
            return 1;
        } else if (tabuleiro[0][coluna] == 'O' && tabuleiro[0][coluna] == tabuleiro[1][coluna] && tabuleiro[1][coluna] == tabuleiro[2][coluna]) {
            return 2;
        }
    }

    if (tabuleiro[0][0] != '-' && tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2]) {

        if (tabuleiro[0][0] == 'X') {
            return 1;
        } else {
            return 2;
        }
    }

    if (tabuleiro[0][2] != '-' && tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][0]) {

        if (tabuleiro[0][2] == 'X') {
            return 1;
        } else {
            return 2;
        }
    }

    return 0;
}

void exibeInstrucoes() {
    cout << "\nMapa de Posicoes:";
    cout << "\n 7 | 8 | 9";
    cout << "\n 4 | 5 | 6";
    cout << "\n 1 | 2 | 3";
}

void jogo(string nomeDoJogadorUm, string nomeDoJogadorDois, int pontuacaoJogadorUm, int pontuacaoJogadorDois, vector<Jogador>& ranking) {
    string nomeDoJogadorAtual;
    char tabuleiro[3][3];
    int linha, coluna;
    int linhaJogada, colunaJogada, posicaoJogada;
    int estadoDeJogo = 1;
    int turnoDoJogador = 1;
    int rodada = 0;
    int opcao;
    bool posicionouJogada;

    iniciaTabuleiro(tabuleiro);

    while (rodada < 9 && estadoDeJogo == 1) {

        limpaTela();

        cout << "\nRodada:" << rodada << "\n";
        cout << "Pontuacao:" << nomeDoJogadorUm << " " << pontuacaoJogadorUm << " x " << pontuacaoJogadorDois << " " << nomeDoJogadorDois;

        exibeTabuleiro(tabuleiro);

        exibeInstrucoes();

        if (turnoDoJogador == 1) {
            nomeDoJogadorAtual = nomeDoJogadorUm;
        } else {
            nomeDoJogadorAtual = nomeDoJogadorDois;
        }

        posicionouJogada = false;

        int posicoes[9][2] = {{2, 0}, {2, 1}, {2, 2}, {1, 0}, {1, 1}, {1, 2}, {0, 0}, {0, 1}, {0, 2}};

        while (posicionouJogada == false) {
            cout << "\n" << nomeDoJogadorAtual << "Digite uma posicao conforme o mapa acima:";
            cin >> posicaoJogada;

            linhaJogada = posicoes[posicaoJogada - 1][0];
            colunaJogada = posicoes[posicaoJogada - 1][1];

            if (tabuleiro[linhaJogada][colunaJogada] == '-') {
                posicionouJogada = true;

                if (turnoDoJogador == 1) {
                    tabuleiro[linhaJogada][colunaJogada] = 'X';
                    turnoDoJogador = 2;
                } else {
                    tabuleiro[linhaJogada][colunaJogada] = 'O';
                    turnoDoJogador = 1;
                }
            }
        }

        if (confereTabuleiro(tabuleiro) == 1) {
            cout << "O jogador X venceu";
            pontuacaoJogadorUm++;
            adicionaAoRanking(ranking, nomeDoJogadorUm.c_str(), pontuacaoJogadorUm);
            estadoDeJogo = 0;
        } else if (confereTabuleiro(tabuleiro) == 2) {
            cout << "O jogador O venceu";
            pontuacaoJogadorDois++;
            adicionaAoRanking(ranking, nomeDoJogadorDois.c_str(), pontuacaoJogadorDois);
            estadoDeJogo = 0;
        }

        rodada++;
    }

    exibeTabuleiro(tabuleiro);
    cout << "Fim	 de jogo";
    cout << "\nO que deseja fazer?";
    cout << "\n1-Continuar Jogando";
    cout << "\n2-Menu Inicial";
    cout << "\n3-Sair";
    cin >> opcao;
    if (opcao == 1) {
        jogo(nomeDoJogadorUm, nomeDoJogadorDois, pontuacaoJogadorUm, pontuacaoJogadorDois, ranking);
    } else if (opcao == 2) {
        menuInicial(ranking);
    }
}

void menuInicial(vector<Jogador>& ranking) {
    int opcao = 0;
    string nomeDoJogadorUm, nomeDoJogadorDois;

    while (opcao < 1 || opcao > 3) {
        limpaTela();
        cout << "Bem vindo ao Jogo da Velha\n";
        cout << "1 - Jogar\n";
        cout << "2 - Exibir Ranking\n";
        cout << "3 - Sair\n";
        cout << "Escolha uma opcao e tecle ENTER: ";
        cin >> opcao;

        switch (opcao) {
            case 1:
                cout << "Digite o nome do jogador 1: ";
                cin >> nomeDoJogadorUm;

                cout << "Digite o nome do jogador 2: ";
                cin >> nomeDoJogadorDois;

                jogo(nomeDoJogadorUm, nomeDoJogadorDois, 0, 0, ranking);
                break;
            case 2:
                exibeRanking(ranking);
                break;
        }
    }
}

int main() {
    vector<Jogador> ranking;
    menuInicial(ranking);
    return 0;
}


