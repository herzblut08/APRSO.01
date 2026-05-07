#pragma once

namespace APRSO {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class TechForm : public System::Windows::Forms::Form
    {
    public:
        String^ currentUser;

        TechForm(String^ username)
        {
            currentUser = username;
            InitializeComponent();
        }

    protected:
        ~TechForm() { if (components) delete components; }

    private:
        System::ComponentModel::Container^ components;

        Panel^ panelTop;
        Label^ lblHeader;
        Button^ btnLogout;
        Panel^ panelContent;

        GroupBox^ grpMyApps;
        ListView^ lvMyApps;

        GroupBox^ grpDone;
        Label^ lblDoneInfo;
        TextBox^ txtDoneDesc;
        Button^ btnMarkDone;

    private:
        void InitializeComponent(void)
        {
            this->SuspendLayout();

            this->Text = L"Рабочий стол технического сотрудника — АПРСО";
            this->Size = System::Drawing::Size(860, 620);
            this->StartPosition = FormStartPosition::CenterScreen;
            this->BackColor = Color::FromArgb(245, 245, 245);
            this->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0f);

            // ===== ШАПКА =====
            panelTop = gcnew Panel();
            panelTop->Dock = DockStyle::Top;
            panelTop->Height = 45;
            panelTop->BackColor = Color::FromArgb(52, 73, 94);

            lblHeader = gcnew Label();
            lblHeader->Text = L"ИС Студенческого общежития  |  "
                + currentUser + L"  (технический сотрудник)";
            lblHeader->ForeColor = Color::White;
            lblHeader->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5f);
            lblHeader->Location = System::Drawing::Point(10, 0);
            lblHeader->Size = System::Drawing::Size(700, 45);
            lblHeader->TextAlign = ContentAlignment::MiddleLeft;
            panelTop->Controls->Add(lblHeader);

            btnLogout = gcnew Button();
            btnLogout->Text = L"Выход";
            btnLogout->Location = System::Drawing::Point(760, 8);
            btnLogout->Size = System::Drawing::Size(70, 28);
            btnLogout->BackColor = Color::FromArgb(192, 57, 43);
            btnLogout->ForeColor = Color::White;
            btnLogout->FlatStyle = FlatStyle::Flat;
            btnLogout->FlatAppearance->BorderSize = 0;
            btnLogout->Cursor = Cursors::Hand;
            btnLogout->Click += gcnew EventHandler(this, &TechForm::btnLogout_Click);
            panelTop->Controls->Add(btnLogout);
            this->Controls->Add(panelTop);

            // ===== КОНТЕНТ =====
            panelContent = gcnew Panel();
            panelContent->Location = System::Drawing::Point(0, 45);
            panelContent->Size = System::Drawing::Size(860, 575);
            panelContent->AutoScroll = true;
            this->Controls->Add(panelContent);

            BuildContent();
            this->ResumeLayout(false);
        }

        void BuildContent()
        {
            panelContent->Controls->Clear();

            // ===== МОИ НАЗНАЧЕННЫЕ ЗАЯВКИ =====
            grpMyApps = gcnew GroupBox();
            grpMyApps->Text = L"  МОИ НАЗНАЧЕННЫЕ ЗАЯВКИ";
            grpMyApps->Font = gcnew System::Drawing::Font(L"Segoe UI", 10.0f, FontStyle::Bold);
            grpMyApps->ForeColor = Color::FromArgb(52, 73, 94);
            grpMyApps->Location = System::Drawing::Point(15, 10);
            grpMyApps->Size = System::Drawing::Size(820, 220);
            grpMyApps->BackColor = Color::White;
            panelContent->Controls->Add(grpMyApps);

            lvMyApps = gcnew ListView();
            lvMyApps->Location = System::Drawing::Point(10, 28);
            lvMyApps->Size = System::Drawing::Size(700, 178);
            lvMyApps->View = View::Details;
            lvMyApps->FullRowSelect = true;
            lvMyApps->GridLines = true;
            lvMyApps->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0f);

            lvMyApps->Columns->Add(L"№", 50);
            lvMyApps->Columns->Add(L"Ком.", 50);
            lvMyApps->Columns->Add(L"Тема", 220);
            lvMyApps->Columns->Add(L"Категория", 100);
            lvMyApps->Columns->Add(L"Приоритет", 80);
            lvMyApps->Columns->Add(L"Статус", 100);
            lvMyApps->Columns->Add(L"Дата назначения", 110);

            AddTechRow(lvMyApps, L"201", L"214", L"Не работает кран",
                L"Ремонт", L"Высокий", L"В работе", L"12.06.2025");
            AddTechRow(lvMyApps, L"203", L"118", L"Перегорела лампа",
                L"Ремонт", L"Низкий", L"Назначена", L"13.06.2025");

            lvMyApps->Items[0]->ForeColor = Color::FromArgb(41, 128, 185);
            lvMyApps->Items[1]->ForeColor = Color::FromArgb(243, 156, 18);

            grpMyApps->Controls->Add(lvMyApps);

            // Кнопки «Выполнено»
            Button^ btn201 = CreateDoneBtn(725, 28);
            btn201->Click += gcnew EventHandler(this, &TechForm::btnDone201_Click);
            grpMyApps->Controls->Add(btn201);

            Button^ btn203 = CreateDoneBtn(725, 62);
            btn203->Click += gcnew EventHandler(this, &TechForm::btnDone203_Click);
            grpMyApps->Controls->Add(btn203);

            // ===== ОТМЕТИТЬ ВЫПОЛНЕНИЕ =====
            grpDone = gcnew GroupBox();
            grpDone->Text = L"  ОТМЕТИТЬ ВЫПОЛНЕНИЕ — ЗАЯВКА №201";
            grpDone->Font = gcnew System::Drawing::Font(L"Segoe UI", 10.0f, FontStyle::Bold);
            grpDone->ForeColor = Color::FromArgb(52, 73, 94);
            grpDone->Location = System::Drawing::Point(15, 240);
            grpDone->Size = System::Drawing::Size(820, 185);
            grpDone->BackColor = Color::White;
            panelContent->Controls->Add(grpDone);

            Label^ lblInfo = gcnew Label();
            lblInfo->Text = L"Комната: 214  |  Тема: Не работает кран  |  Приоритет: Высокий";
            lblInfo->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0f, FontStyle::Bold);
            lblInfo->Location = System::Drawing::Point(15, 28);
            lblInfo->Size = System::Drawing::Size(780, 22);
            grpDone->Controls->Add(lblInfo);

            Label^ lblDescLbl = gcnew Label();
            lblDescLbl->Text = L"Описание выполненных работ:";
            lblDescLbl->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0f, FontStyle::Bold);
            lblDescLbl->Location = System::Drawing::Point(15, 58);
            lblDescLbl->AutoSize = true;
            grpDone->Controls->Add(lblDescLbl);

            txtDoneDesc = gcnew TextBox();
            txtDoneDesc->Location = System::Drawing::Point(15, 80);
            txtDoneDesc->Size = System::Drawing::Size(785, 60);
            txtDoneDesc->Multiline = true;
            txtDoneDesc->Text = L"Заменил прокладку в кране. Течь устранена. Работа выполнена.";
            txtDoneDesc->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
            grpDone->Controls->Add(txtDoneDesc);

            btnMarkDone = gcnew Button();
            btnMarkDone->Text = L"Отметить как выполненное";
            btnMarkDone->Location = System::Drawing::Point(270, 148);
            btnMarkDone->Size = System::Drawing::Size(260, 30);
            btnMarkDone->BackColor = Color::FromArgb(39, 174, 96);
            btnMarkDone->ForeColor = Color::White;
            btnMarkDone->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5f, FontStyle::Bold);
            btnMarkDone->FlatStyle = FlatStyle::Flat;
            btnMarkDone->FlatAppearance->BorderSize = 0;
            btnMarkDone->Cursor = Cursors::Hand;
            btnMarkDone->Click += gcnew EventHandler(this, &TechForm::btnMarkDone_Click);
            grpDone->Controls->Add(btnMarkDone);
        }

        void AddTechRow(ListView^ lv, String^ num, String^ room,
            String^ tema, String^ cat, String^ prior,
            String^ status, String^ date)
        {
            ListViewItem^ item = gcnew ListViewItem(num);
            item->SubItems->Add(room);
            item->SubItems->Add(tema);
            item->SubItems->Add(cat);
            item->SubItems->Add(prior);
            item->SubItems->Add(status);
            item->SubItems->Add(date);
            lv->Items->Add(item);
        }

        Button^ CreateDoneBtn(int x, int y)
        {
            Button^ btn = gcnew Button();
            btn->Text = L"Выполнено";
            btn->Location = System::Drawing::Point(x, y);
            btn->Size = System::Drawing::Size(85, 26);
            btn->BackColor = Color::FromArgb(39, 174, 96);
            btn->ForeColor = Color::White;
            btn->FlatStyle = FlatStyle::Flat;
            btn->FlatAppearance->BorderSize = 0;
            btn->Cursor = Cursors::Hand;
            return btn;
        }

        // ===== ОБРАБОТЧИКИ =====
        void btnDone201_Click(Object^ sender, EventArgs^ e)
        {
            grpDone->Text = L"  ОТМЕТИТЬ ВЫПОЛНЕНИЕ — ЗАЯВКА №201";
        }

        void btnDone203_Click(Object^ sender, EventArgs^ e)
        {
            grpDone->Text = L"  ОТМЕТИТЬ ВЫПОЛНЕНИЕ — ЗАЯВКА №203";
        }

        void btnMarkDone_Click(Object^ sender, EventArgs^ e)
        {
            if (txtDoneDesc->Text->Trim() == L"")
            {
                MessageBox::Show(L"Введите описание выполненных работ.",
                    L"Ошибка", MessageBoxButtons::OK, MessageBoxIcon::Warning);
                return;
            }
            MessageBox::Show(
                L"Статус заявки изменён на «Ожидает подтверждения».\n"
                L"Комендант уведомлён.",
                L"Выполнено", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }

        void btnLogout_Click(Object^ sender, EventArgs^ e)
        {
            if (MessageBox::Show(L"Выйти из системы?", L"Выход",
                MessageBoxButtons::YesNo, MessageBoxIcon::Question)
                == System::Windows::Forms::DialogResult::Yes)
                this->Close();
        }
    };
}