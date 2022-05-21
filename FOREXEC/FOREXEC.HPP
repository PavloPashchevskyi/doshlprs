#ifndef FOREXEC_HPP
#define FOREXEC_HPP

#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <process.h>
#include <stdlib.h>

class ForExec {
 private:
  char filesDir[116];
  char execSourcePath[128];
  char execObjectPath[128];
  char execCommandPath[128];
  char expression[128];

  void saveBeforeExecute() {
   char source[1099];
   strcpy(source, "");
   strcat(source, "#include <stdio.h>\n");
   strcat(source, "#include <conio.h>\n");
   strcat(source, "#include <math.h>\n");
   strcat(source, "#include <stdlib.h>\n\n");
   strcat(source, "#define accuracy 0.000001\n\n");
   strcat(source, "double formula(double x) {\n return ");
   strcat(source, this->expression);
   strcat(source, "\n}\n\n");
   strcat(source, "int main(int argc, char *argv[]) {\n");
   strcat(source, " double from, to, step, *breakPoints, y, temp, h;\n");
   strcat(source, " unsigned bpq = 0, j;\n");
   strcat(source, " char **strBreakPoints;\n");
   strcat(source, " FILE *f;\n");
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
   strcat(source, " }\n f = fopen(\"fe_res.txt\", \"wt\");\n");
   strcat(source, " for (h = from; h <= to; h += step) {\n");
   strcat(source, "  temp = h;\n");
   strcat(source, "  for (j = 0; j < bpq; j++) {\n");
   strcat(source, "   if (fabs(temp - breakPoints[j]) < accuracy) {\n");
   strcat(source, "    temp += accuracy;\n   }\n  }\n");
   strcat(source, "  y = formula(temp);\n");
   strcat(source, "  fprintf(f, \"%f %f\\n\", temp, y);\n");
   strcat(source, " }\n fclose(f);\n"); //845
   strcat(source, " if (bpq > 0) {\n  free(breakPoints);\n }\n");
   strcat(source, " return 0;\n}\n");

   FILE *f = fopen(this->execSourcePath, "wt");
   fprintf(f, "%s", source);
   fclose(f);
  }

  int callCompiler() {
   char commandText[69];
   strcpy(commandText, "");
   sprintf(commandText, "gcc -x c -std=c90 -c %s -o %s", this->execSourcePath, this->execObjectPath);
   int result = system(commandText);
   if (result == -1) {
    printf("ERROR#%d: Unable to compile the %s file\n%s\n",
     errno,
     this->execSourcePath,
     sys_errlist[errno]
    );
   }

   return result;
  }

  int callLinker() {
   char commandText[70];
   strcpy(commandText, "");
   sprintf(commandText, "gcc -std=c90 %s -o %s", this->execObjectPath, this->execCommandPath);
   int result = system(commandText);
   if (result == -1) {
    printf(
     "ERROR#%d: Unable to link command %s\n%s\n",
      errno,
      this->execCommandPath,
      sys_errlist[errno]
    );
   }

   return result;
  }

 public:
  ForExec(char strFilesDir[116]) {
   strcpy(this->filesDir, strFilesDir);
   strcpy(this->execSourcePath, this->filesDir);
   strcpy(this->execObjectPath, this->filesDir);
   strcpy(this->execCommandPath, this->filesDir);
   int filesDirLength = strlen(this->filesDir);
   if(this->filesDir[filesDirLength - 1] != '\\') {
    strcat(this->filesDir, "\\");
   }
   strcat(this->execSourcePath, "FOREXECR.C");
   strcat(this->execObjectPath, "FOREXECR.O");
   strcat(this->execCommandPath, "FOREXECR.EXE");
  }
  char* getFilesDirectory() {
   return this->filesDir;
  }
  void setFormula(char expression[128]) {
   int exprLength = strlen(expression);
   if (expression[exprLength - 1] != ';') {
    strcat(expression, ";");
   }
   strcpy(this->expression, expression);
  }
  int execute(double from, double to, double step, double *breakPoints = NULL, unsigned bpq = 0) {
   this->saveBeforeExecute();
   int result = this->callCompiler();
   if (result == -1) {
    printf("Unable to create command, executing the formula\n");
    return result;
   }
   result = this->callLinker();
   char *commandText = new char[81 + 18 * bpq + bpq], breakPoint[19];
   sprintf(commandText, "%s %f %f %f", this->execCommandPath, from, to, step);
   if (bpq > 0) {
    strcat(commandText, " ");
    for (unsigned i = 0; i < bpq; i++) {
     sprintf(breakPoint, "%f", breakPoints[i]);
     strcat(commandText, breakPoint);
     if (i < bpq - 1) {
      strcat(commandText, " ");
     }
    }
   }
   result = system(commandText);
   delete [] commandText;
   if (result == -1) {
    printf(
     "ERROR#%d: Unable to execute the formula for range [%f; %f] with step %f\n%s\n",
      errno,
      from,
      to,
      step,
      sys_errlist[errno]
    );
   }

   return result;
  }
};

#endif