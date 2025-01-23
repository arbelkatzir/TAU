#ifndef __PARSER_H__
#define __PARSER_H__

#include "algs.h" // for encrypt_t in the command_t struct

// defines & typedefs

#define HELP_FLAG "-h"

typedef enum {
  OP_NONE = 0,

  OP_ENC,
  OP_DEC,
  OP_CENSOR,

  OP_LAST,
} op_t;

typedef struct {
  op_t op;
  encrypt_t enc_type;
  const char *input_path;
  const char *output_path;
  const char *blacklist_path;
} command_t;

// functions

// parsing arguments main function
int parse_args(int argc, const char *argv[], command_t *p_cmd);

// print help to screen
void print_help();

#endif //__PARSER_H__
