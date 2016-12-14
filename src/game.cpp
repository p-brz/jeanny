#include "game.h"
#include "pins.h"

Game::Game(){
    this->state = State::waitTurn;
}

State Game::getCurrentState(){
    return this->state;
}

void Game::changeState(State state){
    this->state = state;
}

void Game::waitPlayer(){
    int user_started_game = LOW;
    digitalWrite(ledPins[0], HIGH);

    while(user_started_game == LOW){
        user_started_game = digitalRead(buttonsPins[0]);
    }

    digitalWrite(ledPins[0], LOW);
    this->changeState(State::myTurn);
}

/* Estou esperando a minha vez */
void Game::waitTurn(){

}

/* Estado no qual o jogador recebe a vez e deve
   decidir o que fazer com ela */
void Game::myTurn(){
    int myRandomValue = random(1, 3);
    if(myRandomValue == 1){
        this->changeTurn();
        this->changeState(State::waitTurn);
    }else{
        $this->blinkRandomLed();
    }
}

/* Passa a vez para o outro user */
void Game::changeTurn(){

}

/* Blink de um led aleatório */
void Game::blinkRandomLed(){
    this->currentOnPosition = random(0, 2);

}

/* Espera o usuário apertar o botão ou timeout */
void Game::waitKey(){

}

/* Notifica o outro jogador que o jogo acabou */
void Game::resetGame(){

}

/* Fim de jogo */
void Game::gameOver(){

}

/* Sucesso em apertar o botão do led */
void Game::pressSuccess(){

}
