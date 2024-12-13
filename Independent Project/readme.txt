testfile.c:
It gives error for all the required cases.
we have passed a 2d array to the the kernel_2d_memcpy() syscall which gives 2d array with elements copied from the original array. 


syscall.c:
we have used  __copy_to_user  to copy the matrix to an array from which __copy_to_user is used to copy the array to the final matrix.
The error cases return with -1 value.