#ifndef GRMODE_HPP
#define GRMODE_HPP

#include <graphics.h>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>

class GrMode {
 private:
  static GrMode *hInstance;
  static int graphicalModeOpeningResult;
  GrMode() {
   hInstance = 0;

   /* request auto detection */
   int gdriver = DETECT, gmode, errorcode;

   /* initialize graphics mode */
   initgraph(&gdriver, &gmode, "");

   /* read result of initialization */
   GrMode::graphicalModeOpeningResult = graphresult();

   if (GrMode::graphicalModeOpeningResult != grOk)  /* an error occurred */
   {
    printf("Graphics error: %s\n",
     grapherrormsg(GrMode::graphicalModeOpeningResult));
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
  static GrMode* closeGraphicalModeIfOpened() {
   if (GrMode::graphicalModeOpeningResult == grOk) {
    closegraph();
    if (hInstance != 0) {
     delete GrMode::hInstance;
     GrMode::hInstance = 0;
    }
   }
   return GrMode::hInstance;
  }
  ~GrMode() {
  }
};

GrMode *GrMode::hInstance;
int GrMode::graphicalModeOpeningResult = grNoInitGraph;

#endif