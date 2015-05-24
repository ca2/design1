#include "framework.h"


namespace syllomatter
{


   view::extract::extract(::aura::application * papp) :
      ::object(papp)
   {

   }


   view::view(::aura::application * papp) :
      ::object(papp),
      html_form(papp),
      html_view(papp)
   {

      m_iMessageId = -1;
      m_dataid = "view";
      m_iBufSize = 1024 * 1024;
      m_buf1 = new char[m_iBufSize];
      m_buf2 = new char[m_iBufSize];

   }


   view::~view()
   {

   }


   void view::install_message_handling(::message::dispatch * pinterface)
   {

      ::user::form::install_message_handling(pinterface);

      IGUI_WIN_MSG_LINK(WM_DESTROY, pinterface, this, &view::_001OnDestroy);
      IGUI_WIN_MSG_LINK(WM_SIZE, pinterface, this, &view::_001OnSize);
      IGUI_WIN_MSG_LINK(WM_PAINT, pinterface, this, &view::_001OnPaint);
      IGUI_WIN_MSG_LINK(WM_CREATE, pinterface, this, &view::_001OnCreate);
      IGUI_WIN_MSG_LINK(WM_CONTEXTMENU, pinterface, this, &view::_001OnContextMenu);
      IGUI_WIN_MSG_LINK(WM_SETCURSOR, pinterface, this, &view::_001OnSetCursor);
      IGUI_WIN_MSG_LINK(WM_ERASEBKGND, pinterface, this, &view::_001OnEraseBkgnd);

      //   IGUI_WIN_MSG_LINK(WM_USER + 177     , this, this, &view::_001OnTabClick);
      IGUI_WIN_MSG_LINK(WM_APP + 119      , this, this, &view::_001OnWavePlayerEvent);
      //connect_command(ID_FILE_PRINT, ::aura::impact::OnFilePrint)
      //connect_command(ID_FILE_PRINT_DIRECT, ::aura::impact::OnFilePrint)
      //connect_command(ID_FILE_PRINT_PREVIEW, ::aura::impact::OnFilePrintPreview)
      //   IGUI_WIN_MSG_LINK(WM_LBUTTONDOWN, pinterface, this, &::user::interaction::_001OnLButtonDown);
      // IGUI_WIN_MSG_LINK(WM_LBUTTONUP, pinterface, this, &::user::interaction::_001OnLButtonUp);
      IGUI_WIN_MSG_LINK(WM_KEYDOWN, pinterface, this, &::user::interaction::_001OnKeyDown);
      IGUI_WIN_MSG_LINK(WM_KEYUP, pinterface, this, &::user::interaction::_001OnKeyUp);


   }
   /////////////////////////////////////////////////////////////////////////////
   // view drawing

   void view::OnDraw(::draw2d::graphics * pdcScreen)
   {
      UNREFERENCED_PARAMETER(pdcScreen);
   }

   /////////////////////////////////////////////////////////////////////////////
   // view diagnostics

#ifdef DEBUG
   void view::assert_valid() const
   {
      ::aura::impact::assert_valid();
   }

   void view::dump(dump_context & dumpcontext) const
   {
      ::aura::impact::dump(dumpcontext);
   }
#endif //DEBUG

   /////////////////////////////////////////////////////////////////////////////
   // view message handlers

   // vmpLightView.cpp : implementation of the view class
   //


   /////////////////////////////////////////////////////////////////////////////
   // view


   bool view::pre_create_window(::user::create_struct& cs)
   {

      cs.style &= ~WS_EX_CLIENTEDGE;

      return ::aura::impact::pre_create_window(cs);

   }


   void view::_001OnInitialUpdate()
   {
      ::aura::impact::_001OnInitialUpdate();


   }

   
   void view::on_update(::aura::impact * pSender, LPARAM lHint, ::object* phint)
   {

      ::user::form_view::on_update(pSender, lHint, phint);

   }


   void view::_001OnDestroy(::signal_details * pobj)
   {

      ::aura::impact::_001OnDestroy(pobj);

   }


   void view::_001OnSize(::signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

   }

   void view::_001OnPaint(::signal_details * pobj)
   {

      UNREFERENCED_PARAMETER(pobj);

   }


   void view:: _001OnDraw(::draw2d::graphics * pdc)
   {

      ::user::form::_001OnDraw(pdc);

   }


   void view::_001OnCreate(::signal_details * pobj)
   {

      if(pobj->previous())
         return;

   }


   void view::_001OnContextMenu(::signal_details * pobj)
   {
      SCAST_PTR(::message::context_menu, pcontextmenu, pobj)
         point point = pcontextmenu->GetPoint();

   }


   void view::_001OnTabClick(int32_t iTab)
   {
      if(iTab == 1)
      {
         System.simple_message_box(NULL, "Playlist");
      }
   }

   void view::_001OnWavePlayerEvent(::signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //   SCAST_PTR(::message::base, pbase, pobj)
   }

   void view::_001OnUpdateViewEncoding(::signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //SCAST_PTR(::message::update_cmd_ui, pupdatecmdui, pobj)
   }
   void view::_001OnViewEncoding(::signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      //SCAST_PTR(::message::command, pcommand, pobj)
   }


   /*xxxvoid view::data_on_after_change(int32_t iConfigurationId, int32_t iLine, int32_t iColumn, CVmsDataUpdateHint * puh)
   {
   if(iConfigurationId == _vmsp::CConfiguration::CfgKaraokeEncoding)
   {
   PrepareLyricLines();
   RedrawWindow();
   }
   }*/


   void view::_001OnSetCursor(::signal_details * pobj)
   {

      SCAST_PTR(::message::mouse, pmouse, pobj);

      pmouse->m_ecursor = ::visual::cursor_arrow;

      pobj->previous();

   }


   void view::_001OnEraseBkgnd(::signal_details * pobj)
   {
      SCAST_PTR(::message::erase_bkgnd, perasebkgnd, pobj)
         perasebkgnd->m_bRet = true;
      perasebkgnd->set_result(TRUE);
   }

   void view::on_document_complete(const char * pszUrl)
   {
      UNREFERENCED_PARAMETER(pszUrl);
      /*sp(::user::interaction) pui = get_child_by_name("check");
      sp(::user::elemental) ptext =pui;
      string str;
      DILoad("check", str);
      ptext->_001SetText(str);
      pui = get_child_by_name("copy");
      ptext =pui;
      DILoad("copy", str);
      ptext->_001SetText(str);*/
   }


   ::aura::document * view::get_document()
   {

      return ::aura::impact::get_document();

   }


   bool view::BaseOnControlEvent(::user::control_event * pevent)
   {
      if(pevent->m_eevent == ::user::event_button_clicked)
      {
         if(pevent->m_puie->m_id == "submit")
         {
            string strCheck;
            string strCopy;
            sp(::user::interaction) pui = get_child_by_name("check");
            sp(::user::elemental) ptext =pui;
            ptext->_001GetText(strCheck);
            pui = get_child_by_name("copy");
            ptext =pui;
            ptext->_001GetText(strCopy);
            data_set("check", strCheck);
            data_set("copy", strCopy);
            start_syllomatter_extract(strCopy, strCheck);
         }
         else if(::str::begins(pevent->m_puie->m_id, "message_"))
         {
            string str = pevent->m_puie->m_id;
            ::str::begins_eat(str, "message_");
            if(m_iMessageId >= 0)
            {
               string strId;
               strId.Format("messagetext_%d", m_iMessageId);
               html::elemental * pelemental = get_html_data()->get_element_by_id(strId);
               pelemental->m_style.m_propertyset["background-color"] = "#FFFFFF";
            }
            m_iMessageId = atoi(str);
            string strId;
            strId.Format("messagetext_%d", m_iMessageId);
            html::elemental * pelemental = get_html_data()->get_element_by_id(strId);
            pelemental->m_style.m_propertyset["background-color"] = "#CCFFC2";
            _001RedrawWindow();
         }
      }
      return false;
   }

   void view::start_syllomatter_extract(const char * pszCopy, const char * pszCheck)
   {
      extract * pextract = new extract(get_app());
      pextract->m_strCopy = pszCopy;
      pextract->m_strCheck = pszCheck;
      pextract->m_pview = this;
      GetParentFrame()->GetParent()->send_message(WM_USER + 1123);
      __begin_thread(get_app(), ThreadProc_syllomatter_extract, pextract);
   }

   uint32_t c_cdecl view::ThreadProc_syllomatter_extract(LPVOID lpParam)
   {
      extract * pextract = (extract *) lpParam;
      pextract->m_pview->syllomatter_extract(pextract);
      delete pextract;
      return 0;
   }

   sp(list_view) view::get_list()
   {
      return get_document()->get_typed_view < list_view > ();
   }

   void view::syllomatter_extract(extract * pextract)
   {
      ::file::listing straPath(get_app());
      //   cube1sp(::core::application) papp = &App(pextract->get_app());
      stringa straRepos;
      straRepos.add("appmatter");
      straRepos.add("appseed");
      straRepos.add("appseedcore");
      //straRepos.add("ca2os");
      //straRepos.add("matter");
      //straRepos.add("netmatter");
      //straRepos.add("netseed");
      //straRepos.add("netseedcore");
      straRepos.add("node");
      straRepos.add("seed");

      for(int32_t i = 0; i < straRepos.get_size(); i++)
      {
         
         straPath.rls(pextract->m_strCheck / straRepos[i]);

      }

      ::datetime::time time;
      time = ::datetime::time::get_current_time();
      string strFileTitle;
      int32_t iSerial = 0;
      while(iSerial <= 99)
      {
         if(iSerial == 0)
         {
            strFileTitle.Format("syllomatter%04d-%02d-%02d_%02d-%02d-%02d.txt",
               time.GetYear(),
               time.GetMonth(),
               time.GetDay(),
               time.GetHour(),
               time.GetMinute(),
               time.GetSecond());
         }
         else
         {
            strFileTitle.Format("syllomatter%04d-%02d-%02d_%02d-%02d-%02d %02d.txt",
               time.GetYear(),
               time.GetMonth(),
               time.GetDay(),
               time.GetHour(),
               time.GetMinute(),
               time.GetSecond(),
               iSerial);
         }

         strFileTitle = pextract->m_strCopy / strFileTitle;

         if(!Application.file().exists(strFileTitle))
         {

            break;

         }

         iSerial++;

      }

      pextract->m_strLogFilePath = strFileTitle;
      
      ::file::text_buffer_sp spfile(allocer());
      
      Application.dir().mk(pextract->m_strLogFilePath.folder());

      spfile->open(pextract->m_strLogFilePath, ::file::type_text | ::file::mode_create | ::file::mode_write);

      spfile->close();

      strsize iLen = pextract->m_strCheck.get_length();
      sp(list_view) plist = get_list();
      ::count iCount = straPath.get_size();
      int32_t iProgress = 0;
      //   int32_t iAnimation = 0;
      uint32_t dwLastUpdate = ::GetTickCount();
      string strFormat;
      plist->m_straStatus.add("");
      plist->m_stra.add("...");
      int32_t iCmp;
      string strStatus;
      for(int32_t i = 0; i < iCount; i++)
      {
         string & strPath = straPath[i];
         if(strPath.Left(iLen).CompareNoCase(pextract->m_strCheck) == 0)
         {
            iCmp = syllomatter_defer_extract(pextract, strPath.Mid(iLen + 1));
            if(iCmp != 0)
            {
               switch(iCmp)
               {
               case 1:
               case -1:
                  strStatus = "Modified";
                  break;
               case 5:
                  strStatus = "Added";
                  break;
               case -5:
                  strStatus = "Deleted";
                  break;
               default:
                  strStatus = "";
               }
               plist->m_stra.insert_at(plist->m_stra.get_upper_bound(), strPath);
               plist->m_straStatus.insert_at(plist->m_straStatus.get_upper_bound(), strStatus);
               plist->_001OnUpdateItemCount();
            }
         }
         if((::GetTickCount() - dwLastUpdate) > 100)
         {
            dwLastUpdate = ::GetTickCount();
            strFormat.Format("%d/%d", i, iCount);
            plist->m_stra[plist->m_stra.get_upper_bound()] = strFormat;
            plist->_001RedrawWindow();
         }
         iProgress++;
      }

      plist->m_stra[plist->m_stra.get_upper_bound()] = "OK";

   }


   int32_t view::syllomatter_defer_extract(extract * pextract, const ::file::path & pszTopic)
   {

      ::file::path strSrc = pextract->m_strCheck / pszTopic;

      if(strSrc.find("\\.svn\\") > 0)
      {

         return 0;

      }

      if(Application.dir().is(strSrc))
      {

         return 0;

      }

      ::file::path strChk = pextract->m_strCheck / pszTopic.folder() / ".svn\\text-base" / pszTopic.name() + ".svn-base";

      ::file::path strDst = pextract->m_strCopy / pszTopic;

      int32_t iCmp = bin_cmp(strSrc, strChk);

      if(iCmp == 1 || iCmp == -1 || iCmp == 5 || iCmp == -5)
      {
         string strStatus;
         string strStatus2;
         if(iCmp == 1 || iCmp == -1)
         {
            strStatus = "Modified";
            strStatus2 = "M";
         }
         else if(iCmp == 5)
         {
            strStatus = "Added";
            strStatus2 = "A";
         }
         else if(iCmp == -5)
         {
            strStatus = "Deleted";
            strStatus2 = "D";
         }

         Application.dir().mk(strDst.folder());

         Application.file().copy(strDst, strSrc, false);

         ::file::text_buffer_sp spfile(allocer());

         spfile->open(pextract->m_strLogFilePath, ::file::type_text | ::file::mode_no_truncate | ::file::mode_write);

         string str;

         str = strStatus2 + ": " + strSrc + "\r\n";

         spfile->seek_to_end();

         spfile->write_string(str);

         return iCmp;

      }

      return 0;

   }


   int32_t view::bin_cmp(const ::file::path & pszFilePath1,const ::file::path & pszFilePath2)
   {
      
      ::file::buffer_sp spfile1(get_app());

      ::file::buffer_sp spfile2(get_app());

      if(!spfile1->open(pszFilePath1, ::file::type_binary | ::file::mode_read))
         return -5;

      if(!spfile2->open(pszFilePath2, ::file::type_binary | ::file::mode_read))
         return 5;

      ::file::file_status status1;

      ::file::file_status status2;

      if(!spfile1->GetStatus(status1))
         return -5;

      if(!spfile2->GetStatus(status2))
         return 5;

      if(status1.m_mtime == status2.m_mtime)
         return 0;

      primitive::memory_size iRead1;
      primitive::memory_size iRead2;
      while(true)
      {
         iRead1 = spfile1->read(m_buf1, m_iBufSize);
         iRead2 = spfile2->read(m_buf2, m_iBufSize);
         if(iRead1 > iRead2)
            return 1;
         else if(iRead1 < iRead2)
            return -1;
         if(iRead1 == 0)
            break;
         else if(iRead2 == 0)
            break;
         int32_t iCmp = memcmp(m_buf1, m_buf2, iRead1);
         if(iCmp > 0)
            return 1;
         else if(iCmp < 0)
            return -1;
      }
      return 0;
   }




} // namespace syllomatter
