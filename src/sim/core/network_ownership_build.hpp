#pragma once
// Shared HUMAN/CPU editing uses the completed protocol7 model/UDP/GPU gates.
// Explicit0 retains the earlier protocol6 configuration for archived probes.
#ifndef DAYBREAK_ENABLE_NETWORK_OWNERSHIP
#define DAYBREAK_ENABLE_NETWORK_OWNERSHIP 1
#endif
#ifndef DAYBREAK_ENABLE_NETWORK_SELECTION_OPTIONS
#define DAYBREAK_ENABLE_NETWORK_SELECTION_OPTIONS 1
#endif
#ifndef DAYBREAK_ENABLE_NETWORK_NATIVE_INPUT
#define DAYBREAK_ENABLE_NETWORK_NATIVE_INPUT 1
#endif
namespace daybreak::net {
inline constexpr bool shared_network_ownership_enabled=DAYBREAK_ENABLE_NETWORK_OWNERSHIP!=0;
inline constexpr bool shared_network_selection_options_enabled=shared_network_ownership_enabled&&DAYBREAK_ENABLE_NETWORK_SELECTION_OPTIONS!=0;
inline constexpr bool shared_network_native_input_enabled=shared_network_selection_options_enabled&&DAYBREAK_ENABLE_NETWORK_NATIVE_INPUT!=0;
inline constexpr unsigned lobby_protocol_version=shared_network_native_input_enabled?9:shared_network_ownership_enabled?(shared_network_selection_options_enabled?8:7):6;
}
