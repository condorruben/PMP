#include <Arduino.h>
#include <dht.h>

// used PINS { A0, 4, 6, 7, 8, 9 }

#pragma region Modes
#define NONE_MODE 0xFF
#define MAGIC_MODE 0
#define TEMPERATURE_MODE 1
#define HUMIDITY_MODE 2
#define FLAME_MODE 3
#pragma endregion

#pragma region Setup and Loop variables
byte mode = -1;
#pragma endregion

#pragma region Magic Variables
int magicLedPinA = 9;
int magicSwitchPinA = 8;
int magicSwitchStateA = 0;
int magicLedPinB = 6;
int magicSwitchPinB = 7;
int magicSwitchStateB = 0;
int magicBrightness = 0;
#pragma endregion

#pragma region TempHumidi Variables
int tempHumidiPin = 4;
dht tempHumidiDHT;
#pragma endregion

#pragma region Flame Variables
int flamePin = A0;
int flameValue = 0;
#pragma endregion

#pragma region Magic Functions
void MagicSetup()
{    
    pinMode(magicLedPinA, OUTPUT); 
    pinMode(magicLedPinB, OUTPUT);  
    pinMode(magicSwitchPinA, INPUT); 
    pinMode(magicSwitchPinB, INPUT);
}

void MagicRun()
{
    for(int i = 0; i < 10000; ++i)
    {
        magicSwitchStateA = digitalRead(magicSwitchPinA);
        if (magicSwitchStateA == HIGH && magicBrightness != 255)
        { 
            magicBrightness ++;
        } 

        magicSwitchStateB = digitalRead(magicSwitchPinB);
        if (magicSwitchStateA == LOW && magicBrightness != 0)
        { 
        magicBrightness --;
        } 

        analogWrite(magicLedPinA, magicBrightness);         
        analogWrite(magicLedPinB, 255 - magicBrightness);   

        delay(1);
    }
    analogWrite(magicLedPinA, 0);         
    analogWrite(magicLedPinB, 0); 
    Serial.println("Game Over");
    
}
#pragma endregion

#pragma region TempHumidi Functions
void TempHumidiSetup()
{
    return;
}

void TempHumidiRun(int mode)
{
    tempHumidiDHT.read11(tempHumidiPin);

    if (mode == TEMPERATURE_MODE)
    {
        Serial.print("The temperature is ");
        Serial.print(tempHumidiDHT.temperature);
        Serial.println(" degrees celsius");
    }
    if (mode == HUMIDITY_MODE)
    {
        Serial.print("The humidity is ");
        Serial.print(tempHumidiDHT.humidity);
        Serial.println(" %");
    }
    delay(1500);
}
#pragma endregion

#pragma region Flame Functions
void FlameSetup()
{
    return;
}

void FlameRun()
{
    for (int i = 0; i < 500; ++i)
    {
        flameValue = analogRead(flamePin);

        if (flameValue < 95)
        {
            Serial.println("Yes, I sense fire ");
            return;
        }
        delay(10);
    }
    Serial.println("No, there is no fire nearby");
}
#pragma endregion

#pragma region Setup and Loop
void setup() 
{   
    Serial.begin(9600);
    MagicSetup();
    TempHumidiSetup();
    FlameSetup();

    Serial.println("Arduino Configured");
}

void loop() 
{
    if (Serial.available())
    {
        mode = Serial.read();

        switch (mode)
        {
            case NONE_MODE:
                Serial.println("None Mode");

                break;
            case MAGIC_MODE:
                MagicRun();

                break;
            case TEMPERATURE_MODE:
                TempHumidiRun(TEMPERATURE_MODE);

                break;
            case HUMIDITY_MODE:
                TempHumidiRun(HUMIDITY_MODE);

                break;
            case FLAME_MODE:
                FlameRun();

                break;
        
            default:
                break;
        }
    }
    
}
#pragma endregion
