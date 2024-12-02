

#include <LiquidCrystal.h>

// Configuración del LCD 
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Declaración de pines
const int botonPin = 2;    // Pin del botón
const int ledPin1 = 3;     // Pin del LED (o salida)

const int fotoceldaPin = A0;  // Pin de la fotocelda
const int ledPin2 = 4;        // Pin del LED o salida
const int umbral1 = 500;      // Umbral 

const int humedadPin = A1;    // Pin del sensor de humedad
const int ledPin3 = 5;        // Pin de salida
const int umbral2 = 10;       // Umbral 

const int tempPin = A2;       // Pin del sensor de temperatura
const int ledPin4 = 6;        // Pin de salida
const int umbral = 150;       // Umbral para activar la salida a temperaturas 

const int pirPin = 10;        // Pin de entrada del PIR
const int ledPin5 = 11;       // Pin de salida

// Variables para almacenar el estado
bool estadoLed = LOW;          // Estado inicial del LED
bool estadoBoton;              // Estado actual del botón
bool ultimoEstadoBoton = LOW;  // Último estado del botón

void setup() {
  // Inicializa el LCD
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Sistema Iniciado");
  delay(2000); // Retardo para mostrar el mensaje inicial

  // Configuración de pines
  pinMode(botonPin, INPUT);
  pinMode(ledPin1, OUTPUT);

  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  pinMode(ledPin4, OUTPUT);
  pinMode(pirPin, INPUT);
  pinMode(ledPin5, OUTPUT);

  Serial.begin(9600); // Inicia la comunicación serial para monitoreo
}

void loop() {
  // Lógica para el botón
  estadoBoton = digitalRead(botonPin); // Leemos el estado del botón
  if (estadoBoton == HIGH && ultimoEstadoBoton == LOW) {
    estadoLed = !estadoLed; // Cambiamos el estado del LED
    digitalWrite(ledPin1, estadoLed); // Actualizamos el LED
    delay(50); // Pequeño retardo para evitar rebotes
  }
  ultimoEstadoBoton = estadoBoton; // Guardamos el estado actual del botón

  // Lógica para la fotocelda
  int lecturaFotocelda = analogRead(fotoceldaPin);
  lcd.setCursor(0, 0); // Muestra en la primera fila
  lcd.print("Luz: ");
  lcd.print(lecturaFotocelda);
  lcd.print("    "); // Borra datos sobrantes

  if (lecturaFotocelda >= umbral1) {
    digitalWrite(ledPin2, HIGH);
  } else {
    digitalWrite(ledPin2, LOW);
  }

  // Lógica para el sensor de humedad
  int lecturaHumedad = analogRead(humedadPin);
  lcd.setCursor(0, 1); // Muestra en la segunda fila
  lcd.print("Hum: ");
  lcd.print(lecturaHumedad);
  lcd.print("    ");

  if (lecturaHumedad <= umbral2) {
    digitalWrite(ledPin3, HIGH);
  } else {
    digitalWrite(ledPin3, LOW);
  }

  // Lógica para el sensor de temperatura
  int lecturaTemp = analogRead(tempPin);
  Serial.print("Temperatura: ");
  Serial.println(lecturaTemp);

  if (lecturaTemp >= umbral) {
    digitalWrite(ledPin4, HIGH);
  } else {
    digitalWrite(ledPin4, LOW);
  }

  // Lógica para el sensor PIR
  int estadoPIR = digitalRead(pirPin);
  if (estadoPIR == HIGH) {
    digitalWrite(ledPin5, HIGH);
    Serial.println("Movimiento detectado");
  } else {
    digitalWrite(ledPin5, LOW);
    Serial.println("Sin movimiento");
  }

  delay(100); // Pequeño retardo para estabilidad
}

  
  





