#ifndef __HH_EVO_MODEL_TRNCMP
#define __HH_EVO_MODEL_TRNCMP

#include <evo/Metric.hh>
#include <evo/Encoding.hh>


namespace evo {

// =======================================================================================
class Model {
  // -------------------------------------------------------------------------------------
 protected:

 public:
  Model   ( void ) {};
  ~Model  ( void ) {};

  Metric*   alloc_metric   ( void ) { return (Metric*)0; };
  Encoding* alloc_encoding ( void ) { return (Encoding*)0; };
  

}; // end class Model


}; // end namespace evo


#endif
