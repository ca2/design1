#pragma once


namespace user
{


   class CLASS_DECL_DESIGN_TEXTFORMAT image_list :
      virtual public ::user::box
   {
   public:


      int                     m_iTextHeight;
      bool                    m_bNoName;
      int                     m_iPad;
      e_align                 m_ealign;
      string_to_string        m_mapName;

      spa(::draw2d::dib)      m_diba;
      spa(::draw2d::dib)      m_dibaThumb;

      index                   m_iHover;
      index_array             m_iaSel;
      index                   m_iHitLast;
      index                   m_iHitLButtonDown;
      size                    m_size;
      bool                    m_bMultiSel;
      size                    m_sizeImage;


      image_list();
      virtual ~image_list();


      virtual index hit_test(point point, ::user::e_element & eelement) override;

      virtual bool get_item_rect(LPRECT lprect, index i);
      virtual bool get_element_rect(LPRECT lprect, index i, e_element eelement);


      virtual void assert_valid() const override;
      virtual void dump(dump_context & dumpcontext) const override;

      virtual bool _001GetItemText(string & str, index iItem);

      virtual bool update_data(bool bSaveAndValidate) override;

      virtual int64_t add_ref() override
      {
         return ::object::add_ref();
      }
      virtual int64_t dec_ref() override
      {
         return ::object::dec_ref();
      }

      virtual void install_message_routing(::message::sender * psender) override;

      virtual void _001OnDraw(::draw2d::graphics * pgraphics) override;

      virtual ::draw2d::dib * get_current_dib();

      virtual string get_current_dib_link();

      virtual void on_layout() override;

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnDestroy);
      DECL_GEN_SIGNAL(_001OnLButtonDown);
      DECL_GEN_SIGNAL(_001OnLButtonUp);
      DECL_GEN_SIGNAL(_001OnMouseMove);
      DECL_GEN_SIGNAL(_001OnMouseLeave);


      index _001GetCurSel();

      index_array _001GetSelection();

      void _001SetCurSel(index iFind, ::action::context actioncontext);

      void _001SetSelection(const index_array & ia, ::action::context actioncontext);


   };


   class CLASS_DECL_DESIGN_TEXTFORMAT image_list_view :
      virtual public show < margin < image_list > >
   {
   public:



      image_list_view(::aura::application * papp);
      virtual ~image_list_view();


      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;


      virtual int64_t add_ref()
      {
         return ::object::add_ref();
      }
      virtual int64_t dec_ref()
      {
         return ::object::dec_ref();
      }

      virtual void install_message_routing(::message::sender * psender);

      virtual void on_update(::user::impact * pSender, LPARAM lHint, object* pHint);



      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnDestroy);


   };


} // namespace user


