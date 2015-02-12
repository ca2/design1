#include "framework.h"


namespace devedge
{


   folder::folder(::aura::application * papp) :
      element(papp),
      spa(file)(papp)
   {
   }


   bool folder::load(project * pproject, const char * pszFilter)
   {
      
      m_pproject = pproject;
      
      m_strFilter = pszFilter;
      
      stringa straPath;
      
      Application.dir().ls_pattern(pproject->m_strProjectDir, m_strFilter, &straPath);
      
      for(index i = 0; i < straPath.get_count(); i++)
      {
         
         sp(file) pfile = add_new();

         pfile->initialize(this, straPath[i]);

      }
      
      return true;

   }

   index folder::find(const char * pszName)
   {
      for(index i = 0; i < get_count(); i++)
      {
         file & file = operator()(i);
         if(file.m_strName.CompareNoCase(pszName) == 0)
            return i;
      }
      return -1;
   }

   bool folder::has(const char * pszName)
   {
      return find(pszName) >= 0;
   }

   elemental::e_solution_type folder::get_solution_type()
   {
      return solution_type_folder;
   }


} // namespace devedge



