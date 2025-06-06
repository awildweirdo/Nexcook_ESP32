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
    if (errorchk()) {
        return;
    }

    if (stringcmp)
    {
        inputString.trim(); // Clean \r and \n

        if (inputString.startsWith("RECIPE:"))
        {
            String recipeName = inputString.substring(7);
            recipeName.toLowerCase();
            cookrecipe(recipeName);
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

void cookrecipe(String item){
  spinachrice();
}

void spinachrice(){
  //dispensing onions to grinder
  hopper.id=1; //id=1 is onion
  hopper.weight=100;
  hopper.busy=true;
  hopper.start();
  hopper.busy=false;
  hopper.stop();

  //chopping onions
  chop.start();
  chop.stop();

  //dispense 10ml oil
  oildis.vol=10;
  oildis.start();
  oildis.stop();

  //heat oil to 170
  heat.temp=170;
  heat.start();
  heat.stop();

  //spice dispense mustard
    spicedis.id=1; //id=1 is mustard
    spicedis.weight=5; //5 grams of mustard
    spicedis.start();
    spicedis.stop();
    //spice dispense cumin
    spicedis.id=2; //id=2 is cumin
    spicedis.weight=5; //5 grams of cumin
    spicedis.start();
    spicedis.stop();

    delay(10000); // Wait for spices to be added
    //add chopped onions to pan
    hopper.id=1; //id=1 is onion
    hopper.weight=100; //100 grams of onion
    hopper.start();
    delay(5000); // Wait for onions to be added
    hopper.stop();
    
    //turn heat to 140
    heat.temp=140;
    heat.start();
    heat.stop();
    
    //dispense tomatos
    hopper.id=3; //id=3 is tomato
    hopper.weight=100; //100 grams of tomato
    hopper.start();
    hopper.stop();

    //chopping tomatos
    chop.start();
    chop.stop();

    //add chopped tomatos to pan
    hopper.id=3; //id=3 is tomato
    hopper.weight=100; //100 grams of tomato
    hopper.start();
    hopper.stop();
    
    //dispense ginger and garlic
    hopper.id=4; //id=4 is ginger and garlic
    hopper.weight=20; //20 grams of ginger and garlic
    hopper.start();
    hopper.stop();

    //grinding ginger and garlic
    grind.start();
    grind.stop();

    //dispense ground ginger and garlic to pan
    hopper.id=4; //id=4 is ginger and garlic
    hopper.weight=20; //20 grams of ginger and garlic
    hopper.start();
    hopper.stop(); 

    //turn heat to 130
    heat.temp=130;  
    heat.start();
    heat.stop();
    
    //dispense spinach
    hopper.id=5; //id=5 is spinach
    hopper.weight=200; //200 grams of spinach
    hopper.start();
    hopper.stop();

    //steam spinach
    steam.start();  
    steam.stop(); 

    //water dispense 250ml
    waterdis.vol=250; //250ml of water      
    waterdis.start();
    waterdis.stop();

    //turn heat to 100
    heat.temp=100;
    heat.start();
    heat.stop();

    //add rice
    hopper.id=4; //id=4 is rice
    hopper.weight=200; //200 grams of rice
    hopper.start();
    hopper.stop();

    //turn heat to 90
    heat.temp=90;
    heat.start();
    delay(5000);
    heat.stop();

    //dispense spinach 
    hopper.id=5; //id=5 is spinach
    hopper.weight=200; //200 grams of spinach
    hopper.start();
    hopper.stop();

    //stir the mixture
    stirrer.start();
    lcd.clear();
    Serial.println("complete");

    //return module data to rpi
    Serial.println("MODULE:water-dispenser=-250,spice-dispenser=-10,hopper-dispenser=-100,hopper-dispenser=-100,hopper-dispenser=-20,hopper-dispenser=-200");

    return;

}

/*
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
}*/

bool errorchk(){
  if(digitalRead(13)){
    spicedis.errorID=1;
    spicedis.error= true;
    spicedis.errorhan();
    return true;
  }
  return false;
}