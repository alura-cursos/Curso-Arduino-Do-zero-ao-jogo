#define LED_VERDE 2
#define LED_AMARELO 3
#define LED_VERMELHO 4
#define LED_AZUL 5

#define BOTAO_VERDE 8
#define BOTAO_AMARELO 9
#define BOTAO_VERMELHO 10
#define BOTAO_AZUL 11

#define UM_SEGUNDO 1000
#define MEIO_SEGUNDO 500

#define TAMANHO_SEQUENCIA 4
#define INDEFINIDO -1
int sequenciaLuzes[TAMANHO_SEQUENCIA];


void setup(){
    Serial.begin(9600);
    iniciaPortas();
    iniciaJogo();
}

void iniciaJogo() {
  int potenciometro = analogRead(0);
  Serial.println(potenciometro);
  for(int indice = 0; indice < TAMANHO_SEQUENCIA; indice ++){
    sequenciaLuzes[indice] = sorteiaCor();
  }
}

int sorteiaCor() {
    return random(LED_VERDE, LED_AZUL + 1); // 2-5 (6)
}

void iniciaPortas(){
    pinMode(LED_VERDE, OUTPUT);
    pinMode(LED_AMARELO, OUTPUT);
    pinMode(LED_VERMELHO, OUTPUT);
    pinMode(LED_AZUL, OUTPUT);

    pinMode(BOTAO_VERDE, INPUT_PULLUP);
    pinMode(BOTAO_AMARELO, INPUT_PULLUP);
    pinMode(BOTAO_VERMELHO, INPUT_PULLUP);
    pinMode(BOTAO_AZUL, INPUT_PULLUP);
}


void loop(){
    Serial.println(checaRespostaJogador());
}

int checaRespostaJogador() {
  if(digitalRead(BOTAO_VERDE) == LOW) {
     return piscaLed(LED_VERDE);  
  }
  if(digitalRead(BOTAO_AMARELO) == LOW) {
     return piscaLed(LED_AMARELO);  
  }
  if(digitalRead(BOTAO_VERMELHO) == LOW) {
     return piscaLed(LED_VERMELHO);  
  }
  if(digitalRead(BOTAO_AZUL) == LOW) {
     return piscaLed(LED_AZUL);  
  }
  return INDEFINIDO;
}

int piscaLed(int portaLed){
  digitalWrite(portaLed,HIGH);
  delay(UM_SEGUNDO); 
  digitalWrite(portaLed,LOW);
  delay(MEIO_SEGUNDO);
  return portaLed;
}
