#include <Adafruit_LiquidCrystal.h>

int s = 0;
int count = 0;
int button1 = 2;
int button2 = 3;
int button3 = 4;
int button4 = 5;
int hora, resto, minutos, segundos;

Adafruit_LiquidCrystal lcd_1(0);

void setup()
{
  lcd_1.begin(16, 2);
  

  pinMode(button1, INPUT); //button1 add 1 min
  pinMode(button2, INPUT); //button2 add 10 min
  pinMode(button3, INPUT); //button3 add play/pause min
  pinMode(button4, INPUT); //button4 reset

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

  if (digitalRead(button1) == HIGH){
    s += 60;
  }
  if (digitalRead(button2) == HIGH){
    s += 10*60;
  }
  if (digitalRead(button3) == HIGH){
    if (count == 0){
      count = 1;
    }else{
      count = 0;
    }
  }
  if (digitalRead(button4) == HIGH){
    s = 0;
    count = 0;
    lcd_1.clear();
  }

  if (count == 1){
    if (s > 0){
      delay(100);
      s = s-1;
    }
  }

  timer(s);

  lcd_1.print(hora);
  lcd_1.print(":");
  lcd_1.print(minutos);
  lcd_1.print(":");
  lcd_1.print(segundos);

 
 
}