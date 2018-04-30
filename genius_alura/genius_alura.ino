#define LED_VERDE 2
#define LED_AMARELO 3
#define LED_VERMELHO 4
#define LED_AZUL 5

#define INDEFINIDO -1

#define BUZZER 13

#define BOTAO_VERDE 8
#define BOTAO_AMARELO 9
#define BOTAO_VERMELHO 10
#define BOTAO_AZUL 11

#define UM_SEGUNDO 1000
#define MEIO_SEGUNDO 500

#define TAMANHO_SEQUENCIA 4

enum Estados {
  PRONTO_PARA_PROXIMA_RODADA,
  USUARIO_RESPONDENDO,
  JOGO_FINALIZADO_SUCESSO,
  JOGO_FINALIZADO_FALHA
};

int sequenciaLuzes[TAMANHO_SEQUENCIA];

int rodada = 0;

int ledsRespondidos = 0;

void setup() {
  Serial.begin(9600);
  
  iniciaPortas();
  iniciaJogo();
}

void iniciaPortas() {
  pinMode(LED_VERDE, OUTPUT);
  pinMode(LED_AMARELO, OUTPUT);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_AZUL, OUTPUT);

  pinMode(BOTAO_VERDE, INPUT_PULLUP);
  pinMode(BOTAO_AMARELO, INPUT_PULLUP);
  pinMode(BOTAO_VERMELHO, INPUT_PULLUP);
  pinMode(BOTAO_AZUL, INPUT_PULLUP);

  pinMode(BUZZER, OUTPUT);
}

void iniciaJogo() {
  
  int jogo = analogRead(0);
  randomSeed(jogo);

  for (int i = 0; i < TAMANHO_SEQUENCIA; i++) {
    sequenciaLuzes[i] = sorteiaCor();
  }
}

int sorteiaCor() {
  return random(LED_VERDE, LED_AZUL + 1);
}

void loop() {
  switch (estadoAtual()) {
    case PRONTO_PARA_PROXIMA_RODADA:
      Serial.println("Pronto para a proxima rodada");
      preparaNovaRodada();
      break;
    case USUARIO_RESPONDENDO:
      Serial.println("Usuario respondendo");
      processaRespostaUsuario();
      break;
    case JOGO_FINALIZADO_SUCESSO:
      Serial.println("Jogo finalizado com sucesso");
      jogoFinalizadoSucesso();
      break;
    case JOGO_FINALIZADO_FALHA:
      Serial.println("Jogo finalizado com falha");
      jogoFinalizadoFalha();
      break;
  }
  delay(MEIO_SEGUNDO);

}

void preparaNovaRodada() {
  rodada++;
  ledsRespondidos = 0;
  if (rodada <= TAMANHO_SEQUENCIA) {
    tocaLedsRodada();
  }
}

void processaRespostaUsuario() {
  int resposta = checaRespostaJogador();

  if (resposta == INDEFINIDO) {
    return;
  }
  
  if (resposta == sequenciaLuzes[ledsRespondidos]) {
    ledsRespondidos++; 
  } else {
    Serial.println("Sequencia errada");
    rodada = TAMANHO_SEQUENCIA + 2;
  }
}

int estadoAtual() {
  if (rodada <= TAMANHO_SEQUENCIA) {
    if (ledsRespondidos == rodada) {
      return PRONTO_PARA_PROXIMA_RODADA; 
    } else {
      return USUARIO_RESPONDENDO;
    }
  } else if (rodada == TAMANHO_SEQUENCIA + 1) {
    return JOGO_FINALIZADO_SUCESSO;
  } else {
    return JOGO_FINALIZADO_FALHA;
  }
}

void tocaLedsRodada() {
  for (int i = 0; i < rodada; i++) {
    piscaLed(sequenciaLuzes[i]);
  }
}

int checaRespostaJogador() {
  if (digitalRead(BOTAO_VERDE) == LOW) {
    return piscaLed(LED_VERDE);
  }
  if (digitalRead(BOTAO_AMARELO) == LOW) {
    return piscaLed(LED_AMARELO);
  }
  if (digitalRead(BOTAO_VERMELHO) == LOW) {
    return piscaLed(LED_VERMELHO);
  }
  if (digitalRead(BOTAO_AZUL) == LOW) {
    return piscaLed(LED_AZUL);
  }

  return INDEFINIDO;
}

void jogoFinalizadoSucesso() {
  piscaLed(LED_VERDE);
  piscaLed(LED_AMARELO);
  piscaLed(LED_VERMELHO);
  piscaLed(LED_AZUL);
  delay(MEIO_SEGUNDO);
}

void jogoFinalizadoFalha() {
  tocaSom(300);
  digitalWrite(LED_VERDE,HIGH);
  digitalWrite(LED_AMARELO,HIGH);
  digitalWrite(LED_VERMELHO,HIGH);
  digitalWrite(LED_AZUL,HIGH);
  delay(UM_SEGUNDO);
  digitalWrite(LED_VERDE,LOW);
  digitalWrite(LED_AMARELO,LOW);
  digitalWrite(LED_VERMELHO,LOW);
  digitalWrite(LED_AZUL,LOW);
  delay(MEIO_SEGUNDO);
}

int piscaLed(int portaLed) {

  verificaSomDoLed(portaLed);

  digitalWrite(portaLed,HIGH);
  delay(UM_SEGUNDO);
  digitalWrite(portaLed,LOW);
  delay(MEIO_SEGUNDO);

  return portaLed;
}

void tocaSom(int frequencia) {
  tone(BUZZER,frequencia, 100);
}

void verificaSomDoLed(int portaLed) {
  switch (portaLed) {
    case LED_VERDE:
      tocaSom(2000);
      break;
    case LED_AMARELO:
      tocaSom(2200);
      break;
    case LED_VERMELHO:
      tocaSom(2400);
      break;
    case LED_AZUL:
      tocaSom(2500);
      break;
  }
}

int calculaTempoLed() {
  int potenciometro = analogRead(1);
  Serial.println(potenciometro);
  return potenciometro;
}

