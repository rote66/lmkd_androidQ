Android Low Memory Killer Daemon For Android P
================================
Tested Android P Kernel-4.4

This is a self-used branch to solve the problem that android-9 stock lmkd doesn't support PSI.

Pick some upstream changes without upgrading android and changing the lmkd.rc file.

The branch that seems to be stable so far is 632f1c5, newer ones still need to be tested.

Using the aosp android-10 source to compile the module, replace the original lmkd and then use the mm command on it to compile the module alone.

[LMK_README](README_lmk.md)