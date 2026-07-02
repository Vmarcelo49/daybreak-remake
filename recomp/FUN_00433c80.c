// ============================================
// Address:  0x00433c80
// Original: FUN_00433c80
// Status:   unreviewed
// ============================================

undefined4 *FUN_00433c80(undefined4 *param_1)

{
    undefined4 uVar1;
    char cVar2;
    undefined4 *puVar3;
    undefined4 in_stack_00000018;
    undefined4 in_stack_0000001c;

    while (true)
    {
        cVar2 = FUN_00433b00(&stack0x00000010);
        if (cVar2 == '\0')
            break;
        puVar3  = (undefined4 *)FUN_0040fbf0();
        uVar1   = *puVar3;
        puVar3  = (undefined4 *)FUN_0040fbf0();
        *puVar3 = uVar1;
        iterator__operator__();
        iterator__operator__();
    }
    *param_1   = in_stack_00000018;
    param_1[1] = in_stack_0000001c;
    return param_1;
}
