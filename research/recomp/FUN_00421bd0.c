// ============================================
// Address:  0x00421bd0
// Original: FUN_00421bd0
// Status:   unreviewed
// ============================================

void __fastcall FUN_00421bd0(int param_1)

{
    int iVar1;
    int iVar2;
    uint uVar3;
    uint uVar4;

    uVar3 = FUN_0065d150();
    uVar4 = FUN_0065d150();
    iVar1 = *(int *)(DAT_006cfaf0 + 0x40);
    iVar2 = *(int *)(DAT_006cfaf0 + 0x38);
    *(float *)(param_1 + 0x14) =
        (float)(uVar3 % (uint)(*(int *)(DAT_006cfaf0 + 0x3c) - *(int *)(DAT_006cfaf0 + 0x34))) +
        (float)*(int *)(DAT_006cfaf0 + 0x34);
    *(float *)(param_1 + 0x1c) =
        (float)(uVar4 % (uint)(iVar1 - iVar2)) + (float)*(int *)(DAT_006cfaf0 + 0x38);
    *(undefined4 *)(param_1 + 0x18) = 0x447a0000;
    return;
}
