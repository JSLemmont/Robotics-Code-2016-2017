#include "..\include\main.h"
#include "..\include\library.h"
//SRC (Slew Rate Control)
int slewTarget[10] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }; //arrays go from 0-9 speed is 0 for all ports
int slewTemp;

// Under Progress...

void autoDrive(int straight, int leftTurning, int rightTurning)
{
	motorSet(2, straight);  motorSet(4, straight); motorSet(8, straight); motorSet(9, straight);
	motorSet(2, leftTurning); motorSet(8, leftTurning);
	motorSet(4, rightTurning); motorSet(9, rightTurning);
}


/*Slew rate commanding
void motorsSlew(const signed char *ports, int speed) {
	signed char port;
	int j = 0;
	while (ports[j] != 20) {
		port = ports[j];
		if ((port >= 1) && (port <= 10)) { //1 <= port <= 10
			slewTarget[port - 1] = speed;
		}
		else if ((port >= -10) && (port <= -1)) { //-10 <= port <= -1
			slewTarget[-port - 1] = -speed;
		}
		j++;
	}
}
*/
//SRC
void slewControlTask(void * parameter) {
	while (1) {
		if (isEnabled()) {
			for (int j = 0; j< 10; j++) { //Cycle through each motor port starts at 0 goes to next line
				slewTemp = motorGet(j + 1); //j plus 1 ports go from 1-10
				if (slewTemp != slewTarget[j]) {
					if (slewTemp < slewTarget[j]) {
						slewTemp += 15;
						if (slewTemp > slewTarget[j])
							slewTemp = slewTarget[j];
					}
					if (slewTemp > slewTarget[j]) {
						slewTemp -= 15;
						if (slewTemp < slewTarget[j])
							slewTemp = slewTarget[j];
					}
				}
				motorSet(j + 1, slewTemp);
			}
		}
		wait(20);
	}
}




