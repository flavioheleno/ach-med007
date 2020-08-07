# ACH-MED007

This is an old university project that aims to create a sub-set of z80's instruction set.

The code is quite old and should still work, use it at your own risk.

## Opcodes

Num | OPCODE     | PAGE | CYCLES
----|------------|------|-------
01  | ADD A, n   | 142  | 2
02  | BIT b, r   | 224  | 2
03  | CALL nn    | 255  | 5
04  | CCF        | 170  | 1
05  | CPL        | 168  | 1
06  | DAA*       | 166  | 1
07  | DEC ss     | 187  | 1
08  | DJNZ e     | 253  | 2/3
09  | INC ss     | 184  | 1
10  | JP nn      | 238  | 3
11  | JR C, e    | 242  | 3
12  | JR NC, e   | 244  | 3
13  | JR Z, e    | 246  | 2/3
14  | JR NZ, e   | 248  | 2/3
15  | LD (nn), A | 97   | 4
16  | LD r, n    | 82   | 2
17  | LD A, (nn) | 94   | 4
18  | NEG        | 169  | 2
19  | PUSH qq    | 116  | 3
20  | POP qq     | 119  | 3
21  | RET        | 260  | 3
22  | RLA        | 191  | 1
23  | RRA        | 193  | 1
24  | SCF        | 171  | 1
25  | SET b, r   | 232  | 2

## License

This project is licensed under the [MIT License](LICENSE).
