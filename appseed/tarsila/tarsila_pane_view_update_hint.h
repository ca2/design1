#pragma once


namespace tarsila
{


   enum e_pane_view
   {
      pane_view_none,
      pane_view_context_menu,
   };



   class CLASS_DECL_APP_CORE_TARSILA pane_view_update_hint :
      public ::object
   {
   public:
      enum e_type
      {
         type_get_view,
         TypeSetView,
         TypeOnShowKaraoke,
         TypeOnShowView,
      };
   public:
      void set_type(e_type e_type);
      bool is_type_of(e_type e_type);

      pane_view_update_hint();
      virtual ~pane_view_update_hint();

      int32_t   m_iId;
   protected:
      e_type m_etype;

   };

} // namespace tarsila
