#ifndef GRMODE_HPP
#define GRMODE_HPP

#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

class GrMode {
 private:
  static GrMode *hInstance;
  GrMode() {
   hInstance = 0;

   /* request auto detection */
   int gdriver = DETECT, gmode, errorcode;

   /* initialize graphics mode */
   initgraph(&gdriver, &gmode, "");

   /* read result of initialization */
   errorcode = graphresult();

   if (errorcode != grOk)  /* an error occurred */
   {
    printf("Graphics error: %s\n", grapherrormsg(errorcode));
    printf("Press any key to halt:");
    getch();
    exit(1);             /* return with error code */
   }
  }
 public:
  static GrMode* initGraphicalMode() {
   if (GrMode::hInstance == 0) {
    GrMode::hInstance = new GrMode();
   }
   return GrMode::hInstance;
  }
  ~GrMode() {
   closegraph();
   if (hInstance != 0) {
    delete GrMode::hInstance;
    GrMode::hInstance = 0;
   }
  }
};

GrMode *GrMode::hInstance;

#endif