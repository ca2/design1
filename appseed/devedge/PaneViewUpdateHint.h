#pragma once

enum e_pane_view
{
   pane_view_none,
   pane_view_context_menu,
   PaneViewDevEdge,
   PaneViewHtmlEdit,
   PaneViewHtml,
   "file_manager",
   PaneViewPlaylist,
   PaneViewMediaLibrary,
   PaneViewAudioControl,
   PaneViewOptions,
};


class CLASS_DECL_CA2_DEVEDGE PaneViewUpdateHint :
   public base_object
{
public:
   enum EType
   {
      type_get_view,
      TypeSetView,
      TypeOnShowKaraoke,
      TypeOnBeforeShowView,
      TypeOnShowView,
   };
   // DECLARE_DYNAMIC(PaneViewUpdateHint)
public:
   void SetType(EType etype);
   bool IsTypeOf(EType etype);

   PaneViewUpdateHint();
   virtual ~PaneViewUpdateHint();

   e_pane_view m_eview;
protected:
   EType m_etype;

};
