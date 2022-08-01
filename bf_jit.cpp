// Copyright 2014 Brian Quinlan
// See "LICENSE" file for details.

#include <cstdint>
#include <stack>

#include "bf_jit.h"

using std::stack;

// The total number of times that a loop condition (e.g. "[") must be evaluated
// before the loop is compiled.
const int kLoopCompilationThreshold = 20;

BrainfuckJIT::BrainfuckJIT() {}

bool BrainfuckJIT::init(string::const_iterator start,
                        string::const_iterator end) {
  start_ = start;
  end_ = end;

  // Build the mapping from the position of the start of a block (i.e. "]") to
  // a Loop struct.
  stack<string::const_iterator> block_starts;
  for (string::const_iterator it = start; it != end; ++it) {
    if (*it == '[') {
      block_starts.push(it);
    } else if (*it == ']') {
      if (block_starts.size() != 0) {
        const string::const_iterator &loop_start = block_starts.top();
        loop_start_to_loop_[loop_start] = Loop(it+1);
        block_starts.pop();
      }
    }
  }

  if (block_starts.size() != 0) {
    fprintf(
        stderr,
        "Unable to find loop end in block starting with: %s\n",
        string(block_starts.top(), end).c_str());
    return false;
  }
  return true;
}

void* BrainfuckJIT::run(BrainfuckIO* io_layer,
                    void* reader_arg,
                    void* writer_arg,
                    void* memory) {
  uint8_t* byte_memory = reinterpret_cast<uint8_t *>(memory);
  // When processing a "[", push the position of that command onto a stack so
  // that we can quickly return to the start of the block when then "]" is
  // interpreted.
  stack<string::const_iterator> return_stack;

  for (string::const_iterator it = start_; it != end_;) {
    switch (*it) {
      case '<':
        --byte_memory;
         ++it;
        break;
      case '>':
        ++byte_memory;
         ++it;
        break;
      case '-':
        *byte_memory -= 1;
         ++it;
        break;
      case '+':
        *byte_memory += 1;
         ++it;
        break;
      case ',':
        *byte_memory = io_layer->bf_read(reader_arg);
         ++it;
        break;
      case '.':
        io_layer->bf_write(writer_arg, *byte_memory);
         ++it;
        break;
      case '[':
        {
          Loop &loop = loop_start_to_loop_[it];

          if (loop.compiled == nullptr &&
              loop.condition_evaluation_count > kLoopCompilationThreshold) {
            shared_ptr<BrainfuckCompileAndGo> compiled(
              new BrainfuckCompileAndGo());
            string::const_iterator compilation_end(loop.after_end);

            if (!compiled->init(it, compilation_end)) {
              fprintf(stderr,
                      "Unable to compile code: %s\n",
                      string(it, compilation_end).c_str());
            } else {
              loop.compiled = compiled;
            }
          }

          if (loop.compiled) {
            byte_memory = reinterpret_cast<uint8_t *>(
                loop.compiled->run(io_layer,
                                   reader_arg,
                                   writer_arg,
                                   byte_memory));
            it = loop_start_to_loop_[it].after_end;
          } else {
            ++loop.condition_evaluation_count;
            if (*byte_memory) {
              return_stack.push(it);
              ++it;
            } else {
              it = loop_start_to_loop_[it].after_end;
            }
          }
        }
        break;
      case ']':
        if (return_stack.size() != 0) {
          it = return_stack.top();
          return_stack.pop();
        } else {
          ++it;
        }
        break;
      default:
        ++it;
        break;
    }
  }
  return byte_memory;
}
