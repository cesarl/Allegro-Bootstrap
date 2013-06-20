#include				<math.h>
#include				"Vector3d.hh"

Vector3d::Vector3d()
  : _x(0)
  , _y(0)
  , _z(0)
{
}

Vector3d::Vector3d(const Vector3d& other)
  : _x(other._x)
  , _y(other._y)
  , _z(other._z)
{
}

Vector3d::Vector3d(double x, double y, double z)
  : _x(x)
  , _y(y)
  , _z(z)
{
}

Vector3d::~Vector3d()
{
}

Vector3d				&Vector3d::operator+=(const Vector3d& other)
{
  this->_x += other._x;
  this->_y += other._y;
  this->_z += other._z;
  return (*this);
}

Vector3d				&Vector3d::operator-=(const Vector3d& other)
{
  this->_x -= other._x;
  this->_y -= other._y;
  this->_z -= other._z;
  return (*this);
}

Vector3d				&Vector3d::operator*=(const Vector3d& other)
{
  this->_x *= other._x;
  this->_y *= other._y;
  this->_z *= other._z;
  return (*this);
}

Vector3d				&Vector3d::operator/=(const Vector3d& other)

{
  this->_x /= other._x;
  this->_y /= other._y;
  this->_z /= other._z;
  return (*this);
}

Vector3d				&Vector3d::operator=(float value)
{
  this->_x = value;
  this->_y = value;
  this->_z = value;
  return (*this);
}

Vector3d				&Vector3d::operator+=(float value)
{
  this->_x += value;
  this->_y += value;
  this->_z += value;
  return (*this);
}

Vector3d				&Vector3d::operator-=(float value)
{
  this->_x -= value;
  this->_y -= value;
  this->_z -= value;
  return (*this);
}

Vector3d				&Vector3d::operator*=(float value)
{
  this->_x *= value;
  this->_y *= value;
  this->_z *= value;
  return (*this);
}

Vector3d				&Vector3d::operator/=(float value)
{
  this->_x /= value;
  this->_y /= value;
  this->_z /= value;
  return (*this);
}

Vector3d				operator+(const Vector3d& left, const Vector3d& right)
{
  Vector3d				tmp(left);

  tmp += right;
  return (tmp);
}

Vector3d				operator-(const Vector3d& left, const Vector3d& right)
{
  Vector3d				tmp(left);

  tmp -= right;
  return (tmp);
}

Vector3d				operator*(const Vector3d& left, const Vector3d& right)
{
  Vector3d				tmp(left);

  tmp *= right;
  return (tmp);
}

Vector3d				operator/(const Vector3d& left, const Vector3d& right)
{
  Vector3d				tmp(left);

  tmp /= right;
  return (tmp);
}

bool					Vector3d::operator==(const Vector3d& other) const
{
  return (
	  (((other._x - 0.0001f) < this->_x) && (this->_x < (other._x + 0.0001f))) &&
	  (((other._y - 0.0001f) < this->_y) && (this->_y < (other._y + 0.0001f))) &&
	  (((other._z - 0.0001f) < this->_z) && (this->_z < (other._z + 0.0001f))) );
}

bool					Vector3d::operator!=(const Vector3d& other) const
{
  return (!(*this == other));
}

Vector3d				&Vector3d::operator=(const Vector3d& other)
{
  this->_x = other._x;
  this->_y = other._y;
  this->_z = other._z;
  return *this;
}

double					Vector3d::distance(const Vector3d& other)
{
  return sqrt((other._x - this->_x) * (other._x - this->_x)
	      + (other._y - this->_y) * (other._y - this->_y));
}
double					Vector3d::length()
{
  return sqrt(this->_x * this->_x + this->_y * this->_y + this->_z * this->_z);
}

double					Vector3d::dotProduct(const Vector3d& other)
{
  return (this->_x * other._x + this->_y * other._y + this->_z * other._z);

}

Vector3d				Vector3d::crossProduct(const Vector3d& other)
{
  double nx = (this->_y * other._z) - (this->_z * other._y);
  double ny = (this->_z * other._x) - (this->_x * other._z);
  double nz = (this->_x * other._y) - (this->_y * other._x);

  return Vector3d(nx, ny, nz);
}

Vector3d				Vector3d::normal()
{
  double length;
  if (this->length() == 0)
    length = 0;
  else
    length = 1 / this->length();
  double nx = this->_x * length;
  double ny = this->_y * length;
  double nz = this->_z * length;
  return Vector3d(nx, ny, nz);
}

double					Vector3d::angle(const Vector3d& other)
{
  double dx = this->_x - other._x;
  double dy = this->_y - other._y;

  return (atan2(dy, dx) / M_PI * 180.0f);
}
