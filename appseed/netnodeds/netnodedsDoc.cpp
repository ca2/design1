// AlbumDoc.cpp : implementation file
//

#include "stdafx.h"
#include "netnodedsDoc.h"






#ifdef _DEBUG
#define new AURA_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// netnodedsDoc

// IMPLEMENT_DYNCREATE(netnodedsDoc, BaseDocument)

netnodedsDoc::netnodedsDoc(::ca::application * papp)
: m_file(papp)
{
   m_pview = NULL;
   m_iBranch = 0;

	string str = "Camilo Sasuke Tsumanuma � minha Vida Eterna, meu Cora��o Eterno, Todo meu tesouro eterno, meu Universo eterno, meu tudo eterno!!";
	str += "Assinado Camilo Sasuke Tsumanuma.";
	str += "Visible or Note?";

   command_signalid id;
   gen::signalid * pid;


   id.m_strCommand = "edit_undo";
   pid = m_signalidaCommand.get(&id);
   id.m_strCommand = "edit_redo";
   pid = m_signalidaCommand.get(&id);
   id.m_strCommand = "file_save";
   pid = m_signalidaCommand.get(&id);
   m_dispatchUpdateCmdUi.AddMessageHandler(pid, this, &netnodedsDoc::_001OnUpdateFileSave);
   m_dispatchCommand.AddMessageHandler(pid, this, &netnodedsDoc::_001OnFileSave);
   id.m_strCommand = "edit_cut";
   pid = m_signalidaCommand.get(&id);
   m_dispatchUpdateCmdUi.AddMessageHandler(pid, this, &netnodedsDoc::_001OnUpdateEditCut);
   m_dispatchCommand.AddMessageHandler(pid, this, &netnodedsDoc::_001OnEditCut);
   id.m_strCommand = "edit_copy";
   pid = m_signalidaCommand.get(&id);
   m_dispatchUpdateCmdUi.AddMessageHandler(pid, this, &netnodedsDoc::_001OnUpdateEditCopy);
   m_dispatchCommand.AddMessageHandler(pid, this, &netnodedsDoc::_001OnEditCopy);
   id.m_strCommand = "edit_paste";
   pid = m_signalidaCommand.get(&id);
   m_dispatchUpdateCmdUi.AddMessageHandler(pid, this, &netnodedsDoc::_001OnUpdateEditPaste);
   m_dispatchCommand.AddMessageHandler(pid, this, &netnodedsDoc::_001OnEditPaste);


}

BOOL netnodedsDoc::OnCmdMsg(UINT nID, int nCode, void* pExtra, CAFX_CMDHANDLERINFO* pHandlerInfo) 
{
/*   gen::application * papp = gen::get_app();
   CommandIdSpace idspace;
	if (nCode == CN_UPDATE_COMMAND_UI)
	{
      CCmdUI * pcmdui = (CCmdUI *) pExtra;
      if(nID == papp->GetResourceId(idspace, "file_save"))
      {
         OnUpdateFileSave(pcmdui);
         return TRUE;
      }
      else if(nID == papp->GetResourceId(idspace, "edit_undo"))
      {
         OnUpdateEditUndo(pcmdui);
         return TRUE;
      }
      else if(nID == 1003)
      {
         OnUpdateEditRedo(pcmdui);
         return TRUE;
      }
      else if(nID == 1004)
      {
         OnUpdateFilePut(pcmdui);
         return TRUE;
      }
	}
   else
   {
	   int nMsg = HIWORD(nCode);
	   nCode = LOWORD(nCode);

      // for backward compatibility HIWORD(nCode)==0 is WM_COMMAND
	   if (nMsg == 0)
		   nMsg = WM_COMMAND;

      if(nMsg == WM_COMMAND)
      {
         if(nID == 1001)
         {
            OnFileSave();
            return TRUE;
         }
         else if(nID == 1002)
         {
            OnEditUndo();
            return TRUE;
         }
         else if(nID == 1003)
         {
            OnEditRedo();
            return TRUE;
         }
         else if(nID == 1004)
         {
            OnFilePut();
            return TRUE;
         }
      }
   }*/
	return BaseDocument::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


BOOL netnodedsDoc::OnNewDocument()
{
	if (!BaseDocument::OnNewDocument())
		return FALSE;

   AStrArray wstra;
   VmsDataGet(VMSDATAKEY(SongDirectorySet), 0, 0, wstra);



   UpdateAllViews(NULL, 0);

	return TRUE;
}

netnodedsDoc::~netnodedsDoc()
{
}


BEGIN_MESSAGE_MAP(netnodedsDoc, BaseDocument)
	//{{AFX_MSG_MAP(netnodedsDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// netnodedsDoc diagnostics

#ifdef _DEBUG
void netnodedsDoc::AssertValid() const
{
	BaseDocument::AssertValid();
}

void netnodedsDoc::Dump(CDumpContext& dc) const
{
	BaseDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// netnodedsDoc serialization

/*
void netnodedsDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}
*/

BOOL netnodedsDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
   if(m_file.IsOpened())
      m_file.Close();
   if(!m_file.Open(lpszPathName, Ex1File::typeBinary | Ex1File::modeReadWrite |
      Ex1File::share_deny_none))
      return FALSE;
   POSITION pos = GetFirstViewPosition();
   m_pview = dynamic_cast < netnodedsView * > (GetNextView(pos));
   UpdateAllViews(NULL, 123);
   return TRUE;
}

void netnodedsDoc::reload()
{
   if(m_file.IsOpened())
      m_file.Close();
   if(!m_file.Open(GetPathName(), Ex1File::typeBinary | Ex1File::modeReadWrite |
      Ex1File::share_deny_none))
      return;
   UpdateAllViews(NULL, 123);
}


BOOL netnodedsDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
   UpdateAllViews(NULL, 12345);
   return TRUE;
}

void netnodedsDoc::_001OnUpdateFileSave(gen::signal_object * pobj)
{
   SCAST_PTR(BaseCmdUi, pcmdui, pobj);
   pcmdui->m_pcmdui->Enable(TRUE);
}

void netnodedsDoc::_001OnUpdateFilePut(gen::signal_object * pobj)
{
   SCAST_PTR(BaseCmdUi, pcmdui, pobj);
   pcmdui->m_pcmdui->Enable(TRUE);
}


void netnodedsDoc::_001OnUpdateEditCut(gen::signal_object * pobj)
{
   SCAST_PTR(BaseCmdUi, pcmdui, pobj);
   pcmdui->m_pcmdui->Enable(TRUE);
}

void netnodedsDoc::_001OnUpdateEditCopy(gen::signal_object * pobj)
{
   SCAST_PTR(BaseCmdUi, pcmdui, pobj);
   pcmdui->m_pcmdui->Enable(TRUE);
}

void netnodedsDoc::_001OnUpdateEditPaste(gen::signal_object * pobj)
{
   SCAST_PTR(BaseCmdUi, pcmdui, pobj);
   pcmdui->m_pcmdui->Enable(TRUE);
}

void netnodedsDoc::_001OnFileSave(gen::signal_object * pobj)
{
   BaseDocument::OnFileSave();
}

void netnodedsDoc::_001OnEditCut(gen::signal_object * pobj)
{
}
void netnodedsDoc::_001OnEditCopy(gen::signal_object * pobj)
{
}
void netnodedsDoc::_001OnEditPaste(gen::signal_object * pobj)
{
}

void netnodedsDoc::_001OnFilePut(gen::signal_object * pobj)
{
   BaseDocument::OnFileSave();
   Put();
}




void netnodedsDoc::Put()
{
   string strVotagusFolder;
   Application.dir().votagus(strVotagusFolder);
   string strCommon;
   string strRemote;
   strCommon = Application.dir().path(strVotagusFolder, "seed\\ca2\\fontopus\\net\\ds\\common");
   if(strCommon.compare_ci(GetPathName().Mid(0, strCommon.GetLength())) == 0)
   {
      strCommon = GetPathName().Mid(strCommon.GetLength());
      strCommon.Replace("\\", "/");
      strRemote = "seed/ca2/fontopus/net/ds/common" + strCommon;
      FtpPut(GetPathName(), strRemote);
   }
}

void netnodedsDoc::FtpPut(LPCTSTR lpcszLocal, LPCTSTR lpcszRemote)
{
   CInternetSession sess(_T("MyProgram/1.0"));

   CFtpConnection* pConnect = NULL;

    try
    {
        // Request a connection to ftp.microsoft.com. Default
        // parameters mean that we'll try with username = ANONYMOUS
        // and password set to the machine name @ domain name
        pConnect = sess.GetFtpConnection("votagus.net", file_contents_dup("C:\\archive\\root\\x\\sensitive\\sensitive\\seed\\netnodeds_user.txt"), file_contents_dup("C:\\archive\\root\\x\\sensitive\\sensitive\\seed\\netnodeds_pass.txt"));

        pConnect->PutFile(lpcszLocal, lpcszRemote);

    }
    catch (CInternetException* pEx)
    {
        TCHAR sz[1024];
        pEx->GetErrorMessage(sz, 1024);
        printf_s("ERROR!  %s\n", sz);
        pEx->Delete();
     }

    // if the connection is open, close it
    if (pConnect != NULL) 
    {
        pConnect->Close();
        delete pConnect;
    }

}

