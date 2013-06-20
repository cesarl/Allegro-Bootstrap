#ifndef		__VECTOR3D_H__
#define		__VECTOR3D_H__

class		Vector3d
{
private:
  double	_x;
  double	_y;
  double	_z;
public:
  Vector3d();
  Vector3d(const Vector3d& other);
  Vector3d(double x, double y, double z);
  ~Vector3d();
  double	getX() const { return this->_x; }
  void		setX(double v) { this->_x = v; }
  double	getY() const { return this->_y; }
  void		setY(double v) { this->_y = v; }
  double	getZ() const { return this->_z; }
  void		setZ(double v) { this->_z = v; }
  Vector3d	&operator=(float value);
  Vector3d	&operator+=(float value);
  Vector3d	&operator-=(float value);
  Vector3d	&operator*=(float value);
  Vector3d	&operator/=(float value);
  Vector3d	&operator+=(const Vector3d& other);
  Vector3d	&operator-=(const Vector3d& other);
  Vector3d	&operator*=(const Vector3d& other);
  Vector3d	&operator/=(const Vector3d& other);
  bool		operator==(const Vector3d& other) const;
  bool		operator!=(const Vector3d& other) const;
  Vector3d	&operator=(const Vector3d& other);
  double	distance(const Vector3d& other);
  double	length();
  double	dotProduct(const Vector3d& other);
  Vector3d	crossProduct(const Vector3d& other);
  Vector3d	normal();
  double	angle(const Vector3d& other);
};

Vector3d	operator+(const Vector3d& left, const Vector3d& right);
Vector3d	operator-(const Vector3d& left, const Vector3d& right);
Vector3d	operator*(const Vector3d& left, const Vector3d& right);
Vector3d	operator/(const Vector3d& left, const Vector3d& right);

#endif		// __VECTOR3D_H__
