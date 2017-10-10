// Macros for SerialUSB debugging Arduino sketches
#ifndef __DEBUGMACROS_H__
#define __DEBUGMACROS_H__

static const char EMPTY[] = ""; 

#define DEBUG 0
#define debug_print(msg, ...) \
  do { if (DEBUG) { SerialUSB.print(__func__); SerialUSB.print("::"); \
    SerialUSB.print(msg, ##__VA_ARGS__); } } while (0)
// prints a short version w/o the function label
#define debug_prints(msg, ...) \
  do { if (DEBUG) SerialUSB.print(msg, ##__VA_ARGS__); } while (0)
#define debug_println(msg, ...) \
  do { if (DEBUG) { SerialUSB.print(__func__); SerialUSB.print("::"); \
    SerialUSB.println(msg, ##__VA_ARGS__); } } while (0)
// prints a short version w/o the function label
#define debug_printlns(msg, ...) \
  do { if (DEBUG) SerialUSB.println(msg, ##__VA_ARGS__); } while (0)

#endif
