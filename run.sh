#!/bin/sh
set -e

# Clean previous build artifacts
./clean.sh

# Build the OS, create ISO, and run in QEMU
# qemu.sh sources iso.sh, which sources build.sh, which sources headers.sh
./qemu.sh
