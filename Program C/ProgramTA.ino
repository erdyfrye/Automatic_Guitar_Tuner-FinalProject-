#include "arduinoFFT.h"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE); 
arduinoFFT FFT = arduinoFFT();
const uint16_t samples = 128;
const double samplingFrequency = 750; //untuk resolusi frekuensi
unsigned int sampling_period_us;
unsigned long microseconds;
double total;
double mean;
double vReal[samples];
double vImag[samples];
#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif
int INA = 13;
int INB = 12;
int PWM=11;
void setup()
{
  Serial.begin(115200);
sbi(ADCSRA, ADPS2);
cbi(ADCSRA, ADPS1);
sbi(ADCSRA, ADPS0);
   sampling_period_us = round(1000000*(1.0/samplingFrequency));
  pinMode(PWM, OUTPUT);
  pinMode(INA,OUTPUT);
  pinMode(INB,OUTPUT);
  pinMode(0, INPUT_PULLUP);
  pinMode(1, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  lcd.begin(16,2);//Defining 16 columns and 2 rows of lcd display
  lcd.backlight();//To Power ON the back light
  lcd.setCursor(0,0);
  lcd.print("Arduino   Guitar");
  lcd.setCursor(6,1);
  lcd.print("Tuner");
  delay(5000);
  lcd.clear();
}

void loop()
{

  total=0;
  for(int i=0; i<samples; i++)
  {
     microseconds = micros();
     vReal[i] = analogRead(A0);
   
      while(micros() < (microseconds + sampling_period_us))
      { 
      }
  }
  for (int i = 0; i < samples; i++)
  {
   total=total+vReal[i];
   mean = total/samples;   
    
  }
 for (int i = 0; i < samples; i++)
  {
    vReal[i] = vReal[i] - mean;
    vImag[i]=0;
  }

FFT.Windowing(vReal, samples, FFT_WIN_TYP_HANN, FFT_FORWARD);
FFT.Compute(vReal, vImag, samples, FFT_FORWARD);
FFT.ComplexToMagnitude(vReal, vImag, samples);
double peak = FFT.MajorPeak(vReal, samples, samplingFrequency);
  int Er=digitalRead(0);
  int A=digitalRead(1);
  int D=digitalRead(2);
  int G=digitalRead(3);
  int B=digitalRead(4);
  int Et=digitalRead(5);
 if((peak)<(55))
 {
  peak=0;
  digitalWrite(INA,LOW);
  digitalWrite(INB, LOW);
  lcd.setCursor(10,0);
  lcd.print("         ");
  lcd.setCursor(0,1);
  lcd.print("                 ");

 }
 
 if ((peak)>0)
 {
  Serial.println(peak);
    if (Er==LOW)
    {
      peak=peak-0.81;
      lcd.setCursor(0,0); //Defining positon to write from first row,first column .
      lcd.print("E2");
      lcd.setCursor(10,0);
      lcd.print(peak);
      if((peak)<81.91)
        {
          
          digitalWrite(INA,HIGH);
          digitalWrite(INB,LOW);
          analogWrite(PWM, 160);
          lcd.setCursor(0,1);
          lcd.print(">>>>>");
          lcd.setCursor(6,1);
          lcd.print("                 ");
         //delay(500);
        }
      if((peak)>82.91)
        {
          
          digitalWrite(INA,LOW);
          digitalWrite(INB,HIGH);
          analogWrite(PWM, 140);
          lcd.setCursor(0,1);
          lcd.print("           ");
          lcd.setCursor(11,1);
          lcd.print("<<<<<");
        //delay(500);
        }
      else if ((peak)>=81.91 && (peak)<=82.91)
        {
          digitalWrite(INA,LOW);
          digitalWrite(INB,LOW);
          lcd.setCursor(0,1);
          lcd.print("     ");
          lcd.setCursor(11,1);
          lcd.print("     ");
          lcd.setCursor(6,1);
          lcd.print("Tune");
          delay(2000);
        }
    }
    if (A==LOW)
    {
      peak=peak-1.05;
      lcd.setCursor(0,0);
      lcd.print("A2");
      lcd.setCursor(10,0);
      lcd.print(peak);
      if((peak)<109.50)
      {
        digitalWrite(INA,HIGH);
        digitalWrite(INB,LOW);
        analogWrite(PWM, 160);
        lcd.setCursor(0,1);
        lcd.print(">>>>>");
        lcd.setCursor(6,1);
        lcd.print("          ");
       //delay(500);
      }
      if((peak)>110.50)
      {
        digitalWrite(INA,LOW);
        digitalWrite(INB,HIGH);
        analogWrite(PWM, 120);
        lcd.setCursor(0,1);
        lcd.print("           ");
        lcd.setCursor(11,1);
        lcd.print("<<<<<");
      //delay(500);
      }
      else if ((peak)>=109.50 && (peak)<=110.50)
      {
        digitalWrite(INA,LOW);
        digitalWrite(INB, LOW);
        lcd.setCursor(0,1);
        lcd.print("     ");
        lcd.setCursor(11,1);
        lcd.print("     ");
        lcd.setCursor(6,1);
        lcd.print("Tune");
        delay(2000);
      }
    }
    if (D==LOW)
    {
      peak=peak-1.96;
      lcd.setCursor(0,0);
      lcd.print("D3");
      lcd.setCursor(10,0);
      lcd.print(peak);
      if((peak)<146.30)
      {
        digitalWrite(INA,HIGH);
        digitalWrite(INB,LOW);
        analogWrite(PWM, 192);
        lcd.setCursor(0,1);
        lcd.print(">>>>>");
        lcd.setCursor(6,1);
        lcd.print("          ");
      //delay(500);
      }
      if((peak)>147.30)
      {
        digitalWrite(INA,LOW);
        digitalWrite(INB,HIGH);
        analogWrite(PWM, 170);
        lcd.setCursor(0,1);
        lcd.print("           ");
        lcd.setCursor(11,1);
        lcd.print("<<<<<");
       // delay(500);
      }
      else if ((peak)>=146.30 && (peak)<=147.30)
      {
        digitalWrite(INA,LOW);
        digitalWrite(INB, LOW);
        lcd.setCursor(0,1);
        lcd.print("     ");
        lcd.setCursor(11,1);
        lcd.print("     ");
        lcd.setCursor(6,1);
        lcd.print("Tune");
        delay(2000);
      
      }
    }
    if (G==LOW)
    {
      peak=peak-3.08;
      lcd.setCursor(0,0);
      lcd.print("G3");
      lcd.setCursor(10,0);
      lcd.print(peak);
      if((peak)<195.50)
      {
        digitalWrite(INA,HIGH);
        digitalWrite(INB,LOW);
        analogWrite(PWM, 220);
        lcd.setCursor(0,1);
        lcd.print(">>>>>");
        lcd.setCursor(6,1);
        lcd.print("          ");
          lcd.setCursor(10,0);
          lcd.print(peak);
      // delay(500);
      }
      if((peak)>196.50)
      {
         
        digitalWrite(INA,LOW);
        digitalWrite(INB,HIGH);
        analogWrite(PWM, 150);
        lcd.setCursor(0,1);
        lcd.print("           ");
        lcd.setCursor(11,1);
        lcd.print("<<<<<");
      // delay(500);
        
      }
      else if ((peak)>=195.50 && (peak)<=196.50)
      {
        digitalWrite(INA,LOW);
        digitalWrite(INB, LOW);
        lcd.setCursor(0,1);
        lcd.print("     ");
        lcd.setCursor(11,1);
        lcd.print("     ");
        lcd.setCursor(6,1);
        lcd.print("Tune");
        delay(2000);
      }
    }
    if (B==LOW)
    {
      peak=peak-3.7;
      lcd.setCursor(0,0);
      lcd.print("B3");
      lcd.setCursor(10,0);
      lcd.print(peak);
      if((peak)<246.50)
      {
        digitalWrite(INA,HIGH);
        digitalWrite(INB,LOW);
        analogWrite(PWM, 125);
        lcd.setCursor(6,1);
        lcd.print("          ");
        lcd.setCursor(0,1);
        lcd.print(">>>>>");
      // delay(500);
      }
      if((peak)>247.50)
      {
        digitalWrite(INA,LOW);
        digitalWrite(INB,HIGH);
        analogWrite(PWM, 100);
        lcd.setCursor(0,1);
        lcd.print("           ");
        lcd.setCursor(11,1);
        lcd.print("<<<<<");
       // delay(500);
      }
      else if ((peak)>=246.40 && (peak)<=247.40)
      {
        digitalWrite(INA,LOW);
        digitalWrite(INB, LOW);
        lcd.setCursor(0,1);
        lcd.print("     ");
        lcd.setCursor(11,1);
        lcd.print("     ");
        lcd.setCursor(6,1);
        lcd.print("Tune");
        delay(2000);
      
      }
    }
    if (Et==LOW)
    {
      peak=peak-5;
      lcd.setCursor(0,0);
      lcd.print("E4");
      lcd.setCursor(10,0);
      lcd.print(peak);
      if((peak)<329.10)
      {
        digitalWrite(INA,HIGH);
        digitalWrite(INB,LOW);
        analogWrite(PWM, 150);
        lcd.setCursor(0,1);
        lcd.print(">>>>>");
        lcd.setCursor(6,1);
        lcd.print("          ");
      // delay(500);
      }
      if((peak)>330.10)
      {
        digitalWrite(INA,LOW);
        digitalWrite(INB,HIGH);
        analogWrite(PWM, 150);
        lcd.setCursor(0,1);
        lcd.print("           ");
        lcd.setCursor(11,1);
        lcd.print("<<<<<");
       // delay(500);
      }
      else if ((peak)>=329.10 && (peak)<=330.10)
      {
        digitalWrite(INA,LOW);
        digitalWrite(INB,LOW);
        lcd.setCursor(0,1);
        lcd.print("     ");
        lcd.setCursor(11,1);
        lcd.print("     ");
        lcd.setCursor(6,1);
        lcd.print("Tune");
        delay(2000);
       
      }
    }
  }
 }
