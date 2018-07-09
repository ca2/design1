#pragma once


namespace userex
{


   class CLASS_DECL_DESIGN_TEXTFORMAT group_image_list_view :
      virtual public ::user::impact
   {
   public:


      class group :
         virtual public ::object
      {
      public:

         string                  m_strGroup;
         string                  m_strIcon;
         string                  m_strTitle;
         sp(image_list_view)     m_plist;

      };


      sized                         m_size;
      ::visual::dib_sp              m_dib;
      stringa                       m_straClass;
      ::user::button                m_buttonMenu;
      spa(group)                    m_groupa;
      sp(::user::menu)              m_pmenu;
      string                        m_strGroup;


      group_image_list_view(::aura::application * papp);
      virtual ~group_image_list_view();


      virtual void assert_valid() const override;

      virtual void dump(dump_context & dumpcontext) const override;


      virtual ::userex::image_list_view * get_group_list(string strGroup);

      virtual ::file::path get_link_path(string strLink);

      virtual void install_message_routing(::message::sender * psender) override;

      virtual void on_update(::user::impact * pSender, LPARAM lHint, object* pHint) override;

      virtual void on_control_event(::user::control_event * pevent) override;

      virtual string get_group_title(group * pgroup);

      virtual void _001OnNcDraw(::draw2d::graphics * pgraphics) override;
      virtual void _001OnDraw(::draw2d::graphics * pgraphics) override;

      virtual void on_command(::user::command * pcommand) override;

      virtual bool add_group(string strGroup, string strIcon, string strTitle, ::file::path pathFolder);

      virtual bool show_group(string strGroup, ::file::path pathFolder = "");

      virtual void show_menu();

      virtual string get_menu_xml();

      ::userex::image_list_view * get_current_list();

      virtual group * get_group(string strGroup);

      DECL_GEN_SIGNAL(_001OnCreate);

      virtual void on_layout() override;


   };


} // namespace tranquillum





