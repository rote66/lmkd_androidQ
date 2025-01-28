Android Low Memory Killer Daemon For Android Q
================================

This is a self-used branch to solve the problem that android10 stock lmkd doesn't support adjusting PSI-related parameters via prop, which leads to abnormal usage on low-configuration devices.

Pick some upstream changes without upgrading android and changing the lmkd.rc file.

The branch that seems to be stable so far is 632f1c5, newer ones still need to be tested.

Using the aosp android-10 source to compile the module, replace the original lmkd and then use the mm command on it to compile the module alone.

[LMK_README](README_lmk.md)