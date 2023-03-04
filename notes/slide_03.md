# ppt

1. The words of a computer's language are called **instructions**, and its vocabulary is called an **instruction set**.

2. Two Key Principles of Machine Design:

   1. Instructions are represented as (binary) numbers and, as such, are indistinguishable from data.
   2. Programs are stored in alterable memory (that can be read from or written to) just like data.

   Stored program:

   - binary-code compatibility: Programs can be shipped as files of binary numbers
   - Computers can inherit ready-made software provided they are compatible with an existing **ISA**, which leads the industry to align around a small number of **ISA**s.

3. **C**omplex **I**nstruction **S**et **C**omputer (CISC): 

   - Implement complex instruction directly by hardware
   - lots of instructions of variable size, very memory optimal and typically less registers
   - example: intel x86

4. **R**educed **I**nstruction **S**et **C**omputer (RISC):

   - instructions, all of fixed size, more registers, optimized for speed
   - usually called a "Load/Store" architecture
   - examples: MIPS, Sun SPARC, HP PA-RISC, IBM PowerPC

5. RISC Philosophy:

   - fixed instruction length
   - load-store instruction set
   - limited number of addressing modes
   - limited number of operations

6. Instruction sets are measured by how well compilers use them as opposed to how well assembly language programmers use them.

7. Instruction Categories:

   - Load/Store
   - Computational
   - Jump and branch
   - Floating point
   - Memory management
   - Special

8. 3 instruction formats: all **32-bit** wide

   ![](/Users/wangkaize/Desktop/CSC3050/notes/src/图片7.png)

   - op (6-bit): opcode that specifies the operation

   - rs (5-bit): the first register source operand
   - rt (5-bit): the second register source operand
   - rd (5-bit): the register destination operand
   - shamt (5-bit): shift amount
   - funct (6-bit): function code that selects specific variant of the operation

9. MIPS register:

   - holds 32 32-bit registers
   - one write port
   - two read port

10. Register are

    1. Faster than the main memory

       - but register with more locations are slower
       - increase on read/write port impacts speed quadratically

    2. Easier for a complier to use

    3. can hold variables

       - So that code density improve (Since register are named with fewer bits than a memory location)

    4. MIPS Register convention:

       | Name        | Register number | Usage                           | Preserved on call? |
       | ----------- | --------------- | ------------------------------- | ------------------ |
       | `$zero`     | 0               | constant value 0                | N/A                |
       | `$at`       | 1               | (**Reserved for an Assembler**) | No                 |
       | `$v0`-`$v1` | 2-3             | Returned values                 | No                 |
       | `$a0`-`$a3` | 4-7             | Arguments                       | No                 |
       | `$t0`-`$t7` | 8-15            | Temporaries                     | No                 |
       | `$s0`-`$s7` | 16-23           | Saved values                    | Yes                |
       | `$t8`-`$t9` | 24-25           | Temporaries                     | No                 |
       | `$k0`-`$k1` | 26-27           | (**Reserved for OS**)           | No                 |
       | `$gp`       | 28              | Global Pointer                  | Yes                |
       | `$sp`       | 29              | Stack Pointer                   | Yes                |
       | `fp`        | 30              | Frame Pointer                   | Yes                |
       | `$ra`       | 31              | Return address                  | Yes                |

       Preserve on call:

       - If some value is stored in that register before the procedure is called, then you may not make the assumption that the same value will be in the register at the return from the procedure. “Preserved across procedure calls” means that **the value stored in the register will not be changed by a procedure**.

    5. Arithmetic operations (using MIPS Registers)

       1. Addition

          ```assembly
          add $1,$2,$3 		# $1 gets $2+$3
          addi $1,$2,100 	# $1 gets $2+100
          addu $1,$2,$3		# $1 gets $2+$3 and all values are treated as unsigned integers, not 2's complement
          addiu $1,$2,100	# $1 gets $2+100 and all values are treated as unsigned integers, not 2's complement
          ```

       2. Subtraction

          ```assembly
          sub $1,$2,$3 		# $1 gets $2-$3
          subu $1,$2,$3		# $1 gets $2-$3 and all values are treated as unsigned integers, not 2's complement
          ```

       3. Multiplication

          ```assembly
          mul $1,$2,$3		# $1 gets $2*$3 (without overflow, which means the result is only 32-bit)
          mult $2,$3			# $hi,$lo = $2*$3 
          								# Upper 32 bits stored in special register $hi
          								# Lower 32 bits stored in special register $lo
          ```

       4. Division

          ```assembly
          div $2,$3				# Remainder stored in special register $hi
          								# Quotient stored in special register $lo            
          ```

       5. `hi` and `lo` are special registers used to store the result of multiplication and division. They are separate from the `$0 .. $31` general purpose registers, not directly addressable. Their contents are accessed with special instructions `mfhi` and `mflo` (Move From HI/LO).

    6. Register operands

       1. Arithmetic instructions use register operands (as above)
       2. MIPS has 32 × 32-bit registers
       3. Assembler names (convention above)

    7. Memory operands

       1. Main memory used for composite data
          - Arrays, structures, dynamic data
       2. To apply arithmetic operations
          - Load values from memory into registers
          - Store result from register to memory
       3. Memory is byte addressed
          - Each address identifies an 8-bit byte
       4. Words are aligned in memory
          - Address must be a multiple of 4
       5. MIPS is **Big Endian**
       6. `lw `, `li`, `la`, `sw`, `syscall`: https://www.youtube.com/watch?v=5AN4Fo0GiBI

    8. Big/Small Endian:

       1. big: The leftmost byte stores at the starting address of a word
       2. small: The rightmost byte stores at the starting address of a word

       ![](/Users/wangkaize/Desktop/CSC3050/notes/src/图片8.png)

    9. Immediate operands: `addi`

       - remember that no immediate subtraction exists (if necessary, use negative constant in `addi`)

    10.  `lw rd offset(rs)`: offset take a word for 32 bytes by default?

    11. Hardware design principle:

        1. Simplicity favors regularity
           - Regularity makes implementation simpler
           - Simplicity enables higher performance at lower cost
        2. Smaller is faster
           - main memory: millions of locations
           - register: less location leads to higher speed
        3. Make the common case fast
           - Small constants are common
           - Immediate operand avoids a load instruction
        4. Good design demands good compromises
           - Different formats complicate decoding, but allow 32-bit instructions uniformly
           - Keep formats as similar as possible

11. translate **C** into **MIPS**:

    C:

    ```C
    A[300] = h + A[300]; // h in $s2, base address of A in $t1
    ```

    To MIPS:

    ```assembly
    lw $t0,1200($t1)
    add $t0,$s2,$t0
    sw $t0,1200($t1)
    ```

    Translate into decimal machine code: http://en.wikibooks.org/wiki/MIPS_Assembly/Instruction_Formats#Opcodes

    | op   | rs   | rt   | address |
    | ---- | ---- | ---- | ------- |
    | 35   | 9    | 8    | 1200    |

    | op   | rs   | rt   | rd   | shamt | funct |
    | ---- | ---- | ---- | ---- | ----- | ----- |
    | 0    | 18   | 8    | 8    | 0     | 12    |

    | op   | rs   | rt   | address |
    | ---- | ---- | ---- | ------- |
    | 43   | 9    | 8    | 1200    |

    Translate into binary machine code (omitted)

12. logic operation:

    ![](/Users/wangkaize/Desktop/CSC3050/notes/src/截屏2023-02-23 22.29.26.png)

    - `sll`: sll by $i$ bits equals multiplication by $2^i$
    - `srl`: srl by $i$ bits equals division by $2^i$ **(for unsigned numbers)**

13. step 2 & 3 are required because each unit of index is 4 byte

    ![](/Users/wangkaize/Desktop/CSC3050/notes/src/截屏2023-02-23 22.42.03.png)

14. control operation: **Branch** to a labeled instruction if a condition is true

    1. ```assembly
       beq rs, rt, L1 	# if (rs == rt) branch to instruction labeled L1
       ```

    2. ```assembly
       bne rs, rt, L1 	# if (rs != rt) branch to instruction labeled L1
       ```

    3. ```assembly
       j L1 						# unconditional jump to instruction labeled L1
       ```

15. 

# offset take a word for 32 bytes by default?

