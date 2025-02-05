#ifndef LINKABLE_HPP
#define LINKABLE_HPP

class Linkable {
 protected:
  virtual int callCompiler() = 0;
  virtual int callLinker() = 0;
};

#endif
