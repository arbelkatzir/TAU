
#include <string.h> // check if ok



#include "error_types.h"
#include "parser.h"
// TODO - add you includes here

static int process_operation(command_t cmd) {
    // TODO:
    // Assuming cmd is OK, no need to validate members as they are beeing
    // validated inside parse args & within each processed operation.

    // TODO: process command according to operation
    int err;

    if (cmd.op == OP_ENC) {
        return encrypt_file(cmd.input_path, cmd.output_path, cmd.enc_type);
    }
    if (cmd.op == OP_DEC) {
        return decrypt_file(cmd.input_path, cmd.output_path, cmd.enc_type);
    }
    else if (cmd.op == OP_CENSOR) {
        return censor_and_encrypt(cmd.input_path, cmd.output_path, cmd.enc_type, cmd.blacklist_path);
    }
    return OK;
}

int main(int argc, const char* argv[]) {

    // TODO: check if need to print help (no args or 1 arg and its help) and print it.

    // TODO: call parse arguments of parser

    // TODO: run command - call process operation
    if (argc < 2) {
        return ERR_NUM_ARGS;
    }
    // Ensure minimum required arguments are provided
    if (argc < 6 || argc > 8) {
        return ERR_NUM_ARGS;
    }

    // TODO: check if need to print help (no args or 1 arg and its help) and print it.
    if (argc == 2 && strcmp(argv[1], "-h") == 0) {
        print_help();
        return OK;
    }

    // TODO: call parse arguments of parser
    command_t cmd;  // Define a command structure (you must implement this in parser.h)
    int err = parse_args(argc, argv, &cmd);  // Pass cmd to parse_args
    if (err != OK) {
        return err;
    }

    // TODO: run command - call process operation
    err = process_operation(cmd);
    if (err != OK) {
        return err;
    }
    return 0;
}
