#pragma once


namespace devedge
{


   class solution_document;
   class solution_view;


   class CLASS_DECL_DEVEDGE solution :
      virtual public ::devedge::elemental
   {
   public:
      
      
      xml::document                                               m_xmldoc;
      comparable_array < ::devedge::project * >                     m_projectptra;
      sp(solution_document)                                         m_pdoc;
      solution_view *                                             m_pview;
      string                                                      m_strSolutionPath;
      string                                                      m_strSolutionDir;


      solution(sp(solution_document) pdoc);


      bool load(var varFile, solution_view * pview);


      sp(::xml::node) node_get_projects();

      virtual e_solution_type get_solution_type();


   };


} // namespace devedge


