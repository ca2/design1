#pragma once


namespace biteditor
{


   class CLASS_DECL_CA2_BITEDITOR hex_box : 
      public ::user::interaction
   {
   public:


      char *                  m_pchLineBuffer;

      ::draw2d::font_sp           m_spfont;

      size                    m_size;

      sp(view)        m_pview;
      bool                    m_bMouseDown;
      point                   m_ptSelStart;
      bool                    m_bFocus;
      bool                    m_bCaretOn;
      uint32_t                   m_dwLastCaret;
      uint32_t                   m_dwCaretTime;
      int32_t                     m_iLineOffset;
      int32_t                     m_y;
      bool                    m_bGetTextNeedUpdate;


      hex_box(::aura::application * papp);
      virtual ~hex_box();



      virtual void install_message_handling(::message::dispatch * pdispatch);


      void read_line(string & str, file_position_t iLine);

      void _001OnKeyboardFocusTimer(sp(view) pview, int32_t iTimer);

      void on_update();

      file_position_t char_hit_test(sp(view) pview, ::draw2d::graphics * pdc, int32_t x, int32_t y, bool bSelBeg);

      virtual void _001OnDraw(::draw2d::dib * pdib);
      virtual void _001GetSelText(string & str); 

      void _001GetViewSel(file_position_t &iSelStart, file_position_t &iSelEnd);

      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnMouseMove);
      DECL_GEN_SIGNAL(_001OnChar);
      DECL_GEN_SIGNAL(_001OnSysChar);

      void _001OnCalcLayout(sp(view) pview, ::draw2d::graphics * pdc);
      
      void _001OnCalcLayoutProc(sp(view) pview, ::draw2d::graphics * pdc);

      void SetFile(sp(::file::stream_buffer) pfile);
      void OnFileUpdate();


      void IndexRegisterDelete(file_position_t iSel, file_size_t iCount);
      void IndexRegisterInsert(file_position_t iSel, const char * lpcszWhat);


   };


} // namespace biteditor


