// ============================================
// Address:  0x0065d150
// Original: FUN_0065d150
// Suggested: GetRandomNumber (confidence: medium)
// Status:   suggested — name kept as comment until reviewed
// NOTE: agent:extraction suggested 'GetRandomNumber'. agent:local identifies o algoritmo
// especificamente como Mersenne Twister (MT19937): state de 624 words (DAT_006d31d0[0x26f]),
// seeding via index DAT_006b77bc, constantes 0x80000000/0x7fffffff para twist, tempering (shifts
// 0xb/0x13a58ad/0x1df8c/0xf/0x12). Sugeriu 'MersenneTwisterRand'. 'GetRandomNumber' é correto;
// 'MersenneTwisterRand' documenta o algoritmo. Operador decide o nível de detalhe.
// ============================================

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

uint FUN_0065d150(void)

{
    uint *puVar1;
    uint uVar2;
    int local_c;

    if (0x26f < DAT_006b77bc)
    {
        if (DAT_006b77bc == 0x271)
        {
            FUN_0065d0c0(0x1571);
        }
        for (local_c = 0; local_c < 0xe3; local_c = local_c + 1)
        {
            (&DAT_006d31d0)[local_c] =
                ((&DAT_006d31d0)[local_c] & 0x80000000 | (&DAT_006d31d4)[local_c] & 0x7fffffff) >>
                    1 ^
                *(uint *)(&DAT_006d3804 + local_c * 4) ^
                *(uint *)(&DAT_006b77c0 + ((&DAT_006d31d4)[local_c] & 1) * 4);
        }
        for (; local_c < 0x26f; local_c = local_c + 1)
        {
            (&DAT_006d31d0)[local_c] =
                ((&DAT_006d31d0)[local_c] & 0x80000000 | (&DAT_006d31d4)[local_c] & 0x7fffffff) >>
                    1 ^
                *(uint *)(&DAT_006d2e44 + local_c * 4) ^
                *(uint *)(&DAT_006b77c0 + ((&DAT_006d31d4)[local_c] & 1) * 4);
        }
        DAT_006d3b8c = (DAT_006d3b8c & 0x80000000 | DAT_006d31d0 & 0x7fffffff) >> 1 ^
                       _DAT_006d3800 ^ *(uint *)(&DAT_006b77c0 + (DAT_006d31d0 & 1) * 4);
        DAT_006b77bc = 0;
    }
    puVar1       = &DAT_006d31d0 + DAT_006b77bc;
    DAT_006b77bc = DAT_006b77bc + 1;
    uVar2        = *puVar1 >> 0xb ^ *puVar1;
    uVar2        = (uVar2 & 0x13a58ad) << 7 ^ uVar2;
    uVar2        = (uVar2 & 0x1df8c) << 0xf ^ uVar2;
    return uVar2 >> 0x12 ^ uVar2;
}
