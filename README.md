<h1 align="center">Two Pass Assembler</h1>
this project takes a .as file (assembly code file) and than translate it to some files that the computer will be able to understand and run
this is the final project of course 20465 - Systems Programming in C of the open university
## Files Structure
- Assembler files:

    - `assembler.c` - Main program.
   
    - `pre_assembler.c` - check the code validation & make .am file (after macro file)

    - `first_pass.c` - An implementation of first pass algorithm.

    - `line_read.c` - parse each line and divide it to our field.

    - `second_pass.c` - An implementation of second pass algorithm.

    - `errors.c` - A thorough check of errors during first and second pass.
    
    - `output.c` - Creates *.ext*, *.ent* and *.ob* output files.
