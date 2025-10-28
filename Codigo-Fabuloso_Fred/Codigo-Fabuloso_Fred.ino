/*                    FABULOSO FRED
                Programación en Lenguaje C
                
   Integrantes:
    Alvarado Lagunes María José        ID 331869 
    Hidalgo Rodríguez Melissa          ID 262931
    López Silva Carlos Andrés          ID 241236
    Reynaldo Sebastían Llamas Llamas   ID 320301

 El juego te reta a repetir su secuencia de luces, cada nivel agregará otro LED que tienes que memorizar y repetir en el mismo orden,
 en caso de que la secuencia introducida sea incorrecta en el monitor serial aparecerá la secuencia que se debía de introducir y la que se introdujo. 
 Para volver a jugar presionar el botón de reinicio del Arduino. 

 Link de la simulación: https://www.tinkercad.com/embed/lwc8VqB2iYI?editbtn=1
*/ 

#define NIVMAX 10 //Nivel máximo del juego
#define TIME 300
//Constantes para los pines de salida, para la generación de aleatorios deben ser pines consecutivos
#define LED_AZUL 2
#define LED_ROJO 3
#define LED_AMAR 4
#define LED_NARA 5
#define LED_VERD 6
//Constantes para los pines de entrada
#define PUSH_AZUL 7
#define PUSH_ROJO 8
#define PUSH_AMAR 9
#define PUSH_NARA 10
#define PUSH_VERD 11

int nivel=1, opc=0, secLED[NIVMAX];

//Prototipos de funciones
void menu();
void llenar(int secLED[]);
void secOn(int secLED[]);
void ledOn(int pin, int tiempo);
void capturar(int push[]);
bool comparar(int push[], int secLED[]);
void imprimir(int vec[]);

void setup() {
  //Seleccionar los pines de salida
  pinMode(LED_AZUL,OUTPUT);
  pinMode(LED_ROJO,OUTPUT);
  pinMode(LED_AMAR,OUTPUT);
  pinMode(LED_NARA,OUTPUT);
  pinMode(LED_VERD,OUTPUT);
  //Selecionar los pines de entrada, usando las resistencias del mismo arduino
  //En la configuración de resistencias pull-up cuando el botón se presiona el estado es LOW
  pinMode(PUSH_AZUL,INPUT_PULLUP);
  pinMode(PUSH_ROJO,INPUT_PULLUP);
  pinMode(PUSH_AMAR,INPUT_PULLUP);
  pinMode(PUSH_NARA,INPUT_PULLUP);
  pinMode(PUSH_VERD,INPUT_PULLUP);
  //Iniciar a los pines en LOW
  digitalWrite(LED_AZUL,LOW);
  digitalWrite(LED_ROJO,LOW);
  digitalWrite(LED_AMAR,LOW);
  digitalWrite(LED_NARA,LOW);
  digitalWrite(LED_VERD,LOW);
  //Iniciar monitor serial
  Serial.begin(9600);
}//setup

void loop() {
  int push[nivel];
  bool iguales;
  
  if(nivel==1){
    menu(); //Seleccionar la dificultad
  }//if
  if(opc==2){
    llenar(secLED); //En díficil cada nivel genera una nueva secuencia
  }//if
  
  Serial.print("Nivel ");
  Serial.println(nivel);
  delay(4*TIME);

  secOn(secLED);  //Mostrar la secuencia de los LED
  capturar(push); //Capturar los botones presionados
  
  iguales = comparar(push,secLED); 
  if(iguales){
     Serial.println("Correcto");
    if(nivel<NIVMAX){    
      nivel++; 
    }//if
    else{
      Serial.println("Nivel maximo alcanzado");
      delay(1000);
      exit(0);
    }//else
  }//if
  else{
    Serial.println("Incorrecto \nSecuencia mostrada");
    imprimir(secLED);
    Serial.println("Tu secuencia");
    imprimir(push);
    nivel=1;
    delay(1000);
    exit(0);
  }//else
}//loop

//Implementación de funciones

/* La función menu muestra los modos de juego disponibles y guarda la selección de la dificultad en la variable opc */
void menu(){
  int flag=0;
  do{
    Serial.println("Bienvenido al fabuloso FRED \nSelecciona la dificultad");
    Serial.println("Facil...........1"); //La secuencia no cambia en cada nivel
    Serial.println("Dificil.........2"); //La secuencia cambia en cada nivel
    Serial.println("Salir...........3");
    
    while(Serial.available()==0){} //Mientras no haya datos pendientes para su lectura el programa se detiene
    opc = Serial.read()-48; //Se restan 48 porque el valor leído esta en ASCII
    Serial.println(opc);
    
    switch(opc){
      case 1: llenar(secLED); //En fácil solo se genera una secuencia por juego
        flag = 1;
        break;
      case 2: flag = 1;
        break;
      case 3: exit(0);
      default: Serial.print("Opcion invalida\n"); 
        break;
    }//switch
  }while(flag!=1); //Se pregunta la dificultad hasta que sea una opción válida
}//menu

/* La función llenar genera números aleatorios y los almacena en el vector secLed */
void llenar(int secLED[]){
  int lim = NIVMAX; //Cuando el modo de juego es fácil se llena todo el vector
  if (opc==2){
    lim = nivel; //Cuando el modo de juego es díficil se llena el vector hasta nivel
  }//if
  for(int i=0; i<lim; i++){
    secLED[i] = random(LED_AZUL, LED_VERD+1); //Números aleatorios con rango del pin de menor tamaño al pin de mayor tamaño
  }//for 
}//llenar

/* La función secOn enciende los LED correspondientes a los valores guardados en el vector secLED, dependiendo del nivel es
   el numero de LED que se encienden */
void secOn(int secLED[]){
  int pin=0, tiempo=3*TIME;
  for(int i=0; i<nivel; i++){
    pin = secLED[i];
    ledOn(pin, tiempo);
    delay(TIME);
  }//for 
}//secOn

/* La función ledOn enciende un LED por un tiempo determinado */
void ledOn(int pin, int tiempo){
  digitalWrite(pin,HIGH);
  delay(tiempo);
  digitalWrite(pin,LOW);
}//ledOn

/* La función capturar detecta cuando un botón se presiona y almacena su poscición en el vector push */
void capturar(int push[]){
  int pres=0, tiempo=TIME;
  for(int i=0; i<nivel; i++){
    pres=0;
    while(pres!=1){ //Se pregunta por cada uno de los botones hasta que uno se presione
      if(digitalRead(PUSH_AZUL)==0){
        ledOn(LED_AZUL, tiempo);  //Se enciende el LED correspondiente al botón
        push[i] = LED_AZUL; //Se guarda en el vector el valor del pin del LED
        pres=1;
      }//if azul
      if(digitalRead(PUSH_ROJO)==0){
        ledOn(LED_ROJO, tiempo);
        push[i] = LED_ROJO;
        pres=1;
      }//if rojo
      if(digitalRead(PUSH_AMAR)==0){
        ledOn(LED_AMAR, tiempo);
        push[i] = LED_AMAR;
        pres=1;
      }//if amarillo
      if(digitalRead(PUSH_NARA)==0){
        ledOn(LED_NARA, tiempo);
        push[i] = LED_NARA;
        pres=1;
      }//if naranja
      if(digitalRead(PUSH_VERD)==0){
        ledOn(LED_VERD, tiempo);
        push[i] = LED_VERD;
        pres=1;
      } //if verde
    }//while
  }//for
}//capturar

/* La función comparar compara los elementos del vector secLed y el vector push */
bool comparar(int push[], int secLED[]){
  bool iguales=true;
  for(int i=0; i<nivel; i++){
    if(secLED[i] != push[i]){
      iguales = false;
      break;
    }//if
  }//for
  return iguales;
}//comparar

/* La función imprimir muestra los elementos de un vector en el monitor serial */
void imprimir(int vec[]){
  for(int i=0; i<nivel; i++){
    Serial.print(vec[i]);
    Serial.print("\t");
  }//for
  Serial.println();
}//imprimir
