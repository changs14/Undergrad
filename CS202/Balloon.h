#include <iostream>
using namespace std;

class Balloon{
protected:
    static float PointsPerBalloon; 
    static float PointsMultiplier; 
    static float PointsTotal;
    static int BalloonCount;
public: 
    Balloon();
    virtual ~Balloon();
    static int GetBalloonCount();
    static float GetPointTotal();
    virtual char GetIdentifier() const; 
};

class RedBalloon : public Balloon{
public:
    char GetIdentifier() const;
    ~RedBalloon();
};

class BlueBalloon : public Balloon{
public:
    char GetIdentifier() const;
    ~BlueBalloon();
};

class YellowBalloon : public Balloon{
public:
    char GetIdentifier() const;
    ~YellowBalloon();
};
