# Operating-Systems-
Linux Operating Systems - Multithreading codes  

# POSIX_THREADS 
This project demonstrates the use of POSIX Threads and semaphores for thread synchronization in C.  
The program creates three separate threads:  
The first thread prints one  
The second thread prints two  
The third thread prints three  
Using semaphores, the threads are synchronized so that they continuously print the sequence

# Max_POSIX  

This program finds the maximum value in an N x N integer matrix using POSIX Threads.
The user provides N, the number of threads p (with N divisible by p), and the matrix A.
The program creates p threads, each calculating the maximum in N/p rows.
Each thread computes a local maximum, then updates a shared variable holding the global maximum.
The update to the shared variable is a critical section and must be protected using a mutex.
Finally, the program prints the maximum value found.
    
# Parallel_1_final :  
Processor 0 reads a vector sized "n"

The programm calculates parallely and prints (through processor 0) : The average value "av". Max value.
Variance = ((x0 - av)^2 + (x1 - av)^2 + ... + (xn-1 - av)^2)/n. Vector X' where X[i]' = |X[i] - max|^2.

# Parallel_2_final :   
Processor 0 reads number "N" and then the array A[N][N].

The programm calculates parallely and prints (through processor 0) : If the array is diagonally dominant The max element the diagonal. Array B where B[i][j] = max - |A[i][j]|, i!=j.
B[i][i] = max, i==j. The min value of array B and it's position.

An array is diagonally dominant when the element of the diagonal is greater than the sum of the elements in the same row
