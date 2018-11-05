#pragma once


namespace veritile
{


   class CLASS_DECL_APP_CORE_VERITILE general_data:
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


      general_data(::aura::application * papp);
      virtual  ~general_data();


   };


} // namespace veritile










