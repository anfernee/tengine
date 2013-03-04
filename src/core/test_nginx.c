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

    // test_slab();

    return 0;
}
