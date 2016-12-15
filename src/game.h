#ifndef _GAME_H_
#define _GAME_H_

#include "Arduino.h"
#include "buzzer.h"

const int startDifficulty = 2000;

enum class State{
    waitPlayer,
    waitTurn,
    myTurn,
    waitKey
};

class Game{
private:
    State state;
    Buzzer buzzer;
    int currentOnPosition;
    int isServer;

    int timeoutMilis;
    int timeoutCounter;
    int perTurnDifficultyIncrease;
    int difficultyLimit;

public:
    Game(int isServer);

    State getCurrentState();

    void changeState(State state);

    /* Estado único para o servidor - Aguarda o apertar um botão */
    void waitPlayer();

    /* Estou esperando a minha vez */
    void waitTurn();

    /* Estado no qual o jogador recebe a vez e deve
    decidir o que fazer com ela */
    void myTurn();

    /* Passa a vez para o outro user */
    void changeTurn();

    /* Blink de um led aleatório */
    void blinkRandomLed();

    /* Espera o usuário apertar o botão ou timeout */
    void waitKey();

    /* Notifica o outro jogador que o jogo acabou */
    void resetGame();

    /* Fim de jogo */
    void gameOver();

    /* Sucesso em apertar o botão do led */
    void pressSuccess();

    /* Notifica o fim do jogo para o outro jogador */
    void notifyEndGame();

    /* Executa a função de estado atual */
    void runState();

};

#endif
