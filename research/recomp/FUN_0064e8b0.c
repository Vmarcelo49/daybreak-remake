// ============================================
// Address:  0x0064e8b0
// Original: FUN_0064e8b0
// Status:   unreviewed
// ============================================

float10 __thiscall FUN_0064e8b0(int param_1, undefined4 param_2)

{
    int iVar1;
    float10 fVar2;
    int *local_c;
    float local_8;

    local_c = (int *)0x0;
    iVar1   = (**(code **)(**(int **)(param_1 + 0xc) + 0x2c))(
        *(undefined4 *)(param_1 + 0xc), param_2, &local_c);
    if (iVar1 < 0)
    {
        fVar2 = (float10)0.0;
    }
    else
    {
        fVar2   = (float10)(**(code **)(*local_c + 0x10))(local_c);
        local_8 = (float)fVar2;
        (**(code **)(*local_c + 8))(local_c);
        fVar2 = (float10)local_8;
    }
    return fVar2;
}
