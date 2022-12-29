#pragma once
#include "structures.h"
#include "actions.h"
#include "undoRedo.h"
#include "saveGame.h"


namespace Guimain {

	Board board;
	Player p1;
	Player p2;
	int turns = 0;
	int play_stack[3000];
	
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class GameForm : public System::Windows::Forms::Form
	{

		static int secounds = 0, minutes = 0;
		String ^sec, ^min;
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ actionsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ undoToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ redoToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ saveToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ exitToolStripMenuItem;
	internal: System::Windows::Forms::Panel^ winnerpanel;
	private:
	private: System::Windows::Forms::Label^ label2;
	internal:


	private: System::Windows::Forms::Timer^ timer;




	public:
		void updatePanel1() {

			panel1->Controls->Clear();
			Panel^ panel1;
			panel1 = gcnew System::Windows::Forms::Panel;
			PrintBoard(board.height, board.width, board);
			PrintButtons(board.width);
			p1_label_score->Text = L"Score:" + System::Convert::ToString((p1.score));
			p1_label_moves->Text = L"Moves:" + System::Convert::ToString(p1.turns_played);
			p2_label_moves->Text = L"Moves:" + System::Convert::ToString(p2.turns_played);
			p2_label_score->Text = L"Score:" + System::Convert::ToString(p2.score);
			turns_label->Text = L"Player " + System::Convert::ToString((turns % 2) + 1) + "'s Turn";
			if (turns == (board.height) * (board.width)) {
				gameend();
			}
		}
		
		Void button_Click(System::Object^ sender, System::EventArgs^ e) {
			Button^ clicked = (Button^) sender;
			int ret=PlayerMove(&board, (turns & 1) ? (&p2) : (&p1), System::Convert::ToInt32(clicked->Tag));
			if (!ret) {
				play_stack[turns++] = System::Convert::ToInt32(clicked->Tag);
				play_stack[turns] = -1;
				this->redoToolStripMenuItem->Enabled = false;
				this->undoToolStripMenuItem->Enabled = true;
			}
			updatePanel1();
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
					button->BackColor = System::Drawing::Color::RoyalBlue;
					button->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
					button->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
					if (fboard.board[i][j] == 1) {
						button->BackgroundImage = System::Drawing::Image::FromFile("ORANGE.PNG");
					}

					if (fboard.board[i][j] == 2) {
						button->BackgroundImage = System::Drawing::Image::FromFile("RED.PNG");
					}
					
					panel1->Controls->Add(button);
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
					select->Click += gcnew EventHandler(this,&GameForm::button_Click);
					panel1->Controls->Add(select);
			}
		}

		void addtimer() {
			Timer ^timer;
			timer = gcnew System::Windows::Forms::Timer;
			timer->Enabled = true;
			timer->Interval = 1000;
			timer->Tick += gcnew System::EventHandler(this, &GameForm::timer_Tick);
		}

		void gameend(){
			timer->Enabled = false;
			panel1->Enabled = false;
			if (p1.score < p2.score){}
			if (p1.score > p2.score) {}
			else {}
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

	private: System::ComponentModel::IContainer^ components;

	private:


#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(GameForm::typeid));
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
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->actionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->undoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->redoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->timer = (gcnew System::Windows::Forms::Timer(this->components));
			this->winnerpanel = (gcnew System::Windows::Forms::Panel());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->menuStrip1->SuspendLayout();
			this->winnerpanel->SuspendLayout();
			this->SuspendLayout();
			// 
			// main_menu
			// 
			this->main_menu->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->main_menu->BackColor = System::Drawing::SystemColors::Control;
			this->main_menu->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->main_menu->Location = System::Drawing::Point(350, 560);
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
			this->p1_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->p1_label->Location = System::Drawing::Point(12, 21);
			this->p1_label->Name = L"p1_label";
			this->p1_label->Size = System::Drawing::Size(122, 37);
			this->p1_label->TabIndex = 1;
			this->p1_label->Text = L"Player1";
			// 
			// p1_label_score
			// 
			this->p1_label_score->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->p1_label_score->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->p1_label_score->Location = System::Drawing::Point(16, 58);
			this->p1_label_score->Name = L"p1_label_score";
			this->p1_label_score->Size = System::Drawing::Size(60, 16);
			this->p1_label_score->TabIndex = 2;
			this->p1_label_score->Text = L"Score:0";
			// 
			// p1_label_moves
			// 
			this->p1_label_moves->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->p1_label_moves->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F));
			this->p1_label_moves->Location = System::Drawing::Point(16, 74);
			this->p1_label_moves->Name = L"p1_label_moves";
			this->p1_label_moves->Size = System::Drawing::Size(75, 26);
			this->p1_label_moves->TabIndex = 3;
			this->p1_label_moves->Text = L"Moves:0";
			// 
			// turns_label
			// 
			this->turns_label->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->turns_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->turns_label->Location = System::Drawing::Point(338, 32);
			this->turns_label->Name = L"turns_label";
			this->turns_label->Size = System::Drawing::Size(124, 24);
			this->turns_label->TabIndex = 4;
			this->turns_label->Text = L"Player 1\'s Turn";
			this->turns_label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// time_label
			// 
			this->time_label->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->time_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 21.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->time_label->Location = System::Drawing::Point(350, 56);
			this->time_label->Name = L"time_label";
			this->time_label->Size = System::Drawing::Size(100, 35);
			this->time_label->TabIndex = 5;
			this->time_label->Text = L"0:0";
			this->time_label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// p2_label_moves
			// 
			this->p2_label_moves->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->p2_label_moves->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F));
			this->p2_label_moves->Location = System::Drawing::Point(687, 76);
			this->p2_label_moves->Name = L"p2_label_moves";
			this->p2_label_moves->Size = System::Drawing::Size(75, 26);
			this->p2_label_moves->TabIndex = 8;
			this->p2_label_moves->Text = L"Moves:0";
			this->p2_label_moves->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// p2_label_score
			// 
			this->p2_label_score->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->p2_label_score->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->p2_label_score->Location = System::Drawing::Point(702, 58);
			this->p2_label_score->Name = L"p2_label_score";
			this->p2_label_score->Size = System::Drawing::Size(60, 16);
			this->p2_label_score->TabIndex = 7;
			this->p2_label_score->Text = L"Score:0";
			this->p2_label_score->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// p2_label
			// 
			this->p2_label->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->p2_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->p2_label->Location = System::Drawing::Point(648, 21);
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
			// menuStrip1
			// 
			this->menuStrip1->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->menuStrip1->AutoSize = false;
			this->menuStrip1->BackColor = System::Drawing::SystemColors::ActiveCaption;
			this->menuStrip1->Dock = System::Windows::Forms::DockStyle::None;
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->actionsToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Padding = System::Windows::Forms::Padding(4, 2, 0, 2);
			this->menuStrip1->Size = System::Drawing::Size(784, 21);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// actionsToolStripMenuItem
			// 
			this->actionsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->undoToolStripMenuItem,
					this->redoToolStripMenuItem, this->saveToolStripMenuItem, this->exitToolStripMenuItem
			});
			this->actionsToolStripMenuItem->Name = L"actionsToolStripMenuItem";
			this->actionsToolStripMenuItem->Size = System::Drawing::Size(59, 17);
			this->actionsToolStripMenuItem->Text = L"Actions";
			// 
			// undoToolStripMenuItem
			// 
			this->undoToolStripMenuItem->Enabled = false;
			this->undoToolStripMenuItem->Name = L"undoToolStripMenuItem";
			this->undoToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->undoToolStripMenuItem->Text = L"Undo";
			this->undoToolStripMenuItem->Click += gcnew System::EventHandler(this, &GameForm::undoToolStripMenuItem_Click);
			// 
			// redoToolStripMenuItem
			// 
			this->redoToolStripMenuItem->Enabled = false;
			this->redoToolStripMenuItem->Name = L"redoToolStripMenuItem";
			this->redoToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->redoToolStripMenuItem->Text = L"Redo";
			this->redoToolStripMenuItem->Click += gcnew System::EventHandler(this, &GameForm::redoToolStripMenuItem_Click);
			// 
			// saveToolStripMenuItem
			// 
			this->saveToolStripMenuItem->Name = L"saveToolStripMenuItem";
			this->saveToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->saveToolStripMenuItem->Text = L"Save";
			this->saveToolStripMenuItem->Click += gcnew System::EventHandler(this, &GameForm::saveToolStripMenuItem_Click);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(180, 22);
			this->exitToolStripMenuItem->Text = L"Exit";
			// 
			// timer
			// 
			this->timer->Enabled = true;
			this->timer->Interval = 1000;
			this->timer->Tick += gcnew System::EventHandler(this, &GameForm::timer_Tick);
			// 
			// winnerpanel
			// 
			this->winnerpanel->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->winnerpanel->Controls->Add(this->label2);
			this->winnerpanel->Location = System::Drawing::Point(182, 190);
			this->winnerpanel->Name = L"winnerpanel";
			this->winnerpanel->Size = System::Drawing::Size(450, 150);
			this->winnerpanel->TabIndex = 10;
			this->winnerpanel->Visible = false;
			// 
			// label2
			// 
			this->label2->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(114, 20);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(240, 40);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Player 1 wins";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// GameForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(784, 611);
			this->ControlBox = false;
			this->Controls->Add(this->winnerpanel);
			this->Controls->Add(this->menuStrip1);
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
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menuStrip1;
			this->MaximizeBox = false;
			this->Name = L"GameForm";
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->Text = L"GameForm";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->winnerpanel->ResumeLayout(false);
			this->ResumeLayout(false);

		}

#pragma endregion

	private: System::Void main_menu_Click(System::Object^ sender, System::EventArgs^ e) {
		timer->Enabled = false;
		this->Close();
		turns = 0;
		Reset(&board,&p1,&p2);
		secounds = 0;
		minutes = 0;
	}

private: System::Void timer_Tick(System::Object^ sender, System::EventArgs^ e) {
	secounds++;
	if (secounds == 60) { 
		secounds = 0;
		minutes++;
	}
	sec = Convert::ToString(secounds);
	min = Convert::ToString(minutes);
	time_label->Text = min + ":" + sec;
}
	   
private: System::Void undoToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	this->redoToolStripMenuItem->Enabled = true;
	UndoMove(&board,&p1,&p2,play_stack,&turns);
	updatePanel1();
	if(!canUndo(play_stack,turns))
		this->undoToolStripMenuItem->Enabled = false;
}

private: System::Void redoToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	this->undoToolStripMenuItem->Enabled = true;
	RedoMove(&board, &p1, &p2, play_stack, &turns);
	updatePanel1();
	if (!canRedo(play_stack, turns))
		this->redoToolStripMenuItem->Enabled = false;
}

private: System::Void saveToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	SaveBoard(&board, "games_struct.txt", "G1");
}
};
}
