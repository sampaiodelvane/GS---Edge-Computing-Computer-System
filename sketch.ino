#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Definições de Pinos
#define FIRE_PIN    A0
#define SMOKE_PIN   A1
#define RED_LED     8
#define YELLOW_LED  9
#define GREEN_LED   10
#define BUZZER_PIN  11

// LCD I2C no endereço 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Variáveis de Controle de Temperatura
float tempAtual = 25.0; 
bool subindo = true;

void setup() {
  pinMode(RED_LED,    OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED,  OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  Serial.begin(9600);
  
  // Inicialização do LCD
  Wire.begin();
  lcd.init();
  lcd.backlight();
  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.print("TERRAVIS V1.0");
  delay(2000);
  lcd.clear();
  
  randomSeed(analogRead(A3));
}

void loop() {
  // 1. Simulação de Temperatura (9 a 50)
  float variacao = (random(5, 25) / 10.0); 
  
  if (subindo) {
    tempAtual += variacao;
    if (tempAtual >= 50.0) {
      tempAtual = 50.0;
      subindo = false;
    }
  } else {
    tempAtual -= variacao;
    if (tempAtual <= 9.0) {
      tempAtual = 9.0;
      subindo = true;
    }
  }

  // 2. Cálculo do Risco (Fórmula Python)
  float risco = 0;
  if (tempAtual >= 20.0) {
    risco = pow(2.71828, (0.15 * (tempAtual - 25.0)));
  }
  float riscoExibicao = (risco > 100.0) ? 100.0 : risco;

  // 3. Classificação do Nível de Risco
  String nivel = "";
  if (tempAtual > 40.0) {
    nivel = "CRITICO";
  } else if (tempAtual > 35.0) {
    nivel = "ALTO";
  } else if (tempAtual > 30.0) {
    nivel = "MEDIO";
  } else {
    nivel = "BAIXO";
  }

  // 4. Sensores de Emergência
  int fireValue = analogRead(FIRE_PIN);
  int smokeValue = analogRead(SMOKE_PIN);
  bool emergencia = (fireValue > 600) || (smokeValue > 600);

  // 5. Lógica de Alertas, LEDs e LCD
  lcd.clear();

  if (emergencia) {
    digitalWrite(RED_LED,    HIGH);
    digitalWrite(YELLOW_LED, LOW);
    digitalWrite(GREEN_LED,  LOW);
    tone(BUZZER_PIN, 1000);
    
    lcd.setCursor(0, 0);
    lcd.print("!! EMERGENCIA !!");
    lcd.setCursor(0, 1);
    if (fireValue > 600) lcd.print("FOGO DETECTADO  ");
    else lcd.print("FUMACA DETECTADA");
  } else {
    // LEDs baseados no nível (Ajuste Visual)
    if (nivel == "CRITICO" || nivel == "ALTO") {
      digitalWrite(RED_LED,    HIGH);
      digitalWrite(YELLOW_LED, LOW);
      digitalWrite(GREEN_LED,  LOW);
      tone(BUZZER_PIN, 800);
    } else if (nivel == "MEDIO") {
      digitalWrite(RED_LED,    LOW);
      digitalWrite(YELLOW_LED, HIGH);
      digitalWrite(GREEN_LED,  LOW);
      tone(BUZZER_PIN, 500);
    } else {
      digitalWrite(RED_LED,    LOW);
      digitalWrite(YELLOW_LED, LOW);
      digitalWrite(GREEN_LED,  HIGH);
      noTone(BUZZER_PIN);
    }

    // Exibição no LCD
    lcd.setCursor(0, 0);
    lcd.print("T:");
    lcd.print(tempAtual, 1);
    lcd.print("C R:");
    lcd.print(riscoExibicao, 1);
    lcd.print("%");
    
    lcd.setCursor(0, 1);
    lcd.print("NIVEL: ");
    lcd.print(nivel);
    
    // Log Serial Limpo (Apenas a linha de medida solicitada)
    Serial.print("Temperatura: "); Serial.print(tempAtual);
    Serial.print("C | Risco: "); Serial.print(riscoExibicao);
    Serial.print("% - "); Serial.println(nivel);
  }

  delay(1500);
}
