#pragma once


namespace tarsila
{


   class CLASS_DECL_APP_CORE_TARSILA polygon:
      virtual public element
   {
      public:



         point_array                                     m_pointa;


         polygon(::aura::application * papp);

         virtual bool contains(point pt);


         virtual void xml_import(::xml::input_tree & xmlif);
         virtual void xml_export(::xml::output_tree & xmlof);


         virtual void on_draw(draw * pdraw);

         virtual void translate(size sz);

         virtual ::count sel_get_point_count();
         virtual bool sel_get_point(LPPOINT ppt, index iIndex);
         virtual bool sel_set_point(LPPOINT lppoint, index iIndex);


   };




} // namespace tarsila





