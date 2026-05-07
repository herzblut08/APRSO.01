#pragma once

#include "RegisterForm.h"
#include "StudentForm.h"
#include "KomendantForm.h"
#include "TechForm.h"
#include "AdminForm.h"

namespace APRSO {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;
    using namespace System::ComponentModel;

    public ref class LoginForm : public System::Windows::Forms::Form
    {
    public:
        LoginForm(void)
        {
            InitializeComponent();
        }

    protected:
        ~LoginForm()
        {
            if (components)
                delete components;
        }

    private:
        System::ComponentModel::Container^ components;
        Panel^ panelHeader;
        Label^ lblTitle;
        Panel^ panelMain;
        Label^ lblSubtitle;
        Label^ lblLogin;
        TextBox^ txtLogin;
        Label^ lblPassword;
        TextBox^ txtPassword;
        Button^ btnLogin;
        LinkLabel^ lnkRegister;
        Label^ lblError;

    private:
        void InitializeComponent(void)
        {
            this->components = gcnew System::ComponentModel::Container();
            this->SuspendLayout();

            this->Text = L"ÈÑ Ñòóäåí÷åñêîãî îáùåæèòèÿ";
            this->Size = System::Drawing::Size(420, 520);
            this->StartPosition = FormStartPosition::CenterScreen;
            this->FormBorderStyle =
                System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;
            this->BackColor = Color::WhiteSmoke;
            this->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0f);

            // ØÀÏÊÀ
            panelHeader = gcnew Panel();
            panelHeader->Size = System::Drawing::Size(420, 60);
            panelHeader->Location = System::Drawing::Point(0, 0);
            panelHeader->BackColor = Color::FromArgb(52, 73, 94);

            lblTitle = gcnew Label();
            lblTitle->Text = L"ÈÑ Ñòóäåí÷åñêîãî îáùåæèòèÿ";
            lblTitle->ForeColor = Color::White;
            lblTitle->Font = gcnew System::Drawing::Font(
                L"Segoe UI", 13.0f, FontStyle::Bold);
            lblTitle->AutoSize = false;
            lblTitle->Size = System::Drawing::Size(420, 60);
            lblTitle->TextAlign = ContentAlignment::MiddleCenter;
            panelHeader->Controls->Add(lblTitle);
            this->Controls->Add(panelHeader);

            // ÎÑÍÎÂÍÀß ÏÀÍÅËÜ
            panelMain = gcnew Panel();
            panelMain->Size = System::Drawing::Size(360, 400);
            panelMain->Location = System::Drawing::Point(30, 80);
            panelMain->BackColor = Color::White;
            panelMain->BorderStyle =
                System::Windows::Forms::BorderStyle::FixedSingle;

            lblSubtitle = gcnew Label();
            lblSubtitle->Text = L"Âõîä â ñèñòåìó";
            lblSubtitle->Font = gcnew System::Drawing::Font(
                L"Segoe UI", 12.0f, FontStyle::Bold);
            lblSubtitle->ForeColor = Color::FromArgb(52, 73, 94);
            lblSubtitle->AutoSize = false;
            lblSubtitle->Size = System::Drawing::Size(340, 35);
            lblSubtitle->Location = System::Drawing::Point(10, 20);
            lblSubtitle->TextAlign = ContentAlignment::MiddleCenter;
            panelMain->Controls->Add(lblSubtitle);

            lblLogin = gcnew Label();
            lblLogin->Text = L"Ëîãèí:";
            lblLogin->Font = gcnew System::Drawing::Font(
                L"Segoe UI", 9.0f, FontStyle::Bold);
            lblLogin->Location = System::Drawing::Point(30, 80);
            lblLogin->AutoSize = true;
            panelMain->Controls->Add(lblLogin);

            txtLogin = gcnew TextBox();
            txtLogin->Location = System::Drawing::Point(30, 100);
            txtLogin->Size = System::Drawing::Size(300, 28);
            txtLogin->Font = gcnew System::Drawing::Font(L"Segoe UI", 10.0f);
            txtLogin->Text = L"ivanov_s";
            txtLogin->BorderStyle =
                System::Windows::Forms::BorderStyle::FixedSingle;
            panelMain->Controls->Add(txtLogin);

            lblPassword = gcnew Label();
            lblPassword->Text = L"Ïàðîëü:";
            lblPassword->Font = gcnew System::Drawing::Font(
                L"Segoe UI", 9.0f, FontStyle::Bold);
            lblPassword->Location = System::Drawing::Point(30, 145);
            lblPassword->AutoSize = true;
            panelMain->Controls->Add(lblPassword);

            txtPassword = gcnew TextBox();
            txtPassword->Location = System::Drawing::Point(30, 165);
            txtPassword->Size = System::Drawing::Size(300, 28);
            txtPassword->Font = gcnew System::Drawing::Font(L"Segoe UI", 10.0f);
            txtPassword->PasswordChar = '*';
            txtPassword->BorderStyle =
                System::Windows::Forms::BorderStyle::FixedSingle;
            panelMain->Controls->Add(txtPassword);

            lblError = gcnew Label();
            lblError->Text = L"";
            lblError->ForeColor = Color::Red;
            lblError->Location = System::Drawing::Point(30, 205);
            lblError->Size = System::Drawing::Size(300, 20);
            lblError->Font = gcnew System::Drawing::Font(L"Segoe UI", 8.5f);
            panelMain->Controls->Add(lblError);

            btnLogin = gcnew Button();
            btnLogin->Text = L"Âîéòè";
            btnLogin->Location = System::Drawing::Point(80, 235);
            btnLogin->Size = System::Drawing::Size(200, 40);
            btnLogin->BackColor = Color::FromArgb(52, 152, 219);
            btnLogin->ForeColor = Color::White;
            btnLogin->Font = gcnew System::Drawing::Font(
                L"Segoe UI", 11.0f, FontStyle::Bold);
            btnLogin->FlatStyle = FlatStyle::Flat;
            btnLogin->FlatAppearance->BorderSize = 0;
            btnLogin->Cursor = Cursors::Hand;
            btnLogin->Click += gcnew EventHandler(
                this, &LoginForm::btnLogin_Click);
            panelMain->Controls->Add(btnLogin);

            Label^ lblLine = gcnew Label();
            lblLine->BorderStyle =
                System::Windows::Forms::BorderStyle::Fixed3D;
            lblLine->Location = System::Drawing::Point(30, 295);
            lblLine->Size = System::Drawing::Size(300, 2);
            panelMain->Controls->Add(lblLine);

            lnkRegister = gcnew LinkLabel();
            lnkRegister->Text = L"Íåò àêêàóíòà? Çàðåãèñòðèðîâàòüñÿ";
            lnkRegister->Location = System::Drawing::Point(60, 310);
            lnkRegister->Size = System::Drawing::Size(250, 25);
            lnkRegister->TextAlign = ContentAlignment::MiddleCenter;
            lnkRegister->LinkColor = Color::FromArgb(52, 152, 219);
            lnkRegister->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0f);
            lnkRegister->LinkClicked +=
                gcnew LinkLabelLinkClickedEventHandler(
                    this, &LoginForm::lnkRegister_Click);
            panelMain->Controls->Add(lnkRegister);

            this->Controls->Add(panelMain);
            this->ResumeLayout(false);
        }

        // ÏÐÎÂÅÐÊÀ ËÎÃÈÍÀ È ÏÀÐÎËß
        String^ CheckCredentials(String^ login, String^ password)
        {
            if (login == L"ivanov_s" && password == L"student123")
                return L"student";
            if (login == L"petrova_av" && password == L"kom2025")
                return L"komendant";
            if (login == L"smirnov_pb" && password == L"tech2025")
                return L"tech";
            if (login == L"admin" && password == L"admin123")
                return L"admin";
            return L"";
        }

        // ÎÒÊÐÛÒÈÅ ÔÎÐÌÛ ÏÎ ÐÎËÈ
        void OpenRoleForm(String^ role, String^ login)
        {
            this->Hide();

            if (role == L"student")
            {
                StudentForm^ form = gcnew StudentForm(login);
                form->FormClosed += gcnew FormClosedEventHandler(
                    this, &LoginForm::OnSubFormClosed);
                form->Show();
            }
            else if (role == L"komendant")
            {
                KomendantForm^ form = gcnew KomendantForm(login);
                form->FormClosed += gcnew FormClosedEventHandler(
                    this, &LoginForm::OnSubFormClosed);
                form->Show();
            }
            else if (role == L"tech")
            {
                TechForm^ form = gcnew TechForm(login);
                form->FormClosed += gcnew FormClosedEventHandler(
                    this, &LoginForm::OnSubFormClosed);
                form->Show();
            }
            else if (role == L"admin")
            {
                AdminForm^ form = gcnew AdminForm(login);
                form->FormClosed += gcnew FormClosedEventHandler(
                    this, &LoginForm::OnSubFormClosed);
                form->Show();
            }
        }

        // ÂÎÇÂÐÀÒ ÍÀ ÔÎÐÌÓ ÂÕÎÄÀ
        void OnSubFormClosed(Object^ sender, FormClosedEventArgs^ e)
        {
            this->Show();
            txtLogin->Clear();
            txtPassword->Clear();
            lblError->Text = L"";
        }

        // ÊÍÎÏÊÀ ÂÎÉÒÈ
        void btnLogin_Click(Object^ sender, EventArgs^ e)
        {
            String^ login = txtLogin->Text->Trim();
            String^ password = txtPassword->Text;
            lblError->Text = L"";

            if (login == L"" || password == L"")
            {
                lblError->Text = L"Çàïîëíèòå îáÿçàòåëüíûå ïîëÿ";
                return;
            }

            String^ role = CheckCredentials(login, password);

            if (role == L"")
            {
                lblError->Text = L"Íåâåðíûé ëîãèí èëè ïàðîëü";
                return;
            }

            OpenRoleForm(role, login);
        }

        // ÑÑÛËÊÀ ÇÀÐÅÃÈÑÒÐÈÐÎÂÀÒÜÑß
        void lnkRegister_Click(Object^ sender,
            LinkLabelLinkClickedEventArgs^ e)
        {
            RegisterForm^ form = gcnew RegisterForm();
            form->ShowDialog();
        }
    };
}