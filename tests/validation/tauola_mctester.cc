#include "Tauola/Tauola.h"
#include "Tauola/TauolaHepMC3Event.h"
#include "Tauola/TauolaHepMC3Particle.h"

//HepMC3 headers
#include "HepMC3/GenEvent.h"
#include "HepMC3/GenParticle.h"

// MC-TESTER header
#include "Generate.h"
#include "Setup.H"
#include "HepMC3Event.h"

#include "tauola_make_simple_event.h"
using namespace std;
using namespace Tauolapp;


/** example main for decaying a stop with modified tauola */
int main(void){

    int NumberOfEvents = 10000;

    //These three lines are not really necessary since they are the default
    Tauola::setDecayingParticle(15);
    Tauola::setSameParticleDecayMode(0);
    Tauola::setOppositeParticleDecayMode(0);

    Tauola::initialize();

    MC_Initialize();

    Setup::decay_particle = 15;

    // Begin event loop. Generate event.
    for (int iEvent = 0; iEvent < NumberOfEvents; ++iEvent) {
        if(iEvent%1000==0) cout<<iEvent<<endl;

        HepMC3::GenEvent * event = tauola_make_simple_event();
        event->set_print_precision(8);

        //cout << "BEFORE:"<<endl;
        //event->print();

        TauolaHepMC3Event *t_event = new TauolaHepMC3Event(event);
        t_event->decayTaus();

        // Run MC-TESTER on the event
        HepMC3Event temp_event(*event,false);
        MC_Analyze(&temp_event);

        //cout << "AFTER:"<<endl;
        //event->print();

        //clean up
        delete event;
        delete t_event;
    }
    // This is an access to old FORTRAN info on generated tau sample.
    // That is why it refers to old version number (eg. 2.7) for TAUOLA.
    Tauola::summary();
    MC_Finalize();
}

