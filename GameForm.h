#pragma once
#include "structures.h"

namespace Guimain {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class GameForm : public System::Windows::Forms::Form
	{
	public:

		void PrintBoard(int h, int w, Board fboard) {
			Button^ button;
			for (int i = 0; i < h; i++) {
				for (int j = 0; j < w; j++) {
					button = gcnew System::Windows::Forms::Button;
					button->Height = 400 / h;
					button->Width = 400 / w;
					button->Left = 50 + (j * (button->Width));
					button->Top = 50 + (i * (button->Height));
					button->Text = i + "" + j;
					if (fboard.board[i][j] == 0) { button->Text = "red"; }
					Controls->Add(button);
				}
			}
		}

		GameForm(int h, int w)
		{
			InitializeComponent();
			Board board{};
			board.height = h;
			board.width = w;
			PrintBoard(board.height, board.width, board);
		}
		
	protected:
		~GameForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ main_menu;
	protected:

	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->main_menu = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// main_menu
			// 
			this->main_menu->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->main_menu->Location = System::Drawing::Point(200, 465);
			this->main_menu->Name = L"main_menu";
			this->main_menu->Size = System::Drawing::Size(100, 25);
			this->main_menu->TabIndex = 0;
			this->main_menu->Text = L"Main Menu";
			this->main_menu->UseVisualStyleBackColor = true;
			this->main_menu->Click += gcnew System::EventHandler(this, &GameForm::main_menu_Click);
			// 
			// GameForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(500, 500);
			this->Controls->Add(this->main_menu);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"GameForm";
			this->Text = L"GameForm";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void main_menu_Click(System::Object^ sender, System::EventArgs^ e) {
		GameForm::Visible = false;
	}
	};
}
