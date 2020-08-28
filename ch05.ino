#include <SoftwareSerial.h>   // Incluimos la librería  SoftwareSerial  
SoftwareSerial BT(10,11);    // Definimos los pines RX y TX del Arduino conectados al Bluetooth
int led=3;  //puerto digital 3
int a=4;//puerto digital 4
int b=5;//puerto digital 5
int c=6;//puerto digital 6
int d=7;//puerto digital 7

int gi=8; //giro a la izquierda
int gd=9; //giro a la derecha
int sw=0; //interruptor 
int pwm=0; //osilador 
int velocidad=100;
char cadena[255];
int i=0; //tamaño actual del array
void setup()
{
  BT.begin(9600);       // Inicializamos el puerto serie BT (Para Modo AT 2)
  Serial.begin(9600);   // Inicializamos  el puerto serie  
  pinMode(led,OUTPUT);  // Señal PWM
   pinMode(a,OUTPUT);
   pinMode(b,OUTPUT);
   pinMode(c,OUTPUT);
   pinMode(d,OUTPUT);
   pinMode(gi,OUTPUT);
   pinMode(gd,OUTPUT);
  Serial.println("Comunicacion Iniciada :) ");
}
 
void loop()
{
  if(BT.available())    // Si llega un dato por el puerto BT se envía al monitor serial
  {
    char dato=BT.read();
    Serial.write(dato);
    cadena[i++]=dato;
    //Serial.println(dato);
    if(dato=='\n')
    {
      Serial.print(cadena);

        //led
        if(strstr(cadena,"a")!=0)
        {
          sw=0;
          pwm=0;
          digitalWrite(led,LOW);
          digitalWrite(gd,LOW);
          digitalWrite(gi,LOW);
          //digitalWrite(led,LOW);
        }
        
        if(strstr(cadena,"p")!=0)
        {
          Serial.println("Encendiendo Motor");
          sw=1;
          pwm=0;
          digitalWrite(led,LOW);
          digitalWrite(gd,HIGH);
          digitalWrite(gi,LOW);
        }

        if(strstr(cadena,"v")!=0)
        {
          velocidad+=200;
          if(velocidad>1000)
          {
            velocidad = 100;
          }  
          Serial.println(velocidad);
        }

        if(strstr(cadena,"g")!=0)
        {
          Serial.println("girando a la derecha");
          digitalWrite(gd,HIGH);
          digitalWrite(gi,LOW);
          /*digitalWrite(a,HIGH);
          digitalWrite(b,LOW);
          digitalWrite(c,LOW);
          digitalWrite(d,LOW);
          delay(100);
          digitalWrite(a,LOW);
          digitalWrite(b,HIGH);
          digitalWrite(c,LOW);
          digitalWrite(d,LOW);
          delay(100);
          digitalWrite(a,LOW);
          digitalWrite(b,LOW);
          digitalWrite(c,HIGH);
          digitalWrite(d,LOW);
          delay(100);
          digitalWrite(a,LOW);
          digitalWrite(b,LOW);
          digitalWrite(c,LOW);
          digitalWrite(d,HIGH);
          delay(100);          */
        }

        if(strstr(cadena,"i")!=0)
        {
          Serial.println("Girando a la izquierda");
          digitalWrite(gd,LOW);
          digitalWrite(gi,HIGH);
          /*digitalWrite(a,LOW);
          digitalWrite(b,LOW);
          digitalWrite(c,LOW);
          digitalWrite(d,HIGH);
          delay(100); 
          digitalWrite(a,LOW);
          digitalWrite(b,LOW);
          digitalWrite(c,HIGH);
          digitalWrite(d,LOW);
          delay(100);
          digitalWrite(a,LOW);
          digitalWrite(b,HIGH);
          digitalWrite(c,LOW);
          digitalWrite(d,LOW);
          delay(100);
          digitalWrite(a,HIGH);
          digitalWrite(b,LOW);
          digitalWrite(c,LOW);
          digitalWrite(d,LOW);
          delay(100);*/
                     
        }

        

        BT.write("\r"); //Envia Retorno de carro de la app.
        clean();
    }

  }
 
  if(Serial.available())  // Si llega un dato por el monitor serial se envía al puerto BT
  {
     BT.write(Serial.read());
  }

  
  if(sw==1)
  {
    Serial.println("PWM XD");
    delay(velocidad);
    if(pwm==1)
    {
      digitalWrite(led,HIGH);
      pwm=0;
    }
    else{
      pwm=1;
      digitalWrite(led,LOW);
    }
  }

  
}
void clean()
{
   for (int cl=0; cl<=i; cl++)  {   cadena[cl]=0;  }  i=0;
   digitalWrite(a,HIGH);
   digitalWrite(c,HIGH);
}
