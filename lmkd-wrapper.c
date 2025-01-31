#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(){
    int ret, enforce_status;
    const char *msg;
    int kmsg = open("/dev/kmsg", O_WRONLY);
    if (kmsg == -1) {
        perror("Failed to open /dev/kmsg");
        return 1;
    }
    
    FILE *selinux_file = fopen("/sys/fs/selinux/enforce", "r");
    if (selinux_file == NULL) {
    	msg = "lmkd-wrapper: Failed to read SELinux enforce status.\n";
        write(kmsg, msg, strlen(msg));
    }
    
    fscanf(selinux_file, "%d", &enforce_status);
    fclose(selinux_file);

    if (enforce_status != 0) {
    	msg = "lmkd-wrapper: SELinux is not permissive, switching to permissive...\n";
        write(kmsg, msg, strlen(msg));
        ret = system("/system/bin/setenforce 0");
        if (ret == 0) {
                msg = "lmkd-wrapper: SELinux switching successfully.\n";
		write(kmsg, msg, strlen(msg));
		fflush(stdout);
	    	} else {
		char error_message[50];
		snprintf(error_message, sizeof(error_message), "lmkd-wrapper: SELinux failed to switch permissive, return code: %d\n", ret);
		write(kmsg, error_message, strlen(error_message));
		fflush(stdout);
	    }
    }

    if (access("/proc/pressure/memory", F_OK) == 0) {
        system("/system/bin/chown system:system /proc/pressure/memory");
        system("/system/bin/chmod 0664 /proc/pressure/memory");
        msg = "lmkd-wrapper: Modified permissions for /proc/pressure/memory.\n";
        write(kmsg, "lmkd-wrapper: Modified permissions for /proc/pressure/memory.\n", 70);
    } else {
    	msg = "lmkd-wrapper: /proc/pressure/memory does not exist.\n";
        write(kmsg, msg, strlen(msg));
    }
    
    setenv("LD_PRELOAD", "/system/lib64/liblmkd_shims.so", 1);
    msg = "lmkd-wrapper: Starting lmkd_psi...\n";
    write(kmsg, msg, strlen(msg));
    fflush(stdout);

    ret = system("/system/bin/lmkd_psi");

    if (ret == 0) {
        write(kmsg, "lmkd-wrapper: lmkd started successfully.\n", 41);
        fflush(stdout);
    } else {
        char error_message[50];
        snprintf(error_message, sizeof(error_message), "lmkd-wrapper: Failed to start lmkd, return code: %d\n", ret);
        write(kmsg, error_message, strlen(error_message));
        fflush(stdout);
    }

    close(kmsg);

    return 0;
}
