#pragma once
namespace daybreak {
//5278CF..527956, Tomitake character6/weapon2 slot6 prefix, after the+A0 gate.
//The caller supplies one execution per actual handler visit. Full recovered
//bodies already execute this prefix and must not receive another decrement.
inline void advance_native_actor_spine_prefix(float& value){
 if(value>0){value=value-10.f;if(value<0)value=0;}
 if(value<0){value=value+10.f;if(value>0)value=0;}
}
}
