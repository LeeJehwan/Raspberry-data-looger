#include <stdio.h>
#include <stdlib.h>
#include <bcm2835.h>
#include <sensor/sensor.h>
#include <monitor/monitor.h>
#include <logger/logger.h>
#include <timer/timer.h>
#include <util/sensor_data.h>
#include <control/control.h>

#define SENSOR_BMP180
//#define SENSOR_ADS1256
sensor_data **data = NULL;
void logger_routine();

int main(){
    int i = 0;
    int nData = 3;
    int type = ON;
    int sec = 1;
    int msec = 0;
    
    control_beep();
    
    /* Data Storage Preparation */
    data = (sensor_data **)malloc(sizeof(sensor_data*) * nData);

    for(i = 0 ; i < nData ; i++) {
        data[i] = sensor_data_init();
    }

    /* Initialize */
#ifdef SENSOR_BMP180
    if(!bmp180_begin()) return 1;
#endif
#ifdef SENSOR_ADS1256
    if(!ads1256_begin()) return 1;
#endif

    control_init();
    
    /* timer setup */ 
    Timer_logger* timer = timer_init();
    timer_setfunction(timer,logger_routine);
    if(timer_interval(timer, sec, msec) == -1) return -1;
    timer_onoff(timer, type);
    
    while(get_control_flag()){
        if(get_control_timer_flag()){
            timer_interval(timer, get_control_timer_interval(), msec);
            timer_onoff(timer,type);
            set_control_timer_flag_off();
        }
        if(control_push()){
            type ^= 1;

            if(type == 1)
                fprintf(stdout, "start\n");
            else
                fprintf(stdout, "pause\n");

            timer_onoff(timer, type);

            while(control_push())
                bcm2835_delay(10);

        } 
        bcm2835_delay(10);
    }
    /* Clean-up */
    for(i = 0 ; i < nData ; i++) {
        sensor_data_deinit(&data[i]);
    }
#ifdef SENSOR_BMP180
    bmp180_end();
#endif
#ifdef SENSOR_ADS1256
    ads1256_end();
#endif
    free(data);
    timer_deinit(&timer);

    control_beep();
    
    fprintf(stdout, "program end\n");
    return 0;
}



void logger_routine(){
    int i = 0;
    int result = 0;
    int nData = 3;

    /* Sensing */
#ifdef SENSOR_BMP180
        sensor_data_set(data[0], "temp", SENSOR_DATA_TYPE_DOUBLE, read_temperature(), "C");
        sensor_data_set(data[1], "press", SENSOR_DATA_TYPE_DOUBLE, read_pressure()/100.0, "Pa");
        sensor_data_set(data[2], "alti", SENSOR_DATA_TYPE_DOUBLE, read_altitude(), "h");
#endif
#ifdef SENSOR_ADS1256
    while((ADS1256_Scan() == 0));
    for (i = 0; i < nData; i++)
    {
        sensor_data_set(data[i], "???", SENSOR_DATA_TYPE_DOUBLE, ADS1256_GetAdc(i) /1670.0, "mV");
    }
#endif

#ifdef DEBUG
    /* Monitor */
    monitor(data, nData);
    fprintf(stdout, "\n");  
#endif

    /* Logging */
    result = logging("./data/data_corpus.dat", data, nData);
    if(result) {
        fprintf(stderr, "File is not written.\n");
        return;
    }
}
