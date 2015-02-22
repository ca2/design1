

#include "framework.h"


namespace netnodeds
{


   solution::solution(sp(solution_document) pdoc) :
      element(pdoc->get_app()),
      m_pdoc(pdoc),
      m_xmldoc(pdoc->get_app())
   {
   }


   bool solution::load(var varFile, solution_view * pview)
   {
      
      m_pview = pview;

      if(!m_xmldoc.load(Application.file().as_string(varFile)))
         return false;

      return m_pview->load();

   }


   elemental::e_solution_type solution::get_solution_type()
   {
      return solution_type_folder;
   }

   sp(::xml::node) solution::node_get_projects()
   {


      return m_xmldoc.get_root()->get_child("projects");


   }




} // namespace netnodeds