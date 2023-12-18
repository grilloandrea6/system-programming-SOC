#ifndef TASKMAN_TASKMAN_H_INCLUDED
#define TASKMAN_TASKMAN_H_INCLUDED

#include <coro/coro.h>

struct taskman_handler {
    /**
     * @brief Called when a task calls `taskman_wait`. Returns 0 if should wait, 1 otherwise.
     *
     */
    int (*on_wait)(struct taskman_handler* handler, void* stack, void* arg);

    /**
     * @brief Checks if the task should be resumed.
     *
     */
    int (*can_resume)(struct taskman_handler* handler, void* stack, void* arg);

    /**
     * @brief Called at each main loop iteration.
     *
     */
    void (*loop)(struct taskman_handler* handler);
};

/**
 * @brief Initializes the task manager at startup.
 *
 */
void taskman_glinit();

/**
 * @brief Spawns a new task.
 *
 * @param coro_fn Coroutine function corresponding to the task.
 * @param arg Argument to be passed to the coroutine.
 * @param stack_sz Stack size allocated to it.
 * @return void* Pointer to the stack of the scheduled task.
 */
void* taskman_spawn(coro_fn_t coro_fn, void* arg, size_t stack_sz);

/**
 * @brief Executes the main loop of the task manager.
 *
 */
void taskman_loop();

/**
 * @brief Registers a wait handler.
 *
 * @param handler Handler struct.
 */
void taskman_register(struct taskman_handler* handler);

/**
 * @brief Wait using a handler.
 *
 * @param handler
 * @param arg
 */
void taskman_wait(struct taskman_handler* handler, void* arg);

#endif /* TASKMAN_TASKMAN_H_INCLUDED */
