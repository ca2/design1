#include "framework.h"


namespace devedge
{


   project::project(::aura::application * papp) :
      element(papp),
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
      
      m_strProjectDir = System.dir().name(m_strProjectPath);
   
      if(!m_source.load(this))
         return false;

      if(!m_headers.load(this))
         return false;

      return true;


   }


   string project::calc_project_dir()
   {

      string str = m_psolution->m_pdoc->get_path_name();

      str = System.dir().name(str);

      System.file().path().eat_end_level(str, 3, "\\");

      return System.dir().path(str, m_pnodeProject->attr("path").get_string(), "project.ca2project");

   }

   elemental::e_solution_type project::get_solution_type()
   {
      return solution_type_project;
   }


} // namespace devedge





