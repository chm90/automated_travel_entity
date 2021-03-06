#ifndef NAVIGATION_PATH_H
#define NAVIGATION_PATH_H 1

#define _USE_MATH_DEFINES

#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <sstream>
#include <math.h>
#include <iostream>
#include <memory>

#include <project_msgs/stop.h>
#include "project_msgs/direction.h"

using namespace std;

class Path {
  public:
    double linVel;
    double angVel;
    bool move;
    bool replan;
    bool rollback;
    bool onlyTurn;
    double directionChange;

    vector<pair<double,double> > globalPath;

    ros::ServiceClient lppService;
    ros::Publisher statusPub;
    ros::Publisher stopPub;

    Path(double _pathRad, double _distanceTol, double _angleTol): 
        linVel(0), angVel(0), 
        pathRad(_pathRad), 
        distanceTol(_distanceTol), 
        angleTol(_angleTol), 
        move(false),
        replan(false),
        rollback(false),
        onlyTurn(false) {};
    void setGoal(double x, double y, double theta);
    void followPath(double x, double y, double theta);
    void obstaclesCallback(const project_msgs::stop::ConstPtr& msg);
    void setPath(double x, double y, double theta, double p_distancetol, double p_angleTol, vector<pair<double,double> > path);
  private:
    double pathRad;
    double distanceTol;
    double angleTol;
    double goalX;
    double goalY;
    double goalAng;
    double distance(pair<double,double>& a, pair<double, double>& b);
    double getAngle(pair<double,double> &g, pair<double, double> &p);
    double diffAngles(double a, double b) ;
    double normalizeAngle(double angle);
    void amendDirection();
    void stop();
    void goalIsReached();
};

#endif // NAVIGATION_PATH_H
