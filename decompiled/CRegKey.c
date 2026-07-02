// Function: CRegKey
// Address:  0x006940f0
// Reason:   keyword:Key


/* Library Function - Single Match
    public: __thiscall ATL::CRegKey::CRegKey(struct HKEY__ *)
   
   Library: Visual Studio 2010 Debug */

CRegKey * __thiscall ATL::CRegKey::CRegKey(CRegKey *this,HKEY__ *param_1)

{
  *(HKEY__ **)this = param_1;
  *(undefined4 *)(this + 4) = 0;
  *(undefined4 *)(this + 8) = 0;
  return this;
}

