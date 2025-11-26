#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/cogitator_os.kernel isodir/boot/cogitator_os.kernel
cat > isodir/boot/grub/grub.cfg << EOF
menuentry "cogitator_os" {
	multiboot /boot/cogitator_os.kernel
}
EOF
grub-mkrescue -o cogitator_os.iso isodir
