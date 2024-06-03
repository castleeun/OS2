//20211067 전성은
//2-1,2-2 했습니다.
//2-3 미완성

//2-1
/*
#include <stdio.h>
#include <stdlib.h>
// 프로세스 구조체
typedef struct Process {
    int pid;
    char type; // 'F' for Foreground, 'B' for Background
    struct Process* next;
} Process;

// 연결 리스트 노드 구조체
typedef struct ListNode {
    Process* head;
    int length;
    struct ListNode* next;
} ListNode;

// 스택 노드 구조체
typedef struct StackNode {
    ListNode* list;
    struct StackNode* next;
} StackNode;

// Dynamic Queue 구조체
typedef struct {
    StackNode* top;
    int threshold;
    StackNode* promote_node;
} DynamicQueue;

// 프로세스 생성
Process* create_process(int pid, char type) {
    Process* new_process = (Process*)malloc(sizeof(Process));
    new_process->pid = pid;
    new_process->type = type;
    new_process->next = NULL;
    return new_process;
}

// 리스트 노드 생성
ListNode* create_list_node() {
    ListNode* new_list = (ListNode*)malloc(sizeof(ListNode));
    new_list->head = NULL;
    new_list->length = 0;
    new_list->next = NULL;
    return new_list;
}

// 스택 노드 생성
StackNode* create_stack_node() {
    StackNode* new_stack = (StackNode*)malloc(sizeof(StackNode));
    new_stack->list = create_list_node();
    new_stack->next = NULL;
    return new_stack;
}

// Dynamic Queue 초기화
DynamicQueue* create_dynamic_queue(int threshold) {
    DynamicQueue* queue = (DynamicQueue*)malloc(sizeof(DynamicQueue));
    queue->top = create_stack_node();
    queue->threshold = threshold;
    queue->promote_node = queue->top;
    return queue;
}

// enqueue 함수
void enqueue(DynamicQueue* queue, Process* process) {
    StackNode* stack = queue->top;
    stack->list->length++;
    process->next = stack->list->head;
    stack->list->head = process;

    // split_n_merge 호출 필요
}

// dequeue 함수
Process* dequeue(DynamicQueue* queue) {
    if (queue->top == NULL) {
        return NULL;
    }

    ListNode* list = queue->top->list;
    if (list->head == NULL) {
        return NULL;
    }

    Process* process = list->head;
    list->head = process->next;
    list->length--;

    if (list->length == 0) {
        StackNode* temp = queue->top;
        queue->top = queue->top->next;
        free(temp->list);
        free(temp);
    }

    return process;
}

// promote 함수
void promote(DynamicQueue* queue) {
    // 프로세스를 상위 리스트로 이동시키는 코드 필요
}

// split_n_merge 함수
void split_n_merge(DynamicQueue* queue) {
    // 리스트 길이가 임계치를 넘을 경우 리스트를 분할하고 병합하는 코드 필요
}

// Wait Queue 구조체와 함수 정의
typedef struct WaitQueueNode {
    Process* process;
    int wait_time;
    struct WaitQueueNode* next;
} WaitQueueNode;

typedef struct {
    WaitQueueNode* head;
} WaitQueue;

WaitQueue* create_wait_queue() {
    WaitQueue* wq = (WaitQueue*)malloc(sizeof(WaitQueue));
    wq->head = NULL;
    return wq;
}

void add_to_wait_queue(WaitQueue* wq, Process* process, int wait_time) {
    WaitQueueNode* node = (WaitQueueNode*)malloc(sizeof(WaitQueueNode));
    node->process = process;
    node->wait_time = wait_time;
    node->next = wq->head;
    wq->head = node;
}

// 큐 상태 출력 함수
void print_queue(DynamicQueue* dq, WaitQueue* wq) {
    StackNode* stack = dq->top;
    printf("---------------------------\n");
    printf("DQ: ");
    while (stack != NULL) {
        ListNode* list = stack->list;
        Process* process = list->head;
        printf("[");
        while (process != NULL) {
            printf("%d%c ", process->pid, process->type);
            process = process->next;
        }
        printf("] ");
        stack = stack->next;
    }
    printf("(bottom/top)\n");
    printf("---------------------------\n");
    printf("WQ: [");
    WaitQueueNode* wq_node = wq->head;
    while (wq_node != NULL) {
        printf("%d%c:%d ", wq_node->process->pid, wq_node->process->type, wq_node->wait_time);
        wq_node = wq_node->next;
    }
    printf("]\n");
    printf("---------------------------\n");
}

int main() {
    DynamicQueue* dq = create_dynamic_queue(3);
    WaitQueue* wq = create_wait_queue();

    enqueue(dq, create_process(1, 'B'));
    enqueue(dq, create_process(2, 'B'));
    enqueue(dq, create_process(7, 'B'));
    enqueue(dq, create_process(4, 'B'));

    print_queue(dq, wq);

    Process* p1 = dequeue(dq);
    if (p1) {
        printf("Running: [%d%c]\n", p1->pid, p1->type);
        free(p1);
    }

    print_queue(dq, wq);

    enqueue(dq, create_process(11, 'F'));
    enqueue(dq, create_process(3, 'F'));
    enqueue(dq, create_process(6, 'B'));
    enqueue(dq, create_process(8, 'B'));

    print_queue(dq, wq);

    Process* p2 = dequeue(dq);
    if (p2) {
        printf("Running: [%d%c]\n", p2->pid, p2->type);
        free(p2);
    }

    print_queue(dq, wq);

    add_to_wait_queue(wq, create_process(15, 'F'), 2);
    add_to_wait_queue(wq, create_process(10, 'B'), 5);

    print_queue(dq, wq);

    return 0;
}
*/

//2-2
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Process {
    int pid;
    char type; 
    int burst_time;
    int remaining_time;
    struct Process* next;
} Process;

typedef struct ListNode {
    Process* head;
    int length;
    struct ListNode* next;
} ListNode;

typedef struct StackNode {
    ListNode* list;
    struct StackNode* next;
} StackNode;

typedef struct {
    StackNode* top;
    int threshold;
    StackNode* promote_node;
} DynamicQueue;

typedef struct WaitQueueNode {
    Process* process;
    int wait_time;
    struct WaitQueueNode* next;
} WaitQueueNode;

typedef struct {
    WaitQueueNode* head;
} WaitQueue;

DynamicQueue* dq;
WaitQueue* wq;

Process* create_process(int pid, char type, int burst_time) {
    Process* new_process = (Process*)malloc(sizeof(Process));
    new_process->pid = pid;
    new_process->type = type;
    new_process->burst_time = burst_time;
    new_process->remaining_time = burst_time;
    new_process->next = NULL;
    return new_process;
}

ListNode* create_list_node() {
    ListNode* new_list = (ListNode*)malloc(sizeof(ListNode));
    new_list->head = NULL;
    new_list->length = 0;
    new_list->next = NULL;
    return new_list;
}

StackNode* create_stack_node() {
    StackNode* new_stack = (StackNode*)malloc(sizeof(StackNode));
    new_stack->list = create_list_node();
    new_stack->next = NULL;
    return new_stack;
}

DynamicQueue* create_dynamic_queue(int threshold) {
    DynamicQueue* queue = (DynamicQueue*)malloc(sizeof(DynamicQueue));
    queue->top = create_stack_node();
    queue->threshold = threshold;
    queue->promote_node = queue->top;
    return queue;
}

WaitQueue* create_wait_queue() {
    WaitQueue* wq = (WaitQueue*)malloc(sizeof(WaitQueue));
    wq->head = NULL;
    return wq;
}

void add_to_wait_queue(WaitQueue* wq, Process* process, int wait_time) {
    WaitQueueNode* node = (WaitQueueNode*)malloc(sizeof(WaitQueueNode));
    node->process = process;
    node->wait_time = wait_time;
    node->next = wq->head;
    wq->head = node;
}

void split_n_merge(DynamicQueue* queue, ListNode* list);

void enqueue(DynamicQueue* queue, Process* process) {
    StackNode* stack = queue->top;
    stack->list->length++;
    process->next = stack->list->head;
    stack->list->head = process;

    split_n_merge(queue, stack->list); 
}



Process* dequeue(DynamicQueue* queue) {
    if (queue->top == NULL) {
        return NULL;
    }

    ListNode* list = queue->top->list;
    if (list->head == NULL) {
        return NULL;
    }

    Process* process = list->head;
    list->head = process->next;
    list->length--;

    if (list->length == 0) {
        StackNode* temp = queue->top;
        queue->top = queue->top->next;
        free(temp->list);
        free(temp);
    }

    return process;
}

void promote(DynamicQueue* queue) {
    StackNode* current_stack = queue->top;
    StackNode* prev_stack = NULL;

    while (current_stack->next != NULL) {
        ListNode* current_list = current_stack->list;

        if (current_list->length > queue->threshold) {
            if (prev_stack == NULL) {
                queue->top = current_stack->next;
            }
            else {
                prev_stack->next = current_stack->next;
            }

            StackNode* next_stack = current_stack->next;
            current_stack->next = next_stack->next;
            next_stack->next = current_stack;
            if (prev_stack == NULL) {
                queue->top = next_stack;
            }
            else {
                prev_stack->next = next_stack;
            }
        }

        prev_stack = current_stack;
        current_stack = current_stack->next;
    }
}

void split_n_merge(DynamicQueue* queue, ListNode* list) {
    if (list->length > queue->threshold) {
        ListNode* second_list = create_list_node();
        int half_length = list->length / 2;
        Process* current_process = list->head;
        for (int i = 0; i < half_length - 1; ++i) {
            current_process = current_process->next;
        }
        second_list->head = current_process->next;
        current_process->next = NULL;
        list->length = half_length;
        second_list->length = half_length;

        StackNode* new_stack = create_stack_node();
        new_stack->list = second_list;
        new_stack->next = queue->top->next;
        queue->top->next = new_stack;
    }
}


void print_queue(DynamicQueue* dq, WaitQueue* wq) {
    StackNode* stack = dq->top;
    printf("---------------------------\n");
    printf("DQ: ");
    while (stack != NULL) {
        ListNode* list = stack->list;
        Process* process = list->head;
        if (stack->next == NULL) {
            printf("P => ");
        }
        printf("[");
        while (process != NULL) {
            printf("%d%c ", process->pid, process->type);
            process = process->next;
        }
        printf("] ");
        stack = stack->next;
    }
    printf("(bottom/top)\n");

    printf("---------------------------\n");
    printf("WQ: [");
    WaitQueueNode* wq_node = wq->head;
    while (wq_node != NULL) {
        printf("%d%c:%d ", wq_node->process->pid, wq_node->process->type, wq_node->wait_time);
        wq_node = wq_node->next;
    }
    printf("]\n");
    printf("---------------------------\n");
}

void custom_sleep(int seconds) {
    clock_t start_time = clock();
    clock_t desired_end_time = start_time + seconds * CLOCKS_PER_SEC;

    while (clock() < desired_end_time) {
     
    }
}

void parse_command(char* command, char** argv) {
    while (*command != '\0') {
        while (*command == ' ' || *command == '\n') {
            *command++ = '\0';
        }
        *argv++ = command;
        while (*command != '\0' && *command != ' ' && *command != '\n') {
            command++;
        }
    }
    *argv = NULL;
}

void execute_command(char** argv) {
    if (strcmp(argv[0], "enqueue") == 0) {
        if (argv[1] == NULL || argv[2] == NULL || argv[3] == NULL) {
            printf("Usage: enqueue [pid] [type] [burst_time]\n");
            return;
        }
        int pid = atoi(argv[1]);
        char type = argv[2][0];
        int burst_time = atoi(argv[3]);
        Process* process = create_process(pid, type, burst_time);
        enqueue(dq, process);
    }
    else if (strcmp(argv[0], "dequeue") == 0) {
        Process* process = dequeue(dq);
        if (process != NULL) {
            printf("Running: [%d%c]\n", process->pid, process->type);
            free(process);
        }
    }
    else if (strcmp(argv[0], "sleep") == 0) {
        if (argv[1] == NULL || argv[2] == NULL) {
            printf("Usage: sleep [pid] [sleep_time]\n");
            return;
        }
        int pid = atoi(argv[1]);
        int sleep_time = atoi(argv[2]);
        StackNode* stack = dq->top;
        Process* prev = NULL;
        Process* process = NULL;
        while (stack != NULL) {
            ListNode* list = stack->list;
            process = list->head;
            while (process != NULL) {
                if (process->pid == pid) {
                    if (prev == NULL)
                    {
                        list->head = process->next;
                    }
                    else {
                        prev->next = process->next;
                    }
                    list->length--;
                    if (list->length == 0) {
                        StackNode* temp = dq->top;
                        dq->top = dq->top->next;
                        free(temp->list);
                        free(temp);
                    }
                    break;
                }
                prev = process;
                process = process->next;
            }
            if (process != NULL) {
                break;
            }
            stack = stack->next;
        }

        if (process != NULL) {
            add_to_wait_queue(wq, process, sleep_time);
        }
    }
    else {
        printf("Invalid command: %s\n", argv[0]);
    }
}

void run() {
    char command[256];
    char* argv[64];
    while (1) {
        printf("shell> ");
        fgets(command, 256, stdin);
        parse_command(command, argv);
        execute_command(argv);
    }
}

int main() {
    dq = create_dynamic_queue(3);
    wq = create_wait_queue();

    run();

    return 0;
}
*/

//2-3