#ifndef FOREXEC_HPP
#define FOREXEC_HPP

#include "./FOREXEC/EXECUTOR.HPP"

class ForExec : public Executor {
 protected:
  void saveBeforeExecute() {
   char source[1119]; //1099
   strcpy(source, "");
   strcat(source, "#include <stdio.h>\n");
   strcat(source, "#include <conio.h>\n");
   strcat(source, "#include <math.h>\n");
   strcat(source, "#include <stdlib.h>\n\n");
   strcat(source, "#define accuracy 0.000001\n\n");
   strcat(source, "double f(double x) {\n return ");
   strcat(source, this->expression);
   strcat(source, "\n}\n\n");
   strcat(source, "int main(int argc, char *argv[]) {\n");
   strcat(source, " double from, to, step, *breakPoints, y, h;\n");
   strcat(source, " unsigned bpq = 0, j, b;\n");
   strcat(source, " char **strBreakPoints;\n");
   strcat(source, " FILE *fl;\n");
   strcat(source, " if (argc < 4) {\n");
   strcat(source, "  printf(\"Command must have from 3 arguments\\n\");\n");
   strcat(source, "  getch();\n  return -1;\n }\n");
   strcat(source, " from = atof(argv[1]);\n");
   strcat(source, " to = atof(argv[2]);\n");
   strcat(source, " step = atof(argv[3]);\n");
   strcat(source, " while (argv[bpq + 4] != NULL) {\n  bpq++;\n }\n");
   strcat(source, " if (bpq > 0) {\n");
   strcat(source, "  strBreakPoints = &argv[4];\n");
   strcat(source, "  breakPoints = (double*)malloc(bpq * sizeof(double));\n");
   strcat(source, "  for (j = 0; j < bpq; j++) {\n");
   strcat(source, "   breakPoints[j] = atof(strBreakPoints[j]);\n  }\n");
   strcat(source, " }\n fl = fopen(\"fe_res.txt\", \"wt\");\n");
   strcat(source, " for (h = from; h <= to; h += step) {\n");
   strcat(source, "  b = 0;\n");
   strcat(source, "  for (j = 0; j < bpq; j++) {\n");
   strcat(source, "   if (fabs(h - breakPoints[j]) < accuracy) {\n");
   strcat(source, "    b = 1;\n    break;\n   }\n  }\n  if (b == 1) {\n   continue;\n  }\n");
   strcat(source, "  y = f(h);\n");
   strcat(source, "  fprintf(fl, \"%f %f\\n\", h, y);\n");
   strcat(source, " }\n fclose(fl);\n"); //845
   strcat(source, " if (bpq > 0) {\n  free(breakPoints);\n }\n");
   strcat(source, " return 0;\n}\n");

   FILE *f = fopen(this->execSourcePath, "wt");
   fprintf(f, "%s", source);
   fclose(f);
  }
 public:
  ForExec(char strFilesDir[116], char fileNameBeforeExtension[9]) :
   Executor(strFilesDir, fileNameBeforeExtension) {
   }
   ~ForExec() {
   }
};

#endif