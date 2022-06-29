#include "./GRAPHIC/PLANE2D.HPP"
#include "./GRAPHIC/PLANEHIST.HPP"
#include "./GRAPHIC/GRAPHIC.HPP"
#include "./GRAPHIC/GMANAGER.HPP"
#include "./GRAPHIC/GCONTROL.HPP"

#include "./MENU/MENU.HPP"
#include "./MENU/MCONTROL.HPP"

#include "./FOREXEC/FOREXEC.HPP"
#include "./FOREXEC/FEREADER.HPP"

void onGraphicItemSelect();
void onYourGraphicItemSelect();
void onHistogramItemSelect();
void onGraphicSeparatelyItemSelect();

void onAboutItemSelect() {
 outtextxy(127, 0, "It is the C++ Application for DOS!");
}

void onSomeItemSelect() {
 outtextxy(127, 7, "This is action on \"Some\" menu item select");
}

void buildGraphicalMenu() {
 static unsigned i = 0;
 i++;
 MenuItem items[] = {
  MenuItem("about", "About"),
  MenuItem("some", "Some"),
  MenuItem("graphic", "Graphic"),
  MenuItem("yourgraph", "Your graph"),
  MenuItem("histogram", "Histogram"),
  MenuItem("graphsep", "Graph only"),
  MenuItem("exit", "Exit")
 };
 items[0].setOnSelectAction(onAboutItemSelect);
 items[1].setOnSelectAction(onSomeItemSelect);
 items[2].setOnSelectAction(onGraphicItemSelect);
 items[3].setOnSelectAction(onYourGraphicItemSelect);
 items[4].setOnSelectAction(onHistogramItemSelect);
 items[5].setOnSelectAction(onGraphicSeparatelyItemSelect);
 Menu grMenu(items, 7);
 grMenu.show();
 if (i < 2) {
  MControl ctrl(grMenu);
 }
}

void onGraphicItemSelect() {
 cleardevice();
 Plane2D axes(0, 6.28, 0.261799, 0, 3, GREEN, WHITE, 1, 1);
 axes.addGraphic(sqrt, NULL, 0, RED);
 axes.addGraphic(sin, NULL, 0, YELLOW);

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
 if (strcmp(x, "Зеленский") == 0) {
  return 33.33333333333333333;
 }
 if (strcmp(x, "Порошенко") == 0) {
  return 11.11;
 }
 if (strcmp(x, "Тимошенко") == 0) {
  return 11.05;
 }
 if (strcmp(x, "Смешко") == 0) {
  return 11.17;
 }
 return 7.45;
}

void onHistogramItemSelect() {
 cleardevice();
 unsigned valuesCount = 4;
 char values[][40] = {"Зеленский", "Порошенко", "Тимошенко", "Смешко"};

 PlaneHis *planeHistogram;
 planeHistogram = new PlaneHis(valuesCount, values, sample, WHITE);
 planeHistogram->plot();

 char c = getch();
 if (c == 27) {
  cleardevice();
  buildGraphicalMenu();
 }
}

void onGraphicSeparatelyItemSelect() {
 cleardevice();

 double X[] = {-M_PI,-5*M_PI/6,-2*M_PI/3,-M_PI/2,-M_PI/3,-M_PI/4,-M_PI/6,0,M_PI/6,M_PI/4,M_PI/3,M_PI/2,2*M_PI/3,5*M_PI/6,M_PI};
 Graphic grSep(X, sin, 15/*, tanBreakPoints, 1*/);
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

int main() {
  buildGraphicalMenu();
  return 0;
}
