#include "framework.h"


namespace veritile
{


   main_document::main_document(::aura::application * papp) :
      ::object(papp),
      ::data::data_container_base(papp),
      ::user::document(papp)
   {

   }
   

   main_document::~main_document()
   {

   }


} // namespace syllomatter


