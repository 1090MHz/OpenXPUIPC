// SPDX-License-Identifier: LGPL-3.0-or-later
// Wire protocol definitions shared between plugin and client tools
#pragma once

#include <cstddef>
#include <cstdint>

namespace xpuipc {

// UDP action codes used by the XConnect-style UDP server.
constexpr uint32_t ACTION_READ      = 1;
constexpr uint32_t ACTION_WRITE     = 2;
constexpr uint32_t ACTION_READTRUE  = 3;
constexpr uint32_t ACTION_WRITETRUE = 4;

// Native FSUIPC IPC action codes used by the shared-memory UIPCMAIN server.
// IMPORTANT: FSUIPC 64-bit READ uses action 4, so IPC code must not use
// ACTION_WRITETRUE for shared-memory request decoding.
constexpr uint32_t IPC_READ32 = 1;
constexpr uint32_t IPC_WRITE  = 2;
constexpr uint32_t IPC_READ64 = 4;

constexpr int      UDP_PORT         = 5193;
constexpr size_t   MAX_PACKET       = 0x7F00;

#pragma pack(push, 1)
struct ReadHeader  { uint32_t action; uint32_t offset; uint32_t size; };
struct WriteHeader { uint32_t action; uint32_t offset; uint32_t size; };
#pragma pack(pop)

} // namespace xpuipc
