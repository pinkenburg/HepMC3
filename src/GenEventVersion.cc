/**
 *  @file GenEventVersion.cc
 *  @brief Implementation of \b class HepMC3::GenEventVersion
 *
 *  @date Created       <b> 19th March 2014 </b>
 *  @date Last modified <b> 25th March 2014 </b>
 */
#include <iostream>
#include "HepMC3/GenEventVersion.h"
#include "HepMC3/Log.h"
using std::endl;

namespace HepMC3 {

GenEventVersion::GenEventVersion(int number, const char *name):
m_version(number),
m_name(name) {
}

GenEventVersion::~GenEventVersion() {
    for( vector<GenParticle*>::const_iterator i = m_particles.begin(); i != m_particles.end(); ++i ) {
        delete (*i);
    }
    for( vector<GenVertex*>::const_iterator i = m_vertices.begin(); i != m_vertices.end(); ++i ) {
        delete (*i);
    }
}

void GenEventVersion::record_change(GenParticle *p) {

    DEBUG( 10, "GenEventVersion: adding particle: "<<p->barcode()<<" ("<<p->pdg_id()<<") " )

    // First entry
    if( m_particles.size() == 0 ) {
        m_particles.push_back( p );
        DEBUG( 10, "GenEventVersion: particle added to version "<<m_version<< " as first: "<<p->barcode()<<" ("<<p->pdg_id()<<") " )
    }
    // Entry not within the list range
    else if( m_particles.back()->barcode() < p->barcode() ) {
        m_particles.push_back( p );
        DEBUG( 10, "GenEventVersion: particle added to version "<<m_version<< " as last: "<<p->barcode()<<" ("<<p->pdg_id()<<") " )
    }
    // Particle within the list range
    else {
        for( vector<GenParticle*>::iterator i = m_particles.begin(); i != m_particles.end(); ++i ) {

            // Already exists on the list - do nothing
            if ((*i)->barcode() == p->barcode() ) return;

            // Particle does not exist on the list - insert (max O(n))
            if ((*i)->barcode() >  p->barcode() ) {
                m_particles.insert( i, p );
                DEBUG( 10, "GenEventVersion: particle added to version "<<m_version<< " in-between: "<<p->barcode()<<" ("<<p->pdg_id()<<") " )
            }
        }
    }
}

void GenEventVersion::record_change(GenVertex *v) {

    DEBUG( 10, "GenEventVersion: adding vertex: "<<v->barcode() )

    // First entry
    if( m_vertices.size() == 0 ) {
        m_vertices.push_back( v );
        DEBUG( 10, "GenEventVersion: vertex added to version "<<m_version<< " as first: "<<v->barcode() )
    }
    // Entry not within the list range
    else if( m_vertices.back()->barcode() > v->barcode() ) {
        m_vertices.push_back( v );
        DEBUG( 10, "GenEventVersion: vertex added to version "<<m_version<< " as last: "<<v->barcode() )
    }
    // Particle within the list range
    else {
        for( vector<GenVertex*>::iterator i = m_vertices.begin(); i != m_vertices.end(); ++i  ) {

            // Already exists on the list - do nothing
            if ((*i)->barcode() == v->barcode() ) return;

            // Particle does not exist on the list - insert (max O(n))
            if ((*i)->barcode() >  v->barcode() ) {
                m_vertices.insert( i, v );
                DEBUG( 10, "GenEventVersion: vertex added to version "<<m_version<< " in-between: "<<v->barcode() )
            }
        }
    }
}

} // namespace HepMC3