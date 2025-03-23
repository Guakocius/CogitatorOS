HPC equ 2
SPT equ 18
disk_load:
    pusha
    push ax
    push eax
    push ebx
    push edx

    mov ebx, ecx

    mov edx, 0
    mov eax, ebx
    mov ecx, SPT
    div ecx

    add edx, 1
    push edx

    mov edx, 0
    mov ecx, HPC
    div ecx

    push edx

    mov eax, HPC
    mov ecx, SPT
    mul ecx

    mov ecx, eax
    mov eax, ebx
    mov edx, 0
    div ecx
    push eax

    pop eax
    mov ch, al ; Cylinder
    pop eax
    mov dh, al ; Head
    pop eax
    mov cl, al ; Sector
    pop eax
    mov dl, al ; Drive
    
    pop ebx
    pop eax

    mov ah, 0x02 ; Read sectors

    int 0x13
    jc disk_error
    
    pop dx
    cmp dl, al ; Check if the number of read sectors is equal to the number of sectors to read
    jne disk_warn

disk_load_done:
    popa
    ret

disk_error:
    call error_loop
    jmp disk_load_done

disk_warn:
    call error_loop
    jmp disk_load_done

error_loop:
    mov dh, ah
    mov ah, 0x0E
    mov al, 'E'
    int 0x10
    mov al, 'r'
    int 0x10
    int 0x10
    mov al, 0x20 ; Space
    int 0x10
    mov al, dh ; Print Error Code
    int 0x10
