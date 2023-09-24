/* INCLUDES */
#include "WiFi.h"
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>
#include <Firebase_ESP_Client.h>
#include "addons/TokenHelper.h"
#include "addons/RTDBHelper.h"
#include <DHT.h>

/* DEFINES */
//Intervalo entre as checagens de novas mensagens
#define INTERVAL 1000
//Token do bot
// Vitor
#define BOT_TOKEN "6404416342:AAFJWGHQT3qH1YzAGvHvDrk1kQhHQGJIZ3E"
// Gustavo
//#define BOT_TOKEN "6335696437:AAEl7TtYYzItSwNtzE4Xc7xREfcYQsQCxMY"
#define DHTPIN 2 //Pino digital D2 (GPIO5) conectado ao DHT11
#define DHTTYPE DHT11 //Tipo do sensor DHT11
#define BLUE 16
#define GREEN 5
#define RED 4
// Insert Firebase project API Key
#define API_KEY "AIzaSyDziPSAgb1QUvBek2SbZohJ0cZx89sY9kY"
// Insert RTDB URLefine the RTDB URL
#define DATABASE_URL "https://projeto-a-d1cbc-default-rtdb.firebaseio.com/"
//Quantidade de usuários que podem interagir com o bot
#define SENDER_ID_COUNT 2


/* INICIALIZAÇÃO DE SERVIÇOS */
//FIREBASE
FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;
//Cliente para conexões seguras
WiFiClientSecure client;
//Objeto com os métodos para comunicarmos pelo Telegram
UniversalTelegramBot bot(BOT_TOKEN, client);
//SENSOR DE TEMPERATURA E UMIDADE
DHT dht(DHTPIN, DHTTYPE);


/* DEFINIÇÕES DE VARIÁVEIS GLOBAIS*/
const char* ssid = "SSID";
const char* password = "PASSWORD";
//Comandos aceitos
const String STATS_LED = "status led";
const String TEMPERATURA = "temperatura";
const String UMIDADE = "umidade";
const String STATS_GERAL = "status sala";
const String START = "/start";
unsigned long sendDataPrevMillis = 0;
bool signupOK = false;
int cor_led = 0;
//Tempo em que foi feita a última checagem
uint32_t lastCheckTime = 0;
uint32_t lastTime = 0;
//Ids dos usuários que podem interagir com o bot.
String validSenderIds[SENDER_ID_COUNT] = {"1980038306", "5385567687"};



/* FUNÇÕES */

String readTemp() {
  return String(dht.readTemperature());
}

String readHumi() {
  return String(dht.readHumidity());
}

String statusLed(){
  if (((dht.readTemperature() >= 22) && (dht.readTemperature() <= 26)) && ((dht.readHumidity() >= 50) && (dht.readHumidity() <= 70))) {
    return "verde";
  } else {
    return "vermelho";
  }
}

void setupWifi() {
  Serial.print("Conectando na rede ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  client.setCACert(TELEGRAM_CERTIFICATE_ROOT);
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.print("\nWiFi conectado. Endereço de IP: ");
  Serial.println(WiFi.localIP());
}

void setupFirebase() {
  config.api_key = API_KEY;
  config.database_url = DATABASE_URL;
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("Firebase conectado");
    signupOK = true;
  } else {
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }
  config.token_status_callback = tokenStatusCallback;
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void setupPin() {
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(RED, OUTPUT);
}

void setup() {
  dht.begin();
  Serial.begin(115200);
  Serial.println();

  setupWifi();
  setupFirebase();
  setupPin();
}

void loop() {
  uint32_t now = millis();
  if (now - lastCheckTime > INTERVAL) {
    //Coloca o tempo de útlima checagem como agora e checa por mensagens
    lastCheckTime = now;
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    handleNewMessages(numNewMessages);
  }

  if ((dht.readTemperature() >= 22 && dht.readTemperature() <= 26) && (dht.readHumidity() >= 50 && dht.readHumidity() <= 85)) {
    ligaLedVerde();
    enviaFirebase(1);
  }

  if (dht.readTemperature() < 22 || dht.readTemperature() > 26) {
    ligaLedVermelho();
    enviaFirebase(0);
    if (millis() - lastTime > 180000) {
      for (int i=0; i < SENDER_ID_COUNT; i++) {
        alertaTemperatura(validSenderIds[i]);
      }
    }
  }

  if (dht.readHumidity() < 50 || dht.readHumidity() > 87) {
    ligaLedVermelho();
    enviaFirebase(0);
    if (millis() - lastTime > 180000) {
      for (int i=0; i < SENDER_ID_COUNT; i++) {
        alertaUmidade(validSenderIds[i]);
      }
    }
  }

}

void ligaLedVerde() {
  digitalWrite(GREEN, HIGH);
  digitalWrite(BLUE, LOW);
  digitalWrite(RED, LOW);
}

void ligaLedVermelho() {
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
  digitalWrite(RED, HIGH);
}

void enviaFirebase(int cor_led) {
  Firebase.RTDB.setInt(&fbdo, "esp/led", cor_led);
  Firebase.RTDB.setString(&fbdo, "esp/temperatura", readTemp());
  Firebase.RTDB.setString(&fbdo, "esp/umidade", readHumi());
}

void handleNewMessages(int numNewMessages) {
  for (int i=0; i<numNewMessages; i++) //para cada mensagem nova
  {
    //id do chat 
    String chatId = String(bot.messages[i].chat_id);     
    //id do contato
    String senderId = String(bot.messages[i].from_id); 
    
    Serial.println("senderId: " + senderId); //mostra no monitor serial o id de quem mandou a mensagem

    boolean validSender = validateSender(senderId); //verifica se é o id de um remetente da lista de remetentes válidos

    //se não for um remetente válido
    if(!validSender) {
      bot.sendMessage(chatId, "Desculpe, você não possui permissão", "HTML");
      continue;
    }
    
    //texto que chegou
    String text = bot.messages[i].text;

    if (text.equalsIgnoreCase(START)) {
      ComandoStart(chatId, bot.messages[i].from_name); //mostra todas as mensagens que são aceitas
    }
    else if (text.equalsIgnoreCase(STATS_LED)) {
      ComandoLed(chatId); //envia mensagem apenas com a status do led
    }
    else if(text.equalsIgnoreCase(TEMPERATURA)) {
      ComandoTemperatura(chatId); //envia mensagem apenas com a temperatura
    }
    else if(text.equalsIgnoreCase(UMIDADE)) {
      ComandoUmidade(chatId); //envia mensagem apenas com a umidade
    }
    else if (text.equalsIgnoreCase(STATS_GERAL)) {
      ComandoStatus(chatId); //envia mensagem com o estado do relê, temperatura e umidade
    }
    else {
      ComandoNaoEncontrado(chatId); //mostra mensagem que a opção não é válida e mostra as opções
    }
  }
}

boolean validateSender(String senderId) {
  for(int i=0; i<SENDER_ID_COUNT; i++) {
    //Se o id do remetente faz parte do array retorna que é válido
    if(senderId == validSenderIds[i]) {
      return true;
    }
  }

  //Se o id do remetente não faz parte do array retorna que é inválido
  return false;
}

void ComandoStart(String chatId, String fromName) {
  //Mostra Olá e o nome do contato seguido dos comandos válidos
  String message = "<b>Olá " + fromName + ".</b>\n";
  message += comandosAceitos();
  bot.sendMessage(chatId, message, "HTML");
}

String comandosAceitos() {
  //String com a lista de comandos válidos
  String message = "Os comandos disponíveis são:\n\n";
  message += "<b>" + STATS_LED + "</b>: Para verificar o status do led\n";
  message += "<b>" + TEMPERATURA + "</b>: Para verificar apenas a temperatura\n";
  message += "<b>" + UMIDADE + "</b>: Para verificar apenas a umidade\n";
  message += "<b>" + STATS_GERAL + "</b>: Para verificar o status do led, temperatura e umidade";
  return message;
}

void ComandoLed(String chatId) {
  bot.sendMessage(chatId, "O led está <b>"+ statusLed() + "</b>", "HTML");
}

void ComandoTemperatura(String chatId) {
  String message = "A temperatura é de " + readTemp() + " °C";
  bot.sendMessage(chatId, message, "HTML");
}

void ComandoUmidade(String chatId) {
  String message = "A umidade é de " + readHumi() + "%";
  bot.sendMessage(chatId, message, "HTML");
}

void ComandoStatus(String chatId) {
  String message = "";
  message += "A temperatura é de " + readTemp() + " °C, ";
  message += "a umidade é de " + readHumi() + "% e ";
  message += "o led está " + statusLed();
  bot.sendMessage(chatId, message, "");
}

void ComandoNaoEncontrado(String chatId) {
  String message = "Comando não encontrado\n";
  message += comandosAceitos();
  bot.sendMessage(chatId, message, "HTML");
}

void alertaTemperatura(String chatId){
  String message = "Alerta de Temperatura!!";
  message += "A temperatura está " + readTemp() + " °C";
  bot.sendMessage(chatId, message, "");
}

void alertaUmidade(String chatId){
  String message = "Alerta de Umidade!!";
  message += "A umidade está " + readHumi() + "%";
  bot.sendMessage(chatId, message, "");
}