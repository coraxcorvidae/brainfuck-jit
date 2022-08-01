// Copyright 2014 Jon Ripley
// See "LICENSE" file for details.
//
// Frame limmited Brainfuck input/output layer implementation.

#ifndef BF_IO_GAME_H_
#define BF_IO_GAME_H_

#include "bf_io.h"

using std::string;

class BrainfuckIOGame : public BrainfuckIO
{
public:
    BrainfuckIOGame();

    virtual void init(int fps, bool log);

    // Passed to BrainfuckRunner->run(...) to provide output functionality for
    // the "." command.
    virtual bool bf_write(void *, char c);

    // Passed to BrainfuckRunner->run(...) to provide input functionality for
    // the "," command.
    virtual char bf_read(void *);

    long frame_limit;
    bool frame_log;
};

#endif // BF_IO_GAME_H_
