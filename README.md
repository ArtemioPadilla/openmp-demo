# OpenMP Demo

Simple OpenMP examples for macOS.

## Install

```bash
brew install gcc
```

## Build & Run

```bash
make RegionesParalelas
./RegionesParalelas

make DefiniendoNHilos
./DefiniendoNHilos
```

## Control Threads

```bash
OMP_NUM_THREADS=4 ./RegionesParalelas
```

## Clean

```bash
make clean
```
