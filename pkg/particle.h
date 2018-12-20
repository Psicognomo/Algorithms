
#ifndef PARTICLE_H
#define PARTICLE_H

#include <iostream>
#include <cmath>

class particle {
 public:
  particle(double,double,double,double radius=1);
  particle(const particle&);
  ~particle();

  void setVelocity(double,double);

  inline const double x() const;
  inline const double y() const;
  inline const double vx() const;
  inline const double vy() const;
  inline const double mass() const;
  inline const double radius() const;

  particle& move(const double);

  const double timeToNextCollision(const particle&) const;
  inline const double movementX(const double) const;
  inline const double movementY(const double) const;

  const double distance(const particle&) const;

  void impact(particle&);

  void print() const {
    std::cout<<"=========="<<std::endl;
    std::cout<<"Position : "<<m_x<<","<<m_y<<std::endl;
    std::cout<<"Velocity : "<<m_vx<<","<<m_vy<<std::endl;
    std::cout<<"Mass: "<<m_mass<<std::endl;
    std::cout<<"Radius: "<<m_radius<<std::endl;
    std::cout<<"=========="<<std::endl;
  }

 private:
  particle();

 private:
  double m_x;
  double m_y;

  double m_vx;
  double m_vy;

  double m_mass;
  double m_radius;
};

particle::particle() {}
particle::particle( double x,double y,double mass,double radius ) 
: m_x( x ),
  m_y( y ),
  m_mass( mass ),
  m_radius( radius ) {}
particle::particle( const particle &other )
: m_x( other.m_x ),
  m_y( other.m_y ),
  m_mass( other.m_mass ),
  m_radius( other.m_radius ) {}
particle::~particle() {}

void particle::setVelocity( double Vx,double Vy ) {
  m_vx = Vx;
  m_vy = Vy;
}

const double particle::x() const { return m_x; }
const double particle::y() const { return m_y; }
const double particle::vx() const { return m_vx; }
const double particle::vy() const { return m_vy; }
const double particle::mass() const { return m_mass; }
const double particle::radius() const { return m_radius; }

particle& particle::move( const double dT ) {
  m_x += this->movementX( dT );
  m_y += this->movementY( dT );
  return *this;
}

const double particle::timeToNextCollision( const particle &other ) const {
  double dT = 0;
  if ( ( other.m_vx - m_vx) != 0 ) 
    dT = ( m_x - other.m_x ) / ( other.m_vx - m_vx);
  else if ( ( other.m_vy - m_vy) != 0 )
    dT = ( m_y - other.m_y ) / ( other.m_vy - m_vy);
  else 
    return -1;

  //  this->print();
  //  other.print();

  particle copyThis( *this );
  particle copyOther( other );
  copyThis.move( dT );
  copyOther.move( dT );

  //  std::cout<<"==== THIS: "<< copyThis.x() << " , "<<copyThis.y() <<std::endl;
  //  std::cout<<"==== OTHER: "<< copyOther.x() << " , "<<copyOther.y() <<std::endl;
  //  std::cout<<"    Time: "<<dT<<std::endl;
  //  std::cout<<"    Distance: "<< copyThis.distance( copyOther ) << std::endl;
  //  std::cout<<"      -- : "<< (m_radius + other.m_radius) << std::endl;

  double minDistance = m_radius + other.m_radius;

  if ( copyThis.distance( copyOther ) < minDistance )
    return dT;

  return -1;
}
inline const double particle::movementX( const double dT ) const { return m_vx * dT; }
inline const double particle::movementY( const double dT ) const { return m_vy * dT; }

const double particle::distance( const particle &other ) const { 
  const double deltaX = this->x() - other.x();
  const double deltaY = this->y() - other.y();
  //  std::cout<<"Delta X: "<< deltaX << std::endl;
  //  std::cout<<"Delta Y: "<< deltaY << std::endl;
  return sqrt( deltaX*deltaX + deltaY*deltaY );
}

void particle::impact( particle &other ) {
  const double relativeVx = other.m_vx - m_vx;
  const double relativeVy = other.m_vy - m_vy;

  double finalV3X = 2 * other.m_mass / ( m_mass + other.m_mass ) * relativeVx + m_vx;
  double finalV3Y = 2 *other.m_mass / ( m_mass + other.m_mass ) * relativeVy + m_vy;

  double finalV4X = ( other.m_mass - m_mass ) / ( m_mass + other.m_mass ) * relativeVx + m_vx;
  double finalV4Y = ( other.m_mass - m_mass ) / ( m_mass + other.m_mass ) * relativeVy + m_vy;

  this->setVelocity( finalV3X,finalV3Y );
  other.setVelocity( finalV4X,finalV4Y );  
}

#endif

