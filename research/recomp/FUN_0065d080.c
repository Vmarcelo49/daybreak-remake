// ============================================
// Address:  0x0065d080
// Original: FUN_0065d080
// Status:   unreviewed
// ============================================

float10 __thiscall FUN_0065d080(undefined4 param_1, undefined4 param_2)

{
    float10 fVar1;
    float fVar2;

    fVar1 = (float10)FUN_0065d050(param_2, param_1);
    fVar2 = (float)fVar1;
    if (fVar2 == 0.0)
    {
        fVar1 = (float10)0.0;
    }
    else
    {
        fVar1 = (float10)FUN_0065d010(param_2);
        fVar1 = fVar1 / (float10)fVar2;
    }
    return fVar1;
}
