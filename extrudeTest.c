// by Zachariah, Kaelan, Lyndon, Daddy Parth
#include "global.c"
#include "move.c"
#include "start.c"

task main(){
	zero();
	extrude(true);
	wait1Msec(1000);
	extrude(false);
}
