#include <LiquidCrystal.h>
#include "Module.h"

// Module object creation
SpiceDispenser spicedis;
Hopper hopper;
Grind grind;
Chop chop;
Heat heat;
OilDispenser oildis;
BoilingWater boilw;
Steamer steam;
Stirrer stirrer;
Cleaning clean;

String inputString = "";
bool stringcmp = false;
LiquidCrystal lcd(19, 23, 18, 17, 16, 15);

//pin declarations for error inputs
int SPICE_ID1=13;


void setup()
{
    lcd.begin(16, 2);
    Serial.begin(9600);
    pinMode(SPICE_ID1, INPUT);
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
        if (module == "water")
        {
            dispenseOilWater(1, value);
        }
        else if (module == "spice")
        {
            dispenseSpice(1, value);
        }
        else if (module == "ingredients")
        {
            dispenseSpice(2, value); // For simplicity, treating ingredients as spice ID 2
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

bool errorchk(){
  if(digitalRead(13)){
    spicedis.errorID=1;
    spicedis.error= true;
    spicedis.errorhan();
    return true;
  }
  return false;
}

void dispenseSpice(int ID, int weight)
{
    lcd.clear();
    lcd.print("spice- ID: " + String(ID));
    lcd.setCursor(0, 1);
    lcd.print("Weight: " + String(weight));
    delay(10000);
    lcd.clear();
}

void dispenseOilWater(int ID, int weight)
{
    lcd.clear();
    lcd.print("Oil/water-ID: " + String(ID));
    lcd.setCursor(0, 1);
    lcd.print("Weight: " + String(weight));
    delay(10000);
    lcd.clear();
}
