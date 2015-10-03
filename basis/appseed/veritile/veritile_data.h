#pragma once


namespace veritile
{


   class CLASS_DECL_APP_CORE_VERITILE data:
      virtual public ::data::data,
      virtual public ::xml::exportable,
      virtual public ::xml::importable
   {
   public:



      drawing                                         m_drawing;
      point_array                                     m_pointa;




      data(::aura::application * papp);


      virtual void xml_import(::xml::input_tree & xmlif);
      virtual void xml_export(::xml::output_tree & xmlof);


   };


} // namespace veritile





