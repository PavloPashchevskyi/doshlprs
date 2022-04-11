#ifndef PLANEHIS_HPP
#define PLANEHIS_HPP

#include "./GRMODE.HPP"
#include "./GRAPHIC/PLOTABLE.HPP"

#include <string.h>

class PlaneHis : public Plotable {
 private:
  unsigned valuesQuantity;
  char values[][40];
  double *histogramValues;
  int tagsColor;
  const static unsigned margin;
  static unsigned histogramsQuantity;

  void write() {
   // horizontal value
   char strValue[40];
   strcpy(strValue, "");
   setcolor(tagsColor);
   for (unsigned i = 0; i < valuesQuantity; i++) {
    outtextxy(transformX(i), getmaxy() - PlaneHis::margin, values[i]);
   }
   // end horizontal value
   // percentage
   char strPercentage[8];
   for (i = 0; i < valuesQuantity; i++) {
    sprintf(strPercentage, "%4.2f\%", histogramValues[i]);
    outtextxy(transformX(i), transformY(histogramValues[i]) - PlaneHis::margin, strPercentage);
   }
   // end percentage
  }
 public:
  PlaneHis(
   unsigned uiValuesQuantity,
   char arrStrValues[][40],
   double (*h)(char *x),
   int iTagsColor = WHITE
  ) {
   GrMode::initGraphicalMode();
   valuesQuantity = uiValuesQuantity;
   histogramValues = new double[valuesQuantity];
   for (unsigned i = 0; i < valuesQuantity; i++) {
    strcpy(values[i], arrStrValues[i]);
    histogramValues[i] = h(values[i]);
   }
   tagsColor = iTagsColor;
   xTranslationAddition = PlaneHis::margin; //8;
   xStretchFactor =  (getmaxx() / valuesQuantity); //39.4375;
   yTranslationAddition = getmaxy() - PlaneHis::margin; //471;
   yStretchFactor = -(getmaxy() / 100); //-117.75;

   PlaneHis::histogramsQuantity++;
  }
  PlaneHis(
   unsigned uiValuesQuantity,
   double *arrValues,
   double (*h)(double x),
   int iTagsColor = WHITE
  ) {
   GrMode::initGraphicalMode();
   char *arrStrValues[40];
   valuesQuantity = uiValuesQuantity;
   histogramValues = new double[valuesQuantity];
   for (unsigned i = 0; i < valuesQuantity; i++) {
    sprintf(arrStrValues[i], "%3.2f", arrValues[i]);
    strcpy(values[i], arrStrValues[i]);
    histogramValues[i] = h(arrValues[i]);
   }
   tagsColor = iTagsColor;
   xTranslationAddition = PlaneHis::margin; //8;
   xStretchFactor =  (getmaxx() / valuesQuantity); //39.4375;
   yTranslationAddition = getmaxy() - PlaneHis::margin; //471;
   yStretchFactor = -(getmaxy() / 100); //-117.75;

   PlaneHis::histogramsQuantity++;
  }
  static unsigned getHistogramsQuantity() {
   return PlaneHis::histogramsQuantity;
  }
  void plot() {
   setlinestyle(lineStyle, 1, lineThickness);
   int margins = 2 * PlaneHis::margin;
   int horizontalAxeLength = getmaxx() - margins;
   int horizPixelsPerRect = horizontalAxeLength / valuesQuantity;
   unsigned hc = 1;
   int poly[8];
   for (unsigned i = 0; i < valuesQuantity; i++) {
    setcolor(hc);
    setfillstyle(LTSLASH_FILL, hc);

    poly[0] = transformX(i);
    poly[1] = transformY(0);
    poly[2] = poly[0];
    poly[3] = transformY(histogramValues[i]);
    poly[4] = poly[0] + horizPixelsPerRect;
    poly[5] = poly[3];
    poly[6] = poly[4];
    poly[7] = poly[1];

    fillpoly(4, poly);

    (hc > 0 && hc < 15) ? hc++ : 1;

    write();

    }
  }
  ~PlaneHis() {
   delete [] histogramValues;
   for (unsigned i = 0; i < valuesQuantity; i++) {
    delete values[i];
   }
   delete [] values;
   PlaneHis::histogramsQuantity--;
   closegraph();
  }
};

unsigned PlaneHis::histogramsQuantity = 0;
const unsigned PlaneHis::margin = 7;

#endif