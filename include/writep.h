#ifndef PROCESS_MONITOR_H
#define PROCESS_MONITOR_H

#define MAX_PROCESSES 500
#define MAX_NAME_LENGTH 256

typedef struct {
    char pid[16];
    char name[MAX_NAME_LENGTH];
    float ram_usage;
    float cpu_usage;
    char runtime[32];
} ProcessInfo;

typedef struct {
    ProcessInfo processes[MAX_PROCESSES];
    int count;
} ProcessMonitor;

void print_usage(void);
void init_monitor(ProcessMonitor *monitor);
int update_processes(ProcessMonitor *monitor);
int write_processes_to_file(ProcessMonitor *monitor, int times);

#endif // PROCESS_MONITOR_H