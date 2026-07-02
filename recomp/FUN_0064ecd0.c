// ============================================
// Address:  0x0064ecd0
// Original: FUN_0064ecd0
// Status:   unreviewed
// ============================================


undefined4 __thiscall FUN_0064ecd0(int param_1,char *param_2,int *param_3)

{
  char cVar1;
  int iVar2;
  undefined4 uVar3;
  size_t sVar4;
  wchar_t *pwVar5;
  undefined4 local_10;
  void *local_c;
  undefined1 local_8 [4];
  
  iVar2 = FUN_0064e7c0(param_2);
  *param_3 = iVar2;
  if (*param_3 == -1) {
    wsprintfA(&DAT_006d12b0,"%s%s",&DAT_006d11a8,param_2);
    FUN_006560c0(local_8,&DAT_006d12b0);
    cVar1 = FUN_0064d6e0();
    if (cVar1 == '\0') {
      iVar2 = FUN_0064f010();
      *param_3 = iVar2;
      FUN_0064ee90(local_8);
      sVar4 = _strlen(param_2);
      local_c = operator_new(sVar4 + 1);
      FUN_0064ef70(&local_c);
      pwVar5 = std::basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>::back
                         ((basic_string<wchar_t,std::char_traits<wchar_t>,std::allocator<wchar_t>_>
                           *)(param_1 + 0x34));
      FUN_0066b860(*(undefined4 *)pwVar5,param_2);
      local_10 = 0xffffffff;
      FUN_0064ef70(&local_10);
      uVar3 = 1;
    }
    else {
      *param_3 = -1;
      uVar3 = 0;
    }
  }
  else {
    uVar3 = 1;
  }
  return uVar3;
}

