#include <ngx_config.h>
#include <ngx_core.h>
#include <nginx.h>

#include <stdio.h>
#include <assert.h>

ngx_uint_t          ngx_max_module;
ngx_uint_t          ngx_dump_config;

ngx_module_t  ngx_core_module;

char **
ngx_set_environment(ngx_cycle_t *cycle, ngx_uint_t *last) {
    return NULL;
}

ngx_pid_t
ngx_exec_new_binary(ngx_cycle_t *cycle, char *const *argv) {
    ngx_pid_t pid;

    return pid;
}

static u_char *ngx_prefix;

void
inspect_array(ngx_array_t *array) {
    printf("array: nelts: %d, size: %d, nalloc: %d\n",
            (uint32_t)array->nelts, (uint32_t)array->size, (uint32_t)array->nalloc);
}

void
inspect_list(ngx_list_t *list) {
    printf("list: nelts: %d, size: %d, nalloc: %d\n",
           (uint32_t)list->part.nelts, (uint32_t)list->size, (uint32_t)list->nalloc);
}

void
test_slab() {
    ngx_slab_pool_t *sp;
    void *p;

    sp = malloc(1024 * 1024);
    sp->end = (u_char *)sp + 1024 * 1024;
    sp->min_shift = 3;
    sp->addr = sp;

    ngx_slab_init(sp);

    p = ngx_slab_alloc_locked(sp, 10);
    printf("allocated address: %p\n", p);
    printf("sp->addr: %p\n", sp->addr);
    printf("sp->end: %p\n", sp->end);
}

void
test_array() {
    ngx_array_t *array;
    int *p;
    int i;

    array = ngx_array_create(ngx_cycle->pool, 100, sizeof(int));

    for(i = 0; i < 10; i++) {
        p = (int *)ngx_array_push(array);
        *p = i;
    }

    inspect_array(array);
}

void
test_list() {
    ngx_list_t *list;
    ngx_list_part_t *part;
    int *p, i;
    uint32_t j;
    int *data;

    list = ngx_list_create(ngx_cycle->pool, 100, sizeof(int));

    for(i = 0; i < 10; i++) {
        p = (int *)ngx_list_push(list);
        *p = i;
    }

    part = &list->part;
    printf("%p %p\n", part, list->last);
    while(part) {
        data = (int *)part->elts;

        for(j = 0; j < part->nelts; j++) {
            printf("%d ", data[j]);
        }
        part = part->next;
    }
    printf("\n");

    inspect_list(list);
}


int main(int argc, const char *argv[])
{
    ngx_log_t *log;
    ngx_cycle_t init_cycle;

    ngx_time_init();

    log = ngx_log_init(ngx_prefix);
    assert(log);

    if (ngx_os_init(log) != NGX_OK) {
        return 1;
    }

    ngx_pid = ngx_getpid();
    printf("pid: %d\n", ngx_pid);
    // ngx_log_stderr(0, "stderr log");

    ngx_memzero(&init_cycle, sizeof(ngx_cycle_t));
    init_cycle.log = log;
    ngx_cycle = &init_cycle;

    init_cycle.pool = ngx_create_pool(1024, log);
    if (init_cycle.pool == NULL) {
        return 1;
    }

    test_slab();
    test_array();
    test_list();

    printf("done!\n");

    return 0;
}
