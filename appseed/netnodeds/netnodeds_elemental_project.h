#pragma once


namespace netnodeds
{


   class solution;


   class CLASS_DECL_DESIGN_NETNODEDS project :
      virtual public ::netnodeds::elemental
   {
   public:
      
      
      sp(::xml::node)                  m_pnodeProject;
      bool                             m_bFramework;
      source                           m_source;
      headers                          m_headers;
      solution *                       m_psolution;
      ::file::path                     m_strProjectPath;
      ::file::path                     m_strProjectDir;


      project(::aura::application * papp);

      virtual e_solution_type get_solution_type();

      ::file::path calc_project_dir();

      bool load(solution * pdoc, sp(::xml::node) pnodeProject);


   };


}


