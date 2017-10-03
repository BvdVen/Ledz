#include <Arduino.h>

//Led pin groups
int rd1[] = {13, 15}; // example of a pin group

//END Led pin groups

class LedzGroup;
class LedzItem;

//IntArray
typedef struct {
  LedzGroup *array;
  size_t used;
  size_t size;
} LedzGroupArray;

typedef struct {
  LedzItem *array;
  size_t used;
  size_t size;
} LedzItemArray;

typedef struct {
  int *array;
  size_t used;
  size_t size;
} IntArray;


void initArray(IntArray *a, size_t initialSize) {
  a->array = (int *)malloc(initialSize * sizeof(int));
  a->used = 0;
  a->size = initialSize;
}

void insertArray(IntArray *a, int element) {
  // a->used is the number of used entries, because a->array[a->used++] updates a->used only *after* the array has been accessed.
  // Therefore a->used can go up to a->size
  if (a->used == a->size) {
    a->size *= 2;
    a->array = (int *)realloc(a->array, a->size * sizeof(int));
  }
  a->array[a->used++] = element;
}

void freeArray(IntArray *a) {
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}
//End IntArray

//LEDZ ITEM
class LedzItem {
  private:
    IntArray pins;
    int nrPins;
    int duration;
  public:
    LedzItem() {
        initArray(&pins, 1);
        this->nrPins = 0;
        this->duration = 0;
    };
    LedzItem(int dur) {
      initArray(&pins, 1);
      this->nrPins = 0;
      this->duration = dur;
    };
    void addPin(int pin) {
      if (pin > 0) {
        insertArray(&pins, pin);
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
      Serial.println(duration);
      delay(this->duration);
      delay(3000);

      //disable pins
      togglePins(false);
    };

    void togglePins(bool isHigh) {
      for (int i = 0; i < this->nrPins; i++)
      {
        if (isHigh)
          digitalWrite(this->pins.array[i], HIGH);
        else
          digitalWrite(this->pins.array[i], LOW);
      }
    };
};
// END LEDZ ITEM


//LedzItemArray

void initLedzItemArray(LedzItemArray *a, size_t initialSize) {
  a->array = (LedzItem *)malloc(initialSize * sizeof(int));
  a->used = 0;
  a->size = initialSize;
}

void insertLedzItemArray(LedzItemArray *a, LedzItem element) {
  if (a->used == a->size) {
    a->size *= 2;
    a->array = (LedzItem *)realloc(a->array, a->size * sizeof(int));
  }
  a->array[a->used++] = element;
}

void freeLedzItemArray(LedzItemArray *a) {
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}
//End LedzItemArray

//LEDZ GROUP
class LedzGroup {
  private:
    LedzItemArray items;
    int nrItems;
    int repetitions ;
  public:
    LedzGroup() {
        initLedzItemArray(&items,1);
        this->nrItems = 0;
        this->repetitions = 0;
    };
    LedzGroup(int repetitions) {
      initLedzItemArray(&items,1);
      this->repetitions = repetitions;
      this->nrItems = 0;
    };
    LedzItem* add(int duration) {
      Serial.println("Added LedzItem");
      LedzItem ledzItem = LedzItem(duration);
      insertLedzItemArray(&this->items, ledzItem);
      this->nrItems++;

      return &this->items.array[this->nrItems - 1];
    };

    void start() {
      Serial.print("START() GROUP: ");

      Serial.print("Repetitions: ");
      Serial.println(this->repetitions);
      Serial.println(this->nrItems);

      //number of repetitions
      for (int repetition = 0; repetition < this->repetitions; repetition++) {

        //loop through items
        for (int itemI = 0; itemI < this->nrItems; itemI++) {
          this->items.array[itemI].start();
        }
      }
    };

};

//END LEDZ GROUP



void initLedzGroupArray(LedzGroupArray *a, size_t initialSize) {
  a->array = (LedzGroup *)malloc(initialSize * sizeof(int));
  a->used = 0;
  a->size = initialSize;
}

void insertLedzGroupArray(LedzGroupArray *a, LedzGroup element) {
  if (a->used == a->size) {
    a->size *= 2;
    a->array = (LedzGroup *)realloc(a->array, a->size * sizeof(int));
  }
  a->array[a->used++] = element;
};

void freeLedzGroupArray(LedzGroupArray *a) {
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
};

// LEDZ
class Ledz {

  private:
    LedzGroupArray groups;

  public:
    int nrGroups;
    Ledz() {
      this->nrGroups = 0;
      initLedzGroupArray(&groups, 1);
    };

    void start() {

      Serial.print("nr groups: ");
      Serial.println(this->nrGroups);

      //loop through groups
      for (int groupI = 0; groupI < this->nrGroups; groupI++) {
        this->groups.array[groupI].start();
      }
    };

    LedzGroup* add(int repetitions)
    {
      LedzGroup ledzGroup = LedzGroup(repetitions);

      insertLedzGroupArray(&groups, ledzGroup);

      this->nrGroups++;
      return &groups.array[this->nrGroups - 1];
    };
};

//END LEDZ

Ledz ledz = Ledz();

void setup() {

  Serial.begin(9600);
  pinMode(13, OUTPUT);
  pinMode(15, OUTPUT);
  pinMode(16, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(18, OUTPUT);
  pinMode(19, OUTPUT);

  Serial.println("Setup");

  LedzGroup* ledzGroup;
  LedzItem* ledzItem;

  //Group 1
  ledzGroup = ledz.add(5); //repetitions
  ledzItem = ledzGroup->add(3000); // duration
  //ledzItem->addPins(2, rd1); //pins array
  ledzItem->addPin(13);
  ledzItem->addPin(15);
 ledzItem->addPin(16);
  ledzItem->addPin(17);
  ledzItem->addPin(18);*/

   ledzItem = ledzGroup->add(5000);
    ledzItem->addPin(15); //pin
    ledzItem->addPin(13); //pin

    // Group 2
    ledzGroup = ledz.add(2);
    ledzItem = ledzGroup->add(1000);
    ledzItem->addPin(13);

 ledzGroup = ledz.add(2);
 ledzItem = ledzGroup->add(1000);
    ledzItem->addPin(13);

  ledzGroup = ledz.add(2);
  ledzItem = ledzGroup->add(1000);
    ledzItem->addPin(13);

   ledzGroup = ledz.add(2);
   ledzItem = ledzGroup->add(1000);
    ledzItem->addPin(13);

    ledzGroup = ledz.add(2);
    ledzItem = ledzGroup->add(1000);
    ledzItem->addPin(13);

  Serial.println("Finished setup");
}

void loop() {
    delay(3000);
  ledz.start();
}
