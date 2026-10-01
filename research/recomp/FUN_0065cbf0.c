// ============================================
// Address:  0x0065cbf0
// Original: FUN_0065cbf0
// Status:   unreviewed
// ============================================

undefined4 __thiscall
FUN_0065cbf0(int param_1, undefined4 param_2, uint param_3, undefined4 param_4, uint *param_5)

{
    uint uVar1;
    int iVar2;
    undefined4 local_10;

    FUN_0065d670();
    timeGetTime();
    iVar2 = *(int *)(param_1 + 0x24) + (uint)CARRY4(param_3, *(uint *)(param_1 + 0x20));
    if ((iVar2 < *(int *)(param_1 + 0x3c)) ||
        ((iVar2 <= *(int *)(param_1 + 0x3c) &&
          (param_3 + *(uint *)(param_1 + 0x20) <= *(uint *)(param_1 + 0x38)))))
    {
        local_10 = param_3;
    }
    else
    {
        local_10 = *(int *)(param_1 + 0x38) - *(int *)(param_1 + 0x20);
    }
    FUN_006539b0(*(undefined4 *)(param_1 + 0x30), *(undefined4 *)(param_1 + 0x20), 0);
    FUN_006537b0(*(undefined4 *)(param_1 + 0x30), param_2, local_10);
    uVar1                     = *(uint *)(param_1 + 0x20);
    *(uint *)(param_1 + 0x20) = local_10 + *(uint *)(param_1 + 0x20);
    *(uint *)(param_1 + 0x24) = *(int *)(param_1 + 0x24) + (uint)CARRY4(local_10, uVar1);
    *param_5                  = local_10;
    FUN_0065d6a0();
    return 0;
}
