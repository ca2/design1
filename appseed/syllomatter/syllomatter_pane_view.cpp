#include "framework.h"


namespace syllomatter
{


   pane_view::pane_view(::aura::application * papp) :
      ::object(papp),
      ::user::tab(papp),
      
      ::user::tab_view(papp),
      ::userex::pane_tab_view(papp),
      place_holder_container(papp)
   {


      m_pviewdataOld = NULL;
      m_psvnview = NULL;


      

      m_pviewdata              = NULL;
      m_pviewdataOld              = NULL;


   }


   pane_view::~pane_view()
   {
   }



#ifdef DEBUG
   void pane_view::assert_valid() const
   {
      ::user::impact::assert_valid();
   }

   void pane_view::dump(dump_context & dumpcontext) const
   {
      ::user::impact::dump(dumpcontext);
   }
#endif //DEBUG

   /////////////////////////////////////////////////////////////////////////////
   // pane_view message handlers

   void pane_view::_001OnCreate(::signal_details * pobj) 
   {

      if(pobj->previous())
         return;

      add_tab("menu", syllomatter::PaneViewContextMenu);
      add_tab("Form", syllomatter::PaneViewForm);
      add_tab("SVN", syllomatter::PaneViewSVN);
      add_tab("File Manager", "file_manager");

      set_cur_tab_by_id(syllomatter::PaneViewForm);

   }


   void pane_view::on_update(::user::impact * pSender, LPARAM lHint, ::object* pHint) 
   {

      UNREFERENCED_PARAMETER(pSender);
      UNREFERENCED_PARAMETER(lHint);

      if(pHint != NULL)
      {
         if(base_class <syllomatter::pane_view_update_hint >::bases(pHint))
         {
            syllomatter::pane_view_update_hint * puh = (syllomatter::pane_view_update_hint *) pHint;
            if(puh->is_type_of(syllomatter::pane_view_update_hint::TypeGetView))
            {
               puh->m_iId = atoi(get_cur_tab_id());
            }
            else if(puh->is_type_of(syllomatter::pane_view_update_hint::TypeSetView))
            {
               set_cur_tab_by_id(puh->m_iId);
            }
         }
      }
      if(pHint != NULL)
      {
         if(base_class <syllomatter::pane_view_update_hint > :: bases(pHint))
         {
            syllomatter::pane_view_update_hint * puh = (syllomatter::pane_view_update_hint * ) pHint;
            if(puh->is_type_of(syllomatter::pane_view_update_hint::TypeOnShowKaraoke))
            {
               GetTopLevelFrame()->SetActiveView(this);
            }
            else if(puh->is_type_of(syllomatter::pane_view_update_hint::TypeOnShowView))
            {

               int32_t iTab;

               {

                  switch(puh->m_iId)
                  {
                  case syllomatter::PaneViewContextMenu:
                     iTab = 0;
                     break;
                  case syllomatter::PaneViewForm:
                     iTab = 1;
                     break;
                  case syllomatter::PaneViewSVN:
                     iTab = 2;
                     {
                        GetParentFrame()->LoadToolBar(1, "syllomatter_list_toolbar.xml");
                     }
                     break;
                  case syllomatter::PaneViewFileManager:
                     iTab = 3;
                     break;
                  }
                  _001SetSel(iTab);
               }

            }
         }
      }

   }

   void pane_view::on_show_view()
   {
      ::userex::pane_tab_view::on_show_view();
      if(m_pviewdata->m_id ==  syllomatter::PaneViewSVN)
      {
         GetParentFrame()->LoadToolBar(0, "syllomatter_list_toolbar.xml");
      }
      else
      {
         //GetParentFrame()->LoadToolBar("syllomatter_list_toolbar.xml");
      }
   }


   bool pane_view::pre_create_window(::user::create_struct& cs) 
   {
      cs.dwExStyle &= ~WS_EX_CLIENTEDGE;   

      return ::user::impact::pre_create_window(cs);
   }


   void pane_view::on_create_view(::user::view_creator_data * pcreatordata)
   {
      
      sp(::syllomatter::application) papp =  (get_app());

      switch(pcreatordata->m_id)
      {
      case syllomatter::PaneViewContextMenu:
      {
         sp(::user::menu_list_view) pview = (::user::impact::create_view< ::user::menu_list_view >(pcreatordata));
         pview->LoadXmlMenu("main_menu.xml");
         pview->MenuFill(pview,GetParentFrame());
         /*{
         sp(front_document) pdoc = (devedgeFrontDoc *) (dynamic_cast < syllomattersp(::core::application) > (((sp(::user::frame_window)) GetParentFrame())->m_pauraapp->m_pcoreapp))->m_ptemplateFront->open_document_file("http://localhost:10011/");
         if(pdoc != NULL)
         {
         POSITION pos = pdoc->get_view_count();
         sp(::user::impact) pview = pdoc->get_view(pos);
         if(pview != NULL)
         {
         sp(::user::frame_window) pframe = (sp(::user::frame_window)) pview->GetParentFrame();
         if(pframe != NULL)
         {
         pcreatordata->m_pdoc = pdoc;
         pcreatordata->m_pwnd = pframe;
         }
         }
         }
         }*/
      }
         break;

         /*         create_context cc;
         cc.m_pCurrentDoc = get_document();
         cc.m_typeinfoNewView =  RUNTIME_CLASS(::user::menu_list_view);

         sp(::user::impact) pview = (CreateView(&cc, 101, this));
         if(pview != NULL)
         {
         sp(::user::menu_list_view) pmenuview = (sp(::user::menu_list_view)) pview;
         pmenuview->m_wnd.LoadMenu(IDR_POPUP_LYRICVIEW);
         pmenuview->m_wnd.m_bAutoClose = false;
         pcreatordata = new ViewData();
         pcreatordata->m_eview = eview;
         pcreatordata->m_pdoc = get_document();
         pcreatordata->m_pwnd = pview;
         }*/
      case syllomatter::PaneViewForm:
         {
            m_pdoctemplateExtractChanges = new ::user::single_document_template(
               get_app(),
               "syllomatter/frame",
               System.type_info < syllomatter::document > (),
               System.type_info < syllomatter::frame > (),
               System.type_info < syllomatter::view > ());

            /*
            sp(::user::document) pdoc =  (
            m_pdoctemplateExtractChanges->open_document_file(
            Application.dir().matter("syllomatter_extract_changes_form.xhtml")));*/
            m_pdocForm = (
               m_pdoctemplateExtractChanges->open_document_file(NULL, true, pcreatordata->m_pholder));
            //m_pdocForm->open_commit_message();
            sp(::syllomatter::view) pview = m_pdocForm->get_typed_view < ::syllomatter::view > ();
            m_pviewForm = pview;
            if(pview != NULL)
            {
               pcreatordata->m_pdoc = get_document();
            }
         }
         break;
      case syllomatter::PaneViewSVN:
         {
            //         sp(::user::document) pdoc =  (m_pdoctemplateExtractChanges->get_document());
            /*         create_context cc;
            cc.m_pCurrentDoc = pdoc;
            cc.m_typeinfoNewView = System.type_info < svn_view > ();*/
                                      sp(::syllomatter::svn_view) pview = (::user::impact::create_view< svn_view >(pcreatordata));
            m_psvnview = pview;
            m_psvnview->m_ppaneview = this;
            m_psvnview->CreateViews();
            m_psvnview->m_plistview->m_ppaneview = this;
            if(pview != NULL)
            {
               pcreatordata->m_pdoc = get_document();
            }
         }
         break;
      default:
         break;
      }
      //pcreatordata->m_eflag.signalize(user::view_creator_data::flag_hide_all_others_on_show);
      ::userex::pane_tab_view::on_create_view(pcreatordata);
   }




   void pane_view::_001OnMenuMessage(::signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      set_cur_tab_by_id(m_pviewdataOld->m_id);
   }

   void pane_view::install_message_handling(::message::dispatch * pinterface)
   {
      ::userex::pane_tab_view::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &pane_view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_USER + 1122  , pinterface, this, &pane_view::_001OnMenuMessage);
      IGUI_WIN_MSG_LINK(WM_USER + 1123  , pinterface, this, &pane_view::_001OnStartVerisvnwellExtract);

   }

   void pane_view::_001OnStartVerisvnwellExtract(::signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      set_cur_tab_by_id(syllomatter::PaneViewSVN);
   }



} // namespace syllomatter


