#include "framework.h"


namespace syllomatter
{


   filemanager_document::filemanager_document(::aura::application * papp) :
      element(papp),
      ::data::data_container_base(papp),
      ::aura::document(papp),
      ::userfs::document(papp),
      ::filemanager::manager(papp)
   {

   }


   filemanager_document::~filemanager_document()
   {

   }
   

}  //  namespace syllomatter


