leader = Semaphore(0);
mux = Semaphore(1);
follower = Semaphore(0);


##Thread A
leader.signal();
follower.wait();
mux.wait();
	#dance
mux.signal();

##Thread B
leader.wait();
follower.signal();
mux.wait();
	#dance
mux.signal();

