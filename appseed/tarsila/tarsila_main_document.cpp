#include "framework.h"


namespace tarsila
{


   main_document::main_document(::aura::application * papp) :
      ::object(papp),
      ::data::data_container_base(papp),
      ::user::controller(papp),
      ::user::document(papp)
   {

   }
   

   main_document::~main_document()
   {
   }


} // namespace syllomatter


