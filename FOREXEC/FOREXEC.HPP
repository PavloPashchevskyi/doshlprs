#ifndef FOREXEC_HPP
#define FOREXEC_HPP

#include "./FOREXEC/EXECUTOR.HPP"

class ForExec : public Executor {
 protected:
  void saveBeforeExecute() {
   char *source; //963
   char *includedSource; //213
   char includedSourcePath[120];

   strcpy(includedSourcePath, "");
   strcat(includedSourcePath, this->filesDir);
   strcat(includedSourcePath, "F.H");

   char *includedSourceMatches[] = {"return ", this->expression, ""};
   if (isFileRecreatingNeeded(includedSourcePath, includedSourceMatches)) {
    includedSource = new char[213];

    strcpy(includedSource, ""); //0
    strcat(includedSource, "#ifndef F_H\n"); //12
    strcat(includedSource, "#define F_H\n\n"); //25
    strcat(includedSource, "#include <math.h>\n\n"); //44
    strcat(includedSource, "double f(double x) {\n"); //65
    strcat(includedSource, " return "); //73
    strcat(includedSource, this->expression); //73+128=201
    strcat(includedSource, "\n}\n\n"); //205
    strcat(includedSource, "#endif\n"); //212

    FILE *includedF = fopen(includedSourcePath, "wt");
    fprintf(includedF, "%s", includedSource);
    fclose(includedF);

    delete [] includedSource;
   }

   char *sourceMatches[] = {"\"F.H\"", " = f(", ""};
   if (isFileRecreatingNeeded(this->execSourcePath, sourceMatches)) {
    source = new char[963];

    strcpy(source, ""); //0
    strcat(source, "#include <stdio.h>\n"); //19
    strcat(source, "#include <conio.h>\n"); //38
    strcat(source, "#include <stdlib.h>\n\n"); //59
    strcat(source, "#include \"F.H\"\n\n"); //75
    strcat(source, "#define accuracy 0.000001\n\n"); //102
    strcat(source, "int main(int argc, char *argv[]) {\n"); //137
    strcat(source, " double from, to, step, *breakPoints, y, h;\n"); //181
    strcat(source, " unsigned bpq = 0, j, b;\n"); //206
    strcat(source, " char **strBreakPoints;\n"); //230
    strcat(source, " FILE *fl;\n"); //241
    strcat(source, " if (argc < 4) {\n"); //258
    strcat(source, "  printf(\"Command must have from 3 arguments\\n\");\n"); //308
    strcat(source, "  getch();\n  return -1;\n }\n"); //335
    strcat(source, " from = atof(argv[1]);\n"); //358
    strcat(source, " to = atof(argv[2]);\n"); //379
    strcat(source, " step = atof(argv[3]);\n"); //402
    strcat(source, " while (argv[bpq + 4] != NULL) {\n  bpq++;\n }\n"); //447
    strcat(source, " if (bpq > 0) {\n"); //463
    strcat(source, "  strBreakPoints = &argv[4];\n"); //492
    strcat(source, "  breakPoints = (double*)malloc(bpq * sizeof(double));\n"); //547
    strcat(source, "  for (j = 0; j < bpq; j++) {\n"); //577
    strcat(source, "   breakPoints[j] = atof(strBreakPoints[j]);\n  }\n"); //626
    strcat(source, " }\n fl = fopen(\"fe_res.txt\", \"wt\");\n"); //662
    strcat(source, " for (h = from; h <= to; h += step) {\n"); //700
    strcat(source, "  b = 0;\n"); //709
    strcat(source, "  for (j = 0; j < bpq; j++) {\n"); //739
    strcat(source, "   if (fabs(h - breakPoints[j]) < accuracy) {\n"); //785
    strcat(source, "    b = 1;\n    break;\n   }\n  }\n  if (b == 1) {\n   continue;\n  }\n"); //849
    strcat(source, "  y = f(h);\n"); //861
    strcat(source, "  fprintf(fl, \"%f %f\\n\", h, y);\n"); //893
    strcat(source, " }\n fclose(fl);\n"); //909
    strcat(source, " if (bpq > 0) {\n  free(breakPoints);\n }\n"); //949
    strcat(source, " return 0;\n}\n"); //962

    FILE *f = fopen(this->execSourcePath, "wt");
    fprintf(f, "%s", source);
    fclose(f);

    delete [] source;
   }
  }
 public:
  ForExec(char strFilesDir[116], char fileNameBeforeExtension[9]) :
   Executor(strFilesDir, fileNameBeforeExtension) {
   }
   ~ForExec() {
   }
};

#endif