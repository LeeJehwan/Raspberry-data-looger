#ifndef __TIMER_H__
#define __TIMER_H__

#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

#define ON 1
#define OFF 0

/* signal data structure */
typedef struct{
	struct sigevent         te;  
	struct itimerspec       its;  
	struct sigaction        sa;  
    timer_t timerID;
}Timer_logger;

/* timer temp-save data structure */ 
typedef struct{
    int t_sec;
    int t_msec;
}temp_time;

static temp_time temp_t;

/* initialize & deinitialize */
Timer_logger* timer_init();
void timer_deinit(Timer_logger **instance);

/* timer setting  */
int timer_setfunction(Timer_logger *timer, void (*fn));
int timer_interval(Timer_logger *timer, int sec, int msec);

/* timer on/off */
void timer_onoff(Timer_logger *timer, int type);

/* timer off seting */
static void timer_interval_off(Timer_logger *timer);

#endif 
