Zoher Ghadyali  
Think OS Chapter 5  
Reading Questions

**1) Suppose you have the value 128 stored as an unsigned 8-bit number.  What happens if you convert it to a 16-bit number and accidentally apply sign extension?**

The value 128 stored as an unsigned 8-bit number is 10000000. The fact that is unsigned means that it will only ever be treated as a positive number. If it was signed, then the first bit would be used to indicate sign, 1 if negative and 0 if positive. If you take 10000000 and convert it to a 16-bit number and accidentally apply sign extension, that gives you 1111111110000000. Since the number is unsigned, that means you are representing a positive number which in base 10 is 65,408.

**2) Write a C expression that computes the two's complement of 12 using the XOR bitwise operator.  Try it out and confirm that the result is interpreted as -12.**

The C expression that I have written is contained in the file **ThinkOS_Ch5_Q2.c**. Currently, this file prints out the value 244 which is -12 in 2's complement.

**3) Can you guess why IEEE floating-point uses biased integers to represent the exponent rather than a sign bit or two's complement?**

I think IEEE floating-point uses biased integers to represent the exponent rather than a sign bit because you need to be able to store both negative and positive exponents (to represent very small and very large numbers) and a small negative exponent in 2's complement (ex. -12) could be easily interpreted as a very large positive exponent (ex. 244). If the programmer accidentally stores their exponent as an unsigned variable, the compiler will interpret the exponent vastly differently from what the programmer expects. If you use a sign bit, you decrease the maximum value an exponent can take on.

**4) Following the example in Section 5.4, write the 32-bit binary representation of -13 in single precision IEEE floating-point.  What would you get if you accidentally interpreted this value as an integer?**

We write the 32-bit binary representation of -13 as 1 | 10000010 | 01010000000000000000000.  
The lines indicate that this representation contains the sign | exponent + 127 | coefficient.  
If we accidentally interpret this value as an integer, we would read the value as 3,240,624,128.

**5) Write a function that takes a string and converts from lower-case to upper-case by flipping the sixth bit.  As a challenge, you can make a faster version by reading the string 32 or 64 bits at a time, rather than one character at a time.  This optimization is made easier if the length of the string is a multiple of 4 or 8 bytes.**

The function that I have written is contained in the file **ThinkOS_Ch5_Q5.c**. Currently, this file takes in a string of maximum length 10 and converts all lower-case letters to upper-case by flipping the sixth bit. This implementation currently does this process a character at a time as opposed to reading the string.
