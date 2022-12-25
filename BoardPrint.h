#pragma once


using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

void PrintBoard(int h, int w) {
	Button^ button;
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			button = gcnew System::Windows::Forms::Button;
			button->Height = 400 / h;
			button->Width = 400 / w;
			button->Left = 50 + (i * (button->Width));
			button->Top = 50 + (j * (button->Height));
			button->Text = i + "" + j;
			Controls->Add(button);
		}
	}
}