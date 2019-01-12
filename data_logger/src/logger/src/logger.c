#include <util/sensor_data.h>
#include <stdio.h>

int logging(char *path, sensor_data **data, int len) {
	int i;
	FILE *file = fopen(path, "a");
    if(file == NULL){
        file = fopen("../data/data_corpus.dat", "a");
        if(file == NULL) printf("file open error\n");
    }
    double value;
	for(i = 0 ; i < len ; i++) {
        value = sensor_data_get_value(data[i]);
		fprintf(file, "%.2f", value);
		if(i < len-1) fprintf(file, ",");
	}
	fprintf(file, "\n");
	int e = fclose(file);
    if(e == EOF) printf("file close error\n");

	return 0;
}
