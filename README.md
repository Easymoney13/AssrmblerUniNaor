<h1 align="center">Two Pass Assembler</h1>
This project takes a .as file (assembly code file) and than translate it to files the computer will be able to understand and run.
This is the final project of course 20465 - Systems Programming in C of the open university.

## Files Structure
- Assembler files:

    - `assembler.c` - Main program.
   
    - `pre_assembler.c` - check the code validation & make .am file (after macro file).

    - `first_pass.c` - An implementation of first pass algorithm.

    - `line_read.c` - Parse each line and divide it to our field.

    - `second_pass.c` - An implementation of second pass algorithm.

    - `analyze_str.c` - Contain functions about strings.
    
    - `free_code.c` - Free all the allocated memory from the program.
    
    - `helper.c` - File that contain helper function for the program.
    
    - `store.h` - Contain all constants and usful data.
    
    - `FinalCreator.c`- Contain all the final files creation and look for problems.
## Computer and Language Structure

### Computer Structure
Our imaginary computer consists of CPU, Registers and RAM (some of the RAM is utilized as stack).

The CPU has 8 registers (r0-r7). each register size is 12 bits. lsb is 0 and msb is 11.
### Word and Sentence Structure

Each computer instruction consists between 1 to 3 words which are encoded in the following manner:

| 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10 | 11 |
|---|---|---|---|---|---|---|---|---|---|---|---|
|  origin | origin  |  destination | destination  | funct | funct | funct | funct | opcode | opcode | opcode | opcode |

The assembler consists of 16 actions, each of them consists a different funct and opcode (*mov, cmp, add, sub, lea, clr, not, inc, dec, jmp, bne, jsr, red, prn, rts and stop*).
There are 4 kinds of sentences the assembler knows:

1. Empty Sentence - A line contains only whitespaces.

2. Comment Sentence - A line that starts with `;`.

3. Instruction Sentence - Variables assignment and declaration.

4. Command Sentence - Creates an action for the machine to execute upon running the program.

Line maximum length is 80. 
