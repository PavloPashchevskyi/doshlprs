#include "./GRAPHIC/PLANE2D.HPP"
#include "./GRAPHIC/PLANEHIST.HPP"
#include "./GRAPHIC/GRAPHIC.HPP"

#include "./MENU/MENU.HPP"
#include "./MENU/MCONTROL.HPP"

void onGraphicItemSelect();
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
  MenuItem("histogram", "Histogram"),
  MenuItem("graphsep", "Graph only"),
  MenuItem("exit", "Exit")
 };
 items[0].setOnSelectAction(onAboutItemSelect);
 items[1].setOnSelectAction(onSomeItemSelect);
 items[2].setOnSelectAction(onGraphicItemSelect);
 items[3].setOnSelectAction(onHistogramItemSelect);
 items[4].setOnSelectAction(onGraphicSeparatelyItemSelect);
 Menu grMenu(items, 6);
 grMenu.show();
 if (i < 2) {
  MControl ctrl(grMenu);
 }
}

void onGraphicItemSelect() {
 cleardevice();
 Plane2D axes(0, 16, 1, 0, 4, GREEN, WHITE, 1, 1);
 axes.addGraphic(sqrt);
 char c = getch();
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

double invertProp(double x) {
 return 1. / x;
}

int main() {
  buildGraphicalMenu();
  return 0;
}
