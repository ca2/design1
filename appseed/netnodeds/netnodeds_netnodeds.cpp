#include "framework.h"


namespace netnodeds
{


   netnodeds::netnodeds(::aura::application * papp) :
      element(papp),
      ::aura::departament(papp)
   {

   }


   netnodeds::~netnodeds()
   {

   }


   bool netnodeds::initialize1()
   {

      System.factory().creatable_small < ::netnodeds::document > ();
      System.factory().creatable_small < ::netnodeds::child_frame > ();
      System.factory().creatable_small < ::netnodeds::view > ();
      System.factory().creatable_small < ::netnodeds::main_document > ();
      System.factory().creatable_small < ::netnodeds::main_frame > ();
      System.factory().creatable_small < ::netnodeds::pane_view > ();

      System.factory().creatable_small < ::netnodeds::solution_document > ();
      System.factory().cloneable_small < ::netnodeds::solution_view > ();

      System.factory().cloneable_small < ::netnodeds::project > ();
      System.factory().cloneable_small < ::netnodeds::folder > ();
      System.factory().cloneable_small < ::netnodeds::headers > ();
      System.factory().cloneable_small < ::netnodeds::source > ();
      System.factory().cloneable_small < ::netnodeds::file > ();

      System.factory().cloneable_small < ::netnodeds::front_document > ();
      System.factory().cloneable_small < ::netnodeds::front_child_frame > ();
      System.factory().cloneable_small < ::netnodeds::front_view > ();

      System.factory().cloneable_small < ::netnodeds::html_edit_document > ();
      System.factory().cloneable_small < ::netnodeds::html_edit_child_frame > ();
      System.factory().cloneable_small < ::netnodeds::html_edit_view > ();

      System.factory().cloneable_small < ::netnodeds::html_stage_document > ();
      System.factory().cloneable_small < ::netnodeds::html_stage_child_frame > ();
      System.factory().cloneable_small < ::netnodeds::html_stage_view > ();


      return true;

   }


   bool netnodeds::initialize3()
   {

      m_ptemplateEdge = new ::user::single_document_template(
         get_app(), 
         "netnodeds/frame", 
         System.type_info < ::netnodeds::main_document > (), 
         System.type_info < ::netnodeds::main_frame > (), 
         System.type_info < ::netnodeds::pane_view > ());

      Application.add_document_template(m_ptemplateEdge);

      m_ptemplate_netnodeds = new ::user::multiple_document_template(
         get_app(), 
         "netnodeds/frame", 
         System.type_info < document > (), 
         System.type_info < ::netnodeds::child_frame > (), 
         System.type_info < view > ());

      Application.add_document_template(m_ptemplate_netnodeds);

      m_ptemplate_solution = new ::user::single_document_template(
         get_app(), 
         "netnodeds/frame", 
         System.type_info < ::netnodeds::solution_document > (), 
         System.type_info < ::netnodeds::child_frame > (), 
         System.type_info < ::netnodeds::solution_view > ());

      Application.add_document_template(m_ptemplate_solution);

      m_ptemplateHtmlEdit = new ::user::single_document_template(
         get_app(), 
         "netnodeds/frame", 
         System.type_info < ::netnodeds::html_edit_document > (), 
         System.type_info < ::netnodeds::html_edit_child_frame > (), 
         System.type_info < ::netnodeds::html_edit_view > ());

      Application.add_document_template(m_ptemplateHtmlEdit);

      m_ptemplateHtmlStage = new ::user::single_document_template(
         get_app(), 
         "netnodeds/frame", 
         System.type_info < ::netnodeds:: html_stage_document > (),
         System.type_info < ::netnodeds::html_stage_child_frame > (), 
         System.type_info < ::netnodeds::html_stage_view > ());

      Application.add_document_template(m_ptemplateHtmlStage);

      m_ptemplateFront = new ::user::single_document_template(
         get_app(),
         "netnodeds/frame", 
         System.type_info < ::netnodeds::front_document > (),
         System.type_info < ::netnodeds::front_child_frame > (), 
         System.type_info < ::netnodeds::front_view > ());

      Application.add_document_template(m_ptemplateFront);

      return true;

   }


} // namespace netnodeds





