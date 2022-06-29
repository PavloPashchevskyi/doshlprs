#ifndef GMANAGER_HPP
#define GMANAGER_HPP

#include "./GRAPHIC/PLANE2D.HPP"

class GManager {
 private:
  Plane2D *plane2D;
 public:
  GManager(Plane2D *p2D) {
   plane2D = p2D;
  }
  void moveLeft() {
   plane2D->setXFrom(plane2D->getXFrom() - plane2D->getXStep());
   plane2D->setXTo(plane2D->getXTo() - plane2D->getXStep());
   for (unsigned i = 0; i < plane2D->getGraphicsQuantity(); i++) {
    plane2D->getGraphic(i).moveLeft();
   }
   plane2D->setYFromToMin();
   plane2D->setYToToMax();
  }
  void moveRight() {
   plane2D->setXFrom(plane2D->getXFrom() + plane2D->getXStep());
   plane2D->setXTo(plane2D->getXTo() + plane2D->getXStep());
   for (unsigned i = 0; i < plane2D->getGraphicsQuantity(); i++) {
    plane2D->getGraphic(i).moveRight();
   }
   plane2D->setYFromToMin();
   plane2D->setYToToMax();
  }
  void moveUp() {
   plane2D->setXFrom(plane2D->getXFrom() + plane2D->getXStep());
   plane2D->setXTo(plane2D->getXTo() + plane2D->getXStep());
   for (unsigned i = 0; i < plane2D->getGraphicsQuantity(); i++) {
    plane2D->getGraphic(i).moveUp();
   }
   plane2D->setYFromToMin();
   plane2D->setYToToMax();
  }
  void moveDown() {
   plane2D->setXFrom(plane2D->getXFrom() - plane2D->getXStep());
   plane2D->setXTo(plane2D->getXTo() - plane2D->getXStep());
   for (unsigned i = 0; i < plane2D->getGraphicsQuantity(); i++) {
    plane2D->getGraphic(i).moveDown();
   }
   plane2D->setYFromToMin();
   plane2D->setYToToMax();
  }
  void increaseScale() {
   double factor = plane2D->getScaleFactor();
   double newXTo = plane2D->getXTo() / factor;
   double newXStep = (fabs(newXTo - plane2D->getXFrom()) * plane2D->getXStep()) / fabs(plane2D->getXTo() - plane2D->getXFrom());
   plane2D->setXTo(newXTo);
   plane2D->setXStep(newXStep);
   for (unsigned i = 0; i < plane2D->getGraphicsQuantity(); i++) {
    plane2D->getGraphic(i).increaseScale();
   }
   plane2D->setYFromToMin();
   plane2D->setYToToMax();
  }
  void decreaseScale() {
   double factor = plane2D->getScaleFactor();
   double newXTo = plane2D->getXTo() * factor;
   double newXStep = (fabs(newXTo - plane2D->getXFrom()) * plane2D->getXStep()) / fabs(plane2D->getXTo() - plane2D->getXFrom());
   plane2D->setXTo(newXTo);
   plane2D->setXStep(newXStep);
   for (unsigned i = 0; i < plane2D->getGraphicsQuantity(); i++) {
    plane2D->getGraphic(i).decreaseScale();
   }
   plane2D->setYFromToMin();
   plane2D->setYToToMax();
  }
  unsigned deleteGraphic(unsigned n) {
   return plane2D->deleteGraphic(n);
  }
  void deleteAllGraphics() {
   unsigned oldGraphicsQuantity = plane2D->getGraphicsQuantity();
   for (int i = oldGraphicsQuantity - 1; i >= 0; i--) {
    plane2D->deleteGraphic(i);
   }
  }
  void redraw() {
   plane2D->redraw();
  }
  ~GManager() {
   delete plane2D;
  }
};

#endif