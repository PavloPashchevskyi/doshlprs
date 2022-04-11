#ifndef PLOTABLE_HPP
#define PLOTABLE_HPP

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <graphics.h>

class Plotable {
 protected:
  double xTranslationAddition, xStretchFactor;
  double yTranslationAddition, yStretchFactor;
  int color, lineStyle, lineThickness;

  int transformValue(
   double value,
   double translationAddition = 0,
   double stretchFactor = 1
  ) {
   return (int) (translationAddition + value * stretchFactor);
  }

  int transformX(double x) {
   return transformValue(x, xTranslationAddition, xStretchFactor);
  }

  int transformY(double y) {
   return transformValue(y, yTranslationAddition, yStretchFactor);
  }

 public:
  Plotable() {
   xTranslationAddition = 319;
   xStretchFactor = 78.875;
   yTranslationAddition = 239;
   yStretchFactor = 235.5;
   color = YELLOW;
   lineStyle = SOLID_LINE;
   lineThickness = 1;
  }
  Plotable(
   double xTA,
   double xSF,
   double yTA,
   double ySF,
   int clr = YELLOW,
   int ls = SOLID_LINE,
   int lth = 1
  ) {
   xTranslationAddition = xTA;
   xStretchFactor = xSF;
   yTranslationAddition = yTA;
   yStretchFactor = ySF;
   color = clr;
   lineStyle = ls;
   lineThickness = lth;
  }
  void setXTranslationAddition(double xTA = 319) {
   xTranslationAddition = xTA;
  }
  void setXStretchFactor(double xSF = 78.875) {
   xStretchFactor = xSF;
  }
  void setYTranslationAddition(double yTA = 239) {
   yTranslationAddition = yTA;
  }
  void setYStretchFactor(double ySF = 235.5) {
   yStretchFactor = ySF;
  }
  int stretchFromX(double x, double f = 1.) {
   return (int) transformValue(x, xTranslationAddition, xStretchFactor) * f;
  }
  int stretchFromY(double y, double f = 1.) {
   return transformValue(y, yTranslationAddition, yStretchFactor) * f;
  }
  int getColor() {
   return color;
  }
  void setColor(int color) {
   if (color==getbkcolor()) {
    printf("Graphics color must NOT be the same as background color\n");
    getch();
    exit(1);
   }
   this->color = color;
  }
  void setLineStyle(int lineStyle = SOLID_LINE) {
   this->lineStyle = lineStyle;
  }
  void setLineThickness(int lineThickness = 1) {
   this->lineThickness = lineThickness;
  }
  virtual void plot() = 0;
};

#endif