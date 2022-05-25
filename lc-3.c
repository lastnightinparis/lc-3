#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define MEMORY_MAX (1 << 16)
uint16_t memory[MEMORY_MAX]; /*65536 memory cells*/

/*registers*/
/*
 * R0 - R7 general purpose registers
 * PC - program counter
 * COND - flag register
 * */
enum {
    R_R0,
    R_R1,
    R_R2,
    R_R3,
    R_R4,
    R_R5,
    R_R6,
    R_R7,
    R_PC,
    R_COND,
    R_COUNT
};

uint16_t reg[R_COUNT];

/* opcodes */
enum {
    OP_BR,  /* branch */
    OP_ADD, /* add */
    OP_LD,  /* load */
    OP_ST,  /* store */
    OP_JSR, /* jump register */
    OP_AND, /* bitwise and */
    OP_LDR, /* load register */
    OP_STR, /* store register */
    OP_RTI, /* unused */
    OP_NOT, /* bitwise not */
    OP_LDI, /* load indirect */
    OP_STI, /* store indirect */
    OP_JMP, /* jump */
    OP_RES, /* reserved */
    OP_LEA, /* load effective address */
    OP_TRAP, /* execute trap*/
};
/* condition flags */
enum {
    FL_POS = 1 << 0, /* P */
    FL_ZRO = 1 << 1, /* Z */
    FL_NEG = 1 << 2, /* N */
};

enum {
    MR_KBSR = 0xFE00, /* keyboard status */
    MR_KBDR = 0xFE02  /* keyboard data */
};

uint16_t mem_read(uint16_t addr) {
    if (addr == MR_KBSR) {
        if (check_key()) {
            memory[MR_KBSR] = (1 << 15);
            memory[MR_KBDR] = getchar();
        } else {
            memory[MR_KBSR] = 0;
        }
    }
    return memory[addr];
}

void read_image_file(FILE *file) {

}

int read_image(const char *path) {
    FILE *file = fopen(path, "rb");
    if (!file) return 0;
    read_image_file(file);
    fclose(file);
    return 1;
}

int main(int argc, const char *argv[]) {
    /* load arguments */
    if (argc < 2) {
        printf("lc3 [image] ... \n");
        exit(2);
    }

    for (int i = 1; i < argc; i++) {
        if (!read_image(argv[i])) {
            printf("failed to load image: %s\n", argv[i]);
        }
    }


    /* setup */

    reg[R_COND] = FL_ZRO;

    enum {
        PC_START = 0x3000
    };

    reg[R_PC] = PC_START;
    int running = 1;

    while (running) {
        uint16_t instr = mem_read(reg[R_PC]++);
        uint16_t op = instr >> 12;

        switch (op) {
            case OP_ADD:
                break;
            case OP_AND:
                break;
            case OP_NOT:
                break;
            case OP_BR:
                break;
            case OP_JMP:
                break;
            case OP_JSR:
                break;
            case OP_LD:
                break;
            case OP_LDI:
                break;
            case OP_LDR:
                break;
            case OP_LEA:
                break;
            case OP_ST:
                break;
            case OP_STI:
                break;
            case OP_STR:
                break;
            case OP_TRAP:
                break;
            case OP_RES:
                break;
            case OP_RTI:
                break;
            default:
                /* bad opcode */
                break;
        }
    }

    return 0;
}
