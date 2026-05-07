#pragma once

namespace APRSO {

    using namespace System;
    using namespace System::Windows::Forms;
    using namespace System::Drawing;

    public ref class KomendantForm : public System::Windows::Forms::Form
    {
    public:
        String^ currentUser;

        KomendantForm(String^ username)
        {
            currentUser = username;
            InitializeComponent();
        }

    protected:
        ~KomendantForm() { if (components) delete components; }

    private:
        System::ComponentModel::Container^ components;

        Panel^ panelTop;
        Label^ lblHeader;
        Button^ btnLogout;
        Panel^ panelMenu;
        Panel^ panelContent;

        // Счётчики
        Panel^ panelCounters;
        Panel^ pNew;
        Panel^ pWork;
        Panel^ pFree;

        // Список заявок
        GroupBox^ grpApps;
        ComboBox^ cmbFilter;
        ComboBox^ cmbCategory;
        TextBox^ txtSearch;
        ListView^ lvApps;

        // Панель обработки заявки
        GroupBox^ grpProcess;
        Label^ lblAppInfo;
        Label^ lblAppDesc;
        Label^ lblAssign;
        ComboBox^ cmbAssign;
        Button^ btnAssign;
        Button^ btnReject;
        Button^ btnClose;

    private:
        void InitializeComponent(void)
        {
            this->SuspendLayout();

            this->Text = L"Рабочий стол коменданта — АПРСО";
            this->Size = System::Drawing::Size(1050, 720);
            this->StartPosition = FormStartPosition::CenterScreen;
            this->BackColor = Color::FromArgb(245, 245, 245);
            this->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0f);

            // ===== ШАПКА =====
            panelTop = gcnew Panel();
            panelTop->Dock = DockStyle::Top;
            panelTop->Height = 45;
            panelTop->BackColor = Color::FromArgb(52, 73, 94);

            lblHeader = gcnew Label();
            lblHeader->Text = L"ИС Студенческого общежития  |  Комендант: " + currentUser;
            lblHeader->ForeColor = Color::White;
            lblHeader->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.5f);
            lblHeader->Location = System::Drawing::Point(10, 0);
            lblHeader->Size = System::Drawing::Size(750, 45);
            lblHeader->TextAlign = ContentAlignment::MiddleLeft;
            panelTop->Controls->Add(lblHeader);

            btnLogout = gcnew Button();
            btnLogout->Text = L"Выход";
            btnLogout->Location = System::Drawing::Point(950, 8);
            btnLogout->Size = System::Drawing::Size(70, 28);
            btnLogout->BackColor = Color::FromArgb(192, 57, 43);
            btnLogout->ForeColor = Color::White;
            btnLogout->FlatStyle = FlatStyle::Flat;
            btnLogout->FlatAppearance->BorderSize = 0;
            btnLogout->Cursor = Cursors::Hand;
            btnLogout->Click += gcnew EventHandler(this, &KomendantForm::btnLogout_Click);
            panelTop->Controls->Add(btnLogout);
            this->Controls->Add(panelTop);

            // ===== ЛЕВОЕ МЕНЮ =====
            panelMenu = gcnew Panel();
            panelMenu->Location = System::Drawing::Point(0, 45);
            panelMenu->Size = System::Drawing::Size(150, 675);
            panelMenu->BackColor = Color::FromArgb(44, 62, 80);

            // ВСТАВИТЬ ЭТО:
            array<String^>^ menuItems = gcnew array<String^>(5);
            menuItems[0] = L"Заявки";
            menuItems[1] = L"Студенты";
            menuItems[2] = L"Комнаты";
            menuItems[3] = L"Оплаты";
            menuItems[4] = L"Заселение/Выселение";

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
            panelContent->Size = System::Drawing::Size(890, 675);
            panelContent->AutoScroll = true;
            this->Controls->Add(panelContent);

            BuildContent();
            this->ResumeLayout(false);
        }

        void BuildContent()
        {
            panelContent->Controls->Clear();

            // ===== СЧЁТЧИКИ =====
            panelCounters = gcnew Panel();
            panelCounters->Location = System::Drawing::Point(10, 8);
            panelCounters->Size = System::Drawing::Size(865, 70);
            panelCounters->BackColor = Color::Transparent;
            panelContent->Controls->Add(panelCounters);

            CreateCounter(panelCounters, 0, L"5", L"Новых заявок", Color::FromArgb(231, 76, 60));
            CreateCounter(panelCounters, 300, L"8", L"В работе", Color::FromArgb(243, 156, 18));
            CreateCounter(panelCounters, 600, L"12", L"Свободных комнат", Color::FromArgb(39, 174, 96));

            // ===== СПИСОК ЗАЯВОК =====
            grpApps = gcnew GroupBox();
            grpApps->Text = L"  СПИСОК ЗАЯВОК";
            grpApps->Font = gcnew System::Drawing::Font(L"Segoe UI", 10.0f, FontStyle::Bold);
            grpApps->ForeColor = Color::FromArgb(52, 73, 94);
            grpApps->Location = System::Drawing::Point(10, 85);
            grpApps->Size = System::Drawing::Size(865, 260);
            grpApps->BackColor = Color::White;
            panelContent->Controls->Add(grpApps);

            // Фильтры
            cmbFilter = gcnew ComboBox();
            cmbFilter->Location = System::Drawing::Point(10, 28);
            cmbFilter->Size = System::Drawing::Size(100, 26);
            cmbFilter->DropDownStyle = ComboBoxStyle::DropDownList;
            cmbFilter->Items->Add(L"Все");
            cmbFilter->Items->Add(L"Новые");
            cmbFilter->Items->Add(L"В работе");
            cmbFilter->Items->Add(L"Закрытые");
            cmbFilter->SelectedIndex = 0;
            grpApps->Controls->Add(cmbFilter);

            cmbCategory = gcnew ComboBox();
            cmbCategory->Location = System::Drawing::Point(120, 28);
            cmbCategory->Size = System::Drawing::Size(130, 26);
            cmbCategory->DropDownStyle = ComboBoxStyle::DropDownList;
            cmbCategory->Items->Add(L"Категория");
            cmbCategory->Items->Add(L"Ремонт");
            cmbCategory->Items->Add(L"Адм. вопрос");
            cmbCategory->Items->Add(L"Оплата");
            cmbCategory->SelectedIndex = 0;
            grpApps->Controls->Add(cmbCategory);

            txtSearch = gcnew TextBox();
            txtSearch->Location = System::Drawing::Point(260, 28);
            txtSearch->Size = System::Drawing::Size(200, 26);
            // ВСТАВИТЬ ЭТО:
            txtSearch->Text = L"Поиск...";
            txtSearch->ForeColor = Color::Gray;
            grpApps->Controls->Add(txtSearch);

            // ListView заявок
            lvApps = gcnew ListView();
            lvApps->Location = System::Drawing::Point(10, 62);
            lvApps->Size = System::Drawing::Size(840, 188);
            lvApps->View = View::Details;
            lvApps->FullRowSelect = true;
            lvApps->GridLines = true;
            lvApps->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0f);
            lvApps->ItemSelectionChanged +=
                gcnew ListViewItemSelectionChangedEventHandler(
                    this, &KomendantForm::lvApps_SelectionChanged);

            lvApps->Columns->Add(L"№", 45);
            lvApps->Columns->Add(L"Студент", 130);
            lvApps->Columns->Add(L"Ком.", 45);
            lvApps->Columns->Add(L"Тема", 200);
            lvApps->Columns->Add(L"Категория", 100);
            lvApps->Columns->Add(L"Приоритет", 80);
            lvApps->Columns->Add(L"Статус", 90);
            lvApps->Columns->Add(L"Исполнитель", 95);

            AddKomRow(lvApps, L"201", L"Иванов С.", L"214",
                L"Не работает кран", L"Ремонт", L"Высокий", L"В работе", L"Смирнов");
            AddKomRow(lvApps, L"202", L"Козлова М.", L"301",
                L"Замена замка", L"Ремонт", L"Средний", L"Новая", L"—");
            AddKomRow(lvApps, L"199", L"Петров А.", L"115",
                L"Справка", L"Адм. вопрос", L"Низкий", L"Закрыта", L"Петрова");

            // Окраска строк
            lvApps->Items[0]->ForeColor = Color::FromArgb(41, 128, 185);
            lvApps->Items[1]->ForeColor = Color::FromArgb(243, 156, 18);
            lvApps->Items[2]->ForeColor = Color::FromArgb(39, 174, 96);

            grpApps->Controls->Add(lvApps);

            // Кнопки строк (Открыть/Назначить)
            Button^ btnOpen201 = CreateRowBtn(L"Открыть", 750, 62);
            btnOpen201->Click += gcnew EventHandler(this, &KomendantForm::btnOpen_Click);
            grpApps->Controls->Add(btnOpen201);

            Button^ btnAssign202 = CreateRowBtn(L"Назначить", 750, 93);
            btnAssign202->Click += gcnew EventHandler(this, &KomendantForm::btnAssignRow_Click);
            grpApps->Controls->Add(btnAssign202);

            Button^ btnOpen199 = CreateRowBtn(L"Открыть", 750, 124);
            btnOpen199->Click += gcnew EventHandler(this, &KomendantForm::btnOpen_Click);
            grpApps->Controls->Add(btnOpen199);

            // ===== ПАНЕЛЬ ОБРАБОТКИ =====
            grpProcess = gcnew GroupBox();
            grpProcess->Text = L"  ОБРАБОТКА ЗАЯВКИ №201";
            grpProcess->Font = gcnew System::Drawing::Font(L"Segoe UI", 10.0f, FontStyle::Bold);
            grpProcess->ForeColor = Color::FromArgb(52, 73, 94);
            grpProcess->Location = System::Drawing::Point(10, 355);
            grpProcess->Size = System::Drawing::Size(865, 160);
            grpProcess->BackColor = Color::White;
            panelContent->Controls->Add(grpProcess);

            lblAppInfo = gcnew Label();
            lblAppInfo->Text =
                L"Студент: Иванов С.А.  |  Комната: 214  |  Дата: 12.06.2025  "
                L"|  Категория: Ремонт  |  Приоритет: Высокий";
            lblAppInfo->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0f, FontStyle::Bold);
            lblAppInfo->Location = System::Drawing::Point(15, 28);
            lblAppInfo->Size = System::Drawing::Size(830, 22);
            grpProcess->Controls->Add(lblAppInfo);

            lblAppDesc = gcnew Label();
            lblAppDesc->Text =
                L"Описание: Не работает кран в комнате 214, постоянно течёт горячая вода. "
                L"Прошу устранить.";
            lblAppDesc->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0f);
            lblAppDesc->Location = System::Drawing::Point(15, 53);
            lblAppDesc->Size = System::Drawing::Size(830, 22);
            grpProcess->Controls->Add(lblAppDesc);

            lblAssign = gcnew Label();
            lblAssign->Text = L"Назначить исполнителя:";
            lblAssign->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0f, FontStyle::Bold);
            lblAssign->Location = System::Drawing::Point(15, 85);
            lblAssign->AutoSize = true;
            grpProcess->Controls->Add(lblAssign);

            cmbAssign = gcnew ComboBox();
            cmbAssign->Location = System::Drawing::Point(175, 83);
            cmbAssign->Size = System::Drawing::Size(250, 26);
            cmbAssign->DropDownStyle = ComboBoxStyle::DropDownList;
            cmbAssign->Items->Add(L"Смирнов П.В. (сантехник)");
            cmbAssign->Items->Add(L"Орлов Д.С. (электрик)");
            cmbAssign->Items->Add(L"Фёдоров А.Н. (слесарь)");
            cmbAssign->SelectedIndex = 0;
            grpProcess->Controls->Add(cmbAssign);

            // Кнопки действий
            int btnY = 118;

            Button^ bAssign = CreateActionBtn(L"Назначить", 15, btnY, Color::FromArgb(52, 152, 219));
            Button^ bReject = CreateActionBtn(L"Отклонить", 130, btnY, Color::FromArgb(231, 76, 60));
            Button^ bClose = CreateActionBtn(L"Закрыть", 250, btnY, Color::FromArgb(39, 174, 96));

            bAssign->Click += gcnew EventHandler(this, &KomendantForm::btnDoAssign_Click);
            bReject->Click += gcnew EventHandler(this, &KomendantForm::btnDoReject_Click);
            bClose->Click += gcnew EventHandler(this, &KomendantForm::btnDoClose_Click);

            grpProcess->Controls->Add(bAssign);
            grpProcess->Controls->Add(bReject);
            grpProcess->Controls->Add(bClose);
        }

        // ===== ВСПОМОГАТЕЛЬНЫЕ МЕТОДЫ =====

        void CreateCounter(Panel^ parent, int x, String^ value,
            String^ label, Color color)
        {
            Panel^ p = gcnew Panel();
            p->Location = System::Drawing::Point(x, 0);
            p->Size = System::Drawing::Size(280, 65);
            p->BackColor = color;

            Label^ lVal = gcnew Label();
            lVal->Text = value;
            lVal->Font = gcnew System::Drawing::Font(L"Segoe UI", 22.0f, FontStyle::Bold);
            lVal->ForeColor = Color::White;
            lVal->Location = System::Drawing::Point(15, 5);
            lVal->AutoSize = true;
            p->Controls->Add(lVal);

            Label^ lLbl = gcnew Label();
            lLbl->Text = label;
            lLbl->Font = gcnew System::Drawing::Font(L"Segoe UI", 10.0f);
            lLbl->ForeColor = Color::White;
            lLbl->Location = System::Drawing::Point(70, 18);
            lLbl->AutoSize = true;
            p->Controls->Add(lLbl);

            parent->Controls->Add(p);
        }

        void AddKomRow(ListView^ lv, String^ num, String^ student,
            String^ room, String^ tema, String^ cat,
            String^ prior, String^ status, String^ exec)
        {
            ListViewItem^ item = gcnew ListViewItem(num);
            item->SubItems->Add(student);
            item->SubItems->Add(room);
            item->SubItems->Add(tema);
            item->SubItems->Add(cat);
            item->SubItems->Add(prior);
            item->SubItems->Add(status);
            item->SubItems->Add(exec);
            lv->Items->Add(item);
        }

        Button^ CreateRowBtn(String^ text, int x, int y)
        {
            Button^ btn = gcnew Button();
            btn->Text = text;
            btn->Location = System::Drawing::Point(x, y);
            btn->Size = System::Drawing::Size(80, 26);
            btn->BackColor = Color::FromArgb(52, 73, 94);
            btn->ForeColor = Color::White;
            btn->FlatStyle = FlatStyle::Flat;
            btn->FlatAppearance->BorderSize = 0;
            btn->Cursor = Cursors::Hand;
            return btn;
        }

        Button^ CreateActionBtn(String^ text, int x, int y, Color color)
        {
            Button^ btn = gcnew Button();
            btn->Text = text;
            btn->Location = System::Drawing::Point(x, y);
            btn->Size = System::Drawing::Size(100, 30);
            btn->BackColor = color;
            btn->ForeColor = Color::White;
            btn->FlatStyle = FlatStyle::Flat;
            btn->FlatAppearance->BorderSize = 0;
            btn->Font = gcnew System::Drawing::Font(L"Segoe UI", 9.0f, FontStyle::Bold);
            btn->Cursor = Cursors::Hand;
            return btn;
        }

        // ===== ОБРАБОТЧИКИ =====
        void lvApps_SelectionChanged(Object^ sender,
            ListViewItemSelectionChangedEventArgs^ e) {
        }

        void btnOpen_Click(Object^ sender, EventArgs^ e)
        {
            MessageBox::Show(L"Карточка заявки открыта для просмотра.",
                L"Заявка", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }

        void btnAssignRow_Click(Object^ sender, EventArgs^ e)
        {
            grpProcess->Text = L"  ОБРАБОТКА ЗАЯВКИ №202";
            MessageBox::Show(L"Заявка №202 открыта для назначения исполнителя.",
                L"Назначение", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }

        void btnDoAssign_Click(Object^ sender, EventArgs^ e)
        {
            String^ exec = cmbAssign->SelectedItem->ToString();
            MessageBox::Show(
                L"Исполнитель назначен: " + exec +
                L"\nСтатус заявки изменён на «Назначена».\nИсполнитель уведомлён.",
                L"Назначение", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }

        void btnDoReject_Click(Object^ sender, EventArgs^ e)
        {
            if (MessageBox::Show(L"Отклонить заявку?", L"Подтверждение",
                MessageBoxButtons::YesNo, MessageBoxIcon::Question)
                == System::Windows::Forms::DialogResult::Yes)
                MessageBox::Show(L"Заявка отклонена.", L"Статус",
                    MessageBoxButtons::OK, MessageBoxIcon::Information);
        }

        void btnDoClose_Click(Object^ sender, EventArgs^ e)
        {
            if (MessageBox::Show(L"Закрыть заявку? Студент получит уведомление.",
                L"Подтверждение", MessageBoxButtons::YesNo, MessageBoxIcon::Question)
                == System::Windows::Forms::DialogResult::Yes)
                MessageBox::Show(L"Заявка закрыта. Статус: «Закрыта».",
                    L"Статус", MessageBoxButtons::OK, MessageBoxIcon::Information);
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