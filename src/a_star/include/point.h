#ifndef POINT_H
#define POINT_H
#include <cmath>
#include <ostream>

class Point
{
public:
    Point(double _x=0, double _y=0):x(_x),y(_y){};
    double x,y;
    double getDistance(const Point &other){
        return sqrt(pow(other.x-x,2)+pow(other.y-y,2));
    }
    friend std::ostream& operator<< (std::ostream& stream, const Point& pt) {
               stream<<"Point("<<pt.x<<","<<pt.y<<")";
               return stream;
    }

};

#endif // POINT_H
