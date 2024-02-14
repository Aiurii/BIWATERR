
//PROIEKTUKO LIBURUTEGIAK
#include <OneWire.h>
#include <DallasTemperature.h>


#include <LCD_I2C.h>

OneWire ourWire(2);
DallasTemperature sensors(&ourWire);

LCD_I2C lcd(0x27, 20, 4); // PCF8574 modulu gehienen helbide lehenetsia, pantailaren arabera

int pinAnalogico=A0;

#define SensorpH A1          // the pH meter Analog output is connected with the Arduino’s Analog
unsigned long int avgValue;  //Store the average value of the sensor feedback
float b;
int buf[10],temp1;



void setup()
{
  Serial.begin(9600);
  lcd.begin(); // Wire liburutegia erabiliz I2C gailu gehiago erabiltzen ari bazara, erabili lcd.begin(false)
                 // honek liburutegiari (LCD_I2C) Wire.begin() deitzeari uzten dio
  lcd.backlight();
    
  sensors.begin();
}

void loop()
{

//TEMPERATURA
sensors.requestTemperatures();
float temp=sensors.getTempCByIndex(0);

//pH VALUE
 for(int i=0;i<10;i++)       //Get 10 sample value from the sensor for smooth the value
  { 
    buf[i]=analogRead(SensorpH);
    delay(10);
  }
  for(int i=0;i<9;i++)        //sort the analog from small to large
  {
    for(int j=i+1;j<10;j++)
    {
      if(buf[i]>buf[j])
      {
        temp1=buf[i];
        buf[i]=buf[j];
        buf[j]=temp1;
      }
    }
  }
  avgValue=0;
  for(int i=2;i<8;i++)                      //take the average value of 6 center sample
    avgValue+=buf[i];
  float phValue=(float)avgValue*5.0/1024/6; //convert the analog into millivolt
  phValue=3.5*phValue;                      //convert the millivolt into pH value


//TURBIEDAD
int valorAnalogo=analogRead(pinAnalogico);
float (valorTurbiedad)=map(valorAnalogo, 900, 10, 0, 100);


    
//PANTALLA    
    lcd.setCursor(0, 0);
    lcd.print("Tenperatura:");
    lcd.print(temp);
    lcd.print("C");
    lcd.setCursor(0, 1); 
    lcd.print("pH kantitatea: ");
    lcd.print(phValue,2);
    lcd.setCursor(0, 2); 
    lcd.print("o2 kantitatea: ");
    lcd.setCursor(0, 3); 
    lcd.print("Turbidity: ");
    lcd.print(valorTurbiedad);
    delay(1000);
    //delay(2000);

   

    //lcd.backlight();
    //lcd.clear();
}


