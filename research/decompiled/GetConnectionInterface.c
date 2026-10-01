// Function: GetConnectionInterface
// Address:  0x00695a30
// Reason:   keyword:connect


/* Library Function - Single Match
    public: virtual long __stdcall ATL::IConnectionPointImpl<class CTextImage,&struct _GUID const
   IID_IVsTextStreamEvents,class ATL::CComDynamicUnkArray>::GetConnectionInterface(struct _GUID *)
   
   Libraries: Visual Studio 2019 Debug, Visual Studio 2019 Release */

long ATL::
     IConnectionPointImpl<CTextImage,&struct__GUID_const_IID_IVsTextStreamEvents,ATL::CComDynamicUnkArray>
     ::GetConnectionInterface(_GUID *param_1)

{
  long lVar1;
  undefined4 *in_stack_00000008;
  
  if (in_stack_00000008 == (undefined4 *)0x0) {
    lVar1 = -0x7fffbffd;
  }
  else {
    *in_stack_00000008 = 0x7b785574;
    in_stack_00000008[1] = 0x11cf8c82;
    in_stack_00000008[2] = 0xaa000cbc;
    in_stack_00000008[3] = 0xf674ac00;
    lVar1 = 0;
  }
  return lVar1;
}

