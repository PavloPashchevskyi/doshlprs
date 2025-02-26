#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <stdio.h>

class Config {
 private:
  static const char *FORMULA_EXECUTOR_COMPILER_PATH;
  static const char *FORMULA_EXECUTOR_LINKER_PATH;
  static const char *FORMULA_LINKER_COMPILER_PATH;
  static const char *FORMULA_LINKER_LINKER_PATH;
  static const char *FORMULA_EXECUTOR_INCLUDE_PATH;
  static const char *FORMULA_LINKER_INCLUDE_PATH;
  static const char *FORMULA_EXECUTOR_LIB_PATH;
  static const char *FORMULA_LINKER_LIB_PATH;
  static const char *FORMULA_EXECUTOR_LANGUAGE;
  static const char *FORMULA_LINKER_LANGUAGE;
  static const char *FORMULA_EXECUTOR_LANGUAGE_STANDARD;
  static const char *FORMULA_LINKER_LANGUAGE_STANDARD;
  static const char *FORMULA_LINKER_ADDITIONAL_OBJS;
  static const char *FORMULA_LINKER_STATIC_LIBS;

  static char FORMULA_EXECUTOR_COMPILER_COMMAND_TEXT[127];
  static char FORMULA_EXECUTOR_LINKER_COMMAND_TEXT[127];
  static char FORMULA_LINKER_COMPILER_COMMAND_TEXT[127];
  static char FORMULA_LINKER_LINKER_COMMAND_TEXT[127];
 public:
  static char* getFormulaExecutorCompilerCommandText(
   char *sourcePath,
   char *objectPath
  ) {
   sprintf(Config::FORMULA_EXECUTOR_COMPILER_COMMAND_TEXT, "%s -x %s -std=%s -c %s -o %s", Config::FORMULA_EXECUTOR_COMPILER_PATH, Config::FORMULA_EXECUTOR_LANGUAGE, Config::FORMULA_EXECUTOR_LANGUAGE_STANDARD, sourcePath, objectPath);
   return Config::FORMULA_EXECUTOR_COMPILER_COMMAND_TEXT;
  }
  static char* getFormulaExecutorLinkerCommandText(char *objectPath, char *commandPath) {
   sprintf(Config::FORMULA_EXECUTOR_LINKER_COMMAND_TEXT, "%s -std=%s %s -o %s", Config::FORMULA_EXECUTOR_LINKER_PATH, Config::FORMULA_EXECUTOR_LANGUAGE_STANDARD, objectPath, commandPath);
   return Config::FORMULA_EXECUTOR_LINKER_COMMAND_TEXT;
  }
  static char* getFormulaLinkerCompilerCommandText(char *sourceName) {
   sprintf(Config::FORMULA_LINKER_COMPILER_COMMAND_TEXT, "%s -I%s -L%s -c -Wd %s", Config::FORMULA_LINKER_COMPILER_PATH, Config::FORMULA_LINKER_INCLUDE_PATH, Config::FORMULA_LINKER_LIB_PATH, sourceName);
   return Config::FORMULA_LINKER_COMPILER_COMMAND_TEXT;
  }
  static char* getFormulaLinkerLinkerCommandText(char *sourceName) {
   sprintf(Config::FORMULA_LINKER_LINKER_COMMAND_TEXT, "%s -L%s -Twd %s %s.OBJ,%s.DLL,%s.MAP,%s", Config::FORMULA_LINKER_LINKER_PATH, Config::FORMULA_LINKER_LIB_PATH, Config::FORMULA_LINKER_ADDITIONAL_OBJS, sourceName, sourceName, sourceName, Config::FORMULA_LINKER_STATIC_LIBS);
   return Config::FORMULA_LINKER_LINKER_COMMAND_TEXT;
  }
};

const char* Config::FORMULA_EXECUTOR_COMPILER_PATH = "c:\\compile\\djgpp\\bin\\gcc";
const char* Config::FORMULA_EXECUTOR_LINKER_PATH = "c:\\compile\\djgpp\\bin\\gcc";
const char* Config::FORMULA_LINKER_COMPILER_PATH =
 "c:\\compile\\bc\\bin\\bcc.exe";
const char* Config::FORMULA_LINKER_LINKER_PATH =
 "c:\\compile\\bc\\bin\\tlink.exe";
const char* Config::FORMULA_EXECUTOR_INCLUDE_PATH = "";
const char* Config::FORMULA_LINKER_INCLUDE_PATH = "c:\\compile\\bc\\include";
const char* Config::FORMULA_EXECUTOR_LIB_PATH = "";
const char* Config::FORMULA_LINKER_LIB_PATH = "c:\\compile\\bc\\lib";
const char* Config::FORMULA_EXECUTOR_LANGUAGE = "c";
const char* Config::FORMULA_LINKER_LANGUAGE = "";
const char* Config::FORMULA_EXECUTOR_LANGUAGE_STANDARD = "c90";
const char* Config::FORMULA_LINKER_LANGUAGE_STANDARD = "c90";
const char* Config::FORMULA_LINKER_ADDITIONAL_OBJS = "C0S.OBJ";
const char* Config::FORMULA_LINKER_STATIC_LIBS = "EMU.LIB MATHS.LIB CS.LIB";

char Config::FORMULA_EXECUTOR_COMPILER_COMMAND_TEXT[127];
char Config::FORMULA_EXECUTOR_LINKER_COMMAND_TEXT[127];
char Config::FORMULA_LINKER_COMPILER_COMMAND_TEXT[127];
char Config::FORMULA_LINKER_LINKER_COMMAND_TEXT[127];

#endif