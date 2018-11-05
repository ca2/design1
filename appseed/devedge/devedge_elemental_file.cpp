#include "framework.h"

namespace devedge
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

      ::devedge::devedge & devedge = Application.devedge();
      sp(::create) cc(get_app());
      cc->m_spCommandLine->m_varFile = m_strPath;
      cc->m_puiParent = puieParent;
      devedge.m_ptemplate_devedge->request_create(cc);

      m_pdocument = ::user::get_document(cc);

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

} // namespace devedge