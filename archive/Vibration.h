#ifndef _VIBRATION_H_
#define _VIBRATION_H_
/** Class that handles Vibration inputs from the vibration sensor */
class Vibration {
	bool* vibration; /**< Boolean to register one deviance from the rest state (swinging the sensor once to a side = one vibration) */
	unsigned int numVib; /**< Number of registered vibrations (to be used for collecting data on how many vibrations are there in a full washing cycle of 25 minutes) */
	int machineID; /**< The ID number of the washer to be easily located, we will use our own ID system. */
public:
	/** 2-argument constructor
	@param vib Pointer to an array of recorded vibrations from the vibrations sensor\
	@param id Machine ID number*/
	Vibration(bool* vib, int id);
	/** obtain a state variable
	@return The value of the state variable indicating the number of vibrations*/
	unsigned int getNumVib();
	/** obtain a state variable
	@return The value of the state variable indicating whether or not a vibration occured*/
	bool* getVibration();
};

#endif /* _VIBRATION_H_ */