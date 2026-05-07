#using <System.dll>
#using <System.Windows.Forms.dll>
#using <System.Drawing.dll>

#include "LoginForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<System::String^>^ args)
{
    Application::EnableVisualStyles();
    Application::SetCompatibleTextRenderingDefault(false);
    Application::Run(gcnew APRSO::LoginForm());
    return 0;
}