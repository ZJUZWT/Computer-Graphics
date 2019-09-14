//
// Created by MrKill on 2019/9/6.
//

#include <cmath>
#include "Coordinate.h"

Coordinate::Coordinate(GLdouble x, GLdouble y,GLdouble mode) {
    this->x = x ;
    this->y = y ;
    this->mode = mode ;
}

Coordinate::Coordinate(Coordinate p1, Coordinate p2) {
    this->x = p2.x-p1.x ;
    this->y = p2.y-p1.y ;
    this->mode = p2.mode - p1.mode ;
}

Coordinate Coordinate::midPoint(Coordinate p1, Coordinate p2) {
    Coordinate newPoint = (p1+p2)/2 ;
    return newPoint ;
}

Coordinate Coordinate::transVertical() {
    Coordinate newVector = Coordinate( -this->y , this->x , 0 ) ;
    return newVector ;
}

Coordinate Coordinate::transStandard() {
    Coordinate newVector = Coordinate( this->x/this->length() , this->y/this->length() , 0 ) ;
    return newVector ;
}

Coordinate Coordinate::operator+(Coordinate v) {
    Coordinate newVector = Coordinate( this->x+v.x , this->y+v.y , this->mode+v.mode ) ;
    return newVector ;
}

Coordinate Coordinate::operator+(GLdouble k) {
    Coordinate newVector = Coordinate( this->x+k , this->y+k , this->mode ) ;
    return newVector ;
}

Coordinate Coordinate::operator-(Coordinate v) {
    Coordinate newVector = Coordinate( this->x-v.x , this->y-v.y , this->mode-v.mode ) ;
    return newVector ;
}

Coordinate Coordinate::operator-(GLdouble k) {
    Coordinate newVector = Coordinate( this->x-k , this->y-k , this->mode ) ;
    return newVector ;
}

Coordinate Coordinate::operator*(GLdouble k) {
    Coordinate newVector = Coordinate( this->x*k , this->y*k , this->mode*k ) ;
    return newVector ;
}

Coordinate Coordinate::operator/(GLdouble k) {
    Coordinate newVector = Coordinate( this->x/k , this->y/k , this->mode/k ) ;
    return newVector ;
}

GLdouble Coordinate::operator*(Coordinate v) {
    return this->x*v.x+this->y*v.y ;
}

GLdouble Coordinate::length() {
    return sqrt(pow(this->x,2)+pow(this->y,2)) ;
}