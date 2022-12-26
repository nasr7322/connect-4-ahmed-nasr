#pragma once
#include "structures.h"
#include "actions.h"

Board board;
Player p1;
Player p2;
int turns=0;

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
		Void button_Click(System::Object^ sender, System::EventArgs^ e) {
			Button^ clicked = (Button^) sender;
			int ret=PlayerMove(&board, (turns & 1) ? (&p2) : (&p1), System::Convert::ToInt32(clicked->Tag));
			if(!ret)
				turns++;
			Controls->Clear();
			InitializeComponent();
			PrintBoard(board.height, board.width, board);
			PrintButtons(board.width);
		}

		void PrintBoard(int h, int w, Board fboard) {
			Button^ button;
			for (int i = 0; i < h; i++) {
				for (int j = 0; j < w; j++) {
					button = gcnew System::Windows::Forms::Button;
					button->Height = 400 / h;
					button->Width = 400 / w;
					button->Left = 50 + (j * (button->Width));
					button->Top = 50 + (i * (button->Height));
					button->Enabled = false;
					button->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
					//button->Text = System::Convert::ToString(fboard.board[i][j]);
					if (fboard.board[i][j] == 1) {
						button->BackgroundImage = System::Drawing::Image::FromFile("C:\\Users\\acer\\source\\repos\\connect-4-ahmed-nasr\\ORANGE.PNG");
					}

					if (fboard.board[i][j] == 2) {
						button->BackgroundImage = System::Drawing::Image::FromFile("C:\\Users\\acer\\source\\repos\\connect-4-ahmed-nasr\\RED.PNG");
					}
					
					Controls->Add(button);
				}
			}
		}
		void PrintButtons(int w) {
			Button^ select;
			for (int i = 0; i < w; i++) {
					select = gcnew System::Windows::Forms::Button;
					select->Height = 25;
					select->Width = 400 / w;
					select->Left = 50 + (i * (select->Width));
					select->Top = 15;
					select->Tag = i;
					select->Click += gcnew EventHandler( this, &GameForm::button_Click);

					select->Text = "C" + i;
					//if (fboard.board[i][j] == 0) { button->Text = ; }
					Controls->Add(select);
			}
		}

		GameForm(int h, int w)
		{
			InitializeComponent();
			
			board.height = h;
			board.width = w;
			p1.score = p1.turns_played = 0;
			p1.id = 1;
			p2.score = p2.turns_played = 0;
			p2.id = 2;
			PrintBoard(board.height, board.width, board);
			PrintButtons(w);
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
			this->main_menu->BackColor = System::Drawing::SystemColors::Control;
			this->main_menu->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->main_menu->Location = System::Drawing::Point(350, 629);
			this->main_menu->Margin = System::Windows::Forms::Padding(4);
			this->main_menu->Name = L"main_menu";
			this->main_menu->Size = System::Drawing::Size(133, 31);
			this->main_menu->TabIndex = 0;
			this->main_menu->Text = L"Main Menu";
			this->main_menu->UseVisualStyleBackColor = false;
			this->main_menu->Click += gcnew System::EventHandler(this, &GameForm::main_menu_Click);
			// 
			// GameForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(667, 615);
			this->Controls->Add(this->main_menu);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Margin = System::Windows::Forms::Padding(4);
			this->Name = L"GameForm";
			this->Text = L"GameForm";
			this->Load += gcnew System::EventHandler(this, &GameForm::GameForm_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void main_menu_Click(System::Object^ sender, System::EventArgs^ e) {
		GameForm::Visible = false;
		
	}
	private: System::Void GameForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
};
}
