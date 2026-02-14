#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int pid;
    char cpu[10];
    char mem[10];
    char vsz[16];
    char rss[16];
    char tty[16];
    char stat[10];
    char start[16];
    char time[16];
    char command[256];
} ProcessInfo;

ProcessInfo aux_data[10000];

int main() {
    system("ps aux > x1.txt");
    system("ps -eLf > x2.txt");

    FILE *f1 = fopen("x1.txt", "r");
    FILE *f2 = fopen("x2.txt", "r");
    FILE *fout = fopen("merged.txt", "w");

    if (f1 == NULL || f2 == NULL || fout == NULL) {
        printf("Error opening files.\n");
        return 1;
    }

    char buffer[1024];

    fgets(buffer, sizeof(buffer), f1);
    fgets(buffer, sizeof(buffer), f2);

    int aux_count = 0;
    char user[32];

    while (fscanf(f1, "%s %d %s %s %s %s %s %s %s %s %[^\n]", 
                  user, &aux_data[aux_count].pid, aux_data[aux_count].cpu, 
                  aux_data[aux_count].mem, aux_data[aux_count].vsz, 
                  aux_data[aux_count].rss, aux_data[aux_count].tty, 
                  aux_data[aux_count].stat, aux_data[aux_count].start, 
                  aux_data[aux_count].time, aux_data[aux_count].command) == 11) {
        aux_count++;
    }

    fprintf(fout, "UID      PID   PPID   LWP C NLWP %%CPU %%MEM   VSZ    RSS TTY      STAT START   TIME    COMMAND\n");

    char uid[32], ppid[16], lwp[16], c[16], nlwp[16], stime[16], tty_elf[16], time_elf[16], cmd[256];
    int pid_elf;

    while (fscanf(f2, "%s %d %s %s %s %s %s %s %s %[^\n]", 
                  uid, &pid_elf, ppid, lwp, c, nlwp, stime, tty_elf, time_elf, cmd) == 10) {
        
        for (int i = 0; i < aux_count; i++) {
            if (aux_data[i].pid == pid_elf) {
                fprintf(fout, "%-8s %-5d %-6s %-3s %-1s %-4s %-4s %-4s %-6s %-5s %-8s %-4s %-7s %-7s %s\n",
                        uid, pid_elf, ppid, lwp, c, nlwp,
                        aux_data[i].cpu, aux_data[i].mem, aux_data[i].vsz,
                        aux_data[i].rss, aux_data[i].tty, aux_data[i].stat,
                        aux_data[i].start, aux_data[i].time, aux_data[i].command);
                break;
            }
        }
    }

    fclose(f1);
    fclose(f2);
    fclose(fout);

    system("cat merged.txt");
    system("rm x1.txt x2.txt");

    return 0;
}