.globl dot

.text
# =======================================================
# FUNCTION: Dot product of 2 int arrays
# Arguments:
#   a0 (int*) is the pointer to the start of arr0
#   a1 (int*) is the pointer to the start of arr1
#   a2 (int)  is the number of elements to use
#   a3 (int)  is the stride of arr0
#   a4 (int)  is the stride of arr1
# Returns:
#   a0 (int)  is the dot product of arr0 and arr1
# Exceptions:
#   - If the number of elements to use is less than 1,
#     this function terminates the program with error code 36
#   - If the stride of either array is less than 1,
#     this function terminates the program with error code 37
# =======================================================
dot:
    # Prologue
    # Check the number of elements
    addi t0, x0, 1
    blt a2, t0, except_element

    # Check the number of stride
    blt a3, t0, except_stride
    blt a4, t0, except_stride

    # Initialize the sum and used element as 0
    li t0, 0
    li t1, 0

loop_start:
    bge t1, a2, loop_end 

    # For arr0
    mul t2, t1, a3
    slli t2, t2, 2
    add t2, a0, t2
    lw t2, 0(t2)

    # For arr1
    mul t3, t1, a4
    slli t3, t3, 2
    add t3, a1, t3
    lw t3, 0(t3)

    # Add the value to sum
    mul t2, t2, t3
    add t0, t0, t2

    # Update the used number of element
    addi t1, t1, 1
    j loop_start

loop_end:
    # Epilogue
    add a0, t0, x0
    jr ra

except_element:
    li a0, 36
    j exit

except_stride:
    li a0, 37
    j exit