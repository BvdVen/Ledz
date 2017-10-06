#include <Arduino.h>

//Led pin groups

int rd1[] = {13, 15}; // example of a pin group

//END Led pin groups

template<typename Data>
class List {
  size_t d_size; // Stores no. of actually stored objects
  size_t d_capacity; // Stores allocated capacity
  Data *d_data; // Stores data
  public:
    List() : d_size(0), d_capacity(0), d_data(0) {}; // Default constructor
    List(List const &other) : d_size(other.d_size), d_capacity(other.d_capacity), d_data(0) { d_data = (Data *)malloc(d_capacity*sizeof(Data)); memcpy(d_data, other.d_data, d_size*sizeof(Data)); }; // Copy constuctor
    ~List() { free(d_data); }; // Destructor
    List &operator=(List const &other) { free(d_data); d_size = other.d_size; d_capacity = other.d_capacity; d_data = (Data *)malloc(d_capacity*sizeof(Data)); memcpy(d_data, other.d_data, d_size*sizeof(Data)); return *this; }; // Needed for memory management
    void push_back(Data const &x) { if (d_capacity == d_size) resize(); d_data[d_size++] = x; }; // Adds new value. If needed, allocates more space
    size_t size() const { return d_size; }; // Size getter
    Data const &operator[](size_t idx) const { return d_data[idx]; }; // Const getter
    Data &operator[](size_t idx) { return d_data[idx]; }; // Changeable getter
  private:
    void resize() { d_capacity = d_capacity ? d_capacity*2 : 1; Data *newdata = (Data *)malloc(d_capacity*sizeof(Data)); memcpy(newdata, d_data, d_size * sizeof(Data)); free(d_data); d_data = newdata; };// Allocates double the old space
};

//LEDZ ITEM
class LedzItem {
  private:
    int duration;
    int pinSize;
  public:
    List<int> pins;
    LedzItem() {
        this->duration = 0;
    };
    LedzItem(int dur) {
      this->duration = dur;
    };
    int GetPinCount(){
        return pins.size();
    };
    void addPin(int pin) {
      if (pin > 0) {
        pins.push_back(pin);
      }
    };
    void addPins(int size, int newPins[]) {
      for (int i = 0; i < size; i++) {
        addPin(newPins[i]);
      }
    };

    void start() {
      //enable pins
      togglePins(true);

      //delay
      Serial.print("duration: ");
      Serial.println(duration);

      Serial.print("pins: ");
      Serial.println(pins.size());

      delay(this->duration);

      //disable pins
      togglePins(false);
    };

    void togglePins(bool isHigh) {
      for (int i = 0; i < pins.size(); i++)
      {
        if (isHigh)
          digitalWrite(pins[i], HIGH);
        else
          digitalWrite(pins[i], LOW);
      }
    };
};
// END LEDZ ITEM

//LEDZ GROUP
class LedzGroup {
  private:
    int repetitions ;
  public:
    List<LedzItem> items;
    LedzGroup() {
        this->repetitions = 0;
    };
    LedzGroup(int repetitions) {
      this->repetitions = repetitions;
    };
    LedzItem* add(int duration) {
      Serial.println("Added LedzItem");
      LedzItem ledzItem = LedzItem(duration);
      items.push_back(ledzItem);

      return &items[items.size() - 1];
    };

    void start() {
      Serial.print("START() GROUP: ");

      Serial.print("Repetitions: ");
      Serial.println(this->repetitions);
      Serial.print("Items: ");
      Serial.println(items.size());

      //number of repetitions
      for (int repetition = 0; repetition < this->repetitions; repetition++) {

        //loop through items
        for (int itemI = 0; itemI < items.size(); itemI++) {
          items[itemI].start();
        }
      }
    };

};

//END LEDZ GROUP

// LEDZ
class Ledz {

  public:
    List<LedzGroup> groups;
    Ledz() {
    };

    void start() {

      Serial.print("nr groups: ");
      Serial.println(groups.size());

      //loop through groups
      for (int groupI = 0; groupI < groups.size(); groupI++) {
        groups[groupI].start();
      }
    };

    LedzGroup* add(int repetitions)
    {
        Serial.print("nr groups: ");
      Serial.println(groups.size());

      LedzGroup ledzGroup = LedzGroup(repetitions);
      groups.push_back(ledzGroup);
      return &groups[groups.size() - 1];
    };
};

//END LEDZ

Ledz ledz = Ledz();

void initPins(){

    for (int groupI = 0; groupI < ledz.groups.size(); groupI++) {
            Serial.print("Group ");
            Serial.println(groupI);

            LedzGroup* lg = &ledz.groups[groupI];

        for(int itemI = 0; itemI < lg->items.size(); itemI++){
                Serial.print("   Item (");
                Serial.print(lg->items.size());
                Serial.print(") - ");
                Serial.println(itemI);

                 LedzItem li = lg->items[itemI];

           for(int pinI = 0; pinI < li.GetPinCount(); pinI++){

                Serial.print("      Pins ");
                Serial.println(li.pins[pinI]);

                pinMode(li.pins[pinI],OUTPUT);
            }
        }
    }
}

void setup() {

  Serial.begin(9600);

  Serial.println("Setup");

  LedzGroup* lg;
  LedzItem* li;

  //Group 1
  lg = ledz.add(1); //repetitions
    li = lg->add(2000); // duration
      li->addPin(14);
      li->addPin(15);
      li->addPin(16);
      li->addPin(17);

    li = lg->add(2000);
        li->addPin(18); //pin
        li->addPin(19); //pin

    // Group 2
   lg = ledz.add(2);
    li = lg->add(3000);
    li->addPin(14);
    li->addPins(2, rd1); //pins array

 lg = ledz.add(2);
 li = lg->add(1000);
    li->addPin(11);
    initPins();

  Serial.println("Finished setup");
}
void loop() {

Serial.println("Looping");

  ledz.start();

Serial.println("Finished Looping");
}
