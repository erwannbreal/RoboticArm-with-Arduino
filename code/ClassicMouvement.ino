/*
 * Ce code permet l'automatisation du bras avec une simple préssion sur un bouton.
 * Lorseque le bouton est préssé, le bras va prendre un cube et le mettre dans un gobelet.
 */

#include<Servo.h>
const int bouton = A1;        //broche analogique du bouton

int valeur = 0;          //valeur du bouton

Servo pince;
Servo gauche;           //nom donné aux différens servos
Servo droite;
Servo bas;

void setup() {

pince.attach(6);
bas.attach(7);        //broches donné aux différents servos
gauche.attach(8);
droite.attach(9);
  
Serial.begin(9600);

pinMode(bouton, INPUT_PULLUP);          //initialisation du bouton en "input" en utilisant la résistance pullup de l'arduino
}

void loop() {
  
  valeur=analogRead(bouton);           
  Serial.println(valeur);

  if(valeur<200){
    pince.write(0);   //début du mouvement du bras lorseque le bouton est préssé, prendre le cube et le mettre dans le gobelet
    delay(500);
    bas.write(133);
    delay(20);
    droite.write(165);
    delay(100);
    gauche.write(65);
    delay(800); 
    pince.write(180);
    delay(1000);
    gauche.write(125);
    droite.write(135);
    delay(150);
    bas.write(80);
    pince.write(180);
    delay(1000);
    pince.write(0); 
    }else{                  //position par défault lorseque le bouton n'est pas préssé
      bas.write(80);
      gauche.write(120);
      droite.write(140);
      pince.write(50);      
      }
delay(100);

}
