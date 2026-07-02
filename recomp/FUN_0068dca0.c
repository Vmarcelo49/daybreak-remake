// ============================================
// Address:  0x0068dca0
// Original: FUN_0068dca0
// Status:   unreviewed
// ============================================

int __fastcall FUN_0068dca0(int *param_1)

{
    int iVar1;
    int *piVar2;

    iVar1 = *param_1;
    if (iVar1 != 0)
    {
        piVar2     = (int *)FUN_0068dce0(*param_1);
        *param_1   = *piVar2;
        param_1[1] = param_1[1] + -1;
    }
    return iVar1;
}
