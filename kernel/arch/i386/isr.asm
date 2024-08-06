extern ExceptionHandle

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

global IsrStubTable
IsrStubTable:
%assign i 0
%rep 32
    dd IsrStub%+i
%assign i i+1
%endrep