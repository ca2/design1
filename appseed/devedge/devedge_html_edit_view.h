#pragma once


namespace devedge
{


   class CLASS_DECL_DEVEDGE html_edit_view : 
      virtual public html_view
   {
   public:


      enum e_message
      {
         MessageUserCheckChange,
      };


      uint32_t          m_dwLastKeyWparam;
      uint32_t          m_dwLastKeyLparam;

      string         m_str;

      stringa        m_straScript;
      


      html_edit_view(::aura::application * papp);
      virtual ~html_edit_view();

      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;


      virtual sp(::user::box) BackViewGetWnd();
      virtual sp(::user::interaction) get_guie();

      virtual void _001OnDraw(::draw2d::graphics * pgraphics);

      void transform();
      void transform_back();



      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnMouseMove);
      DECL_GEN_SIGNAL(_001OnKeyDown);
      DECL_GEN_SIGNAL(_001OnKeyUp);
      void _001OnTimer(::timer * ptimer);;
      DECL_GEN_SIGNAL(_001OnUser);


      DECL_GEN_SIGNAL(_001OnChar);
      DECL_GEN_SIGNAL(_001OnSysChar);

      DECL_GEN_SIGNAL(_001OnPost);

         using html_view::hit_test;
      
      ::user::elemental * hit_test(int32_t x, int32_t y);
      void on_update(::user::impact * pSender, LPARAM lHint, ::object* phint);

      virtual void key_to_char(WPARAM wparam, LPARAM lparam);

      sp(::user::document) get_document() const;



      virtual void pre_translate_message(::message::message * pobj);
      virtual void install_message_routing(::message::sender * pinterface);
      virtual bool pre_create_window(::user::create_struct& cs);

      virtual void _001OnInitialUpdate();


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


} // namespace devedge


