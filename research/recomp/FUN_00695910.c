// ============================================
// Address:  0x00695910
// Original: FUN_00695910
// Status:   unreviewed
// ============================================

undefined4 FUN_00695910(int param_1, undefined4 param_2, int param_3)

{
    int iVar1;
    undefined4 uVar2;

    iVar1 = FUN_006871b0(param_2, &DAT_006acfe4);
    if (iVar1 == 0)
    {
        uVar2 = FUN_0068df80(param_1, param_2, param_3);
    }
    else if (param_3 == 0)
    {
        uVar2 = 0x80004003;
    }
    else
    {
        uVar2 = FUN_0068e090(param_1 + -4, param_3);
    }
    return uVar2;
}
