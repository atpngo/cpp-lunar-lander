#ifndef CONTROLLER
#define CONTROLLER

class Controller
{
    public:
        Controller(double p, double i, double d);
        ~Controller();
        // PID using 3 sensors
        bool MoveToY(double py, double vy, double targetAltitude);
        double MoveToAngle(double theta, double omega, double targetAngle, double gimbalAngle, double vx);

    private:
        long double error = 0;
        long double prevError = 0;
        long double totalError = 0;
        long double deltaError = 0;

        // PID Constants
        double Kp = 1;
        double Ki = 0.0;
        double Kd = 100; 
        // 1, 0, 20 seems to work well from going from ground to air
};

#endif // CONTROLLER