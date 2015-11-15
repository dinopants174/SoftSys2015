Zoher Ghadyali  
Think OS Chapter 4  
Reading Questions

**1) What abstractions do file systems provide?  Give an example of something that is logically true about files systems but not true of their implementations.**

A file system maps from each file's names to its contents, which are a sequence of bytes. A file system translates byte-based file operations into block-based operations on storage devices and the programmer doesn't need to think about block-based persistent memory. It would be logically true that files in the same directory are next to each other in persistent memory but that isn't necessarily true.

**2) What information do you imagine is stored in an OpenFileTableEntry?**

The OpenFileTableEntry contains the file position and probably some boolean to determine if the next character is already in memory or to indicate to the OS that it should load the next block of data.

**3) What are some of the ways operating systems deal with the relatively slow performance of persistent storage?**

Operating systems deal with the slow performance of persistent storage by using block transfers, prefetching, buffering, and caching.

**4) Suppose your program writes a file and prints a message indicating that it is done writing.  Then a power cut crashes your computer.  After you restore power and reboot the computer, you find that the file you wrote is not there.  What happened?**

Data written to a file is buffered so it remains stored in memory until there is a full block to write to storage. If there wasn't a full block to write to persistent memory, then when the power cut crashes your computer, the data is lost in the buffer and is not written to a file.

**5) Can you think of one advantage of a File Allocation Table over a UNIX inode?  Or an advantage of a inode over a FAT?**

One advantage of a FAT over a UNIX inode is that FAT contains entries for each cluster which is a contiguous area of disk storage which has better performance than a system of non-contiguous segments.

**6) What is overhead?  What is fragmentation?**

Overhead is the amount of space data structures used by the block allocator take up. Fragmentation is the unused space when some block is left unused/partially used.

**7) Why is the "everything is a file" principle a good idea?  Why might it be a bad idea?**

The "everything is a file" principle is a good idea because it is a stream of bytes abstraction that can be applied in multiple areas but are still treated the same by the programmer. It might be bad idea with representing growing file sizes given that larger and larger files must be represented using more indirection blocks in a file system.