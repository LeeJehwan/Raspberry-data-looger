#include <monitor.h>
#include <stdio.h>
#include <string.h>

void monitor(sensor_data **data, int len){
	int i = 0;
    char name[SENSOR_DATA_NAME_LEN];
    double value;
    char unit[SENSOR_DATA_UNIT_LEN];
	
    for(i = 0 ; i < len ; i++) {
        strncpy(name, sensor_data_get_name(data[i]), sizeof(name)-1);
        name[sizeof(name)-1] = '\0';
        value = sensor_data_get_value(data[i]);
        strncpy(unit, sensor_data_get_unit(data[i]), sizeof(unit)-1);
        unit[sizeof(unit)-1] = '\0';

		fprintf(stdout, "%s: %0.2f %s\n", name, value, unit);
	}
}
