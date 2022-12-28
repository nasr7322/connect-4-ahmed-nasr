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
					button->Width = 500 / w;
					button->Left = 150 + (j * (button->Width));
					button->Top = 135 + (i * (button->Height));
					button->Enabled = false;
					button->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;

					if (fboard.board[i][j] == 1) {
						button->BackgroundImage = System::Drawing::Image::FromFile("C:\\Users\\PM\\source\\repos\\connect-4-ahmed-nasr\\ORANGE.PNG");
					}

					if (fboard.board[i][j] == 2) {
						button->BackgroundImage = System::Drawing::Image::FromFile("C:\\Users\\PM\\source\\repos\\connect-4-ahmed-nasr\\RED.PNG");
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
					select->Width = 500 / w;
					select->Left = 150 + (i * (select->Width));
					select->Top = 100;
					select->Tag = i;
					select->Click += gcnew EventHandler( this, &GameForm::button_Click);
					select->Text = i + "C";
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
	private: System::Windows::Forms::Label^ p1_label;
	private: System::Windows::Forms::Label^ p1_label_score;
	private: System::Windows::Forms::Label^ p1_label_moves;
	private: System::Windows::Forms::Label^ turns_label;
	private: System::Windows::Forms::Label^ time_label;
	private: System::Windows::Forms::Label^ p2_label_moves;
	private: System::Windows::Forms::Label^ p2_label_score;
	private: System::Windows::Forms::Label^ p2_label;
	private: System::Windows::Forms::Label^ owrname;

	protected:

	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->main_menu = (gcnew System::Windows::Forms::Button());
			this->p1_label = (gcnew System::Windows::Forms::Label());
			this->p1_label_score = (gcnew System::Windows::Forms::Label());
			this->p1_label_moves = (gcnew System::Windows::Forms::Label());
			this->turns_label = (gcnew System::Windows::Forms::Label());
			this->time_label = (gcnew System::Windows::Forms::Label());
			this->p2_label_moves = (gcnew System::Windows::Forms::Label());
			this->p2_label_score = (gcnew System::Windows::Forms::Label());
			this->p2_label = (gcnew System::Windows::Forms::Label());
			this->owrname = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// main_menu
			// 
			this->main_menu->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->main_menu->BackColor = System::Drawing::SystemColors::Control;
			this->main_menu->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;

			this->main_menu->Location = System::Drawing::Point(350, 550);

			this->main_menu->Name = L"main_menu";
			this->main_menu->Size = System::Drawing::Size(100, 25);
			this->main_menu->TabIndex = 0;
			this->main_menu->Text = L"Main Menu";
			this->main_menu->UseVisualStyleBackColor = false;
			this->main_menu->Click += gcnew System::EventHandler(this, &GameForm::main_menu_Click);
			// 
			// p1_label
			// 
			this->p1_label->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->p1_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0)));
			this->p1_label->Location = System::Drawing::Point(12, 9);
			this->p1_label->Name = L"p1_label";
			this->p1_label->Size = System::Drawing::Size(122, 37);
			this->p1_label->TabIndex = 1;
			this->p1_label->Text = L"Player1";
			// 
			// p1_label_score
			// 
			this->p1_label_score->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->p1_label_score->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0)));
			this->p1_label_score->Location = System::Drawing::Point(16, 46);
			this->p1_label_score->Name = L"p1_label_score";
			this->p1_label_score->Size = System::Drawing::Size(60, 16);
			this->p1_label_score->TabIndex = 2;
			this->p1_label_score->Text = L"Score:"+ p1.score;
			// 
			// p1_label_moves
			// 
			this->p1_label_moves->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->p1_label_moves->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F));
			this->p1_label_moves->Location = System::Drawing::Point(16, 62);
			this->p1_label_moves->Name = L"p1_label_moves";
			this->p1_label_moves->Size = System::Drawing::Size(60, 26);
			this->p1_label_moves->TabIndex = 3;
			this->p1_label_moves->Text = L"Moves:"+ 0;
			// 
			// turns_label
			// 
			this->turns_label->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->turns_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0)));
			this->turns_label->Location = System::Drawing::Point(338, 17);
			this->turns_label->Name = L"turns_label";
			this->turns_label->Size = System::Drawing::Size(124, 24);
			this->turns_label->TabIndex = 4;
			this->turns_label->Text = L"Player " + ((turns % 2)+1) + "'s Turn";
			this->turns_label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// time_label
			// 
			this->time_label->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->time_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 21.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0)));
			this->time_label->Location = System::Drawing::Point(350, 41);
			this->time_label->Name = L"time_label";
			this->time_label->Size = System::Drawing::Size(100, 35);
			this->time_label->TabIndex = 5;
			this->time_label->Text = L"00:00";
			this->time_label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// p2_label_moves
			// 
			this->p2_label_moves->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->p2_label_moves->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F));
			this->p2_label_moves->Location = System::Drawing::Point(698, 63);
			this->p2_label_moves->Name = L"p2_label_moves";
			this->p2_label_moves->Size = System::Drawing::Size(60, 26);
			this->p2_label_moves->TabIndex = 8;
			this->p2_label_moves->Text = L"Moves:"+ 0;
			this->p2_label_moves->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// p2_label_score
			// 
			this->p2_label_score->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->p2_label_score->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0)));
			this->p2_label_score->Location = System::Drawing::Point(698, 47);
			this->p2_label_score->Name = L"p2_label_score";
			this->p2_label_score->Size = System::Drawing::Size(60, 16);
			this->p2_label_score->TabIndex = 7;
			this->p2_label_score->Text = L"Score:" + p2.score;
			this->p2_label_score->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// p2_label
			// 
			this->p2_label->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->p2_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,static_cast<System::Byte>(0)));
			this->p2_label->Location = System::Drawing::Point(648, 9);
			this->p2_label->Name = L"p2_label";
			this->p2_label->Size = System::Drawing::Size(124, 37);
			this->p2_label->TabIndex = 6;
			this->p2_label->Text = L"Player2";
			// 
			// owrname
			// 
			this->owrname->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->owrname->Font = (gcnew System::Drawing::Font(L"Open Sans", 7));
			this->owrname->Location = System::Drawing::Point(300, 590);
			this->owrname->Name = L"owrname";
			this->owrname->Size = System::Drawing::Size(200, 25);
			this->owrname->TabIndex = 9;
			this->owrname->Text = L"Mohamed Nasr and Ahmed Hassan";
			this->owrname->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// GameForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;

			this->ClientSize = System::Drawing::Size(784, 611);
			this->ControlBox = false;
			this->Controls->Add(this->owrname);
			this->Controls->Add(this->p2_label_moves);
			this->Controls->Add(this->p2_label_score);
			this->Controls->Add(this->p2_label);
			this->Controls->Add(this->time_label);
			this->Controls->Add(this->turns_label);
			this->Controls->Add(this->p1_label_moves);
			this->Controls->Add(this->p1_label_score);
			this->Controls->Add(this->p1_label);
			this->Controls->Add(this->main_menu);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"GameForm";
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->Text = L"GameForm";
			this->ResumeLayout(false);
		}
#pragma endregion

	private: System::Void main_menu_Click(System::Object^ sender, System::EventArgs^ e) {
		GameForm::Visible = false;	
	}
};
}
