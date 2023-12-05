#include <Ultrasonic.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int echoPin = 6;  // PINO DIGITAL UTILIZADO PELO HC-SR04 ECHO(RECEBE)
const int trigPin = 7;  // PINO DIGITAL UTILIZADO PELO HC-SR04 TRIG(ENVIA)
const int echoPinb = 8; // PINO DIGITAL UTILIZADO PELO HC-SR04 ECHO(RECEBE)
const int trigPinb = 9; // PINO DIGITAL UTILIZADO PELO HC-SR04 TRIG(ENVIA)

#define movimento 0
#define entrar 1
#define sair 2

Ultrasonic ultrasonic(trigPin, echoPin);    // INICIALIZANDO OS PINOS DO ARDUINO
Ultrasonic ultrasonicb(trigPinb, echoPinb); // INICIALIZANDO OS PINOS DO ARDUINO

int pessoas = 0;
int acao = movimento;

void setup()
{
  pinMode(echoPin, INPUT);   // DEFINE O PINO COMO ENTRADA (RECEBE)
  pinMode(trigPin, OUTPUT);  // DEFINE O PINO COMO SAIDA (ENVIA)
  pinMode(echoPinb, INPUT);  // DEFINE O PINO COMO ENTRADA (RECEBE)
  pinMode(trigPinb, OUTPUT); // DEFINE O PINO COMO SAIDA (ENVIA)

  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Pessoas Na Sala");
  lcd.setCursor(0, 1);
  lcd.print("Presentes:");
  delay(1000);
}

void loop()
{
  bool estadoSensorFora = !digitalRead(echoPinb);
  bool estadoSensorDentro = !digitalRead(echoPin);

  digitalWrite(trigPin, HIGH);
  digitalWrite(trigPin, LOW);
  digitalWrite(trigPinb, HIGH);
  digitalWrite(trigPinb, LOW);

  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Pessoas Na Sala");

  if (acao == movimento)
  {
    // if usado para o sensor identificar que alguém está entrando
    if (!estadoSensorFora)
    {
      acao = entrar;
    }
    // if usado para o sensor identificar que alguém está saindo
    else if (!estadoSensorDentro)
    {
      acao = sair;
    }
  }

  if (!estadoSensorDentro && !estadoSensorFora)
  {
    lcd.setCursor(0, 1);
    lcd.print("Sai da frente");
    delay(6500);
  }

  // if usado para contabilizar que a pessoa tenha entrado na sala
  if (acao == entrar)
  {
    pessoas++;
    lcd.setCursor(0, 1);
    lcd.print(pessoas);
    delay(500);
    acao = movimento;
  }

  // if usado para contabilizar que a pessoa tenha saído da sala
  if (acao == sair)
  {
    pessoas--;
    lcd.setCursor(0, 1);
    lcd.print(pessoas);
    delay(500);
    acao = movimento;
  }

  // Exibição do total no display
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Pessoas Na Sala");
  lcd.setCursor(0, 1);
  lcd.print(pessoas);
  delay(50);
}