#include <assert.h>
#include <defs.h>
#include <taskman/taskman.h>

#include <implement_me.h>

/// @brief Maximum number of wait handlers.
#define TASKMAN_NUM_HANDLERS 32

/// @brief Maximum number of scheduled tasks.
#define TASKMAN_NUM_TASKS 128

/// @brief Maximum stack size.
#define TASKMAN_STACK_SIZE 8192

__global struct {
    /// @brief Wait handlers.
    struct taskman_handler* handlers[TASKMAN_NUM_HANDLERS];

    /// @brief Number of wait handlers;
    size_t handlers_count;

    /// @brief Stack area. Contains multiple independent stacks.
    uint8_t stack[TASKMAN_STACK_SIZE];

    /// @brief Stack offset (for the next allocation).
    size_t stack_offset;

    /// @brief Scheduled tasks.
    void* tasks[TASKMAN_NUM_TASKS];

    /// @brief Number of tasks scheduled.
    size_t tasks_count;
} taskman;

/**
 * @brief Extra information attached to the coroutine used by the task manager.
 *
 */
struct task_data {
    struct {
        /// @brief Handler
        /// @note NULL if waiting on `coro_yield`.
        struct taskman_handler* handler;

        /// @brief Argument to the wait handler
        void* arg;
    } wait;
};

void taskman_glinit() {
    taskman.handlers_count = 0;
    taskman.stack_offset = 0;
    taskman.tasks_count = 0;
}

void* taskman_spawn(coro_fn_t coro_fn, void *arg, size_t stack_sz) {
    // (1) allocate stack space for the new task
    // (2) initialize the coroutine and struct task_data
    // (3) register the coroutine in the tasks array
    // use die_if_not() statements to handle error conditions (like no memory)

    die_if_not(taskman.stack_offset + stack_sz <= TASKMAN_STACK_SIZE);
    void* myStack = &taskman.stack[taskman.stack_offset];
    taskman.stack_offset += stack_sz;

    coro_init(myStack, stack_sz, coro_fn, arg);

    die_if_not(taskman.tasks_count < TASKMAN_NUM_TASKS);
    taskman.tasks[taskman.tasks_count] = myStack;
    taskman.tasks_count++;

    struct task_data my_task;
    my_task.wait.arg = arg;
    my_task.wait.handler = NULL;

    *(struct task_data*)coro_data(myStack) = my_task;
    
    return myStack;
}

void taskman_loop() {
    // (a) Call the `loop` functions of all the wait handlers.
    // (b) Iterate over all the tasks, and resume them if.
    //        * The task is not complete.
    //        * it yielded using `coro_yield`.
    //        * the waiting handler says it can be resumed.

    while (1) {
        for(int i = 0; i < taskman.handlers_count; i++) {
            taskman.handlers[i]->loop(taskman.handlers[i]);
        }


        for(int i = 0; i < taskman.tasks_count; i++) {

            if (!coro_completed(taskman.tasks[i], (void**)NULL)) {
                struct task_data my_task_data = *(struct task_data*)coro_data(taskman.tasks[i]);

                if(my_task_data.wait.handler != NULL) {
                    if(my_task_data.wait.handler->can_resume(my_task_data.wait.handler,taskman.tasks[i], my_task_data.wait.arg)) {
                        my_task_data.wait.handler = NULL;

                        coro_resume(taskman.tasks[i]);
                    }
                } else {
                    coro_resume(taskman.tasks[i]);
                }
            }
        }
    }
}

void taskman_register(struct taskman_handler* handler) {
    die_if_not(handler != NULL);
    die_if_not(taskman.handlers_count < TASKMAN_NUM_HANDLERS);

    taskman.handlers[taskman.handlers_count] = handler;
    taskman.handlers_count++;
}

void taskman_wait(struct taskman_handler* handler, void* arg) {
    die_if_not(handler != NULL);

    void* stack = coro_stack();
    struct task_data* task_data = coro_data(stack);

    // I suggest that you read `struct taskman_handler` definition.
    // Call handler->on_wait, see if there is a need to yield.
    // Update the wait field of the task_data.
    // Yield if necessary.

    if(!handler->on_wait(handler,stack,arg)) {
        task_data->wait.arg = arg;
        task_data->wait.handler = handler;
        coro_yield();
    } 
}
