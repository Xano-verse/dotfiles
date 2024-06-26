if exists("b:riscv_asm_defined_zvkng")
    finish
endif

if !exists("b:riscv_asm_zvkn")
    let b:riscv_asm_zvkn = b:riscv_asm_zvkn_max
    let b:undo_ftplugin .= "| unlet! b:riscv_asm_zvkn"
    runtime! syntax/riscv-isas/riscv_asm_zvkn.vim
endif
if !exists("b:riscv_asm_zvkg")
    let b:riscv_asm_zvkg = b:riscv_asm_zvkg_max
    let b:undo_ftplugin .= "| unlet! b:riscv_asm_zvkg"
    runtime! syntax/riscv-isas/riscv_asm_zvkg.vim
endif

let b:riscv_asm_defined_zvkng = 0
