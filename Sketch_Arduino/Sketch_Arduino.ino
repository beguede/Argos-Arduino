int janela1 = 2; // Define ID Janela 1
int janela2 = 3; // Define ID Janela 2
int janela3 = 4; // Define ID Janela 3
int porta1 = 5; // Define ID Porta 1
int porta2 = 6; // Define ID Porta 2
int porta3 = 7; // Define ID Porta 3
int apagador1 = 8; // Define ID Apagador 1
int apagador2 = 9; // Define ID Apagador 2
int apagador3 = 10; // Define ID Apagador 3
int lampada1 = 11; // Define ID Lampada 1
int lampada2 = 12; // Define ID Lampada 2
int lampada3 = 13; // Define ID Lampada 3
int temperatura1 = 0; // Define ID Sensor Temperatura

//int sistema = 13; // Define ID Sistema

int l1atual = 0; //Status Apagador 1 Atual (PushButom)
int l2atual = 0; //Status Apagador 2 Atual (PushButom)
int l3atual = 0; //Status Apagador 3 Atual (PushButom)

int l1last = 0; //Status Apagador 1 Anterior (PushButom)
int l2last = 0; //Status Apagador 2 Anterior (PushButom)
int l3last = 0; //Status Apagador 3 Anterior (PushButom)

char val; //Caracter Recebido pela Porta Serial
String data = ""; //Data total recebida pela Porta Serial

int received = 0; // Valida se dado foi recebido com sucesso
int cnt = 0; // Conta caracteres a ser recebido
int error = 0; // Valor Incorreto

float temp;

void setup() {  
  
  pinMode(janela1, INPUT); //Entrada para Janela 1  - j1
  pinMode(janela2, INPUT); //Entrada para Janela 2  - j2
  pinMode(janela3, INPUT); //Entrada para Janela 3  - j3
  pinMode(porta1, INPUT); //Entrada para Porta 1   - p1
  pinMode(porta2, INPUT); //Entrada para Porta 2   - p2
  pinMode(porta3, INPUT); //Entrada para Porta 2   - p2
  pinMode(apagador1, INPUT); //Entrada para Apagador 1 - a1
  pinMode(apagador2, INPUT); //Entrada para Apagador 2 - a2
  pinMode(apagador3, INPUT); //Entrada para Apagador 3 - a3
  pinMode(lampada1, OUTPUT); //Saida para Lampada 1 - l1
  pinMode(lampada2, OUTPUT); //Saida para Lampada 2 - l2
  pinMode(lampada3, OUTPUT); //Saida para Lampada 3 - l3
  
//  pinMode(sistema, OUTPUT); //Saida Arduino/Manual
  
  Serial.begin(9600); //Define velocidade de comunicação
    	
//  digitalWrite(sistema, HIGH); //Seta o Sistema para o modo Arduino.
}

void loop() {
  received = 0;
  error = 0;
     
  pushbuttom(); //Função do Pushbuttom
  
  evento(); //Função Comunica Porta Serial
  
  delay(10); //Delay para o sistema funcionar
  
  //verificatemp(); //Verifica a Temperatura atual
  
  if ((received != 1) && (cnt > 0)) {
    portas();
  }
}

void evento() {
  
  while( Serial.available() ) //Aguarda enquanto tiver dados a serem enviados pela serial
  {
    val = Serial.read();    // Le a serial e grava no char 'val'
   
    if( val != ';' ) {      // 
      data += val;          // Adiciona o Valor a String 'data'
      cnt++;
      received = 1;
    }
    
    if ( val == ';' ) {
      data = "";
      cnt = 0;
    } 
  } 
}

void portas() {
  
//  readstatus("status", sistema);
  
  readstatus("l1", lampada1);
  readstatus("l2", lampada2);
  readstatus("l3", lampada3);
  readstatus("j1", janela1);
  readstatus("j2", janela2);
  readstatus("j3", janela3);
  readstatus("p1", porta1);
  readstatus("p2", porta2);
  readstatus("p3", porta3);
  
  writestatus("a10", lampada1, 0);
  writestatus("a11", lampada1, 1);
  writestatus("a20", lampada2, 0);
  writestatus("a21", lampada2, 1);
  writestatus("a30", lampada3, 0);
  writestatus("a31", lampada3, 1);
  
  readstatusanalog("t1", temperatura1);
  
  if (error == 0) {
    data = "";
    Serial.print("err");
  }
  cnt = 0;
}

void readstatus(String code, int name) {
  if (data == code) {
    Serial.print(code + digitalRead(name));
    error = 1;
    data = "";
  }
}

void writestatus(String code, int name, int value) {
  if (data == code) {
    digitalWrite(name, value);
    error = 1;
    data = "";
  }  
}

void readstatusanalog(String code, int name) {
  if (data == code) {
    //temp = ((5.0 * analogRead(name) * 100.0) / 1024);
    Serial.print(code + analogRead(name));
    //Serial.print("-");
    //Serial.print(temp);
    error = 1;
    data = "";
  }
}

void pushbuttom() {
  
  l1atual = digitalRead(apagador1);
  l2atual = digitalRead(apagador2);
  l3atual = digitalRead(apagador3);


if (l1atual != l1last) {
  
  if (digitalRead(lampada1))
    digitalWrite(lampada1, 0);
  else
    digitalWrite(lampada1, 1);
  
  l1last = l1atual;
}
/*  if (l1atual != l1last) {
    
    if (l1atual == 0) {
      if (digitalRead(lampada1)) {
        digitalWrite(lampada1, 0);
        l1last = 0;
      } else {
        digitalWrite(lampada1, 1);
        l1last = 0;
      }
    } else {
      l1last = l1atual;
    }
  } 
*/  
  if (l2atual != l2last) {
    
    if (l2atual == 0) {
      if (digitalRead(lampada2)) {
        digitalWrite(lampada2, 0);
        l2last = 0;
      } else {
        digitalWrite(lampada2, 1);
        l2last = 0;
      }
    } else {
      l2last = l2atual;
    }
  } 
  
  if (l3atual != l3last) {
    
    if (l3atual == 0) {
      if (digitalRead(lampada3)) {
        digitalWrite(lampada3, 0);
        l3last = 0;
      } else {
        digitalWrite(lampada3, 1);
        l3last = 0;
      }
    } else {
      l3last = l3atual;
    }
  }  
}

void verificatemp() {
  
    temp = analogRead(temperatura1);
    temp = temp * 0.48828125; // Cálculo para temperatura em ºC
    Serial.print("TEMPRATURE = ");
    Serial.print(temp);
    Serial.print(" C");
    Serial.println();
}
