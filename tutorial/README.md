# PULP SDK and RISC-V

A version of NanvixOS that runs on RISC-V chips.

### What is PULP SDK?

[PULP SDK](https://github.com/pulp-platform/pulp-sdk) is a set of programs made on top of [GVSoC](https://arxiv.org/abs/2201.08166), a highly configurable, fast and accurate full-platform simulator for RISC-V.

### Why not QEMU?

[QEMU](https://www.qemu.org/) is not as accurate as PULP SDK :)

## Getting started

Create a folder to download all the necessary packages.
Follow [this instructions](https://github.com/riscv-collab/riscv-gnu-toolchain#getting-the-sources) to download RISC-V GNU Toolchain and compile it somewhere (this will be your cross-compilers to RISC-V). The correct compiler is the newlib with the flag to 32-bit RV32GC (this is all explained in the readme file), in the end you should have something like: riscv32-unknown-elf-gcc.

Download PULP SDK [here](https://github.com/pulp-platform/pulp-sdk#getting-started). Export the folder used to compile the RISC-V GCC, using the command below:

```bash
export TARGET=qemu-riscv32
export PULP_RISCV_GCC_TOOLCHAIN=<INSTALL_DIR>
```

<INSTALL_DIR> refers to the folder you compiled the riscv-gnu-toolchain.

After this you can source the file specified in the instructions and run the PULP SDK.

## Running the NanvixOS inside PULP SDK
