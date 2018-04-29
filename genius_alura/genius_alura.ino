#define LED_VERMELHO 4
#define BOTAO_VERMELHO 10

void setup() {
  Serial.begin(9600);
  pinMide(LED_VERMELHO,OUTPUT);

  pinMode(BOTAO_VERMELHO,INPUT_PULLUP);

  digitalWrite(LED_VERMELHO,HIGH);
  delay(1000);
  digitalWrite(LED_VERMELHO,LOW);
}

void loop() {
  int estadoBotao = digitalRead(BOTAO_VERMELHO);
  Seriail.println(estadoBotao);
  delay(500);
}

