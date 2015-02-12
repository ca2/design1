#include "framework.h"


namespace devedge
{


   devedge::devedge(::aura::application * papp) :
      element(papp),
      ::aura::departament(papp)
   {

   }


   devedge::~devedge()
   {

   }


   bool devedge::initialize1()
   {

      System.factory().creatable_small < ::devedge::document > ();
      System.factory().creatable_small < ::devedge::child_frame > ();
      System.factory().creatable_small < ::devedge::view > ();
      System.factory().creatable_small < ::devedge::main_document > ();
      System.factory().creatable_small < ::devedge::main_frame > ();
      System.factory().creatable_small < ::devedge::pane_view > ();

      System.factory().creatable_small < ::devedge::solution_document > ();
      System.factory().cloneable_small < ::devedge::solution_view > ();

      System.factory().cloneable_small < ::devedge::project > ();
      System.factory().cloneable_small < ::devedge::folder > ();
      System.factory().cloneable_small < ::devedge::headers > ();
      System.factory().cloneable_small < ::devedge::source > ();
      System.factory().cloneable_small < ::devedge::file > ();

      System.factory().cloneable_small < ::devedge::front_document > ();
      System.factory().cloneable_small < ::devedge::front_child_frame > ();
      System.factory().cloneable_small < ::devedge::front_view > ();

      System.factory().cloneable_small < ::devedge::html_edit_document > ();
      System.factory().cloneable_small < ::devedge::html_edit_child_frame > ();
      System.factory().cloneable_small < ::devedge::html_edit_view > ();

      System.factory().cloneable_small < ::devedge::html_stage_document > ();
      System.factory().cloneable_small < ::devedge::html_stage_child_frame > ();
      System.factory().cloneable_small < ::devedge::html_stage_view > ();


      return true;

   }


   bool devedge::initialize3()
   {

      m_ptemplateEdge = new ::user::single_document_template(
         get_app(), 
         "devedge/frame", 
         System.type_info < ::devedge::main_document > (), 
         System.type_info < ::devedge::main_frame > (), 
         System.type_info < ::devedge::pane_view > ());

      Application.add_document_template(m_ptemplateEdge);

      m_ptemplate_devedge = new ::user::multiple_document_template(
         get_app(), 
         "devedge/frame", 
         System.type_info < document > (), 
         System.type_info < ::devedge::child_frame > (), 
         System.type_info < view > ());

      Application.add_document_template(m_ptemplate_devedge);

      m_ptemplate_solution = new ::user::single_document_template(
         get_app(), 
         "devedge/frame", 
         System.type_info < ::devedge::solution_document > (), 
         System.type_info < ::devedge::child_frame > (), 
         System.type_info < ::devedge::solution_view > ());

      Application.add_document_template(m_ptemplate_solution);

      m_ptemplateHtmlEdit = new ::user::single_document_template(
         get_app(), 
         "devedge/frame", 
         System.type_info < ::devedge::html_edit_document > (), 
         System.type_info < ::devedge::html_edit_child_frame > (), 
         System.type_info < ::devedge::html_edit_view > ());

      Application.add_document_template(m_ptemplateHtmlEdit);

      m_ptemplateHtmlStage = new ::user::single_document_template(
         get_app(), 
         "devedge/frame", 
         System.type_info < ::devedge:: html_stage_document > (),
         System.type_info < ::devedge::html_stage_child_frame > (), 
         System.type_info < ::devedge::html_stage_view > ());

      Application.add_document_template(m_ptemplateHtmlStage);

      m_ptemplateFront = new ::user::single_document_template(
         get_app(),
         "devedge/frame", 
         System.type_info < ::devedge::front_document > (),
         System.type_info < ::devedge::front_child_frame > (), 
         System.type_info < ::devedge::front_view > ());

      Application.add_document_template(m_ptemplateFront);

      return true;

   }


} // namespace devedge





