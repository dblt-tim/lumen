extern display_int_info

section .text

%macro ISR_ENTRY_START 0

push rax
push rbx
push rcx
push rdx
push rsi
push rdi
push rbp
push r8
push r9
push r10
push r11
push r12
push r13
push r14
push r15

%endmacro

%macro ISR_ENTRY_END 0

pop r15
pop r14
pop r13
pop r12
pop r11
pop r10
pop r9
pop r8
pop rbp
pop rdi
pop rsi
pop rdx
pop rcx
pop rbx
pop rax

%endmacro

%macro ISR_ENTRY_NOERR 1
global isr%1
isr%1:
    cli
    ISR_ENTRY_START
    
    push 0
    push %1
    
    mov rdi, rsp
    call display_int_info

    add rsp, 16

    ISR_ENTRY_END
    sti
    iretq
%endmacro

%macro ISR_ENTRY_ERR 1
global isr%1
isr%1:
    cli
    ISR_ENTRY_START
    push %1
    mov rdi, rsp
    call display_int_info
    add rsp, 16
    ISR_ENTRY_END
    sti
    iretq
%endmacro

; Exceptions 0–31 (CPU reserved)
ISR_ENTRY_NOERR 0     ; Divide-by-zero
ISR_ENTRY_NOERR 1     ; Debug
ISR_ENTRY_NOERR 2     ; Non-maskable interrupt
ISR_ENTRY_NOERR 3     ; Breakpoint
ISR_ENTRY_NOERR 4     ; Overflow
ISR_ENTRY_NOERR 5     ; Bound range exceeded
ISR_ENTRY_NOERR 6     ; Invalid opcode
ISR_ENTRY_NOERR 7     ; Device not available
ISR_ENTRY_ERR   8     ; Double fault
ISR_ENTRY_NOERR 9     ; Coprocessor segment overrun (reserved)
ISR_ENTRY_ERR   10    ; Invalid TSS
ISR_ENTRY_ERR   11    ; Segment not present
ISR_ENTRY_ERR   12    ; Stack segment fault
ISR_ENTRY_ERR   13    ; General protection fault
ISR_ENTRY_ERR   14    ; Page fault
ISR_ENTRY_NOERR 15    ; Reserved
ISR_ENTRY_NOERR 16    ; x87 Floating Point Exception
ISR_ENTRY_ERR   17    ; Alignment check
ISR_ENTRY_NOERR 18    ; Machine check
ISR_ENTRY_NOERR 19    ; SIMD Floating-Point Exception
ISR_ENTRY_NOERR 20    ; Virtualization Exception
ISR_ENTRY_NOERR 21    ; Control Protection Exception
; 22–31 are reserved or unused
ISR_ENTRY_NOERR 22
ISR_ENTRY_NOERR 23
ISR_ENTRY_NOERR 24
ISR_ENTRY_NOERR 25
ISR_ENTRY_NOERR 26
ISR_ENTRY_NOERR 27
ISR_ENTRY_NOERR 28
ISR_ENTRY_NOERR 29
ISR_ENTRY_ERR   30    ; Security Exception
ISR_ENTRY_NOERR 31

section .data

global isr_table

isr_table:
    dq isr0
    dq isr1
    dq isr2
    dq isr3
    dq isr4
    dq isr5
    dq isr6
    dq isr7
    dq isr8
    dq isr9
    dq isr10
    dq isr11
    dq isr12
    dq isr13
    dq isr14
    dq isr15
    dq isr16
    dq isr17
    dq isr18
    dq isr19
    dq isr20
    dq isr21
    dq isr22
    dq isr23
    dq isr24
    dq isr25
    dq isr26
    dq isr27
    dq isr28
    dq isr29
    dq isr30
    dq isr31
