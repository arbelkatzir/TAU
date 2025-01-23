#include <string.h>

#include "parser.h"
#include "error_types.h"
#include <stdio.h>

#define FLAGS_LEN(flags) (sizeof(flags) / sizeof(flag_t))

typedef struct {
    const char* short_name;
    const char* long_name;
    const char* description;
} flag_t;

static const flag_t flags[] = { {HELP_FLAG, "help", "print this description"},
                               {"-p", "operation", "enc/dec/censor"},
                               {"-t", "encryption type", "0/1/2/3"},
                               {"-i", "input", "file path"},
                               {"-o", "output", "file path"},
                               {"-b", "blacklist", "file path"} };

void print_help() {
    printf("Usage:\n");
    for (int i = 0; i < FLAGS_LEN(flags); i++) {
        printf("%*s%*s: %s,\n", 4, flags[i].short_name, 17, flags[i].long_name,
            flags[i].description);
    }
    printf("Please try again.\n");
}

int parse_args(int argc, const char* argv[], command_t* p_cmd) {
    // TODO
    // Initialize command structure
    p_cmd->input_path = NULL;
    p_cmd->output_path = NULL;
    p_cmd->op = OP_NONE;
    p_cmd->enc_type = ENC_TYPE_NONE;  // Default encryption type
    p_cmd->blacklist_path = NULL;

    // Parse arguments
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-i") == 0 && i + 1 < argc) {
            p_cmd->input_path = argv[++i];
        }
        else if (strcmp(argv[i], "-o") == 0 && i + 1 < argc) {
            p_cmd->output_path = argv[++i];
        }
        else if (strcmp(argv[i], "-p") == 0 && i + 1 < argc) {
            const char* operation = argv[++i];
            if (strcmp(operation, "enc") == 0) {
                p_cmd->op = OP_ENC;
            }
            else if (strcmp(operation, "dec") == 0) {
                p_cmd->op = OP_DEC;
            }
            else if (strcmp(operation, "censor") == 0) {
                p_cmd->op = OP_CENSOR;
            }
            else {
                return ERR_BAD_OP;
            }
        }
        else if (strcmp(argv[i], "-t") == 0 && i + 1 < argc) {
            p_cmd->enc_type = atoi(argv[++i]);
            if (p_cmd->enc_type < ENC_TYPE_NONE || p_cmd->enc_type >= ENC_TYPE_LAST) {
                return ERR_BAD_ENC_TYPE;
            }
        }
        else if (strcmp(argv[i], "-b") == 0 && i + 1 < argc) {
            p_cmd->blacklist_path = argv[++i];
        }
        else {
            return ERR_UNKNOWN_FLAG;
        }
    }

    // Validate required arguments
    if (!p_cmd->input_path) {
        return ERR_MISSING_ARG;
    }
    if (!p_cmd->output_path) {
        return ERR_MISSING_ARG;
    }
    if (p_cmd->op == OP_NONE) {
        return ERR_MISSING_ARG;
    }

    // Additional checks for specific operations
    if ((p_cmd->op == OP_ENC || p_cmd->op == OP_DEC) && p_cmd->enc_type == ENC_TYPE_NONE) {
        return ERR_MISSING_ARG;
    }
    if (p_cmd->op == OP_CENSOR && !p_cmd->blacklist_path) {
        return ERR_MISSING_ARG;
    }

    return OK;
}
