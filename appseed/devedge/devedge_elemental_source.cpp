#include "framework.h"


namespace devedge
{


   source::source(::aura::application * papp) :
      ::object(papp),
      spa(file)(papp),
      folder(papp)
   {
      m_bFramework = false;
   }

   bool source::load(project * pproject)
   {
      
      if(!folder::load(pproject, "*.cpp"))
         return false;

      m_bFramework = has("framework.cpp");

      return true;

   }


   elemental::e_solution_type source::get_solution_type()
   {
      return solution_type_source;
   }


} // namespace devedge


