// ============================================
// Address:  0x00410420
// Original: basic_string<char,std::char_traits<char>,std::allocator<char>_>
// Status:   unreviewed
// ============================================

/* Library Function - Single Match
    public: __thiscall std::basic_string<char,struct std::char_traits<char>,class
   std::allocator<char> >::basic_string<char,struct std::char_traits<char>,class
   std::allocator<char> >(class std::basic_string<char,struct std::char_traits<char>,class
   std::allocator<char> > const &)

   Library: Visual Studio 2003 Debug */

basic_string<char, std::char_traits<char>, std::allocator<char> _>
    *__thiscall std::basic_string<char, std::char_traits<char>, std::allocator<char> _>::
        basic_string<char, std::char_traits<char>, std::allocator<char> _>(
            basic_string<char, std::char_traits<char>, std::allocator<char> _> *this,
            basic_string<char, struct_std::char_traits<char>, class_std::allocator<char> _>
                *param_1)

{
    basic_string<char, std::char_traits<char>, std::allocator<char> _> *pbVar1;

    pbVar1 = this;
    allocator<>(param_1);
    _String_val<>(pbVar1);
    basic_string<char, std::char_traits<char>, std::_DebugHeapAllocator<char> _>::_Tidy(
        (basic_string<char, std::char_traits<char>, std::_DebugHeapAllocator<char> _> *)this,
        false,
        0);
    basic_string<char, std::char_traits<char>, std::_DebugHeapAllocator<char> _>::assign(
        (basic_string<char, std::char_traits<char>, std::_DebugHeapAllocator<char> _> *)this,
        (basic_string<char, struct_std::char_traits<char>, class_std::_DebugHeapAllocator<char> _>
             *)param_1,
        0,
        0xffffffff);
    return this;
}
