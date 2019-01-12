#ifndef __CONTROL_H__
#define __CONTROL_H__

#include <signal.h>
#include <bcm2835.h>  
#include <stdio.h>

#define CONTROL_KEY 20

static int control_flag;
static int control_timer_flag;
static int control_timer_interval;

static struct sigaction control_sig_action[3];

/* Initializer */
void control_init();

/* control  */
int control_push();

/* signal action function */
static void control_flag_control();
static void control_timer_up_control();
static void control_timer_down_control();

/* get & set function */
int get_control_flag();
int get_control_timer_interval();
int get_control_timer_flag();
void set_control_timer_flag_off();

#endif
