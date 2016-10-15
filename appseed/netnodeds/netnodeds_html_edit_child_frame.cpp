#include "framework.h"


namespace netnodeds
{


   html_edit_child_frame::html_edit_child_frame(::aura::application * papp) :
      ::object(papp),
      simple_child_frame(papp)
   {

      IGUI_WIN_MSG_LINK(::axis::application::APPM_LANGUAGE, this, this, &html_edit_child_frame::_001OnAppLanguage);

   }


   html_edit_child_frame::~html_edit_child_frame()
   {

   }


   bool html_edit_child_frame::on_create_bars()
   {

      //DestroyBars();
      /*if (!m_menubar.CreateEx(this))
      {
      TRACE0("Failed to create toolbar\n");
      return -1;      // fail to create
      }

      if(!m_menubar.Initialize(
      BaseMenuCentral::GetMenuCentral()->MenuV033GetImageList(),
      BaseMenuCentral::GetMenuCentral()->MenuV033GetImageListDisabled(),
      prel,
      System.visual().font_central().GetMenuFont()) ||
      VMS_FAILED(m_menubar.LoadMenuBar(uiMenuBar)))
      {
      TRACE0("Failed to create toolbar\n");
      return -1;      // fail to create
      }*/

      ::file::text_buffer_sp spfile(get_app());

      ::file::path strModuleFolder;
      strModuleFolder = System.dir().module();

      if(!spfile->open(strModuleFolder/ "netnodeds_toolbar.xml", ::file::type_text | ::file::mode_read))
         return false;

      string str;
      spfile->read_full_string(str);

      if (!LoadToolBar("netnodeds", "netnodeds_toolbar.xml"))
      {
         TRACE0("Failed to create toolbar\n");
         return false;      // fail to create
      }

      on_layout();

      return true;

      /*   if(m_dialogbar.GetSafeoswindow_() == NULL)
      {
      uint32_t uiDialogBar = pdoc->get_filemanager_data()->m_ptemplate->m_uiDialogBar;

      if (!m_dialogbar.create(this, uiDialogBar, 
      CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
      {
      TRACE0("Failed to create dialogbar\n");
      return false;      // fail to create
      }
      }
      pdoc->get_filemanager_data()->m_ptemplate->m_pdialogbar = &m_dialogbar;*/


      //   HINSTANCE hinstance = ::ca::GetResourceHandle();
      // ::ca::SetResourceHandle(GetModuleHandle("vmsfilemanager.dll"));
      //::ca::SetResourceHandle(hinstance);

      /*   if (!m_rebar.create(this) ||
      //       !m_rebar.AddBar(&m_menubar) ||
      !m_rebar.AddBar(&m_toolbar) ||
      !m_rebar.AddBar(&m_dialogbar))
      {
      TRACE0("Failed to create rebar\n");
      return -1;      // fail to create
      }*/

      on_layout();

      return true;
   }

   bool html_edit_child_frame::pre_create_window(::user::create_struct& cs)
   {
      cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
      cs.style &= ~WS_BORDER;
      return simple_child_frame::pre_create_window(cs);
   }


   //bool html_edit_child_frame::DestroyBars()
   //{

   //   m_toolbar.DestroyWindow();
   //   m_toolbar.RemoveAllTools();

   //   //   m_dialogbar.DestroyWindow();

   //   return true;
   //}

   bool html_edit_child_frame::_001OnCmdMsg(::aura::cmd_msg * pcmdmsg)  
   {

      //   FileManagerFileListCallback * pcallback = GetFileManager()->get_filemanager_data()->m_ptemplate->m_pfilelistcallback;
      /*if(pcallback != NULL && 
      pcallback->GetMenuItemCallback(nID))
      {
      ::fs::item_array itema;
      if(nCode == CN_UPDATE_COMMAND_UI)
      {
      GetSelected(itema);
      pcallback->GetMenuItemUpdate(nID, itema, (cmd_ui *) pExtra);
      return TRUE;
      }
      else
      {
      int32_t nMsg;
      if (nCode != CN_UPDATE_COMMAND_UI)
      {
      nMsg = HIWORD(nCode);
      }

      // for backward compatibility HIWORD(nCode)==0 is WM_COMMAND
      if (nMsg == 0)
      nMsg = WM_COMMAND;

      if(nMsg == WM_COMMAND)
      {
      GetSelected(itema);
      pcallback->OnMenuItemAction(nID, itema);
      return TRUE;
      }
      }
      }*/
      return simple_child_frame::_001OnCmdMsg(pcmdmsg);
   }

   void html_edit_child_frame::OnChangeEditSearch()
   {

      /*   sp(::user::document) pdoc = GetActiveDocument();

      if(pdoc != NULL)
      {
      FileManagerViewUpdateHint uh;
      uh.set_type(FileManagerViewUpdateHint::TypeFilter);
      string str;
      ::ca::window * pwnd = m_dialogbar.get_child_by_id(IDC_EDIT_SEARCH);
      pwnd->GetWindowText(str);
      uh.m_wstrFilter = str;
      pdoc->update_all_views(
      NULL,
      0,
      &uh);

      }
      */
   }

   void html_edit_child_frame::_001OnCreate(::signal_details * pobj) 
   {
      
      UNREFERENCED_PARAMETER(pobj);

      

   }


   void html_edit_child_frame::_001OnAppLanguage(::signal_details * pobj)
   {
      // xyzxyz || see the code below!! in App Language!!
      on_create_bars();
      pobj->m_bRet = false;
   }


   sp(::filemanager::manager) html_edit_child_frame::GetFileManager()
   {
      return (GetActiveDocument());
   }

   /*void html_edit_child_frame::GetSelected(::fs::item_array &itema)
   {
   sp(::filemanager::SimpleFileListInterface) plistinterface = 
   (GetActiveView());
   if(plistinterface != NULL)
   {
   plistinterface->GetSelected(itema);
   }
   }*/


} // namespace netnodeds



