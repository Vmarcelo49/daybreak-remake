#pragma once
namespace daybreak {
// 0x64e360: sibling first, then child. Host supplies matrix operations so
// D3DX arithmetic fidelity can be verified independently of traversal.
template<class Host>
void update_frame(unsigned frame,unsigned parent,Host& host){
    const auto extra=host.extra(frame);
    if(extra)host.multiply_local(frame,extra);
    if(parent)host.combine(frame,parent);else host.copy_local(frame);
    const auto sibling=host.sibling(frame);
    if(sibling)update_frame(sibling,parent,host);
    const auto child=host.child(frame);
    if(child)update_frame(child,host.combined(frame),host);
}
}
