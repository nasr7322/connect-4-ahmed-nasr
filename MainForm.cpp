#include "MainForm.h"
#include "GameForm.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]

void main(array<String^>^ args) {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Guimain::MainForm form;
	Application::Run(%form);
}

