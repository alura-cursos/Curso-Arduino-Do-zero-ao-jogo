//int ledVermelho = 2;
//declarando a constante

#define LED_VERMELHO 2
#define UM_SEGUNDO 1000
#define MEIO_SEGUNDO 500

void setup(){
    Serial.begin(9600);
    pinMode(LED_VERMELHO, OUTPUT);
}

void loop(){
    Serial.println(LED_VERMELHO);
    piscaLed(LE D_VERMELHO); //estamos chamando a função
}

void piscaLed(int portaLed){
    digitalWrite(portaLed, HIGH);
    delay(UM_SEGUNDO);
    digitalWrite(portaLed, LOW);
    delay(MEIO_SEGUNDO);    
}
