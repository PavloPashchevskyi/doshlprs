#ifndef CONFIG_HPP
#define CONFIG_HPP

struct Config {
 static const char *FORMULA_EXECUTOR_COMPILER_PATH;
 static const char *FORMULA_EXECUTOR_LINKER_PATH;
 static const char *FORMULA_LINKER_COMPILER_PATH;
 static const char *FORMULA_LINKER_LINKER_PATH;
 static const char *FORMULA_EXECUTOR_INCLUDE_PATH;
 static const char *FORMULA_LINKER_INCLUDE_PATH;
 static const char *FORMULA_EXECUTOR_LIB_PATH;
 static const char *FORMULA_LINKER_LIB_PATH;
 static const char *FORMULA_LINKER_ADDITIONAL_OBJS;
 static const char *FORMULA_LINKER_STATIC_LIBS;
};

const char* Config::FORMULA_EXECUTOR_COMPILER_PATH = "gcc";
const char* Config::FORMULA_EXECUTOR_LINKER_PATH = "gcc";
const char* Config::FORMULA_LINKER_COMPILER_PATH =
 "c:\\compile\\bc\\bin\\bcc.exe";
const char* Config::FORMULA_LINKER_LINKER_PATH =
 "c:\\compile\\bc\\bin\\tlink.exe";
const char* Config::FORMULA_EXECUTOR_INCLUDE_PATH = "";
const char* Config::FORMULA_LINKER_INCLUDE_PATH = "c:\\compile\\bc\\include";
const char* Config::FORMULA_EXECUTOR_LIB_PATH = "";
const char* Config::FORMULA_LINKER_LIB_PATH = "c:\\compile\\bc\\lib";
const char* Config::FORMULA_LINKER_ADDITIONAL_OBJS = "C0S.OBJ";
const char* Config::FORMULA_LINKER_STATIC_LIBS = "EMU.LIB MATHS.LIB CS.LIB";

#endif