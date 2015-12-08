# mutual exclusion

mutex = Semaphore(n)
x = 0

## Thread A

mutex.wait()
x = x + 1
mutex.signal()

## Thread B

mutex.wait()
x = x + 1
mutex.signal()
