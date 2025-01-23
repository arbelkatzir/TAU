#ifndef __ERROR_TYPES__
#define __ERROR_TYPES__

typedef enum {
  OK = 0,
  // parser errors
  ERR_NUM_ARGS,     // 1
  ERR_MISSING_ARG,  // 2
  ERR_UNKNOWN_FLAG, // 3
  ERR_BAD_OP,       // 4
  ERR_BAD_ENC_TYPE, // 5
  // MISC. errors
  ERR_NULL_PTR,     // 6
  ERR_MEMORY,       // 7
  ERR_FILE,         // 8
  ERR_BAD_FUNC_ARG, // 9
} error_types;

#endif // ERROR_TYPES__
