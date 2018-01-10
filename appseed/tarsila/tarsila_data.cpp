#include "framework.h"


namespace tarsila
{


   data::data(::aura::application * papp):
      ::object(papp),
      ::data::data(papp),
      m_drawing(papp)
   {
      m_drawing.m_emode = drawing::mode_selection;

   }



   void data::xml_import(::xml::input_tree & xmlif)
   {

      xmlif.import_node("drawing",m_drawing);

   }

   void data::xml_export(::xml::output_tree & xmlof)
   {

      xmlof.export_node("drawing",m_drawing);

   }



} // namespace tarsila







