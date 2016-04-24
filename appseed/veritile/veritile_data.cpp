#include "framework.h"


namespace veritile
{


   data::data(::aura::application * papp):
      ::object(papp),
      ::data::data(papp),
      m_data(papp)
   {
      m_bTmx = false;
      m_spalayer.add(canew(layer(papp)));
   }



   void data::xml_import(::xml::input_tree & xmlif)
   {

      if (m_bTmx)
      {
         m_ptmxmap = new tmx::map;
         xmlif.import_node("map", *m_ptmxmap);
      }

   }

   void data::xml_export(::xml::output_tree & xmlof)
   {

      //xmlof.export_node("drawing",m_drawing);

   }



} // namespace veritile







