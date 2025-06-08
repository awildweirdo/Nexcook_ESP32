#ifndef MODULE_H
#define MODULE_H

#include <Arduino.h> // required for String and millis()
#include <LiquidCrystal.h>
extern LiquidCrystal lcd;

class Module
{
public:
  virtual void start() = 0;
  virtual void stop() = 0;
  //virtual bool isBusy() = 0;
  int id = 0;
  int weight = 0;
  int vol = 0;
  int temp = 0;
  bool busy;
};

class SpiceDispenser : public Module
{
public:
  void start() override;
  void stop() override;
  //bool isBusy() override;
  void errorhan();
  //int weight;
  //int id;
  //bool busy;
  bool error;
  int errorID;

};

class Hopper : public Module
{
public:
  void start() override;
  void stop() override;
  //bool isBusy() override;
  //int weight;
  //int id;
  //bool busy;
  bool error;
  int errorID;
};

class Grind : public Module
{
public:
  void start() override;
  void stop() override;
  //bool isBusy() override;
  //bool busy;
  bool error;
};

class Chop : public Module
{
public:
  void start() override;
  void stop() override;
  //bool isBusy() override;
  //bool busy;
  bool error;
};

class Heat : public Module
{
public:
  void start() override;
  void stop() override;
  //bool isBusy() override;
  //int temp;
  //bool busy;
  bool error;

};

class OilDispenser : public Module
{
public:
  void start() override;
  void stop() override;
  //bool isBusy() override;
  //int vol;
  //bool busy;
  bool error;
};

class WaterDispenser :public Module
{
public:
  void start() override;
  void stop() override;
  //bool isBusy() override;
  //int vol;
  //bool busy;
  bool error;
};

class BoilingWater : public Module
{
public:
  void start() override;
  void stop() override;
  //bool isBusy() override;
  //bool busy;
  bool error;
};

class Steamer : public Module
{
public:
  void start() override;
  void stop() override;
  //bool isBusy() override;
  //bool busy;
  bool error;
};

class Stirrer : public Module
{
public:
  void start() override;
  void stop() override;
  //bool isBusy() override;
  //bool busy;
  bool error;
};

class Cleaning : public Module
{
public:
  void start() override;
  void stop() override;
  //bool isBusy() override;
  //bool busy;
  bool error;
};

#endif
