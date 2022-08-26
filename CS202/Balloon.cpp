#include "Balloon.h"
using namespace std;

/******************************************
 * BALLOON
******************************************/
// Init static variables. 
float Balloon::PointsPerBalloon = 1.0;
float Balloon::PointsMultiplier = 1.0;
float Balloon::PointsTotal = 1.0;
int Balloon::BalloonCount = 0;

Balloon::Balloon(){
    //Add balloon to total count
    BalloonCount++;
}

Balloon::~Balloon(){
    //Remove balloon and add points 
    BalloonCount--;
    PointsTotal += PointsPerBalloon * PointsMultiplier;
}

int Balloon::GetBalloonCount(){
    //Return current number of balloons
    return BalloonCount;
}

float Balloon::GetPointTotal(){
    //Return current total amount of points
    return PointsTotal;
}

char Balloon::GetIdentifier() const{
    //Default identifier
    return '\0';
}

/******************************************
* RED BALLOON
******************************************/
char RedBalloon::GetIdentifier() const{
    //Red identifier
    return 'R';
}
 
RedBalloon::~RedBalloon(){
    //Increase point multiplier and pop red balloon
    PointsMultiplier += 0.1;
    cout<<"Red Balloon - *POP*"<<endl;
}

/******************************************
* Blue BALLOON
******************************************/
char BlueBalloon::GetIdentifier() const{
    //Blue identifier
    return 'B';
}

BlueBalloon::~BlueBalloon(){
    //Increase points per balloon and pop blue balloon.
    PointsPerBalloon += 0.1;
    cout<<"Blue Balloon - *POP*"<<endl;
}

/******************************************
* Yellow BALLOON
******************************************/
char YellowBalloon::GetIdentifier() const{
    //Yellow identifier
    return 'Y';
}

YellowBalloon::~YellowBalloon(){
    //Pop yellow balloon
    cout<<"Yellow Balloon - *POP*"<<endl;
}
