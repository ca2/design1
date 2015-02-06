#include "framework.h"


namespace tarsila
{


   main_document::main_document(::aura::application * papp) :
      element(papp),
      ::data::data_container_base(papp),
      ::aura::document(papp)
   {
   }
   

   main_document::~main_document()
   {
   }


} // namespace syllomatter


