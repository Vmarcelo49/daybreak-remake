// ============================================
// Address:  0x0068ac50
// Original: FUN_0068ac50
// Status:   unreviewed
// ============================================

undefined4 __fastcall FUN_0068ac50(int param_1)

{
    int iVar1;
    undefined4 uVar2;

    iVar1 = FUN_0068daa0();
    if (iVar1 == 0)
    {
        if (*(char *)(param_1 + 0xa1) == '\0')
        {
            if (*(char *)(param_1 + 0x24) == '\0')
            {
                uVar2 = 0;
            }
            else
            {
                uVar2 = 0x8004020b;
            }
        }
        else
        {
            uVar2 = 1;
        }
    }
    else
    {
        uVar2 = 0x80040227;
    }
    return uVar2;
}
