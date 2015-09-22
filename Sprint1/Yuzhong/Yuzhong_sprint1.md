Yuzhong Huang
SoftSys 2015  
Sprint 1

**hw01** contains **cards.c** which is the card-counting program in Head First C Chapter 1. I change the original program by using several functions to make the code cleaner and better-structured. **hw01** also contains the **hello.c** file used in the first chapter of ThinkOS. The **hello.c** file (from ThinkOS) prints out a simple string and also stores an integer in variable "x". File **hello.s** is the assembly version of **hello.c**, which helps to better understand how to store a value in a low level aspect. File named **2** is the assembly code with optimization of 2 (gcc with option -O2).

**hw02** contains a **stack.c** file provided by Allen Downey with comments that demonstrate what we now know the code is doing. We test and understand the code in a group, so you may see the same file in other member's folder. This implementation of **stack.c** has a function foo() that returns a pointer to an array on the stack that is created and deleted within the scope of that function. The bar() function also creates an array on the stack and fills it with the values 0-4 and then wipes the stack outside the scope of the function. The main() calls foo() and bar() and the printf statements in all three functions show that each time an array is created on the stack, that array occurs at the same address. main() then tries to loop through the returned pointer variable from foo() which produces nonsense since the output of foo() is just a pointer to an array that no longer exists in the stack when main runs.  **stack.c** is the file included in ThinkOS. It helps to understand memory segmentation and how many space do heap need to allocate certain amout od data. The homework for chapter 2.5 **find_track.c**, which ask to implements the pattern-match method in the program. 

**hw03** contains tee.c which writes or append user's std input into several files. In addition, **hw02** contains a folder **GPS exe**, which includes all the exercises in chapter 3 of ead First C. This exercises aim to teach users how to build a small tool as well as using piping in linux.

**hw04** includes

I didn't have a digital version of my answers to questions in ThinkOS, since personally, answering the questions in my head to help me review certain chapters and later discussing with my teammates is more efficient for me.