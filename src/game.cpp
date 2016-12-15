#include "game.h"
#include "pins.h"

#define INIT_TIMEOUT 4000

Game::Game(Network * peer)
    : peer(peer)
{
    //this->isServer = isServer;
    //this->buzzer = Buzzer;

    this->timeoutMilis = INIT_TIMEOUT;
    this->timeoutCounter = 0;
    this->perTurnDifficultyIncrease = 100;
    this->difficultyLimit = 350;
}

void Game::begin(){
    this->peer->setOnEvent([this](const char * evt, Object & obj){
        this->onEvent(evt, obj);
    });
}

void Game::onEvent(const char * evt, Object & obj){
    Serial.print("Received evt on game: ");
    Serial.println(evt);
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

void Game::turnOffAllLeds()
{
    for (int i = 0; i < 2; ++i) {
        digitalWrite(ledPins[i], LOW);
    }    
}

void Game::runState(){
    this->peer->update();
    
//    switch (this->state) {
//        case State::waitPlayer:
//            this->waitPlayer();
//            break;
//        case State::waitTurn:
//            this->waitTurn();
//            break;
//        case State::myTurn:
//            this->myTurn();
//            break;
//        case State::waitKey:
//            this->waitKey();
//            break;
//    }
    
//    if(state != State::waitKey){
//        turnOffAllLeds();
//    }
}

/************************************
* State methods                     *
*************************************/
void Game::waitPlayer(){
    
    int state = digitalRead(buttonsPins[0]);
    digitalWrite(ledPins[0], HIGH);
    if(startButtonPreviousState == -1){
        Serial.println("Waiting player");
        startButtonPreviousState = state;
    }
    
    // Stuck 1
    if(!(state == LOW && startButtonPreviousState == HIGH)){
        startButtonPreviousState = state;
        state = digitalRead(buttonsPins[0]);
        delay(20);
    }else{
        startButtonPreviousState = -1;
        Serial.println("Start game!");
        digitalWrite(ledPins[0], LOW);
        this->changeState(State::myTurn);
    }
}

/* Jogador recebe a vez e deve decidir o que fazer com ela */
void Game::myTurn(){
    Serial.println("My turn");
    int myRandomValue = random(1, 3);
    if(myTurnCount >= 1 &&  myRandomValue == 1){
        this->changeTurn();
        this->changeState(State::waitTurn);
    }else{
        this->blinkRandomLed();
        ++myTurnCount;
    }
}

/* Espera o usuário apertar o botão ou timeout */
void Game::waitKey(){
    int otherButton = (this->currentOnPosition - 1) * -1;
    int completedLoop = 0;
    int wasSuccessful = 0;

    delay(10);
    int currentButtonInput = digitalRead(buttonsPins[this->currentOnPosition]);
    int incorrectButtonInput = digitalRead(buttonsPins[otherButton]);

    if(incorrectButtonInput == HIGH){
        completedLoop = 1;
        wasSuccessful = 0;
    }else if(currentButtonInput == HIGH){
        completedLoop = 1;
        wasSuccessful = 1;
    }else{
//        Serial.print("Time: ");
//        Serial.print(timeoutCounter);
//        Serial.print("/");
//        Serial.println(timeoutMilis);
        
        
        this->timeoutCounter += 10;
        if(this->timeoutCounter > this->timeoutMilis){
            completedLoop = 1;
            wasSuccessful = 0;
        }
    }
    
    if(completedLoop == 1){
        if(wasSuccessful == 1){
            this->pressSuccess();
        }else{
            this->myTurnCount = 0;
            this->gameOver();
        }
    }
}

/************************************
* Transition methods                *
*************************************/
/* Blink de um led aleatório */
void Game::blinkRandomLed(){
    Serial.println("blinkRandomLed");
    
    this->currentOnPosition = random(0, 2);
    this->timeoutCounter = 0;
    digitalWrite(ledPins[this->currentOnPosition], HIGH);
    this->changeState(State::waitKey);
}

/* Sucesso em apertar o botão do led */
void Game::pressSuccess(){
     this->buzzer.playNumberedMelody(this->currentOnPosition, 250);
     turnOffAllLeds();
     delay(timeoutMilis / 4);
     
     if(timeoutMilis >= difficultyLimit){
        timeoutMilis -= perTurnDifficultyIncrease;
     }
     
     if(timeoutMilis < difficultyLimit){
        timeoutMilis = difficultyLimit;
     }
     
     this->changeState(State::myTurn);
}

/* Reinicia o jogo */
void Game::resetGame(){
    timeoutMilis = INIT_TIMEOUT;
    Serial.println("reset game!");
    
    if(this->isServer){
        this->changeState(State::waitPlayer);
    }else{
        this->changeState(State::waitTurn);
    }
}

/* Fim de jogo */
void Game::gameOver(){
    Serial.println("game over!!");
    
    this->buzzer.playNumberedMelody(3, 500);
    this->buzzer.playNumberedMelody(3, 500);
    this->buzzer.playNumberedMelody(3, 500);
    
    timeoutMilis = INIT_TIMEOUT;
    
    this->turnOffAllLeds();
    
    delay(300);
    
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
void Game::notifyEndGame(){
    Serial.println("notify end game!");
    // TODO: Enviar notificação para o outro jogador, sinalizando fim de jogo
    peer->notifyEndGame();
}

/* [Request and Network] Passa a vez para o outro user */
void Game::changeTurn(){
    // TODO: Enviar requisição para o outro jogador, passando a vez
    // TODO: Entrar no estado wait Turn
    
//    peer->sendChangeTurn(timeoutMilis);
}

/* [State] Estou esperando a minha vez */
void Game::waitTurn(){
    Serial.println("Waiting turn");
    // TODO: Escutar requisições do tipo "você venceu"
    // Receber timeout atual
    
    // Stuck 3
//    while(!peer->waitTurn(timeoutMilis)){
    
//    }
    myTurnCount = 0;
    this->changeState(State::myTurn);
}
