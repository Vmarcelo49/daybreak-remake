// ============================================
// Address:  0x0065d870
// Original: FUN_0065d870
// Status:   unreviewed
// ============================================


void __fastcall FUN_0065d870(undefined4 *param_1)

{
  HFONT pHVar1;
  HDC pHVar2;
  HGDIOBJ pvVar3;
  tagTEXTMETRICA local_3c;
  
  pHVar1 = CreateFontA(param_1[0x4d],0,0,0,700,(uint)*(byte *)((int)param_1 + 0x131),0,0,0x80,4,0,2,
                       0x31,(LPCSTR)(param_1 + 0xc));
  param_1[2] = pHVar1;
  pHVar2 = GetDC((HWND)*param_1);
  param_1[1] = pHVar2;
  pvVar3 = SelectObject((HDC)param_1[1],(HGDIOBJ)param_1[2]);
  param_1[3] = pvVar3;
  GetTextMetricsA((HDC)param_1[1],&local_3c);
  param_1[9] = local_3c.tmAscent;
  return;
}

