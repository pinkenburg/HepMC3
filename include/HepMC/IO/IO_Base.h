#ifndef  HEPMC_IO_BASE_H
#define  HEPMC_IO_BASE_H
/**
 *  @file  IO_Base.h
 *  @brief Definition of \b class IO_Base
 *
 *  @class HepMC::IO_Base
 *  @brief Base class for all I/O interfaces
 *
 *  @ingroup IO
 *
 */

namespace HepMC {

class GenEvent;

class IO_Base {
//
// Constructors
//
public:
    /** Virtual destructor */
    virtual ~IO_Base() {}

//
// Abstract functions
//
public:
    /** @brief Write event */
    virtual void write_event(const GenEvent &evt) = 0;

    /** @brief Get event */
    virtual bool fill_next_event(GenEvent &evt)   = 0;
};

} // namespace HepMC

#endif