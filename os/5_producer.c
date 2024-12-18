// Create a C program to solve the producer consumer problem where producer and consumers are two processes. Producer will produce in a theoretically infinite sized buffer and the consumer will consume from it. Incorporate empty buffer scenario and some waiting time for each process so that their production and consumption can be observed.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

#define BUF_SIZE 3
#define N_ITEMS 10

int main() {
    int p_to_r[2], r_to_p[2], c_to_r[2], r_to_c[2];
    int buf[BUF_SIZE];
    int cnt = 0, h = 0, t = 0;
    pid_t p_pid, c_pid;

    srand(time(NULL));

    if (pipe(p_to_r) == -1 || pipe(r_to_p) == -1 ||
        pipe(c_to_r) == -1 || pipe(r_to_c) == -1) {
        perror("pipe");
        exit(1);
    }

    p_pid = fork();
    if (p_pid < 0) {
        perror("fork");
        exit(1);
    }

    if (p_pid == 0) {
        close(p_to_r[0]); close(r_to_p[1]);
        close(c_to_r[0]); close(c_to_r[1]);
        close(r_to_c[0]); close(r_to_c[1]);

        for (int i = 0; i < N_ITEMS; i++) {
            int itm = rand() % 100;
            int st;

            if (write(p_to_r[1], &itm, sizeof(itm)) <= 0) break;
            if (read(r_to_p[0], &st, sizeof(st)) <= 0) break;

            if (st == 0) {
                printf("P: produced %d\n", itm);
                sleep(1);
            } else {
                printf("P: buffer full, retry %d\n", itm);
                i--;
                sleep(1);
            }
        }

        printf("P: Done\n");
        close(p_to_r[1]); close(r_to_p[0]);
        exit(0);
    }

    c_pid = fork();
    if (c_pid < 0) {
        perror("fork");
        exit(1);
    }

    if (c_pid == 0) {
        close(p_to_r[0]); close(p_to_r[1]);
        close(r_to_p[0]); close(r_to_p[1]);
        close(c_to_r[0]); close(r_to_c[1]);

        for (int i = 0; i < N_ITEMS; i++) {
            int req = 1, itm;

            if (write(c_to_r[1], &req, sizeof(req)) <= 0) break;
            if (read(r_to_c[0], &itm, sizeof(itm)) <= 0) break;

            if (itm != -1) {
                printf("C: consumed %d\n", itm);
                sleep(3);
            } else {
                printf("C: buffer empty, retry\n");
                i--;
                sleep(1);
            }
        }

        printf("C: Done\n");
        close(c_to_r[1]); close(r_to_c[0]);
        exit(0);
    }

    close(p_to_r[1]); close(r_to_p[0]);
    close(c_to_r[1]); close(r_to_c[0]);

    int p_done = 0, c_done = 0;

    while (!p_done || !c_done) {
        fd_set fds;
        FD_ZERO(&fds);
        if (!p_done) FD_SET(p_to_r[0], &fds);
        if (!c_done) FD_SET(c_to_r[0], &fds);

        struct timeval t_out;
        t_out.tv_sec = 1;
        t_out.tv_usec = 0;

        if (select(FD_SETSIZE, &fds, NULL, NULL, &t_out) < 0) {
            perror("select");
            exit(1);
        }

        if (waitpid(p_pid, NULL, WNOHANG) > 0) p_done = 1;
        if (waitpid(c_pid, NULL, WNOHANG) > 0) c_done = 1;

        if (!p_done && FD_ISSET(p_to_r[0], &fds)) {
            int itm, st;
            if (read(p_to_r[0], &itm, sizeof(itm)) > 0) {
                if (cnt < BUF_SIZE) {
                    buf[t] = itm;
                    t = (t + 1) % BUF_SIZE;
                    cnt++;
                    st = 0;
                } else {
                    st = -1;
                }
                write(r_to_p[1], &st, sizeof(st));
            }
        }

        if (!c_done && FD_ISSET(c_to_r[0], &fds)) {
            int req, itm;
            if (read(c_to_r[0], &req, sizeof(req)) > 0) {
                if (cnt > 0) {
                    itm = buf[h];
                    h = (h + 1) % BUF_SIZE;
                    cnt--;
                } else {
                    itm = -1;
                }
                write(r_to_c[1], &itm, sizeof(itm));
            }
        }
    }

    printf("R: Done\n");

    close(p_to_r[0]); close(r_to_p[1]);
    close(c_to_r[0]); close(r_to_c[1]);

    while (wait(NULL) > 0);

    return 0;
}