# OpenMP Demo

Simple OpenMP examples for macOS.

## Install

```bash
brew install gcc
```

## Programs

| File | Description |
|------|-------------|
| `RegionesParalelas.cpp` | Basic parallel regions |
| `DefiniendoNHilos.cpp` | Custom thread count |
| `p_sum.cpp` | Parallel array sum |
| `system_info.cpp` | Show system parallelism info |

## Build & Run

```bash
make <program>
./<program>
```

Example:
```bash
make p_sum && ./p_sum
```

## Control Threads

```bash
OMP_NUM_THREADS=4 ./p_sum
```

## Clean

```bash
make clean
```
