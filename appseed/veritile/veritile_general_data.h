#pragma once


namespace veritile
{


   class CLASS_DECL_APP_CORE_VERITILE property_sheet_data:
      virtual public ::data::data
   {
   public:


      class CLASS_DECL_APP_CORE_VERITILE item
      {
      public:


         ::user::validate     m_validate;


      };

      strid_map < item >      m_map;

      property_set            m_set;


      property_sheet_data(::aura::application * papp);
      virtual  ~property_sheet_data();


   };


} // namespace veritile










