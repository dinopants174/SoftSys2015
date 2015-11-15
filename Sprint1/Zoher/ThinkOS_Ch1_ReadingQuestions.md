Zoher Ghadyali  
Think OS Chapter 1  
Reading Questions

**1) Give an example of a feature common in interpreted languages that is rare in compiled languages.**

A feature common in interpreted languages that is rare in compiled languages is the ability to put break points in your code since the interpreter executes each line of code sequentially, the user can run the code to a break point.

**2) Name two advantages of static typing over dynamic typing.**

Two advantages of static typing is that the program runs faster at run time since the compiler has already checked if the types are correct and that these checks done by the compiler happen when the program is compiled so they happen in parts of the prgoram that might not have run yet.

**3) Give an example of a static semantic error.**

A static semantic error is a logical error. An example would be a type mismatch, if the type on the LHS of an assignment did not match the type on the RHS of the assignment or trying to use a floating point numner as an index to an array.

**4) What are two reasons you might want to turn off code optimization?**

Two reasosn that you might want to turn off code optimiziation are when developing new code because optimization may make bugs appear or disappear and when writing tests for your code because optimization may affect things used in your tests.

**5) When you run gcc with -S, why might the results look different on different computers?**

The results might look different on different computers because gcc is producing assembly code and assembly is specific to a particular computer architecture.

**6) If you spell a variable name wrong, or if you spell a function name wrong, the error messages you get might look very different.  Why?**

You get very different looking errors because the erorrs come up at different times in the compilation process. Spelling a variable name wrong will probably come up in the parsing stage of compilation whereas spelling a function name wrong might only be caught once the compiler gets to the linking stage.

**7) What is a segmentation fault?**

A segmentation fault is when you try to read or write to an incorrect location in memory.