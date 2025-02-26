DOS Helpers are the modules for using in another applications, written with C++ for DOS.

ATTENTION! For working of these DOS helpers driver "EGAVGA.BGI" by (c) Borland International, Inc is required. It is in repository. Please, do not replace to another folder or remove it!

Modules provides such elements of GUI application as the following.

 - Graphical vertical menu ("MENU" folder)
 - Function(s) graphic(s) plotter ("GRAPHIC" folder)
 - Histogram plotter ("GRAPHIC" folder)
 - Executing the formula, written with C language as value, returned from C function ("FOREXEC" folder). GCC is required for this.

 To use these modules, please, do the following.

 1. Rename "__CONFIG.HPP" to "CONFIG.HPP";
 2. In renamed file "CONFIG.HPP", please, write the path(s) to your compiler, linker and options for them. It is needed, for example, to be able to build graphic of fuction, which formula was input by yourself, after you selected     "Your graph" menu item.
 3. Change your current directory to the directory of these DOS helpers
 4. Compile "CONFIG.HPP". In "Borland C++ 3.1" it may be done by opening "CONFIG.HPP" and pressing "Alt+F9" keys combination.
 5. Build your project. In "Borland C++ 3.1" it may be done by opening the "MAIN.CPP" file and press "F9" key.
 6. Run "MAIN.EXE" file, which is in the directory of these DOS helpers. In "Borland C++ 3.1" it may be done by opening the "MAIN.CPP" file and press "Ctrl+F9" keys combination.

 There is class Config in file "CONFIG.HPP". It is class, which contains string constants with paths to compiler, linker and options of command to run it; string static variables with command text to run and methods, which build text of commands and return values of static variables (with command text). You can add your own constants, static variables, methods and modify existing methods depending on text of your commands to run your compiler and linker. Methods getFormulaLinkerCompilerCommandText() and getFormulaLinkerLinkerCommandText() are now using in ./FOREXEC/EXECUTOR.HPP file to call compiler and linker respectively. Please, keep this in mind before deleting or renaming these methods.

 Options in "CONFIG.HPP":
     Config::FORMULA_EXECUTOR_COMPILER_PATH = <path_to_your_compiler (for example, to bcc.exe)>
     Config::FORMULA_EXECUTOR_LINKER_PATH = "c:\\compile\\djgpp\\bin\\gcc" = <path_to_your_linker (for example, to tlink.exe)>
     Config::FORMULA_EXECUTOR_INCLUDE_PATH = <path_to_include_files_of_your_compiler_if_needed>
     Config::FORMULA_EXECUTOR_LIB_PATH = <path_to_lib_files_of_your_compiler_if_needed>
     Config::FORMULA_EXECUTOR_LANGUAGE = <for example, "c", "c++", "assembler" or "none" in case of gcc compilers. In case of "Borland c++ 3.1" leave empty>
     Config::FORMULA_EXECUTOR_LANGUAGE_STANDARD = <for example, "c90" for gcc compilers. In case of "Borland c++ 3.1" leave empty>

These modules are written by Pavlo Pashchevskyi (mailto://googalltooth@gmail.com) and free to use by anyone, who wants to write GUI applications for DOS with C and/or C++ language.

If you have any questions or suggestions regarding these modules, please, contact me by email.
