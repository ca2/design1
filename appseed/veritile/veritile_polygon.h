#pragma once


namespace veritile
{


   class CLASS_DECL_APP_CORE_VERITILE polygon:
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

      virtual int sel_get_point_count();
      virtual bool sel_get_point(LPPOINT ppt,int iIndex);
      virtual bool sel_set_point(LPPOINT lppoint,int iIndex);


   };




} // namespace veritile





