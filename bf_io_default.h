// Copyright 2022 Jon Ripley
// See "LICENSE" file for details.
//
// Default Brainfuck input/output layer implementation.

#ifndef BF_IO_DEFAULT_H_
#define BF_IO_DEFAULT_H_

#include <string>
#include "bf_io.h"

using std::string;

class BrainfuckIODefault: public BrainfuckIO {
 public:
 // Passed to BrainfuckRunner->run(...) to provide output functionality for
 // the "." command.
 virtual bool bf_write(void*, char c) ;

 // Passed to BrainfuckRunner->run(...) to provide input functionality for
 // the "," command.
 virtual char bf_read(void*);
};

#endif  // BF_IO_DEFAULT_H_
