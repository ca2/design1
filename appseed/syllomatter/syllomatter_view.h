#pragma once


namespace syllomatter
{


   class document;
   class list_view;


   class CLASS_DECL_CA2_SYLLOMATTER view :
      public html_view
   {
   public:


      view(::aura::application * papp);


      class extract : 
         virtual public ::object
      {
      public:

         sp(view)             m_pview;
         ::file::path         m_strCopy;
         ::file::path         m_strCheck;
         ::file::path         m_strLogFilePath;

         extract(::aura::application * papp);

      };

      int32_t      m_iBufSize;
      char *   m_buf1;
      char *   m_buf2;
      int32_t m_iMessageId;

      virtual ~view();
#ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
#endif

      virtual void _001OnDraw(::draw2d::graphics * pdc);

      void on_document_complete(const char * pszUrl);

      sp(list_view) get_list();

      virtual void install_message_handling(::message::dispatch * pinterface);
      virtual bool pre_create_window(::user::create_struct& cs);
      virtual void OnDraw(::draw2d::graphics * pgraphics);      // overridden to draw this ::view
      virtual void _001OnInitialUpdate();
         virtual void on_update(::aura::impact * pSender, LPARAM lHint, ::object* pHint);

      bool BaseOnControlEvent(::user::control_event * pevent);

      void start_syllomatter_extract(const char * pszCopy, const char * pszCheck);
      static uint32_t c_cdecl ThreadProc_syllomatter_extract(LPVOID lpParam);
      void syllomatter_extract(extract * pextract);
      int32_t syllomatter_defer_extract(extract * pextract, const ::file::path & pszTopic);
      int32_t bin_cmp(const ::file::path & pszFilePath1, const ::file::path & pszFilePath2);

      ::aura::document * get_document();

      DECL_GEN_SIGNAL(_001OnDestroy);
         DECL_GEN_SIGNAL(_001OnSize);
         DECL_GEN_SIGNAL(_001OnPaint);
         DECL_GEN_SIGNAL(_001OnCreate);
         DECL_GEN_SIGNAL(_001OnContextMenu);
         DECL_GEN_SIGNAL(_001OnSetCursor);
         DECL_GEN_SIGNAL(_001OnEraseBkgnd);
         DECL_GEN_SIGNAL(_001OnUpdateViewEncoding);
         DECL_GEN_SIGNAL(_001OnViewEncoding);
         DECL_GEN_SIGNAL(_001OnWavePlayerEvent);

         virtual void _001OnTabClick(int32_t iTab);

   };



} // namespace syllomatter


