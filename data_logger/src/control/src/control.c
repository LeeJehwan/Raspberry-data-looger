#include "control.h"


/* get & set function */
int get_control_flag(){
    return control_flag;
}
int get_control_timer_interval(){
    return control_timer_interval;
}
int get_control_timer_flag(){
    return control_timer_flag;
}
void set_control_timer_flag_off(){
    control_timer_flag = 0;
}

/* signal action function */ 
static void control_flag_control(){
    control_flag ^= 1;
    fprintf(stdout, "\nCTRL+C interrupt catched\n");
}
static void control_timer_up_control(){
    control_timer_flag = 1;
    control_timer_interval++;
    fprintf(stdout,"timer interval: %d sec \n",control_timer_interval);
}
static void control_timer_down_control(){
    control_timer_flag = 1;
    if(control_timer_interval == 1){
        fprintf(stdout,"interval cannot be 0\n");
    }
    else{
        control_timer_interval--;
        fprintf(stdout,"timer interval: %d sec \n",control_timer_interval);
    }
}

/* switch & sigaction initialize */ 
void control_init(){
    control_timer_interval = 1;
    control_flag = 1;
    bcm2835_gpio_fsel(CONTROL_KEY, BCM2835_GPIO_FSEL_INPT);
    bcm2835_gpio_set_pud(CONTROL_KEY, BCM2835_GPIO_PUD_UP);
  
    //SIGINT=2, ctrl+C interrupt
    control_sig_action[0].sa_flags =SA_SIGINFO;
    control_sig_action[0].sa_sigaction = control_flag_control;
    sigemptyset(&control_sig_action[0].sa_mask);
    if(sigaction(SIGINT, &control_sig_action[0], NULL) == -1){
        fprintf(stderr, "sigaction error\n");
    }

    //SIGUSR1=10, timer_up
    control_sig_action[1].sa_flags =SA_SIGINFO;
    control_sig_action[1].sa_sigaction = control_timer_up_control;
    sigemptyset(&control_sig_action[1].sa_mask);
    if(sigaction(SIGUSR1, &control_sig_action[1], NULL) == -1){
        fprintf(stderr, "sigaction error\n");
    }

    //SIGUSR2=12, timer_down
    control_sig_action[2].sa_flags =SA_SIGINFO;
    control_sig_action[2].sa_sigaction = control_timer_down_control;
    sigemptyset(&control_sig_action[2].sa_mask);
    if(sigaction(SIGUSR2, &control_sig_action[2], NULL) == -1){
        fprintf(stderr, "sigaction error\n");
    }

}

/* switch function */
int control_push(){
    if(bcm2835_gpio_lev(CONTROL_KEY)==0)
        return 1;
    return 0;
}

