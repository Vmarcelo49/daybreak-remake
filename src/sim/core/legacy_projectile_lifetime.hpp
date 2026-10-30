#pragma once
#include <cstdint>
namespace daybreak {
enum class NativeProjectileEventResult {Rejected,Applied,Unsupported};
//42F950 initializes118=1.435A20 holds one temporary reference around scripts;
//5F5E00 releases the object's reference, then435A20 drops its temporary hold.
//Identity160 belongs to a birth, independently of registration150 and owner8.
struct LegacyProjectileLifetime {
 bool managed=false;
 std::uint32_t serial=0,references=1;
 void retain(){++references;}
 bool release(){return --references==0;}
 void begin_script(){if(managed)retain();}
 bool finish_script(bool script_released){if(!managed)return script_released;if(script_released)release();return release();}
};
}
