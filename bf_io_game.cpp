// Copyright 2014 Jon Ripley
// See "LICENSE" file for details.

#include <string>
#include <unistd.h>

#include "bf_io_game.h"

BrainfuckIOGame::BrainfuckIOGame() {}

void BrainfuckIOGame::init(int fps, bool log) {
    frame_limit = (1.0 / fps) * 1000000;
    frame_log = log;
}

// Passed to BrainfuckRunner->run(...) to provide output functionality for
// the "." command when --fps limiter specified.
bool BrainfuckIOGame::bf_write(void *, char c) {
  static int frame_count = 0;
  static int p = 0;
  static clock_t time = clock();
  static double delta;
  static double lag = 0.0;

  // State machine to look for ANSI Escape Codes on the output stream
  switch (c) {
    // Start ANSI Escape Code
    case 0x1b:
      p = 1;
      break;
    
    // cont...
    case '[':
      if (p == 1) {
        p = 2;
      }
      break;
    
    // Found (esc)(lsb)H or (esc)(lsb)f
    case 'H': case 'f':
      if (p != 2) {
          p = 0;
          break;
      } 
      p = 3;
      break;

    default:
      p = 0;
      break;
  }

  // Found cursor home. Sleep until frame timer elapses and log to stderr if
  // --fps-log option specified.
  if (p == 3) {
    frame_count++;
    delta = difftime(clock(), time);
    if (delta < frame_limit) {
      usleep(frame_limit - delta);
    } else {
      lag += delta-frame_limit;
    }
    time = clock();
    p = 0;
    if (frame_log) {
      fprintf(stderr,"Frame %d Delta %ld Limit %ld Lag %d\n", frame_count, (long)delta, frame_limit, (int)lag);
    }
  }

  return putchar(c) != EOF;
}

char BrainfuckIOGame::bf_read(void *) {
    int c = getchar();
    if (c == EOF) {
        return 0; 
    } else {
        return c;
    }
}