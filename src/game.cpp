#include "game.h"
#include "pins.h"

Game::Game(int isServer){
    this->isServer = isServer;
    this->buzzer = Buzzer();
    this->state = State::waitTurn;

    this->timeoutMilis = 0;
    this->timeoutCounter = 0;
    this->perTurnDifficultyIncrease = 200;
    this->difficultyLimit = 300;
}

/************************************
* Helper methods                    *
*************************************/
State Game::getCurrentState(){
    return this->state;
}

void Game::changeState(State state){
    this->state = state;
}

void Game::runState(){
    switch (this->state) {
        case State::waitPlayer:
            this->waitPlayer();
            break;
        case State::waitTurn:
            this->waitTurn();
            break;
        case State::myTurn:
            this->myTurn();
            break;
        case State::waitKey:
            this->waitKey();
            break;
    }
}

/************************************
* State methods                     *
*************************************/
void Game::waitPlayer(){
    int user_started_game = LOW;
    digitalWrite(ledPins[0], HIGH);

    while(user_started_game == LOW){
        user_started_game = digitalRead(buttonsPins[0]);
    }

    digitalWrite(ledPins[0], LOW);
    this->changeState(State::myTurn);
}

/* Jogador recebe a vez e deve decidir o que fazer com ela */
void Game::myTurn(){
    int myRandomValue = random(1, 3);
    if(myRandomValue == 1){
        this->changeTurn();
        this->changeState(State::waitTurn);
    }else{
        $this->blinkRandomLed();
    }
}

/* Espera o usuário apertar o botão ou timeout */
void Game::waitKey(){
    int otherButton = (this->currentOnPosition - 1) * -1;
    int completedLoop = 0;
    int wasSuccessful = 0;

    while(completedLoop == 0){
        currentButtonInput = digitalRead(buttonsPins[this->currentOnPosition]);
        incorrectButtonInput = digitalRead(buttonsPins[otherButton]);

        if(incorrectButtonInput == HIGH){
            completedLoop = 1;
            wasSuccessful = 0;
        }else if(currentButtonInput == HIGH){
            completedLoop = 1;
            wasSuccessful = 1;
        }else{
            this->timeoutCounter += 1;
            delay(1);
            if(this->timeoutCounter > this->timeoutMilis){
                completedLoop = 1;
                wasSuccessful = 0;
            }
        }
    }

    if(wasSuccessful == 1){
        this->pressSuccess();
    }else{
        this->gameOver();
    }
}

/************************************
* Transition methods                *
*************************************/
/* Blink de um led aleatório */
void Game::blinkRandomLed(){
    this->currentOnPosition = random(0, 2);
    this->timeoutCounter = 0;
    digitalWrite(this->ledPins[this->currentOnPosition], HIGH);
    this->changeState(State::waitKey);
}

/* Sucesso em apertar o botão do led */
void Game::pressSuccess(){
    this->buzzer->playNumberedMelody(this->currentOnPosition, 250);
    this->changeState(State::myTurn);
}

/* Reinicia o jogo */
void Game::resetGame(){
    if(this->isServer){
        this->changeState(State::waitPlayer);
    }else{
        this->changeState(State::waitTurn);
    }
}

/* Fim de jogo */
void Game::gameOver(){
    this->buzzer->playNumberedMelody(3, 500);
    this->buzzer->playNumberedMelody(3, 500);
    this->buzzer->playNumberedMelody(3, 500);

    this->notifyEndGame();
    this->resetGame();
}

/************************************
* Request and network methods       *
*************************************/



/************************************
* TODO methods                      *
*************************************/
/* [Request and Network] Envia a requisição de fim de jogo */
void notifyEndGame(){
    // TODO: Enviar notificação para o outro jogador, sinalizando fim de jogo
}

/* [Request and Network] Passa a vez para o outro user */
void Game::changeTurn(){
    // TODO: Enviar requisição para o outro jogador, passando a vez
    // TODO: Entrar no estado wait Turn
}

/* [State] Estou esperando a minha vez */
void Game::waitTurn(){
    // TODO: Escutar requisições do tipo "você venceu"
    // Receber timeout atual
}
