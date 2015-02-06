#include "framework.h"


namespace biteditor
{


   child_frame::child_frame(::aura::application * papp) :
      element(papp),
      simple_child_frame(papp)
   {

      IGUI_WIN_MSG_LINK(::core::application::APPM_LANGUAGE, this, this, &child_frame::_001OnAppLanguage);

   }


   child_frame::~child_frame()
   {

   }


   bool child_frame::on_create_bars()
   {

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

      if(!LoadToolBar(0,"biteditor_toolbar.xml"))
      {
         TRACE0("Failed to create toolbar\n");
         return false;      // fail to create
      }

      layout();

      return true;

      /*   if(m_dialogbar.GetSafeoswindow_() == NULL)
      {
      uint32_t uiDialogBar = pdoc->get_filemanager_template()->m_uiDialogBar;

      if (!m_dialogbar.create(this, uiDialogBar, 
      CBRS_ALIGN_TOP, AFX_IDW_DIALOGBAR))
      {
      TRACE0("Failed to create dialogbar\n");
      return false;      // fail to create
      }
      }
      pdoc->get_filemanager_template()->m_pdialogbar = &m_dialogbar;*/


      //   HINSTANCE hinstance = ::ca2::GetResourceHandle();
      // ::ca2::SetResourceHandle(GetModuleHandle("vmsfilemanager.dll"));
      //::ca2::SetResourceHandle(hinstance);

      /*   if (!m_rebar.create(this) ||
      //       !m_rebar.AddBar(&m_menubar) ||
      !m_rebar.AddBar(&m_toolbar) ||
      !m_rebar.AddBar(&m_dialogbar))
      {
      TRACE0("Failed to create rebar\n");
      return -1;      // fail to create
      }*/

      layout();

      return true;
   }


   void child_frame::_001OnCreate(::signal_details * pobj) 
   {
      pobj->previous();

      //   SetMenu(NULL);

      m_hMenuDefault = NULL;

   }


   void child_frame::_001OnAppLanguage(::signal_details * pobj)
   {
      pobj->m_bRet = false;
   }



} // namespace biteditor






