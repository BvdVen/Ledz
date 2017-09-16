#include <Arduino.h>

const int MAXGROUPS = 10; //number of LedzGroups you want to create
const int MAXITEMS = 10; // max number of items in a LedzGroup
const int MAXPINS = 16; // max number of pins in an LedzItem

//Led pin groups
int rd1[] = {13, 15}; // example of a pin group

//END Led pin groups

//LEDZ ITEM
class LedzItem {
  private:
    int pins[MAXPINS];
    int nrPins = 0;
    int duration = 0;
  public:
    LedzItem() {};
    LedzItem(int dur) {
      this->nrPins = 0;
      this->duration = dur;
    };
    void addPin(int pin) {
      if (pin > 0) {
        this->pins[this->nrPins] = pin;
        this->nrPins++;
        Serial.println(pin);
      }
    };
    void addPins(int size, int pins[]) {
      for (int i = 0; i < size; i++) {
        addPin(pins[i]);
      }
    };

    void start() {

      //enable pins
      togglePins(true);

      //delay
      Serial.print("duration: ");
      Serial.println(this->duration);
      delay(this->duration);

      //disable pins
      togglePins(false);
    };

    void togglePins(bool isHigh) {
      for (int i = 0; i < this->nrPins; i++)
      {
        if (isHigh)
          digitalWrite(this->pins[i], HIGH);
        else
          digitalWrite(this->pins[i], LOW);
      }
    };
};

// END LEDZ ITEM

//LEDZ GROUP
class LedzGroup {
  private:
    LedzItem items[MAXITEMS];
    int nrItems = 0;
    int repetitions = 0;
  public:
    LedzGroup() {};
    LedzGroup(int repetitions) {
      this->repetitions = repetitions;
      this->nrItems = 0;
    };
    LedzItem* add(int duration) {
      //Serial.println("Added LedzItem");
      LedzItem ledzItem = LedzItem(duration);
      this->items[this->nrItems] = ledzItem;
      this->nrItems++;
      return &this->items[this->nrItems - 1];
    };

    void start() {
      Serial.print("START() GROUP: ");

      Serial.print("Repetitions: ");
      Serial.println(this->repetitions);
      //number of repetitions
      for (int repetition = 0; repetition < this->repetitions; repetition++) {

        //loop through items
        for (int itemI = 0; itemI < this->nrItems; itemI++) {
          this->items[itemI].start();
        }
      }
    };

};

//END LEDZ GROUP

// LEDZ
class Ledz {

  private:
    LedzGroup groups[MAXGROUPS];

  public:
    int nrGroups = 0;
    Ledz() {
      this->nrGroups = 0;
    };

    void start() {

      Serial.print("nr groups: ");
      Serial.println(this->nrGroups);


      //loop through groups
      for (int groupI = 0; groupI < this->nrGroups; groupI++) {
        this->groups[groupI].start();
      }
    };

    LedzGroup* add(int repetitions)
    {
      LedzGroup ledzGroup = LedzGroup(repetitions);

      groups[this->nrGroups] = ledzGroup;

      this->nrGroups++;
      return &groups[this->nrGroups - 1];
    };
};

//END LEDZ

Ledz ledz = Ledz();

void setup() {

  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(15, OUTPUT);

  Serial.println("Setup");

  LedzGroup* ledzGroup;
  LedzItem* ledzItem;

  //Group 1
  ledzGroup = ledz.add(5); //repetitions
  ledzItem = ledzGroup->add(3000); // duration
  ledzItem->addPins(2, rd1); //pins array

   ledzItem = ledzGroup->add(5000);
    ledzItem->addPin(15); //pin
    ledzItem->addPin(13); //pin

    // Group 2
    ledzGroup = ledz.add(2);
    ledzItem = ledzGroup->add(1000);
    ledzItem->addPin(13);
  
  Serial.println("Finished setup");
}

void loop() {
  ledz.start();
}

