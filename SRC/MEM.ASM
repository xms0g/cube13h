.model small
.data
.code
public __memsetw
public __memcpyw
; --------------------------------------------------------------------
; void far* _Cdecl _memsetw(void far* dest, int val, unsigned count) ;
; --------------------------------------------------------------------
__memsetw proc
    push bp
    mov bp, sp

    push es
    push di
    push cx

    les di, [bp+4]
    mov ax, [bp+8]
    mov cx, [bp+10]
    rep stosw

    pop cx
    pop di
    pop es
    
    mov ax, [bp+4]    ; offset part of dest
    mov dx, [bp+6]    ; segment part of dest

    mov sp, bp
    pop bp
    ret
__memsetw endp

; --------------------------------------------------------------------------
; void far* _Cdecl _memcpyw(void far* dest, void far* src, unsigned count) ; 
; --------------------------------------------------------------------------
__memcpyw proc
    push bp
    mov bp, sp

    push ds
    push es
    push di
    push cx
    
    les di, [bp+4]
    lds si, [bp+8]
    mov cx, [bp+12]
    rep movsw

    pop cx
    pop di
    pop es
    pop ds
    
    mov ax, [bp+4]    ; offset part of dest
    mov dx, [bp+6]    ; segment part of dest    
    
    mov sp, bp
    pop bp
    ret
__memcpyw endp
end