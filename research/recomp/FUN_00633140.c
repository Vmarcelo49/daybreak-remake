// ============================================
// Address:  0x00633140
// Original: FUN_00633140
// Status:   unreviewed
// ============================================

void __thiscall FUN_00633140(int param_1, int param_2, float param_3)

{
    int iVar1;
    float10 fVar2;

    *(float *)(param_1 + 0x88) = (-(param_3 + 90.0) * 3.1415927) / 180.0;
    if ((((param_2 != *(int *)(param_1 + 0x7c)) || (*(char *)(param_1 + 0x94) == '\0')) &&
         (-1 < param_2)) &&
        (iVar1 = FUN_0064e910(), param_2 < iVar1))
    {
        *(int *)(param_1 + 0x7c)        = param_2;
        *(undefined1 *)(param_1 + 0x94) = 1;
        fVar2                           = (float10)FUN_0064e8b0(param_2);
        *(float *)(param_1 + 0x84)      = (float)fVar2;
        *(undefined4 *)(param_1 + 0x80) = 0;
        *(undefined1 *)(param_1 + 0x95) = 0;
    }
    return;
}
