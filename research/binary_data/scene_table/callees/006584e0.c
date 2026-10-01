// Called by LoadNextScene
// Address: 0x006584e0


void __fastcall FUN_006584e0(int param_1)

{
  int iVar1;
  
  if (*(int *)(param_1 + 0xc) != 0) {
    iVar1 = (**(code **)(**(int **)(param_1 + 0xc) + 0x24))
                      (*(undefined4 *)(param_1 + 0xc),0x100,param_1 + 0x20);
    if (iVar1 < 0) {
      (**(code **)(**(int **)(param_1 + 0xc) + 0x1c))(*(undefined4 *)(param_1 + 0xc));
      _memset((void *)(param_1 + 0x20),0,0x100);
    }
  }
  return;
}

