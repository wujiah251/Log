#include "../../include/log.h"

// 多线程测试

#define THREAD_NUM 10

int64_t get_current_millis()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (int64_t)tv.tv_sec * 1000 + tv.tv_usec / 1000;
}

void *log_worker(void *args)
{
    for (int i = 0; i < 1e5; ++i)
    {
        LOG_ERROR("this test is no.%d", i);
    }
}

int main(int argc, char **argv)
{
    LOG_INIT("log", "main", WARN);
    uint64_t start_ts = get_current_millis();
    pthread_t tids[THREAD_NUM];
    for (int i = 0; i < THREAD_NUM; ++i)
    {
        pthread_create(&tids[i], NULL, log_worker, NULL);
    }
    for (int i = 0; i < THREAD_NUM; ++i)
    {
        pthread_join(tids[i], NULL);
    }
    uint64_t end_ts = get_current_millis();
    printf("time use %llus\n", end_ts - start_ts);
}
