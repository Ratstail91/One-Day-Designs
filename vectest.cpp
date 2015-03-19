#include "bounding_box.hpp"
#include "vector2.hpp"

#include <iostream>

inline double sin(Vector2 v) {
	return v.y / sqrt(v.x*v.x + v.y*v.y);
}

inline double cos(Vector2 v) {
	return v.x / sqrt(v.x*v.x + v.y*v.y);
}

inline double tan(Vector2 v) {
	return v.y / v.x;
}

//return the amount to move
Vector2 projectCollisionVectorH(Vector2 origin, Vector2 motion, int boxLeft, int boxRight, int boxTop, int boxBottom) {
	//length of a, c
	double a = std::min(std::abs(boxLeft - origin.x), std::abs(boxRight - origin.x));
	double c = a / cos(motion); //NOTE: B and motion are equivilent

	//if motion vector is too short for a collision
	if (std::abs(c) > motion.Length()) {
		return motion;
	}

	//is A within the box's bounds?
	Vector2 A = motion * std::abs(a);
	if ((A + origin).y >= boxTop && (A + origin).y <= boxBottom) {
		//if so, scale A down so that the new x is 1 unit outside of the box
		return motion * ((a>0 ? a-1 : a+1) / motion.x);
	}
	else {
		//if not, return the normal end point
		return motion;
	}
}

//return the amount to move
Vector2 projectCollisionVectorV(Vector2 origin, Vector2 motion, int boxLeft, int boxRight, int boxTop, int boxBottom) {
	//length of a, c
	double a = std::min(std::abs(boxTop - origin.y), std::abs(boxBottom - origin.y));
	double c = a / sin(motion); //NOTE: B and motion are equivilent

	//if motion vector is too short for a collision
	if (std::abs(c) > motion.Length()) {
		return motion;
	}

	//is A within the box's bounds?
	Vector2 A = motion * std::abs(a);
	if ((A + origin).x >= boxLeft && (A + origin).x <= boxRight) {
		//if so, scale A down so that the new y is 1 unit outside of the box
		return motion * ((a>0 ? a-1 : a+1) / motion.y);
	}
	else {
		//if not, return the normal end point
		return motion;
	}
}

Vector2 projectCollisionVector(Vector2 origin, Vector2 motion, int boxLeft, int boxRight, int boxTop, int boxBottom) {
	//BUGFIX: no motion
	if (motion == 0) {
		return motion;
	}

	//BUGIFX: moving away
	if (!BoundingBox(boxLeft, boxTop, boxRight-boxLeft, boxBottom-boxTop).CheckOverlap({int(origin.x+motion.x+motion.x), int(origin.y+motion.y+motion.y)})) {
		return motion;
	}

	Vector2 h = projectCollisionVectorH(origin, motion, boxLeft, boxRight, boxTop, boxBottom);
	Vector2 v = projectCollisionVectorV(origin, motion, boxLeft, boxRight, boxTop, boxBottom);
	return h.SquaredLength() < v.SquaredLength() ? h : v;
}

int main(int, char**) {
	Vector2 origin = {100, 100}, motion = {1, 1};
	BoundingBox box = {0, 110, 200, 200};

	for (int i = 0; i < 20; i++) {
		Vector2 end = projectCollisionVector(origin, motion, box.x, box.x + box.w, box.y, box.y + box.h);
		std::cout << "\t" << "end: (" << end.x << "," << end.y << ")";
		origin += end;
		std::cout << "\t" << "origin: (" << origin.x << "," << origin.y << ")";
		std::cout << "\t[" << box.CheckOverlap({(int)origin.x, (int)origin.y}) << "]";
		std::cout << std::endl;
	}

	motion = -motion;

	for (int i = 0; i < 20; i++) {
		Vector2 end = projectCollisionVector(origin, motion, box.x, box.x + box.w, box.y, box.y + box.h);
		std::cout << "\t" << "end: (" << end.x << "," << end.y << ")";
		origin += end;
		std::cout << "\t" << "origin: (" << origin.x << "," << origin.y << ")";
		std::cout << "\t[" << box.CheckOverlap({(int)origin.x, (int)origin.y}) << "]";
		std::cout << std::endl;
	}

	std::cout << "Result: (" << origin.x << ", " << origin.y << ")" << std::endl;
	return 0;
}