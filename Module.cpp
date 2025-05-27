#include "Module.h"

void SpiceDispenser::start()
{
  lcd.setCursor(0, 0);
  lcd.print("Spice Cat id-" + String(id));
  lcd.setCursor(0, 1);
  lcd.print("Weight- " + String(weight));
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
  Serial.print("Error in Spice Dispenser with ID: ");
  Serial.println(id);
}

void Hopper::start()
{
  lcd.setCursor(0, 0);
  lcd.print("Hopper Cat id-" + String(id));
  lcd.setCursor(0, 1);
  lcd.print("Weight- " + String(weight));
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
void BoilingWater::start()
{
  lcd.setCursor(0, 0);
  lcd.print("Boiling water...");
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
