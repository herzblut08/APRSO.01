#pragma once


namespace APRSO {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class RegisterForm : public System::Windows::Forms::Form
    {
    public:
        RegisterForm(void) { InitializeComponent(); }

    protected:
        ~RegisterForm() { if (components) delete components; }

    private:
        System::ComponentModel::Container^ components;

        Panel^ panelHeader;
        Label^ lblTitle;
        Panel^ panelMain;

        Label^ lblSubtitle;
        Label^ lblFio;
        TextBox^ txtFio;
        Label^ lblEmail;
        TextBox^ txtEmail;
        Label^ lblPhone;
        TextBox^ txtPhone;
        Label^ lblGroup;
        TextBox^ txtGroup;
        Label^ lblLogin;
        TextBox^ txtLogin;
        Label^ lblPassword;
        TextBox^ txtPassword;
        Label^ lblRepeat;
        TextBox^ txtRepeat;
        Button^ btnRegister;
        LinkLabel^ lnkLogin;
        Label^ lblError;

    private:
        void InitializeComponent(void)
        {
            this->SuspendLayout();

            // ===== ФОРМА =====
            this->Text = L"Регистрация — ИС Студенческого общежития";
            this->Size = System::Drawing::Size(440, 660);
            this->StartPosition = FormStartPosition::CenterScreen;
            this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
            this->MaximizeBox = false;
            this->BackColor = Color::WhiteSmoke;
            this->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0f);

            // ===== ШАПКА =====
            panelHeader = gcnew Panel();
            panelHeader->Size = System::Drawing::Size(440, 55);
            panelHeader->Location = System::Drawing::Point(0, 0);
            panelHeader->BackColor = Color::FromArgb(52, 73, 94);

            lblTitle = gcnew Label();
            lblTitle->Text = L"ИС Студенческого общежития";
            lblTitle->ForeColor = Color::White;
            lblTitle->Font = gcnew System::Drawing::Font(L"Segoe UI", 13.0f, FontStyle::Bold);
            lblTitle->Size = System::Drawing::Size(440, 55);
            lblTitle->TextAlign = ContentAlignment::MiddleCenter;
            panelHeader->Controls->Add(lblTitle);
            this->Controls->Add(panelHeader);

            // ===== ПАНЕЛЬ КОНТЕНТА =====
            panelMain = gcnew Panel();
            panelMain->Size = System::Drawing::Size(390, 560);
            panelMain->Location = System::Drawing::Point(25, 70);
            panelMain->BackColor = Color::White;
            panelMain->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;

            // Подзаголовок
            lblSubtitle = gcnew Label();
            lblSubtitle->Text = L"Регистрация нового пользователя";
            lblSubtitle->Font = gcnew System::Drawing::Font(L"Segoe UI", 11.0f, FontStyle::Bold);
            lblSubtitle->ForeColor = Color::FromArgb(52, 73, 94);
            lblSubtitle->Size = System::Drawing::Size(370, 30);
            lblSubtitle->Location = System::Drawing::Point(10, 15);
            lblSubtitle->TextAlign = ContentAlignment::MiddleCenter;
            panelMain->Controls->Add(lblSubtitle);

            // Вспомогательная функция создания полей
            int yPos = 55;
            int gap = 52;

            // ФИО
            AddFieldLabel(panelMain, L"ФИО:", yPos);
            txtFio = AddFieldBox(panelMain, L"Иванов Сергей Александрович", yPos + 18);
            yPos += gap;

            // Email
            AddFieldLabel(panelMain, L"Email:", yPos);
            txtEmail = AddFieldBox(panelMain, L"ivanov@mail.ru", yPos + 18);
            yPos += gap;

            // Телефон
            AddFieldLabel(panelMain, L"Телефон:", yPos);
            txtPhone = AddFieldBox(panelMain, L"+7 (900) 123-45-67", yPos + 18);
            yPos += gap;

            // Группа
            AddFieldLabel(panelMain, L"Группа:", yPos);
            txtGroup = AddFieldBox(panelMain, L"СИд-023", yPos + 18);
            yPos += gap;

            // Логин
            AddFieldLabel(panelMain, L"Логин:", yPos);
            txtLogin = AddFieldBox(panelMain, L"ivanov_s", yPos + 18);
            yPos += gap;

            // Пароль
            AddFieldLabel(panelMain, L"Пароль:", yPos);
            txtPassword = AddFieldBox(panelMain, L"", yPos + 18);
            txtPassword->PasswordChar = '*';
            yPos += gap;

            // Повтор пароля
            AddFieldLabel(panelMain, L"Повтор пароля:", yPos);
            txtRepeat = AddFieldBox(panelMain, L"", yPos + 18);
            txtRepeat->PasswordChar = '*';
            yPos += gap;

            // Ошибка
            lblError = gcnew Label();
            lblError->Text = L"";
            lblError->ForeColor = Color::Red;
            lblError->Location = System::Drawing::Point(25, yPos);
            lblError->Size = System::Drawing::Size(340, 18);
            panelMain->Controls->Add(lblError);

            // Кнопка регистрации
            btnRegister = gcnew Button();
            btnRegister->Text = L"Зарегистрироваться";
            btnRegister->Location = System::Drawing::Point(70, yPos + 22);
            btnRegister->Size = System::Drawing::Size(250, 38);
            btnRegister->BackColor = Color::FromArgb(52, 152, 219);
            btnRegister->ForeColor = Color::White;
            btnRegister->Font = gcnew System::Drawing::Font(L"Segoe UI", 10.0f, FontStyle::Bold);
            btnRegister->FlatStyle = FlatStyle::Flat;
            btnRegister->FlatAppearance->BorderSize = 0;
            btnRegister->Cursor = Cursors::Hand;
            btnRegister->Click += gcnew EventHandler(this, &RegisterForm::btnRegister_Click);
            panelMain->Controls->Add(btnRegister);

            // Ссылка на вход
            lnkLogin = gcnew LinkLabel();
            lnkLogin->Text = L"Уже есть аккаунт? Войти";
            lnkLogin->Location = System::Drawing::Point(110, yPos + 68);
            lnkLogin->Size = System::Drawing::Size(170, 20);
            lnkLogin->TextAlign = ContentAlignment::MiddleCenter;
            lnkLogin->LinkColor = Color::FromArgb(52, 152, 219);
            lnkLogin->LinkClicked += gcnew LinkLabelLinkClickedEventHandler(
                this, &RegisterForm::lnkLogin_Click);
            panelMain->Controls->Add(lnkLogin);

            this->Controls->Add(panelMain);
            this->ResumeLayout(false);
        }

        // Создаёт Label для поля
        void AddFieldLabel(Panel^ parent, String^ text, int y)
        {
            Label^ lbl = gcnew Label();
            lbl->Text = text;
            lbl->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0f, FontStyle::Bold);
            lbl->Location = System::Drawing::Point(25, y);
            lbl->AutoSize = true;
            parent->Controls->Add(lbl);
        }

        // Создаёт TextBox для поля
        TextBox^ AddFieldBox(Panel^ parent, String^ placeholder, int y)
        {
            TextBox^ tb = gcnew TextBox();
            tb->Location = System::Drawing::Point(25, y);
            tb->Size = System::Drawing::Size(335, 26);
            tb->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5f);
            tb->Text = placeholder;
            tb->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
            parent->Controls->Add(tb);
            return tb;
        }

        // ===== ОБРАБОТЧИКИ =====
        void btnRegister_Click(Object^ sender, EventArgs^ e)
        {
            lblError->Text = L"";

            if (txtFio->Text->Trim() == L"" || txtLogin->Text->Trim() == L""
                || txtPassword->Text == L"" || txtEmail->Text->Trim() == L"")
            {
                lblError->Text = L"Заполните все обязательные поля";
                return;
            }

            if (txtPassword->Text != txtRepeat->Text)
            {
                lblError->Text = L"Пароли не совпадают";
                return;
            }

            MessageBox::Show(
                L"Пользователь «" + txtFio->Text + L"» успешно зарегистрирован!\n"
                L"Роль: Студент",
                L"Регистрация завершена",
                MessageBoxButtons::OK, MessageBoxIcon::Information);

            this->Close();
        }

        void lnkLogin_Click(Object^ sender, LinkLabelLinkClickedEventArgs^ e)
        {
            this->Close();
        }
    };
}