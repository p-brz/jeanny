#ifndef _GAME_H_
#define _GAME_H_

enum class State{
    waitPlayer,
    myTurn,
    waitTurn,
    waitKey
};

class Game{
private:
    State state;
    int currentOnPosition;
    int timeoutMilis;

public:
    Game();

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

};

#endif
