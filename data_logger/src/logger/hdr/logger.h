#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <util/sensor_data.h>

int logging(char *path, sensor_data **data, int len);

#endif
