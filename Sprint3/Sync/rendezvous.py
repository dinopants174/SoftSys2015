# rendezvous

a1Done = Semaphore(0)
b1Done = Semaphore(0)
x = 0
y = 0

## Thread A

y = y + 1
a1Done.signal()
b1Done.wait()
x = x - 1


## Thread B

x = x + 1
b1Done.signal()
a1Done.wait()
y = y - 1

