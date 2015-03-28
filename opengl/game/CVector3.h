#ifndef CVECTOR3_H
#define CVECTOR3_H

struct CVector3 {

public:
  CVector3() {}
	~CVector3() {}
  
  CVector3(float x, float y, float z) {
		x = x;
		y = y;
		z = z;
  }
  
  CVector3 operator+(CVector3 vVector) {
    return CVector3(vVector.x + x, vVector.y + y, vVector.z + z);
  }
  
  CVector3 operator-(CVector3 vVector) {
    return CVector3(x - vVector.x, y - vVector.y, z - vVector.z);
  }
  
  CVector3 operator*(float num) {
    return CVector3(x * num, y * num, z * num);
  }
  
  CVector3 operator/(float num) {
    return CVector3(x / num, y / num, z / num);
  }
  
  float x, y, z;

  
};

#endif
