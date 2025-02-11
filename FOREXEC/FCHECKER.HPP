#ifndef FCHECKER_HPP
#define FCHECKER_HPP

#include <stdio.h>
#include <string.h>

class FChecker {
 protected:
  static unsigned isFileRecreatingNeeded(
   char *fileName,
   unsigned minFileSize,
   char **strings
  ) {
   unsigned checkingStringsQuantity = 0;
   while (strcmp(strings[checkingStringsQuantity], "") != 0) {
    checkingStringsQuantity++;
   }
   if (checkingStringsQuantity < 1) {
    return 0;
   }
   FILE *f = fopen(fileName, "rt");
   if (!f) {
    return 1;
   }
   char *fileTestStr = new char[1820];
   unsigned matchesQuantity = 0;
   unsigned symbolsQuantity = 0;
   while ((fgets(fileTestStr, 1820, f)) != NULL) {
    symbolsQuantity += strlen(fileTestStr);
    for (unsigned i = 0; i < checkingStringsQuantity; i++) {
     if (strstr(fileTestStr, strings[i]) != NULL) {
      matchesQuantity++;
     }
    }
   }
   delete [] fileTestStr;
   fclose(f);
   if (symbolsQuantity < minFileSize) {
    return 1;
   }
   return matchesQuantity < checkingStringsQuantity;
  }
};

#endif