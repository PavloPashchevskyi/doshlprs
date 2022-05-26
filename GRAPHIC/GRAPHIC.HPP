#ifndef GRAPHIC_HPP
#define GRAPHIC_HPP

#include "./GRAPHIC/PLOTABLE.HPP"
#include "./GRMODE.HPP"

#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <graphics.h>

class Graphic : public Plotable {
 private:
  double *X;
  double *Y;
  double *breakPoints;
  unsigned valuesQuantity, breakPointsQuantity;
  double xTranslationAddition, xStretchFactor;
  double yTranslationAddition, yStretchFactor;
  static const double accuracy;
  static unsigned graphicsQuantity;

  void sort() {
   for (unsigned i = 0; i < valuesQuantity; i++) {
    for (unsigned j = i + 1; j < valuesQuantity; j++) {
     if (X[i] > X[j]) {
      double temp = X[i];
      X[i] = X[j];
      X[j] = temp;
      temp = Y[i];
      Y[i] = Y[j];
      Y[j] = temp;
     }
    }
   }
  }

  double getMinX() {
   sort();
   return X[0];
  }

  double getMaxX() {
   sort();
   return X[valuesQuantity - 1];
  }

  double getMinY() {
   double min = 3.4e+38;
   for (unsigned i = 0; i < valuesQuantity; i++) {
    if (Y[i] < min) {
     min = Y[i];
    }
   }
   return min;
  }

  double getMaxY() {
   double max = 3.4e-38;
   for (unsigned i = 0; i < valuesQuantity; i++) {
    if (Y[i] > max) {
     max = Y[i];
    }
   }
   return max;
  }

  double getMinXStep() {
   sort();
   double minStep = 3.4e+38;
   for (unsigned i = 0, j = i + 1; i < valuesQuantity; i++, j++) {
    double diff = X[j] - X[i];
    if (diff < minStep) {
     minStep = diff;
    }
   }
   return minStep;
  }

  void setBreakPoints(double *bps = NULL, unsigned bpq = 0) {
   breakPointsQuantity = bpq;
   if (breakPointsQuantity > 0) {
    breakPoints = new double[breakPointsQuantity];
    for (unsigned i = 0; i < breakPointsQuantity; i++) {
     breakPoints[i] = bps[i];
    }
   } else {
    if (breakPoints != NULL) {
     delete [] breakPoints;
    }
   }
  }

  void buildLine(int x1, int y1, int x2, int y2, int &k, int &b) {
   k = (y2 - y1) / (x2 - x1);
   b = y1 - ((x1 * (y2 - y1)) / (x2 - x1));
  }

  unsigned doesPointBelongToLine(
   double pointX,
   double pointY,
   double lineXBegin,
   double lineYBegin,
   double lineXEnd,
   double lineYEnd
  ) {
   double k = (lineYEnd - lineYBegin) / (lineXEnd - lineXBegin);
   double b = lineYBegin - ((lineXBegin * (lineYEnd - lineYBegin)) / (lineXEnd - lineXBegin));

    return fabs(pointY - (k * pointX + b)) < Graphic::accuracy;
  }

  unsigned* previousLine(int x1, int y1, int x2, int y2) {
   int lineLength = (int) sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
   unsigned *prevPixels = new unsigned[lineLength];
   int k, b;
   int i = 0, x = x1, y = y1;
   while (x <= x2) {
    this->buildLine(x, y, x + 1, y +1, k, b);
    prevPixels[i] = getpixel(x, k * x + b);
    x++;
    y++;
    i++;
   }
   return prevPixels;
  }

  void drawLinePixelByPixel(int x1, int y1, int x2, int y2, unsigned *colors)
  {
   int i = 0, x = x1, y = y1, k, b;
   while (x <= x2) {
    this->buildLine(x, y, x + 1, y + 1, k, b);
    putpixel(x, k * x + b, colors[i]);
    x++;
    y++;
    i++;
   }
  }

 public:
  Graphic() {
   GrMode::initGraphicalMode();
   valuesQuantity = 1;
   breakPointsQuantity = 0;
   X = new double[valuesQuantity];
   Y = new double[valuesQuantity];
   xTranslationAddition = 319.;
   xStretchFactor = 78.875;
   yTranslationAddition = 239.;
   yStretchFactor = 235.5;
   this->color = YELLOW;
   this->lineStyle = SOLID_LINE;
   this->lineThickness = 1;
   breakPoints = NULL;
   Graphic::graphicsQuantity++;
  }
  Graphic(
   double xFrom,
   double xTo,
   double xStep,
   double *Y,
   double *bps = NULL,
   unsigned bpq = 0,
   int color = YELLOW,
   int lineStyle = SOLID_LINE,
   int lineThickness = 1
  ) {
   GrMode::initGraphicalMode();
   setBreakPoints(bps, bpq);
   valuesQuantity = (unsigned) ((fabs(xTo - xFrom) / xStep) - bpq + 1);
   this->X = new double[valuesQuantity];
   this->Y = new double[valuesQuantity];
   unsigned i = 0;
   for (double h = xFrom; h <= xTo; h += xStep) {
    if (breakPointsQuantity > 0) {
     unsigned b = 0;
     for (unsigned j = 0; j < breakPointsQuantity; j++) {
      if (fabs(h - breakPoints[j]) < Graphic::accuracy) {
       b = 1;
       break;
      }
     }
     if (b == 1) {
      continue;
     }
    }
    X[i] = h;
    this->Y[i] = Y[i];
    i++;
   }
   xTranslationAddition = 319.;
   xStretchFactor = 78.875;
   yTranslationAddition = 239.;
   yStretchFactor = 235.5;
   this->color = color;
   this->lineStyle = lineStyle;
   this->lineThickness = lineThickness;
   Graphic::graphicsQuantity++;
  }
  Graphic(
   double *X,
   double *Y,
   unsigned valuesQty,
   double *bps = NULL,
   unsigned bpq = 0,
   int color = YELLOW,
   int lineStyle = SOLID_LINE,
   int lineThickness = 1
  ) {
   GrMode::initGraphicalMode();
   valuesQuantity = valuesQty;
   this->X = new double[valuesQuantity];
   this->Y = new double[valuesQuantity];
   for (unsigned i = 0; i < valuesQuantity; i++) {
    this->X[i] = X[i];
    this->Y[i] = Y[i];
   }
   sort();
   xTranslationAddition = 319.;
   xStretchFactor = 78.875;
   yTranslationAddition = 239.;
   yStretchFactor = 235.5;
   this->color = color;
   this->lineStyle = lineStyle;
   this->lineThickness = lineThickness;
   setBreakPoints(bps, bpq);
   Graphic::graphicsQuantity++;
  }
  Graphic(
   double *X,
   double (*f)(double x),
   unsigned valuesQty,
   double *bps = NULL,
   unsigned bpq = 0,
   int color = YELLOW,
   int lineStyle = SOLID_LINE,
   int lineThickness = 1
  ) {
   GrMode::initGraphicalMode();
   valuesQuantity = valuesQty;
   this->X = new double[valuesQuantity];
   Y = new double[valuesQuantity];
   for (unsigned i = 0; i < valuesQuantity; i++) {
    this->X[i] = X[i];
    this->Y[i] = f(X[i]);
   }
   sort();
   xTranslationAddition = 319.;
   xStretchFactor = 78.875;
   yTranslationAddition = 239.;
   yStretchFactor = 235.5;
   this->color = color;
   this->lineStyle = lineStyle;
   this->lineThickness = lineThickness;
   setBreakPoints(bps, bpq);
   Graphic::graphicsQuantity++;
  }
  unsigned getValuesQuantity() {
   return valuesQuantity;
  }
  void setValuesQuantity(unsigned valuesQty) {
   valuesQuantity = valuesQty;
  }
  void setFunction(double *X, double *Y, double *bps, unsigned bpq) {
   for (unsigned i = 0; i < valuesQuantity; i++) {
    this->X[i] = X[i];
    this->Y[i] = Y[i];
   }
   sort();
   setBreakPoints(bps, bpq);
  }
  void setFunction(
   double *X,
   double (*f)(double x),
   double *bps = NULL,
   unsigned bpq = 0
  ) {
   for (unsigned i = 0; i < valuesQuantity; i++) {
    this->X[i] = X[i];
    this->Y[i] = f(X[i]);
   }
   sort();
   setBreakPoints(bps, bpq);
  }
  static unsigned getGraphicsQuantity() {
   return Graphic::graphicsQuantity;
  }
  static unsigned setGraphicsQuantity(unsigned graphicsQty) {
   Graphic::graphicsQuantity = graphicsQty;
  }
  double* getX() {
   return X;
  }
  double* getY() {
   return Y;
  }
  unsigned getBreakPointsQuantity() {
   return breakPointsQuantity;
  }
  double* getBreakPoints() {
   return breakPoints;
  }
  void shiftXRight(double step, double *newYs) {
   for (unsigned i = 0; i < valuesQuantity; i++) {
    X[i] = X[i] + step;
    Y[i] = newYs[i];
   }
  }
  void shiftXLeft(double step, double *newYs) {
   for (int i = valuesQuantity - 1; i >= 0; i--) {
    X[i] = X[i] - step;
    Y[i] = newYs[i];
   }
  }
  void plot() {
   setcolor(color);
   setlinestyle(lineStyle, 1, lineThickness);

   for (unsigned i = 0; i < valuesQuantity - 1; i++) {
    double currPointX = X[i], currPointY = Y[i];
    double nextPointX = X[i + 1], nextPointY = Y[i + 1];
    int trCurrPointX = transformX(currPointX);
    int trCurrPointY = transformY(currPointY);
    int trNextPointX = transformX(nextPointX);
    int trNextPointY = transformY(nextPointY);
    if (breakPointsQuantity > 0) {
     for (unsigned j = 0; j < breakPointsQuantity; j++) {
      if (!doesPointBelongToLine(breakPoints[j], 0.00, currPointX, currPointY, nextPointX, nextPointY)) {
       line(trCurrPointX, trCurrPointY, trNextPointX, trNextPointY);
      }
     }
    } else {
     line(trCurrPointX, trCurrPointY, trNextPointX, trNextPointY);
    }
   }
  }
  void moveLeft(double step, double *newYs) {
   for (int i = valuesQuantity - 1; i >= 0; i--) {
    X[i] = X[i] - step;
    Y[i] = newYs[i];
   }
  }
  void moveRight(double step, double *newYs) {
   for (unsigned i = 0; i < valuesQuantity; i++) {
    X[i] = X[i] + step;
    Y[i] = newYs[i];
   }
  }
  void moveUp(double step, double *newXs) {
   for (unsigned i = 0; i < valuesQuantity; i++) {
    X[i] = newXs[i];
    Y[i] = Y[i] + step;
   }
  }
  void moveDown(double step, double *newXs) {
   for (unsigned i = 0; i < valuesQuantity; i++) {
    X[i] = newXs[i];
    Y[i] = Y[i] + step;
   }
  }
  ~Graphic() {
   delete [] X;
   delete [] Y;
   if (breakPointsQuantity > 0) {
    delete [] breakPoints;
    breakPointsQuantity = 0;
   }
   Graphic::graphicsQuantity--;
  }
};

const double Graphic::accuracy = 0.01;
unsigned Graphic::graphicsQuantity = 0;

#endif
