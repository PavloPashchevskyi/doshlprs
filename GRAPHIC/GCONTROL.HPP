#ifndef GCONTROL_HPP
#define GCONTROL_HPP

#include "./GRAPHIC/GMANAGER.HPP"

class GControl {
 private:
  GManager *gManager;
 public:
  GControl(GManager *gm) {
   this->gManager = gm;
   char c;
   do {
    c = getch();
    switch (c) {
     case 72: { // arrow up
      gManager->moveUp();
     } break;
     case 80: { // arrow down
      gManager->moveDown();
     } break;
     case 75: { // arrow left
      gManager->moveLeft();
     } break;
     case 77: { // arrow right
      gManager->moveRight();
     } break;
     case 119: { // w
      gManager->increaseScale();
     } break;
     case 115: { // s
      gManager->decreaseScale();
     } break;
     case 99: { // c
      gManager->deleteAllGraphics();
     } break;
     default: {
      if (c >= 48 && c <= 57) {
       gManager->deleteGraphic(c - 48);
      }
     } break;
    }
    gManager->redraw();
   } while (c != 27);
  }
  ~GControl() {
   delete gManager;
  }
};

#endif