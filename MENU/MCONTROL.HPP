#ifndef MCONTROL_HPP
#define MCONTROL_HPP

#include "./MENU/MENU.HPP"

class MControl {
 private:
  Menu *menu;
  void goDown(int &itemNo) {
   menu->increaseItemNumber(itemNo);
   if (!menu->getItem(itemNo).isEnabled()) {
    goDown(itemNo);
   }
  }
  void climb(int &itemNo) {
   menu->decreaseItemNumber(itemNo);
   if (!menu->getItem(itemNo).isEnabled()) {
    climb(itemNo);
   }
  }
 public:
  MControl(Menu *mMenu) {
   this->menu = mMenu;
   int i = 0;
   char c;
   do {
    c = getch();
    if (c == 27) { // esc
     break;
    }
    if (c == 80) { // down arrow
     menu->cancelHighlightingItem(i);
     this->goDown(i);
     menu->highlightItem(i);
    }
    if (c == 72) { // up arrow
     menu->cancelHighlightingItem(i);
     this->climb(i);
     menu->highlightItem(i);
    }
    if (c == 13) {
     menu->selectItem(i);
    }
    menu->redrawItems();
   } while (strcmp(menu->getSelectedItem().getName(), "exit") != 0);
  }
  ~MControl() {
   delete menu;
  }
};

#endif