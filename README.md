# OpenXPUIPC

> **Early development.** The IPC protocol layer is functional, but most FSUIPC offset-to-DataRef mappings are stubs. Expect incomplete simulator data until coverage grows.

An open-source, FSUIPC-compatible IPC bridge plugin for X-Plane 12, written in C++.

OpenXPUIPC aims to allow existing FSUIPC client software — flight tools, hardware interfaces, loggers, and automation scripts — to connect to X-Plane 12. It implements the same inter-process communication interface that FSUIPC exposes, with individual offsets progressively mapped onto X-Plane's native DataRef system.

See [LEGAL.md](LEGAL.md) for the independence statement and offset definition attribution.

---

## How it works

The plugin provides two interfaces that share a common **Bridge** engine:

| Interface  | Transport                                          | Platform       | Clients                                                 |
| ---------- | -------------------------------------------------- | -------------- | ------------------------------------------------------- |
| FSUIPC IPC | Windows `SendMessage` via hidden `UIPCMAIN` window | Windows only   | FSUIPC-compatible apps (FSUIPC.dll, WASM modules, etc.) |
| UDP server | UDP on port `5193`                                 | Cross-platform | XConnect-style clients                                  |

The Bridge maintains a snapshot buffer of FSUIPC offset values, refreshed at ~18 Hz from X-Plane DataRefs inside a flight-loop callback. Read requests are served directly from this snapshot without touching the DataRef layer; write requests are queued and flushed on the next flight-loop tick, keeping all DataRef access safely on X-Plane's main thread.

### Offset coverage

The offset catalog is organized into categories derived from the FSUIPC SDK. The categories and their entries are all present in the reference headers, but most individual offsets currently return stub/zero values — DataRef mappings are being filled in progressively.

`AI_Traffic_TCAS` · `Autopilot` · `Cockpit` · `Controls` · `Electrical` · `Engines` · `Environment` · `Failure` · `Fuel` · `Hydraulics` · `Misc` · `Plane` · `Pos_Attitude` · `Radios` · `Simulation` · `Weather`

---

## Building

### Prerequisites

- Visual Studio 2022 (MSVC, x64)
- Docker (for the library download step below)

### 1. Download third-party libraries

The `PreflightCheckLibs` Docker container downloads pre-built Windows binaries (GLFW, GLEW, FreeType, ImGui, libsodium, libcurl, nlohmann/json) and the X-Plane SDK, then copies them into `third_party/`.

**Command Prompt:**

```cmd
set EXPORT_BASE_DIR=../third_party && docker-compose -f ./PreflightCheckLibs/docker-compose.yml up
```

**PowerShell:**

```powershell
$env:EXPORT_BASE_DIR="../third_party"; docker-compose -f ./PreflightCheckLibs/docker-compose.yml up
```

### 2. Open and build

Open `OpenXPUIPC.sln` in Visual Studio and build the `x64 / Release` configuration.

The output plugin (`.xpl`) is placed in `x64/Release/`.

---

## Installing the plugin

Copy the built `.xpl` file into your X-Plane plugin folder:

```
X-Plane 12/Resources/plugins/OpenXPUIPC/win_x64/OpenXPUIPC.xpl
```

Restart X-Plane. The plugin will appear under **Plugins → OpenXPUIPC** with a status item showing `IPC OK, UDP OK (5193)` when both interfaces have started successfully.

---

## Offset generator

The generated reference headers under `generated/fsuipc_offsets/` are produced by the Python toolchain in `tools/python/`. To regenerate them from an FS-Interrogate export:

```powershell
python tools/python/generators/generate_fsuipc_tables.py research/FSUIPC_FSI.txt
```

The generator uses Jinja2 templates in `tools/python/templates/` and outputs one header per offset category.

---

## Dependencies

| Library                                    | Purpose                 | Location           |
| ------------------------------------------ | ----------------------- | ------------------ |
| [spdlog](https://github.com/gabime/spdlog) | Structured logging      | `spdlog/`          |
| [fmt](https://github.com/fmtlib/fmt)       | String formatting       | `fmt/`             |
| XPlaneUtilities                            | X-Plane logging helpers | `XPlaneUtilities/` |
| X-Plane SDK (XPLM)                         | Plugin API              | via `third_party/` |

---

## License

LGPL-3.0-or-later — see [LICENSE](LICENSE).
