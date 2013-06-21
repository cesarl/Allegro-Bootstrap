#ifndef		__VECTOR3D_H__
#define		__VECTOR3D_H__

class		Vector3d
{
public:
  double	x;
  double	y;
  double	z;
public:
  Vector3d();
  Vector3d(const Vector3d& other);
  Vector3d(double x, double y, double z);
  ~Vector3d();
  double	getX() const { return this->x; }
  void		setX(double v) { this->x = v; }
  double	getY() const { return this->y; }
  void		setY(double v) { this->y = v; }
  double	getZ() const { return this->z; }
  void		setZ(double v) { this->z = v; }
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
