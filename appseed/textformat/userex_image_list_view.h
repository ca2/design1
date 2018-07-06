#pragma once


namespace userex
{


   class CLASS_DECL_APP_CORE_TEXTFORMAT image_list_view :
      virtual public user::image_list_view
   {
   public:


      ::file::path         m_pathFolder;
      ::file::listing      m_listing;
      stringa              m_straPattern;
      stringa              m_straPatternNames;


      image_list_view(::aura::application * papp);
      virtual ~image_list_view();


      virtual void assert_valid() const;
      virtual void dump(dump_context & dumpcontext) const;

      virtual stringa get_ls_pattern_stra() const;

      virtual bool update_data(bool bSaveAndValidate);

      virtual bool _001GetItemText(string & str, index iItem);

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

      virtual string get_link_prefix();

      virtual ::file::path get_link_path(string strLink);

      virtual void on_layout();

      DECL_GEN_SIGNAL(_001OnCreate);
      DECL_GEN_SIGNAL(_001OnDestroy);



   };


} // namespace tranquillum


