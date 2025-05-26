/*
 * 文件名 : ipc.h
 * 版权 : (C) 2006 by zhonghonglie
 * 功能 : 声明 IPC 机制的函数原型和全局变量
 */
#ifndef IPC_H  // 头文件保护宏，防止重复包含
#define IPC_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#define BUFSZ 256

// IPC 函数原型声明
int get_ipc_id(char* proc_file, key_t key);
char* set_shm(key_t shm_key, int shm_num, int shm_flag);
int set_msq(key_t msq_key, int msq_flag);
int set_sem(key_t sem_key, int sem_val, int sem_flag);
int down(int sem_id);
int up(int sem_id);

/* 信号灯控制用的共用体 */
typedef union semuns {
    int val;
} Sem_uns;

/* 消息结构体 */
typedef struct msgbuf {
    long mtype;
    char mtext[1];
} Msg_buf;

// ===== 以下是关键修改部分 =====
// 将原来的变量定义改为 extern 声明，实际定义放在 ipc.c 中

// 生产消费者共享缓冲区及其相关变量
extern key_t buff_key;  // 改为 extern 声明
extern int buff_num;    // 改为 extern 声明
extern char* buff_ptr;  // 改为 extern 声明

// 生产者放产品位置的共享指针
extern key_t pput_key;  // 改为 extern 声明
extern int pput_num;    // 改为 extern 声明
extern int* pput_ptr;   // 改为 extern 声明

// 消费者取产品位置的共享指针
extern key_t cget_key;  // 改为 extern 声明
extern int cget_num;    // 改为 extern 声明
extern int* cget_ptr;   // 改为 extern 声明

// 生产者有关的信号量
extern key_t prod_key;  // 改为 extern 声明
extern key_t pmtx_key;  // 改为 extern 声明
extern int prod_sem;    // 改为 extern 声明
extern int pmtx_sem;    // 改为 extern 声明

// 消费者有关的信号量
extern key_t cons_key;  // 改为 extern 声明
extern key_t cmtx_key;  // 改为 extern 声明
extern int cons_sem;    // 改为 extern 声明
extern int cmtx_sem;    // 改为 extern 声明

extern int sem_val;     // 改为 extern 声明
extern int sem_flg;     // 改为 extern 声明
extern int shm_flg;     // 改为 extern 声明

#endif // IPC_H