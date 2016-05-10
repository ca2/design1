#pragma once


namespace biteditor
{

   class document;


   class CLASS_DECL_CA2_BITEDITOR view : 
      virtual public ::userex::scroll_view
   {
   public:

      //size                          m_sizeTotal;
      mutex                         m_mutexData;

      file_position_t               m_iSelStart;
      file_position_t               m_iSelEnd;
      file_position_t               m_iViewOffset;
      file_position_t               m_iViewSize;
      index                         m_iColumn;


      biteditor::ascii_box *        m_pasciibox;
      biteditor::hex_box *          m_phexbox;
      ::count m_iLineSize;
      int32_t                       m_iLineHeight;


      view(::aura::application * papp);
      virtual ~view();


#ifdef DEBUG
      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;
#endif

      //   virtual void _001OnDraw(::draw2d::dib * pdib);

      int64_t CalcLineCount();

      int32_t UpdateScrollSizes();


      uint32_t m_dwLastKeyWparam;
      uint32_t m_dwLastKeyLparam;

      DECL_GEN_SIGNAL(_001OnLButtonDown);
         DECL_GEN_SIGNAL(_001OnLButtonUp);
         DECL_GEN_SIGNAL(_001OnMouseMove);
         DECL_GEN_SIGNAL(_001OnKeyDown);
         DECL_GEN_SIGNAL(_001OnKeyUp);
         virtual void _001OnTimer(::timer * ptimer);
         DECL_GEN_SIGNAL(_001OnHScroll);

         DECL_GEN_SIGNAL(_001OnRButtonUp);

         DECL_GEN_SIGNAL(_001OnChar);
         DECL_GEN_SIGNAL(_001OnSysChar);

         void on_update(::user::impact * pSender, LPARAM lHint, ::object* phint);

      void key_to_char(WPARAM wparam, LPARAM lparam);

      sp(::biteditor::document) get_document() const;

      virtual void pre_translate_message(::signal_details * pobj);
      virtual void install_message_handling(::message::dispatch * pinterface);
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


         void get_view_lines(stringa & stra);


      virtual void _001GetSelText(string & str);


      virtual int32_t get_wheel_scroll_delta();


      index SelToColumn(file_position_t iSel);
      index SelToLine(file_position_t iSel);
      file_position_t LineColumnToSel(index iLine, index iColumn);

      void OneLineUp();

      virtual size get_total_size();


   };


} // namespace biteditor



