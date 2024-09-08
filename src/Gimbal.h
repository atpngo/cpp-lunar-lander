#ifndef GIMBAL
#define GIMBAL


class Gimbal
{
    public:
        Gimbal(double initialAngle = 90.0);
        ~Gimbal();
        void SetAngle(double angle);
        double GetAngleDeg();
        double GetAngleRad();

        void DecreaseAngle();
        void IncreaseAngle();
        double GetGimbalAngle(); // clamped between min and max (-10.5 - 10.5)

    private:
        double minAngle;
        double maxAngle;

        double angularPosition;      // degrees
        double angularVelocity;      // degrees per second
        double angularAcceleration;  // degrees per second^2
        

};


#endif // GIMBAL