#include <SoftwareSerial.h>   // Incluimos la librería  SoftwareSerial  
SoftwareSerial BT(10,11);    // Definimos los pines RX y TX del Arduino conectados al Bluetooth
int led=13;  //puerto digital 13
char cadena[255];
int i=0; //tamaño actual del array
void setup()
{
  BT.begin(9600);       // Inicializamos el puerto serie BT (Para Modo AT 2)
  Serial.begin(9600);   // Inicializamos  el puerto serie  
  pinMode(led,OUTPUT);
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
          digitalWrite(led,LOW);
        }
        
        if(strstr(cadena,"p")!=0)
        {
          digitalWrite(led,HIGH);
        }

        BT.write("\r"); //Envia Retorno de carro de la app.
        clean();
    }
  }
 
  if(Serial.available())  // Si llega un dato por el monitor serial se envía al puerto BT
  {
     BT.write(Serial.read());
  }
}
void clean()
{
   for (int cl=0; cl<=i; cl++)  {   cadena[cl]=0;  }  i=0;
}
