// ============================================
// Address:  0x00668b80
// Original: FUN_00668b80
// Status:   unreviewed
// ============================================


undefined4 FUN_00668b80(allocator<char> *param_1)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined *puVar5;
  int extraout_var;
  undefined4 local_c;
  
  local_c = 0x80004005;
  if (param_1 == (allocator<char> *)0x0) {
    local_c = 0x80004003;
  }
  else {
    uVar1 = FUN_00669460(&DAT_006ad184);
    iVar4 = extraout_var;
    iVar2 = ___(uVar1);
    if (iVar2 != 0) {
      uVar1 = FUN_00669440(iVar4,0);
      puVar5 = &DAT_006ad254;
      uVar3 = std::allocator<char>::allocator<char>(param_1);
      iVar2 = _IsEqualGUID(uVar3,puVar5,iVar4,uVar1);
      if (iVar2 != 0) {
        puVar5 = &DAT_006ad224;
        uVar3 = FUN_00669420(&DAT_006ad224);
        iVar2 = _IsEqualGUID(uVar3,puVar5,iVar4,uVar1);
        if (iVar2 != 0) {
          *(undefined1 *)(iVar4 + 0x168) = 1;
          return 0;
        }
      }
    }
    uVar1 = FUN_00669460(&DAT_006ad194);
    iVar2 = ___(uVar1);
    if (iVar2 == 0) {
      FUN_00669440();
      *(undefined1 *)(iVar4 + 0x168) = 0;
      puVar5 = &DAT_006ad254;
      uVar1 = std::allocator<char>::allocator<char>(param_1);
      iVar4 = _IsEqualGUID(uVar1,puVar5);
      if (iVar4 != 0) {
        uVar1 = FUN_00669420(&DAT_006ad224);
        iVar4 = _IsEqualGUID(uVar1);
        if (iVar4 != 0) {
          local_c = 0;
        }
      }
    }
    else {
      local_c = 0x80070057;
    }
  }
  return local_c;
}

