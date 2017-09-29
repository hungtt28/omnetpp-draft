/*
 * Coord.h
 *
 *  Created on: Sep 29, 2017
 *      Author: hungt
 */

#ifndef COORD_H_
#define COORD_H_

#include <omnetpp.h>

class Coord {
public:
	double x;
	double y;

public:
    Coord(): x(0.0), y(0.0) {};
	Coord(double x, double y): x(x), y(y) {};
    // virtual ~Coord();
	
	double distance(Coord *coord)
	{
		return distance(coord->x, coord->y);
	}

	double distance(double x1, double y1)
	{
		return sqrt((x - x1) * (x - x1) + (y - y1) * (y - y1));
	}
};

#endif /* COORD_H_ */
