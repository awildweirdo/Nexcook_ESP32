#include <LiquidCrystal.h>
#include "Module.h"

// Module object creation
SpiceDispenser spicedis;
Hopper hopper;
Grind grind;
Chop chop;
Heat heat;
OilDispenser oildis;
WaterDispenser waterdis;
BoilingWater boilw;
Steamer steam;
Stirrer stirrer;
Cleaning clean;

String inputString = "";
bool stringcmp = false;
LiquidCrystal lcd(19, 23, 18, 17, 16, 15);

//pin declarations for error inputs
int SPICE_ID1=13;

void  error_spice(){
    spicedis.errorID=1;
    spicedis.error= true;
    spicedis.errorhan();
    return;
  
}

void setup()
{
    lcd.begin(16, 2);
    Serial.begin(9600);
    pinMode(SPICE_ID1, INPUT);
    
    //Attach interrupts for error handling
    attachInterrupt(SPICE_ID1,error_spice,HIGH);
}

void loop()
{
    lcd.setCursor(0, 0);
    lcd.print("Waiting...");
    if(errorchk()){
      return;
    }
    if (stringcmp)
    {
        if (inputString.startsWith("MODULE:"))
        {
            parseAndExecute(inputString.substring(7));
        }
        else
        {
            Serial.println("Unknown command received.");
        }
        inputString = "";
        stringcmp = false;
    }
}

void serialEvent()
{
    while (Serial.available())
    {
        char inChar = (char)Serial.read();
        inputString += inChar;
        if (inChar == '\n' || inChar == '\r')
        {
            stringcmp = true;
        }
    }
}

void parseAndExecute(String command)
{
    lcd.clear();
    int lastIndex = 0;
    command += ','; // Add a trailing comma for parsing
    while (command.indexOf(',', lastIndex) != -1)
    {
        int nextIndex = command.indexOf(',', lastIndex);
        String moduleCommand = command.substring(lastIndex, nextIndex);
        int equalPos = moduleCommand.indexOf('=');
        String module = moduleCommand.substring(0, equalPos);
        int value = moduleCommand.substring(equalPos + 1).toInt();
        if(errorchk()){
          lcd.clear();
        return;
        }
        if (module == "water")
        {
            waterdis.vol=value;
            waterdis.start();
        }
        else if (module == "spice")
        {
            spicedis.id=1;
            spicedis.weight=value;
            spicedis.start();
        }
        else if (module == "ingredients")
        {
            hopper.id=2;
            hopper.weight=value;
            hopper.start();
        }
        else
        {
            lcd.print("Unkown");
        }
        lastIndex = nextIndex + 1;
    }
    Serial.println("complete");
    lcd.clear();
}

