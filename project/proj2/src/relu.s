.globl relu

.text
# ============================================================================== 
# FUNCTION: Performs an inplace element-wise ReLU on an array of ints 
# Arguments: 
#   a0 (int*) is the pointer to the array 
#   a1 (int)  is the # of elements in the array 
# Returns: 
#   None 
# Exceptions: 
#   - If the length of the array is less than 1, 
#     this function terminates the program with error code 36 
# ============================================================================== 
relu:
    # Prologue 
    addi t2, x0, 1          # immediate 1 
    blt a1, t2, except      # check if length is less than 1 

    li t0, 0                # initialize index to 0

loop_start:
    bge t0, a1, loop_end    # if index >= length, exit loop

    slli t1, t0, 2          # calculate byte offset (4 * index)
    add t3, a0, t1          # calculate address of current element
    lw t4, 0(t3)            # load the current element

    blt t4, x0, set_zero    # if current element < 0, set to 0
    j loop_continue         # if >= 0, just update index

set_zero:
    sw x0, 0(t3)            # set the current element to 0

loop_continue:
    addi t0, t0, 1          # increment the index
    j loop_start            # repeat the loop

loop_end:
    # Epilogue 
    jr ra

except:
    li a0, 36               # set error code 36
    j exit                  # exit with error code
