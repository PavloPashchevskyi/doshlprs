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
  double xFrom, xTo, xStep, yFrom, yTo, yStep;
  double *X;
  double (*F)(double);
  double *Y;
  double *breakPoints;
  unsigned valuesQuantity, breakPointsQuantity;
  double xTranslationAddition, xStretchFactor;
  double yTranslationAddition, yStretchFactor;
  double scaleFactor;
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

  unsigned isSorted() {
   for (unsigned i = 0; i < valuesQuantity; i++) {
    for (unsigned j = i + 1; j < valuesQuantity; j++) {
     if (X[i] > X[j]) {
      return 0;
     }
    }
   }
   return 1;
  }

  double getMinX() {
   double minX = 3.4e+308;
   for (unsigned i = 0; i < valuesQuantity; i++) {
    if (X[i] < minX) {
     minX = X[i];
    }
   }
   return minX;
  }

  double getMaxX() {
   double maxX = 3.4e-308;
   for (unsigned i = 0; i < valuesQuantity; i++) {
    if (X[i] > maxX) {
     maxX = X[i];
    }
   }
   return maxX;
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
   double minStep = 3.4e+38;
   for (unsigned i = 0; i < valuesQuantity; i++) {
    for (unsigned j = i + 1; j < valuesQuantity; j++) {
     double diff = fabs(X[j] - X[i]);
     if (diff < minStep) {
      minStep = diff;
     }
    }
   }
   return minStep;
  }

  double getMinYStep() {
   double minStep = 3.4e+38;
   for (unsigned i = 0; i < valuesQuantity; i++) {
    for (unsigned j = i + 1; j < valuesQuantity; j++) {
     double diff = fabs(Y[j] - Y[i]);
     if (diff < minStep) {
      minStep = diff;
     }
    }
   }
   return minStep;
  }

  double getMaxScaleFactor() {
   return 2;
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
   scaleFactor = this->getMaxScaleFactor();
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
   this->xFrom = xFrom;
   this->xTo = xTo;
   this->xStep = xStep;
   yFrom = this->getMinY();
   yTo = this->getMaxY();
   yStep = this->getMinYStep();
   xTranslationAddition = 319.;
   xStretchFactor = 78.875;
   yTranslationAddition = 239.;
   yStretchFactor = 235.5;
   this->color = color;
   this->lineStyle = lineStyle;
   this->lineThickness = lineThickness;
   scaleFactor = this->getMaxScaleFactor();
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
   if (!isSorted()) {
    sort();
   }

   xFrom = this->getMinX();
   xTo = this->getMaxX();
   xStep = this->getMinXStep();
   yFrom = this->getMinY();
   yTo = this->getMaxY();
   yStep = this->getMinYStep();

   xTranslationAddition = 319.;
   xStretchFactor = 78.875;
   yTranslationAddition = 239.;
   yStretchFactor = 235.5;
   this->color = color;
   this->lineStyle = lineStyle;
   this->lineThickness = lineThickness;
   setBreakPoints(bps, bpq);
   scaleFactor = this->getMaxScaleFactor();
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
   if (!isSorted()) {
    sort();
   }

   xFrom = this->getMinX();
   xTo = this->getMaxX();
   xStep = this->getMinXStep();
   yFrom = this->getMinY();
   yTo = this->getMaxY();
   yStep = this->getMinYStep();

   F = f;

   xTranslationAddition = 319.;
   xStretchFactor = 78.875;
   yTranslationAddition = 239.;
   yStretchFactor = 235.5;
   this->color = color;
   this->lineStyle = lineStyle;
   this->lineThickness = lineThickness;
   setBreakPoints(bps, bpq);
   scaleFactor = this->getMaxScaleFactor();
   Graphic::graphicsQuantity++;
  }
  Graphic(const Graphic &right) {
   setBreakPoints(right.breakPoints, right.breakPointsQuantity);
   this->F = right.F;
   this->valuesQuantity = right.valuesQuantity;
   this->X = new double[valuesQuantity];
   this->Y = new double[valuesQuantity];
   for (unsigned i = 0; i < valuesQuantity; i++) {
    this->X[i] = right.X[i];
    this->Y[i] = right.Y[i];
   }
   this->xFrom = right.xFrom;
   this->xTo = right.xTo;
   this->xStep = right.xStep;
   this->yFrom = right.yFrom;
   this->yTo = right.yTo;
   this->yStep = right.yStep;
   this->xTranslationAddition = right.xTranslationAddition;
   this->xStretchFactor = right.xStretchFactor;
   this->yTranslationAddition = right.yTranslationAddition;
   this->yStretchFactor = right.yStretchFactor;
   this->color = right.color;
   this->lineStyle = right.lineStyle;
   this->lineThickness = right.lineThickness;
   this->scaleFactor = right.scaleFactor;
   Graphic::graphicsQuantity++;
  }
  Graphic& operator =(const Graphic &right) {
   if (X != NULL || Y != NULL) {
    Graphic::graphicsQuantity--;
   }
   if(X != NULL) {
    delete [] this->X;
   }
   if (Y != NULL) {
    delete [] this->Y;
   }
   if (breakPoints != NULL) {
    delete [] breakPoints;
   }
   setBreakPoints(right.breakPoints, right.breakPointsQuantity);
   this->F = right.F;
   this->valuesQuantity = right.valuesQuantity;
   this->X = new double[valuesQuantity];
   this->Y = new double[valuesQuantity];
   for (unsigned i = 0; i < valuesQuantity; i++) {
    this->X[i] = right.X[i];
    this->Y[i] = right.Y[i];
   }
   this->xFrom = right.xFrom;
   this->xTo = right.xTo;
   this->xStep = right.xStep;
   this->yFrom = right.yFrom;
   this->yTo = right.yTo;
   this->yStep = right.yStep;
   this->xTranslationAddition = right.xTranslationAddition;
   this->xStretchFactor = right.xStretchFactor;
   this->yTranslationAddition = right.yTranslationAddition;
   this->yStretchFactor = right.yStretchFactor;
   this->color = right.color;
   this->lineStyle = right.lineStyle;
   this->lineThickness = right.lineThickness;
   this->scaleFactor = right.scaleFactor;
   Graphic::graphicsQuantity++;

   return *this;
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
   if (!isSorted()) {
    sort();
   }
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
   if (!isSorted()) {
    sort();
   }

   xFrom = this->getMinX();
   xTo = this->getMaxX();
   xStep = this->getMinXStep();
   yFrom = this->getMinY();
   yTo = this->getMaxY();
   yStep = this->getMinYStep();


   setBreakPoints(bps, bpq);
  }
  void setFunction(
   double xFrom,
   double xTo,
   double xStep,
   double (*f)(double x),
   double *bps = NULL,
   unsigned bpq = 0
  ) {
   double *x, *y;
   setBreakPoints(bps, bpq);
   this->xFrom = xFrom;
   this->xTo = xTo;
   this->xStep = xStep;
   F = f;
   valuesQuantity = (unsigned) ((fabs(xTo - xFrom) / xStep) - bpq + 1);
   x = new double[valuesQuantity];
   y = new double[valuesQuantity];
   unsigned i = 0;
   for (double h = xFrom; h <= xTo; h += xStep) {
    if (bpq > 0) {
     unsigned b = 0;
     for (unsigned j = 0; j < bpq; j++) {
      if (fabs(h - bps[j]) < Graphic::accuracy) {
       b = 1;
       break;
      }
     }
     if (b == 1) {
      continue;
     }
    }
    x[i] = h;
    y[i] = F(x[i]);
    i++;
   }
   delete [] X;
   delete [] Y;
   X = x;
   Y = y;
   if (!isSorted()) {
    sort();
   }

   yFrom = this->getMinY();
   yTo = this->getMaxY();
   yStep = this->getMinYStep();
  }
  static unsigned getGraphicsQuantity() {
   return Graphic::graphicsQuantity;
  }
  static unsigned setGraphicsQuantity(unsigned graphicsQty) {
   Graphic::graphicsQuantity = graphicsQty;
  }
  double getScaleFactor() {
   return scaleFactor;
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
  void moveLeft() {
   double *x, *y;
   x = new double [valuesQuantity];
   y = new double [valuesQuantity];
   for (unsigned i = 0; i < valuesQuantity; i++) {
    x[i] = (i > 0) ? X[i - 1] : X[i] - xStep;
    y[i] = F(x[i]);
   }
   delete [] X;
   delete [] Y;
   X = x;
   Y = y;
   xFrom -= xStep;
   xTo -= xStep;
   if (!isSorted()) {
    sort();
   }
  }
  void moveRight() {
   double *x, *y;
   x = new double [valuesQuantity];
   y = new double [valuesQuantity];
   for (unsigned i = 0; i < valuesQuantity; i++) {
    x[i] = (i < valuesQuantity - 1) ? X[i + 1] : X[i] + xStep;
    y[i] = F(x[i]);
   }
   delete [] X;
   delete [] Y;
   X = x;
   Y = y;
   xFrom += xStep;
   xTo += xStep;
   if (!isSorted()) {
    sort();
   }
  }
  void moveUp() {
   double *x, *y;
   x = new double [valuesQuantity];
   y = new double [valuesQuantity];
   for (unsigned i = 0; i < valuesQuantity; i++) {
    x[i] = (i < valuesQuantity - 1) ? X[i + 1] : X[i] + xStep;
    y[i] = F(x[i]);
   }
   delete [] X;
   delete [] Y;
   X = x;
   Y = y;
   xFrom += xStep;
   xTo += xStep;
   if (!isSorted()) {
    sort();
   }
  }
  void moveDown() {
   double *x, *y;
   x = new double [valuesQuantity];
   y = new double [valuesQuantity];
   for (unsigned i = 0; i < valuesQuantity; i++) {
    x[i] = (i > 0) ? X[i - 1] : X[i] - xStep;
    y[i] = F(X[i]);
   }
   delete [] X;
   delete [] Y;
   X = x;
   Y = y;
   xFrom -= xStep;
   xTo -= xStep;
   if (!isSorted()) {
    sort();
   }
  }
  void increaseScale() {
   double factor = this->getMaxScaleFactor();
   scaleFactor = factor;
   double newXTo = (fabs(factor) < 1) ? xTo * factor : xTo / factor;
   double newXStep = (fabs(newXTo - xFrom) * xStep) / fabs(xTo - xFrom);
   xTo = newXTo;
   xStep = newXStep;
   setFunction(xFrom, xTo, xStep, F, breakPoints, breakPointsQuantity);
  }
  void decreaseScale() {
   double factor = this->getMaxScaleFactor();
   scaleFactor = factor;
   double newXTo = (fabs(factor) < 1) ? xTo / factor : xTo * factor;
   double newXStep = (fabs(newXTo - xFrom) * xStep) / fabs(xTo - xFrom);
   xTo = newXTo;
   xStep = newXStep;
   setFunction(xFrom, xTo, xStep, F, breakPoints, breakPointsQuantity);
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
