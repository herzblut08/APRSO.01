#pragma once

namespace APRSO {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class AdminForm : public System::Windows::Forms::Form
    {
    public:
        String^ currentUser;

        AdminForm(String^ username)
        {
            currentUser = username;
            InitializeComponent();
        }

    protected:
        ~AdminForm()
        {
            if (components)
                delete components;
        }

    private:
        System::ComponentModel::Container^ components;

        Panel^ panelTop;
        Label^ lblHeader;
        Button^ btnLogout;
        Panel^ panelMenu;
        Panel^ panelContent;
        GroupBox^ grpUsers;
        ListView^ lvUsers;
        Button^ btnAddUser;
        GroupBox^ grpReports;
        Label^ lblReportType;
        ComboBox^ cmbReportType;
        Label^ lblPeriodFrom;
        DateTimePicker^ dtFrom;
        Label^ lblPeriodTo;
        DateTimePicker^ dtTo;
        Button^ btnGenerate;
        Button^ btnExport;
        Label^ lblReportResult;

    private:
        void InitializeComponent(void)
        {
            this->components = gcnew System::ComponentModel::Container();
            this->SuspendLayout();

            this->Text = L"Панель администратора — АПРСО";
            this->Size = System::Drawing::Size(1000, 700);
            this->StartPosition = FormStartPosition::CenterScreen;
            this->BackColor = Color::FromArgb(245, 245, 245);
            this->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0f);

            // ===== ШАПКА =====
            panelTop = gcnew Panel();
            panelTop->Dock = DockStyle::Top;
            panelTop->Height = 45;
            panelTop->BackColor = Color::FromArgb(52, 73, 94);

            lblHeader = gcnew Label();
            lblHeader->Text = L"ИС Студенческого общежития  |  Администратор системы";
            lblHeader->ForeColor = Color::White;
            lblHeader->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5f);
            lblHeader->Location = System::Drawing::Point(10, 0);
            lblHeader->Size = System::Drawing::Size(750, 45);
            lblHeader->TextAlign = ContentAlignment::MiddleLeft;
            panelTop->Controls->Add(lblHeader);

            btnLogout = gcnew Button();
            btnLogout->Text = L"Выход";
            btnLogout->Location = System::Drawing::Point(900, 8);
            btnLogout->Size = System::Drawing::Size(70, 28);
            btnLogout->BackColor = Color::FromArgb(192, 57, 43);
            btnLogout->ForeColor = Color::White;
            btnLogout->FlatStyle = FlatStyle::Flat;
            btnLogout->FlatAppearance->BorderSize = 0;
            btnLogout->Cursor = Cursors::Hand;
            btnLogout->Click += gcnew EventHandler(
                this, &AdminForm::btnLogout_Click);
            panelTop->Controls->Add(btnLogout);
            this->Controls->Add(panelTop);

            // ===== ЛЕВОЕ МЕНЮ =====
            panelMenu = gcnew Panel();
            panelMenu->Location = System::Drawing::Point(0, 45);
            panelMenu->Size = System::Drawing::Size(150, 655);
            panelMenu->BackColor = Color::FromArgb(44, 62, 80);

            // ВСТАВИТЬ ЭТО:
            array<String^>^ menuItems = gcnew array<String^>(5);
            menuItems[0] = L"Главная";
            menuItems[1] = L"Пользователи";
            menuItems[2] = L"Справочники";
            menuItems[3] = L"Отчёты";
            menuItems[4] = L"Настройки";

            for (int i = 0; i < 5; i++)
            {
                Button^ btn = gcnew Button();
                btn->Text = menuItems[i];
                btn->Location = System::Drawing::Point(0, i * 48);
                btn->Size = System::Drawing::Size(150, 48);
                btn->BackColor = (i == 0)
                    ? Color::FromArgb(52, 152, 219)
                    : Color::FromArgb(44, 62, 80);
                btn->ForeColor = Color::White;
                btn->FlatStyle = FlatStyle::Flat;
                btn->FlatAppearance->BorderSize = 0;
                btn->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0f);
                btn->Cursor = Cursors::Hand;
                panelMenu->Controls->Add(btn);
            }
            this->Controls->Add(panelMenu);

            // ===== КОНТЕНТ =====
            panelContent = gcnew Panel();
            panelContent->Location = System::Drawing::Point(150, 45);
            panelContent->Size = System::Drawing::Size(840, 655);
            panelContent->AutoScroll = true;
            this->Controls->Add(panelContent);

            BuildContent();
            this->ResumeLayout(false);
        }

        void BuildContent()
        {
            panelContent->Controls->Clear();

            // ===== УПРАВЛЕНИЕ ПОЛЬЗОВАТЕЛЯМИ =====
            grpUsers = gcnew GroupBox();
            grpUsers->Text = L"  УПРАВЛЕНИЕ ПОЛЬЗОВАТЕЛЯМИ";
            grpUsers->Font = gcnew System::Drawing::Font(
                L"Segoe UI", 10.0f, FontStyle::Bold);
            grpUsers->ForeColor = Color::FromArgb(52, 73, 94);
            grpUsers->Location = System::Drawing::Point(10, 10);
            grpUsers->Size = System::Drawing::Size(815, 240);
            grpUsers->BackColor = Color::White;
            panelContent->Controls->Add(grpUsers);

            btnAddUser = gcnew Button();
            btnAddUser->Text = L"+ Добавить пользователя";
            btnAddUser->Location = System::Drawing::Point(555, 22);
            btnAddUser->Size = System::Drawing::Size(245, 30);
            btnAddUser->BackColor = Color::FromArgb(39, 174, 96);
            btnAddUser->ForeColor = Color::White;
            btnAddUser->FlatStyle = FlatStyle::Flat;
            btnAddUser->FlatAppearance->BorderSize = 0;
            btnAddUser->Font = gcnew System::Drawing::Font(
                L"Segoe UI", 9.5f, FontStyle::Bold);
            btnAddUser->Cursor = Cursors::Hand;
            btnAddUser->Click += gcnew EventHandler(
                this, &AdminForm::btnAddUser_Click);
            grpUsers->Controls->Add(btnAddUser);

            lvUsers = gcnew ListView();
            lvUsers->Location = System::Drawing::Point(10, 60);
            lvUsers->Size = System::Drawing::Size(790, 168);
            lvUsers->View = View::Details;
            lvUsers->FullRowSelect = true;
            lvUsers->GridLines = true;
            lvUsers->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0f);

            lvUsers->Columns->Add(L"ID", 40);
            lvUsers->Columns->Add(L"ФИО", 200);
            lvUsers->Columns->Add(L"Email", 190);
            lvUsers->Columns->Add(L"Роль", 130);
            lvUsers->Columns->Add(L"Статус", 80);
            lvUsers->Columns->Add(L"Действия", 110);

            AddUserRow(lvUsers, L"1", L"Иванов С.А.",
                L"ivanov@u.ru", L"Студент", L"Активен");
            AddUserRow(lvUsers, L"2", L"Петрова А.В.",
                L"petrova@u.ru", L"Комендант", L"Активен");
            AddUserRow(lvUsers, L"3", L"Смирнов П.В.",
                L"smirnov@u.ru", L"Тех. сотрудник", L"Активен");
            AddUserRow(lvUsers, L"4", L"Козлова М.Д.",
                L"kozlova@u.ru", L"Студент", L"Активен");
            AddUserRow(lvUsers, L"5", L"Администратор",
                L"admin@u.ru", L"Администратор", L"Активен");

            lvUsers->Items[1]->BackColor = Color::FromArgb(230, 250, 235);
            lvUsers->Items[4]->BackColor = Color::FromArgb(230, 230, 250);

            grpUsers->Controls->Add(lvUsers);

            // Кнопки Изм. / Удал. для каждой строки
            int rowY = 60;
            for (int i = 0; i < 5; i++)
            {
                Button^ bEdit = gcnew Button();
                bEdit->Text = L"Изм.";
                bEdit->Location = System::Drawing::Point(675, rowY);
                bEdit->Size = System::Drawing::Size(50, 26);
                bEdit->BackColor = Color::FromArgb(52, 152, 219);
                bEdit->ForeColor = Color::White;
                bEdit->FlatStyle = FlatStyle::Flat;
                bEdit->FlatAppearance->BorderSize = 0;
                bEdit->Cursor = Cursors::Hand;
                bEdit->Click += gcnew EventHandler(
                    this, &AdminForm::btnEdit_Click);
                grpUsers->Controls->Add(bEdit);

                Button^ bDel = gcnew Button();
                bDel->Text = L"Удал.";
                bDel->Location = System::Drawing::Point(730, rowY);
                bDel->Size = System::Drawing::Size(55, 26);
                bDel->BackColor = Color::FromArgb(231, 76, 60);
                bDel->ForeColor = Color::White;
                bDel->FlatStyle = FlatStyle::Flat;
                bDel->FlatAppearance->BorderSize = 0;
                bDel->Cursor = Cursors::Hand;
                bDel->Click += gcnew EventHandler(
                    this, &AdminForm::btnDelete_Click);
                grpUsers->Controls->Add(bDel);

                rowY += 31;
            }

            // ===== ФОРМИРОВАНИЕ ОТЧЁТОВ =====
            grpReports = gcnew GroupBox();
            grpReports->Text = L"  ФОРМИРОВАНИЕ ОТЧЁТОВ";
            grpReports->Font = gcnew System::Drawing::Font(
                L"Segoe UI", 10.0f, FontStyle::Bold);
            grpReports->ForeColor = Color::FromArgb(52, 73, 94);
            grpReports->Location = System::Drawing::Point(10, 260);
            grpReports->Size = System::Drawing::Size(815, 185);
            grpReports->BackColor = Color::White;
            panelContent->Controls->Add(grpReports);

            lblReportType = gcnew Label();
            lblReportType->Text = L"Тип отчёта:";
            lblReportType->Font = gcnew System::Drawing::Font(
                L"Segoe UI", 9.0f, FontStyle::Bold);
            lblReportType->Location = System::Drawing::Point(15, 35);
            lblReportType->AutoSize = true;
            grpReports->Controls->Add(lblReportType);

            cmbReportType = gcnew ComboBox();
            cmbReportType->Location = System::Drawing::Point(110, 32);
            cmbReportType->Size = System::Drawing::Size(250, 26);
            cmbReportType->DropDownStyle = ComboBoxStyle::DropDownList;
            cmbReportType->Items->Add(L"Отчёт по заселённости");
            cmbReportType->Items->Add(L"Отчёт по задолженностям");
            cmbReportType->Items->Add(L"Отчёт по заявкам");
            cmbReportType->Items->Add(L"Отчёт по персоналу");
            cmbReportType->SelectedIndex = 0;
            grpReports->Controls->Add(cmbReportType);

            lblPeriodFrom = gcnew Label();
            lblPeriodFrom->Text = L"Период с:";
            lblPeriodFrom->Font = gcnew System::Drawing::Font(
                L"Segoe UI", 9.0f, FontStyle::Bold);
            lblPeriodFrom->Location = System::Drawing::Point(15, 75);
            lblPeriodFrom->AutoSize = true;
            grpReports->Controls->Add(lblPeriodFrom);

            dtFrom = gcnew DateTimePicker();
            dtFrom->Location = System::Drawing::Point(95, 72);
            dtFrom->Size = System::Drawing::Size(140, 26);
            dtFrom->Format = DateTimePickerFormat::Short;
            dtFrom->Value = System::DateTime(2025, 6, 1);
            grpReports->Controls->Add(dtFrom);

            lblPeriodTo = gcnew Label();
            lblPeriodTo->Text = L"по:";
            lblPeriodTo->Font = gcnew System::Drawing::Font(
                L"Segoe UI", 9.0f, FontStyle::Bold);
            lblPeriodTo->Location = System::Drawing::Point(245, 75);
            lblPeriodTo->AutoSize = true;
            grpReports->Controls->Add(lblPeriodTo);

            dtTo = gcnew DateTimePicker();
            dtTo->Location = System::Drawing::Point(270, 72);
            dtTo->Size = System::Drawing::Size(140, 26);
            dtTo->Format = DateTimePickerFormat::Short;
            dtTo->Value = System::DateTime(2025, 6, 30);
            grpReports->Controls->Add(dtTo);

            btnGenerate = gcnew Button();
            btnGenerate->Text = L"Сформировать";
            btnGenerate->Location = System::Drawing::Point(15, 112);
            btnGenerate->Size = System::Drawing::Size(150, 32);
            btnGenerate->BackColor = Color::FromArgb(52, 152, 219);
            btnGenerate->ForeColor = Color::White;
            btnGenerate->Font = gcnew System::Drawing::Font(
                L"Segoe UI", 9.5f, FontStyle::Bold);
            btnGenerate->FlatStyle = FlatStyle::Flat;
            btnGenerate->FlatAppearance->BorderSize = 0;
            btnGenerate->Cursor = Cursors::Hand;
            btnGenerate->Click += gcnew EventHandler(
                this, &AdminForm::btnGenerate_Click);
            grpReports->Controls->Add(btnGenerate);

            btnExport = gcnew Button();
            btnExport->Text = L"Экспорт в Excel";
            btnExport->Location = System::Drawing::Point(175, 112);
            btnExport->Size = System::Drawing::Size(150, 32);
            btnExport->BackColor = Color::FromArgb(39, 174, 96);
            btnExport->ForeColor = Color::White;
            btnExport->Font = gcnew System::Drawing::Font(
                L"Segoe UI", 9.5f, FontStyle::Bold);
            btnExport->FlatStyle = FlatStyle::Flat;
            btnExport->FlatAppearance->BorderSize = 0;
            btnExport->Cursor = Cursors::Hand;
            btnExport->Click += gcnew EventHandler(
                this, &AdminForm::btnExport_Click);
            grpReports->Controls->Add(btnExport);

            lblReportResult = gcnew Label();
            lblReportResult->Text = L"";
            lblReportResult->Font = gcnew System::Drawing::Font(
                L"Segoe UI", 9.0f, FontStyle::Bold);
            lblReportResult->ForeColor = Color::FromArgb(52, 73, 94);
            lblReportResult->Location = System::Drawing::Point(15, 152);
            lblReportResult->Size = System::Drawing::Size(790, 22);
            grpReports->Controls->Add(lblReportResult);
        }

        void AddUserRow(ListView^ lv, String^ id, String^ name,
            String^ email, String^ role, String^ status)
        {
            ListViewItem^ item = gcnew ListViewItem(id);
            item->SubItems->Add(name);
            item->SubItems->Add(email);
            item->SubItems->Add(role);
            item->SubItems->Add(status);
            item->SubItems->Add(L"Изм. | Удал.");
            lv->Items->Add(item);
        }

        // ===== ОБРАБОТЧИКИ =====
        void btnAddUser_Click(Object^ sender, EventArgs^ e)
        {
            MessageBox::Show(
                L"Откроется форма добавления нового пользователя.",
                L"Добавление",
                MessageBoxButtons::OK,
                MessageBoxIcon::Information);
        }

        void btnEdit_Click(Object^ sender, EventArgs^ e)
        {
            MessageBox::Show(
                L"Откроется форма редактирования пользователя.",
                L"Редактирование",
                MessageBoxButtons::OK,
                MessageBoxIcon::Information);
        }

        void btnDelete_Click(Object^ sender, EventArgs^ e)
        {
            System::Windows::Forms::DialogResult res =
                MessageBox::Show(
                    L"Удалить пользователя?",
                    L"Подтверждение",
                    MessageBoxButtons::YesNo,
                    MessageBoxIcon::Question);

            if (res == System::Windows::Forms::DialogResult::Yes)
                MessageBox::Show(
                    L"Пользователь удалён.",
                    L"Удаление",
                    MessageBoxButtons::OK,
                    MessageBoxIcon::Information);
        }

        void btnGenerate_Click(Object^ sender, EventArgs^ e)
        {
            String^ type = cmbReportType->SelectedItem->ToString();
            String^ from = dtFrom->Value.ToString(L"dd.MM.yyyy");
            String^ to = dtTo->Value.ToString(L"dd.MM.yyyy");

            lblReportResult->Text =
                L"Результат: Всего комнат: 120 | Занято: 108 | "
                L"Свободно: 12 | Заселённость: 90%  ("
                + type + L", " + from + L" — " + to + L")";
        }

        void btnExport_Click(Object^ sender, EventArgs^ e)
        {
            MessageBox::Show(
                L"Отчёт экспортирован в файл:\n"
                L"C:\\Reports\\report_"
                + System::DateTime::Now.ToString(L"yyyyMMdd") + L".xlsx",
                L"Экспорт",
                MessageBoxButtons::OK,
                MessageBoxIcon::Information);
        }

        void btnLogout_Click(Object^ sender, EventArgs^ e)
        {
            System::Windows::Forms::DialogResult res =
                MessageBox::Show(
                    L"Выйти из системы?",
                    L"Выход",
                    MessageBoxButtons::YesNo,
                    MessageBoxIcon::Question);

            if (res == System::Windows::Forms::DialogResult::Yes)
                this->Close();
        }
    };
}