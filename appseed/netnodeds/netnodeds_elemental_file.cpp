#include "framework.h"


namespace netnodeds
{


   file::file(::aura::application * papp) : 
      ::object(papp)
   {   

      m_pdocument = NULL;

   }


   void file::initialize(folder * pfolder, const char * pszPath)
   {
      m_pfolder = pfolder;
      m_strPath = pszPath;
      m_strName = m_strPath.name();
   }


   void file::open(sp(::user::interaction) puieParent)
   {

      ::netnodeds::netnodeds & netnodeds = Application.netnodeds();
      sp(::create) cc(get_app());
      cc->m_spCommandLine->m_varFile = m_strPath;
      cc->m_puiParent = puieParent;
      m_pdocument =  (netnodeds.m_ptemplate_netnodeds->open_document_file(cc));

   }


   void file::close()
   {
      if(m_pdocument != NULL)
      {
         m_pdocument->on_close_document();
      }
   }

   elemental::e_solution_type file::get_solution_type()
   {
      return solution_type_file;
   }

} // namespace netnodeds