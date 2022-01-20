//************************************************THE CKICKEN TRAIL**************************************************************

#include <Adafruit_GFX.h>
#include <Arduino_ST7789_Fast.h>
#include <SPI.h>
#include <EEPROM.h>
#include "bitmap.h"

//ARQUIVO DAS FONTES
#include <Fonts/FreeMonoBoldOblique12pt7b.h>
#include <Fonts/FreeSansBoldOblique12pt7b.h>

//PINAGEM
#define selectSlave 13
#define dataControl 9
#define reset 8
#define largura 240
#define altura 240

//DEFINIÇAO DAS CORES
#define RED 0xF800
#define BLACK 0x0000
#define YELLOW 0xFFE0
#define WHITE 0xFFFF
#define BLUE 0x001F
#define RUA 0x8282
#define LINHA 0xE7E7


//botoes

const int BotaoSeta = 2;
const int BotaoEnter = 4;

const int BotaoCima = 12;
const int BotaoBaixo = 3;
const int BotaoDireita = 5;
const int BotaoEsquerda = 6;


//BOTAO UM E BOTAO DOIS
int setinha = 1;
int enter = 0;

//x e y da galinha
int xG = 0;
int yG = 90;

//vidas da galinha
int vida = 1;

//x  do fogao
int xF;

//x do milho
int xM;

int pontos = 0;

char alfabeto[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
char nome[4] = {'A', 'A', 'A', 'A'};

Arduino_ST7789 lcd = Arduino_ST7789(dataControl, reset);

void setup()
{
  Serial.begin(9600);
  lcd.begin();

  //DEFINE OS BOTOES COMO PULL UP
  pinMode(BotaoSeta, INPUT_PULLUP);
  pinMode(BotaoEnter, INPUT_PULLUP);
  pinMode(BotaoCima, INPUT_PULLUP);
  pinMode(BotaoBaixo, INPUT_PULLUP);
  pinMode(BotaoDireita, INPUT_PULLUP);
  pinMode(BotaoEsquerda, INPUT_PULLUP);


  //CHAMA A TELA INICIAL
  chamaTelaInicial();
  lcd.fillScreen(BLACK);

}

void loop()
{

  menu();

}

void chamaTelaInicial() {

  lcd.fillScreen();

  lcd.fillRect(0, 0, 240, 40, 0xE0E0);
  lcd.fillRect(0, 30, 240, 40, 0xE1E1);
  lcd.fillRect(0, 60, 240, 40, 0xE2E2);
  lcd.fillRect(0, 90, 240, 40, 0xE3E3);
  lcd.fillRect(0, 120, 240, 40, 0xE4E4);
  lcd.fillRect(0, 150, 240, 40, 0xE5E5);
  lcd.fillRect(0, 180, 240, 40, 0xE6E6);
  lcd.fillRect(0, 210, 240, 40, 0xE7E7);

  lcd.setTextSize(2);
  lcd.setFont(&FreeMonoBoldOblique12pt7b);
  lcd.setCursor(75, 60);
  lcd.print("THE");
  delay(1000);
  lcd.setCursor(30, 120);
  lcd.print("CHICKEN");
  delay(1000);
  lcd.setCursor(55, 180);
  lcd.print("TRAIL");
  lcd.setFont();

  delay(1000);

}

void menu() {

  ///botao controla a seta, que de acordo com o case mira na opcao correta
  if (digitalRead(BotaoSeta) == LOW) {
    delay(50);
    setinha += 1;

  } else if (setinha > 4) {
    delay(50);
    setinha = 1;

  }

  switch (setinha) {
    case 1:  // menu com a seta na primeira posição

      lcd.fillScreen();
      degrade1();

      lcd.setTextColor(BLACK); //define cor de fundo, atrás do texto
      lcd.setTextSize(3);
      lcd.setCursor(75, 50);
      lcd.print(">START");
      lcd.setCursor(80, 100);
      lcd.print("CREDIT");
      lcd.setCursor(90, 150);
      lcd.print("RANK");
      lcd.setCursor(90, 200);
      lcd.print("QUIT");
      delay(200);
      // loop para deixar o menu estático

      //case do menu
      while (setinha == 1) {
        // ao apertar o botão da seta ele quebra o laço de repettição e muda para a proxima posição da seta
        if (digitalRead(BotaoSeta) == LOW) {

     //entra jogo,ranking 
          break;
          // ao apertar o botão enter ele entra no menu
        } else if (digitalRead(BotaoEnter) == LOW) {
          entrar();
        }

      }
      break;

    case 2:  // menu com a seta na segunda posição

      lcd.fillScreen();
      degrade2();

      lcd.setTextColor(BLACK); //define cor de fundo, atrás do texto
      lcd.setTextSize(3);
      lcd.setCursor(85, 50);
      lcd.print("START");
      lcd.setCursor(75, 100);
      lcd.print(">CREDIT");
      lcd.setCursor(90, 150);
      lcd.print("RANK");
      lcd.setCursor(90, 200);
      lcd.print("QUIT");
      delay(200);

      while (setinha == 2) {
        // ao apertar o botão da seta ele quebra o laço de repettição e muda para a proxima posição da seta
        if (digitalRead(BotaoSeta) == LOW) {

          break;
          // ao apertar o botão enter ele entra no menu
        } else if (digitalRead(BotaoEnter) == LOW) {
          entrar();
        }

      }
      break;

    case 3:   // menu com a seta na terceira posição

      lcd.fillScreen();
      degrade1();

      lcd.setTextColor(BLACK); //define cor de fundo, atrás do texto
      lcd.setTextSize(3);
      lcd.setCursor(85, 50);
      lcd.print("START");
      lcd.setCursor(80, 100);
      lcd.print("CREDIT");
      lcd.setCursor(85, 150);
      lcd.print(">RANK");
      lcd.setCursor(90, 200);
      lcd.print("QUIT");
      delay(200);

      while (setinha == 3) {
       //troca o case 
        if (digitalRead(BotaoSeta) == LOW) {
          break;
        } 
       //chama menu  
        else if (digitalRead(BotaoEnter) == LOW) {
          entrar();
        }

      }
      break;

    case 4:  // menu com a seta na quarta posição

      lcd.fillScreen();
      degrade2();

      lcd.setTextColor(BLACK); //define cor de fundo, atrás do texto
      lcd.setTextSize(3);

      lcd.setCursor(85, 50);
      lcd.print("START");
      lcd.setCursor(80, 100);
      lcd.print("CREDIT");
      lcd.setCursor(90, 150);
      lcd.print("RANK");
      lcd.setCursor(85, 200);
      lcd.print(">QUIT");
      delay(200);


      while (setinha == 4) {
        // ao apertar o botão da seta ele quebra o laço de repettição e muda para a proxima posição da seta
        if (digitalRead(BotaoSeta) == LOW) {

          break;
          // ao apertar o botão enter ele entra no menu
        } else if (digitalRead(BotaoEnter) == LOW) {
          entrar();
        }

      }
      break;
  }
}
  //Funcao que entra na opcao de acordo com posicao da setinha
  void entrar() {

    switch (setinha) {
      case 1:
        chamaJOGO();
        break;

      case 2:
        chamaCREDIT();
        break;

      case 3:
        chamaRANK();
        break;

      case 4:
        chamaSAIR();
        break;

    }

  }

  void chamaCREDIT() {

    delay(100);
    lcd.fillScreen();

    lcd.fillRect(0, 0, 240, 40, 0xE0E0);
    lcd.fillRect(0, 40, 240, 40, 0x9090);
    lcd.fillRect(0, 80, 240, 40, 0xF4F4);
    lcd.fillRect(0, 120, 240, 40, 0x3535);
    lcd.fillRect(0, 160, 240, 40, 0x7777);
    lcd.fillRect(0, 200, 240, 40, 0x8888);

    lcd.setTextColor(WHITE);
    lcd.setTextSize(3);

    lcd.setCursor(60, 10);
    lcd.print("CREDITOS");
    lcd.setCursor(90, 45);
    lcd.print("Anna");
    lcd.setCursor(90, 85);
    lcd.print("Maju");
    lcd.setCursor(100, 125);
    lcd.print("Day");
    lcd.setCursor(75, 165);
    lcd.print("Thyago");
    lcd.setCursor(80, 205);
    lcd.print("Vitor");

  }

  void chamaRANK() {

    char nome0[4] = {'A', 'A', 'A', 'A'};
    char nome1[4] = {'A', 'A', 'A', 'A'};
    char nome2[4] = {'A', 'A', 'A', 'A'};

    delay(100);
    lcd.fillScreen();

    //funcao que faz o degrade na tela
    degrade1();

    //chama funcao que organiza a ordem dos pontos
    ranking(nome);

    lcd.setTextColor(WHITE);
    lcd.setTextSize(3);
    lcd.setCursor(65, 20);
    lcd.print("RANKING");

    lcd.setTextSize(2);

    // posicao 0,1,2,3 = nome  posicao = 4= pontuacao
    // posicao 5,6,7,8 = nome  posicao = 9= pontuacao
    // posicao 10,11,12,13 = nome  posicao = 14= pontuacao

    lcd.setCursor(100, 70);

    //Insere o nome do jogador com maior pontuacao
    for (int i = 0; i < 4; i++) {
      nome[i] = EEPROM.read(i);
      lcd.print(nome[i]);
    }
    //pontuacao do jogador
    lcd.setCursor(120, 93);
    lcd.print(EEPROM[4]);


    //Printa jogador com a segunda melhor pontuacao
    lcd.setCursor(100, 130);
    for (int i = 5; i < 9; i++) {
      nome1[i] = EEPROM.read(i);
      lcd.print(nome1[i]);
    }
    // printa a pontuacao do jogador
    lcd.setCursor(120, 153);
    lcd.print(EEPROM[9]);

    //printa jogador com a terceira melhor pontuacao
    lcd.setCursor(100, 190);
    for (int i = 9; i < 15; i++) {
      nome2[i] = EEPROM.read(i);
      lcd.print(nome2[i]);
    }
    // printa a pontuacao do jogador
    lcd.setCursor(120, 213);
    lcd.print(EEPROM[14]);

  }

  void chamaSAIR() {

    delay(100);
    lcd.fillScreen();

    lcd.fillRect(0, 0, 240, 40, 0xE0E0);
    delay(100);
    lcd.fillRect(0, 30, 240, 40, 0xC0C0);
    delay(100);
    lcd.fillRect(0, 60, 240, 40, 0xA0A0);
    delay(100);
    lcd.fillRect(0, 90, 240, 40, 0x8080);
    delay(100);
    lcd.fillRect(0, 120, 240, 40, 0x6060);
    delay(100);
    lcd.fillRect(0, 150, 240, 40, 0x4040);
    delay(100);
    lcd.fillRect(0, 180, 240, 40, 0x2020);
    delay(100);
    lcd.fillRect(0, 210, 240, 40, 0x0000);

    lcd.setTextColor(0xFFFF);
    lcd.setTextSize(3);
    lcd.setCursor(60, 70);
    delay(100);
    lcd.print("SAINDO");
    delay(200);
    lcd.print(".");
    delay(200);
    lcd.print(".");
    delay(200);
    lcd.print(".");
    delay(200);
    lcd.setCursor(10, 110);
    delay(100);
    lcd.print("VOLTE SEMPRE");
    delay(200);

    ///retorna a zero
    exit(0);

  }
  //-----------------------------------------JOGO----------------------------------
  void chamaJOGO() {

    setinha = 0;
    
    //controla funcionamento do jogo 
    vida = 1;
    
    pontos = 0;

    //Reseta posicao do personagem e obstaculo
    xG = 0;
    yG = 90;
    xF = 230;

    cenario();
    delay(50);

    //faz o jogo funcionar apartir disso 
    while (vida > 0) {
      
      jogo(xF, xM, &xG, &yG);
    }
  }

  void cenario() {

    lcd.fillScreen();

    lcd.fillRect(0, 0, 240, 40, 0x1F1F);
    lcd.fillRect(0, 30, 240, 40, 0x3F3F);
    lcd.fillRect(0, 60, 240, 40, 0x5F5F);
    lcd.fillRect(0, 90, 240, 40, 0x7F7F);
    lcd.fillRect(0, 120, 240, 40, 0x9F9F);
    lcd.fillRect(0, 150, 240, 40, 0xBFBF);

    lcd.fillRect(0, 90, 240, 120, BLACK);
    lcd.drawLine(0, 150, 240, 150, LINHA);
    lcd.fillRect(0, 210, 240, 100, RUA);

  }

  //limpa um pedaço da tela, com base na
  //na posição do objeto desenhado antes
  void limpa(int x, int y, int xx, int yy) {

    lcd.fillRect(x, y, xx, yy, BLACK);
    lcd.drawLine(0, 150, 200, 150, LINHA);

  }

  int jogo(int xF, int xM, int *xG, int *yG) {
    
    int t, j;
    
    //aleatoriza os objetos entre dois valores 
    // r==fogao , rr==milho 
    int r[2] = {90, 175};
    int rr[2] = {100, 185};

    t = random(0, 2);
    j = random(0, 2);

    // controla o fogão que vai de 210 a -30 
    for (xF = 210 ; xF >= -30; xF = xF - 30) {

      lcd.drawBitmap(xF, r[t], fogao, 15, 15, WHITE);
      delay(50);
      limpa(xF - 15, r[t], 30, 15);

      personagem(xG, yG);

      lcd.drawBitmap(205, 90, ninho, 35, 35, 0x4040);
      lcd.drawBitmap(205, 170, ninho, 35, 35, 0x4040);

      //compara as posições da galinha e dos fogoes
      if (*xG <= xF + 5 && *xG + 27 >= xF && *yG  == r[t]) {
        delay(20);
        vida = 0;
        gameOver();
        break;
      }

      if (*xG >= 210) {
        vida = 0;
        chamaTelaWin();1
        break;
      }

    }
    if (vida > 0) {
      for (xM = 210 ; xM >= -30; xM = xM - 20) {
        lcd.fillRect(xM, rr[j], 5, 5, WHITE);
        delay(50);
        limpa(xM - 5, rr[j], 10, 5);

        personagem(xG, yG);

        if (*xG <= xM + 5  && *xG + 20 >= xM && *yG  == rr[j] - 10) {
          pontos++;
          delay(100);
          lcd.fillRect(210, 10, 30, 20, 0x1F1F);
          lcd.setTextColor(WHITE);
          lcd.setTextSize(2);
          lcd.setCursor(120, 10);
          lcd.print("pontos:");
          lcd.setCursor(210, 10);
          lcd.print(pontos);
        }
      }
    }
  }

  int personagem(int *xG, int *yG) {

    if (*yG == 90 || *yG == 175) {
      if (*xG % 2 != 0) {

        lcd.drawBitmap(*xG, *yG, chicken1, 27, 29, WHITE);

      } else {

        lcd.drawBitmap(*xG, *yG, chicken, 27, 29, WHITE);

      }
    }

    if (digitalRead(BotaoDireita) == LOW) {

      delay(50);

      *xG = *xG + 15;

      if (*xG % 2 != 0) {

        limpa(*xG - 15, *yG, 30, 30);
        delay(50);
        lcd.drawBitmap(*xG, *yG, chicken1, 27, 29, WHITE);

      } else {

        limpa(*xG - 15, *yG, 30, 30);
        delay(50);
        lcd.drawBitmap(*xG, *yG, chicken, 27, 29, WHITE);

      }
    }

    if (digitalRead(BotaoEsquerda) == LOW) {

      delay(50);

      *xG = *xG - 15;

      if (*xG < 0) {
        *xG = 0;
      }

      if (*xG % 2 != 0) {

        limpa(*xG + 15, *yG, 30, 30);
        delay(50);
        lcd.drawBitmap(*xG, *yG, chicken1, 27, 29, WHITE);

      } else {

        limpa(*xG + 15, *yG, 30, 30);
        delay(50);
        lcd.drawBitmap(*xG, *yG, chicken, 27, 29, WHITE);

      }
    }


    if (digitalRead(BotaoCima) == LOW) {

      delay(50);

      *yG = 90;

      limpa(*xG, 175, 30, 30);

    }

    if (digitalRead(BotaoBaixo) == LOW) {

      delay(50);

      *yG = 175;

      limpa(*xG, 90, 30, 30);

    }

  }
///-----------------------------------------------EEPROM-----------------------------------------------------
  int armazenaEeprom(char nome[4]) {

    int aux;
    
    int troca;

    for (int i = 4; i < 15; i = i + 5) {

      aux = EEPROM.read(i);

      if (aux == 0 || pontos > aux) { //se na proxima posicao for igual a zero

        troca = EEPROM.read(i + 5);
        EEPROM.write(i + 10, troca);

        troca = EEPROM.read(i);
        EEPROM.write(i + 5, troca);

        EEPROM.write(i, pontos); //armazena pontos nessa posicao

        for (int j = i - 4; j < i; j++) {

          EEPROM.write(j, nome[j]);

        }
        return 0;
      }

    }
    lcd.fillScreen();
    degrade2();

    lcd.setTextColor(WHITE);
    lcd.setTextSize(3);
    lcd.setCursor(40, 70);
    lcd.print("CARREGANDO");
    lcd.drawRect(50, 130, 155, 40, WHITE);
    delay(300);
    lcd.fillRect(55, 132, 10, 35, WHITE);
    delay(300);
    lcd.fillRect(55, 132, 30, 35, WHITE);
    delay(300);
    lcd.fillRect(55, 132, 50, 35, WHITE);
    delay(300);
    lcd.fillRect(55, 132, 70, 35, WHITE);
    delay(300);
    lcd.fillRect(55, 132, 90, 35, WHITE);
    delay(300);
    lcd.fillRect(55, 132, 110, 35, WHITE);
    delay(300);
    lcd.fillRect(55, 132, 130, 35, WHITE);
    delay(600);
    lcd.fillRect(55, 132, 145, 35, WHITE);

  }

 int resetaRanking() {

    for (int i = 0; i < 20; i++) {

      EEPROM[i] = 0;

    }
  }

  int ranking(char nome[4]) {
    int t;
    int j;
    int troca;
    int indice_maior;
    int pontos[20];
    char nomeS[3][4];
    char trocA[999];

    for (int i = 4; i < 15; i = i + 5) {

      pontos[i] = EEPROM.read(i);


    }

    for (int i = 0; i < 3; i++) {

      for (int j = 0; j < 4; j++) {

        nomeS[i][j] = EEPROM[j];

      }
    }


    for (t = 4; t < 15; t += 5) {

      indice_maior = t;


      for (j = t + 5; j < 16; j += 5) {

        if (pontos[indice_maior] < pontos[j]) {

          indice_maior = j;


        }
      }

      troca =  pontos[t];
      pontos[t] = pontos[indice_maior];
      pontos[indice_maior] = troca;

      strcpy(trocA, nomeS[t]);
      strcpy(nomeS[t], nomeS[indice_maior]);
      strcpy(nomeS[indice_maior], trocA);

    }


    for (int i = 4; i < 15; i = i + 5) {

      EEPROM.write(i, pontos[i]);

    }
    
    for (int t = 0; t < 3; t++) {
      
      for (int i = 4; i < 15; i = i + 5) {

        for (int j = i - 4; j < i; j++) {

          EEPROM.write(j, nomeS[t][j]);

        }
      }
    }

  }

  void chamaTelaWin() {

    lcd.fillScreen();
    lcd.fillRect(0, 0, 240, 40, 0xE0E0);
    lcd.fillRect(0, 40, 240, 40, 0xE1E1);
    lcd.fillRect(0, 80, 240, 40, 0xE2E2);
    lcd.fillRect(0, 120, 240, 40, 0xE3E3);
    lcd.fillRect(0, 160, 240, 40, 0xE4E4);
    lcd.fillRect(0, 200, 240, 40, 0xE5E5);

    lcd.setTextSize(2);
    lcd.setTextColor(WHITE);

    lcd.setCursor(80, 35);
    delay(100);
    lcd.setFont(&FreeSansBoldOblique12pt7b);
    lcd.print("WIN");
    lcd.setFont();

    lcd.drawBitmap(70, 80, win, 120, 120, WHITE);

    delay(2500);
    cadastroPlayer(nome, alfabeto);

  }

  int cadastroPlayer(char nome[4], char alfabeto[26]) {

    int i, pos;
    int controle_posicao = 90;

    lcd.fillScreen();
    lcd.fillRect(0, 0, 240, 40, 0xE0E0);
    lcd.fillRect(0, 30, 240, 40, 0xE1E1);
    lcd.fillRect(0, 60, 240, 40, 0xE2E2);
    lcd.fillRect(0, 90, 240, 40, 0xE3E3);
    lcd.fillRect(0, 120, 240, 40, 0xE4E4);
    lcd.fillRect(0, 150, 240, 40, 0xE5E5);
    lcd.fillRect(0, 180, 240, 40, 0xE6E6);
    lcd.fillRect(0, 210, 240, 40, 0xE7E7);

    lcd.setCursor(30, 20);
    lcd.setTextSize(2);
    lcd.print("INSIRA SEU NICK");

    lcd.setTextSize(3);
    i = 0;
    pos = -1;
    while (i < 4) {
      lcd.setCursor(controle_posicao, 150);
      lcd.print('-');
      lcd.setCursor(controle_posicao, 120);
      if (digitalRead(BotaoEnter) == LOW) {
        lcd.fillRect(controle_posicao, 120, 15, 21, 0xE4E4);
        pos += 1;
        if (pos > 25) {
          pos = 0;
        }
        nome[i] = alfabeto[pos];
        lcd.setCursor(controle_posicao, 120);
        lcd.print(nome[i]);
      } else if (digitalRead(BotaoSeta) == LOW) {
        i++;
        controle_posicao += 20;
        pos = -1;

      }
      delay(300);

    }

    armazenaEeprom(nome);

  }

  void gameOver() {
    lcd.fillScreen();

    lcd.fillRect(0, 0, 240, 40, 0xE0E0);
    lcd.fillRect(0, 40, 240, 40, 0xE1E1);
    lcd.fillRect(0, 80, 240, 40, 0xE2E2);
    lcd.fillRect(0, 120, 240, 40, 0xE3E3);
    lcd.fillRect(0, 160, 240, 40, 0xE4E4);
    lcd.fillRect(0, 200, 240, 40, 0xE5E5);


    lcd.setTextSize(1);
    lcd.setTextColor(WHITE);

    lcd.setCursor(50, 60);
    delay(100);
    lcd.setFont(&FreeSansBoldOblique12pt7b);
    lcd.print("GAME OVER");
    lcd.setFont();

    lcd.drawBitmap(60, 100, frito, 120, 120, WHITE);

    delay(2500);
    cadastroPlayer(nome, alfabeto);
  }

  void degrade1() {
    lcd.fillRect(0, 0, 240, 40, 0xE7E7);
    lcd.fillRect(0, 30, 240, 40, 0xE6E6);
    lcd.fillRect(0, 60, 240, 40, 0xE5E5);
    lcd.fillRect(0, 90, 240, 40, 0xE4E4);
    lcd.fillRect(0, 120, 240, 40, 0xE3E3);
    lcd.fillRect(0, 150, 240, 40, 0xE2E2);
    lcd.fillRect(0, 180, 240, 40, 0xE1E1);
    lcd.fillRect(0, 210, 240, 40, 0xE0E0);
  }
  void degrade2() {
    lcd.fillRect(0, 0, 240, 40, 0xE0E0);
    lcd.fillRect(0, 30, 240, 40, 0xE1E1);
    lcd.fillRect(0, 60, 240, 40, 0xE2E2);
    lcd.fillRect(0, 90, 240, 40, 0xE3E3);
    lcd.fillRect(0, 120, 240, 40, 0xE4E4);
    lcd.fillRect(0, 150, 240, 40, 0xE5E5);
    lcd.fillRect(0, 180, 240, 40, 0xE6E6);
    lcd.fillRect(0, 210, 240, 40, 0xE7E7);

  }
