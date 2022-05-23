#ifndef FEREADER_HPP
#define FEREADER_HPP

#include <stdio.h>
#include <math.h>
#include <stdlib.h>

class FEReader {
 private:
  double xFrom, xTo, xStep, yFrom, yTo, *X, *Y;
  unsigned valuesQuantity;

  void calculateXFrom() {
   double min = 3.4e+308;
   for (unsigned i = 0; i < valuesQuantity; i++) {
    if (X[i] < min) {
     min = X[i];
    }
   }
   xFrom = min;
  }

  void calculateXTo() {
   double max = 3.4e-308;
   for (unsigned i = 0; i < valuesQuantity; i++) {
    if (X[i] > max) {
     max = X[i];
    }
   }
   xTo = max;
  }

  void calculateXStep() {
   double minStep = 3.4e+308, step;
   for (unsigned i = 0; i < valuesQuantity; i++) {
    for (unsigned j = i + 1; j < valuesQuantity; j++) {
     step = fabs(X[j] - X[i]);
     if (step < minStep) {
      minStep = step;
     }
    }
   }
   xStep = minStep;
  }

  void calculateYFrom() {
   double min = 3.4e+308;
   for (unsigned i = 0; i < valuesQuantity; i++) {
    if (Y[i] < min) {
     min = Y[i];
    }
   }
   yFrom = min;
  }

  void calculateYTo() {
   double max = 3.4e-308;
   for (unsigned i = 0; i < valuesQuantity; i++) {
    if (Y[i] > max) {
     max = Y[i];
    }
   }
   yTo = max;
  }

 public:
  FEReader(char fileName[128]) {
   double x, y;
   char strTemp[39], cTemp;
   valuesQuantity = 0;
   FILE *f = fopen(fileName, "rt");
   if (f == NULL) {
    printf(
     "ERROR#%d: %s\nCannot open text file \"%s\" for reading\n",
     errno,
     sys_errlist[errno],
     fileName
    );
    exit(-1);
   }
   while(!feof(f)) {
    fgets(strTemp, 38, f);
    valuesQuantity++;
   }
   fseek(f, -1, SEEK_END);
   fscanf(f, "%c", &cTemp);
   if (cTemp == '\n') {
    valuesQuantity--;
   }
   fseek(f, 0, SEEK_SET);
   X = new double [valuesQuantity];
   Y = new double [valuesQuantity];
   for (unsigned i = 0; i < valuesQuantity; i++) {
    fscanf(f, "%lf %lf", &x, &y);
    X[i] = x;
    Y[i] = y;
   }
   fclose(f);
  }
  double getXFrom() {
   this->calculateXFrom();
   return xFrom;
  }
  double getXTo() {
   this->calculateXTo();
   return xTo;
  }
  double getXStep() {
   this->calculateXStep();
   return xStep;
  }
  double getYFrom() {
   this->calculateYFrom();
   return yFrom;
  }
  double getYTo() {
   this->calculateYTo();
   return yTo;
  }
  unsigned getValuesQuantity() {
   return valuesQuantity;
  }
  double* getX() {
   return X;
  }
  double getXClause(unsigned i) {
   return X[i];
  }
  double* getY() {
   return Y;
  }
  double getYClause(unsigned i) {
   return Y[i];
  }
  ~FEReader() {
   delete [] X;
   delete [] Y;
  }
};

#endif