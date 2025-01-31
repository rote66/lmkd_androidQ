LMKD-Wrapper For Android P
================================

**depredated**

This file is designed to use android10's lmkd without compiling and without modifying lmkd.rc in Android9.

init does not allow sh scripts as class core services, so a binary call to LD_PRELOAD is used to run LMKD to solve some function non-existence.

How to compile:

<NDK-PATH>/toolchains/llvm/prebuilt/linux-x86_64/bin/clang -target aarch64-linux-android* -shared -fPIC -o liblmkd_shims liblmkd_shims.c

<NDK-PATH>/toolchains/llvm/prebuilt/linux-x86_64/bin/clang -target aarch64-linux-android* -shared -fPIC -o lmkd lmkd-wrapper.c

put .so file -> /system/lib64
