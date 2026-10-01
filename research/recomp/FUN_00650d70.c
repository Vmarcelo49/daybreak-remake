// ============================================
// Address:  0x00650d70
// Original: FUN_00650d70
// Status:   unreviewed
// ============================================

void __fastcall FUN_00650d70(int param_1)

{
    undefined4 uVar1;

    if (*(char *)(param_1 + 0x59) != '\0')
    {
        if (DAT_006d16f8 != (int *)0x0)
        {
            uVar1                            = (**(code **)(*DAT_006d16f8 + 0xc))(DAT_006d16f8);
            *(undefined4 *)(param_1 + 0x28c) = uVar1;
        }
        if (*(int *)(param_1 + 0x28c) == -0x7789f797)
        {
            FUN_00650de0();
        }
    }
    if (*(int *)(param_1 + 0x28c) == 0)
    {
        *(undefined1 *)(param_1 + 0x59) = 0;
    }
    return;
}
