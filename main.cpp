#include <wx/wx.h>
#include <wx/clipbrd.h>
#include "include/base64.h"

enum
{
    ID_Hello = 1
};


class MyApp : public wxApp
{
public:
    bool OnInit() override;
};

wxIMPLEMENT_APP(MyApp);



class MainFrame : public wxFrame
{
public:
    MainFrame();
 
private:
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
};
 



 
bool MyApp::OnInit()
{
    MainFrame *frame = new MainFrame();
    frame->Show(true);
    frame->SetSize(wxSize(800, 600));
    frame->Center();
    frame->SetMaxSize(wxSize(800, 600));
    frame->SetMinSize(wxSize(800, 600));
    return true;
}



 
MainFrame::MainFrame() : wxFrame(nullptr, wxID_ANY, "Base64 Encoder/Decoder")
{

    wxMenu *menuHelp = new wxMenu;
    menuHelp->Append(wxID_ABOUT);
    menuHelp->Append(wxID_EXIT, "&Exit");
 
    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuHelp, "&Help");
 
    SetMenuBar( menuBar );
    
    wxArrayString choices;
    choices.Add("Decode");
    choices.Add("Encode");    wxPanel *panel = new wxPanel(this, wxID_ANY);
    wxTextCtrl *textctrl = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(20, 20), wxSize(740, 80), wxTE_MULTILINE | wxTE_WORDWRAP);
    wxChoice *choice = new wxChoice(panel, wxID_ANY, wxPoint(350, 113), wxSize(100, 30), choices);
    wxButton *button = new wxButton(panel, wxID_ANY, "Process", wxPoint(180, 110), wxSize(100, 30));
    wxButton *cpybutton = new wxButton(panel, wxID_ANY, "Copy", wxPoint(520, 110), wxSize(100, 30));
    wxStaticText *label = new wxStaticText(panel, wxID_ANY, "Result:", wxPoint(20, 140));
    wxTextCtrl *resultLabel = new wxTextCtrl(panel, wxID_ANY, "", wxPoint(20, 160), wxSize(740, 360), wxTE_MULTILINE | wxTE_READONLY | wxTE_WORDWRAP);
    
    
    button->Bind(wxEVT_BUTTON, [textctrl, choice, choices, resultLabel](wxCommandEvent& event) {
        wxString input = textctrl->GetValue();
        wxString result = "";
        if (choice->GetSelection() == choices.Index("Decode")) {
            result = base64_decode(input.ToStdString());
            
        } else if (choice->GetSelection() == choices.Index("Encode")) {
            result = base64_encode(input.ToStdString());
        }
        resultLabel->SetValue(result);
        
    });    cpybutton->Bind(wxEVT_BUTTON, [resultLabel](wxCommandEvent& event) {
        wxString result = resultLabel->GetValue().AfterFirst(':').Trim(true).Trim(false);
        if (wxTheClipboard->Open()) {
            wxTheClipboard->SetData(new wxTextDataObject(result));
            wxTheClipboard->Close();
        }
    });

    choice->SetSelection(1);

    Bind(wxEVT_MENU, &MainFrame::OnAbout, this, wxID_ABOUT);
    Bind(wxEVT_MENU, &MainFrame::OnExit, this, wxID_EXIT);
}
 
void MainFrame::OnExit(wxCommandEvent& event)
{
    Close(true);
}
 
void MainFrame::OnAbout(wxCommandEvent& event)
{
    wxMessageBox("This is a simple wxWidgets application that encodes and decodes Base64 strings made just for fun and try wxWidgets.\nI used Ai to help me with CmakeLists.txt.",
                 "About", wxOK | wxICON_INFORMATION);
}
 
