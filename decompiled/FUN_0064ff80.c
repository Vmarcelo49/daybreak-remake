// Function: FUN_0064ff80
// Address:  0x0064ff80
// Source:   batch_decompile (mass dump)
// Hash:     18e0fe764163f616


undefined4 __fastcall FUN_0064ff80(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = D3DXCreateEffect(DAT_006d16f8,&DAT_006a5f68,0xd6c,0,0,0,0,param_1,0);
  if (iVar1 < 0) {
    FUN_006553e0(&DAT_006aa950);
    uVar2 = 0;
  }
  else {
    iVar1 = D3DXCreateEffect(DAT_006d16f8,&DAT_006a6cd8,0xe38,0,0,0,0,param_1 + 4,0);
    if (iVar1 < 0) {
      FUN_006553e0(&DAT_006aa96c);
      uVar2 = 0;
    }
    else {
      iVar1 = D3DXCreateEffect(DAT_006d16f8,&DAT_006a7b10,0x32c,0,0,0,0,param_1 + 8,0);
      if (iVar1 < 0) {
        FUN_006553e0(&DAT_006aa988);
        uVar2 = 0;
      }
      else {
        iVar1 = D3DXCreateEffect(DAT_006d16f8,&DAT_006a7e40,0x7ac,0,0,0,0,param_1 + 0xc,0);
        if (iVar1 < 0) {
          FUN_006553e0(&DAT_006aa9a4);
          uVar2 = 0;
        }
        else {
          iVar1 = D3DXCreateEffect(DAT_006d16f8,&DAT_006a85f0,0x6d0,0,0,0,0,param_1 + 0x10,0);
          if (iVar1 < 0) {
            FUN_006553e0(&DAT_006aa9c0);
            uVar2 = 0;
          }
          else {
            iVar1 = D3DXCreateEffect(DAT_006d16f8,&DAT_006a8cc0,0x780,0,0,0,0,param_1 + 0x14,0);
            if (iVar1 < 0) {
              FUN_006553e0(&DAT_006aa9dc);
              uVar2 = 0;
            }
            else {
              iVar1 = D3DXCreateEffect(DAT_006d16f8,&DAT_006a9440,0x78c,0,0,0,0,param_1 + 0x18,0);
              if (iVar1 < 0) {
                FUN_006553e0(&DAT_006aa9f8);
                uVar2 = 0;
              }
              else {
                iVar1 = D3DXCreateEffect(DAT_006d16f8,&DAT_006a9bd0,0xd6c,0,0,0,0,param_1 + 0x1c,0);
                if (iVar1 < 0) {
                  FUN_006553e0(&DAT_006aaa14);
                  uVar2 = 0;
                }
                else {
                  iVar1 = D3DXCreateEffect(DAT_006d16f8,&DAT_006a5640,0x494,0,0,0,0,param_1 + 0x20,0
                                          );
                  if (iVar1 < 0) {
                    FUN_006553e0(&DAT_006aaa30);
                    uVar2 = 0;
                  }
                  else {
                    iVar1 = D3DXCreateEffect(DAT_006d16f8,&DAT_006a5ad8,0x48c,0,0,0,0,param_1 + 0x24
                                             ,0);
                    if (iVar1 < 0) {
                      FUN_006553e0(&DAT_006aaa4c);
                      uVar2 = 0;
                    }
                    else {
                      uVar2 = 1;
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return uVar2;
}

