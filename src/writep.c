#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <getopt.h>
#include <unistd.h>
#include "include/writep.h"

void init_monitor(ProcessMonitor *monitor) {
    monitor->count = 0;
}

int update_processes(ProcessMonitor *monitor) {
    FILE *fp;
    char command[1024];
    snprintf(command, sizeof(command),
        "ps -eo pid,pcpu,pmem,etime,comm --sort=-pcpu | tail -n +2");
    
    fp = popen(command, "r");
    if (!fp) {
        perror("Failed to run ps command");
        return -1;
    }
    
    monitor->count = 0;
    char line[1024];
    
    while (fgets(line, sizeof(line), fp) &&
           monitor->count < MAX_PROCESSES) {
        ProcessInfo *proc = &monitor->processes[monitor->count];
        
        if (sscanf(line, "%15s %f %f %31s %255[^\n]",
                   proc->pid,
                   &proc->cpu_usage,
                   &proc->ram_usage,
                   proc->runtime,
                   proc->name) == 5) {
            char *start = proc->name;
            char *end = start + strlen(start) - 1;
            while (start <= end && (*start == ' ' || *start == '\t')) start++;
            while (end > start && (*end == ' ' || *end == '\t' || *end == '\n')) end--;
            *(end + 1) = '\0';
            memmove(proc->name, start, end - start + 2);
            monitor->count++;
        }
    }
    
    pclose(fp);
    return monitor->count;
}

int write_processes_to_file(ProcessMonitor *monitor, int times) {
    FILE *fp = fopen("./info/processes.info", "w");
    if (!fp) {
        perror("Failed to open processes.info");
        return -1;
    }
    
    fprintf(fp, "PID\tCPU%%\tRAM%%\tRUNTIME\tNAME\n");

    int loop_limit = (times < monitor->count) ? times : monitor->count;

    for (int i = 0; i < loop_limit; i++) {
        fprintf(fp, "%s\t%.1f\t%.1f\t%s\t%s\n",
                monitor->processes[i].pid,
                monitor->processes[i].cpu_usage,
                monitor->processes[i].ram_usage,
                monitor->processes[i].runtime,
                monitor->processes[i].name);
    }
    
    fclose(fp);
    return 0;
}

void print_usage(void)
{
	printf("\t -p : must be followed by a number\n");
	return;
}

int main(int argc, char *argv[]) {
    int c;
    int times = -1;

    while ((c = getopt(argc, argv, "p:")) != -1) {
    switch(c) {    
        case 'p':
			times = atoi(optarg);
			break;
		case '?':
			print_usage();
			return -1;
    }
    }

    if (times == -1) {
        print_usage();
        return -1;
    }

    ProcessMonitor monitor;
    init_monitor(&monitor);
    
    if (update_processes(&monitor) > 0) {
        write_processes_to_file(&monitor, times);
    }
    return 0;
}