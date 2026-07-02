// ============================================
// Address:  0x004331a0
// Original: FUN_004331a0
// Status:   unreviewed
// ============================================

void __thiscall FUN_004331a0(undefined1 *param_1, int param_2)

{
    undefined4 *puVar1;
    undefined4 *puVar2;
    undefined4 *puVar3;
    undefined1 *puStack_50;
    undefined1 local_30[8];
    undefined1 local_28[8];
    undefined1 local_20[8];
    undefined1 *local_18;
    undefined1 *local_14;
    void *pvStack_10;
    undefined1 *puStack_c;
    undefined4 local_8;

    local_8       = 0xffffffff;
    puStack_c     = &LAB_0069e530;
    pvStack_10    = ExceptionList;
    local_14      = &stack0xffffffb4;
    local_18      = (undefined1 *)&puStack_50;
    ExceptionList = &pvStack_10;
    puStack_50    = param_1;
    allocator<>(param_2 + 1);
    FUN_00424d60();
    *(undefined4 *)(param_1 + 4)    = 0;
    *(undefined4 *)(param_1 + 8)    = 0;
    *(undefined4 *)(param_1 + 0xc)  = 0;
    *(undefined4 *)(param_1 + 0x10) = 0;
    local_8                         = 0;
    puStack_50                      = local_20;
    puVar1                          = (undefined4 *)FUN_004273e0();
    puStack_50                      = local_28;
    puVar2                          = (undefined4 *)FUN_004273b0();
    puStack_50                      = local_30;
    puVar3                          = (undefined4 *)FUN_00425ae0();
    puStack_50                      = (undefined1 *)puVar1[1];
    FUN_004332a0(*puVar3, puVar3[1], *puVar2, puVar2[1], *puVar1);
    FUN_00433274();
    return;
}
