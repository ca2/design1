#pragma once


namespace biteditor
{


   class view;


   class CLASS_DECL_CA2_BITEDITOR ascii_box : 
      public ::user::interaction
   {
   public:

      ::draw2d::font_sp                 m_spfont;

      point                         m_pt;
      size                          m_size;

      sp(view)              m_pview;
      bool                          m_bMouseDown;

      char *                        m_pchLineBuffer;

      
      point                         m_ptSelStart;
      bool                          m_bFocus;
      bool                          m_bCaretOn;
      uint32_t                         m_dwLastCaret;
      uint32_t                         m_dwCaretTime;
      int64_t                       m_iLineOffset;
      int32_t                           m_y;
      bool                          m_bGetTextNeedUpdate;


      ascii_box(::aura::application * papp);


      virtual void install_message_handling(::message::dispatch * pdispatch);

      void read_line(string & str, int64_t iLine);

      void _001OnKeyboardFocusTimer(sp(view) pview, uint_ptr iTimer);

      void on_update();

      file_position char_hit_test(sp(view) pview, ::draw2d::graphics * pdc, int32_t x, int32_t y);

      virtual void _001OnDraw(::draw2d::graphics * pdc);

      void _001GetViewSel(file_position &iSelStart, file_position &iSelEnd);

      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnMouseMove);
      DECL_GEN_SIGNAL(_001OnChar);
      DECL_GEN_SIGNAL(_001OnSysChar);
      void _001OnCalcLayout(sp(view) pview, ::draw2d::graphics * pdc);
      void _001OnCalcLayoutProc(sp(view) pview, ::draw2d::graphics * pdc);

      void SetFile(sp(::file::stream_buffer) pfile);
      void OnFileUpdate();

      void IndexRegisterDelete(file_position iSel, file_size iCount);
      void IndexRegisterInsert(file_position iSel, const char * lpcszWhat);


   };


} // namespace biteditor


