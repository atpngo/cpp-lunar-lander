#ifndef GIMBAL
#define GIMBAL


class Gimbal
{
    public:
        Gimbal(double initialAngle = 90.0);
        ~Gimbal();
        void SetAngle(double angle);
        double GetAngle();

        void DecreaseAngle();
        void IncreaseAngle();

    private:
        double minAngle;
        double maxAngle;

        double angularPosition;      // degrees
        double angularVelocity;      // degrees per second
        double angularAcceleration;  // degrees per second^2
        

};


#endif // GIMBAL