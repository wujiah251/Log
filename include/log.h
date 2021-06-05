#ifndef LOG_H_
#define LOG_H_

#include <time.h>
#include <sys/time.h>

// 日志等级
enum LOG_LEVEL
{
    FATAL = 1,
    ERROR,
    WARN,
    INFO,
    DEBUG,
    TRACE,
};

// 自定义一个时间戳
class utc_timer
{
public:
    int year;
    int mon;
    int day;
    int hour;
    int min;
    int sec;

    utc_timer();
    // 获取当前时间
    uint64_t get_curr_time(int *p_msec = NULL);

private:
    // 系统分钟时间
    uint64_t sys_acc_min;
    // 系统秒时间
    uint64_t sys_acc_sec;

    void reset_utc_fmt();
    void reset_utc_fmt_sec();
};

utc_timer::utc_timer()
{
    struct timeval tv;
    // 获取系统时间（但是不陷入内核）
    gettimeofday(&tv, NULL);
    sys_acc_sec = tv.tv_sec;
    sys_acc_min = sys_acc_sec / 60;
    struct tm cur_tm;
    localtime_r((time_t *)&sys_acc_sec, &cur_tm);
    // 注意开始时间是1900
    year = cur_tm.tm_year + 1900;
    // 0-11
    mon = cur_tm.tm_mon + 1;
    day = cur_tm.tm_mday;
    hour = cur_tm.tm_hour;
    min = cur_tm.tm_min;
    sec = cur_tm.tm_sec;
    reset_utc_fmt();
}

uint64_t utc_timer::get_curr_time(int *p_msec = NULL)
{
    struct timeval tv;
    // 先获取时间
    gettimeofday(&tv, NULL);
    if (p_msec)
    {
        *p_msec = tv.tv_sec / 1000;
    }
    // 不是同一秒
    if ((uint32_t)tv.tv_sec != sys_acc_sec)
    {
        sec = tv.tv_sec % 60;
        // 更新秒
        sys_acc_sec = tv.tv_sec;
        // 不在同一分钟
        if (sys_acc_sec / 60 != sys_acc_min)
        {
            // 更新分钟
            sys_acc_sec = sys_acc_sec / 60;
            struct tm cur_tm;
            localtime_r((time_t *)&sys_acc_sec, &cur_tm);
            year = cur_tm.tm_year + 1900;
            mon = cur_tm.tm_mon + 1;
            day = cur_tm.tm_mday;
            hour = cur_tm.tm_hour;
            min = cur_tm.tm_min;
            sec = cur_tm.tm_sec;
            reset_utc_fmt();
        }
        else
        {
            reset_utc_fmt();
        }
    }
    return tv.tv_sec;
}

void utc_timer::reset_utc_fmt()
{
}

void utc_timer::reset_utc_fmt_sec()
{
}

#endif