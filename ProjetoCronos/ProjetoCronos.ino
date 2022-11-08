//Inclui as Bilbiotecas usadas para o uso do Display LCD
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

#define col 16 // Define o numero de colunas do LCD usado
#define lin 2 // Define o numero de linhas do LCD usado
#define ende 0x3F // Define o endereço do display LCD (pode varia de acordo com a fabricante do display)

// Declaração das variáveis usadas no código
int s = 0; // Variável usada para contagem de segundos
int count = 0; // Variavel usada para ativar ou desativar o timer

int button1 = 2; // Define o pino para o botão 1
int button2 = 3; // Define o pino para o botão 2
int button3 = 4; // Define o pino para o botão 3
int button4 = 5; // Define o pino para o botão 4

int hora, resto, minutos, segundos; // Define as variáveis de tempo

unsigned long int tempoAnterior1, tempoAnterior2, tempoAnterior3, tempoAnterior4, tempoAnteriorCont; // Cria as variáveis que serão usadas para contar o tempo de ativação dos botões

LiquidCrystal_I2C lcd_1(ende, col, lin); // Cria a variável do LCD

void setup()
{
  
  lcd_1.init(); // Inicia o LCD
  lcd_1.clear(); // Limpa o LCD 
  lcd_1.backlight(); //Ativa a luz de fundo do LCD
  
  

  pinMode(button1, INPUT_PULLUP); // button1 adiciona 1 min
  pinMode(button2, INPUT_PULLUP); // button2 adiciona 10 min
  pinMode(button3, INPUT_PULLUP); // button3 ativa play/pause do timer
  pinMode(button4, INPUT_PULLUP); // button4 reseta o timer

}
void timer(int tempo){ // Função para transformar os segundos (s) no formato hora:minutos:segundos 

  hora = tempo / 3600;
  resto = tempo % 3600;
  minutos = resto / 60;
  segundos = resto % 60;

}

void tela(){ // Função que vai mostrar na tela do LCD o timer no formato 00:00:00
  
  // Se o tempo em horas for menor que 10 vai printar o número 0 e o numero em seguida
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


void loop()
{
  lcd_1.setCursor(0, 0); // Aponta o "ponteiro de escrita" do LCD na COLUNA 0 LINHA 0
  lcd_1.print("Projeto Cronos"); // Escreve "Projeto Cronos" no local onde está o ponteiro
  lcd_1.setCursor(0, 1); // Aponmta o "ponteiro de escrita" do LCD na COLUNA 0 LINHA 1

  // A função millis() é um contador de tempo em milisegundos que inicia assim que o arduino é ligado
  if (millis() - tempoAnterior1 >= 200){ //Só vai entrar nessa condição se o tempo atual (millis()) menos a ultima marcação de tempo (tempoAnterior) for maior que 200 milisegundos
    tempoAnterior1 = millis(); // Cria uma marcação de tempo
    if (digitalRead(button1) == LOW){ // Quando o botão for pressionado vai interromper a eletricidade e entrará nessa condição
      s += 60; // Adiciona 60 segundos (1 minuto)
    }
  }
  if (millis() - tempoAnterior2 >= 200){
    tempoAnterior2 = millis();
    if (digitalRead(button2) == LOW){
      s += 10*60; // Adiciona 600 segundos (10 minutos)
    }
  }
  if (millis() - tempoAnterior3 >= 150){ // Vai trocar o valor da variavel count ao ser pressionado
    tempoAnterior3 = millis();
    if (digitalRead(button3) == LOW){ 
      if (count == 0){
        count = 1;
      }else{
        count = 0;
      }
    }
  }
  if (millis() - tempoAnterior4 >= 200){
    tempoAnterior4 = millis();
    if (digitalRead(button4) == LOW){ // Faz o tempo ir para 00 e transforma a Variável count em 0 (pausando o timer)
      s = 0;
      count = 0;
      lcd_1.clear(); // Limpar o LCD
    }
  }

  if (count == 1){ // Caso a variavel count seja 1...
    if (s > 0){
      if (millis() - tempoAnteriorCont >= 1000){ // VAi entrar nessa condição a cada 1000 milisegundos (1 segundo)...
        tempoAnteriorCont = millis();
        s--; // E diminuirá nossa variável de tempo (s) em 1
        if (s == 0){
          count = 0; // Ao chegar em 0 vai desativar o contador
        }
      }
    }
  }

  timer(s); //Chama a função timer()
  tela(); // Chama a função tela()

 
 
}
