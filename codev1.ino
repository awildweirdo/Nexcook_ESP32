#include <LiquidCrystal.h>
#include "Module.h"

//Addtional parameter structure
typedef struct{
  int id = -1;
  int weight = -1;
  int vol = -1;
  int temp = -1; 
}moduleparams;

typedef struct{
  Module* module;
  int duration;
  moduleparams params;
}TaskInstruction;

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


//Create task queues and task handlers
QueueHandle_t queueA, queueB;
TaskHandle_t taskprocessorA,taskprocessorB;

//some baic initialization
String inputString = "";
bool stringcmp = false;
LiquidCrystal lcd(19, 23, 18, 17, 16, 15);



void setup()
{
    lcd.begin(16, 2);
    Serial.begin(9600);

    //Start RTOS queues
    queueA=xQueueCreate(10,sizeof(TaskInstruction));
    queueB=xQueueCreate(10,sizeof(TaskInstruction));
    xTaskCreatePinnedToCore(taskProcessor, "processorA", 4096, (void*)queueA,1,&taskprocessorA,0); //runs on core0
    xTaskCreatePinnedToCore(taskProcessor, "processorB", 4096, (void*)queueB,1,&taskprocessorB,1); //runs on core1
}


void loop()
{
    lcd.setCursor(0, 0);
    lcd.print("Waiting...");
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
  /*for now any recipe inputs would be processed as spinach rice...implement
  a if block with each recipe name (item) assigning steps in format below...
  FUTURE: update check function to check availability all ingredients required
  for recipe*/ 

    static TaskInstruction tasks[] = {
    // Dispense onions
    { &hopper, 1000, { .id = 1, .weight = 100 } },

    // Chop onions
    { &chop, 1000, { } },

    // Dispense oil
    { &oildis, 1000, { .vol = 10 } },

    // Heat oil to 170
    { &heat, 2000, { .temp = 170 } },

    // Dispense mustard
    { &spicedis, 1000, { .id = 1, .weight = 5 } },

    // Dispense cumin
    { &spicedis, 1000, { .id = 2, .weight = 5 } },

    // Wait for spices to cook
    { &stirrer, 10000, { } }, // Use stirrer as dummy to delay

    // Add chopped onions to pan
    { &hopper, 5000, { .id = 1, .weight = 100 } },

    // Turn heat to 140
    { &heat, 2000, { .temp = 140 } },

    // Dispense tomatoes
    { &hopper, 1000, { .id = 3, .weight = 100 } },

    // Chop tomatoes
    { &chop, 1000, { } },

    // Add chopped tomatoes to pan
    { &hopper, 1000, { .id = 3, .weight = 100 } },

    // Dispense ginger-garlic
    { &hopper, 1000, { .id = 4, .weight = 20 } },

    // Grind ginger-garlic
    { &grind, 1000, { } },

    // Add ground ginger-garlic
    { &hopper, 1000, { .id = 4, .weight = 20 } },

    // Turn heat to 130
    { &heat, 2000, { .temp = 130 } },

    // Dispense spinach
    { &hopper, 1000, { .id = 5, .weight = 200 } },

    // Steam spinach
    { &steam, 2000, { } },

    // Add water
    { &waterdis, 1000, { .vol = 250 } },

    // Turn heat to 100
    { &heat, 2000, { .temp = 100 } },

    // Add rice
    { &hopper, 1000, { .id = 4, .weight = 200 } },

    // Turn heat to 90 and wait
    { &heat, 5000, { .temp = 90 } },

    // Add spinach again
    { &hopper, 1000, { .id = 5, .weight = 200 } },

    // stir
    { &stirrer, 2000, { } }
  };

  //send return data to rpi
  Serial.println("MODULE:water-dispenser=-250,spice-dispenser=-10,hopper-dispenser=-100,hopper-dispenser=-100,hopper-dispenser=-20,hopper-dispenser=-200");


  int taskCount = sizeof(tasks) / sizeof(TaskInstruction);
  dispatcher(tasks, taskCount);
}

//Dispatcher function
void dispatcher(TaskInstruction* taskList, int taskCount) {
  bool sendToA = true;

  for (int i = 0; i < taskCount; i++) {
    TaskInstruction task = taskList[i];
    Module* module = task.module;  // Use pointer from struct

    if (module == nullptr) {
      Serial.println("Null module pointer.");
      continue;
    }

    if (!module->busy) {
      BaseType_t status;
      if (sendToA) {
        status = xQueueSend(queueA, &task, portMAX_DELAY);
      } else {
        status = xQueueSend(queueB, &task, portMAX_DELAY);
      }

      if (status == pdPASS) {
        module->busy = true;
        sendToA = !sendToA;
      } else {
        Serial.println("Queue full, retrying...");
        i--;
        vTaskDelay(100 / portTICK_PERIOD_MS);
      }
    } else {
      i--;
      vTaskDelay(100 / portTICK_PERIOD_MS);
    }
  }
}


//task processor to handle tasks from dispatcher
void taskProcessor(void* pvParameters) {
  QueueHandle_t queue = (QueueHandle_t) pvParameters;
  TaskInstruction task;

  while (true) {
    if (xQueueReceive(queue, &task, portMAX_DELAY)) {
      Module* module = task.module;

      if (module != nullptr) {
        // Apply parameters to module
        module->id     = task.params.id;
        module->weight = task.params.weight;
        module->vol    = task.params.vol;
        module->temp   = task.params.temp;

        module->busy = true;

        module->start();  // Act on parameters already set above

        vTaskDelay(task.duration / portTICK_PERIOD_MS);

        module->stop();

        module->busy = false;
      } else {
        Serial.println("Null module pointer received in task.");
      }
    }
  }
}

