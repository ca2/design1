#include "framework.h"


namespace devedge
{


   project::project(::aura::application * papp) :
      ::object(papp),
      m_source(papp),
      m_headers(papp)
   {
      m_psolution = NULL;
   }


   bool project::load(solution * psolution, sp(::xml::node) pnodeProject)
   {
      
      m_psolution = psolution;
      
      m_pnodeProject = pnodeProject;
      
      m_strProjectPath = calc_project_dir();
      
      m_strProjectDir = m_strProjectPath.folder();
   
      if(!m_source.load(this))
         return false;

      if(!m_headers.load(this))
         return false;

      return true;


   }


   string project::calc_project_dir()
   {

      ::file::path str = m_psolution->m_pdoc->get_file_path();

      str = str.folder();

      str.go_up(3);

      return str /  m_pnodeProject->attr("path").get_string() / "project.ca2project";

   }

   elemental::e_solution_type project::get_solution_type()
   {
      return solution_type_project;
   }


} // namespace devedge





