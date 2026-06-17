# Independence Statement

This project is an independent implementation of the FSUIPC IPC protocol for X-Plane, written from publicly available specifications and SDK documentation. It aims to be compatible with FSUIPC/XPUIPC client software in the same way any conforming implementation of a published protocol would be — by using the same inter-process communication format, not by using any code or design from existing implementations.

The original XPUIPC plugin by Torsten Knoll is closed-source and has not been actively maintained, leaving the X-Plane community without a supported path forward as X-Plane and its SDK have evolved. OpenXPUIPC exists to fill that gap with an open, community-maintainable implementation. Behavioural compatibility was achieved solely by implementing the client-facing protocol as documented in Pete Dowson's published FSUIPC SDK, which is distributed freely to developers for exactly this purpose.

The protocol specification — including constants, window class name, registered message name, and data structures — is part of Pete Dowson's published FSUIPC client API. As an interface specification, it is not subject to copyright protection; any conforming implementation must reproduce it.

The plugin architecture and the mapping of X-Plane DataRefs to FSUIPC offsets are original work authored for this project, derived through research and runtime testing against a live simulator.

## Offset Definitions

Generated offset tables in this repository are derived from FS-Interrogate, a developer tool distributed as part of the FSUIPC SDK by Peter Dowson. FS-Interrogate is free for use in both freeware and payware applications.
