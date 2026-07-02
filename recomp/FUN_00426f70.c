// ============================================
// Address:  0x00426f70
// Original: FUN_00426f70
// Status:   unreviewed
// ============================================

void FUN_00426f70(undefined4 param_1, undefined4 *param_2)

{
    undefined4 *puVar1;

    puVar1 = (undefined4 *)FUN_00410cf0(0x14, param_1);
    if (puVar1 != (undefined4 *)0x0)
    {
        *puVar1   = *param_2;
        puVar1[1] = param_2[1];
        puVar1[2] = param_2[2];
        puVar1[3] = param_2[3];
        puVar1[4] = param_2[4];
    }
    return;
}
