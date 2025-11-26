#!/bin/sh
set -e
. ./iso.sh

ARCH=$(./target-triplet-to-arch.sh $HOST)
if [ "$ARCH" = "i686" ]; then
  QEMU=qemu-system-i386
else
  QEMU=qemu-system-$ARCH
fi

$QEMU -cdrom cogitator_os.iso
