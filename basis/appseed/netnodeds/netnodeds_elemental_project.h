#pragma once


namespace devedge
{


   class solution;


   class CLASS_DECL_DEVEDGE project :
      virtual public ::devedge::elemental
   {
   public:
      
      
      sp(::xml::node)                      m_pnodeProject;
      bool                             m_bFramework;
      source                           m_source;
      headers                          m_headers;
      solution *                       m_psolution;
      string                           m_strProjectPath;
      string                           m_strProjectDir;


      project(::aura::application * papp);

      virtual e_solution_type get_solution_type();

      string calc_project_dir();

      bool load(solution * pdoc, sp(::xml::node) pnodeProject);


   };


}


