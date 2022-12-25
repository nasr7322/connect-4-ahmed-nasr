#pragma once
#include "structures.h"



namespace Guimain {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;



	/// <summary>
	/// Summary for GameForm
	/// </summary>
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

		GameForm(void)
		{
			InitializeComponent();
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
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~GameForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->SuspendLayout();
			// 
			// GameForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(500, 500);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"GameForm";
			this->Text = L"GameForm";
			this->ResumeLayout(false);

		}
#pragma endregion
	};
}
