#!/bin/bash

prepare() {
    if [[ -z "$CROSS_COMPILE" ]]; then
      echo "CROSS_COMPILE must be set! Quitting..."
      exit 1
    fi
    if [[ ! -d bin ]]; then
      mkdir bin
    fi
    rm -rf bin/*
    if [[ ! -d bin/wario ]]; then
      mkdir bin/wario
    fi
}

build_variant() {
  CROSS_COMPILE=arm-kindlepw2-linux-gnueabi- ARCH=arm TYPE="$2" make distclean
  CROSS_COMPILE=arm-kindlepw2-linux-gnueabi- ARCH=arm TYPE="$2" make "$1"
  CROSS_COMPILE=arm-kindlepw2-linux-gnueabi- ARCH=arm TYPE="$2" make -j8
}

main() {
  prepare
  build_variant imx60_wario_bist_config bist
  mv u-boot.bin bin/wario/uboot_2009-08-lab126_wario_stock_bist.bin
  build_variant imx60_wario_config prod
  mv u-boot.bin bin/wario/uboot_2009-08-lab126_wario_stock_prod.bin
  build_variant imx60_wario_mfgtool_kboot_config mfgtool
  mv u-boot.bin bin/wario/uboot_2009-08-lab126_wario_stock_mfgtool_kboot.bin
  build_variant imx60_wario_mfgtool_config mfgtool
  mv u-boot.bin bin/wario/uboot_2009-08-lab126_wario_stock_mfgtool.bin
  build_variant imx60_wario_fastboot_config prod
  mv u-boot.bin bin/wario/uboot-2009_08_lab126-wario_usb_fastboot.bin
  build_variant imx60_wario_diags_config prod
  mv u-boot.bin bin/wario/uboot_2009-08-lab126_wario_usb_diags.bin
}

main