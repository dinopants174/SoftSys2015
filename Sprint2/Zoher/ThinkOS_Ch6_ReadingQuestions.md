Zoher Ghadyali  
Think OS Chapter 6  
Reading Questions

**1) Which memory management functions would you expect to take constant time?  Which ones take time proportional to the size of the allocated chunk?**

I would expect _free_ to take a constant amount of time since all it has to do is change the state in the boundary tags of the chunk to free instead of allocated. I would expect _realloc_ to take a constant amount of time if the new size is smaller than the old size because all it might have to do is take the old chunk, cut it down to the new size (without modifying the contents), and then change the boundary tags for where the chunk is allocated and where the chunk is free (which might be an example of fragmentation).

I would expect _calloc_ and _malloc_ to take time proportional to the size of the allocated chunk because _calloc_ has to clear the entire chunk and _malloc_ has to make sure it can allocate the chunk to the size specified by its input.

**2) For each of the following memory errors, give an example of something that might go wrong:**

**a) Reading from unallocated memory.**  

Reading from unallocated memory might give you a segmentation fault or it will just read whatever is stored in the unallocated memory and then continues running the program, which would give you unexpected results.

**b) Writing to unallocated memory.**  

Writing to unallocated memory might mean that you write a value to the stack that you then overwrite and that means when you try and access that value which you thought you wrote to allocated memory, you no longer have the value you expect.

**c) Reading from a freed chunk.**  

Reading from a freed chunk might still give you the value that was in the chunk when it was deallocated or the value might have changed since now the memory is deallocated so it can contain values from the stack.

**d) Writing to a freed chunk.**  

Writing to a freed chunk might result in temporarily writing that value to the stack but because the memory is unallocated, it could be modified and that would again give you values you don't expect in memory.

**e) Failing to free a chunk that is no longer needed.**

Failing to free a chunk that is no longer needed results in memory leakage which means a process just keeps taking up more and more memory and could eventually result in an error when a call to _malloc_ fails because you have reached the total amount of memory a process can have or if you run out of virtual addresses.

**3) Run _ps aux --sort rss_ to see a list of processes sorted by RSS, which is "resident set size", the amount of physical memory a process has.  Which processes are using the most memory?**

The processes that are taking up the most memory on my computer are Google Chrome and Spotify which makes sense since Spotify is streaming the music I listen to and Chrome is leaking memory.

**4) What's wrong with allocating a large number of small chunks?  What can you do to mitigate the problem?**

The problem with allocating a large number of small chunks is that each small chunk has overhead which is the space necessary for _malloc_ to know which chunks are free, which are allocated, and their size. Each small chunk requires boundary tags and free list pointers which take up space and are not used efficiently with a large number of small chunks.

To mitigate this problem, you can allocate the small chunks in an array.
