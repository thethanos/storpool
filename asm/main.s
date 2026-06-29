.global _start

.text

_start:
    movq $1, %rax
    movq $1, %rdi
    movq $message, %rsi
    movq $14, %rdx
    syscall

    movq $60, %rax
    movq $0, %rdi
    syscall

.data

message:
    .ascii "Hello, world\n"