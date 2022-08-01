// Copyright 2014 Jon Ripley
// See "LICENSE" file for details.
//
// An abstract interface for classes that provide input and output capabilities.

#ifndef BF_IO_H_
#define BF_IO_H_

#include <string>

using std::string;

class BrainfuckIO {
 public:
 // Passed to BrainfuckRunner->run(...) to provide output functionality for
 // the "." command.
 virtual bool bf_write(void*, char c) = 0;

 // Passed to BrainfuckRunner->run(...) to provide input functionality for
 // the "," command.
 virtual char bf_read(void*) = 0;
};

#endif  // BF_IO_H_
