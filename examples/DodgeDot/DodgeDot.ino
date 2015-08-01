#include "Gamer.h"

int enemies[8],c,player,score;
int wait=20;
byte gameover[8] = {
  B10000001,
  B01000010,
  B00100100,
  B00011000,
  B00011000,
  B00100100,
  B01000010,
  B10000001
};
Gamer gamer;
void getwait(){
  while (not(gamer.isPressed(RIGHT))) {
    if (gamer.isPressed(UP)) {
      if (wait < 20) {
        wait+=1;
      }
      else {
        wait+=10;
      }
    }
    else if (gamer.isPressed(DOWN)) {
      if (wait < 30) {
        wait-=1;
      }
      else {
        wait-=10;
      }
    }
    gamer.showScore(wait);
    delay(10);
  }
  wait*=10;
}
void initvars(){
    for (c=2;c<8;c++) {
    enemies[c] = random(8);
  }
  enemies[0]=-1;
  enemies[1]=-1;
  player=0;
  score=0;
  getwait();
}
void setup(){
  gamer.begin();
  initvars();
  gamer.printImage(gameover);
  gamer.updateDisplay();
  gamer.clear();
  delay(200);
}
void tone(uint8_t n){
  gamer.playTone(n);
  delay(20);
  gamer.stopTone();
}
void loop(){
  if (score == 100) {
    gamer.printImage(win);
    delay(1000);
    initvars();
  }
  if (enemies[0] == player) {
    gamer.printImage(gameover);
    gamer.updateDisplay();
    delay(1000);
    gamer.showScore(score);
    gamer.updateDisplay();
    delay(1000);
    initvars();
  }
  if (gamer.isPressed(DOWN)) {player++;tone(100);}
  else if (gamer.isPressed(UP)) {player--;tone(200);}
  player = constrain(player,0,7);
  gamer.clear();
  gamer.display[0][player]=1;
  for (c=0;c<8;c++){
    gamer.display[c][enemies[c]]=1;
  }
  for (c=0;c<7;c++) {
    enemies[c]=enemies[c+1];
  }
  enemies[7] = random(8);
  gamer.updateDisplay();
  score+=1;
  delay(wait*10);
}
