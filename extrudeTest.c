// by Zachariah, Kaelan, Lyndon, Daddy Parth
#include "global.c"
#include "move.c"
#include "start.c"

task main(){
	//zero()
	/*for (int i = 0; i < 10; i++)
	{
		for (int j = -30; j > -65; j -= 3)
		{
			setServoPosition(S4, 1, j);
			wait1Msec(100);
		}
	}*/
	for (int i = 0; i < 5; i++){
	extrude(true);
	wait1Msec(5000);
	extrude(false);
	wait1Msec(1000);
	}

}
