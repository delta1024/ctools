#!/usr/bin/env sh

LIB_SRC=CtoolsLib

build_arch_package() {
    local makepkg_flags='--skipinteg --clean'
    makepkg $makepkg_flags
}


main() {
    pushd $LIB_SRC
    build_arch_package
    popd
    mkdir -p target/packages
    mv $LIB_SRC/*.pkg.tar.zst target/packages
}

main
