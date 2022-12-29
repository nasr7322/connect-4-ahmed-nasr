#pragma once
#include "structures.h"
#include "actions.h"
#include "undoRedo.h"
#include "saveGame.h"
#include <Windows.h>

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
	private: System::Windows::Forms::Panel^ save_panel;
	private: System::Windows::Forms::Label^ save_label;
	private: System::Windows::Forms::Button^ cancel_button;

	private: System::Windows::Forms::Button^ save_button;

	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ save_box;


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
					try {

						if (fboard.board[i][j] == 1) {
							button->BackgroundImage = System::Drawing::Image::FromFile("ORANGE.PNG");
						}

						if (fboard.board[i][j] == 2) {
							button->BackgroundImage = System::Drawing::Image::FromFile("RED.PNG");
						}

					}
					catch (...) {
						MessageBox::Show("Can't Load Image", "Error", MessageBoxButtons::OK, MessageBoxIcon::Warning);
						

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

		GameForm(int h, int w,Board B,Player P1, Player P2)
		{
			
			InitializeComponent();

			if (B.width != 0) {
				board = B;
				p1 = P1;
				p2 = P2;
			}
			else {

				board.height = h;
				board.width = w;
				p1.score = p1.turns_played = 0;
				p1.id = 1;
				p2.score = p2.turns_played = 0;
				p2.id = 2;
			}
			
			PrintBoard(board.height, board.width, board);
			PrintButtons(w);
			save_panel->Hide();

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
	private: System::Windows::Forms::Panel^ panel1;
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
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->save_panel = (gcnew System::Windows::Forms::Panel());
			this->cancel_button = (gcnew System::Windows::Forms::Button());
			this->save_button = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->save_box = (gcnew System::Windows::Forms::TextBox());
			this->save_label = (gcnew System::Windows::Forms::Label());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->actionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->undoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->redoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->timer = (gcnew System::Windows::Forms::Timer(this->components));
			this->panel1->SuspendLayout();
			this->save_panel->SuspendLayout();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// main_menu
			// 
			this->main_menu->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->main_menu->BackColor = System::Drawing::SystemColors::Control;
			this->main_menu->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->main_menu->Location = System::Drawing::Point(467, 689);
			this->main_menu->Margin = System::Windows::Forms::Padding(4);
			this->main_menu->Name = L"main_menu";
			this->main_menu->Size = System::Drawing::Size(133, 31);
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
			this->p1_label->ForeColor = System::Drawing::Color::Coral;
			this->p1_label->Location = System::Drawing::Point(16, 26);
			this->p1_label->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->p1_label->Name = L"p1_label";
			this->p1_label->Size = System::Drawing::Size(163, 46);
			this->p1_label->TabIndex = 1;
			this->p1_label->Text = L"Player1";
			this->p1_label->Click += gcnew System::EventHandler(this, &GameForm::p1_label_Click);
			// 
			// p1_label_score
			// 
			this->p1_label_score->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->p1_label_score->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->p1_label_score->ForeColor = System::Drawing::Color::Coral;
			this->p1_label_score->Location = System::Drawing::Point(21, 72);
			this->p1_label_score->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->p1_label_score->Name = L"p1_label_score";
			this->p1_label_score->Size = System::Drawing::Size(80, 20);
			this->p1_label_score->TabIndex = 2;
			this->p1_label_score->Text = L"Score:0";
			// 
			// p1_label_moves
			// 
			this->p1_label_moves->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->p1_label_moves->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F));
			this->p1_label_moves->ForeColor = System::Drawing::Color::Coral;
			this->p1_label_moves->Location = System::Drawing::Point(21, 91);
			this->p1_label_moves->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->p1_label_moves->Name = L"p1_label_moves";
			this->p1_label_moves->Size = System::Drawing::Size(100, 32);
			this->p1_label_moves->TabIndex = 3;
			this->p1_label_moves->Text = L"Moves:0";
			// 
			// turns_label
			// 
			this->turns_label->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->turns_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->turns_label->Location = System::Drawing::Point(451, 40);
			this->turns_label->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->turns_label->Name = L"turns_label";
			this->turns_label->Size = System::Drawing::Size(165, 30);
			this->turns_label->TabIndex = 4;
			this->turns_label->Text = L"Player 1\'s Turn";
			this->turns_label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// time_label
			// 
			this->time_label->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->time_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 21.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->time_label->Location = System::Drawing::Point(467, 69);
			this->time_label->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->time_label->Name = L"time_label";
			this->time_label->Size = System::Drawing::Size(133, 43);
			this->time_label->TabIndex = 5;
			this->time_label->Text = L"0:0";
			this->time_label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// p2_label_moves
			// 
			this->p2_label_moves->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->p2_label_moves->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F));
			this->p2_label_moves->ForeColor = System::Drawing::Color::Red;
			this->p2_label_moves->Location = System::Drawing::Point(916, 93);
			this->p2_label_moves->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->p2_label_moves->Name = L"p2_label_moves";
			this->p2_label_moves->Size = System::Drawing::Size(100, 32);
			this->p2_label_moves->TabIndex = 8;
			this->p2_label_moves->Text = L"Moves:0";
			this->p2_label_moves->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// p2_label_score
			// 
			this->p2_label_score->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->p2_label_score->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->p2_label_score->ForeColor = System::Drawing::Color::Red;
			this->p2_label_score->Location = System::Drawing::Point(936, 72);
			this->p2_label_score->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->p2_label_score->Name = L"p2_label_score";
			this->p2_label_score->Size = System::Drawing::Size(80, 20);
			this->p2_label_score->TabIndex = 7;
			this->p2_label_score->Text = L"Score:0";
			this->p2_label_score->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// p2_label
			// 
			this->p2_label->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->p2_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->p2_label->ForeColor = System::Drawing::Color::Red;
			this->p2_label->Location = System::Drawing::Point(864, 26);
			this->p2_label->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->p2_label->Name = L"p2_label";
			this->p2_label->Size = System::Drawing::Size(165, 46);
			this->p2_label->TabIndex = 6;
			this->p2_label->Text = L"Player2";
			// 
			// owrname
			// 
			this->owrname->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->owrname->Font = (gcnew System::Drawing::Font(L"Open Sans", 7));
			this->owrname->Location = System::Drawing::Point(400, 726);
			this->owrname->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->owrname->Name = L"owrname";
			this->owrname->Size = System::Drawing::Size(267, 31);
			this->owrname->TabIndex = 9;
			this->owrname->Text = L"Mohamed Nasr and Ahmed Hassan";
			this->owrname->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// panel1
			// 
			this->panel1->Controls->Add(this->save_panel);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Fill;
			this->panel1->Location = System::Drawing::Point(0, 0);
			this->panel1->Margin = System::Windows::Forms::Padding(4);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(1045, 752);
			this->panel1->TabIndex = 10;
			// 
			// save_panel
			// 
			this->save_panel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->save_panel->Controls->Add(this->cancel_button);
			this->save_panel->Controls->Add(this->save_button);
			this->save_panel->Controls->Add(this->label1);
			this->save_panel->Controls->Add(this->save_box);
			this->save_panel->Controls->Add(this->save_label);
			this->save_panel->Location = System::Drawing::Point(358, 137);
			this->save_panel->Name = L"save_panel";
			this->save_panel->Size = System::Drawing::Size(354, 212);
			this->save_panel->TabIndex = 0;
			// 
			// cancel_button
			// 
			this->cancel_button->Location = System::Drawing::Point(203, 165);
			this->cancel_button->Name = L"cancel_button";
			this->cancel_button->Size = System::Drawing::Size(105, 28);
			this->cancel_button->TabIndex = 4;
			this->cancel_button->Text = L"cancel";
			this->cancel_button->UseVisualStyleBackColor = true;
			this->cancel_button->Click += gcnew System::EventHandler(this, &GameForm::cancel_button_Click);
			// 
			// save_button
			// 
			this->save_button->Location = System::Drawing::Point(58, 169);
			this->save_button->Name = L"save_button";
			this->save_button->Size = System::Drawing::Size(97, 24);
			this->save_button->TabIndex = 3;
			this->save_button->Text = L"save";
			this->save_button->UseVisualStyleBackColor = true;
			this->save_button->Click += gcnew System::EventHandler(this, &GameForm::button1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(112, 87);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(100, 17);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Name of game";
			// 
			// save_box
			// 
			this->save_box->Location = System::Drawing::Point(58, 107);
			this->save_box->Name = L"save_box";
			this->save_box->Size = System::Drawing::Size(248, 22);
			this->save_box->TabIndex = 1;
			// 
			// save_label
			// 
			this->save_label->AutoSize = true;
			this->save_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 30, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->save_label->Location = System::Drawing::Point(34, 17);
			this->save_label->Name = L"save_label";
			this->save_label->Size = System::Drawing::Size(278, 58);
			this->save_label->TabIndex = 0;
			this->save_label->Text = L"Save game";
			this->save_label->Click += gcnew System::EventHandler(this, &GameForm::save_label_Click);
			// 
			// menuStrip1
			// 
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(20, 20);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->actionsToolStripMenuItem });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1045, 28);
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
			this->actionsToolStripMenuItem->Size = System::Drawing::Size(72, 24);
			this->actionsToolStripMenuItem->Text = L"Actions";
			// 
			// undoToolStripMenuItem
			// 
			this->undoToolStripMenuItem->Enabled = false;
			this->undoToolStripMenuItem->Name = L"undoToolStripMenuItem";
			this->undoToolStripMenuItem->Size = System::Drawing::Size(128, 26);
			this->undoToolStripMenuItem->Text = L"Undo";
			this->undoToolStripMenuItem->Click += gcnew System::EventHandler(this, &GameForm::undoToolStripMenuItem_Click);
			// 
			// redoToolStripMenuItem
			// 
			this->redoToolStripMenuItem->Enabled = false;
			this->redoToolStripMenuItem->Name = L"redoToolStripMenuItem";
			this->redoToolStripMenuItem->Size = System::Drawing::Size(128, 26);
			this->redoToolStripMenuItem->Text = L"Redo";
			this->redoToolStripMenuItem->Click += gcnew System::EventHandler(this, &GameForm::redoToolStripMenuItem_Click);
			// 
			// saveToolStripMenuItem
			// 
			this->saveToolStripMenuItem->Name = L"saveToolStripMenuItem";
			this->saveToolStripMenuItem->Size = System::Drawing::Size(128, 26);
			this->saveToolStripMenuItem->Text = L"Save";
			this->saveToolStripMenuItem->Click += gcnew System::EventHandler(this, &GameForm::saveToolStripMenuItem_Click);
			// 
			// exitToolStripMenuItem
			// 
			this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			this->exitToolStripMenuItem->Size = System::Drawing::Size(128, 26);
			this->exitToolStripMenuItem->Text = L"Exit";
			// 
			// timer
			// 
			this->timer->Enabled = true;
			this->timer->Interval = 1000;
			this->timer->Tick += gcnew System::EventHandler(this, &GameForm::timer_Tick);
			// 
			// GameForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1045, 752);
			this->ControlBox = false;
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
			this->Controls->Add(this->panel1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menuStrip1;
			this->Margin = System::Windows::Forms::Padding(4);
			this->MaximizeBox = false;
			this->Name = L"GameForm";
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->Text = L"GameForm";
			this->panel1->ResumeLayout(false);
			this->save_panel->ResumeLayout(false);
			this->save_panel->PerformLayout();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

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
	///SaveBoard(&board, "games_struct.txt", "G1");
	if (!(this->Contains(save_panel)) )
		this->Controls->Add(save_panel);
	save_panel->Show();
	save_panel->BringToFront();
	
}
private: System::Void p1_label_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void save_label_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	if (save_box->Text == ""|| save_box->Text->Length>12) {
		MessageBox::Show("Invalid Name(1<=length<=12)", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
	}else if(GetNoSaved() == 3){
		MessageBox::Show("Maximum number of saved games reached", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);

	}
	else {
		///Casting
		auto a = save_box->Text->ToLower()->ToCharArray();
		char name[255];
		int j = 0;
		for (;j < a->Length;j++) {
			name[j] = a[j];
		}
		name[j] = '\0';
		SaveBoard(&board, "games_struct.txt", name);
		save_panel->Hide();
	}
}
private: System::Void cancel_button_Click(System::Object^ sender, System::EventArgs^ e) {

	save_panel->Hide();
}
};
}
