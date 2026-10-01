// ============================================
// Address:  0x0066df8c
// Original: FUN_0066df8c
// Status:   unreviewed
// ============================================

void FUN_0066df8c(char *param_1)

{
    char cVar1;
    char cVar2;
    int iVar3;
    bool bVar4;

    iVar3 = _tolower((int)*param_1);
    bVar4 = iVar3 == 0x65;
    while (!bVar4)
    {
        param_1 = param_1 + 1;
        iVar3   = _isdigit((int)*param_1);
        bVar4   = iVar3 == 0;
    }
    cVar2    = *param_1;
    *param_1 = DAT_006b835c;
    do
    {
        param_1  = param_1 + 1;
        cVar1    = *param_1;
        *param_1 = cVar2;
        cVar2    = cVar1;
    } while (*param_1 != '\0');
    return;
}
