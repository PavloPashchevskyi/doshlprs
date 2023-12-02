#ifndef EXECUTOR_HPP
#define EXECUTOR_HPP

#include <string.h>
#include <stdio.h>
#include <conio.h>
#include <process.h>
#include <stdlib.h>

class Executor {
 private:
  char execObjectPath[128];

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

 protected:
  char filesDir[116];
  char fileNameBeforeExtension[9];
  char execSourcePath[128];
  char execCommandPath[128];

  char expression[128];

  virtual void saveBeforeExecute() = 0;
  virtual int callWrittenProgram(
   double from,
   double to,
   double step,
   double *additionals = NULL,
   unsigned additionalsQuantity = 0
  ) = 0;

 public:
  Executor(char strFilesDir[116], char fileNameBeforeExtension[9]) {
   strcpy(this->filesDir, strFilesDir);
   strcpy(this->fileNameBeforeExtension, fileNameBeforeExtension);
   strcpy(this->execSourcePath, this->filesDir);
   strcpy(this->execObjectPath, this->filesDir);
   strcpy(this->execCommandPath, this->filesDir);
   int filesDirLength = strlen(this->filesDir);
   if(this->filesDir[filesDirLength - 1] != '\\') {
    strcat(this->filesDir, "\\");
   }
   strcat(this->execSourcePath, this->fileNameBeforeExtension);
   strcat(this->execObjectPath, this->fileNameBeforeExtension);
   strcat(this->execCommandPath, this->fileNameBeforeExtension);
   strcat(this->execSourcePath, ".C");
   strcat(this->execObjectPath, ".O");
   strcat(this->execCommandPath, ".EXE");
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
  int execute(double from, double to, double step, double *additionals = NULL, unsigned aq = 0) {
   this->saveBeforeExecute();
   int result = this->callCompiler();
   if (result == -1) {
    printf("Unable to compile program, executing the formula\n");
    return result;
   }
   result = this->callLinker();
   if (result == -1) {
    printf("Unable to create command, executing the formula\n");
    return result;
   }
   result = callWrittenProgram(from, to, step, additionals, aq);
   if (result == -1) {
    printf("Unable to execute command, written for executing the formula\n");
    return result;
   }
   return result;
  }
  virtual ~Executor() {
  }
};

#endif