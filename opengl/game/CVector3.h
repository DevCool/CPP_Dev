#ifndef CVECTOR3_H
#define CVECTOR3_H

typedef struct CVECTOR3 {
	public:
		CVECTOR3(float x, float y, float z);

		CVECTOR3 operator+(CVECTOR3 vVector);
		CVECTOR3 operator-(CVECTOR3 vVector);
		CVECTOR3 operator*(float num);
		CVECTOR3 operator/(float num);

		float X, Y, Z;
} vector3;

#endif

