
#ifndef PARTICLE_SIMULATION_H
#define PARTICLE_SIMULATION_H

#include "algorithm.h"
#include "particle.h"
#include "minHeapTree.h"

#include <vector>
#include "TRandom3.h"
#include "TCanvas.h"
#include "TGraph.h"

class Event {
 public:
  Event(double,unsigned int,unsigned int);
  ~Event();

  bool operator>(const Event&) const;
  bool operator<(const Event&) const;
  bool operator==(const Event&) const;
  bool operator>=(const Event&) const;
  bool operator<=(const Event&) const;

 private:
  Event();

 public:
  double dT;
  unsigned int indexA;
  unsigned int indexB;
};

Event::Event() {}
Event::Event( double T,unsigned int A,unsigned int B)
: dT( T ), indexA( A ), indexB( B ) {}
Event::~Event() {}
bool Event::operator>( const Event &other ) const { return dT > other.dT; }
bool Event::operator<( const Event &other ) const { return dT < other.dT; }
bool Event::operator==( const Event &other ) const { return dT == other.dT; }
bool Event::operator>=( const Event &other ) const { return ! (*this < other); }
bool Event::operator<=( const Event &other ) const { return ! (*this > other); }

/* =============================================================== */

class particleSimulation : public algorithm {
 public:
  particleSimulation(const int,const double,const double);
  virtual ~particleSimulation();

  virtual const std::string description() const;

  void move(const double);
  void draw(TCanvas&,const int color = 1);
  const double timeAtNextCollision() const;

 protected:
  particleSimulation();

  void generateParticles(const int);
  void generatePriorityQueue();

 private:
  std::unique_ptr< TRandom3 > m_rdm;
  std::unique_ptr< minHeapTree< Event > > m_priorityQueue;
  std::unique_ptr< TGraph > m_box;
  std::vector< std::unique_ptr< particle > > m_particles;

 private:
  double m_boxL;
  double m_boxH;
};

particleSimulation::particleSimulation()
: m_rdm( new TRandom3(0) ),
  m_priorityQueue( new minHeapTree< Event >() ),
  m_boxL( 0 ), 
  m_boxH( 0 ),
  m_box( nullptr ) {}
particleSimulation::particleSimulation( const int N,const double L,const double H )
: m_rdm( new TRandom3(0) ),
  m_priorityQueue( new minHeapTree< Event >() ),
  m_boxL( L ),
  m_boxH( H ),
  m_box( nullptr ) 
{ 
  this->generateParticles( N ); 
  this->generatePriorityQueue();
}
particleSimulation::~particleSimulation() {}

const std::string particleSimulation::description() const {
  std::string output = "Algorithm for simulating the behaviour of some gas particles within a box.";
  return output;
}

void particleSimulation::generateParticles( const int N ) {
  for ( int i(0); i<N; i++ ) {
    std::unique_ptr< particle > toAdd( new particle( m_rdm->Rndm() * m_boxL,m_rdm->Rndm() * m_boxH, 1 ) );
    toAdd->setVelocity( m_rdm->Rndm() * 2 - 1,m_rdm->Rndm() * 2 - 1 );
    m_particles.push_back( std::move(toAdd) );
  }
}

void particleSimulation::generatePriorityQueue() {

  for ( unsigned int i(0); i<m_particles.size(); i++ ) {

    double mindT = -1;
    unsigned int index = 0;
    for ( unsigned int j(i+1); j<m_particles.size(); j++ ) {
      double dT = m_particles.at(i)->timeToNextCollision( *m_particles.at(j) );
      if ( dT < 0 ) continue;
      if ( mindT > 0 && dT > mindT ) continue;
      mindT = dT;
      index = j;
    }

    if ( mindT < 0 ) continue;
    if ( index == 0 ) continue;
    m_priorityQueue->add( Event( mindT,i,index) );
  }

}

void particleSimulation::move( const double dT ) {
  for ( unsigned int i(0); i<m_particles.size(); i++ )
    m_particles.at(i)->move( dT );
}

const double particleSimulation::timeAtNextCollision() const { return m_priorityQueue->size(); }

void particleSimulation::draw( TCanvas &c0 , const int color ) {
  if ( not m_box ) {
    m_box = std::unique_ptr< TGraph >( new TGraph() );
    m_box->SetPoint( 0,0,0 );
    m_box->SetPoint( 1,m_boxL,0 );
    m_box->SetPoint( 2,m_boxL,m_boxH );
    m_box->SetPoint( 3,0,m_boxH );
    m_box->SetPoint( 4,0,0 );
  }

  TGraph points;
  points.SetMarkerStyle(20);
  points.SetMarkerSize(0.6);
  points.SetMarkerColor(color);

  for ( unsigned int i(0); i<m_particles.size(); i++ ) {
    double x = m_particles.at(i)->x();
    double y = m_particles.at(i)->y();
    points.SetPoint( i,x,y );
  }

  c0.cd();
  m_box->Draw("APL");
  points.Draw("PSAME");
  c0.Draw();
  c0.Update();
}

#endif
