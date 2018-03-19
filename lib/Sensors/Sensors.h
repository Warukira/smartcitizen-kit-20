#pragma once

/* 	-----------------
 	|	 Sensors 	|
 	-----------------
*/
enum SensorLocation {
	BOARD_BASE,
	BOARD_URBAN,
	BOARD_AUX
};

enum SensorType {

	// Base Sensors
	SENSOR_BATTERY,
	SENSOR_VOLTIN,

	// Urban Sensors
	SENSOR_NOISE,
	SENSOR_HUMIDITY,
	SENSOR_TEMPERATURE,
	SENSOR_LIGHT,
	SENSOR_CO,
	SENSOR_CO_HEAT_TIME,
	SENSOR_CO_HEAT_CURRENT,
	SENSOR_CO_HEAT_SUPPLY_VOLTAGE,
	SENSOR_CO_HEAT_DROP_VOLTAGE,
	SENSOR_CO_LOAD_RESISTANCE,
	SENSOR_NO2,
	SENSOR_NO2_HEAT_TIME,
	SENSOR_NO2_HEAT_CURRENT,
	SENSOR_NO2_HEAT_SUPPLY_VOLTAGE,
	SENSOR_NO2_HEAT_DROP_VOLTAGE,
	SENSOR_NO2_LOAD_RESISTANCE,

	// I2C Auxiliary Sensors
	SENSOR_ALPHADELTA_SLOT_1A,
	SENSOR_ALPHADELTA_SLOT_1W,
	SENSOR_ALPHADELTA_SLOT_2A,
	SENSOR_ALPHADELTA_SLOT_2W,
	SENSOR_ALPHADELTA_SLOT_3A,
	SENSOR_ALPHADELTA_SLOT_3W,
	SENSOR_ALPHADELTA_TEMPERATURE,
	SENSOR_ALPHADELTA_HUMIDITY,

	SENSOR_GROOVE_I2C_ADC,

	SENSOR_INA219_BUSVOLT,
	SENSOR_INA219_SHUNT,
	SENSOR_INA219_CURRENT,
	SENSOR_INA219_LOADVOLT,

	SENSOR_WATER_TEMP_DS18B20,
	SENSOR_ATLAS_PH,
	SENSOR_ATLAS_EC,
	SENSOR_ATLAS_EC_SG,
	SENSOR_ATLAS_DO,
	SENSOR_ATLAS_DO_SAT,

	SENSOR_CHIRP_MOISTURE,
	SENSOR_CHIRP_TEMPERATURE,
	SENSOR_CHIRP_LIGHT,

	SENSOR_GROOVE_TEMP_SHT31,
	SENSOR_GROOVE_HUM_SHT31,

	// Actuators (This is temp)
	SENSOR_GROOVE_OLED,

	SENSOR_COUNT	
};

const uint32_t minimal_sensor_reading_interval = 60;
const uint32_t default_sensor_reading_interval = 60;
const uint32_t max_sensor_reading_interval = 86400;		// One day

// Structs for RAM storing
struct SensorGroupByTime {		// 5 bytes
	uint32_t time;
	uint8_t numberOfReadings;
	uint32_t readingStartIndex;
};

struct SingleSensorReading {	// 5 bytes
	SensorType sensor;
	float reading;	
};

struct SensorGroupBuffer{
	uint32_t time;
	uint8_t numberOfReadings;
	SingleSensorReading data[SENSOR_COUNT];
};

class OneSensor {
public:
	SensorType type;
	const char *title;
	const char *unit;
	float reading;
	uint32_t lastReadingTime;
	bool valid;
	bool controllable;
	SensorLocation location;
	uint8_t id;
	uint32_t interval;
	bool enabled;
	bool busy;

	OneSensor(SensorLocation nLocation, SensorType nType, const char *nTitle, uint8_t nId=0, bool nEnabled=false, bool nControllable=false, const char *nUnit="") {
		type = nType;
		title = nTitle;
		unit = nUnit;
		reading = 0;
		lastReadingTime = 0;
		valid = false;
		controllable = nControllable;
		location = nLocation;
		id = nId;
		interval = default_sensor_reading_interval;
		enabled = nEnabled;
		busy = false;
	}
};

class AllSensors {
public:
	
	OneSensor list[SENSOR_COUNT] {
	
		//			SensorLocation 		SensorType 							title 									id		enabled		controllable	unit 		
						
		// Base Sensors						
		OneSensor {	BOARD_BASE, 		SENSOR_BATTERY, 					"Battery", 								10,		true,		false,			"%"},
		OneSensor {	BOARD_BASE, 		SENSOR_VOLTIN,						"Input voltage", 						0,		true,		false,			"V"},

		// Urban Sensors
		OneSensor {	BOARD_URBAN, 		SENSOR_NOISE, 						"Noise", 								29,		true,		false,			"dBc"},
		OneSensor {	BOARD_URBAN, 		SENSOR_HUMIDITY,					"Humidity", 							13,		true,		false,			"%"},
		OneSensor {	BOARD_URBAN, 		SENSOR_TEMPERATURE, 				"Temperature", 							12,		true,		false,			"C"},
		OneSensor {	BOARD_URBAN, 		SENSOR_LIGHT, 						"Light", 								14,		true,		false,			"Lux"},
		OneSensor {	BOARD_URBAN, 		SENSOR_CO, 							"Carbon monoxide", 						16,		true,		true,			"kOhm/ppm"},
		OneSensor {	BOARD_URBAN, 		SENSOR_CO_HEAT_TIME, 				"Carbon monoxide heat time",			0,		false,		false,			"sec"},
		OneSensor {	BOARD_URBAN, 		SENSOR_CO_HEAT_CURRENT, 			"Carbon monoxide heat current",			0,		true,		false,			"mA"},
		OneSensor {	BOARD_URBAN, 		SENSOR_CO_HEAT_SUPPLY_VOLTAGE, 		"Carbon monoxide heat supply voltage",	0,		true,		false,			"mV"},
		OneSensor {	BOARD_URBAN, 		SENSOR_CO_HEAT_DROP_VOLTAGE, 		"Carbon monoxide heat drop voltage",	0,		true,		false,			"mV"},
		OneSensor {	BOARD_URBAN, 		SENSOR_CO_LOAD_RESISTANCE, 			"Carbon monoxide load resistance",		0,		true,		false,			"Ohms"},
		OneSensor {	BOARD_URBAN, 		SENSOR_NO2, 						"Nitrogen dioxide",						15,		true,		true,			"kOhm/ppm"},
		OneSensor {	BOARD_URBAN, 		SENSOR_NO2_HEAT_TIME, 				"Nitrogen dioxide heat time",			0,		false,		false,			"sec"},
		OneSensor {	BOARD_URBAN, 		SENSOR_NO2_HEAT_CURRENT, 			"Nitrogen dioxide heat current",		0,		true,		false,			"mA"},
		OneSensor {	BOARD_URBAN, 		SENSOR_NO2_HEAT_SUPPLY_VOLTAGE, 	"Nitrogen dioxide heat supply voltage",	0,		true,		false,			"mV"},
		OneSensor {	BOARD_URBAN, 		SENSOR_NO2_HEAT_DROP_VOLTAGE, 		"Nitrogen dioxide heat drop voltage",	0,		true,		false,			"mV"},
		OneSensor {	BOARD_URBAN, 		SENSOR_NO2_LOAD_RESISTANCE, 		"Nitrogen dioxide load resistance",		0,		true,		false,			"Ohms"},

		// I2C Auxiliary Sensors
		// Alphasense Delta board (3 Gas sensor Slots, + SHT31 Temp-Humidity)
		OneSensor {	BOARD_AUX, 			SENSOR_ALPHADELTA_SLOT_1A,			"AlphaDelta 1A",						0,		false,		true,			},
		OneSensor {	BOARD_AUX, 			SENSOR_ALPHADELTA_SLOT_1W,			"AlphaDelta 1W",						0,		false,		true,			},
		OneSensor {	BOARD_AUX, 			SENSOR_ALPHADELTA_SLOT_2A,	 		"AlphaDelta 2A",						0,		false,		true,			},
		OneSensor {	BOARD_AUX, 			SENSOR_ALPHADELTA_SLOT_2W, 			"AlphaDelta 2W",						0,		false,		true,			},
		OneSensor {	BOARD_AUX, 			SENSOR_ALPHADELTA_SLOT_3A, 			"AlphaDelta 3A",						0,		false,		true,			},
		OneSensor {	BOARD_AUX, 			SENSOR_ALPHADELTA_SLOT_3W, 			"AlphaDelta 3W",						0,		false,		true,			},
		OneSensor {	BOARD_AUX, 			SENSOR_ALPHADELTA_TEMPERATURE, 		"AlphaDelta Temperature", 				0,		false,		false,			"C"},
		OneSensor {	BOARD_AUX, 			SENSOR_ALPHADELTA_HUMIDITY, 		"AlphaDelta Humidity",					0,		false,		false,			"%"},
	
		// Groove I2C ADC
		OneSensor { BOARD_AUX,			SENSOR_GROOVE_I2C_ADC,				"Groove ADC",							0,		false,		false,			"V"},

		// Adafruit INA291 High Side DC Current Sensor
		OneSensor { BOARD_AUX,			SENSOR_INA219_BUSVOLT,				"INA219 Bus voltage",					0,		false,		false,			"V"},
		OneSensor { BOARD_AUX,			SENSOR_INA219_SHUNT,				"INA219 Shunt voltage",					0,		false,		false,			"mV"},
		OneSensor { BOARD_AUX,			SENSOR_INA219_CURRENT,				"INA219 Current",						0,		false,		false,			"mA"},
		OneSensor { BOARD_AUX,			SENSOR_INA219_LOADVOLT,				"INA219 Load voltage",					0,		false,		false,			"V"},

		// Atlas Scientific probes
		OneSensor { BOARD_AUX,			SENSOR_WATER_TEMP_DS18B20,			"DS18B20 Water temperature",			42,		false,		false,			"C"},
		OneSensor { BOARD_AUX,			SENSOR_ATLAS_PH,					"Atlas PH",								43,		false,		true,			"pH"},
		OneSensor { BOARD_AUX,			SENSOR_ATLAS_EC,					"Atlas Conductivity",					45,		false,		true,			"uS/cm"},
		OneSensor { BOARD_AUX,			SENSOR_ATLAS_EC_SG,					"Atlas Specific gravity",				46,		false,		true,			},
		OneSensor { BOARD_AUX,			SENSOR_ATLAS_DO,					"Atlas Dissolved Oxygen",				48,		false,		true,			"mg/L"},
		OneSensor { BOARD_AUX,			SENSOR_ATLAS_DO_SAT,				"Atlas DO Saturation",					49,		false,		true,			"%"},

		// I2C Moisture Sensor (chirp)
		// https://github.com/Miceuz/i2c-moisture-sensor
		OneSensor { BOARD_AUX, 			SENSOR_CHIRP_MOISTURE,				"Soil Moisture",						0,		false,		true,			},
		OneSensor { BOARD_AUX, 			SENSOR_CHIRP_TEMPERATURE,			"Soil Temperature",						0,		false,		true,			"C"},
		OneSensor { BOARD_AUX, 			SENSOR_CHIRP_LIGHT, 				"Soil Light", 							0, 		false, 		true, 			},

		// Temperature and Humidity Groove - SHT31
		OneSensor {	BOARD_AUX, 			SENSOR_GROOVE_TEMP_SHT31, 			"Temperature SHT31", 					0,		false,		false,			"C"},
		OneSensor {	BOARD_AUX, 			SENSOR_GROOVE_HUM_SHT31,			"Humidity SHT31", 						0,		false,		false,			"%"},

		// Later this will be moved to a Actuators.h file
		// Groove I2C Oled Display 96x96
		OneSensor { BOARD_AUX,			SENSOR_GROOVE_OLED,					"Groove OLED",							0,		false,		false,			}


		//-----------------------
		// Add New Sensor Here!!!

	};

	OneSensor & operator[](SensorType type) {
    	return list[type];
	}

private:
	
};
