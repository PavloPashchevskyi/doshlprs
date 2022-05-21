Class "ForExec" (FormulaExecutor) is designed for formula, input by user with C language syntax, to be "understood" by another parts of your project. Class "ForExec" passes formula from user and the range of values formula should be applied on. The results of appying are saving to file "FE_RES.TXT" in directory, where you put folder with this file (one step back from directory with this file). You can use the results from "FE_RES.TXT" in any other part of your project.

To use "ForExec" class you should do the following.

1. Installing of GCC on your DOS (or DOSBox).

1.1. Download DJGPP compiler, for example, from there: ftp://ftp.fu-berlin.de/pc/languages/djgpp/current . You need download the following archives
  v2/djdev205.zip,
  v2gnu/gcc*b.zip (* is version number, for examp;e gcc1030b.zip),
  v2gnu/gpp*b.zip (for example, gpp1030b.zip),
  v2gnu/bnu*b.zip (for example, bnu2351b.zip),
  v2misc/csdpmi*b.zip (for example, csdpmi7b.zip)

 for example to "djgpp_install" directory via "Total commander".

1.2. Unzip the archives to some folder, usually named "djgpp".
1.3. Add a new environment variable DJGPP and update your PATH environment variable. At may be done by adding the following raws to your autoexec.bat file (or, if you use DOSBox, DOSBox configuration file, "#autoexec" section)

 set DJGPP=C:\DJGPP\DJGPP.ENV
 set PATH=C:\DJGPP\BIN;%PATH%
 
 (instead of "C:\DJGPP\" must be the name of directory you unzip files to).

1.4. Reboot DOS (or stop and run your DOSBox)
1.5. Check your djgpp installation
 1.5.1. At any directory run program

  go32-v2

  It showld report how much DPMI memory and swap space can DJGPP use on your system, like this:

  DPMI memory available: 8020 Kb
  DPMI swap space available: 39413 Kb

 1.5.2. Also, at any directory, check version of "gcc" and "gpp"
  
  gcc --version

  will report you something like

   gcc.exe (GCC) 10.3.0
   Copyright (C) 2020 Free Software Foundation, Inc.
   ...
  
  gpp --version

  will report you something like

   gpp.exe (GCC) 10.3.0
   Copyright (C) 2020 Free Software Foundation, Inc.
   ...

1.6. Now you can compile and link C and C++ files.

 Compile

  gcc -c hello_world.c

 Link

  gcc -o hello_world.exe hello_world.o

 You can also run that commands from programs you write (for example, via system() function of C)

1.7. Enjoy

More information you can get on http://www.delorie.com/pub/djgpp/current/v2/readme.1st
   
2. Usage of ForExec class.
 2.1. Methods.
  ForExec::ForExec(char strFilesDir[116]); - creates ForExec object. Passes the name of directory, which will be used by class
  to put self-generated files for formula execution (".c" source files, ".o" object files, binary executable files etc.).
  Please, use BACKSLASHES ONLY for directories separation (not "/").

  void ForExec::setFormula(char expression[128]); - prepares formula, written by user with "C" syntax, to execute. Sign of ";" is     not required. This formula inserts then into code, self-generated by ForExec class, and used as result returned by function,
  which is called then for range of values.

  int execute(double from, double to, double step, double *breakPoints = NULL, double bpq = 0); - executes the formula, which was   set by setFormula(), for the range of values [from; to), including "from", but NOT including "to", with step (the third parameter). If breakpoints are occured in [from; to)   range, please, save them to array and point that array as the 4th parameter. The 5th parameter is quantity of breakpoints. If breakpoints   are occured in range, pointing of the 5th parameter is REQUIRED. Method returns the result of self-generated command execution
  (0 on success and -1 on failure). On failure method shows error message on console. The format of data in the file of     "FE_RES.TXT", generated by execute() method, is the following.

   x_value_1<space>y_value_1<new_line>
   x_value_2<space>y_value_2<new_line>
   ...
   x_value_n<space>y_value_n<new_line>

 2.2. Example of ForExec class usage

  #include <stdio.h>
  #include <conio.h>

  //assume, your current directory is the directory, where you put "FOREXEC" folder with "ForExec" class in the "FOREXEC.HPP" file
  //file with results of formula applying will also appear in your current directory
  #include "./FOREXEC/FOREXEC.HPP"

  int main() {
   clrscr();
   ForExec fe(".\\forexec\\"); //set the directory, in which we want to put self-generated files (BACKSLASHES ONLY)
   fe.setFormula("tan(x)"); //set the formula, results of which you want to use in your project
   double breakPoints[] = {-1.57079633, 1.57079633};
   //set the range of values we want to apply the formula on; set breakpoints occured in the range and its quantity (REQUIRED)
   fe.execute(-1.701696, 1.701696, 0.130800, breakPoints, 2);
   printf("Press any key to exit!\n"); //wait for finishing of ForExec class working and then press any key to exit from main()
   getch();
   return 0;
  }

 2.3. Result of ForExec class usage in 2.2 (content of "FE_RES.TXT" file)

  -1.701696 7.595755
  -1.570896 10032.786601
  -1.440096 -7.607474
  -1.309296 -3.736520
  -1.178496 -2.416939
  -1.047696 -1.734046
  -0.916896 -1.304841
  -0.786096 -1.001397
  -0.655296 -0.768595
  -0.524496 -0.578547
  -0.393696 -0.415382
  -0.262896 -0.269125
  -0.132096 -0.132870
  -0.001296 -0.001296
  0.129504 0.130233
  0.260304 0.266347
  0.391104 0.412346
  0.521904 0.575093
  0.652704 0.764480
  0.783504 0.996219
  0.914304 1.297859
  1.045104 1.723707
  1.175904 2.399316
  1.306704 3.698112
  1.437504 7.457824
  1.568304 401.230662
  1.699104 -7.750950
  