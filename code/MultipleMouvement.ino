/*
 * Ce code permet l'utilisation du bras robotique.
 * Avec différents mouvements qui permet que le bras ne fasse pas que ce que l'on veut
 *     :)
 *     Ce Montage inclus un module a Ultrasons (HC-SR04), qui detecte la presence du cube sur la surface.
 *     
 *     Apercu du plateau : (le bras etand placé sur la gauche en haut.)
 *      __________________
 *     |                  |    X = surface ou doit etre posé le cube.
 *     |              X   |    G = position du gobelet.
 *     |                  |
 *     | G                |
 *     |__________________|
 *     
 *     
 *     Branchement du HC-SR04 :       
 *     | HC-SR04              |   Arduino            |
 *     |----------------------|----------------------|
 *     | Trig                 |   Digital 2          |
 *     |----------------------|----------------------|
 *     | Echo                 |   Digital 3          |
 *     |----------------------|----------------------|
 *     | Vcc                  |   5V                 |
 *     |----------------------|----------------------|
 *     | Gnd                  |   Masse(-)           |
 *     |----------------------|----------------------|
 *     
 *     
 *     Branchement des Servos aux broches Digital de l'Arduino : 
 *     | Servos               |   Arduino            |
 *     |----------------------|----------------------|
 *     | Bas                  |   Digital 7          |
 *     |----------------------|----------------------|
 *     | Pince                |   Digital 6          |
 *     |----------------------|----------------------|
 *     | Gauche               |   Digital 8          |
 *     |----------------------|----------------------|
 *     | Droite               |   Digital 9          |
 *     |----------------------|----------------------|
 *     
 *     Branchements des autres composants (LED + buzzer) :
 *     | Composants           |   Arduino            |
 *     |----------------------|----------------------|
 *     | Led Rouge            |   Digital 13         |
 *     |----------------------|----------------------|
 *     | Led verte            |   Digital 12         |
 *     |----------------------|----------------------|
 *     | Led jaune            |   Digital 10         |
 *     |----------------------|----------------------|
 *     | Buzzer               |   Digital 4          |
 *     |----------------------|----------------------|
 *         
 */


#include<Servo.h>           //Librairie "Servo" premettant de faire bouger les servos.
#include<Ultrasonic.h>        //Librairie "Ultrasonic" permettant d'utiliser le module a Ultrasons.
//const int bouton = A1;   //broche analogique du bouton poussoir (pas activer pour ce code)
Ultrasonic ultrasonic(2, 3);     //broches de branchements du capteur a ultrasons.
int distance;                 //valeur "distance", correspond a la distance que calcule le capteur ultrasons.

//int valeur = 0;         //veleur du bouton, pas de bouton pour ce montage.
int reponse = 0;        //reponse pour le choix aléatoire des mouvements du bras.
 
int vert = 12;            //broche de la led verte, indique que le cube est dans le gobelet.
int rouge = 13;           //broche de la led rouge, indique que le bras n'a pas mis le cube dans le gobelet.
int jaune = 10;             //broche pour la led jaune, indique la presence du cube sur la surface.
 
char buzzer = 4;         //brche donné au buzzer      (fais un son grave quand le cube n'est pas dans le gobelet et fais un son aigu lorsequ'il est dans le gobelet.)

Servo pince;              //nom donné aux différents servos
Servo gauche;
Servo droite;
Servo bas;


void setup() {
  
    pince.attach(6);              //branchement des différents servos sur les broches de l'Arduino.
    bas.attach(7);
    gauche.attach(8);
    droite.attach(9);

    pinMode(vert, OUTPUT);        //type de sortie de la led verte, initialisée en "OUTPUT"
    pinMode(rouge, OUTPUT);       //type de sortie de la led rouge, initialisée en "OUTPUT"
    pinMode(jaune, OUTPUT);       //type de sortie de la led jaune, initialisée en "OUTPUT"
  
Serial.begin(9600);

//pinMode(bouton, INPUT_PULLUP);        //bouton branché sur la résistance inclus sur la carte arduino pas le cas sur ce montage.
    
}

void loop() {
  
    distance=ultrasonic.read();        //initialise la valeur "distance" 
    Serial.println(distance);       //ecris cette valeur dans le Serial Monitor.
    
    if(distance<10) {             //si le capteur ultrasons detecte la presence du cube.

         reponse = random(5);      //initialise la valeur "reponse" qui correspond au mouvements aléatoires du bras.
         switch(reponse) { 

        case 0:
    digitalWrite(jaune, HIGH);     //allume la led jaune pour signaler le presence du cube sur la surface
    pince.write(0);   //prend le cube pour le remettre a sa place initiale :)
    delay(500);
    bas.write(133);
    delay(20);
    droite.write(165);
    delay(100);
    gauche.write(65);
    delay(800); 
    pince.write(180);
    delay(1000);
    digitalWrite(jaune, LOW);         //eteind la led jaune pour dire que le cube n'est pas sur la surface
    gauche.write(125);
    droite.write(135);
    delay(400);
    bas.write(80);
    pince.write(180);
    delay(1000);
    tone(buzzer, 800, 1000);
    digitalWrite(rouge, HIGH);      
    bas.write(133);
    delay(20);
    droite.write(165);
    delay(100);
    gauche.write(65);
    digitalWrite(jaune, HIGH);     //allume la led en jaune pour signaler la presence du cube
    delay(800); 
    pince.write(0);
    delay(1000);
    gauche.write(120);
    droite.write(140);
    delay(500);
    bas.write(80);
    pince.write(50);
    delay(500);
    digitalWrite(rouge, LOW);
    break;
        
            case 1:
      digitalWrite(jaune, HIGH);   //allume la led jaune pour signaler que le cube est sur la surface
      bas.write(133);               //fait non de gauche a droite
      gauche.write(120);
      droite.write(140);
      pince.write(50);
      tone(buzzer, 800, 1000);
      digitalWrite(rouge, HIGH);
      delay(400);
      bas.write(80);
      gauche.write(120);
      droite.write(140);
      pince.write(50);
      delay(400);
      bas.write(133);
      gauche.write(120);
      droite.write(140);
      pince.write(50);
      delay(400);
      digitalWrite(rouge, LOW);
        break;

        case 2:
        digitalWrite(jaune, HIGH);   //allume la led jaune pour signaler que le cube est sur la surface
        pince.write(0);   //mouvement basique = prendre cube et le mettre de le gobelet
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
        digitalWrite(jaune, LOW);     //eteind la led jaune pour dire que le cube n'est pas sur la surface
        delay(400);
        bas.write(80);
        pince.write(180);
        delay(1000);
        pince.write(0);
        digitalWrite(vert, HIGH);
        delay(1000);
        digitalWrite(vert, LOW); 
      break;

      case 3:
    digitalWrite(jaune, HIGH);    //allume la led jaune pour signaler que le cube est sur la surface
    pince.write(0);   //fait semblant de prendre le cube alors que non
    delay(500);
    bas.write(133);
    delay(20);
    droite.write(165);
    delay(100);
    gauche.write(65);
    delay(800); 
    tone(buzzer, 800, 1000);
    digitalWrite(rouge, HIGH);
    pince.write(0);
    delay(400);   
    gauche.write(125);
    droite.write(135);
    delay(1000);
    bas.write(80);
    delay(150); 
    pince.write(0);
    delay(1000);
    pince.write(0);
    digitalWrite(rouge, LOW);
    break;

    case 4:
    digitalWrite(jaune, HIGH);    //allume la led jaune pour signaler que le cube est sur la surface
    pince.write(0);   //faire semblant de prendre la cube alors que non, en ouvrant et fermant la pince plusieurs fois pour ensuite repartir en position gobelet sans le cube.
    delay(500);
    bas.write(133);
    delay(20);
    droite.write(165);
    delay(100);
    gauche.write(65);
    pince.write(0);               //ouvre et ferme la pince plusieurs fois pour apres repartir en position gobelet sans le cube.
    delay(400);
    pince.write(180);
    delay(250);
    pince.write(0);
    delay(200);
    pince.write(180);
    delay(250);
    pince.write(0);
    delay(250);
    pince.write(180);
    delay(250);
    pince.write(0);                //fin du mouvement de la pince.
    tone(buzzer, 800, 1000);
    digitalWrite(rouge, HIGH);
    pince.write(0);
    delay(400);   
    gauche.write(125);
    droite.write(135);
    delay(1000);
    bas.write(80);
    delay(150); 
    pince.write(0);
    delay(1000);
    pince.write(0);
    digitalWrite(rouge, LOW);
    break;
       
    
    }
                
    }else{                        
          bas.write(80);           //position initiale, lorseque le capteur ultrasons ne detecte pas la prescence du cube.
          gauche.write(120);
          droite.write(140);
          pince.write(50); 

           digitalWrite(jaune, LOW);   //éteindre la led jaune, pour signaler que le cube n'est pas sur la surface.
          }
          
          delay(100);        //latence pour eviter de "saturer" l'Arduino.
        }
          
        

         
