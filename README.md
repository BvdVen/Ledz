# Ledz
First Arduino project to control leds.

## 'Pseudocode'
The Ledz program can contain multiple LedzGroups, a LedzGroup contains the repetition count and can contain multiple LedzItems. A LedzItenm contains one or multiple pins and the duration these pins are 'active' (digitalWrite High).

Ledz{
  LedzGroups{
    LedzGroup{
      repetition: ##,
      ledzItems:{
        LedzItem{
          duration: ##,
          pins{
            ##,
            ##
          }
        }
      }
    },
    LedzGroup{....}
  }
}

## Configure
LedzGroup* ledzGroup;
LedzItem* ledzItem;


//Group 1

ledzGroup = ledz.add(5); //repetitions

ledzItem = ledzGroup->add(3000); // duration

ledzItem->addPins(2, rd1); //pins array



ledzItem = ledzGroup->add(5000);

ledzItem->addPin(15); //pin

ledzItem->addPin(13); //pin

