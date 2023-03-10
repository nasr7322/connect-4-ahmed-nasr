#pragma once
#include "structures.h"
#include "actions.h"
#include "undoRedo.h"
#include "saveGame.h"
#include <Windows.h>
#include "AI_player.h"
#include "storeRank.h"

namespace Guimain {

	Board board;
	Player p1;
	Player p2;
	int turns = 0;
	int play_stack[3000];
	bool showleaderboard = false;
	
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class GameForm : public System::Windows::Forms::Form
	{

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
		private: System::Windows::Forms::Button^ p2_icon;
		private: System::Windows::Forms::Button^ p1_icon;
		private: System::Windows::Forms::Button^ Redo_button;
		private: System::Windows::Forms::Button^ Undo_button;
		private: System::Windows::Forms::Button^ Hint_button;
		private: System::Windows::Forms::Button^ Save_menu_button;
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

		//use for debugging
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
		void column_button_Click(System::Object^ sender, System::EventArgs^ e) {
			try {
				Media::SoundPlayer^ plyr = gcnew Media::SoundPlayer("pop.wav");
				plyr->Play();
			}
			catch(...){}
			Button^ clicked = (Button^)sender;
			int ret = PlayerMove(&board, (turns & 1) ? (&p2) : (&p1), System::Convert::ToInt32(clicked->Tag));
			if (!ret) {
				play_stack[turns++] = System::Convert::ToInt32(clicked->Tag);
				play_stack[turns] = -1;
				Redo_button->Enabled = false;
				if (board.mode == 0) Undo_button->Enabled = true;
			}
			else {
				return;
			}
			if (board.mode) {
				int bst = best_move(&board, &p2, &p1);
				int ret = PlayerMove(&board, &p2, bst);
				if (!ret) {
					play_stack[turns++] = bst;
					play_stack[turns] = -1;
				}
			}
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
				select->Text = System::Convert::ToString(i);
				select->Click += gcnew EventHandler(this, &GameForm::column_button_Click);
				panel1->Controls->Add(select);
			}
		}

		//endgame conditiones
		void gameend() {
			timer->Enabled = false;
			panel1->Enabled = false;
			winnerpanel->Visible = true;
			winnerpanel->Location = System::Drawing::Point(225, 250);
			if (p1.score < p2.score) {
				winnerlabel->Text = "Player 2 Wins!!";
				if (board.mode) {
					enter_name_winner->Visible = false;
					winner_name->Enabled = false;
				}
				else {
					try{
						Media::SoundPlayer^ plyr = gcnew Media::SoundPlayer("win.wav");
						plyr->Play();
					}
					catch (...){}
				}
			}
			else if (p1.score > p2.score) {
				winnerlabel->Text = "Player 1 Wins!!";
				try {
					Media::SoundPlayer^ plyr = gcnew Media::SoundPlayer("win.wav");
					plyr->Play();
				}
				catch (...) {}
			}
			else if (p1.score==p2.score)
			{
				winnerlabel->Text = "It's a Draw!!";
				enter_name_winner->Visible = false;
				winner_name->Enabled = false;
			}
			final_scores_label->Text = "Player 1's " + (p1_label_score->Text) + " ||| Player 2's " + p2_label_score->Text;

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
			if (board.mode) Hint_button->Enabled = false;
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
		this->timer = (gcnew System::Windows::Forms::Timer(this->components));
		this->winnerpanel = (gcnew System::Windows::Forms::Panel());
		this->to_leaderboards_button = (gcnew System::Windows::Forms::Button());
		this->enter_name_winner = (gcnew System::Windows::Forms::Label());
		this->winner_name = (gcnew System::Windows::Forms::TextBox());
		this->final_scores_label = (gcnew System::Windows::Forms::Label());
		this->winnerlabel = (gcnew System::Windows::Forms::Label());
		this->p1_icon = (gcnew System::Windows::Forms::Button());
		this->p2_icon = (gcnew System::Windows::Forms::Button());
		this->Redo_button = (gcnew System::Windows::Forms::Button());
		this->Undo_button = (gcnew System::Windows::Forms::Button());
		this->Hint_button = (gcnew System::Windows::Forms::Button());
		this->Save_menu_button = (gcnew System::Windows::Forms::Button());
		this->panel1 = (gcnew System::Windows::Forms::Panel());
		this->save_panel->SuspendLayout();
		this->winnerpanel->SuspendLayout();
		this->SuspendLayout();
		// 
		// main_menu
		// 
		this->main_menu->Anchor = System::Windows::Forms::AnchorStyles::None;
		this->main_menu->BackColor = System::Drawing::SystemColors::Control;
		this->main_menu->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
		this->main_menu->Cursor = System::Windows::Forms::Cursors::Hand;
		this->main_menu->Location = System::Drawing::Point(350, 559);
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
		this->p1_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 26.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));
		this->p1_label->Location = System::Drawing::Point(16, 15);
		this->p1_label->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
		this->p1_label->Name = L"p1_label";
		this->p1_label->Size = System::Drawing::Size(146, 37);
		this->p1_label->TabIndex = 1;
		this->p1_label->Text = L"Player1";
		// 
		// p1_label_score
		// 
		this->p1_label_score->Anchor = System::Windows::Forms::AnchorStyles::None;
		this->p1_label_score->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));
		this->p1_label_score->Location = System::Drawing::Point(21, 61);
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
		this->p1_label_moves->Location = System::Drawing::Point(21, 80);
		this->p1_label_moves->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
		this->p1_label_moves->Name = L"p1_label_moves";
		this->p1_label_moves->Size = System::Drawing::Size(75, 26);
		this->p1_label_moves->TabIndex = 3;
		this->p1_label_moves->Text = L"Moves:0";
		// 
		// turns_label
		// 
		this->turns_label->Anchor = System::Windows::Forms::AnchorStyles::None;
		this->turns_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 18, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));
		this->turns_label->Location = System::Drawing::Point(270, 15);
		this->turns_label->Name = L"turns_label";
		this->turns_label->Size = System::Drawing::Size(242, 37);
		this->turns_label->TabIndex = 4;
		this->turns_label->Text = L"Player 1\'s Turn";
		this->turns_label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		// 
		// time_label
		// 
		this->time_label->Anchor = System::Windows::Forms::AnchorStyles::None;
		this->time_label->BackColor = System::Drawing::Color::Transparent;
		this->time_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 24, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));
		this->time_label->Location = System::Drawing::Point(350, 49);
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
		this->p2_label_moves->Location = System::Drawing::Point(685, 80);
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
		this->p2_label_score->Location = System::Drawing::Point(700, 60);
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
		this->p2_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 26.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));
		this->p2_label->Location = System::Drawing::Point(635, 15);
		this->p2_label->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
		this->p2_label->Name = L"p2_label";
		this->p2_label->Size = System::Drawing::Size(136, 37);
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
		this->cancel_save_button->Cursor = System::Windows::Forms::Cursors::Hand;
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
		this->save_button->Cursor = System::Windows::Forms::Cursors::Hand;
		this->save_button->Location = System::Drawing::Point(60, 131);
		this->save_button->Name = L"save_button";
		this->save_button->Size = System::Drawing::Size(75, 25);
		this->save_button->TabIndex = 3;
		this->save_button->Text = L"save";
		this->save_button->UseVisualStyleBackColor = true;
		this->save_button->Click += gcnew System::EventHandler(this, &GameForm::save_panel_ok_Click);
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
		this->save_box->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &GameForm::box_KeyPress);
		// 
		// save_label
		// 
		this->save_label->Anchor = System::Windows::Forms::AnchorStyles::None;
		this->save_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 30, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));
		this->save_label->Location = System::Drawing::Point(25, 19);
		this->save_label->Name = L"save_label";
		this->save_label->Size = System::Drawing::Size(250, 46);
		this->save_label->TabIndex = 0;
		this->save_label->Text = L"Save game";
		this->save_label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
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
		this->winnerpanel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
		this->winnerpanel->Controls->Add(this->to_leaderboards_button);
		this->winnerpanel->Controls->Add(this->enter_name_winner);
		this->winnerpanel->Controls->Add(this->winner_name);
		this->winnerpanel->Controls->Add(this->final_scores_label);
		this->winnerpanel->Controls->Add(this->winnerlabel);
		this->winnerpanel->Location = System::Drawing::Point(389, 178);
		this->winnerpanel->Name = L"winnerpanel";
		this->winnerpanel->Size = System::Drawing::Size(350, 190);
		this->winnerpanel->TabIndex = 10;
		this->winnerpanel->Visible = false;
		// 
		// to_leaderboards_button
		// 
		this->to_leaderboards_button->Anchor = System::Windows::Forms::AnchorStyles::None;
		this->to_leaderboards_button->Cursor = System::Windows::Forms::Cursors::Hand;
		this->to_leaderboards_button->Location = System::Drawing::Point(124, 154);
		this->to_leaderboards_button->Name = L"to_leaderboards_button";
		this->to_leaderboards_button->Size = System::Drawing::Size(100, 23);
		this->to_leaderboards_button->TabIndex = 6;
		this->to_leaderboards_button->Text = L"Leaderboard";
		this->to_leaderboards_button->UseVisualStyleBackColor = true;
		this->to_leaderboards_button->Click += gcnew System::EventHandler(this, &GameForm::to_leaderboards_button_Click);
		// 
		// enter_name_winner
		// 
		this->enter_name_winner->Anchor = System::Windows::Forms::AnchorStyles::None;
		this->enter_name_winner->Location = System::Drawing::Point(127, 106);
		this->enter_name_winner->Name = L"enter_name_winner";
		this->enter_name_winner->Size = System::Drawing::Size(88, 16);
		this->enter_name_winner->TabIndex = 5;
		this->enter_name_winner->Text = L"Enter Your Name";
		// 
		// winner_name
		// 
		this->winner_name->Anchor = System::Windows::Forms::AnchorStyles::None;
		this->winner_name->Location = System::Drawing::Point(99, 124);
		this->winner_name->Name = L"winner_name";
		this->winner_name->Size = System::Drawing::Size(150, 20);
		this->winner_name->TabIndex = 4;
		this->winner_name->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &GameForm::winner_name_KeyPress);
		// 
		// final_scores_label
		// 
		this->final_scores_label->Anchor = System::Windows::Forms::AnchorStyles::None;
		this->final_scores_label->BackColor = System::Drawing::Color::Transparent;
		this->final_scores_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F));
		this->final_scores_label->Location = System::Drawing::Point(2, 61);
		this->final_scores_label->Name = L"final_scores_label";
		this->final_scores_label->Size = System::Drawing::Size(342, 33);
		this->final_scores_label->TabIndex = 3;
		this->final_scores_label->Text = L"player 1 \'s score: 100 player 2 \'s score: 100";
		this->final_scores_label->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		// 
		// winnerlabel
		// 
		this->winnerlabel->Anchor = System::Windows::Forms::AnchorStyles::None;
		this->winnerlabel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 30, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
			static_cast<System::Byte>(0)));
		this->winnerlabel->Location = System::Drawing::Point(4, 9);
		this->winnerlabel->Name = L"winnerlabel";
		this->winnerlabel->Size = System::Drawing::Size(340, 54);
		this->winnerlabel->TabIndex = 2;
		this->winnerlabel->Text = L"Player 1 wins";
		this->winnerlabel->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		// 
		// p1_icon
		// 
		this->p1_icon->Anchor = System::Windows::Forms::AnchorStyles::None;
		this->p1_icon->BackColor = System::Drawing::Color::Orange;
		this->p1_icon->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
		this->p1_icon->Enabled = false;
		this->p1_icon->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->p1_icon->ForeColor = System::Drawing::Color::Transparent;
		this->p1_icon->Location = System::Drawing::Point(169, 21);
		this->p1_icon->Name = L"p1_icon";
		this->p1_icon->Size = System::Drawing::Size(95, 28);
		this->p1_icon->TabIndex = 11;
		this->p1_icon->UseVisualStyleBackColor = false;
		// 
		// p2_icon
		// 
		this->p2_icon->Anchor = System::Windows::Forms::AnchorStyles::None;
		this->p2_icon->BackColor = System::Drawing::Color::OrangeRed;
		this->p2_icon->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Zoom;
		this->p2_icon->Enabled = false;
		this->p2_icon->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
		this->p2_icon->ForeColor = System::Drawing::Color::Transparent;
		this->p2_icon->Location = System::Drawing::Point(518, 21);
		this->p2_icon->Name = L"p2_icon";
		this->p2_icon->Size = System::Drawing::Size(95, 28);
		this->p2_icon->TabIndex = 12;
		this->p2_icon->UseVisualStyleBackColor = false;
		// 
		// Redo_button
		// 
		this->Redo_button->Anchor = System::Windows::Forms::AnchorStyles::None;
		this->Redo_button->BackColor = System::Drawing::SystemColors::Control;
		this->Redo_button->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
		this->Redo_button->Cursor = System::Windows::Forms::Cursors::Hand;
		this->Redo_button->Enabled = false;
		this->Redo_button->Location = System::Drawing::Point(218, 559);
		this->Redo_button->Name = L"Redo_button";
		this->Redo_button->Size = System::Drawing::Size(100, 25);
		this->Redo_button->TabIndex = 13;
		this->Redo_button->Text = L"Redo";
		this->Redo_button->UseVisualStyleBackColor = false;
		this->Redo_button->Click += gcnew System::EventHandler(this, &GameForm::redoToolStripMenuItem_Click);
		// 
		// Undo_button
		// 
		this->Undo_button->Anchor = System::Windows::Forms::AnchorStyles::None;
		this->Undo_button->BackColor = System::Drawing::SystemColors::Control;
		this->Undo_button->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
		this->Undo_button->Cursor = System::Windows::Forms::Cursors::Hand;
		this->Undo_button->Enabled = false;
		this->Undo_button->Location = System::Drawing::Point(90, 559);
		this->Undo_button->Name = L"Undo_button";
		this->Undo_button->Size = System::Drawing::Size(100, 25);
		this->Undo_button->TabIndex = 14;
		this->Undo_button->Text = L"Undo";
		this->Undo_button->UseVisualStyleBackColor = false;
		this->Undo_button->Click += gcnew System::EventHandler(this, &GameForm::undoToolStripMenuItem_Click);
		// 
		// Hint_button
		// 
		this->Hint_button->Anchor = System::Windows::Forms::AnchorStyles::None;
		this->Hint_button->BackColor = System::Drawing::SystemColors::Control;
		this->Hint_button->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
		this->Hint_button->Cursor = System::Windows::Forms::Cursors::Hand;
		this->Hint_button->Location = System::Drawing::Point(480, 559);
		this->Hint_button->Name = L"Hint_button";
		this->Hint_button->Size = System::Drawing::Size(100, 25);
		this->Hint_button->TabIndex = 15;
		this->Hint_button->Text = L"Hint";
		this->Hint_button->UseVisualStyleBackColor = false;
		this->Hint_button->Click += gcnew System::EventHandler(this, &GameForm::hintToolStripMenuItem_Click);
		// 
		// Save_menu_button
		// 
		this->Save_menu_button->Anchor = System::Windows::Forms::AnchorStyles::None;
		this->Save_menu_button->BackColor = System::Drawing::SystemColors::Control;
		this->Save_menu_button->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
		this->Save_menu_button->Cursor = System::Windows::Forms::Cursors::Hand;
		this->Save_menu_button->Location = System::Drawing::Point(613, 559);
		this->Save_menu_button->Name = L"Save_menu_button";
		this->Save_menu_button->Size = System::Drawing::Size(100, 25);
		this->Save_menu_button->TabIndex = 16;
		this->Save_menu_button->Text = L"Save";
		this->Save_menu_button->UseVisualStyleBackColor = false;
		this->Save_menu_button->Click += gcnew System::EventHandler(this, &GameForm::saveToolStripMenuItem_Click);
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
		this->Controls->Add(this->save_panel);
		this->Controls->Add(this->Save_menu_button);
		this->Controls->Add(this->Hint_button);
		this->Controls->Add(this->Undo_button);
		this->Controls->Add(this->Redo_button);
		this->Controls->Add(this->time_label);
		this->Controls->Add(this->turns_label);
		this->Controls->Add(this->p1_label_moves);
		this->Controls->Add(this->p1_label_score);
		this->Controls->Add(this->p1_label);
		this->Controls->Add(this->p2_label);
		this->Controls->Add(this->p2_label_moves);
		this->Controls->Add(this->p2_label_score);
		this->Controls->Add(this->main_menu);
		this->Controls->Add(this->p1_icon);
		this->Controls->Add(this->p2_icon);
		this->Controls->Add(this->winnerpanel);
		this->Controls->Add(this->panel1);
		this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
		this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
		this->MaximizeBox = false;
		this->Name = L"GameForm";
		this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
		this->Text = L"GameForm";
		this->save_panel->ResumeLayout(false);
		this->save_panel->PerformLayout();
		this->winnerpanel->ResumeLayout(false);
		this->winnerpanel->PerformLayout();
		this->ResumeLayout(false);

	}
       
#pragma endregion
	

//timer

	String^ sec, ^ min;
	private: System::Void timer_Tick(System::Object^ sender, System::EventArgs^ e) {
		board.Secounds++;
		if (board.Secounds == 60) {
			board.Secounds = 0;
			board.Minutes++;
		}
		sec = Convert::ToString(board.Secounds);
		min = Convert::ToString(board.Minutes);
		time_label->Text = min + ":" + sec;

	}

//return to main menu
	private: System::Void main_menu_Click(System::Object^ sender, System::EventArgs^ e) {
		timer->Enabled = false;
		this->Close();
		turns = 0;
		Reset(&board, &p1, &p2);
		board.Secounds = 0;
		board.Minutes = 0;
	}

//undo
	private: System::Void undoToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		if (board.mode == 0)
			Redo_button->Enabled = true;
		debg("Undo");
		for (int i = 0; i < turns; i++)
			debg(play_stack[i]);
		debg(play_stack[turns]);
		UndoMove(&board, &p1, &p2, play_stack, &turns);
		updatePanel1();
		if (!canUndo(play_stack, turns))
			Undo_button->Enabled = false;
	}

//redo
	private: System::Void redoToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		if (board.mode == 0)
			Undo_button->Enabled = true;
		RedoMove(&board, &p1, &p2, play_stack, &turns);
		updatePanel1();
		if (!canRedo(play_stack, turns))
			Redo_button->Enabled = false;
	}

//save
	private: System::Void saveToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		timer->Enabled = false;
		save_panel->Show();
		save_panel->Location = System::Drawing::Point(250,150);

	}

//save panel ok click
	private: System::Void save_panel_ok_Click(System::Object^ sender, System::EventArgs^ e) {
		auto a = save_box->Text->ToLower()->ToCharArray();

		char name[255];
		int j = 0;
		for (; j < a->Length; j++) {
			name[j] = a[j];
		}
		name[j++] = '\n';
		name[j] = '\0';
		if (GetNoSaved() == 3&&!isBoardExist("games_struct.txt", name)) {
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
			save_box->Text == "";
		}
		timer->Enabled = true;
	}
	
//cancel save panel
	private: System::Void cancel_button_Click(System::Object^ sender, System::EventArgs^ e) {
		timer->Enabled = true;
		save_panel->Hide();
	}
	
//hint
	private: System::Void hintToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {

		if (board.width > 10 || board.height > 10) {
			MessageBox::Show("Sorry can't help with big boards ", "Hint", MessageBoxButtons::OK, MessageBoxIcon::Warning);

		}
		else {

			int bst = best_move(&board, (turns & 1) ? (&p2) : (&p1), (turns & 1) ? (&p1) : (&p2));
			MessageBox::Show("Hmmm,I think best move is column " + System::Convert::ToString(bst) + ", " + ((turns & 1) ? ("Player 2") : ("Player 1")), "Hint", MessageBoxButtons::OK, MessageBoxIcon::Information);

		}
	}

//go to leaderboards
	private: System::Void to_leaderboards_button_Click(System::Object^ sender, System::EventArgs^ e) {

			if (winner_name->Text != "") {
				///Casting
				auto a = winner_name->Text->ToLower()->ToCharArray();
				char name[255];
				int j = 0;
				for (; j < a->Length; j++) {
					name[j] = a[j];
				}
				name[j] = '\0';
				int ret = addScore(name, Max(p1.score, p2.score), "scores.txt");

				debg("Save");
				debg(ret);
			}
			Reset(&board, &p1, &p2);
			winnerpanel->Hide();
			showleaderboard = true;
			this->Close();
	}

	public: bool openleaderboard() {
		return showleaderboard;
	}

//input limitations
	private: System::Void box_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if (save_box->Text->Length > 12 && e->KeyChar != 0x08) {
			e->Handled = true;
		}
	}
	private: System::Void winner_name_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if (winner_name->Text->Length > 12 && e->KeyChar != 0x08) {
			e->Handled = true;
		}
	}
};
}
