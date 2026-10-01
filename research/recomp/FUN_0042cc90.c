// ============================================
// Address:  0x0042cc90
// Original: FUN_0042cc90
// Status:   unreviewed
// ============================================

int __fastcall FUN_0042cc90(int param_1)

{
    undefined4 uVar1;
    undefined4 uVar2;
    uint3 uVar4;
    int iVar3;
    float10 fVar5;
    float10 fVar6;
    float fVar7;
    float fVar8;

    fVar5        = (float10)FUN_0042da80();
    fVar5        = (float10)FUN_0065d010((float)fVar5);
    fVar7        = (float)fVar5;
    fVar5        = (float10)FUN_0042da80();
    fVar5        = (float10)FUN_0065d050((float)fVar5);
    DAT_006c78a4 = 0x461c4000;
    fVar6        = (float10)FUN_0065d010(*(undefined4 *)(param_1 + 0x5c));
    fVar8        = (float)(fVar6 * (float10)(float)fVar5);
    fVar6        = (float10)FUN_0065d050(*(undefined4 *)(param_1 + 0x5c), fVar7, fVar8);
    uVar1        = FUN_00423750((float)(fVar6 * (float10)(float)fVar5), fVar7, fVar8);
    uVar2        = FUN_0064ecb0(uVar1);
    FUN_0042d2c0(uVar2, uVar1);
    *(undefined4 *)(param_1 + 0x80) = DAT_006c78a4;
    fVar7                           = *(float *)(param_1 + 0x80);
    uVar4 = (uint3)(CONCAT22((short)((uint)param_1 >> 0x10),
                             (ushort)(fVar7 < 10000.0) << 8 | (ushort)NAN(fVar7) << 10 |
                                 (ushort)(fVar7 == 10000.0) << 0xe) >>
                    8);
    if (fVar7 < 10000.0)
    {
        iVar3 = CONCAT31(uVar4, 1);
    }
    else
    {
        iVar3 = (uint)uVar4 << 8;
    }
    return iVar3;
}
