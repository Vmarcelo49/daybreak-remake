// Function: ~ctype<char>
// Address:  0x00667610
// Reason:   keyword:char


/* Library Function - Single Match
    protected: virtual __thiscall std::ctype<char>::~ctype<char>(void)
   
   Library: Visual Studio 2003 Debug */

void __thiscall std::ctype<char>::~ctype<char>(ctype<char> *this)

{
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  puStack_c = &LAB_0069f388;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  *(undefined ***)this = &PTR_FUN_006ab1b4;
  local_8 = 0;
  FUN_00667670();
  local_8 = 0xffffffff;
  FUN_006679d0();
  ExceptionList = local_10;
  return;
}

