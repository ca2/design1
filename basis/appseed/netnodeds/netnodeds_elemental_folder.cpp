#include "framework.h"


namespace netnodeds
{


   folder::folder(::aura::application * papp) :
      ::object(papp),
      spa(file)(papp)
   {
   }


   bool folder::load(project * pproject, const char * pszFilter)
   {
      
      m_pproject = pproject;
      
      m_strFilter = pszFilter;
      
      ::file::listing straPath(get_app());
      
      straPath.ls_pattern(pproject->m_strProjectDir, m_strFilter);
      
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


} // namespace netnodeds



