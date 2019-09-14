//
// Created by MrKill on 2019/9/6.
//

//#include "Point.h"
//
//Point::Point(GLdouble x, GLdouble y) {
//    this->x = x ;
//    this->y = y ;
//}
//
//Point Point::midPoint(Point p1, Point p2) {
//    Point newPoint = Point((p1.x+p2.x)/2,(p1.y+p2.y)/2) ;
//    return newPoint ;
//}
//
//Point Point::operator+(Vector v) {
//    Point newPoint = Point(this->x+v.x,this->y+v.y) ;
//    return newPoint ;
//}
//
//Point Point::operator-(Vector v) {
//    Point newPoint = Point(this->x-v.x,this->y-v.y) ;
//    return newPoint ;
//}
//
//Point Point::operator*(GLdouble k) {
//    Point newPoint = Point( this->x*k, this->y*k) ;
//    return newPoint ;
//}
//
//Point Point::operator/(GLdouble k) {
//    Point newPoint = Point( this->x/k, this->y/k) ;
//    return newPoint ;
//}
//
//Vector Point::operator-(Point v) {
//    Vector newVector = Vector(this->x-v.x,this->y-v.y) ;
//    return newVector ;
//}