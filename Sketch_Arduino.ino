int janela1 = 1;
int janela2 = 2;
int janela3 = 3;
int porta1 = 4;
int porta2 = 5;
int porta3 = 6;
int apagador1 = 7;
int apagador2 = 8;
int apagador3 = 9;
int lampada1 = 10;
int lampada2 = 11;
int lampada3 = 12;
int sistema = 13;

int l1atual = 0;
int l2atual = 0;
int l3atual = 0;

int l1last = 0;
int l2last = 0;
int l3last = 0;

char val;
String data = "";

int received = 0;
int cnt = 0;
int error = 0;

void setup() {  
  
  pinMode(1, INPUT); //Entrada para Janela 1  - j1
  pinMode(2, INPUT); //Entrada para Janela 2  - j2
  pinMode(3, INPUT); //Entrada para Janela 3  - j3
  pinMode(4, INPUT); //Entrada para Porta 1   - p1
  pinMode(5, INPUT); //Entrada para Porta 2   - p2
  pinMode(6, INPUT); //Entrada para Porta 3   - p3    
  pinMode(7, INPUT); //Entrada para Apagador 1 - a1
  pinMode(8, INPUT); //Entrada para Apagador 2 - a2
  pinMode(9, INPUT); //Entrada para Apagador 3 - a3
  pinMode(10, OUTPUT); //Saida para Lampada 1 - l1
  pinMode(11, OUTPUT); //Saida para Lampada 2 - l2
  pinMode(12, OUTPUT); //Saida para Lampada 3 - l3
  
  pinMode(13, OUTPUT); //Saida Arduino/Manual
  
  Serial.begin(9600);
    	
  digitalWrite(sistema, HIGH); //Seta o Sistema para o modo Arduino.
}

void loop() {
  received = 0;
  error = 0;
  
  l1atual = digitalRead(apagador1);
  l2atual = digitalRead(apagador2);
  l3atual = digitalRead(apagador3);
  
    if (l1atual != l1last) {
    
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

  
  evento();
  
  delay(10); //Delay para o sistema funcionar
  
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
  
  readstatus("status", sistema);
  
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
  
  if (error == 0) {
    data = "";
    Serial.println("Invalid Code");
  }
  cnt = 0;
}

void readstatus(String code, int name) {
  if (data == code) {
    Serial.println(digitalRead(name));
    error = 1;
    data = "";
  }
}

void writestatus(String code, int name, int value) {
  if (data == code) {
    digitalWrite(name, value);
    Serial.println("ok");
    error = 1;
    data = "";
  }  
}

