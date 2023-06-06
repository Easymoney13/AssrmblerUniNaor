.entry LOOP 
.entry LENGTH 
.extern 3L 
.extern W 
.extern LENGTH
3MAIN: mov S1.1, W 
 add r8,STR
LOOP: jmp W 
 prn #-5 
 sub r1, r4 
 inc K,"as" 
 ;this is comment
movy S1.2, r3 
 bne L3 
END: hlt 4
STR: .string abcdef" 
LENGTH: .data 6,-,15 
K: .data 22 
S1: .struct 8, "ab" 