#include "h../bsw/sonar.h"
S32 sonar = 0;

void Ultraschall_auslesen(){

	sonar = sonar_read_distance(<SENSORPROT>);	
};
