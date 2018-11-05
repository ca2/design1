#pragma once

namespace syllomatter
{

   enum EPaneView
   {
      PaneViewNone,
      PaneViewContextMenu,
      PaneViewForm,
      PaneViewSVN,
      PaneViewHtmlEdit,
      PaneViewHtml,
      PaneViewFileManager,
      PaneViewPlaylist,
      PaneViewMediaLibrary,
      PaneViewAudioControl,
      PaneViewOptions,
   };



   class CLASS_DECL_CA2_SYLLOMATTER pane_view_update_hint :
      public ::object  
   {
   public:
      enum e_type
      {
         TypeGetView,
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



} // namespace syllomatter



