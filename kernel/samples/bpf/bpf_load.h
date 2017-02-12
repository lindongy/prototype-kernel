/* Copy of samples/bpf/bpf_load.h */
#ifndef __BPF_LOAD_H
#define __BPF_LOAD_H

#include "libbpf.h"

#define MAX_MAPS 32
#define MAX_PROGS 32

/* Strange: This BPF_LOG_BUF_SIZE gets defined when compiling
 *  tools/lib/bpf/bpf.c into bpf.o, via tools/lib/bpf/bpf.h
 * But tools/lib/bpf/bpf.h does not get included
 */
//#ifndef BPF_LOG_BUF_SIZE
//#define BPF_LOG_BUF_SIZE 65536
//#endif

extern int map_fd[MAX_MAPS];
extern int prog_fd[MAX_PROGS];
extern int event_fd[MAX_PROGS];
extern char bpf_log_buf[BPF_LOG_BUF_SIZE];
extern int prog_cnt;

/* parses elf file compiled by llvm .c->.o
 * . parses 'maps' section and creates maps via BPF syscall
 * . parses 'license' section and passes it to syscall
 * . parses elf relocations for BPF maps and adjusts BPF_LD_IMM64 insns by
 *   storing map_fd into insn->imm and marking such insns as BPF_PSEUDO_MAP_FD
 * . loads eBPF programs via BPF syscall
 *
 * One ELF file can contain multiple BPF programs which will be loaded
 * and their FDs stored stored in prog_fd array
 *
 * returns zero on success
 */
int load_bpf_file(char *path);

void read_trace_pipe(void);
struct ksym {
	long addr;
	char *name;
};

int load_kallsyms(void);
struct ksym *ksym_search(long key);
int set_link_xdp_fd(int ifindex, int fd);
#endif