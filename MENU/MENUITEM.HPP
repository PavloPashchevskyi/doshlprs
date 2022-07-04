#ifndef MENUITEM_HPP
#define MENUITEM_HPP

#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

class MenuItem {
 protected:
  char name[40], caption[40];
  unsigned enabled, highlighted, selected;
  void (*onSelect)();
 public:
  MenuItem() {
   strcpy(this->name, "");
   strcpy(this->caption, "");
   this->enabled = 1;
   this->highlighted = 0;
   this->selected = 0;

   this->onSelect = NULL;
  }
  MenuItem(
   char name[40],
   char caption[40],
   void (*onSelectCB)() = NULL
  ) {
   strcpy(this->name, "");
   strcpy(this->caption, "");
   strcat(this->name, name);
   strcat(this->caption, caption);
   this->enabled = 1;
   this->highlighted = 0;
   this->selected = 0;

   this->onSelect = onSelectCB;
  }
  char* getName() {
   return this->name;
  }
  void setName(char name[40]) {
   strcpy(this->name, name);
  }
  char* getCaption() {
   return this->caption;
  }
  void setCaption(char caption[40]) {
   strcpy(this->caption, caption);
  }
  unsigned isEnabled() {
   return this->enabled;
  }
  void enable() {
   this->enabled = 1;
  }
  void disable() {
   this->enabled = 0;
  }
  unsigned isHighlighted() {
   return this->highlighted;
  }
  void highlight() {
   this->highlighted = 1;
  }
  void cancelHighlighting() {
   this->highlighted = 0;
  }
  void toggle() {
   this->highlighted = (this->highlighted == 0) ? 1 : 0;
  }
  unsigned isSelected() {
   return this->selected;
  }
  void select() {
   this->selected = 1;
   if (this->onSelect != NULL) {
    this->onSelect();
   }
  }
  void cancelSelecting() {
   this->selected = 0;
  }
  void setOnSelectAction(void (*callback)() = NULL) {
   this->onSelect = callback;
  }
  MenuItem(const MenuItem &mi) {
   strcpy(this->name, "");
   strcpy(this->caption, "");
   strcat(this->name, mi.name);
   strcat(this->caption, mi.caption);
   this->enabled = mi.enabled;
   this->highlighted = mi.highlighted;
   this->selected = mi.selected;

   this->onSelect = mi.onSelect;
  }
  MenuItem& operator =(const MenuItem &mi) {
   strcpy(this->name, "");
   strcpy(this->caption, "");
   strcat(this->name, mi.name);
   strcat(this->caption, mi.caption);
   this->enabled = mi.enabled;
   this->highlighted = mi.highlighted;
   this->selected = mi.selected;

   this->onSelect = mi.onSelect;

   return *this;
  }
};

#endif