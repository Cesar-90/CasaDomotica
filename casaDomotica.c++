// Declaramos los pines
const int botonPin = 7;    // Pin del botón
const int ledPin1 = 12;     // Pin del LED (o salida)

//CRK foto celda
const int fotoceldaPin = A0;    // Pin de la fotocelda
const int ledPin2 = 13;          // Pin del LED o salida
const int umbral1 = 700;  

//CRK humedad
const int humedadPin = A1;      // Pin del sensor de humedad
const int salidaPin1 = 8;        // Pin de salida
const int umbral2 = 93;

//CRK TEMP
const int tempPin = A2;        // Pin del sensor de temperatura
const int salidaPin2 = 4;       // Pin de salida

const int umbral = 100;         // Umbral para activar la salida a temperaturas superiores a 30°C (aprox.)

///CRK PIR
const int pirPin = 2;          // Pin de entrada del PIR
const int salidaPin = 3;       // Pin de salida

// Variables para almacenar el estado
bool estadoLed = LOW;      // Estado inicial del LED
bool estadoBoton;          // Estado actual del botón
bool ultimoEstadoBoton = LOW;  // Último estado del botón

void setup() {
  pinMode(botonPin, INPUT);     // Configuramos el pin del botón como entrada
  pinMode(ledPin1, OUTPUT);      // Configuramos el pin del LED como salida
  
  //CRK luz
   pinMode(ledPin2, OUTPUT);      // Configuramos el pin del LED como salida
  Serial.begin(9000);           // Inicia la comunicación serial para monitoreo
  
  //CR Humedad
  pinMode(salidaPin1, OUTPUT);   // Configuramos el pin de salida como salida
  Serial.begin(90);
  
  //CRK Temperatura
    pinMode(salidaPin2, OUTPUT);  // Configuramos el pin de salida como salida
  Serial.begin(9000);          // Inicia la comunicación serial para monitoreo
  
  //CRK PIR
   pinMode(pirPin, INPUT);      // Configuramos el pin del PIR como entrada
  pinMode(salidaPin, OUTPUT);  // Configuramos el pin de salida como salida
  Serial.begin(9600);          // Inicia la comunicación serial para monitoreo
  
}

void loop() {
  estadoBoton = digitalRead(botonPin);   // Leemos el estado del botón

  // Verificamos si hubo un cambio de estado en el botón
  if (estadoBoton == HIGH && ultimoEstadoBoton == LOW) {
    estadoLed = !estadoLed;             // Cambiamos el estado del LED
    digitalWrite(ledPin1, estadoLed);    // Actualizamos el LED
    delay(50);                          // Pequeño retardo para evitar rebotes
  }

  ultimoEstadoBoton = estadoBoton;      // Guardamos el estado actual del botón
  
  
  /////CRK foto celda
    int lectura = analogRead(fotoceldaPin);   // Leemos el valor de la fotocelda
  Serial.println(lectura);                  // Imprimimos la lectura en el monitor serial
  
  // Comprobamos si la lectura está en el último 10%
  if (lectura >= umbral1) {
    digitalWrite(ledPin2, HIGH);             // Encendemos el LED
  } else {
    digitalWrite(ledPin2, LOW);              // Apagamos el LED
  }

  delay(100); 
  
  ///////////////crk Humedad
    int lecturaHumedad = analogRead(humedadPin);   // Leemos el valor del sensor de humedad
  Serial.println(lecturaHumedad);                // Imprimimos la lectura en el monitor serial
  
  // Comprobamos si la lectura está en el último 10% (alta humedad)
  if (lecturaHumedad >= umbral2) {
    digitalWrite(salidaPin1, HIGH);               // Activamos la salida
  } else {
    digitalWrite(salidaPin1, LOW);                // Apagamos la salida
  }

  delay(100);  
  
  
  ///////////////////CRK temperatura
  
   int lecturaTemp = analogRead(tempPin);   // Leemos el valor del sensor de temperatura
  Serial.println(lecturaTemp);             // Imprimimos la lectura en el monitor serial
  
  // Comprobamos si la temperatura supera el umbral
  if (lecturaTemp >= umbral) {
    digitalWrite(salidaPin2, HIGH);         // Activamos la salida
  } else {
    digitalWrite(salidaPin2, LOW);          // Apagamos la salida
  }

  delay(100);                              // Pequeño retardo para evitar lecturas muy rápidas
  
  /////////////////
   int estadoPIR = digitalRead(pirPin);  // Leemos el estado del PIR
  
  // Si el sensor detecta movimiento (estado HIGH)
  if (estadoPIR == HIGH) {
    digitalWrite(salidaPin, HIGH);      // Activamos la salida
    Serial.println("Movimiento detectado");
  } else {
    digitalWrite(salidaPin, LOW);       // Apagamos la salida si no hay movimiento
    Serial.println("Sin movimiento");
  }

  delay(100);                           // Pequeño retardo para evitar lecturas muy rápidas
  
    
  
  
}
