Zoher Ghadyali  
Think OS Chapter 3  
Reading Questions

**1) The Georgian alphabet has 33 letters.  How many bit are needed to specify a letter.**

You need 6 bits to specify 33 letters since 2^6 > 33.

**2) In the UTF-16 character encoding, the binary representation of a character can take up to 32 bits.  Ignoring the details of the encoding scheme, how many different characters can be represented?**

You could represent 2^32 characters.

**3) What is the difference between "memory" and "storage" as defined in Think OS?**

As defined in ThinkOS, "memory" is some kind of random-access memory (RAM) which is where our entire memory diagram resides. "storage" is used for HDDs and SSDs that store files the program reads or writes to.

**4) What is the difference between a GiB and a GB?  What is the percentage difference in their sizes?**

A GiB is a gigibyte which is 2^30 bytes.  
A GB is a gigabyte which is 10^9 bytes.  
A GiB is 7.04% larger than a GB.

**5) How does the virtual memory system help isolate processes from each other?**

The virtual memory system helps isolate processes from each other because the hardware maps the virtual addresses the program generates to physical addresses on a per-process basis so even if two processes generate the same virtual addresses, they map to different physical addresses.

**6) Why do you think the stack and the heap are usually located at opposite ends of the address space?**

The stack and heap are located at opposite ends of the address probably because it is easier and there is less room for error for the stack to grow downward and the heap to grow upward than if the stack and heap started at the same place so the program is allocating memory and also dynamically altering the memory, there is a higher chance that the program accidentally alters allocated memory.

**7) What Python data structure would you use to represent a sparse array?**

You could use a list in Python for a sparse array or a list of lists to represent an array but there are several options in packages like scipy and pandas to represent sparse arrays.

**8) What is a context switch?**

A context switch is the mechanism by which the operating system can interrupt a running process, save its state, and then run another process.

--------------------------------------------------

**1) Add a second call to malloc and check whether the heap on your system grows up (toward larger addresses).  
2) Add a function that prints the address of a local variable, and check whether the stack grows down.  
3) Choose a random number between 1 and 32, and allocate two chunks with that size.  How much space is there between them?  Hint: Google knows how to subtract hexadecimal numbers.**

The output of my version of aspace.c looks like this:

-----------------------  
Address of main is 0x                    10bd71c80  
Address of global is 0x                  10bd72020  
-----------------------  
Address of local is 0x                   7fff53e8e9f8  
Address of another local variable is 0x  7fff53e8e97c  
The stack has grown down  
-----------------------
Address of heap1 is 0x                   7fc832404bc0  
Address of heap2 is 0x                   7fc832404c40  
The heap has grown up  
-----------------------  
Address of rando1 is 0x                  7fc832404cc0  
Address of rando2 is 0x                  7fc832404cd0  
The difference between them is 16 which is the size allocated per rando  

where heap1 and heap2 are the pointer variables that called malloc and show that the heap has grown upward, where local and another local variable are in the stack and show that the stack has grown upward, and where the randos are have been allocated 16 bytes using malloc and where the difference between their addresses was found to be 16 bytes.

When we tested aspace.c with different malloc values like 20, we found the difference between them was 32 and this may have to do with the length of the word that malloc allocates when we call it.





