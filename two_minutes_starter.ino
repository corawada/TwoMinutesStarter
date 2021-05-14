#include"TFT_eSPI.h"
TFT_eSPI tft;

void setup() {
  tft.begin();
  tft.setRotation(1);

  pinMode(WIO_KEY_A, INPUT_PULLUP);
  pinMode(WIO_KEY_B, INPUT_PULLUP);
  pinMode(WIO_KEY_C, INPUT_PULLUP);

  tft.fillScreen(TFT_WHITE);
}

void debugLine(String text){
  tft.setTextSize(2);
  tft.fillRect(0,220,320,20, TFT_WHITE);
  tft.setTextColor(TFT_BLACK);
  tft.drawString(text, 0, 220);
}

void debug(String text){
  tft.setTextSize(2);
  tft.fillRect(0, 200, 320, 20, TFT_WHITE);
  tft.setTextColor(TFT_BLACK);
  tft.drawString(text, 0, 200);
}

//-----i-screen
void iscreen(){
  //--init--
  tft.setTextSize(2);
  tft.setTextColor(TFT_BLACK);
  tft.drawString("start ? ", 100, 100);
  debugLine("start : B");
  while (1){
    if (digitalRead(WIO_KEY_B)==LOW){
      delay(100);
      tft.setTextColor(TFT_WHITE);
      tft.drawString("start ? ", 100, 100);
      break;
    }
  }
}


//-----ro-screen
void roscreen(){
  //---init---
  tft.setTextSize(3);
  tft.setTextColor(TFT_BLACK);
  tft.drawString("/2min", 220, 140);
  debugLine("");
  
  //--main--
  int i;
  for (i=120; i>=1; i--){
    tft.setTextSize(6);
    tft.setTextColor(TFT_BLACK);
    tft.drawString(String(i), 100, 100);
    delay(1000);
    tft.setTextColor(TFT_WHITE);
    tft.drawString(String(i), 100, 100);
  }
  
  // ---end---
  tft.setTextSize(3);
  tft.setTextColor(TFT_WHITE);
  tft.drawString("/2min", 220, 140);
  debugLine("next : B");

  while (1){
    tft.setTextSize(6);
    tft.setTextColor(TFT_BLACK);
    tft.drawString("END", 100, 100);
    if (digitalRead(WIO_KEY_B)==LOW){
      tft.setTextColor(TFT_WHITE);
      tft.drawString("END", 100, 100);
      delay(500);
      break;
    }
    delay(50);
  }
}

int select_ha(int count){
  tft.setTextColor(TFT_WHITE);
  tft.drawString("@", 80, 100);
  tft.drawString("@", 80, 120);
  tft.drawString("@", 80, 140);
  tft.setTextColor(TFT_BLACK);
  tft.drawString("", 80, 100 + count*20);
  while (1){
    if (digitalRead(WIO_KEY_B)==LOW){
      // debugLine((String)result);
      return 1;
    }
    if (digitalRead(WIO_KEY_A) == LOW){
      //count += 1;
      //debug(String(result + 1));
      //delay(250);
      //select_ha(count%3);
      return 0;
    }
    if (digitalRead(WIO_KEY_C) == LOW){
      return 2;
    }
  }
}

//-----ha-screen
int hascreen(){
  //---init---
  tft.setTextSize(2);
  tft.setTextColor(TFT_BLACK);
  tft.drawString("A : 2 minutes", 100, 100);
  tft.drawString("B : continue", 100, 120);
  tft.drawString("C : EXIT", 100, 140);
  debugLine("select your choice");

  int count;
  //  count = 0;
  int result;
  result = select_ha(0);
  delay(50);
  
  //---end---
  tft.setTextSize(2);
  tft.setTextColor(TFT_WHITE);
  tft.drawString("@", 80, 100);
  tft.drawString("@", 80, 120);
  tft.drawString("@", 80, 140);
  tft.drawString("A : 2 minutes", 100, 100);
  tft.drawString("B : continue", 100, 120);
  tft.drawString("C : EXIT", 100, 140);

  delay(200);
  return result;
}

//-----niscreen
void niscreen(){
  debugLine("stop timer : B");
  
  //--main--
  int i;
  i = 0;
  while (1){
    tft.fillRect(0,100,319,100,TFT_WHITE);
    tft.setTextColor(TFT_BLACK);
    tft.setTextSize(6);
    tft.drawString(String(i), 100, 100);
    delay(999);
    i += 1;
    if (digitalRead(WIO_KEY_B)==LOW){
      delay(250);
      debugLine("exit : A");
      break;
    }
  }
  
  while (1){
    if (digitalRead(WIO_KEY_A)==LOW){
      break;
    }
  }

  hoscreen();
  delay(200);
  
}

//-----hoscreen
void hoscreen(){
  tft.fillScreen(TFT_BLACK);
  while(1){
    tft.setTextSize(1);
    tft.setTextColor(TFT_WHITE);
    tft.drawString(".", 0, 0);
    delay(100);
    tft.setTextColor(TFT_BLACK);
    tft.drawString(".", 0, 0);
    delay(100);
    if (digitalRead(WIO_KEY_A)==LOW){
      tft.fillScreen(TFT_WHITE);
      break;
    }
  }
}

void two_minutes_starter(){
  tft.fillRect(0, 100, 320, 140, TFT_WHITE);

  tft.setTextColor(TFT_BLACK);
  tft.setTextSize(2);
  tft.drawString("2 minutes starter!", 50, 40);
  
  iscreen();

  roscreen();

  int select;
  select = hascreen();
  
  if (select == 0){
  }
  else if (select == 1){
    niscreen();
  }
  else if (select == 2){
    hoscreen();
  }
}


void loop() {
  two_minutes_starter();
}
