#pragma once


namespace biteditor
{

   
   class document;


   class CLASS_DECL_CA2_BITEDITOR front_view : public html_view
   {
   public:

   
      uint32_t m_dwLastKeyWparam;
      uint32_t m_dwLastKeyLparam;


      front_view(::aura::application * papp);
      virtual ~front_view();

   #ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
   #endif

      virtual void _001OnDraw(::draw2d::graphics * pdc);



      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnMouseMove);
      DECL_GEN_SIGNAL(_001OnKeyDown);
      DECL_GEN_SIGNAL(_001OnKeyUp);
      DECL_GEN_SIGNAL(_001OnTimer);


      DECL_GEN_SIGNAL(_001OnChar);
      DECL_GEN_SIGNAL(_001OnSysChar);

      DECL_GEN_SIGNAL(_001OnPost);

      using html_view::hit_test;
      ::user::elemental * hit_test(int32_t x, int32_t y);
      void on_update(::aura::impact * pSender, LPARAM lHint, ::object* phint);

      void key_to_char(WPARAM wparam, LPARAM lparam);

      ::aura::document * get_document() const;

      //virtual void pre_translate_message(::signal_details * pobj);
      virtual void install_message_handling(::message::dispatch * pinterface);
      virtual bool pre_create_window(::user::create_struct& cs);
      virtual void _001OnInitialUpdate();

     void OnDocumentComplete(const char * lpszURL);

      DECL_GEN_SIGNAL(_001OnDestroy);
      DECL_GEN_SIGNAL(_001OnSize);
      DECL_GEN_SIGNAL(_001OnPaint);
      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnContextMenu);
      DECL_GEN_SIGNAL(_001OnSetCursor);
      DECL_GEN_SIGNAL(_001OnUpdateViewEncoding);
      DECL_GEN_SIGNAL(_001OnViewEncoding);
      DECL_GEN_SIGNAL(_001OnWavePlayerEvent);

   
   };


} // namespace biteditor
