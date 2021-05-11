#include "hmInteraction.h"

#define IO_MIN 1000
#define IO_MAX 2000
#define ARMING_RANGE 100
#define MAX_INCLINATION 15
#define MAX_ROTATION_FORCE 100
#define MAX_MOTOR_POWER 100
#define MAX_OFFSET 40
#define IDLE 15
#define WAIT 1000

//receiverInput
typedef enum {Y,X,Z,THR}Axis;
const int IO_MID = (IO_MIN+IO_MAX)/2;
const int userPitch=4;
const int userRoll=2;
const int userYaw = 8;
const int userThrottle = 7;
bool lastShutdown=true;
bool shutdown=true;
float userInput[4];


//escOutput
typedef enum { FRL, FRR, BKL, BKR } engines;
float escOutput[4];

//bnoInput
float angle[3];

//pid
typedef enum {P, I, D}PID;
const float pidConstant[3][3]={{1.3,0,0.95},{1.3,0,0.95},{1.3,0,0.95}};
const int pidMax=400;
float pidOffset[2][3]={{0,0,0},{0,0,0}};
float min_error=3;
float time,timePrev,elapsedTime;
float offset[3];

//flightProcedures
const float DEGtoRAD=M_PI/180;
const float maxInclAx=cos(MAX_INCLINATION/sqrt(2)*DEGtoRAD);
float correction[2];
float last_correction[2];













