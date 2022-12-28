﻿#pragma once
#using <System.Xml.dll>
#include "GameForm.h"

using namespace System::Xml;

namespace Guimain {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			game_size_panel->Hide();
		}

	protected:
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:






	private: System::Windows::Forms::Label^ owrname;
	private: System::Windows::Forms::Panel^ game_size_panel;
	private: System::Windows::Forms::Button^ cancel_game_size;
	private: System::Windows::Forms::Button^ ok_game_size;
	private: System::Windows::Forms::Label^ size_instructions;
	private: System::Windows::Forms::Label^ label_select_custom;
	private: System::Windows::Forms::TextBox^ w_box;
	private: System::Windows::Forms::TextBox^ h_box;
	private: System::Windows::Forms::Label^ selecttext;
	private: System::Windows::Forms::Button^ quit;
	private: System::Windows::Forms::Button^ top_players;
	private: System::Windows::Forms::Button^ load_game;
	private: System::Windows::Forms::Label^ gamename;
	private: System::Windows::Forms::Label^ maintext;
	private: System::Windows::Forms::Button^ start_new;



	private:System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MainForm::typeid));
			this->owrname = (gcnew System::Windows::Forms::Label());
			this->game_size_panel = (gcnew System::Windows::Forms::Panel());
			this->cancel_game_size = (gcnew System::Windows::Forms::Button());
			this->ok_game_size = (gcnew System::Windows::Forms::Button());
			this->size_instructions = (gcnew System::Windows::Forms::Label());
			this->label_select_custom = (gcnew System::Windows::Forms::Label());
			this->w_box = (gcnew System::Windows::Forms::TextBox());
			this->h_box = (gcnew System::Windows::Forms::TextBox());
			this->selecttext = (gcnew System::Windows::Forms::Label());
			this->quit = (gcnew System::Windows::Forms::Button());
			this->top_players = (gcnew System::Windows::Forms::Button());
			this->load_game = (gcnew System::Windows::Forms::Button());
			this->gamename = (gcnew System::Windows::Forms::Label());
			this->maintext = (gcnew System::Windows::Forms::Label());
			this->start_new = (gcnew System::Windows::Forms::Button());
			this->game_size_panel->SuspendLayout();
			this->SuspendLayout();
			// 
			// owrname
			// 
			this->owrname->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			this->owrname->Font = (gcnew System::Drawing::Font(L"Open Sans", 7));
			this->owrname->Location = System::Drawing::Point(200, 575);
			this->owrname->Name = L"owrname";
			this->owrname->Size = System::Drawing::Size(200, 25);
			this->owrname->TabIndex = 3;
			this->owrname->Text = L"Mohamed Nasr and Ahmed Hassan";
			this->owrname->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// game_size_panel
			// 
			this->game_size_panel->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->game_size_panel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->game_size_panel->Controls->Add(this->cancel_game_size);
			this->game_size_panel->Controls->Add(this->ok_game_size);
			this->game_size_panel->Controls->Add(this->size_instructions);
			this->game_size_panel->Controls->Add(this->label_select_custom);
			this->game_size_panel->Controls->Add(this->w_box);
			this->game_size_panel->Controls->Add(this->h_box);
			this->game_size_panel->Controls->Add(this->selecttext);
			this->game_size_panel->Location = System::Drawing::Point(150, 250);
			this->game_size_panel->Name = L"game_size_panel";
			this->game_size_panel->Size = System::Drawing::Size(300, 190);
			this->game_size_panel->TabIndex = 14;
			// 
			// cancel_game_size
			// 
			this->cancel_game_size->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->cancel_game_size->Location = System::Drawing::Point(174, 144);
			this->cancel_game_size->Name = L"cancel_game_size";
			this->cancel_game_size->Size = System::Drawing::Size(50, 20);
			this->cancel_game_size->TabIndex = 15;
			this->cancel_game_size->Text = L"Cancel";
			this->cancel_game_size->UseVisualStyleBackColor = true;
			this->cancel_game_size->Click += gcnew System::EventHandler(this, &MainForm::cancel_game_size_Click);
			// 
			// ok_game_size
			// 
			this->ok_game_size->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->ok_game_size->Location = System::Drawing::Point(74, 144);
			this->ok_game_size->Name = L"ok_game_size";
			this->ok_game_size->Size = System::Drawing::Size(50, 20);
			this->ok_game_size->TabIndex = 14;
			this->ok_game_size->Text = L"OK";
			this->ok_game_size->UseVisualStyleBackColor = true;
			this->ok_game_size->Click += gcnew System::EventHandler(this, &MainForm::ok_game_size_Click);
			// 
			// size_instructions
			// 
			this->size_instructions->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->size_instructions->Location = System::Drawing::Point(73, 122);
			this->size_instructions->Name = L"size_instructions";
			this->size_instructions->Size = System::Drawing::Size(152, 15);
			this->size_instructions->TabIndex = 13;
			this->size_instructions->Text = L"*For default size leave empty*";
			this->size_instructions->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label_select_custom
			// 
			this->label_select_custom->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label_select_custom->AutoSize = true;
			this->label_select_custom->Location = System::Drawing::Point(71, 76);
			this->label_select_custom->Name = L"label_select_custom";
			this->label_select_custom->Size = System::Drawing::Size(107, 13);
			this->label_select_custom->TabIndex = 12;
			this->label_select_custom->Text = L"Select a custom size:";
			// 
			// w_box
			// 
			this->w_box->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->w_box->Location = System::Drawing::Point(154, 95);
			this->w_box->Name = L"w_box";
			this->w_box->Size = System::Drawing::Size(70, 20);
			this->w_box->TabIndex = 11;
			this->w_box->Text = L"  ";
			this->w_box->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->w_box->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::w_box_KeyPress);
			// 
			// h_box
			// 
			this->h_box->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->h_box->Location = System::Drawing::Point(74, 95);
			this->h_box->Name = L"h_box";
			this->h_box->Size = System::Drawing::Size(70, 20);
			this->h_box->TabIndex = 10;
			this->h_box->Text = L"  ";
			this->h_box->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->h_box->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::h_box_KeyPress);
			// 
			// selecttext
			// 
			this->selecttext->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->selecttext->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 30));
			this->selecttext->Location = System::Drawing::Point(37, 14);
			this->selecttext->MinimumSize = System::Drawing::Size(1, 1);
			this->selecttext->Name = L"selecttext";
			this->selecttext->Size = System::Drawing::Size(224, 40);
			this->selecttext->TabIndex = 9;
			this->selecttext->Text = L"Game Size";
			this->selecttext->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// quit
			// 
			this->quit->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->quit->Cursor = System::Windows::Forms::Cursors::Hand;
			this->quit->Location = System::Drawing::Point(225, 414);
			this->quit->MaximumSize = System::Drawing::Size(225, 36);
			this->quit->MinimumSize = System::Drawing::Size(150, 24);
			this->quit->Name = L"quit";
			this->quit->Size = System::Drawing::Size(150, 24);
			this->quit->TabIndex = 20;
			this->quit->Text = L"Quit";
			this->quit->UseVisualStyleBackColor = true;
			this->quit->Click += gcnew System::EventHandler(this, &MainForm::quit_Click);
			// 
			// top_players
			// 
			this->top_players->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->top_players->Cursor = System::Windows::Forms::Cursors::Hand;
			this->top_players->Location = System::Drawing::Point(225, 384);
			this->top_players->MaximumSize = System::Drawing::Size(225, 36);
			this->top_players->MinimumSize = System::Drawing::Size(150, 24);
			this->top_players->Name = L"top_players";
			this->top_players->Size = System::Drawing::Size(150, 24);
			this->top_players->TabIndex = 19;
			this->top_players->Text = L"Top Players";
			this->top_players->UseVisualStyleBackColor = true;
			// 
			// load_game
			// 
			this->load_game->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->load_game->Cursor = System::Windows::Forms::Cursors::Hand;
			this->load_game->Location = System::Drawing::Point(225, 354);
			this->load_game->MaximumSize = System::Drawing::Size(225, 36);
			this->load_game->MinimumSize = System::Drawing::Size(150, 24);
			this->load_game->Name = L"load_game";
			this->load_game->Size = System::Drawing::Size(150, 24);
			this->load_game->TabIndex = 18;
			this->load_game->Text = L"Load Game";
			this->load_game->UseVisualStyleBackColor = true;
			// 
			// gamename
			// 
			this->gamename->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->gamename->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10));
			this->gamename->Location = System::Drawing::Point(188, 225);
			this->gamename->Name = L"gamename";
			this->gamename->Size = System::Drawing::Size(224, 25);
			this->gamename->TabIndex = 17;
			this->gamename->Text = L"~~~~~~ Connect Four ~~~~~~";
			this->gamename->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// maintext
			// 
			this->maintext->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->maintext->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 38.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->maintext->Location = System::Drawing::Point(150, 165);
			this->maintext->MinimumSize = System::Drawing::Size(1, 1);
			this->maintext->Name = L"maintext";
			this->maintext->Size = System::Drawing::Size(300, 62);
			this->maintext->TabIndex = 16;
			this->maintext->Text = L"Main Menu";
			this->maintext->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// start_new
			// 
			this->start_new->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->start_new->Cursor = System::Windows::Forms::Cursors::Hand;
			this->start_new->Location = System::Drawing::Point(225, 324);
			this->start_new->MaximumSize = System::Drawing::Size(225, 36);
			this->start_new->MinimumSize = System::Drawing::Size(150, 24);
			this->start_new->Name = L"start_new";
			this->start_new->Size = System::Drawing::Size(150, 24);
			this->start_new->TabIndex = 15;
			this->start_new->Text = L"Start New";
			this->start_new->UseVisualStyleBackColor = true;
			this->start_new->Click += gcnew System::EventHandler(this, &MainForm::start_new_Click);
			// 
			// MainForm
			// 
			this->ClientSize = System::Drawing::Size(600, 600);
			this->ControlBox = false;
			this->Controls->Add(this->game_size_panel);
			this->Controls->Add(this->quit);
			this->Controls->Add(this->top_players);
			this->Controls->Add(this->load_game);
			this->Controls->Add(this->gamename);
			this->Controls->Add(this->maintext);
			this->Controls->Add(this->start_new);
			this->Controls->Add(this->owrname);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MinimumSize = System::Drawing::Size(500, 500);
			this->Name = L"MainForm";
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Main Menu";
			this->game_size_panel->ResumeLayout(false);
			this->game_size_panel->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

//quit game
	private: System::Void quit_Click(System::Object^ sender, System::EventArgs^ e) {
		if (MessageBox::Show("Are you sure you want to quit?", "Quit", MessageBoxButtons::YesNo, MessageBoxIcon::Warning) == System::Windows::Forms::DialogResult::Yes) {
			Application::Exit();
		}
	}

//generate size panel
	private: System::Void start_new_Click(System::Object^ sender, System::EventArgs^ e) {
		game_size_panel->Show();
		game_size_panel->Location = System::Drawing::Point(150, 250);
	}

//start game form
	private: System::Void ok_game_size_Click(System::Object^ sender, System::EventArgs^ e) {
		int height, width;
		try {
			height = System::Convert::ToInt16(h_box->Text);
			width = System::Convert::ToInt16(w_box->Text);
		}
		catch (...) {
			height = 9;
			width = 7;
		}
		if (height < 4 || width < 4) {
			MessageBox::Show("Invalid dimensions", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		else {
			MainForm::Visible = false;
			GameForm^ gameform = gcnew GameForm(height,width);
			gameform->ShowDialog();
			if (! (gameform->Visible) ){ MainForm::Visible = true; }
		}
	}

//cancel size panel
	private: System::Void cancel_game_size_Click(System::Object^ sender, System::EventArgs^ e) {
		game_size_panel->Hide();
	}

//textbox only accepts digits
	private: System::Void h_box_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		// Accept only digits
		if (!Char::IsDigit(e->KeyChar) && e->KeyChar != 0x08) {
			e->Handled = true;
		}
	}

	private: System::Void w_box_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if (!Char::IsDigit(e->KeyChar) && e->KeyChar != 0x08) {
			e->Handled = true;
		}
	}
};

}