#pragma once


class CLASS_DECL_DESIGN_TEXTFORMAT progress :
   virtual public double_scalar_source,
   virtual public object
{
public:


   string                  m_strStatus;
   ::index                 m_iStep;
   ::count                 m_iStepCount;
   string                  m_strTitle;
   sp(::thread)            m_pthread;


   progress(::aura::application * papp, const char * pszTitle);
   virtual ~progress();


   virtual void on_set_scalar(e_scalar escalar, double d, int iFlags);
   virtual void get_scalar_minimum(e_scalar escalar, double & d);
   virtual void get_scalar(e_scalar escalar, double & d);
   virtual void get_scalar_maximum(e_scalar escalar, double & d);

   virtual void format_status(const char *pszFormat);

   virtual void redraw();
   virtual void step();

};


using progress_sp = sp(progress);

namespace userex
{


   class progress_view;


   class CLASS_DECL_DESIGN_TEXTFORMAT progress :
      virtual public ::progress
   {
   public:


      ::user::document *    m_pdoc;
      progress_view *       m_pview;


      progress(::aura::application * papp, const char * pszTitle, ::count iStepCount = 0);
      virtual ~progress();


      virtual i64 dec_ref() override;


      void create_progress(::user::interaction * puiParent);
      void set_progress_title(const char * pszTitle);
      void close_progress();


      virtual void redraw() override;

      virtual void defer_show(::user::interaction * puiParent);


   };


   class CLASS_DECL_DESIGN_TEXTFORMAT progress_view :
      virtual public user::impact,
      virtual public double_scalar
   {
   public:


      ::progress *         m_pprogress;

      ::user::progress     m_progress;

      rect                 m_rectStatus;


      progress_view(::aura::application * papp);
      virtual ~progress_view();


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

      virtual void on_layout();


      virtual void _001OnDraw(::draw2d::graphics * pgraphics);


   };


} // namespace tranquillum


