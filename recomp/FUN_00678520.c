// ============================================
// Address:  0x00678520
// Original: FUN_00678520
// Status:   unreviewed
// ============================================

float10 FUN_00678520(int param_1, int param_2)

{
    int iVar1;
    float10 fVar2;
    undefined8 local_10;

    if ((1 < *(int *)(param_1 + 0x58)) && (*(int *)(param_1 + 4) != 0))
    {
        if (param_2 < *(int *)(param_1 + 0x34))
        {
            if (param_2 < 0)
            {
                iVar1    = 0;
                local_10 = 0.0;
                if (0 < *(int *)(param_1 + 0x34))
                {
                    do
                    {
                        fVar2    = (float10)FUN_00678520(param_1, iVar1);
                        iVar1    = iVar1 + 1;
                        local_10 = (double)(fVar2 + (float10)local_10);
                    } while (iVar1 < *(int *)(param_1 + 0x34));
                }
                return (float10)local_10;
            }
            return (float10) * (longlong *)(*(int *)(param_1 + 0x44) + 8 + param_2 * 0x10) /
                   (float10) * (int *)(*(int *)(param_1 + 0x48) + 8 + param_2 * 0x20);
        }
    }
    return (float10)-131.0;
}
