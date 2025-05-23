#ifndef OS_STDIO_H
#define OS_STDIO_H

#ifdef __OS_FREESTANDING__
    #include "printf.h"
    #include "defines.h"

    #include "../../kernel/arch/x86/include/console.h"
    #include "../../kernel/arch/x86/include/disk.h"
    #include "../../kernel/arch/x86/include/status.h"
    #include "../../kernel/arch/x86/include/display.h"
    #include "../../kernel/arch/x86/include/graphics.h"
    #include "../../kernel/arch/usr/bin/include/input.h"
    #include "../../kernel/arch/x86/include/messages.h"
    #include "../../kernel/arch/usr/bin/include/ps1.h"
    #include "../../kernel/arch/usr/bin/include/shell.h"
    #include "../../kernel/arch/x86/include/state.h"
    #include "../../kernel/arch/x86/include/status_check.h"

    #include "../../kernel/arch/x86/include/util.h"

    #include "../../boot/drivers/include/display.h"
    #include "../../boot/drivers/include/ports.h"
#else
    #include "./nff_ostd.h"
#endif


#endif // !OS_STDIO_H