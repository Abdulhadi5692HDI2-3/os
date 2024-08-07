extern ExceptionHandle
extern IrqHandle
extern IrqPITHandle

%macro IsrErrStub 1
IsrStub%+%1:
    call ExceptionHandle
    iret
%endmacro

%macro IsrNoErrStub 1
IsrStub%+%1:
    call ExceptionHandle
    iret
%endmacro

%macro IsrIrqStub 1
IsrStub%+%1:
    pusha

    mov ax, ds
    push eax

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call IrqHandle
    pop ebx
    mov ds, bx
    mov es, bx
    mov fs, bx
    mov gs, bx

    popa
    add esp, 8
    iret
%endmacro


IsrNoErrStub 0
IsrNoErrStub 1
IsrNoErrStub 2
IsrNoErrStub 3
IsrNoErrStub 4
IsrNoErrStub 5
IsrNoErrStub 6
IsrNoErrStub 7
IsrErrStub   8
IsrNoErrStub 9
IsrErrStub   10
IsrErrStub   11
IsrErrStub   12
IsrErrStub   13
IsrErrStub   14
IsrNoErrStub 15
IsrNoErrStub 16
IsrErrStub   17
IsrNoErrStub 18
IsrNoErrStub 19
IsrNoErrStub 20
IsrNoErrStub 21
IsrNoErrStub 22
IsrNoErrStub 23
IsrNoErrStub 24
IsrNoErrStub 25
IsrNoErrStub 26
IsrNoErrStub 27
IsrNoErrStub 28
IsrNoErrStub 29
IsrErrStub   30
IsrNoErrStub 31
; IsrIrqStub   32
IsrStub32:
    call IrqPITHandle
    iret

IsrIrqStub   33
IsrIrqStub   34
IsrIrqStub   35
IsrIrqStub   36
IsrIrqStub   37
IsrIrqStub   38
IsrIrqStub   39
IsrIrqStub   40
IsrIrqStub   41
IsrIrqStub   42
IsrIrqStub   43
IsrIrqStub   44
IsrIrqStub   45
IsrIrqStub   46

global IsrStubTable
IsrStubTable:
%assign i 0
%rep 47
    dd IsrStub%+i
%assign i i+1
%endrep