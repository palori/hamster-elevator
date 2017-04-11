
#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos_inferior = 0; // valor entre 0 i 180
int pos_superior = 180; // valor entre 0 i 180 (sempre més gran que 'pos_inferior')
int pos_actual = 0; // variable to store the servo position

int pul_pujada = 0; //S'ha de mirar bé i ajustar als que toquin
int pul_baixada = 1;
int led_pujada = 2;
int led_baixada = 3;

int vel_lineal = 0.1; // en m/s
int desplasament = 10; // en cm
int t_moviment = desplasament * 0.01 / vel_lineal; // calculem el temps que tarda en pujar o baixar

int t_espera_graus_servo = t_moviment / (pos_superior - pos_inferior); // calculem el temps que s'ha d'esperar que es mogui cada un dels graus
int t_sortir_cabina = 2000; // temps en 'ms' perque pugui abandornar la cabina
int t_verificacio_aturada_emergencia = 500;

int num_pampallugues = 3;
int t_periode_pampalluga = 1000;

bool aturada_emergencia(){
  if(digitalRead(pul_pujada)==HIGH && digitalRead(pul_baixada)==HIGH){
    delay(t_verificacio_aturada_emergencia);
    if(digitalRead(pul_pujada)==HIGH && digitalRead(pul_baixada)==HIGH){
      for(int p = 0; p < num_pampallugues; p++){
        digitalWrite(led_pujada, HIGH);
        digitalWrite(led_baixada, HIGH);
        delay(t_periode_pampalluga/2);
        digitalWrite(led_pujada, LOW);
        digitalWrite(led_baixada, LOW);
        delay(t_periode_pampalluga/2);
      }
      return true;
    }
  }
  return false;
}

void puja(){
  digitalWrite(led_pujada, HIGH);
  for (pos_actual; pos_actual <= pos_superior; pos_actual += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    if(aturada_emergencia()) break;
    myservo.write(pos_actual); // tell servo to go to position in variable 'pos_actual'
    delay(t_espera_graus_servo); // waits 15ms for the servo to reach the position
  }
  delay(t_sortir_cabina); //Esperem uns ms per a que pugui baixar de la cabina
  digitalWrite(led_pujada, LOW);
}

void baixa(){
  digitalWrite(led_baixada, HIGH);
  for (pos_actual; pos_actual >= pos_inferior; pos_actual -= 1) { // goes from 180 degrees to 0 degrees
    if(aturada_emergencia()) break;
    myservo.write(pos_actual); // tell servo to go to position in variable 'pos_actual'
    delay(t_espera_graus_servo); // waits 15ms for the servo to reach the position
  }
  delay(t_sortir_cabina); //Esperem uns ms per a que pugui baixar de la cabina
  digitalWrite(led_baixada, LOW);
}

void setup() {
  // put your setup code here, to run once:
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
}

void loop() {
  // put your main code here, to run repeatedly:

  if(digitalRead(pul_pujada)==HIGH && digitalRead(pul_baixada)==LOW){
    puja();
    delay(t_sortir_cabina); //Esperem uns ms per a que pugui baixar de la cabina
  }
  if(digitalRead(pul_pujada)==LOW && digitalRead(pul_baixada)==HIGH){
    baixa();
  }
  
  
}

