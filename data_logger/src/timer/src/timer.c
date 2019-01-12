#include "timer.h"

Timer_logger* timer_init(){
    Timer_logger *instance = (Timer_logger*)malloc(sizeof(Timer_logger));
    if(instance == NULL) return NULL;

    return instance;
}
void timer_deinit(Timer_logger **instance){
    free(*instance);
    *instance = NULL;
}
int timer_setfunction(Timer_logger *timer, void (*fn)){
    int sigNo = SIGRTMIN;
    (timer->sa).sa_flags = SA_SIGINFO;  
    (timer->sa).sa_sigaction = fn; 
    sigemptyset(&(timer->sa).sa_mask);  

    if (sigaction(sigNo, &(timer->sa), NULL) == -1)  
    {  
        printf("sigaction error\n");
        return -1;  
    }
    (timer->te).sigev_notify = SIGEV_SIGNAL;  
    (timer->te).sigev_signo = sigNo;  
    (timer->te).sigev_value.sival_ptr = &(timer->timerID);  
    timer_create(CLOCK_REALTIME, &(timer->te), &(timer->timerID));  
}
int timer_interval(Timer_logger *timer, int sec, int msec){
    if(sec == 0 && msec ==0){
        printf("timer interval cannot be 0\n");
        return -1;
    }
    temp_t.t_sec = sec;
    temp_t.t_msec = msec;
    (timer->its).it_interval.tv_sec = sec;
	(timer->its).it_interval.tv_nsec = msec * 1000000;  
	(timer->its).it_value.tv_sec = sec;
	(timer->its).it_value.tv_nsec = msec * 1000000;
}
static void timer_interval_off(Timer_logger *timer){
    int sec = 0;
    int msec = 0;
    (timer->its).it_interval.tv_sec = sec;
    (timer->its).it_interval.tv_nsec = msec * 1000000;  
	(timer->its).it_value.tv_sec = sec;
	(timer->its).it_value.tv_nsec = msec * 1000000;
}
void timer_onoff(Timer_logger *timer, int type){
    if(type == ON){
        timer_interval(timer, temp_t.t_sec, temp_t.t_msec);
	    timer_settime(timer->timerID, 0, &(timer->its), NULL);
    }
    else if(type == OFF){
        timer_interval_off(timer);
        timer_settime(timer->timerID, 0, &(timer->its), NULL);
    }
}

