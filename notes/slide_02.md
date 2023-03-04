# 02

## textbook knowledge

1. Analog signal

   - vary in a smooth way over time

   - analog data are continuously valued

   - example: audio and video:

     ![](/Users/wangkaize/Desktop/CSC3050/notes/src/图片1.png)

2. Digital signal

   - maintains a constant level then changes into another constant level (generally operate in one of two states)

   - digital data are discretely valued

   - example: computer data:

     ![](/Users/wangkaize/Desktop/CSC3050/notes/src/图片2.png)

3. Radix or Base:

   - An orderd set of symbols, called digits, with relations defined for addition, subtraction, multiplication and division
   - Radix or Base of the number system is the total number digits allowed in the number system

4. true form; inverse form; 2's complement

5. Digital circuits generally contain two parts:

   - combinational logic
   - sequential logic

   1. **Combinational circuits**: consists of logic gates with inputs and outputs

      The outputs at any instance of time depend only on the combination of input values based on logic operations such as AND, OR, etc.

   2. **Sequential circuits**: in addition to inputs and outputs, there are also storage elements. Therefore outputs depend on both current inputs and stored values

6. Digital signal representation

   - Active high
   - Active low

7. Logic Gates:

   ![](/Users/wangkaize/Desktop/CSC3050/notes/src/图片3.png)

8. **Truth table**

9. Combinational Circuits: 

   In combinational circuits, the output at any time is a direct function of the applied external inputs.

   ![](/Users/wangkaize/Desktop/CSC3050/notes/src/图片4.png)

10. propagation delay:

    - The delay when the signal arrives at the input of a circuit, and when the output of the circuit changes, is called the propagation delay.
    - A circuit is considered to be fast, if its propagation delay is small (ideally as close to 0 as possible).

11. Timing digram: 

    - The input to a circuit can be changed over time.
    - The timing diagram shows the values of input signals to a circuit with the passage of time, in the form of a waveform.
    - It also shows a waveform for the output

    ![](/Users/wangkaize/Desktop/CSC3050/notes/src/图片5.png)

12. Fan-in:

    - Fan-in of a gate is the number of inputs to the gate.
    - There is **a limitation** on the fan-in for any gate.
    - In CMOS IC technology, higher fan-in implies slower gates (higher propagation delays).

13. Fan-out:

    - Fan-out is the number of gates that can be driven by a driver gate.
    - The driven gate is called the load gate.
    - There is **a limit** to the number of load gates that can be driven by a driver gate.

14. Buffers: 

    - Buffers have a single input and a single output, where **output = input**.
    - Buffers help increase the **driving capability** of a circuit by increasing the fan-out.
    - **Drive Strength**: how much load a gate can drive
    - Greater drive strength, load gates are (dis)charged more quickly.

    ![](/Users/wangkaize/Desktop/CSC3050/notes/src/图片6.png)

15. Decoder:

    - The most common type of decoder has an $n$-bit input and $2^n$ outputs, where only one output is **asserted** for each input conbination. 

    - Since this decoder translates the $n$-bit input into a signal that corresponds to the binary value of the $n$-bit input, the decoder is also called a **minterm generator**.

    - **minterm (product term)**: product that includes all input variables 

      $A \bar{B} C,\ A\bar{B}\bar{C}$ are two minterms in a 3-to-8 decoder whose in put is $A,B$ and $C$.

16. Multiplexor: data selector, which needs $\lceil \log_2 n\rceil$ selector value when there are n inputs.

17. 



## Why do computers use 2's complement code to store value?

Each binary code corresponds to a unique value, where the mapping can ensure that summator can do both addition and subtraction.

| Decimal                    | True Form | Inverse Form | 2's Complement            |
| -------------------------- | --------- | ------------ | ------------------------- |
| 127                        | 0111 1111 | 0111 1111    | 0111 1111                 |
| ...                        | ...       | ...          | ...                       |
| 1                          | 0000 0001 | 0000 0001    | 0000 0001                 |
| 0                          | 0000 0000 | 0000 0000    | 0000 0000                 |
| -0 (not exist in computer) | 1000 0000 | 1111 1111    | 1000 0000 (1111 1111 + 1) |
| -1                         | 1000 0001 | 1111 1110    | 1111 1111                 |
| -2                         | 1000 0010 | 1111 1101    | 1111 1110                 |
| -3                         | 1000 0011 | 1111 1100    | 1111 1101                 |
| ...                        | ...       | ...          | ...                       |
| -126                       | 1111 1110 | 1000 0001    | 1000 0010                 |
| -127                       | 1111 1111 | 1000 0000    | 1000 0001                 |

From above, there is a number `-0` which is redundant in practice. In which form it can be used optimally in computer design?

The answer is that the mapping can ensure that summator can do both addition and subtraction.

See example:

Do the subtraction $1+(-1) = 0$ :

1. True form: $(0000\ 0001)_2+(1000\ 0001)_2=(1000\ 0010)_2=(-2)_{10}$

2. Inverse form: $(0000\ 0001)_2+(1111 1110)_2=(1111 1111)_2=(-0)_2$ 

   Although -0 and 0 is interprete as the same in real life, the existence of -0 violate the rule that each binary representation corresponds to a unique decimal representation, causing the waste of space and conflicts somtimes.

3. 2's complment: $(0000\ 0001)_2 + (1111\ 1111)_2=(0000\ 0000)_2=0_{10}$

Thus 2's complement is the best because it enable that summator can also do subtraction.





