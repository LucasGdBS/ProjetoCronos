#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define col 16
#define lin 2
#define ende 0x3F

//#include <Adafruit_LiquidCrystal.h>

int s = 0;
int count = 0;
int button1 = 2;
int button2 = 3;
int button3 = 4;
int button4 = 5;
int hora, resto, minutos, segundos;

LiquidCrystal_I2C lcd_1(ende, col, lin);

void setup()
{
  Serial.begin(96000);
  lcd_1.init();
  lcd_1.clear();
  lcd_1.backlight();
  
  

  pinMode(button1, INPUT_PULLUP); //button1 add 1 min
  pinMode(button2, INPUT_PULLUP); //button2 add 10 min
  pinMode(button3, INPUT_PULLUP); //button3 add play/pause min
  pinMode(button4, INPUT_PULLUP); //button4 reset

}
void timer(int tempo){

  hora = tempo / 3600;
  resto = tempo % 3600;
  minutos = resto / 60;
  segundos = resto % 60;

}


void loop()
{
  lcd_1.setCursor(0, 0);
  lcd_1.print("Projeto Cronos");
  lcd_1.setCursor(0, 1);

  if (digitalRead(button1) == LOW){
    s += 60;
    Serial.println("A");
  }
  if (digitalRead(button2) == LOW){
    s += 10*60;
    Serial.println("B");
  }
  if (digitalRead(button3) == LOW){
    if (count == 0){
      count = 1;
    }else{
      count = 0;
    }
  }
  if (digitalRead(button4) == LOW){
    lcd_1.clear();
    s = 0;
    count = 0;

  }

  if (count == 1){
    if (s > 0){
      
      s = s-1;
    }
  }

  timer(s);

  /*lcd_1.print(hora);
  lcd_1.print(":");
  lcd_1.print(minutos);
  lcd_1.print(":");
  lcd_1.print(segundos);*/

  if (hora < 10){
    lcd_1.print(0);
    lcd_1.print(hora);
  }else{
    lcd_1.print(hora);
  }
  lcd_1.print(":");
  if (minutos < 10){
    lcd_1.print(0);
    lcd_1.print(minutos);
  }else{
    lcd_1.print(minutos);
  }
  lcd_1.print(":");
  if(segundos < 10){
    lcd_1.print(0);
    lcd_1.print(segundos);
  }else{
    lcd_1.print(segundos);
  }

 
 
}
