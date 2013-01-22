#include <ngx_config.h>
#include <ngx_core.h>
#include <nginx.h>

#include <stdio.h>

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

int main(int argc, const char *argv[])
{
    printf("hello, world.\n");
    return 0;
}
