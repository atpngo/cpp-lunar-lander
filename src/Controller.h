#ifndef CONTROLLER
#define CONTROLLER

class Controller
{
    public:
        Controller();
        ~Controller();
        // PID using 3 sensors
        bool MoveTo(float py, float vy, float targetAltitude);

    private:
        long double error = 0;
        long double prevError = 0;
        long double totalError = 0;
        long double deltaError = 0;

        // PID Constants
        long double Kp = 1;
        long double Ki = 0.0;
        long double Kd = 100; 
        // 1, 0, 20 seems to work well from going from ground to air
};

#endif // CONTROLLER