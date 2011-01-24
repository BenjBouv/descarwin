
#include "evalBestPlanDump.h"

namespace daex {

void evalBestMakespanPlanDump::call( Decomposition & eo )
{
    if( eo.plan().makespan() < _best ) {
        _best = eo.plan().makespan();
        dump( eo );
    } // if better
}

void evalBestFitnessPlanDump::call( Decomposition & eo )
{
    // Note: in EO, maximizing by default, later overloaded for minimizing
    if( eo.fitness() > _best ) {
        _best = eo.fitness();
        dump( eo );
    } // if better
}

} // namespace daex

