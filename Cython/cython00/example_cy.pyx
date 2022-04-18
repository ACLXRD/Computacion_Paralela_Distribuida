cpdef int test(int x):
    cdef y = 0
    cdef i
    for i in range(x):
        y += i
        
    return y