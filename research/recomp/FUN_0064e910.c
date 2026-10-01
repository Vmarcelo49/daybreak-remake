// ============================================
// Address:  0x0064e910
// Original: FUN_0064e910
// Status:   unreviewed
// ============================================

undefined4 __fastcall FUN_0064e910(int param_1)

{
    uint uVar1;
    uint uVar2;
    undefined4 local_c;

    uVar1 = (**(code **)(**(int **)(param_1 + 0xc) + 0x14))(*(undefined4 *)(param_1 + 0xc));
    uVar2 = (**(code **)(**(int **)(param_1 + 0xc) + 0x10))(*(undefined4 *)(param_1 + 0xc));
    if (uVar2 < uVar1)
    {
        local_c = (**(code **)(**(int **)(param_1 + 0xc) + 0x14))(*(undefined4 *)(param_1 + 0xc));
    }
    else
    {
        local_c = (**(code **)(**(int **)(param_1 + 0xc) + 0x10))(*(undefined4 *)(param_1 + 0xc));
    }
    return local_c;
}
