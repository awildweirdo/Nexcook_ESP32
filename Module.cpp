#include "Module.h"

void SpiceDispenser::start()
{
  lcd.setCursor(0, 0);
  lcd.print("Spice Cat id-" + String(id));
  lcd.setCursor(0, 1);
  lcd.print("Weight- " + String(weight));
  delay(5000);
}
void SpiceDispenser::stop()
{
  lcd.clear();
  lcd.setCursor(0, 0);
}
bool SpiceDispenser::isBusy()
{
  return busy;
}
void SpiceDispenser::errorhan()
{
  Serial.println("Error in Spice Dispenser with ID: "+String(errorID));
  
  delay(5000);
}

void Hopper::start()
{
  lcd.setCursor(0, 0);
  lcd.print("Hopper Cat id-" + String(id));
  lcd.setCursor(0, 1);
  lcd.print("Weight- " + String(weight));
  delay(5000);
}

void Hopper::stop()
{
  lcd.clear();
  lcd.setCursor(0, 0);
}

bool Hopper::isBusy()
{
  return busy;
}

void Grind::start()
{
  lcd.setCursor(0, 0);
  lcd.print("Grinding...");
  delay(5000);
}

void Grind::stop()
{
  lcd.clear();
  lcd.setCursor(0, 0);
}

bool Grind::isBusy()
{
  return busy;
}

void Chop::start()
{
  lcd.setCursor(0, 0);
  lcd.print("Chopping...");
  delay(5000);
}

void Chop::stop()
{
  lcd.clear();
  lcd.setCursor(0, 0);
}

bool Chop::isBusy()
{
  return busy;
}

void Heat::start()
{
  lcd.setCursor(0, 0);
  lcd.print("Heating to " + String(temp) + "C");
  delay(5000);
}

void Heat::stop()
{
  lcd.clear();
  lcd.setCursor(0, 0);
}

bool Heat::isBusy()
{
  return busy;
}

void Steamer::start()
{
  lcd.setCursor(0, 0);
  lcd.print("Steaming...");
  delay(5000);
}

void Steamer::stop()
{
  lcd.clear();
  lcd.setCursor(0, 0);
}

bool Steamer::isBusy()
{
  return busy;
}

void Stirrer::start()
{
  lcd.setCursor(0, 0);
  lcd.print("Stirring...");
  delay(5000);
}

void Stirrer::stop()
{
  lcd.clear();
  lcd.setCursor(0, 0);
}

bool Stirrer::isBusy()
{
  return busy;
}

void OilDispenser::start()
{
  lcd.setCursor(0, 0);
  lcd.print("Dispensing oil");
  lcd.setCursor(0, 1);
  lcd.print("Volume: " + String(vol) + "ml");
  delay(5000);
}

void OilDispenser::stop()
{
  lcd.clear();
  lcd.setCursor(0, 0);
}

bool OilDispenser::isBusy()
{
  return busy;
}

void WaterDispenser::start()
{
  lcd.setCursor(0, 0);
  lcd.print("Dispensing water");
  lcd.setCursor(0, 1);
  lcd.print("Volume: " + String(vol) + "ml");
  delay(5000);
}

void WaterDispenser::stop()
{
  lcd.clear();
  lcd.setCursor(0, 0);
}

bool WaterDispenser::isBusy()
{
  return busy;
}

void BoilingWater::start()
{
  lcd.setCursor(0, 0);
  lcd.print("Boiling water...");
  delay(5000);
}
void BoilingWater::stop()
{
  lcd.clear();
  lcd.setCursor(0, 0);
}
bool BoilingWater::isBusy()
{
  return busy;
}

void Cleaning::start()
{
  lcd.setCursor(0, 0);
  lcd.print("Cleaning...");
  delay(5000);
}

void Cleaning::stop()
{
  lcd.clear();
  lcd.setCursor(0, 0);
}

bool Cleaning::isBusy()
{
  return busy;
}
