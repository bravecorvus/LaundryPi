#include "hardware.h"
using namespace std;


#define RPIID 000


int main() {
	GPIOClass* washer = new GPIOClass("17"); //create new GPIO object to be attached to  GPIOWASHER
	// GPIOClass* dryer = new GPIOClass("22"); //create new GPIO object to be attached to  GPIODRYER
	washer->export_gpio(); //export GPIO WASHER
	// dryer->export_gpio(); //export GPIO DRYER
	cout << " GPIO pins exported" << endl;
	washer->setdir_gpio("in"); //set GPIO to input
	// dryer->setdir_gpio("in"); // set GPIO to input
	Vibration washerhardware(washer);
	// Vibration dryerhardware(dryer);





	string inputstatewasher;
	// string inputstatedryer;
	std::chrono::milliseconds interval( 10 ) ; // 10 milliseconds
	for(;;) {
		washerhardware.gpio->getval_gpio(inputstatewasher);
		// dryerhardware.gpio->getval_gpio(inputstatedryer);
		washerhardware.vectorPush(inputstatewasher);
		// dryerhardware.vectorPush(inputstatedryer);
		washerhardware.HugosStatisticalAnalysis();
		// dryerhardware.HugosStatisticalAnalysis();
		washerhardware.sendInformation();
		// dryerhardware.sendInformation();
		std::this_thread::sleep_for( interval ) ;
	}
	return 0;
}