using namespace std;
using namespace pros;

extern Motor leftMotor1;
extern Motor leftMotor2;
extern Motor leftMotor3;

extern Motor rightMotor1;
extern Motor rightMotor2;
extern Motor rightMotor3;

extern Motor intakeMotor;

extern Motor blockerMotor;

extern Motor_Group leftMotorGroup;
extern Motor_Group rightMotorGroup;

void leftDrive(int32_t);
void rightDrive(int32_t);

int32_t accelerate(int32_t, int32_t);
