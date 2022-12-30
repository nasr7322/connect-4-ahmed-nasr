#pragma once
#include "structures.h"
#include "actions.h"
#include "undoRedo.h"
#include "saveGame.h"
#include <Windows.h>
#include "AI_player.h"

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

		int secounds = 0, minutes = 0;
		String^ sec, ^ min;

	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ actionsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ undoToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ redoToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ saveToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ exitToolStripMenuItem;
	private: System::Windows::Forms::Panel^ winnerpanel;
	private: System::Windows::Forms::Label^ winnerlabel;
	private: System::Windows::Forms::Button^ to_leaderboards_button;
	private: System::Windows::Forms::Label^ enter_name_winner;
	private: System::Windows::Forms::TextBox^ winner_name;
	private: System::Windows::Forms::Label^ final_scores_label;
	private: System::Windows::Forms::Panel^ save_panel;
	private: System::Windows::Forms::Label^ save_label;
	private: System::Windows::Forms::Button^ cancel_save_button;
	private: System::Windows::Forms::Button^ save_button;
	private: System::Windows::Forms::Label^ saveas_label;
	private: System::Windows::Forms::TextBox^ save_box;
	private: System::Windows::Forms::ToolStripMenuItem^ hintToolStripMenuItem;
	private: System::Windows::Forms::Button^ p2_icon;
	private: System::Windows::Forms::Button^ p1_icon;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Timer^ timer;
	private: System::Windows::Forms::Button^ main_menu;
	private: System::Windows::Forms::Label^ p1_label;
	private: System::Windows::Forms::Label^ p1_label_score;
	private: System::Windows::Forms::Label^ p1_label_moves;
	private: System::Windows::Forms::Label^ turns_label;
	private: System::Windows::Forms::Label^ time_label;
	private: System::Windows::Forms::Label^ p2_label_moves;
	private: System::Windows::Forms::Label^ p2_label_score;
	private: System::Windows::Forms::Label^ p2_label;
	private: System::ComponentModel::IContainer^ components;

	public:


		//comment here
		void debg(Object^ O) {
			String^ s = System::Convert::ToString(O);
			auto a = s->ToCharArray();

			char name[255];
			int j = 0;
			for (; j < a->Length; j++) {
				name[j] = a[j];
			}
			name[j] = '\0';
			OutputDebugStringA(name);
			OutputDebugStringA("\n");
		}

		//updating panel 1 with buttons and selectors
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

		//column button click
		Void column_button_Click(System::Object^ sender, System::EventArgs^ e) {
			Button^ clicked = (Button^)sender;
			int ret = PlayerMove(&board, (turns & 1) ? (&p2) : (&p1), System::Convert::ToInt32(clicked->Tag));
			if (!ret) {
				play_stack[turns++] = System::Convert::ToInt32(clicked->Tag);
				play_stack[turns] = -1;
				this->redoToolStripMenuItem->Enabled = false;
				if (board.mode == 0)
					this->undoToolStripMenuItem->Enabled = true;
			}
			//updatePanel1(); uncommint when you add the delay
			if (board.mode) {
				int bst = best_move(&board, &p2, &p1);
				int ret = PlayerMove(&board, &p2, bst);
				if (!ret) {
					play_stack[turns++] = bst;
					play_stack[turns] = -1;
				}
			}
			//add delay here
			updatePanel1();
		}

		//printing the board of buttons
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
						try {
							button->BackgroundImage = System::Drawing::Image::FromFile("ORANGE.PNG");
						}
						catch (...) {
							button->Text = "O";
						}
					}
					else if (fboard.board[i][j] == 2) {
						try {
							button->BackgroundImage = System::Drawing::Image::FromFile("RED.PNG");
						}
						catch (...) {
							button->Text = "R";
						}
					}
					panel1->Controls->Add(button);
				}
			}
		}

		//printing the select buttons
		void PrintButtons(int w) {
			Button^ select;
			for (int i = 0; i < w; i++) {
				select = gcnew System::Windows::Forms::Button;
				select->Height = 25;
				select->Width = 500 / w;
				select->Left = 150 + (i * (select->Width));
				select->Top = 100;
				select->Tag = i;
				select->Click += gcnew EventHandler(this, &GameForm::column_button_Click);
				panel1->Controls->Add(select);
			}
		}

		//endgame conditiones
		void gameend() {
			timer->Enabled = false;
			panel1->Enabled = false;
			winnerpanel->Visible = true;
			winnerpanel->Location = System::Drawing::Point(250, 250);
			if (p1.score < p2.score) {
				winnerlabel->Text = "Player 2 Wins!!";
			}
			else if (p1.score > p2.score) {
				winnerlabel->Text = "Player 1 Wins!!";
			}
			else {
				winnerlabel->Text = "It's a Draw!!";
			}
			final_scores_label->Text = "Player 1's " + (p1_label_score->Text) + "player 2's " + p2_label_score->Text;
		}

		GameForm(int h, int w, Board B, Player P1, Player P2)
		{

			InitializeComponent();

			if (B.width != 0) {
				board = B;
				p1 = P1;
				p2 = P2;
				debg(p1.score);
				debg(p1.turns_played);
			}
			else {
				board.height = h;
				board.width = w;
				board.mode = B.mode;
				p1.score = p1.turns_played = 0;
				p1.id = 1;
				p2.score = p2.turns_played = 0;
				p2.id = 2;
			}
			if (board.mode) this->hintToolStripMenuItem->Enabled = false;
			turns = p1.turns_played + p2.turns_played;
			for (int i = 0; i < 3000; i++) play_stack[i] = -1;
			updatePanel1();
			PrintBoard(board.height, board.width, board);
			PrintButtons(board.width);
		}




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
			   this->save_panel = (gcnew System::Windows::Forms::Panel());
			   this->cancel_save_button = (gcnew System::Windows::Forms::Button());
			   this->save_button = (gcnew System::Windows::Forms::Button());
			   this->saveas_label = (gcnew System::Windows::Forms::Label());
			   this->save_box = (gcnew System::Windows::Forms::TextBox());
			   this->save_label = (gcnew System::Windows::Forms::Label());
			   this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			   this->actionsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->undoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->redoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->saveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->hintToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->exitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			   this->timer = (gcnew System::Windows::Forms::Timer(this->components));
			   this->winnerpanel = (gcnew System::Windows::Forms::Panel());
			   this->to_leaderboards_button = (gcnew System::Windows::Forms::Button());
			   this->enter_name_winner = (gcnew System::Windows::Forms::Label());
			   this->winner_name = (gcnew System::Windows::Forms::TextBox());
			   this->final_scores_label = (gcnew System::Windows::Forms::Label());
			   this->winnerlabel = (gcnew System::Windows::Forms::Label());
			   this->p1_icon = (gcnew System::Windows::Forms::Button());
			   this->p2_icon = (gcnew System::Windows::Forms::Button());
			   this->button1 = (gcnew System::Windows::Forms::Button());
			   this->button2 = (gcnew System::Windows::Forms::Button());
			   this->button3 = (gcnew System::Windows::Forms::Button());
			   this->button4 = (gcnew System::Windows::Forms::Button());
			   this->panel1 = (gcnew System::Windows::Forms::Panel());
			   this->save_panel->SuspendLayout();
			   this->menuStrip1->SuspendLayout();
			   this->winnerpanel->SuspendLayout();
			   this->SuspendLayout();
			   // 
			   // main_menu
			   // 
			   this->main_menu->Anchor = System::Windows::Forms::AnchorStyles::None;
			   this->main_menu->BackColor = System::Drawing::SystemColors::Control;
			   this->main_menu->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			   this->main_menu->Location = System::Drawing::Point(350, 565);
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
			   this->p1_label->Location = System::Drawing::Point(16, 26);
			   this->p1_label->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
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
			   this->p1_label_score->Location = System::Drawing::Point(21, 72);
			   this->p1_label_score->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			   this->p1_label_score->Name = L"p1_label_score";
			   this->p1_label_score->Size = System::Drawing::Size(75, 16);
			   this->p1_label_score->TabIndex = 2;
			   this->p1_label_score->Text = L"Score:0";
			   // 
			   // p1_label_moves
			   // 
			   this->p1_label_moves->Anchor = System::Windows::Forms::AnchorStyles::None;
			   this->p1_label_moves->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F));
			   this->p1_label_moves->Location = System::Drawing::Point(21, 91);
			   this->p1_label_moves->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
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
			   this->p2_label_moves->Location = System::Drawing::Point(685, 91);
			   this->p2_label_moves->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
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
			   this->p2_label_score->Location = System::Drawing::Point(700, 71);
			   this->p2_label_score->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
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
			   this->p2_label->Location = System::Drawing::Point(647, 26);
			   this->p2_label->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			   this->p2_label->Name = L"p2_label";
			   this->p2_label->Size = System::Drawing::Size(124, 37);
			   this->p2_label->TabIndex = 6;
			   this->p2_label->Text = L"Player2";
			   // 
			   // save_panel
			   // 
			   this->save_panel->Anchor = System::Windows::Forms::AnchorStyles::None;
			   this->save_panel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			   this->save_panel->Controls->Add(this->cancel_save_button);
			   this->save_panel->Controls->Add(this->save_button);
			   this->save_panel->Controls->Add(this->saveas_label);
			   this->save_panel->Controls->Add(this->save_box);
			   this->save_panel->Controls->Add(this->save_label);
			   this->save_panel->Location = System::Drawing::Point(54, 178);
			   this->save_panel->Name = L"save_panel";
			   this->save_panel->Size = System::Drawing::Size(300, 190);
			   this->save_panel->TabIndex = 0;
			   this->save_panel->Visible = false;
			   // 
			   // cancel_save_button
			   // 
			   this->cancel_save_button->Anchor = System::Windows::Forms::AnchorStyles::None;
			   this->cancel_save_button->Location = System::Drawing::Point(160, 131);
			   this->cancel_save_button->Name = L"cancel_save_button";
			   this->cancel_save_button->Size = System::Drawing::Size(75, 25);
			   this->cancel_save_button->TabIndex = 4;
			   this->cancel_save_button->Text = L"cancel";
			   this->cancel_save_button->UseVisualStyleBackColor = true;
			   this->cancel_save_button->Click += gcnew System::EventHandler(this, &GameForm::cancel_button_Click);
			   // 
			   // save_button
			   // 
			   this->save_button->Anchor = System::Windows::Forms::AnchorStyles::None;
			   this->save_button->Location = System::Drawing::Point(60, 131);
			   this->save_button->Name = L"save_button";
			   this->save_button->Size = System::Drawing::Size(75, 25);
			   this->save_button->TabIndex = 3;
			   this->save_button->Text = L"save";
			   this->save_button->UseVisualStyleBackColor = true;
			   this->save_button->Click += gcnew System::EventHandler(this, &GameForm::button1_Click);
			   // 
			   // saveas_label
			   // 
			   this->saveas_label->Anchor = System::Windows::Forms::AnchorStyles::None;
			   this->saveas_label->AutoSize = true;
			   this->saveas_label->Location = System::Drawing::Point(58, 100);
			   this->saveas_label->Name = L"saveas_label";
			   this->saveas_label->Size = System::Drawing::Size(49, 13);
			   this->saveas_label->TabIndex = 2;
			   this->saveas_label->Text = L"Save as:";
			   // 
			   // save_box
			   // 
			   this->save_box->Anchor = System::Windows::Forms::AnchorStyles::None;
			   this->save_box->Location = System::Drawing::Point(122, 95);
			   this->save_box->Name = L"save_box";
			   this->save_box->Size = System::Drawing::Size(113, 20);
			   this->save_box->TabIndex = 1;
			   // 
			   // save_label
			   // 
			   this->save_label->Anchor = System::Windows::Forms::AnchorStyles::None;
			   this->save_label->AutoSize = true;
			   this->save_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 30, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->save_label->Location = System::Drawing::Point(43, 19);
			   this->save_label->Name = L"save_label";
			   this->save_label->Size = System::Drawing::Size(220, 46);
			   this->save_label->TabIndex = 0;
			   this->save_label->Text = L"Save game";
			   // 
			   // menuStrip1
			   // 
			   this->menuStrip1->Anchor = System::Windows::Forms::AnchorStyles::None;
			   this->menuStrip1->AutoSize = false;
			   this->menuStrip1->BackColor = System::Drawing::Color::Transparent;
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
			   this->actionsToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(5) {
				   this->undoToolStripMenuItem,
					   this->redoToolStripMenuItem, this->saveToolStripMenuItem, this->hintToolStripMenuItem, this->exitToolStripMenuItem
			   });
			   this->actionsToolStripMenuItem->Name = L"actionsToolStripMenuItem";
			   this->actionsToolStripMenuItem->Size = System::Drawing::Size(59, 17);
			   this->actionsToolStripMenuItem->Text = L"Actions";
			   // 
			   // undoToolStripMenuItem
			   // 
			   this->undoToolStripMenuItem->Enabled = false;
			   this->undoToolStripMenuItem->Name = L"undoToolStripMenuItem";
			   this->undoToolStripMenuItem->Size = System::Drawing::Size(103, 22);
			   this->undoToolStripMenuItem->Text = L"Undo";
			   this->undoToolStripMenuItem->Click += gcnew System::EventHandler(this, &GameForm::undoToolStripMenuItem_Click);
			   // 
			   // redoToolStripMenuItem
			   // 
			   this->redoToolStripMenuItem->Enabled = false;
			   this->redoToolStripMenuItem->Name = L"redoToolStripMenuItem";
			   this->redoToolStripMenuItem->Size = System::Drawing::Size(103, 22);
			   this->redoToolStripMenuItem->Text = L"Redo";
			   this->redoToolStripMenuItem->Click += gcnew System::EventHandler(this, &GameForm::redoToolStripMenuItem_Click);
			   // 
			   // saveToolStripMenuItem
			   // 
			   this->saveToolStripMenuItem->Name = L"saveToolStripMenuItem";
			   this->saveToolStripMenuItem->Size = System::Drawing::Size(103, 22);
			   this->saveToolStripMenuItem->Text = L"Save";
			   this->saveToolStripMenuItem->Click += gcnew System::EventHandler(this, &GameForm::saveToolStripMenuItem_Click);
			   // 
			   // hintToolStripMenuItem
			   // 
			   this->hintToolStripMenuItem->Name = L"hintToolStripMenuItem";
			   this->hintToolStripMenuItem->Size = System::Drawing::Size(103, 22);
			   this->hintToolStripMenuItem->Text = L"Hint";
			   this->hintToolStripMenuItem->Click += gcnew System::EventHandler(this, &GameForm::hintToolStripMenuItem_Click);
			   // 
			   // exitToolStripMenuItem
			   // 
			   this->exitToolStripMenuItem->Name = L"exitToolStripMenuItem";
			   this->exitToolStripMenuItem->Size = System::Drawing::Size(103, 22);
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
			   this->winnerpanel->Controls->Add(this->to_leaderboards_button);
			   this->winnerpanel->Controls->Add(this->enter_name_winner);
			   this->winnerpanel->Controls->Add(this->winner_name);
			   this->winnerpanel->Controls->Add(this->final_scores_label);
			   this->winnerpanel->Controls->Add(this->winnerlabel);
			   this->winnerpanel->Location = System::Drawing::Point(443, 178);
			   this->winnerpanel->Name = L"winnerpanel";
			   this->winnerpanel->Size = System::Drawing::Size(300, 190);
			   this->winnerpanel->TabIndex = 10;
			   this->winnerpanel->Visible = false;
			   // 
			   // to_leaderboards_button
			   // 
			   this->to_leaderboards_button->Anchor = System::Windows::Forms::AnchorStyles::None;
			   this->to_leaderboards_button->Location = System::Drawing::Point(100, 156);
			   this->to_leaderboards_button->Name = L"to_leaderboards_button";
			   this->to_leaderboards_button->Size = System::Drawing::Size(100, 23);
			   this->to_leaderboards_button->TabIndex = 6;
			   this->to_leaderboards_button->Text = L"Leaderboard";
			   this->to_leaderboards_button->UseVisualStyleBackColor = true;
			   // 
			   // enter_name_winner
			   // 
			   this->enter_name_winner->Anchor = System::Windows::Forms::AnchorStyles::None;
			   this->enter_name_winner->Location = System::Drawing::Point(103, 107);
			   this->enter_name_winner->Name = L"enter_name_winner";
			   this->enter_name_winner->Size = System::Drawing::Size(88, 16);
			   this->enter_name_winner->TabIndex = 5;
			   this->enter_name_winner->Text = L"Enter Your Name";
			   // 
			   // winner_name
			   // 
			   this->winner_name->Anchor = System::Windows::Forms::AnchorStyles::None;
			   this->winner_name->Location = System::Drawing::Point(75, 125);
			   this->winner_name->Name = L"winner_name";
			   this->winner_name->Size = System::Drawing::Size(150, 20);
			   this->winner_name->TabIndex = 4;
			   // 
			   // final_scores_label
			   // 
			   this->final_scores_label->Anchor = System::Windows::Forms::AnchorStyles::None;
			   this->final_scores_label->Location = System::Drawing::Point(87, 63);
			   this->final_scores_label->Name = L"final_scores_label";
			   this->final_scores_label->Size = System::Drawing::Size(124, 33);
			   this->final_scores_label->TabIndex = 3;
			   this->final_scores_label->Text = L"player 1 \'s score: 100 player 2 \'s score: 100";
			   this->final_scores_label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   // 
			   // winnerlabel
			   // 
			   this->winnerlabel->Anchor = System::Windows::Forms::AnchorStyles::None;
			   this->winnerlabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->winnerlabel->Location = System::Drawing::Point(30, 12);
			   this->winnerlabel->Name = L"winnerlabel";
			   this->winnerlabel->Size = System::Drawing::Size(240, 40);
			   this->winnerlabel->TabIndex = 2;
			   this->winnerlabel->Text = L"Player 1 wins";
			   this->winnerlabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			   // 
			   // p1_icon
			   // 
			   this->p1_icon->Anchor = System::Windows::Forms::AnchorStyles::None;
			   this->p1_icon->BackColor = System::Drawing::Color::Transparent;
			   this->p1_icon->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"p1_icon.BackgroundImage")));
			   this->p1_icon->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			   this->p1_icon->Enabled = false;
			   this->p1_icon->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			   this->p1_icon->ForeColor = System::Drawing::Color::Transparent;
			   this->p1_icon->Location = System::Drawing::Point(145, 20);
			   this->p1_icon->Name = L"p1_icon";
			   this->p1_icon->Size = System::Drawing::Size(50, 50);
			   this->p1_icon->TabIndex = 11;
			   this->p1_icon->UseVisualStyleBackColor = false;
			   // 
			   // p2_icon
			   // 
			   this->p2_icon->Anchor = System::Windows::Forms::AnchorStyles::None;
			   this->p2_icon->BackColor = System::Drawing::Color::Transparent;
			   this->p2_icon->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"p2_icon.BackgroundImage")));
			   this->p2_icon->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
			   this->p2_icon->Enabled = false;
			   this->p2_icon->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			   this->p2_icon->ForeColor = System::Drawing::Color::Transparent;
			   this->p2_icon->Location = System::Drawing::Point(591, 20);
			   this->p2_icon->Name = L"p2_icon";
			   this->p2_icon->Size = System::Drawing::Size(50, 50);
			   this->p2_icon->TabIndex = 12;
			   this->p2_icon->UseVisualStyleBackColor = false;
			   // 
			   // button1
			   // 
			   this->button1->Anchor = System::Windows::Forms::AnchorStyles::None;
			   this->button1->BackColor = System::Drawing::SystemColors::Control;
			   this->button1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			   this->button1->Location = System::Drawing::Point(218, 565);
			   this->button1->Name = L"button1";
			   this->button1->Size = System::Drawing::Size(100, 25);
			   this->button1->TabIndex = 13;
			   this->button1->Text = L"Redo";
			   this->button1->UseVisualStyleBackColor = false;
			   // 
			   // button2
			   // 
			   this->button2->Anchor = System::Windows::Forms::AnchorStyles::None;
			   this->button2->BackColor = System::Drawing::SystemColors::Control;
			   this->button2->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			   this->button2->Location = System::Drawing::Point(90, 565);
			   this->button2->Name = L"button2";
			   this->button2->Size = System::Drawing::Size(100, 25);
			   this->button2->TabIndex = 14;
			   this->button2->Text = L"Undo";
			   this->button2->UseVisualStyleBackColor = false;
			   // 
			   // button3
			   // 
			   this->button3->Anchor = System::Windows::Forms::AnchorStyles::None;
			   this->button3->BackColor = System::Drawing::SystemColors::Control;
			   this->button3->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			   this->button3->Location = System::Drawing::Point(480, 565);
			   this->button3->Name = L"button3";
			   this->button3->Size = System::Drawing::Size(100, 25);
			   this->button3->TabIndex = 15;
			   this->button3->Text = L"Hint";
			   this->button3->UseVisualStyleBackColor = false;
			   // 
			   // button4
			   // 
			   this->button4->Anchor = System::Windows::Forms::AnchorStyles::None;
			   this->button4->BackColor = System::Drawing::SystemColors::Control;
			   this->button4->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			   this->button4->Location = System::Drawing::Point(613, 565);
			   this->button4->Name = L"button4";
			   this->button4->Size = System::Drawing::Size(100, 25);
			   this->button4->TabIndex = 16;
			   this->button4->Text = L"Save";
			   this->button4->UseVisualStyleBackColor = false;
			   // 
			   // panel1
			   // 
			   this->panel1->Dock = System::Windows::Forms::DockStyle::Fill;
			   this->panel1->Location = System::Drawing::Point(0, 0);
			   this->panel1->Name = L"panel1";
			   this->panel1->Size = System::Drawing::Size(784, 611);
			   this->panel1->TabIndex = 17;
			   // 
			   // GameForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(784, 611);
			   this->ControlBox = false;
			   this->Controls->Add(this->button4);
			   this->Controls->Add(this->button3);
			   this->Controls->Add(this->button2);
			   this->Controls->Add(this->button1);
			   this->Controls->Add(this->menuStrip1);
			   this->Controls->Add(this->time_label);
			   this->Controls->Add(this->turns_label);
			   this->Controls->Add(this->p1_label_moves);
			   this->Controls->Add(this->p1_label_score);
			   this->Controls->Add(this->p1_label);
			   this->Controls->Add(this->p2_label_moves);
			   this->Controls->Add(this->p2_label);
			   this->Controls->Add(this->p2_label_score);
			   this->Controls->Add(this->main_menu);
			   this->Controls->Add(this->p2_icon);
			   this->Controls->Add(this->p1_icon);
			   this->Controls->Add(this->save_panel);
			   this->Controls->Add(this->winnerpanel);
			   this->Controls->Add(this->panel1);
			   this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			   this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			   this->MainMenuStrip = this->menuStrip1;
			   this->MaximizeBox = false;
			   this->Name = L"GameForm";
			   this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			   this->Text = L"GameForm";
			   this->save_panel->ResumeLayout(false);
			   this->save_panel->PerformLayout();
			   this->menuStrip1->ResumeLayout(false);
			   this->menuStrip1->PerformLayout();
			   this->winnerpanel->ResumeLayout(false);
			   this->winnerpanel->PerformLayout();
			   this->ResumeLayout(false);

		   }

#pragma endregion

	private: System::Void main_menu_Click(System::Object^ sender, System::EventArgs^ e) {
		timer->Enabled = false;
		this->Close();
		turns = 0;
		Reset(&board, &p1, &p2);
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
		if (board.mode == 0)
			this->redoToolStripMenuItem->Enabled = true;
		debg("Undo");
		for (int i = 0; i < turns; i++)
			debg(play_stack[i]);
		debg(play_stack[turns]);
		UndoMove(&board, &p1, &p2, play_stack, &turns);
		updatePanel1();
		if (!canUndo(play_stack, turns))
			this->undoToolStripMenuItem->Enabled = false;
	}

	private: System::Void redoToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		if (board.mode == 0)
			this->undoToolStripMenuItem->Enabled = true;
		RedoMove(&board, &p1, &p2, play_stack, &turns);
		updatePanel1();
		if (!canRedo(play_stack, turns))
			this->redoToolStripMenuItem->Enabled = false;
	}

	private: System::Void saveToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		///SaveBoard(&board, "games_struct.txt", "G1");
		if (!(this->Contains(save_panel)))
			this->Controls->Add(save_panel);
		save_panel->Show();
		save_panel->BringToFront();

	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		if (save_box->Text == "" || save_box->Text->Length > 12) {
			MessageBox::Show("Invalid Name(1<=length<=12)", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		else if (GetNoSaved() == 3) {
			MessageBox::Show("Maximum number of saved games reached", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);

		}
		else {
			///Casting
			auto a = save_box->Text->ToLower()->ToCharArray();
			char name[255];
			int j = 0;
			for (; j < a->Length; j++) {
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
	private: System::Void hintToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

		if (board.width > 10 || board.height > 10) {
			MessageBox::Show("Sorry can't help with big boards ", "Hint", MessageBoxButtons::OK, MessageBoxIcon::Warning);

		}
		else {

			int bst = best_move(&board, (turns & 1) ? (&p2) : (&p1), (turns & 1) ? (&p1) : (&p2));
			MessageBox::Show("Hmmm,I think best move is column " + System::Convert::ToString(bst) + ", " + ((turns & 1) ? ("Player 2") : ("Player 1")), "Hint", MessageBoxButtons::OK, MessageBoxIcon::Information);

		}
	}
	};
}
