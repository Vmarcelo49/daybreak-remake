// ============================================
// Address:  0x0067db50
// Original: FUN_0067db50
// Status:   unreviewed
// ============================================

void FUN_0067db50(float param_1, uint param_2, uint param_3, float *param_4, undefined4 *param_5)

{
    uint uVar1;
    uint uVar2;

    uVar1    = ((int)param_3 < (int)param_2) - 1;
    uVar2    = (int)(param_2 - param_3) >> 0x1f;
    uVar2    = 0x1f - ((param_2 - param_3 ^ uVar2) - uVar2);
    *param_4 = (*(float *)(&DAT_006be780 + (((int)uVar2 < 0) - 1 & uVar2) * 4) + 1.0) *
               *(float *)(&DAT_006be380 + (~uVar1 & param_2 | uVar1 & param_3) * 4) * param_1;
    *param_5 = 0;
    return;
}
