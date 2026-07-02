// ============================================
// Address:  0x00686ad0
// Original: FUN_00686ad0
// Status:   unreviewed
// ============================================

undefined4 __fastcall FUN_00686ad0(int param_1)

{
    int iVar1;
    undefined4 uVar2;

    iVar1 = FUN_004233c0();
    if (iVar1 == 0)
    {
        uVar2 = 0;
    }
    else
    {
        uVar2 = *(undefined4 *)(param_1 + 0x28);
    }
    return uVar2;
}
