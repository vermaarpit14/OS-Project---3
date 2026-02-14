#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to store information specifically from 'ps aux'
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

// Array to store up to 10000 processes
ProcessInfo aux_data[10000];

int main() {
    // 1. Generate temporary files
    system("ps aux --no-headers > x1.txt");
    system("ps -eLf --no-headers > x2.txt");

    FILE *f1 = fopen("x1.txt", "r");
    FILE *f2 = fopen("x2.txt", "r");
    FILE *fout = fopen("AI_merged.txt", "w");

    if (f1 == NULL || f2 == NULL || fout == NULL) {
        perror("Error opening files");
        return 1;
    }

    // 2. Parse x1.txt (ps aux) into the struct array
    int aux_count = 0;
    char user_dummy[32];
    while (aux_count < 10000 && fscanf(f1, "%s %d %s %s %s %s %s %s %s %s %[^\n]", 
           user_dummy, &aux_data[aux_count].pid, aux_data[aux_count].cpu, 
           aux_data[aux_count].mem, aux_data[aux_count].vsz, 
           aux_data[aux_count].rss, aux_data[aux_count].tty, 
           aux_data[aux_count].stat, aux_data[aux_count].start, 
           aux_data[aux_count].time, aux_data[aux_count].command) == 11) {
        aux_count++;
    }

    // 3. Print Header to merged.txt
    fprintf(fout, "%-10s %-5s %-5s %-5s %-2s %-4s %-4s %-4s %-8s %-6s %-6s %-5s %-7s %-7s %s\n",
            "UID", "PID", "PPID", "LWP", "C", "NLWP", "%CPU", "%MEM", "VSZ", "RSS", "TTY", "STAT", "START", "TIME", "COMMAND");

    // 4. Read x2.txt (ps -eLf) and merge with stored aux_data
    char uid[32], ppid[16], lwp[16], c_val[16], nlwp[16], stime[16], tty_elf[16], time_elf[16], cmd_elf[256];
    int pid_elf;

    while (fscanf(f2, "%s %d %s %s %s %s %s %s %s %[^\n]", 
                  uid, &pid_elf, ppid, lwp, c_val, nlwp, stime, tty_elf, time_elf, cmd_elf) == 10) {
        
        // Find the matching PID in our stored aux_data
        for (int i = 0; i < aux_count; i++) {
            if (aux_data[i].pid == pid_elf) {
                fprintf(fout, "%-10s %-5d %-5s %-5s %-2s %-4s %-4s %-4s %-8s %-6s %-6s %-5s %-7s %-7s %s\n",
                        uid, pid_elf, ppid, lwp, c_val, nlwp,
                        aux_data[i].cpu, aux_data[i].mem, aux_data[i].vsz,
                        aux_data[i].rss, aux_data[i].tty, aux_data[i].stat,
                        aux_data[i].start, aux_data[i].time, aux_data[i].command);
                break; 
            }
        }
    }

    // 5. Cleanup and Display
    fclose(f1);
    fclose(f2);
    fclose(fout);


    // Output result to terminal
    system("cat AI_merged.txt");

    // Remove temporary data files
    system("rm x1.txt x2.txt");

    return 0;
}