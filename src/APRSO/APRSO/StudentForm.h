#pragma once

namespace APRSO {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class StudentForm : public System::Windows::Forms::Form
    {
    public:
        String^ currentUser;

        StudentForm(String^ username)
        {
            currentUser = username;
            InitializeComponent();
        }

    protected:
        ~StudentForm() { if (components) delete components; }

    private:
        System::ComponentModel::Container^ components;

        // Шапка
        Panel^ panelTop;
        Label^ lblHeader;
        Button^ btnLogout;

        // Меню слева
        Panel^ panelMenu;
        Button^ btnMenuCabinet;
        Button^ btnMenuApps;
        Button^ btnMenuContract;
        Button^ btnMenuPayment;
        Button^ btnMenuHelp;

        // Контент
        Panel^ panelContent;

        // Новая заявка
        GroupBox^ grpNewApp;
        Label^ lblTema;
        TextBox^ txtTema;
        Label^ lblCategory;
        ComboBox^ cmbCategory;
        Label^ lblDesc;
        TextBox^ txtDesc;
        Button^ btnSend;

        // Мои заявки
        GroupBox^ grpMyApps;
        ListView^ lvApps;

        // Договор
        GroupBox^ grpContract;
        Label^ lblContractInfo;
        Label^ lblPaymentInfo;
        Button^ btnGetHelp;

    private:
        void InitializeComponent(void)
        {
            this->SuspendLayout();

            this->Text = L"Личный кабинет студента — АПРСО";
            this->Size = System::Drawing::Size(950, 680);
            this->StartPosition = FormStartPosition::CenterScreen;
            this->BackColor = Color::FromArgb(245, 245, 245);
            this->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0f);
            this->MinimumSize = System::Drawing::Size(900, 600);

            // ===== ШАПКА =====
            panelTop = gcnew Panel();
            panelTop->Dock = DockStyle::Top;
            panelTop->Height = 45;
            panelTop->BackColor = Color::FromArgb(52, 73, 94);

            lblHeader = gcnew Label();
            lblHeader->Text = L"ИС Студенческого общежития  |  " + currentUser + L"  |  Комната 214";
            lblHeader->ForeColor = Color::White;
            lblHeader->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5f);
            lblHeader->Location = System::Drawing::Point(10, 0);
            lblHeader->Size = System::Drawing::Size(750, 45);
            lblHeader->TextAlign = ContentAlignment::MiddleLeft;
            panelTop->Controls->Add(lblHeader);

            btnLogout = gcnew Button();
            btnLogout->Text = L"Выход";
            btnLogout->Location = System::Drawing::Point(860, 8);
            btnLogout->Size = System::Drawing::Size(70, 28);
            btnLogout->BackColor = Color::FromArgb(192, 57, 43);
            btnLogout->ForeColor = Color::White;
            btnLogout->FlatStyle = FlatStyle::Flat;
            btnLogout->FlatAppearance->BorderSize = 0;
            btnLogout->Cursor = Cursors::Hand;
            btnLogout->Click += gcnew EventHandler(this, &StudentForm::btnLogout_Click);
            panelTop->Controls->Add(btnLogout);
            this->Controls->Add(panelTop);

            // ===== ЛЕВОЕ МЕНЮ =====
            panelMenu = gcnew Panel();
            panelMenu->Location = System::Drawing::Point(0, 45);
            panelMenu->Size = System::Drawing::Size(160, 635);
            panelMenu->BackColor = Color::FromArgb(44, 62, 80);

            // ВСТАВИТЬ ЭТО:
            array<String^>^ menuItems = gcnew array<String^>(5);
            menuItems[0] = L"Мой кабинет";
            menuItems[1] = L"Мои заявки";
            menuItems[2] = L"Мой договор";
            menuItems[3] = L"Оплата";
            menuItems[4] = L"Справка";

            for (int i = 0; i < 5; i++)
            {
                Button^ btn = gcnew Button();
                btn->Text = menuItems[i];
                btn->Location = System::Drawing::Point(0, i * 45);
                btn->Size = System::Drawing::Size(160, 45);
                btn->BackColor = Color::FromArgb(44, 62, 80);
                btn->ForeColor = Color::White;
                btn->FlatStyle = FlatStyle::Flat;
                btn->FlatAppearance->BorderSize = 0;
                btn->FlatAppearance->BorderColor = Color::FromArgb(44, 62, 80);
                btn->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5f);
                btn->TextAlign = ContentAlignment::MiddleLeft;
                btn->Padding = System::Windows::Forms::Padding(15, 0, 0, 0);
                btn->Cursor = Cursors::Hand;
                btn->Tag = i;
                btn->Click += gcnew EventHandler(this, &StudentForm::menuBtn_Click);
                panelMenu->Controls->Add(btn);
            }
            this->Controls->Add(panelMenu);

            // ===== ПАНЕЛЬ КОНТЕНТА =====
            panelContent = gcnew Panel();
            panelContent->Location = System::Drawing::Point(160, 45);
            panelContent->Size = System::Drawing::Size(775, 635);
            panelContent->BackColor = Color::FromArgb(245, 245, 245);
            panelContent->AutoScroll = true;
            this->Controls->Add(panelContent);

            // Инициализация контента
            BuildContent();

            this->ResumeLayout(false);
        }

        void BuildContent()
        {
            panelContent->Controls->Clear();

            // ===== НОВАЯ ЗАЯВКА =====
            grpNewApp = gcnew GroupBox();
            grpNewApp->Text = L"  НОВАЯ ЗАЯВКА";
            grpNewApp->Font = gcnew System::Drawing::Font(L"Segoe UI", 10.0f, FontStyle::Bold);
            grpNewApp->ForeColor = Color::FromArgb(52, 73, 94);
            grpNewApp->Location = System::Drawing::Point(15, 10);
            grpNewApp->Size = System::Drawing::Size(740, 195);
            grpNewApp->BackColor = Color::White;

            lblTema = gcnew Label();
            lblTema->Text = L"Тема обращения:";
            lblTema->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0f, FontStyle::Bold);
            lblTema->Location = System::Drawing::Point(15, 28);
            lblTema->AutoSize = true;
            grpNewApp->Controls->Add(lblTema);

            txtTema = gcnew TextBox();
            txtTema->Location = System::Drawing::Point(15, 48);
            txtTema->Size = System::Drawing::Size(500, 26);
            txtTema->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
            grpNewApp->Controls->Add(txtTema);

            lblCategory = gcnew Label();
            lblCategory->Text = L"Категория:";
            lblCategory->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0f, FontStyle::Bold);
            lblCategory->Location = System::Drawing::Point(530, 28);
            lblCategory->AutoSize = true;
            grpNewApp->Controls->Add(lblCategory);

            cmbCategory = gcnew ComboBox();
            cmbCategory->Location = System::Drawing::Point(530, 48);
            cmbCategory->Size = System::Drawing::Size(190, 26);
            cmbCategory->DropDownStyle = ComboBoxStyle::DropDownList;
            cmbCategory->Items->Add(L"Ремонт");
            cmbCategory->Items->Add(L"Административный вопрос");
            cmbCategory->Items->Add(L"Оплата");
            cmbCategory->Items->Add(L"Другое");
            cmbCategory->SelectedIndex = 0;
            grpNewApp->Controls->Add(cmbCategory);

            lblDesc = gcnew Label();
            lblDesc->Text = L"Описание проблемы:";
            lblDesc->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0f, FontStyle::Bold);
            lblDesc->Location = System::Drawing::Point(15, 85);
            lblDesc->AutoSize = true;
            grpNewApp->Controls->Add(lblDesc);

            txtDesc = gcnew TextBox();
            txtDesc->Location = System::Drawing::Point(15, 103);
            txtDesc->Size = System::Drawing::Size(590, 65);
            txtDesc->Multiline = true;
            txtDesc->ScrollBars = ScrollBars::Vertical;
            txtDesc->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
            grpNewApp->Controls->Add(txtDesc);

            btnSend = gcnew Button();
            btnSend->Text = L"Отправить заявку";
            btnSend->Location = System::Drawing::Point(620, 103);
            btnSend->Size = System::Drawing::Size(105, 65);
            btnSend->BackColor = Color::FromArgb(52, 152, 219);
            btnSend->ForeColor = Color::White;
            btnSend->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0f, FontStyle::Bold);
            btnSend->FlatStyle = FlatStyle::Flat;
            btnSend->FlatAppearance->BorderSize = 0;
            btnSend->Cursor = Cursors::Hand;
            btnSend->Click += gcnew EventHandler(this, &StudentForm::btnSend_Click);
            grpNewApp->Controls->Add(btnSend);

            panelContent->Controls->Add(grpNewApp);

            // ===== МОИ ЗАЯВКИ =====
            grpMyApps = gcnew GroupBox();
            grpMyApps->Text = L"  МОИ ЗАЯВКИ";
            grpMyApps->Font = gcnew System::Drawing::Font(L"Segoe UI", 10.0f, FontStyle::Bold);
            grpMyApps->ForeColor = Color::FromArgb(52, 73, 94);
            grpMyApps->Location = System::Drawing::Point(15, 215);
            grpMyApps->Size = System::Drawing::Size(740, 195);
            grpMyApps->BackColor = Color::White;

            lvApps = gcnew ListView();
            lvApps->Location = System::Drawing::Point(10, 25);
            lvApps->Size = System::Drawing::Size(715, 158);
            lvApps->View = View::Details;
            lvApps->FullRowSelect = true;
            lvApps->GridLines = true;
            lvApps->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0f);

            lvApps->Columns->Add(L"№", 50);
            lvApps->Columns->Add(L"Тема", 230);
            lvApps->Columns->Add(L"Категория", 120);
            lvApps->Columns->Add(L"Статус", 120);
            lvApps->Columns->Add(L"Дата", 110);

            // Тестовые данные
            AddAppRow(lvApps, L"201", L"Не работает кран",
                L"Ремонт", L"В работе", L"12.06.2025");
            AddAppRow(lvApps, L"198", L"Вопрос по оплате",
                L"Адм. вопрос", L"Закрыта", L"05.06.2025");
            AddAppRow(lvApps, L"195", L"Сломан стол",
                L"Ремонт", L"Закрыта", L"28.05.2025");
            AddAppRow(lvApps, L"190", L"Нет горячей воды",
                L"Ремонт", L"Новая", L"20.05.2025");

            // Цветовая маркировка статусов
            for (int i = 0; i < lvApps->Items->Count; i++)
            {
                String^ status = lvApps->Items[i]->SubItems[3]->Text;
                if (status == L"В работе")
                    lvApps->Items[i]->ForeColor = Color::FromArgb(41, 128, 185);
                else if (status == L"Закрыта")
                    lvApps->Items[i]->ForeColor = Color::FromArgb(39, 174, 96);
                else if (status == L"Новая")
                    lvApps->Items[i]->ForeColor = Color::FromArgb(243, 156, 18);
            }

            grpMyApps->Controls->Add(lvApps);
            panelContent->Controls->Add(grpMyApps);

            // ===== МОЙ ДОГОВОР И ОПЛАТА =====
            grpContract = gcnew GroupBox();
            grpContract->Text = L"  МОЙ ДОГОВОР И ОПЛАТА";
            grpContract->Font = gcnew System::Drawing::Font(L"Segoe UI", 10.0f, FontStyle::Bold);
            grpContract->ForeColor = Color::FromArgb(52, 73, 94);
            grpContract->Location = System::Drawing::Point(15, 420);
            grpContract->Size = System::Drawing::Size(740, 120);
            grpContract->BackColor = Color::White;

            lblContractInfo = gcnew Label();
            lblContractInfo->Text =
                L"Номер договора: ДП-2025-214   Комната: 214 (2-местная)   "
                L"Срок: 01.09.2025 – 30.06.2026";
            lblContractInfo->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0f);
            lblContractInfo->Location = System::Drawing::Point(15, 28);
            lblContractInfo->Size = System::Drawing::Size(710, 22);
            grpContract->Controls->Add(lblContractInfo);

            lblPaymentInfo = gcnew Label();
            lblPaymentInfo->Text =
                L"Статус оплаты: Оплачено до 30.06.2025   "
                L"Следующий платёж: 01.07.2025   Сумма: 2 800 руб.";
            lblPaymentInfo->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0f);
            lblPaymentInfo->ForeColor = Color::FromArgb(39, 174, 96);
            lblPaymentInfo->Location = System::Drawing::Point(15, 55);
            lblPaymentInfo->Size = System::Drawing::Size(560, 22);
            grpContract->Controls->Add(lblPaymentInfo);

            btnGetHelp = gcnew Button();
            btnGetHelp->Text = L"Запросить справку о проживании";
            btnGetHelp->Location = System::Drawing::Point(15, 80);
            btnGetHelp->Size = System::Drawing::Size(250, 30);
            btnGetHelp->BackColor = Color::FromArgb(44, 62, 80);
            btnGetHelp->ForeColor = Color::White;
            btnGetHelp->FlatStyle = FlatStyle::Flat;
            btnGetHelp->FlatAppearance->BorderSize = 0;
            btnGetHelp->Cursor = Cursors::Hand;
            btnGetHelp->Click += gcnew EventHandler(this, &StudentForm::btnGetHelp_Click);
            grpContract->Controls->Add(btnGetHelp);

            panelContent->Controls->Add(grpContract);
        }

        // Добавление строки в ListView заявок
        void AddAppRow(ListView^ lv, String^ num, String^ tema,
            String^ cat, String^ status, String^ date)
        {
            ListViewItem^ item = gcnew ListViewItem(num);
            item->SubItems->Add(tema);
            item->SubItems->Add(cat);
            item->SubItems->Add(status);
            item->SubItems->Add(date);
            lv->Items->Add(item);
        }

        // ===== ОБРАБОТЧИКИ =====
        void menuBtn_Click(Object^ sender, EventArgs^ e)
        {
            Button^ btn = safe_cast<Button^>(sender);
            // Сброс цвета всех кнопок
            for each (Control ^ c in panelMenu->Controls)
            {
                if (Button^ b = dynamic_cast<Button^>(c))
                    b->BackColor = Color::FromArgb(44, 62, 80);
            }
            btn->BackColor = Color::FromArgb(52, 152, 219);
        }

        void btnSend_Click(Object^ sender, EventArgs^ e)
        {
            if (txtTema->Text->Trim() == L"")
            {
                MessageBox::Show(L"Заполните обязательные поля (тема обращения).",
                    L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }
            MessageBox::Show(
                L"Заявка №204 создана!\nСтатус: Новая\nТема: " + txtTema->Text,
                L"Заявка отправлена", MessageBoxButtons::OK, MessageBoxIcon::Information);
            txtTema->Clear();
            txtDesc->Clear();
        }

        void btnGetHelp_Click(Object^ sender, EventArgs^ e)
        {
            MessageBox::Show(
                L"Справка о проживании сформирована и доступна для скачивания.",
                L"Справка", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }

        void btnLogout_Click(Object^ sender, EventArgs^ e)
        {
            if (MessageBox::Show(L"Выйти из системы?", L"Выход",
                MessageBoxButtons::YesNo, MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes)
                this->Close();
        }
    };
}