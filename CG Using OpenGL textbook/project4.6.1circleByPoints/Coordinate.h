//
// Created by MrKill on 2019/9/6.
//

#ifndef PROJECT4_6_1CIRCLEBYPOINTS_COORDINATE_H
#define PROJECT4_6_1CIRCLEBYPOINTS_COORDINATE_H

#include <GL/glut.h>

class Coordinate {
public:

    GLdouble x ;
    GLdouble y ;
    GLdouble mode ;

    Coordinate(GLdouble x,GLdouble y,GLdouble mode) ;
    Coordinate(Coordinate p1,Coordinate p2) ;

    Coordinate transVertical() ;
    Coordinate transStandard() ;
    Coordinate operator+(Coordinate v) ;
    Coordinate operator+(GLdouble k) ;
    Coordinate operator-(Coordinate v) ;
    Coordinate operator-(GLdouble k) ;
    Coordinate operator/(GLdouble k) ;
    Coordinate operator*(GLdouble k) ;

    static Coordinate midPoint(Coordinate p1,Coordinate p2) ;

    GLdouble operator*(Coordinate v) ;
    GLdouble length() ;

};

#endif //PROJECT4_6_1CIRCLEBYPOINTS_COORDINATE_H
