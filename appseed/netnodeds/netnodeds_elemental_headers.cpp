#include "framework.h"


namespace netnodeds
{


   headers::headers(::aura::application * papp) :
      ::object(papp),
      spa(file) (papp),
      folder(papp)
   {
      m_bFramework = false;
   }


   bool headers::load(project * pproject)
   {
      
      if(!folder::load(pproject, "*.h"))
         return false;

      m_bFramework = has("framework.h");

      return true;

   }


   elemental::e_solution_type headers::get_solution_type()
   {
      return solution_type_headers;
   }


} // namespace netnodeds



