<h1 align="center">Two Pass Assembler</h1>
this project takes a .as file (assembly code file) and than translate it to some files that the computer will be able to understand and run
this is the final project of course 20465 - Systems Programming in C of the open university
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
