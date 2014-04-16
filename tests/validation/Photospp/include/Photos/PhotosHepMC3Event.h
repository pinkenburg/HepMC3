#ifndef _PhotosHepMC3Event_h_included_
#define _PhotosHepMC3Event_h_included_
/**
 *  @file PhotosHepMC3Event.h
 *  @brief Definition of \b class Photospp::PhotosHepMC3Event
 *
 *  @class PhotosHepMC3Event
 *  @brief Interface to HepMC3::GenEvent objects
 *
 *  @implements Photospp::PhotosEvent
 *
 *  @date Created       <b> 31 March 2014 </b>
 *  @date Last modified <b> 16 April 2014 </b>
 */
#include "Photos/PhotosEvent.h"
#include "Photos/PhotosParticle.h"
#include "HepMC3/GenEvent.h"
#include <vector>

namespace Photospp
{

class PhotosHepMC3Event : public PhotosEvent
{
//
// Constructors
//
public:
    /** Default constructor
     *  Fills particles list
     */
    PhotosHepMC3Event(HepMC3::GenEvent * event);
    /** Default destructor */
    ~PhotosHepMC3Event();

//
// Functions
//
public:
    /** Print HepMC3 event */
    void print()                                   { if(!m_event) return; m_event->print(); }
//
// Accessors
//
public:
    HepMC3::GenParticle& new_particle()      { return m_event->new_particle(); } //!< Create new particle
    HepMC3::GenVertex&   new_vertex()        { return m_event->new_vertex();   } //!< Create new vertex

    int  last_version()                            { return m_event->last_version(); } //!< Get last version of HepMC3 event
    std::vector<PhotosParticle*> getParticleList() { return m_particles; }    //!< Get particle list
//
// Fields
//
private:
    HepMC3::GenEvent              *m_event;          //!< HepMC3 event pointer
    std::vector<PhotosParticle *>  m_particles;      //!< List of particles
};

} // namespace Photospp
#endif
