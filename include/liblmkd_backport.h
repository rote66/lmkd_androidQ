#include <sys/syscall.h>

#if !defined(__NR_SYSCALL_BASE)
// On ARM EABI arch, __NR_SYSCALL_BASE is 0.
#define __NR_SYSCALL_BASE 0
#endif

#if !defined(__NR_pidfd_open)
#define __NR_pidfd_open (__NR_SYSCALL_BASE + 434)
#endif

#if !defined(__NR_pidfd_send_signal)
#define __NR_pidfd_send_signal (__NR_SYSCALL_BASE + 424)
#endif
