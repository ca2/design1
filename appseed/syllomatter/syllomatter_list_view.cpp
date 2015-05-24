#include "framework.h"


namespace syllomatter
{


   list_view::list_view(::aura::application * papp) :
      ::object(papp),
      simple_list_view(papp),
      m_updatethread(papp),
      m_committhread(papp)
   {
      m_updatethread.m_plistview = this;
      m_committhread.m_plistview = this;

      m_dataid = "list_view";
      connect_command("add", &list_view::_001OnAdd);
      connect_update_cmd_ui("add", &list_view::_001OnUpdateAdd);
      connect_command("delete", &list_view::_001OnDelete);
      connect_update_cmd_ui("delete", &list_view::_001OnUpdateDelete);
      connect_command("revert", &list_view::_001OnRevert);
      connect_update_cmd_ui("revert", &list_view::_001OnUpdateRevert);
      connect_command("syllomatter_do_commit", &list_view::_001OnDoCommit);
      connect_update_cmd_ui("syllomatter_do_commit", &list_view::_001OnUpdateDoCommit);

      m_scrollinfo.m_rectMargin.deflate(26, 26, 26, 26);

   }


   list_view::~list_view()
   {
   }


   void list_view::install_message_handling(::message::dispatch * pinterface)
   {
      ::user::form_list::install_message_handling(pinterface);
      ::aura::impact::install_message_handling(pinterface);
      IGUI_WIN_MSG_LINK(WM_CREATE            , pinterface, this, &list_view::_001OnCreate);
      IGUI_WIN_MSG_LINK(MessageGeneralEvent  , pinterface, this, &list_view::_001OnGeneralEvent);
      IGUI_WIN_MSG_LINK(WM_USER + 1024       , pinterface, this, &list_view::_001OnVerisvnwellListMessage);
   }

   void list_view::_001OnCreate(::signal_details * pobj)
   {
      pobj->previous();

      post_message(MessageGeneralEvent, GeneralEventPosCreate1);

   }

   void list_view::_001InsertColumns()
   {
      ::user::list_column column;

      column.m_iWidth               = 16;
      column.m_iSubItem             = 2;
      column.m_sizeIcon.cx          = 16;
      column.m_sizeIcon.cy          = 16;
      column.m_iControl             = -1;
      column.m_bEditOnSecondClick   = false;
      column.m_pil                  = Session.userex()->shellimageset().GetImageList16();
      _001AddColumn(column);


      column.m_iWidth               = 49;
      column.m_iSubItem             = 0;
      _001AddColumn(column);

      column.m_iWidth               = 700;
      column.m_iSubItem             = 1;
      _001AddColumn(column);
   }

   void list_view::_001GetItemImage(::user::list_item * pitem)
   {
      if(pitem->m_iSubItem == 2)
      {
         if(m_rangeSelection.has_item(pitem->m_iItem))
         {
            pitem->m_iImage = 1;
            pitem->m_bOk = true;
         }
         else
         {
            pitem->m_iImage = 0;
            pitem->m_bOk = true;
         }
      }
      else
      {
         ::user::form_list::_001GetItemImage(pitem);
      }
   }



   void list_view::_001GetItemText(::user::list_item * pitem)
   {
      if(pitem->m_iSubItem == 0)
      {
         pitem->m_strText = m_straStatus[pitem->m_iItem];
         pitem->m_bOk = true;
      }
      else if(pitem->m_iSubItem == 1)
      {
         pitem->m_strText = m_stra[pitem->m_iItem];
         pitem->m_bOk = true;
      }
      else
      {
         pitem->m_bOk = false;  
      }

   }


   int_ptr list_view::_001GetItemCount()
   {
      return m_stra.get_size();
   }

   void list_view::_001OnGeneralEvent(::signal_details * pobj)
   {
      SCAST_PTR(::message::base, pbase, pobj)
         if(pbase->m_wparam == GeneralEventPosCreate1)
         {
            _001UpdateColumns();
         }
   }

   void list_view::Commit_(::fs::item_array & itema)
   {
      m_itema = itema;
      m_stra.remove_all();
      m_straStatus.remove_all();
      _001OnUpdateItemCount();
      
      stringa straSep;

      ::file::listing straSub;

      straSep.add("\r");
      straSep.add("\n");
      straSep.add("\r\n");

      for(int32_t i = 0; i < itema.get_size(); i++)
      {
         m_stra.add(itema[i]->m_strPath);
         m_committhread.m_str = itema[i]->m_strPath;
         m_straStatus.add("X");

         string strCmd = System.dir().module() / "svn\\svn status" + " " + itema[i]->m_strPath;

         string strOutput;
         strOutput = System.process().get_output(strCmd);
         stringa stra;
         stra.add_smallest_tokens(strOutput, straSep, true, FALSE);
         for(int32_t j = 0; j < stra.get_size(); j++)
         {

            string strLine = stra[j];

            string strStatus = strLine[0];
            m_straStatus.add(strStatus);


            string strPath = strLine.Mid(1);
            strPath.trim();
            m_stra.add(strPath);


            if(strStatus == "?" && Application.dir().is(strPath))
            {
               
               straSub.clear_results();

               straSub.rls(strPath);

               for(int32_t l = 0; l < straSub.get_size(); l++)
               {

                  m_stra.add(straSub[l]);

                  m_straStatus.add("?");

               }

            }
         }
      }
      array < sort::ARG_COMPARE_FUNCTION, sort::ARG_COMPARE_FUNCTION > comparefna;
      array < sort::ARG_SWAP_FUNCTION, sort::ARG_SWAP_FUNCTION > swapfna;
      void_ptra comparearga;
      void_ptra swaparga;
      comparefna.add(&list_view::CompareStatus);
      comparefna.add(&list_view::ComparePath);
      comparearga.add((void *) this);
      comparearga.add((void *) this);
      swapfna.add(&list_view::Commit_Swap);
      swaparga.add((void *) this);
      ::sort::quick_sort(m_stra.get_size(), comparefna, swapfna, comparearga, swaparga);
      _001OnUpdateItemCount();
   }


   void list_view::Commit_Swap(LPVOID lparg, index dwa, index dwb)
   {
      sp(list_view) plist = (list_view *) lparg;
      string stra = plist->m_stra[dwa];
      plist->m_stra[dwa] = plist->m_stra[dwb];
      plist->m_stra[dwb] = stra;
      stra = plist->m_straStatus[dwa];
      plist->m_straStatus[dwa] = plist->m_straStatus[dwb];
      plist->m_straStatus[dwb] = stra;
   }


   int32_t list_view::CompareStatus(LPVOID lparg, index dwa, index dwb)
   {
      sp(list_view) plist = (list_view *) lparg;
      return (int32_t) (StatusSortWeight(plist->m_straStatus[dwa]) - StatusSortWeight(plist->m_straStatus[dwb]));
   }


   index list_view::StatusSortWeight(string & strStatus)
   {
      if(strStatus == "M")
         return 1;
      else if(strStatus == "A")
         return 2;
      else if(strStatus == "D")
         return 3;
      else if(strStatus == "?")
         return 4;
      else if(strStatus == " ") // Title 1
         return -1;
      else
         return 5;
   }

   int32_t list_view::ComparePath(LPVOID lparg, index dwa, index dwb)
   {
      sp(list_view) plist = (list_view *) lparg;
      return plist->m_stra[dwa].Compare(plist->m_stra[dwb]);
   }

   void list_view::_001OnAdd(::signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      range range;
      _001GetSelection(range);
      for(index i = 0; i < range.get_item_count(); i++)
      {
         for(index iItem = range.ItemAt(i).get_lower_bound(); iItem <= range.ItemAt(i).get_upper_bound(); iItem++)
         {
            if(m_straStatus[iItem] == "?")
            {
               
               ::process::process_sp process(allocer());

               process->create_child_process(System.dir().module() / "svn\\svn add " + m_stra[iItem], false);

               process->wait_until_exit();

            }
         }
      }
      Commit_(m_itema);
   }

   void list_view::_001OnUpdateAdd(::signal_details * pobj)
   {
      range range;
      _001GetSelection(range);
      bool bEnable = false;
      for(index i = 0; i < range.get_item_count(); i++)
      {
         for(index iItem = range.ItemAt(i).get_lower_bound(); iItem <= range.ItemAt(i).get_upper_bound(); iItem++)
         {
            if(m_straStatus[iItem] == "?")
            {
               bEnable = true;
               break;
            }
         }
         if(bEnable)
            break;
      }
      SCAST_PTR(::aura::cmd_ui, pcmdui, pobj)
         pcmdui->m_pcmdui->Enable(bEnable);
   }

   void list_view::_001OnDelete(::signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      range range;
      _001GetSelection(range);
      for(index i = 0; i < range.get_item_count(); i++)
      {
         for(index iItem = range.ItemAt(i).get_lower_bound(); iItem <= range.ItemAt(i).get_upper_bound(); iItem++)
         {
            
            if(m_straStatus[iItem] == "!")
            {
               
               ::process::process_sp process(allocer());

               process->create_child_process(System.dir().module() / "svn\\svn delete " + m_stra[iItem], false);

               process->wait_until_exit();

            }

         }
      }
      Commit_(m_itema);
   }

   void list_view::_001OnUpdateDelete(::signal_details * pobj)
   {
      range range;
      _001GetSelection(range);
      bool bEnable = false;
      for(index i = 0; i < range.get_item_count(); i++)
      {
         for(index iItem = range.ItemAt(i).get_lower_bound(); iItem <= range.ItemAt(i).get_upper_bound(); iItem++)
         {
            if(m_straStatus[iItem] == "!")
            {
               bEnable = true;
               break;
            }
         }
         if(bEnable)
            break;
      }
      SCAST_PTR(::aura::cmd_ui, pcmdui, pobj)
         pcmdui->m_pcmdui->Enable(bEnable);
   }


   void list_view::_001OnRevert(::signal_details * pobj)
   {
      
      UNREFERENCED_PARAMETER(pobj);
      
      range range;
      
      _001GetSelection(range);
      
      for(index i = 0; i < range.get_item_count(); i++)
      {
         
         for(index iItem = range.ItemAt(i).get_lower_bound(); iItem <= range.ItemAt(i).get_upper_bound(); iItem++)
         {
            
            if(m_straStatus[iItem] == "M" || m_straStatus[iItem] == "A")
            {
               
               ::process::process_sp process(allocer());
               
               process->create_child_process(System.dir().module() / "svn\\svn revert " + m_stra[iItem], false);

               process->wait_until_exit();

            }

         }

      }

      Commit_(m_itema);

   }

   void list_view::_001OnUpdateRevert(::signal_details * pobj)
   {
      range range;
      _001GetSelection(range);
      bool bEnable = false;
      for(index i = 0; i < range.get_item_count(); i++)
      {
         for(index iItem = range.ItemAt(i).get_lower_bound(); iItem <= range.ItemAt(i).get_upper_bound(); iItem++)
         {
            if(m_straStatus[iItem] == "M" || m_straStatus[iItem] == "A" || m_straStatus[iItem] == "D")
            {
               bEnable = true;
               break;
            }
         }
         if(bEnable)
            break;
      }
      SCAST_PTR(::aura::cmd_ui, pcmdui, pobj)
         pcmdui->m_pcmdui->Enable(bEnable);
   }

   list_view::commit_thread::commit_thread(::aura::application * papp) :
      ::object(papp),
      thread(papp),
      simple_thread(papp)
   {
   }

   int32_t list_view::commit_thread::run()
   {
      ::file::path strCmd = System.dir().module() / "svn\\svn commit";
      ::file::path strDelCmd = System.dir().module() / "svn\\svn delete";
      ::file::path strAddCmd = System.dir().module() / "svn\\svn add";
      string strExtraCommitMessage;
      m_plistview->m_psvnview->m_peditview->_001GetText(strExtraCommitMessage);
      if(strExtraCommitMessage .get_length() > 0)
      {
         strExtraCommitMessage = "\n" + strExtraCommitMessage + "\n";
      }
      string strTime;
      strTime = Application.file().time_square();
      string strFileTime;
      strFileTime = Application.file().time_square();
      string strFileAdd;
      strFileAdd = Application.file().time_square();
      string strFileDel;
      strFileDel = Application.file().time_square();
      string strContents;
      string strQuery;
      strQuery.Format("id=%d", m_plistview->m_ppaneview->m_pviewForm->m_iMessageId);
      property_set set;
      set["user"] = &ApplicationUser;
      set["cookies"] = ApplicationUser.m_phttpcookies;
      System.http().download("https://api.ca2.cc/syllomatter/commit_message?" + strQuery, strTime, set);
      string strFile = Application.file().as_string(strTime);
      strFile.replace("\r\n", "\n");
      strFile.replace("\n\r", "\n");
      strFile.replace("\r", "\n");
      strFile += strExtraCommitMessage;
      Application.file().put_contents(strTime, strFile);
      strCmd += " --file " + strTime;
      strCmd += " --targets \"" + strFileTime + "\"";
      strAddCmd += " --targets \"" + strFileAdd + "\"";
      strDelCmd += " --targets \"" + strFileDel + "\"";
      string strCommitMessage;
      strCommitMessage = "Changed file(s):\n";
      string strFiles;
      string strAddFiles;
      string strDelFiles;
      for(int32_t i = 0; i < m_stra.get_size(); i++)
      {
         string strSvnPath = m_stra[i];
         if(m_straStatus[i] == "?")
         {
            strAddFiles += strSvnPath;
            strAddFiles += "\n";
         }
         else if(m_straStatus[i] == "!")
         {
            strDelFiles += strSvnPath;
            strDelFiles += "\n";
         }
         strSvnPath.replace("\\", "/");
         strFiles += strSvnPath;
         strFiles += "\n";
         strCommitMessage += m_stra[i];
         strCommitMessage += "\n";
      }






      // Delete process
      if(strDelFiles.has_char())
      {
         Application.file().put_contents(strFileDel, strDelFiles);
         TRACE(strDelCmd);
         {

            ::process::process_sp process(allocer());
            string strOutput;
            string strNow;
            string strRead;
            string strLine;
            int32_t iRetry = -1;
            if(process->create_child_process(strDelCmd, true, m_str))
            {
               while(true)
               {
                  strNow = process->read();
                  strRead += strNow;
                  strOutput += strNow;
                  while(true)
                  {
                     strsize iFind = strRead.find("\n");
                     if(iFind >= 0)
                     {
                        strLine = strRead.Mid(0, iFind);
                        strRead = strRead.Mid(iFind + 2);
                        m_plistview->m_stra.add(strLine);
                        m_plistview->m_straStatus.add("");
                        m_plistview->post_message(WM_USER + 1024);
                     }
                     else
                     {
                        break;
                     }
                  }
                  if(iRetry < 0)
                  {
                     if(process->has_exited())
                     {
                        iRetry  = 100;
                     }
                  }
                  else
                  {
                     iRetry--;
                     if(iRetry == 0)
                        break;
                  }
               }
            }
         }
      }



      // Add process
      if(strAddFiles.has_char())
      {
         Application.file().put_contents(strFileAdd, strAddFiles);
         TRACE(strAddCmd);
         {

            ::process::process_sp process(allocer());
            string strOutput;
            string strNow;
            string strRead;
            string strLine;
            int32_t iRetry = -1;
            if(process->create_child_process(strAddCmd, true, m_str))
            {
               while(true)
               {
                  strNow = process->read();
                  strRead += strNow;
                  strOutput += strNow;
                  while(true)
                  {
                     strsize iFind = strRead.find("\n");
                     if(iFind >= 0)
                     {
                        strLine = strRead.Mid(0, iFind);
                        strRead = strRead.Mid(iFind + 2);
                        m_plistview->m_stra.add(strLine);
                        m_plistview->m_straStatus.add("");
                        m_plistview->post_message(WM_USER + 1024);
                     }
                     else
                     {
                        break;
                     }
                  }
                  if(iRetry < 0)
                  {
                     if(process->has_exited())
                     {
                        iRetry  = 100;
                     }
                  }
                  else
                  {
                     iRetry--;
                     if(iRetry == 0)
                        break;
                  }
               }
            }
         }

      }


      Application.file().put_contents(strFileTime, strFiles);
      // Commit process
      TRACE(strCmd);
      {

         ::process::process_sp process(allocer());
         string strOutput;
         string strNow;
         string strRead;
         string strLine;
         int32_t iRetry = -1;
         if(process->create_child_process(strCmd, true, m_str))
         {
            while(true)
            {
               strNow = process->read();
               strRead += strNow;
               strOutput += strNow;
               while(true)
               {
                  strsize iFind = strRead.find("\n");
                  if(iFind >= 0)
                  {
                     strLine = strRead.Mid(0, iFind);
                     strRead = strRead.Mid(iFind + 2);
                     m_plistview->m_stra.add(strLine);
                     m_plistview->m_straStatus.add("");
                     m_plistview->post_message(WM_USER + 1024);
                  }
                  else
                  {
                     break;
                  }
               }
               if(iRetry < 0)
               {
                  if(process->has_exited())
                  {
                     iRetry  = 100;
                  }
               }
               else
               {
                  iRetry--;
                  if(iRetry == 0)
                     break;
               }
            }
         }
         strTime = Application.file().time_square();
//         headers.m_propertya.remove_all();
         strQuery.Format("commitid=%d&debug&explain", m_plistview->m_ppaneview->m_pviewForm->m_iMessageId);
         property_set set;
         set["post"]["message"] = System.url().url_encode(strExtraCommitMessage + strCommitMessage);
         if(strOutput.find("Committed revision") > 0)
         {
            set["user"] = &ApplicationUser;
            set["cookies"] = ApplicationUser.m_phttpcookies;
            System.http().download("https://api.ca2.cc/syllomatter/commit_message?" + strQuery, strTime, set);
         }
      }
      return 0;
   }


   void list_view::_001OnDoCommit(::signal_details * pobj)
   {
      UNREFERENCED_PARAMETER(pobj);
      range range;
      _001GetSelection(range);
      for(index i = 0; i < range.get_item_count(); i++)
      {
         for(index iItem = range.ItemAt(i).get_lower_bound(); iItem <= range.ItemAt(i).get_upper_bound(); iItem++)
         {
            if(m_straStatus[iItem] == "M" || m_straStatus[iItem] == "A" || m_straStatus[iItem] == "D" || m_straStatus[iItem] == "?" || m_straStatus[iItem] == "!")
            {
               m_committhread.m_stra.add(m_stra[iItem]);
               m_committhread.m_straStatus.add(m_straStatus[iItem]);
            }
         }
      }
      m_committhread.begin();
   }

   void list_view::_001OnUpdateDoCommit(::signal_details * pobj)
   {
      range range;
      _001GetSelection(range);
      bool bEnable = range.get_item_count() > 0;
      SCAST_PTR(::aura::cmd_ui, pcmdui, pobj)
         pcmdui->m_pcmdui->Enable(bEnable);
   }




   list_view::update_thread::update_thread(::aura::application * papp) :
      ::object(papp),
      thread(papp),
      simple_thread(papp)
   {
   }

   int32_t list_view::update_thread::run()
   {
      m_plistview->m_stra.remove_all();
      m_plistview->m_straStatus.remove_all();
      m_plistview->post_message(WM_USER + 1024);
      stringa straSep;
      stringa straSub;
      straSep.add("\r");
      straSep.add("\n");
      straSep.add("\r\n");
      string strRead;
      string strLine;
      for(int32_t i = 0; i < m_itema.get_size(); i++)
      {
         m_plistview->m_stra.add("Updating " +  m_itema[i]->m_strPath + "...");
         m_plistview->m_straStatus.add(" ");
         m_plistview->post_message(WM_USER + 1024);
         string strCmd = System.dir().module() / "svn\\svn update" + " " + m_itema[i]->m_strPath;
         string strOutput;
         ::process::process_sp process(allocer());
         int32_t iRetry = -1;
         if(process->create_child_process(strCmd, true))
         {
            while(true)
            {
               strRead += process->read();
               while(true)
               {
                  strsize iFind = strRead.find("\r\n");
                  if(iFind >= 0)
                  {
                     strLine = strRead.Mid(0, iFind);
                     strRead = strRead.Mid(iFind + 2);
                     if(::str::begins_ci(strLine, "Updating"))
                     {
                     }
                     else if(::str::begins_ci(strLine, "Restored")
                        || ::str::begins_ci(strLine, "At revision"))
                     {
                        m_plistview->m_stra.add(strLine);
                        m_plistview->m_straStatus.add("");
                        m_plistview->post_message(WM_USER + 1024);
                     }
                     else
                     {
                        m_plistview->m_stra.add(strLine.Mid(4));
                        m_plistview->m_straStatus.add(strLine.Mid(0, 1));
                        m_plistview->post_message(WM_USER + 1024);
                     }
                  }
                  else
                  {
                     break;
                  }
               }
               if(iRetry < 0)
               {
                  if(process->has_exited())
                  {
                     iRetry  = 100;
                  }
               }
               else
               {
                  iRetry--;
                  if(iRetry == 0)
                     break;
               }
            }
         }
      }
      m_plistview->m_stra.add(strRead);
      m_plistview->m_straStatus.add("");
      /*   array < ARG_COMPARE_FUNCTION, ARG_COMPARE_FUNCTION > comparefna;
      array < ARG_SWAP_FUNCTION, ARG_SWAP_FUNCTION > swapfna;
      array < void *, void * > comparearga;
      array < void *, void * > swaparga;
      comparefna.add(&list_view::CompareStatus);
      comparefna.add(&list_view::ComparePath);
      comparearga.add((void *) this);
      comparearga.add((void *) this);
      swapfna.add(&list_view::Commit_Swap);
      swaparga.add((void *) this);
      quick_sort(m_plistview->m_stra.get_size(), comparefna, swapfna, comparearga, swaparga);*/
      m_plistview->post_message(WM_USER + 1024);
      return 0;
   }

   void list_view::Update(::fs::item_array & itema)
   {
      m_updatethread.m_itema = itema;
      m_updatethread.begin();
   }



   void list_view::_001GetItemColor(::user::list_item * pitem)
   {
      if(m_straStatus[pitem->m_iItem] == "M")
      {
         pitem->m_cr = ARGB(255, 100, 150, 255);
         pitem->m_bOk = true;
      }
      else if(m_straStatus[pitem->m_iItem] == "A")
      {
         pitem->m_cr = ARGB(255, 235, 150, 255);
         pitem->m_bOk = true;
      }
      else if(m_straStatus[pitem->m_iItem] == "D")
      {
         pitem->m_cr = ARGB(255, 255, 100, 55);
         pitem->m_bOk = true;
      }
      else
      {
         return ::user::form_list::_001GetItemColor(pitem);
      }
   }


   void list_view::_001OnVerisvnwellListMessage(::signal_details * pobj)
   {
      SCAST_PTR(::message::base, pbase, pobj);
      if(pbase->m_wparam == 0)
      {
         if(pbase->m_lparam == 0)
         {
            _001OnUpdateItemCount();
            _001EnsureVisible(_001GetItemCount() - 1);
         }
      }
   }

   void list_view::LibsvnMinimalClientTest()
   {

      libsvn_minimal_client_test(this,"https://repos.ca2.cc/app/basis");

   }

} // namespace syllomatter



