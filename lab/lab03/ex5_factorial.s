.globl factorial

.data
n: .word 8

.text
# Don't worry about understanding the code in main
# You'll learn more about function calls in lecture soon
main:
    la t0, n
    lw a0, 0(t0)
    jal ra, factorial

    addi a1, a0, 0
    addi a0, x0, 1
    ecall # Print Result

    addi a1, x0, '\n'
    addi a0, x0, 11
    ecall # Print newline

    addi a0, x0, 10
    ecall # Exit

# factorial takes one argument:
# a0 contains the number which we want to compute the factorial of
# The return value should be stored in a0
factorial:
    # YOUR CODE HERE
    addi t1 x0 1     # Stop condition
    addi t2 a0 1     # Get the value of n plus 1
    addi a0 x0 1     # Set the return value as 1
    blt t1 t2 loop

    # This is how you return from a function. You'll learn more about this later.
    # This should be the last line in your program.
    jr ra

loop:
    mul a0 a0 t1 
    addi t1 t1 1
    blt t1 t2 loop

    jr ra
