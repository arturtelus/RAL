# RAL

RAII for OpenAL (+utilities). C++ framework for OpenAL-soft and OpenAL 1.1.

# Features

- RAII playback and capture device handles (ral::Device, ral::CaptureDevice)
- RAII context handle (ral::Context)
- Manage (1..n) openal buffers with error checking, prop getter, data copying (ral::Buffers)
- Manage (1..n) openal sources with error checking, prop getters, overloaded prop setters, aux playback functions (ral::Sources)
- Listener prop getters and oveloaded setters with error checking (ral::Listener)
- AL and ALC error checing in debug bulids
- Simple wav loader

# Building

- CMake 3.15
- C++17

## Project integration

- todo

## TODO

- Unit testing
- Project integration features
- CMake configs
- Creative OpenAL support
- Short examples

# Links

[OpenAL 1.1 Specification](https://www.openal.org/documentation/openal-1.1-specification.pdf)

[OpenAL 1.1 Guide](https://www.openal.org/documentation/OpenAL_Programmers_Guide.pdf)

[OpenAL](https://www.openal.org/)

[OpenAL-Soft](https://github.com/kcat/openal-soft)

[OpenAL by Creative Technology Limited](https://www.openal.org/downloads/)