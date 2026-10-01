// ============================================
// Address:  0x00633220
// Original: FUN_00633220
// Status:   unreviewed
// ============================================

void __fastcall FUN_00633220(int param_1)

{
    undefined4 uVar1;
    float10 fVar2;
    undefined1 local_3c[12];
    undefined1 local_30[12];
    undefined1 local_24[12];
    float local_18;
    float local_14;
    undefined1 local_10[12];

    FUN_0042dfd0(local_24, param_1 + 0xc);
    FUN_0042dfd0(local_10, param_1 + 0x3c);
    fVar2    = (float10)FUN_0042df50(local_24);
    local_14 = (float)fVar2;
    fVar2    = (float10)FUN_0042df50(local_10);
    local_18 = (float)fVar2;
    if (10000.0 < local_14)
    {
        *(undefined4 *)(param_1 + 0x18) = *(undefined4 *)(param_1 + 0xc);
        *(undefined4 *)(param_1 + 0x1c) = *(undefined4 *)(param_1 + 0x10);
        *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x14);
    }
    if (10000.0 < local_18)
    {
        *(undefined4 *)(param_1 + 0x48) = *(undefined4 *)(param_1 + 0x3c);
        *(undefined4 *)(param_1 + 0x4c) = *(undefined4 *)(param_1 + 0x40);
        *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(param_1 + 0x44);
    }
    if (local_14 <= 2.0)
    {
        *(undefined4 *)(param_1 + 0x18) = *(undefined4 *)(param_1 + 0xc);
        *(undefined4 *)(param_1 + 0x1c) = *(undefined4 *)(param_1 + 0x10);
        *(undefined4 *)(param_1 + 0x20) = *(undefined4 *)(param_1 + 0x14);
    }
    else
    {
        uVar1 = FUN_004241d0(local_30, 0x3e4ccccd);
        FUN_00633a60(uVar1);
    }
    if (local_18 <= 2.0)
    {
        *(undefined4 *)(param_1 + 0x48) = *(undefined4 *)(param_1 + 0x3c);
        *(undefined4 *)(param_1 + 0x4c) = *(undefined4 *)(param_1 + 0x40);
        *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(param_1 + 0x44);
    }
    else
    {
        uVar1 = FUN_004241d0(local_3c, 0x3e99999a);
        FUN_00633a60(uVar1);
    }
    if ((*(char *)(param_1 + 0x94) != '\0') &&
        (*(float *)(param_1 + 0x80) < *(float *)(param_1 + 0x84)))
    {
        *(float *)(param_1 + 0x80) = *(float *)(param_1 + 0x80) + 0.016;
    }
    return;
}
