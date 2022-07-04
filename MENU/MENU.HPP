#ifndef MENU_HPP
#define MENU_HPP

#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <graphics.h>
#include <string.h>
#include "./MENU/MENUITEM.HPP"
#include "./GRMODE.HPP"

class Menu {
 private:
  MenuItem *items;
  unsigned itemsQuantity, menuLevel;
  int menuBackColor;
  int defaultItemColor, highlightedItemColor, selectedItemColor;
  int disabledItemColor;
  int logicalXCoordinate, logicalYCoordinate;

  void outputColoredItem(unsigned itemNo) {
   if (items[itemNo].isEnabled()) {
    setcolor(defaultItemColor);
   }
   if (!items[itemNo].isEnabled()) {
    setcolor(disabledItemColor);
   }
   if (items[itemNo].isHighlighted()) {
    setcolor(highlightedItemColor);
   }
   if (items[itemNo].isSelected()) {
    setcolor(selectedItemColor);
   }
   outtextxy(menuLevel * 40, 7 + itemNo * 7, items[itemNo].getCaption());
  }
 public:
  Menu() {
   this->menuLevel = 1;
   this->itemsQuantity = 1;
   this->menuBackColor = GREEN;
   this->defaultItemColor = WHITE;
   this->highlightedItemColor = YELLOW;
   this->selectedItemColor = RED;
   this->disabledItemColor = LIGHTGRAY;
   this->logicalXCoordinate = 120 * menuLevel + 7;
   this->logicalYCoordinate = 0;
   items = new MenuItem[itemsQuantity];
  }
  Menu(
   MenuItem *miItems,
   unsigned itemsQuantity,
   unsigned level = 1,
   int menuBackColor = GREEN,
   int defaultItemColor = WHITE,
   int highlightedItemColor = YELLOW,
   int selectedItemColor = RED,
   int disabledItemColor = LIGHTGRAY
  ) {
   this->itemsQuantity = itemsQuantity;
   this->menuBackColor = menuBackColor;
   this->defaultItemColor = defaultItemColor;
   this->highlightedItemColor = highlightedItemColor;
   this->selectedItemColor = selectedItemColor;
   this->disabledItemColor = disabledItemColor;
   this->logicalXCoordinate = 120 * menuLevel + 7;
   this->logicalYCoordinate = 0;
   this->menuLevel = level;

   items = new MenuItem[itemsQuantity];
   for (unsigned i = 0; i < itemsQuantity; i++) {
    items[i] = miItems[i];
   }
  }
  Menu(const Menu &right) {
   this->itemsQuantity = right.itemsQuantity;
   this->menuBackColor = right.menuBackColor;
   this->defaultItemColor = right.defaultItemColor;
   this->highlightedItemColor = right.highlightedItemColor;
   this->selectedItemColor = right.selectedItemColor;
   this->disabledItemColor = right.disabledItemColor;
   this->menuLevel = right.menuLevel;
   this->logicalXCoordinate = right.logicalXCoordinate;
   this->logicalYCoordinate = right.logicalYCoordinate;

   items = new MenuItem[right.itemsQuantity];
   for (unsigned i = 0; i < right.itemsQuantity; i++) {
    items[i] = right.items[i];
   }
  }
  Menu& operator = (const Menu &right) {
   this->itemsQuantity = right.itemsQuantity;
   this->menuBackColor = right.menuBackColor;
   this->defaultItemColor = right.defaultItemColor;
   this->highlightedItemColor = right.highlightedItemColor;
   this->selectedItemColor = right.selectedItemColor;
   this->disabledItemColor = right.disabledItemColor;
   this->menuLevel = right.menuLevel;
   this->logicalXCoordinate = right.logicalXCoordinate;
   this->logicalYCoordinate = right.logicalYCoordinate;

   items = new MenuItem[right.itemsQuantity];
   for (unsigned i = 0; i < right.itemsQuantity; i++) {
    items[i] = right.items[i];
   }
   return *this;
  }
  void show() {
   GrMode::initGraphicalMode();

   setcolor(this->defaultItemColor);
   setfillstyle(SOLID_FILL, this->menuBackColor);
   bar(120 * (menuLevel - 1), 0, menuLevel * 120, 480);
   for (unsigned i = 0; i < itemsQuantity; i++) {
    this->outputColoredItem(i);
   }
  }
  void redrawItems() {
   for (unsigned i = 0; i < itemsQuantity; i++) {
    this->outputColoredItem(i);
   }
  }
  MenuItem* getItems() {
   return items;
  }
  unsigned getItemsQuantity() {
   return this->itemsQuantity;
  }
  MenuItem& getItem(unsigned itemNo) {
   if (itemNo >= itemsQuantity) {
    printf("%d is incorrect number of menu item. It cannot be negative or >= menu items quantity\nMenu items quantity is %d\n", itemNo, itemsQuantity);
    printf("Press any key to halt:");
    getch();
    exit(1);
   }
   return this->items[itemNo];
  }
  MenuItem& getSelectedItem() {
   MenuItem *si = new MenuItem();
   for (unsigned i = 0; i < this->itemsQuantity; i++) {
    if (this->items[i].isSelected()) {
     *si = this->items[i];
    }
   }
   return *si;
  }
  int getLogicalXCoordinate() {
   return logicalXCoordinate;
  }
  int getLogicalYCoordinate() {
   return logicalYCoordinate;
  }
  void increaseItemNumber(int &itemNo) {
   if (itemNo == NULL) {
    itemNo = 0;
   }
   unsigned itemsQuantity = this->getItemsQuantity();
   if (itemNo >= 0 && itemNo < itemsQuantity - 1) {
    itemNo = itemNo + 1;
   }
   if (itemNo > itemsQuantity - 1) {
     itemNo = itemNo % itemsQuantity;
    }
  }
  void decreaseItemNumber(int &itemNo) {
   if (itemNo == NULL) {
    itemNo = 0;
   }
   unsigned itemsQuantity = this->getItemsQuantity();
   if (itemNo > 0 && itemNo < itemsQuantity) {
    itemNo = itemNo - 1;
   }
   if (itemNo < 0) {
    if (abs(itemNo) > itemsQuantity) {
     itemNo = itemsQuantity - (abs(itemNo) % itemsQuantity);
    } else {
     itemNo = itemsQuantity + itemNo;
    }
   }
  }
  void enableItem(unsigned itemNo) {
   items[itemNo].enable();
   setcolor(this->defaultItemColor);
  }
  void disableItem(unsigned itemNo) {
   items[itemNo].disable();
   setcolor(this->disabledItemColor);
  }
  void highlightItem(unsigned itemNo) {
   items[itemNo].highlight();
   setcolor(this->highlightedItemColor);
  }
  void cancelHighlightingItem(unsigned itemNo) {
   items[itemNo].cancelHighlighting();
   setcolor(this->defaultItemColor);
  }
  void selectItem(unsigned itemNo) {
   unsigned i;
   for (i = 0; i < itemNo; i++) {
    items[i].cancelSelecting();
   }
   for (i = itemNo + 1; i < itemsQuantity; i++) {
    items[i].cancelSelecting();
   }
   items[itemNo].select();
   setcolor(this->selectedItemColor);
  }
  void cancelSelectingItem(unsigned itemNo) {
   items[itemNo].cancelSelecting();
   setcolor(this->highlightedItemColor);
  }
  ~Menu() {
   delete [] items;
  }
};

#endif