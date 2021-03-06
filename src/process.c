#include "process.h"

int cmp(const void *_a, const void *_b) {
    struct PCB *a = (struct PCB *) _a;
    struct PCB *b = (struct PCB *) _b;
    if (a->r < b->r)
        return -1;
    if (a->r > b->r)
        return 1;
    return 0;
}

void setCPU(pid_t pid, int i) {

    cpu_set_t mask;
    CPU_ZERO(&mask);
    CPU_SET(i, &mask);

    if (sched_setaffinity(pid, sizeof(mask), &mask) == -1) {
        fprintf(stderr, "Error: fail to set cpu, %s\n", strerror(errno));
        exit(1);
    }

}

void setPriority(pid_t pid, int p) {

    struct sched_param param;
    param.sched_priority = p;

    if (sched_setscheduler(pid, SCHED_FIFO, &param) == -1) {
        fprintf(stderr, "Error: fail to set priority, %s\n", strerror(errno));
        exit(1);
    }

}

void forkChild(struct PCB *p) {

    p->pid = fork();

    /* error */
    if (p->pid == -1) {
        fprintf(stderr, "Error: fail to fork, %s\n", strerror(errno));
        exit(1);
    }
    
    /* child */
    if (p->pid == 0) {
        for (int i = 0; i < p->t; i++)
            UNIT_OF_TIME
        exit(0);
    }

    /* parent */
    setCPU(p->pid, 1);
    setPriority(p->pid, 1); // lowest priority

}