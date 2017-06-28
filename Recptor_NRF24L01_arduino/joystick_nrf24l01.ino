#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>

int vel_max=255;
int vel_med=100;

#define pwm_m1 3
#define pwm_m2 5

#define avanzar 1
#define retroceder 0

#define up 1
#define down 2
#define left 3
#define right 4
#define circle 5
#define equis 6
#define cuadrade 7
#define triangle 8
#define l1  9
#define l2  10
#define r1  11
#define r2  12
#define select  14
#define start  13
#define sin_movimiento 15

RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL; 
int Dato[1]; 
int dato;

void setup(void)
{
  Serial.begin(9600); //Habilito la comunicacion Serie 
    //Configuracion del RF
  radio.begin();    
  radio.openReadingPipe(1,pipe); 
  radio.startListening();         
}
void loop(void)
{
  Lectura_de_datos();
  Desicion_de_movimientos();
}
void Lectura_de_datos()
{
  if(radio.available())
    {
      
      int done = radio.read(Dato,1);
      dato=Dato[0];
      Serial.println(dato);
    }
}   

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Desicion_de_movimientos()
{
  if(dato!=sin_movimiento)
  {
    if((up==dato)&&(down!=dato)&&(left!=dato)&&(right!=dato)) Avanzar();
    if((up!=dato)&&(down==dato)&&(left!=dato)&&(right!=dato))Retroceder();
    if((up!=dato)&&(down!=dato)&&(left!=dato)&&(right==dato))Giro_der();
    if((up!=dato)&&(down!=dato)&&(left==dato)&&(right!=dato))Giro_izq();

  //  if((dato==up)&&(dato!=down)&&(dato==left)&&(dato!=right)) Avanzar_izq();
  //  if((dato==up)&&(dato!=down)&&(dato!=left)&&(dato==right)) Avanzar_der();

  //  if((dato==down)&&(dato!=down)&&(dato==left)&&(dato!=right)) Retroceder_izq(); 
  //  if((dato==down)&&(dato!=down)&&(dato!=left)&&(dato==right)) Retroceder_der();
 
  }
  else
  { 
    Movimientos_off();
  }
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////


void Avanzar()
{
  M_Dir_avanzar();        //Decido la direccion de los motores
  velocidad();            //y  La velocidad
}
void Retroceder()
{
  M_Dir_retroceder();
  velocidad();
}
void Giro_der()
{
  M_Dir_giro_der();
  velocidad();
}
void Giro_izq()
{
  M_Dir_giro_izq();
  velocidad();
}

void Avanzar_izq()
{
  M_Dir_avanzar();
 
}
void  Avanzar_der()
{
  M_Dir_avanzar();
 // velocidad_giro_der();
}
void Retroceder_izq()
{
  M_Dir_retroceder();
 // velocidad_giro_izq();
}
void Retroceder_der()
{
  M_Dir_retroceder();
 // velocidad_giro_der();
}    
////////////////////////////////////////////////////////////////  
void Movimientos_off()
{
  analogWrite(pwm_m1,0);
  analogWrite(pwm_m2,0);
}
void M_Dir_avanzar(){
  //Serial.println("1");
  digitalWrite(A0,HIGH);
  digitalWrite(A1,LOW);
  digitalWrite(A2,HIGH);
  digitalWrite(A3,LOW);
  }
 void M_Dir_retroceder(){
  //Serial.println("1");
  digitalWrite(A1,HIGH);
  digitalWrite(A0,LOW);
  digitalWrite(A3,HIGH);
  digitalWrite(A2,LOW);
  } 
  void M_Dir_giro_der(){
  //Serial.println("1");
  digitalWrite(A1,HIGH);
  digitalWrite(A0,LOW);
  digitalWrite(A2,HIGH);
  digitalWrite(A3,LOW);
  }
  void M_Dir_giro_izq(){
  //Serial.println("1");
  digitalWrite(A0,HIGH);
  digitalWrite(A1,LOW);
  digitalWrite(A3,HIGH);
  digitalWrite(A2,LOW);
  }

void velocidad(){
 if(r1==dato)
 {
    analogWrite(pwm_m1,vel_max);
    analogWrite(pwm_m2,vel_max);
 }else{
  
    analogWrite(pwm_m1,255);
    analogWrite(pwm_m2,255);
  }
}

  
