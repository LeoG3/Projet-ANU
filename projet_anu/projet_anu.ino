// Theremin optique

//Branchement
#define PHONES 9   // Haut parleur connecté a la sortie 9
#define PHOTOCELL 0 //Photoresistance connecté à l'entrée A0

const int buttonPin = 4;
const int ledPin = 13;

int on = 0;
int lastState = LOW;

//variable definitions
long val = 0;        //stockage de la valeur de Photoresistance
long lastVal = 0;
long maxread = 0;    //valaur max de la phase de calibrage
long minread = 1000;  //valeur min de la pahse de calibrage
double f = 0;         // frequence du son
double normf= 0;    // frequence normalisé
double logfre = 0;      // logarithme de la frequence normalisé
int ilogf = 0;        // logarithme arrondi 
int i = 0;            // 
double factor = 0;    //  echelle du facteur pour la calibration
double shift = 0;     // espace de calibration
long maxfreq = 440;  // Maximum de la frequence desiré apres la calibration
long minfreq = 55;   // minimum de la frequence desiré apres la calibration


//Valeur pour changer l'ecart entre 2 notes 
//double gap = 1.148698355;  //(pentatonic)
                             // it's the 5th root of 2
double gap = 1.059463094;  //(chromatic)
                            // its the 12th root of 2

                              
void setup()
{
  Serial.begin(9600);
  pinMode(PHONES, OUTPUT);    //  mise en sortie des pattes digitales
  pinMode(ledPin,OUTPUT);
  digitalWrite(ledPin,HIGH);

  

//  boucle de calibration pour determiner un les niveaux Max et min de la Photoresistance
//  et associé cela au frequence max et min
  for (i = 0; i< 500; i++) {  // calibration loop runs for 5 seconds
    val = analogRead(PHOTOCELL);   // lecture de la photoresistance 
    tone(PHONES, val);          // joue la note brute pour guide la calibration
    if (val > maxread) {        //  mise en place de la valeur la plus grande
      maxread = val;
    }
    if (val < minread) {        // mise en place de la valeur la plus petite
      minread = val;
    }  
    delay(10);                  // delay
  } 
  
  // on utilise la calibration pour calculer  l'echelle et les changements de parametre
  factor = (double)(maxfreq - minfreq) / (double)(maxread - minread); // changement de parametre
  //c'est comme une pente( lineaire)
  
  shift = factor * minread - minfreq;  //changement de parametre s(utilise comme un offset

  digitalWrite(ledPin,LOW);
}

void loop()
{
  int buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH && lastState == LOW) {
    if (on == 1) {
      on = 0;
    }
    else {
      on = 1;
    }
    delay(50);
  }

  lastState = buttonState;

  
  val = analogRead(PHOTOCELL);   // lecture de la photoresistance 
  
  Serial.println(val);
  
  int averageVal = (lastVal + val)/2;  
  f = factor * averageVal - shift;     // linearise la frequence
                               // entre une valeur Max et min (frequence)
                                // accordé a la calibration
                                // cette ligne cartographie lineairement la frequence vers une valeur entre minfreq et maxfreq a partir du resultat de la calibration
  // permet de lineariser le son 
  normf = f / (double) minfreq;  // divise une fonction exponentielle par la valeur min
  logfre = log(normf) / log(gap);  // nous permet de prendre le log de base gap et le resultat
  ilogf = round(logfre);          // est le nombre de notes au dessus de la plus basse, une fois arrondie.
  f = minfreq * pow(gap,ilogf);   // on ferait mieux de le de-log-er

  if (on == 1) {
    tone(PHONES, f);              // produit la tonalité du signal 
  }
  else {
    noTone(PHONES);
  }

  lastVal = averageVal;
  
}
