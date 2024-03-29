#ifndef PLANE2D_HPP
#define PLANE2D_HPP

#include <stdio.h>
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <graphics.h>

#include "./GRAPHIC/GRAPHIC.HPP"

class Plane2D {
 private:
  double horizFrom, horizTo, horizStep, verticalFrom, verticalTo;
  int xTailPresent, yTailPresent;
  double samplingFreqFactor, quantStepFactor;
  char horizontalAxeName[2], verticalAxeName[7];
  static const int axeTagsMargin;
  static const double accuracy;
  Graphic **graphics;
  unsigned graphicsQuantity;

  void drawAxes(int color) {
   int xhb, yhb, xhe, yhe, xvb, yvb, xve, yve;
   if (horizFrom < 0 && horizTo > 0) { // if negative horizontal axe is needed
    xvb = getmaxx() / 2; yvb = 0; xve = getmaxx() / 2; yve = getmaxy();
    xNegativeAxeEnd = getmaxx() / 2;
   }
   if (horizFrom >= 0) { // if negative horizontal axe is NOT needed
    xvb = Plane2D::axesMargin; yvb = 0; xve = Plane2D::axesMargin; yve = getmaxy();
    xTailPresent = 1;
    xNegativeAxeEnd = Plane2D::axesMargin;
   }
   if (horizTo <= 0) { // if POSITIVE horizontal axe is NOT needed
    xvb = getmaxx() - Plane2D::axesMargin;
    yvb = 0;
    xve = getmaxx() - Plane2D::axesMargin;
    yve = getmaxy();
    xTailPresent = 1;
    xNegativeAxeEnd = getmaxx() - Plane2D::axesMargin;
   }
   if (verticalFrom < 0 && verticalTo > 0) { // if we need negative vertical
    xhb = 0; yhb = getmaxy() / 2; xhe = getmaxx(); yhe = getmaxy() / 2;
    yNegativeAxeEnd = getmaxy() / 2;
   }
   if (verticalFrom >= 0) { // if we DO NOT need negative vertical axe
    xhb = 0;
    yhb = getmaxy() - Plane2D::axesMargin;
    xhe = getmaxx();
    yhe = getmaxy() - Plane2D::axesMargin;
    yTailPresent = 1;
    yNegativeAxeEnd = getmaxy() - Plane2D::axesMargin;
   }
   if (verticalTo <= 0) { // if POSITIVE vertical axe is NOT needed
    xhb = 0; yhb = Plane2D::axesMargin; xhe = getmaxx(); yhe = Plane2D::axesMargin;
    yTailPresent = 1;
    yNegativeAxeEnd = Plane2D::axesMargin;
   }
   if (color == getbkcolor()) {
    printf("Axes color must NOT be the same as background one\n");
    getch();
    exit(1);
   }
   setcolor(color);
   line(xhb, yhb, xhe, yhe);
   line(xvb, yvb, xve, yve);
  }
  void writeAxes(
   int tagsAndGridColor,
   double samplingFreq,
   double quantStep,
   char horizontalAxeName[2] = "X",
   char verticalAxeName[7] = "Y"
  ) {
   char strStep[7];
   int axesTagsQuantity = (int) ((horizTo - horizFrom) / horizStep), i;
   double h, verticalStep = (verticalTo - verticalFrom) / axesTagsQuantity;
   if (tagsAndGridColor==getbkcolor() || tagsAndGridColor==this->axesColor) {
    printf("Tags and/or grid color must NOT be the same as background color or the axes one\n");
    getch();
    exit(1);
   }
   setcolor(tagsAndGridColor);
   outtextxy(
    getmaxx() - Plane2D::axeTagsMargin,
    toYScreenCoordinate(0),
    horizontalAxeName
   );
   outtextxy(toXScreenCoordinate(0), 0, verticalAxeName);
   strcpy(strStep, "");
   for (h = horizFrom; h <= horizTo; h += 2 * horizStep) {
    sprintf(strStep, "%3.2f", h);
    outtextxy(
     toXScreenCoordinate(h) - Plane2D::axeTagsMargin,
     toYScreenCoordinate(0),
     (fabs(h) < Plane2D::accuracy) ? "0" : strStep
    );
   }
   for (h = verticalFrom; h <= verticalTo; h += 2 * verticalStep) {
    sprintf(strStep, "%3.2f", h);
    outtextxy(
     toXScreenCoordinate(0),
     toYScreenCoordinate(h) - Plane2D::axeTagsMargin,
     (fabs(h) < Plane2D::accuracy) ? "" : strStep
    );
   }
   if (fabs(samplingFreq)>=Plane2D::accuracy || fabs(quantStep)>=Plane2D::accuracy) {
    setlinestyle(DASHED_LINE, 1, 1);
    if (fabs(samplingFreq) >= Plane2D::accuracy) {
     for (h = horizFrom; h <= horizTo; h += (2 / samplingFreq) * horizStep) {
      if (fabs(h) >= Plane2D::accuracy) {
       line(toXScreenCoordinate(h), 0, toXScreenCoordinate(h), getmaxy());
      }
     }
    }
    if (fabs(quantStep) >= Plane2D::accuracy) {
     for (h = verticalFrom; h <= verticalTo; h+=(2/quantStep)*verticalStep) {
      if (fabs(h) >= Plane2D::accuracy) {
       line(0, toYScreenCoordinate(h), getmaxx(), toYScreenCoordinate(h));
      }
     }
    }
   }
  }

 protected:
  int axesColor, tagsAndGridColor, xNegativeAxeEnd, yNegativeAxeEnd;
  static const int axesMargin;
  double scaleFactor;

  double calculateXScale() {
   return (getmaxx() - ((xTailPresent) ? Plane2D::axesMargin : 0)) /
    (horizTo - horizFrom);
  }
  int toXScreenCoordinate(double x) {
   double xScale = calculateXScale();
    return (int) (xNegativeAxeEnd + x * xScale);
  }
  double calculateYScale() {
   return (getmaxy() - ((yTailPresent) ? Plane2D::axesMargin : 0)) /
    (verticalTo - verticalFrom);
  }
  int toYScreenCoordinate(double y) {
   double yScale = calculateYScale();
    //yScale = yScale * scaleFactor;
    return (int) (yNegativeAxeEnd - y * yScale);
  }
 public:
  Plane2D(
   double xFrom = -M_PI,
   double xTo = M_PI,
   double xStep = M_PI / 12,
   double yFrom = -1,
   double yTo = 1,
   int axesColor = GREEN,
   int tagsAndGridColor = WHITE,
   double samplingFreqFactor = 0,
   double quantStepFactor = 0,
   char horizontalAxeName[2] = "X",
   char verticalAxeName[7] = "Y"
  ) {
   GrMode::initGraphicalMode();
   horizFrom = xFrom;
   if (xFrom >= xTo) {
    printf("Right bound of horizontal axe must be greater than the left one");
    getch();
    exit(1);             /* return with error code */
   }
   horizTo = xTo;
   if (xStep <= 0) {
    printf("Step must be greater than 0");
    getch();
    exit(1);             /* return with error code */
   }
   horizStep = xStep;
   verticalFrom = yFrom;
   if (yFrom >= yTo) {
    printf("Right bound of vertical axe must be greater than the left one");
    getch();
    exit(1);             /* return with error code */
   }
   verticalTo = yTo;
   this->axesColor = axesColor;
   this->tagsAndGridColor = tagsAndGridColor;
   this->samplingFreqFactor = samplingFreqFactor;
   this->quantStepFactor = quantStepFactor;
   strcpy(this->horizontalAxeName, horizontalAxeName);
   strcpy(this->verticalAxeName, verticalAxeName);
   drawAxes(this->axesColor);
   writeAxes(
    tagsAndGridColor,
    samplingFreqFactor,
    quantStepFactor,
    horizontalAxeName,
    verticalAxeName
   );
   scaleFactor = 1.000000;
  }
  Plane2D(Plane2D &right) {
   horizFrom = right.horizFrom;
   horizTo = right.horizTo;
   horizStep = right.horizStep;
   verticalFrom = right.verticalFrom;
   verticalTo = right.verticalTo;
   axesColor = right.axesColor;
   tagsAndGridColor = right.tagsAndGridColor;
   xNegativeAxeEnd = right.xNegativeAxeEnd;
   yNegativeAxeEnd = right.yNegativeAxeEnd;
   xTailPresent = right.xTailPresent;
   yTailPresent = right.yTailPresent;
   scaleFactor = right.scaleFactor;
   samplingFreqFactor = right.samplingFreqFactor;
   quantStepFactor = right.quantStepFactor;
   strcpy(horizontalAxeName, right.horizontalAxeName);
   strcpy(verticalAxeName, this->verticalAxeName);
  }
  Plane2D& operator=(Plane2D &right) {
   horizFrom = right.horizFrom;
   horizTo = right.horizTo;
   horizStep = right.horizStep;
   verticalFrom = right.verticalFrom;
   verticalTo = right.verticalTo;
   axesColor = right.axesColor;
   tagsAndGridColor = right.tagsAndGridColor;
   xNegativeAxeEnd = right.xNegativeAxeEnd;
   yNegativeAxeEnd = right.yNegativeAxeEnd;
   xTailPresent = right.xTailPresent;
   yTailPresent = right.yTailPresent;
   scaleFactor = right.scaleFactor;
   samplingFreqFactor = right.samplingFreqFactor;
   quantStepFactor = right.quantStepFactor;
   strcpy(horizontalAxeName, right.horizontalAxeName);
   strcpy(verticalAxeName, this->verticalAxeName);

   return *this;
  }
  void addGraphic(
   double (*f)(double),
   double *breakPoints = NULL,
   unsigned bpq = 0,
   unsigned color = YELLOW
  ) {
   double xScale = calculateXScale(), yScale = calculateYScale();
   unsigned grPointsQ = (unsigned) ((horizTo - horizFrom) / horizStep) + 1.;
   double *X = new double[grPointsQ];
   for (unsigned i = 0; i < grPointsQ; i++) {
    X[i] = horizFrom + i * horizStep;
   }
   graphicsQuantity = Graphic::getGraphicsQuantity() + 1;
   graphics = new Graphic*[graphicsQuantity];
   for (i = 0; i < graphicsQuantity; i++) {
    graphics[i] = new Graphic(X, f, grPointsQ, breakPoints, bpq, color);

    graphics[i]->setXTranslationAddition(xNegativeAxeEnd);
    graphics[i]->setXStretchFactor(xScale);
    graphics[i]->setYTranslationAddition(yNegativeAxeEnd);
    graphics[i]->setYStretchFactor(-yScale);

    graphics[i]->plot();
   }
  }
  void addGraphic(
   double *Y,
   double *breakPoints = NULL,
   unsigned bpq = 0,
   unsigned color = YELLOW
  ) {
   double xScale = calculateXScale(), yScale = calculateYScale();
   graphicsQuantity = Graphic::getGraphicsQuantity() + 1;
   graphics = new Graphic*[graphicsQuantity];
   for (unsigned i = 0; i < graphicsQuantity; i++) {
    graphics[i] = new Graphic(horizFrom, horizTo, horizStep, Y, breakPoints, bpq, color);

    graphics[i]->setXTranslationAddition(xNegativeAxeEnd);
    graphics[i]->setXStretchFactor(xScale);
    graphics[i]->setYTranslationAddition(yNegativeAxeEnd);
    graphics[i]->setYStretchFactor(-yScale);

    graphics[i]->plot();
   }
  }
  unsigned deleteGraphic(unsigned i) {
   if (i >= graphicsQuantity) {
    printf("Graphic #%d does not exist or has already been deleted\n", i);
    getch();
    return 0;
   }
   delete graphics[i];
   graphicsQuantity = Graphic::getGraphicsQuantity();
   return 1;
  }
  unsigned deleteAllGraphics() {
   for (unsigned i = 0; i < graphicsQuantity; i++) {
    delete graphics[i];
   }
   delete [] graphics;
   return (Graphic::getGraphicsQuantity() == 0);
  }
  void moveLeft() {
   horizFrom = horizFrom - horizStep;
   horizTo = horizTo - horizStep;
   double **newYs = new double*[graphicsQuantity];
   for (unsigned i = 0; i < graphicsQuantity; i++) {
    newYs[i] = new double[graphics[i]->getValuesQuantity()];
    graphics[i]->shiftXLeft(horizStep, newYs[i]);
   }
  }
  void moveRight() {
   horizFrom = horizFrom + horizStep;
   horizTo = horizTo + horizStep;
  }
  void moveDown() {
   verticalFrom = verticalFrom - horizStep;
   verticalTo = verticalTo - horizStep;
  }
  void moveUp() {
   verticalFrom = verticalFrom + horizStep;
   verticalTo = verticalTo + horizStep;
  }
  void increaseScale() {
   scaleFactor *= 0.125;
  }
  void decreaseScale() {
   scaleFactor *= 1.125;
  }
  void redraw() {
   cleardevice();
   writeAxes(
    tagsAndGridColor,
    samplingFreqFactor,
    quantStepFactor,
    horizontalAxeName,
    verticalAxeName
   );
   drawAxes(axesColor);
   for (unsigned i = 0; i < Graphic::getGraphicsQuantity(); i++) {
    graphics[i]->plot();
   }
  }
  ~Plane2D() {
   for (unsigned i = 0; i < graphicsQuantity; i++) {
    delete graphics[i];
   }
   delete [] graphics;
  }
};

const int Plane2D::axesMargin = 8;
const int Plane2D::axeTagsMargin = 7;
const double Plane2D::accuracy = 0.01;


#endif