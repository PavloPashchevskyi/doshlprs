#include "./GRAPHIC/PLANE2D.HPP"
#include "./GRAPHIC/PLANEHIST.HPP"
#include "./GRAPHIC/GRAPHIC.HPP"
#include "./GRAPHIC/GMANAGER.HPP"
#include "./GRAPHIC/GCONTROL.HPP"

#include "./MENU/MENU.HPP"
#include "./MENU/MCONTROL.HPP"

#include "./FOREXEC/FOREXEC.HPP"
#include "./FOREXEC/FEREADER.HPP"

#include <dos.h>

void onAboutItemSelect();
void onManualItemSelect();
void onGraphicItemSelect();
void onYourGraphicItemSelect();
void onHistogramItemSelect();
void onHistogramOnPlane2DItemSelect();
void onGraphicSeparatelyItemSelect();
void onSoundItemSelect();
void onHelpItemSelect();

void buildGraphicalMenu() {
 static unsigned i = 0;
 i++;
 MenuItem items[] = {
  MenuItem("graphic", "Graphic"),
  MenuItem("yourgraph", "Your graph"),
  MenuItem("graphsep", "Graph only"),
  MenuItem("histogram", "Histogram"),
  MenuItem("histogram_on_plane_2d", "Histogram2"),
  MenuItem("sound", "Sound"),
  MenuItem("help", "Help"),
  MenuItem("exit", "Exit")
 };
 items[0].setOnSelectAction(onGraphicItemSelect);
 items[1].setOnSelectAction(onYourGraphicItemSelect);
 items[2].setOnSelectAction(onGraphicSeparatelyItemSelect);
 items[3].setOnSelectAction(onHistogramItemSelect);
 items[4].setOnSelectAction(onHistogramOnPlane2DItemSelect);
 items[5].setOnSelectAction(onSoundItemSelect);
 items[6].setOnSelectAction(onHelpItemSelect);
 Menu grMenu(items, 8);
 grMenu.show();
 if (i < 2) {
  MControl ctrl(&grMenu);
 }
}

void buildHelpGraphicalMenu() {
 static unsigned i = 0;
 i++;

 MenuItem items[] = {
  MenuItem("manual", "Manual"),
  MenuItem("about", "About")
 };
 items[0].setOnSelectAction(onManualItemSelect);
 items[1].setOnSelectAction(onAboutItemSelect);
 Menu *grPopupMenu = new Menu(items, 2, 2);
 grPopupMenu->show();

 if (i < 2) {
  MControl ctrl(grPopupMenu);
 }
 delete grPopupMenu;
}

void onAboutItemSelect() {
 cleardevice();
 buildGraphicalMenu();
 outtextxy(127, 8, "DOS Helpers are the modules for using in another applications, written with C++ for DOS.");
 outtextxy(127, 16, "ATTENTION! For working of these DOS helpers driver \"EGAVGA.BGI\" by (c) Borland International, Inc is required. It is in repository. Please, do not replace to another folder or remove it!");
 outtextxy(127, 24, "Modules provides such elements of GUI application as the following.");
 outtextxy(127, 32, " - Graphical vertical menu (\"MENU\" folder)");
 outtextxy(127, 40, " - Function(s) graphic(s) plotter (\"GRAPHIC\" folder)");
 outtextxy(127, 48, " - Histogram plotter (\"GRAPHIC\" folder)");
 outtextxy(127, 56, " - Executing the formula, written with C language as value, returned from C function (\"FOREXEC\" folder). GCC is required for this.");
 outtextxy(127, 64, "These modules are written by Pavlo Pashchevskyi (mailto://googalltooth@gmail.com) and free to use by anyone, who wants to write GUI applications for DOS with C and/or C++ language.");
 outtextxy(127, 72, "If you have any questions or suggestions regarding these modules, please, contact me by email.");

 char c = getch();
 if (c == 27) {
  cleardevice();
  buildGraphicalMenu();
  buildHelpGraphicalMenu();
 }
}

void onManualItemSelect() {
 cleardevice();
 buildGraphicalMenu();
 outtextxy(127, 8, "MENU");
 outtextxy(127, 16, "Graphical vertical menu.");
 outtextxy(127, 24, "Use arrows up and down to walk this menu.");
 outtextxy(127, 32, "To select menu item press \"Enter\".");
 outtextxy(127, 40, "To exit program, select \"Exit\" item in main menu or press \"esc\", if you are not in popup menu.");
 outtextxy(127, 48, "If you are in popup menu, press \"esc\" to return to previous menu.");
 outtextxy(127, 56, "GRAPHIC");
 outtextxy(127, 64, "If you are selected \"Graphic\" menu item");
 outtextxy(127, 72, " - press keys from 0 to 9 to delete graphic from plane, which number is from 1 to 10.");
 outtextxy(127, 80, " - press key \"c\" to delete all graphics from plane.");
 outtextxy(127, 88, " - press arrow left/right to move graphic(s) left/right");
 outtextxy(127, 96, " - press arrow down/up to move graphic(s) left/right");
 outtextxy(127, 104, " - press w key to increase scale (zoom in twice)");
 outtextxy(127, 116, " - press s key to decrease scale (unzoom twice)");
 outtextxy(127, 124, " - press \"esc\" to return to menu");
 outtextxy(127, 132, "Known issue: when you try to move graphic or zoom/unzoom and press appropriate button firstly, press it again. When you press firstly, axes are written and drawn wrongly.");

 char c = getch();
 if (c == 27) {
  cleardevice();
  buildGraphicalMenu();
  buildHelpGraphicalMenu();
 }
}


double invertProp(double x) {
 return 1. / x;
}

void onGraphicItemSelect() {
 cleardevice();
 Plane2D axes(0, 6.28, 0.261799, 0, 3, GREEN, WHITE, 1, 1);
 axes.addGraphic(sqrt, NULL, 0, RED);
 axes.addGraphic(sin, NULL, 0, YELLOW);
 double logBPs[1] = {0.00};
 axes.addGraphic(log10, logBPs, 1, BLUE);
 axes.addGraphic(invertProp, logBPs, 1, MAGENTA);

 GManager gm(&axes);
 GControl gc(&gm);

 char c = getch();
 if (c == 27) {
  cleardevice();
  buildGraphicalMenu();
 }
}

void onYourGraphicItemSelect() {
 char expression[128];
 double from, to, step, *breakPoints = NULL;
 unsigned breakPointsQuantity = 0;
 cleardevice();
 printf("Input formula in the format of y = f(x) with C language syntax:\n");
 printf("y = f(x) = ");
 scanf("%s", &expression);
 printf("Which range and step you would like to research this function?\n");
 printf("Left border (including into range): ");
 scanf("%lf", &from);
 printf("Right border (NOT in range): ");
 scanf("%lf", &to);
 printf("Step (difference between two the nearest values): ");
 scanf("%lf", &step);
 printf("Does the function have breakpoints in range you have input?\n");
 char c = getch();
 if (c == 'y' || c == 'Y' || c == 'д' || c == 'Д') {
  printf("How many breakpoints has function in range [%f; %f)? ", from, to);
  scanf("%d", &breakPointsQuantity);
  if (breakPointsQuantity > 0) {
   breakPoints = new double[breakPointsQuantity];
   for (unsigned i = 0; i < breakPointsQuantity; i++) {
    printf("Please, input breakpoint #%d: ", i + 1);
    scanf("%lf", (breakPoints+i));
   }
  }
 }

 cleardevice();

 ForExec fe(".\\forexec\\");
 fe.setFormula(expression);
 fe.execute(from, to, step, breakPoints, breakPointsQuantity);

 FEReader fer(".\\fe_res.txt");

 Plane2D plane2D(fer.getXFrom(), fer.getXTo(), fer.getXStep(), fer.getYFrom(), fer.getYTo());
 plane2D.addGraphic(fer.getY(), breakPoints, breakPointsQuantity);

 if (breakPointsQuantity > 0) {
  delete [] breakPoints;
 }

 c = getch();
 if (c == 27) {
  cleardevice();
  buildGraphicalMenu();
 }
}

double sample(char *x) {
 if (strcmp(x, "Кучма") == 0) {
  return 67.50;
 }
 if (strcmp(x, "Симоненко") == 0) {
  return 3.125;
 }
 if (strcmp(x, "Тимошенко") == 0) {
  return 12.50;
 }
 if (strcmp(x, "Ткаченко") == 0) {
  return 8.4325;
 }
 if (strcmp(x, "Кравчук") == 0) {
  return 8.4325;
 }
 return 6.25;
}

void onHistogramItemSelect() {
 cleardevice();
 unsigned valuesCount = 5;
 char values[][40] = {"Кучма","Симоненко","Тимошенко","Ткаченко","Кравчук"};

 PlaneHis *planeHistogram;
 planeHistogram = new PlaneHis(valuesCount, values, sample, WHITE);
 planeHistogram->plot();

 char c = getch();
 if (c == 27) {
  cleardevice();
  buildGraphicalMenu();
 }
}

void onHistogramOnPlane2DItemSelect() {
 cleardevice();
 unsigned valuesCount = 5;
 char values[][40] = {"Кучма","Симоненко","Тимошенко","Ткаченко","Кравчук"};

 Plane2D *axes = new Plane2D(0,valuesCount,1,0,100,GREEN,WHITE,0,0,"","%",0);
 axes->buildHistogram(valuesCount, values, sample, WHITE);

 char c = getch();
 if (c == 27) {

  delete axes;

  cleardevice();
  buildGraphicalMenu();
 }
}

void onGraphicSeparatelyItemSelect() {
 cleardevice();

 double X[] = {-M_PI,-5*M_PI/6,-2*M_PI/3,-M_PI/2,-M_PI/3,-M_PI/4,-M_PI/6,0,M_PI/6,M_PI/4,M_PI/3,M_PI/2,2*M_PI/3,5*M_PI/6,M_PI};
 Graphic grSep(X, sin, 15);
 grSep.setXTranslationAddition(319.);
 grSep.setXStretchFactor(78.875);
 grSep.setYTranslationAddition(239.);
 grSep.setYStretchFactor(235.5);
 grSep.plot();

 char c = getch();
 if (c == 27) {
  cleardevice();
  buildGraphicalMenu();
 }
}

void onSoundItemSelect() {
 cleardevice();

 sound(1250);
 delay(1000);
 nosound();

 cleardevice();
 buildGraphicalMenu();
}

void onHelpItemSelect() {
 buildHelpGraphicalMenu();

 char c = getch();
 if (c == 27) {
  cleardevice();
  buildGraphicalMenu();
 }
}

int main() {
  buildGraphicalMenu();
  return 0;
}
