.globl argmax

.text
# =================================================================
# FUNCTION: Given a int array, return the index of the largest
#   element. If there are multiple, return the one
#   with the smallest index.
# Arguments:
#   a0 (int*) is the pointer to the start of the array
#   a1 (int)  is the # of elements in the array
# Returns:
#   a0 (int)  is the first index of the largest element
# Exceptions:
#   - If the length of the array is less than 1,
#     this function terminates the program with error code 36
# =================================================================
argmax:
    # Prologue
    addi t0, x0, 1
    blt a1, t0, except  # The length of array is less than 1

    li t0, 0            # The current index        
    li t1, 0            # The index of largest element
    lw t2, 0(a0)        # The max element

loop_start:
    bge t0, a1, loop_end

    slli t3, t0, 2      # byte offset
    add t3, a0, t3      # the address of current element
    lw t3, 0(t3)        # the value of current element

    blt t3, t2, loop_continue
    j update_index

update_index:
    add t1, t0, x0
    add t2, t3, x0
    j loop_continue

loop_continue:
    addi t0, t0, 1
    j loop_start

loop_end:
    # Epilogue
    add a0, t1, x0
    jr ra

except:
    li a0, 36
    j exit
