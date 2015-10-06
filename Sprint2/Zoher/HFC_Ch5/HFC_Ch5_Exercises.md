Zoher Ghadyali  
Head First C Chapter 5  
Exercises

**2) If you run git pull upstream master, you should get a directory named hw03 that contains rand.c and a Makefile.  Read over rand.c and test_rand.c, then compile and run test_rand.c.  Which implementation is fastest?**

I compiled and ran test_rand.c three times which produced 6 total measurements comparing my_random_float() and random_float() where the my_random_float() function uses Allen's implementation and random_float() uses the traditional implementation of this algorithm. On average, I have found that Allen's implementation takes 5000.897 ms and the traditional implementation is 5008.393 ms so Allen's implementation is faster by slightly under 8 ms.

**3) Modify test_rand.c to test my_random_float2.  Which implementation of my algorithm is faster?**

The my_random_float() function is roughly three times faster than the my_random_float2() function.

**4) Fill in the body of my_random_double and test it to see if it returns numbers uniformly distributed from 0 to 1.  Code do that is shown in hw03.  test_rand2.c prints 1000 random numbers, which you can redirect into a file.  check_uniform.py reads the file and plots the cumulative distribution function (CDF) of the values.  For a uniform distribution, the CDF should be a straight line.**

The my_random_double() implementation is in the **rand.c** file. The cumulative distribution plot is contained in **my_random_double_distribution.png**. The CDF is a straight line from 0 to 1.

**5) Modify test_rand.c to compare my_random_double and random_double.  Which is faster?**

My implementation of my_random_double is a little over twice as fast than random_double.