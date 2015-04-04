#include "CVector3.h"

CVECTOR3::CVECTOR3(float x, float y, float z) {
	X = x;
	Y = y;
	Z = z;
}

CVECTOR3 CVECTOR3::operator+(CVECTOR3 vVector) {
	return CVECTOR3(vVector.X + X, vVector.Y + Y, vVector.Z + Z);
}

CVECTOR3 CVECTOR3::operator-(CVECTOR3 vVector) {
	return CVECTOR3(vVector.X - X, vVector.Y - Y, vVector.Z - Z);
}

CVECTOR3 CVECTOR3::operator*(float num) {
	return CVECTOR3(X * num, Y * num, Z * num);
}

CVECTOR3 CVECTOR3::operator/(float num) {
	return CVECTOR3(X / num, Y / num, Z / num);
}

