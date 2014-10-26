/**
 *  @file HepMC3_fileIO_example.cc
 *  @brief Test of file I/O
 *
 *  Parses HepMC3 file and saves it as a new HepMC3 file.
 *  The resulting file should be an exact copy of the input file
 *
 */
#include "HepMC/GenEvent.h"
#include "HepMC/IO/IO_GenEvent.h"

#include <iostream>
using namespace HepMC;
using std::cout;
using std::endl;

int main(int argc, char **argv) {

    if( argc<3 ) {
        cout << "Usage: " << argv[0] << " <HepMC3_input_file> <output_file>" << endl;
        exit(-1);
    }

    IO_GenEvent input_file (argv[1],std::ios::in);
    IO_GenEvent output_file(argv[2],std::ios::out);

    int events_parsed = 0;

    while(!input_file.rdstate()) {
        GenEvent evt(Units::GEV,Units::MM);

        // Read event from input file
        input_file.fill_next_event(evt);

        // If reading failed - exit loop
        if( input_file.rdstate() ) break;

        // Save event to output file
        output_file.write_event(evt);

        if(events_parsed==0) {
            cout << " First event: " << endl;
            evt.print();
        }

        ++events_parsed;
        if( events_parsed%100 == 0 ) cout<<"Events parsed: "<<events_parsed<<endl;
    }

    input_file.close();
    output_file.close();

    return 0;
}