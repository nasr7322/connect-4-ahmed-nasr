 #pragma once
#using <System.Xml.dll>
#include "GameForm.h"
#include <windows.h>

int errors = 0;
int xmlv;
int height=0,width=0,Highscores=0;

using namespace System::Xml;

namespace Guimain {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Xml;

	public ref class MainForm : public System::Windows::Forms::Form
	{

		void debg(Object^ O) {
			String^ s = System::Convert::ToString(O);
			auto a = s->ToCharArray();

			char name[255];
			int j = 0;
			for (;j < a->Length;j++) {
				name[j] = a[j];
			}
			name[j] = '\0';
			OutputDebugStringA(name);
			OutputDebugStringA("\n");
		}
		Void button_Click(System::Object^ sender, System::EventArgs^ e) {
			Button^ clicked = (Button^)sender;
			///int ret = PlayerMove(&board, (turns & 1) ? (&p2) : (&p1), System::Convert::ToInt32(clicked->Tag));
			Board B;
			Player P1, P2;
			String^ s = System::Convert::ToString(clicked->Tag);
			auto a=s->ToCharArray();

			char name[255];
			int j = 0;
			for (;j < a->Length;j++) {
				name[j] = a[j];
			}
			name[j] = '\0';
			///OutputDebugStringA("Gme name\n");
			///OutputDebugStringA(name);
			P1.score = P2.score = P1.turns_played = P2.turns_played = 0;
			P1.id = 1;
			P2.id = 2;
			LoadGame(&B, &P1, &P2, &turns, "games_struct.txt",name );

			debg(P1.score);
			debg(P1.turns_played);
			MainForm::Visible = false;
			GameForm^ gameform = gcnew GameForm(height, width, B, P1, P2);
			gameform->ShowDialog();
			if (!(gameform->Visible)) { MainForm::Visible = true; }
			game_size_panel->Hide();
		}

		void renderGames() {
			FILE* fgames;///names file
			fgames = fopen("games.txt", "r");
			if (!fgames)return;

			char buffer[255];
			int nosaved = GetNoSaved();
			for (int i = 0;i < nosaved;i++) {
				fgets(buffer, 255, fgames);
				Button^ button = gcnew System::Windows::Forms::Button;
				String^ s=gcnew String(buffer);

				button->Height = 20 ;
				button->Width = 80 ;
				button->Left = 112 ;
				button->Top = 130+(i*(button->Height)) ;
				button->Text = s;
				button->Tag =s;
				button->Click += gcnew EventHandler(this, &MainForm::button_Click);
				load_panel->Controls->Add(button);
			}
			fclose(fgames);
		}
	public:
		MainForm(void)
		{
			InitializeComponent();
			game_size_panel->Hide();
			load_panel->Hide();
			gane_mode_panel->Hide();


			renderGames();
		}

	protected:
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}

	void readxml(XmlTextReader^ reader) {
		while (reader->Read())
		{
			if ((reader->NodeType == XmlNodeType::Element)) {
				xmllistBox->Items->Add(reader->Name);
				if (reader->Name == "Height") { xmlv = 1; }
				if (reader->Name == "Width") { xmlv = 2; }
				if (reader->Name == "Highscores") { xmlv = 3; }
			}

			if ((reader->NodeType == XmlNodeType::Text)) {
				xmllistBox->Items->Add(reader->Value);
				if (xmlv == 1) { height = System::Convert::ToInt16(reader->Value); }
				if (xmlv == 2) { width = System::Convert::ToInt16(reader->Value); }
				if (xmlv == 3) { Highscores = System::Convert::ToInt16(reader->Value); }
			}
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
	private: System::Windows::Forms::Panel^ scores_panel;
	private: System::Windows::Forms::Button^ scores_cancel;
	private: System::Windows::Forms::Button^ scores_ok;
	private: System::Windows::Forms::Label^ scores_label2;
	private: System::Windows::Forms::Label^ scores_label1;
	private: System::Windows::Forms::TextBox^ scores_count_box;
	private: System::Windows::Forms::Label^ scores;
	private: System::Windows::Forms::Button^ getxmldata_button;
	private: System::Windows::Forms::ListBox^ listBox;
	private: System::Windows::Forms::Label^ xml_instructions;
	private: System::Windows::Forms::CheckBox^ xml_check;
	private: System::Windows::Forms::Panel^ xml_panel;
	private: System::Windows::Forms::Panel^ load_panel;
	private: System::Windows::Forms::Label^ load_label;
	private: System::Windows::Forms::Label^ label4;


	private: System::Windows::Forms::ListBox^ xmllistBox;

	private:System::ComponentModel::Container^ components;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Label^ label3;
private: System::Windows::Forms::Panel^ gane_mode_panel;
private: System::Windows::Forms::Button^ two_mode_button;
private: System::Windows::Forms::Button^ bot_mode_button;
private: System::Windows::Forms::Label^ mode_label;
private: System::Windows::Forms::Button^ cancel_load;
	private: System::Windows::Forms::Button^ button3;

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
			this->scores_panel = (gcnew System::Windows::Forms::Panel());
			this->scores_cancel = (gcnew System::Windows::Forms::Button());
			this->scores_ok = (gcnew System::Windows::Forms::Button());
			this->scores_label2 = (gcnew System::Windows::Forms::Label());
			this->scores_label1 = (gcnew System::Windows::Forms::Label());
			this->scores_count_box = (gcnew System::Windows::Forms::TextBox());
			this->scores = (gcnew System::Windows::Forms::Label());
			this->getxmldata_button = (gcnew System::Windows::Forms::Button());
			this->xml_instructions = (gcnew System::Windows::Forms::Label());
			this->xml_check = (gcnew System::Windows::Forms::CheckBox());
			this->xml_panel = (gcnew System::Windows::Forms::Panel());
			this->xmllistBox = (gcnew System::Windows::Forms::ListBox());
			this->load_panel = (gcnew System::Windows::Forms::Panel());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->load_label = (gcnew System::Windows::Forms::Label());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->gane_mode_panel = (gcnew System::Windows::Forms::Panel());
			this->two_mode_button = (gcnew System::Windows::Forms::Button());
			this->bot_mode_button = (gcnew System::Windows::Forms::Button());
			this->mode_label = (gcnew System::Windows::Forms::Label());
			this->cancel_load = (gcnew System::Windows::Forms::Button());
			this->game_size_panel->SuspendLayout();
			this->scores_panel->SuspendLayout();
			this->xml_panel->SuspendLayout();
			this->load_panel->SuspendLayout();
			this->panel1->SuspendLayout();
			this->gane_mode_panel->SuspendLayout();
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
			this->game_size_panel->Location = System::Drawing::Point(318, 12);
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
			this->label_select_custom->Size = System::Drawing::Size(141, 17);
			this->label_select_custom->TabIndex = 12;
			this->label_select_custom->Text = L"Select a custom size:";
			// 
			// w_box
			// 
			this->w_box->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->w_box->Location = System::Drawing::Point(154, 95);
			this->w_box->Name = L"w_box";
			this->w_box->Size = System::Drawing::Size(70, 22);
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
			this->h_box->Size = System::Drawing::Size(70, 22);
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
			this->quit->Location = System::Drawing::Point(225, 443);
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
			this->top_players->Location = System::Drawing::Point(225, 413);
			this->top_players->MaximumSize = System::Drawing::Size(225, 36);
			this->top_players->MinimumSize = System::Drawing::Size(150, 24);
			this->top_players->Name = L"top_players";
			this->top_players->Size = System::Drawing::Size(150, 24);
			this->top_players->TabIndex = 19;
			this->top_players->Text = L"Top Players";
			this->top_players->UseVisualStyleBackColor = true;
			this->top_players->Click += gcnew System::EventHandler(this, &MainForm::top_players_Click);
			// 
			// load_game
			// 
			this->load_game->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->load_game->Cursor = System::Windows::Forms::Cursors::Hand;
			this->load_game->Location = System::Drawing::Point(225, 383);
			this->load_game->MaximumSize = System::Drawing::Size(225, 36);
			this->load_game->MinimumSize = System::Drawing::Size(150, 24);
			this->load_game->Name = L"load_game";
			this->load_game->Size = System::Drawing::Size(150, 24);
			this->load_game->TabIndex = 18;
			this->load_game->Text = L"Load Game";
			this->load_game->UseVisualStyleBackColor = true;
			this->load_game->Click += gcnew System::EventHandler(this, &MainForm::load_game_Click);
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
			// scores_panel
			// 
			this->scores_panel->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->scores_panel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->scores_panel->Controls->Add(this->scores_cancel);
			this->scores_panel->Controls->Add(this->scores_ok);
			this->scores_panel->Controls->Add(this->scores_label2);
			this->scores_panel->Controls->Add(this->scores_label1);
			this->scores_panel->Controls->Add(this->scores_count_box);
			this->scores_panel->Controls->Add(this->scores);
			this->scores_panel->Location = System::Drawing::Point(12, 12);
			this->scores_panel->Name = L"scores_panel";
			this->scores_panel->Size = System::Drawing::Size(300, 190);
			this->scores_panel->TabIndex = 16;
			this->scores_panel->Visible = false;
			// 
			// scores_cancel
			// 
			this->scores_cancel->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->scores_cancel->Location = System::Drawing::Point(174, 144);
			this->scores_cancel->Name = L"scores_cancel";
			this->scores_cancel->Size = System::Drawing::Size(50, 20);
			this->scores_cancel->TabIndex = 15;
			this->scores_cancel->Text = L"Cancel";
			this->scores_cancel->UseVisualStyleBackColor = true;
			this->scores_cancel->Click += gcnew System::EventHandler(this, &MainForm::scores_cancel_Click);
			// 
			// scores_ok
			// 
			this->scores_ok->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->scores_ok->Location = System::Drawing::Point(74, 144);
			this->scores_ok->Name = L"scores_ok";
			this->scores_ok->Size = System::Drawing::Size(50, 20);
			this->scores_ok->TabIndex = 14;
			this->scores_ok->Text = L"OK";
			this->scores_ok->UseVisualStyleBackColor = true;
			this->scores_ok->Click += gcnew System::EventHandler(this, &MainForm::scores_ok_Click);
			// 
			// scores_label2
			// 
			this->scores_label2->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->scores_label2->Location = System::Drawing::Point(73, 122);
			this->scores_label2->Name = L"scores_label2";
			this->scores_label2->Size = System::Drawing::Size(152, 15);
			this->scores_label2->TabIndex = 13;
			this->scores_label2->Text = L"*For default size leave empty*";
			this->scores_label2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// scores_label1
			// 
			this->scores_label1->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->scores_label1->AutoSize = true;
			this->scores_label1->Location = System::Drawing::Point(71, 76);
			this->scores_label1->Name = L"scores_label1";
			this->scores_label1->Size = System::Drawing::Size(171, 17);
			this->scores_label1->TabIndex = 12;
			this->scores_label1->Text = L"select a number of scores";
			// 
			// scores_count_box
			// 
			this->scores_count_box->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->scores_count_box->Location = System::Drawing::Point(74, 95);
			this->scores_count_box->Name = L"scores_count_box";
			this->scores_count_box->Size = System::Drawing::Size(150, 22);
			this->scores_count_box->TabIndex = 10;
			this->scores_count_box->Text = L"  ";
			this->scores_count_box->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			this->scores_count_box->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::scores_count_box_KeyPress);
			// 
			// scores
			// 
			this->scores->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->scores->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 30));
			this->scores->Location = System::Drawing::Point(37, 14);
			this->scores->MinimumSize = System::Drawing::Size(1, 1);
			this->scores->Name = L"scores";
			this->scores->Size = System::Drawing::Size(224, 40);
			this->scores->TabIndex = 9;
			this->scores->Text = L"Scores";
			this->scores->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// getxmldata_button
			// 
			this->getxmldata_button->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->getxmldata_button->Cursor = System::Windows::Forms::Cursors::Hand;
			this->getxmldata_button->Location = System::Drawing::Point(225, 353);
			this->getxmldata_button->MaximumSize = System::Drawing::Size(225, 36);
			this->getxmldata_button->MinimumSize = System::Drawing::Size(150, 24);
			this->getxmldata_button->Name = L"getxmldata_button";
			this->getxmldata_button->Size = System::Drawing::Size(150, 24);
			this->getxmldata_button->TabIndex = 21;
			this->getxmldata_button->Text = L"Get XML Data";
			this->getxmldata_button->UseVisualStyleBackColor = true;
			this->getxmldata_button->Click += gcnew System::EventHandler(this, &MainForm::button3_Click);
			// 
			// xml_instructions
			// 
			this->xml_instructions->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->xml_instructions->Location = System::Drawing::Point(5, 9);
			this->xml_instructions->Name = L"xml_instructions";
			this->xml_instructions->Size = System::Drawing::Size(179, 32);
			this->xml_instructions->TabIndex = 23;
			this->xml_instructions->Text = L"If a corrupted file is loaded 3 times the default XML will be used.";
			// 
			// xml_check
			// 
			this->xml_check->AutoSize = true;
			this->xml_check->Checked = true;
			this->xml_check->CheckState = System::Windows::Forms::CheckState::Checked;
			this->xml_check->Location = System::Drawing::Point(7, 133);
			this->xml_check->Name = L"xml_check";
			this->xml_check->Size = System::Drawing::Size(132, 21);
			this->xml_check->TabIndex = 24;
			this->xml_check->Text = L"Use XML values";
			this->xml_check->UseVisualStyleBackColor = true;
			// 
			// xml_panel
			// 
			this->xml_panel->Controls->Add(this->xmllistBox);
			this->xml_panel->Controls->Add(this->xml_check);
			this->xml_panel->Controls->Add(this->xml_instructions);
			this->xml_panel->Location = System::Drawing::Point(388, 316);
			this->xml_panel->Name = L"xml_panel";
			this->xml_panel->Size = System::Drawing::Size(192, 151);
			this->xml_panel->TabIndex = 25;
			this->xml_panel->Visible = false;
			// 
			// xmllistBox
			// 
			this->xmllistBox->FormattingEnabled = true;
			this->xmllistBox->ItemHeight = 16;
			this->xmllistBox->Location = System::Drawing::Point(10, 45);
			this->xmllistBox->Name = L"xmllistBox";
			this->xmllistBox->Size = System::Drawing::Size(173, 68);
			this->xmllistBox->TabIndex = 25;
			// 
			// load_panel
			// 
			this->load_panel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->load_panel->Controls->Add(this->cancel_load);
			this->load_panel->Controls->Add(this->label4);
			this->load_panel->Controls->Add(this->load_label);
			this->load_panel->Location = System::Drawing::Point(112, 230);
			this->load_panel->Name = L"load_panel";
			this->load_panel->Size = System::Drawing::Size(338, 252);
			this->load_panel->TabIndex = 26;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(110, 74);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(111, 17);
			this->label4->TabIndex = 2;
			this->label4->Text = L"Available games";
			// 
			// load_label
			// 
			this->load_label->AutoSize = true;
			this->load_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 30, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->load_label->Location = System::Drawing::Point(25, 13);
			this->load_label->Name = L"load_label";
			this->load_label->Size = System::Drawing::Size(287, 58);
			this->load_label->TabIndex = 0;
			this->load_label->Text = L"Load Game";
			// 
			// panel1
			// 
			this->panel1->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->panel1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panel1->Controls->Add(this->button1);
			this->panel1->Controls->Add(this->button2);
			this->panel1->Controls->Add(this->label1);
			this->panel1->Controls->Add(this->label2);
			this->panel1->Controls->Add(this->textBox2);
			this->panel1->Controls->Add(this->label3);
			this->panel1->Location = System::Drawing::Point(12, 12);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(300, 190);
			this->panel1->TabIndex = 16;
			// 
			// button1
			// 
			this->button1->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->button1->Location = System::Drawing::Point(223, 188);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(50, 20);
			this->button1->TabIndex = 15;
			this->button1->Text = L"Cancel";
			this->button1->UseVisualStyleBackColor = true;
			// 
			// button2
			// 
			this->button2->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->button2->Location = System::Drawing::Point(123, 188);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(50, 20);
			this->button2->TabIndex = 14;
			this->button2->Text = L"OK";
			this->button2->UseVisualStyleBackColor = true;
			// 
			// label1
			// 
			this->label1->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label1->Location = System::Drawing::Point(122, 166);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(152, 15);
			this->label1->TabIndex = 13;
			this->label1->Text = L"*For default size leave empty*";
			this->label1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// label2
			// 
			this->label2->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(120, 120);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(171, 17);
			this->label2->TabIndex = 12;
			this->label2->Text = L"select a number of scores";
			// 
			// textBox2
			// 
			this->textBox2->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->textBox2->Location = System::Drawing::Point(123, 139);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(150, 22);
			this->textBox2->TabIndex = 10;
			this->textBox2->Text = L"  ";
			this->textBox2->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// label3
			// 
			this->label3->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 30));
			this->label3->Location = System::Drawing::Point(86, 58);
			this->label3->MinimumSize = System::Drawing::Size(1, 1);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(224, 40);
			this->label3->TabIndex = 9;
			this->label3->Text = L"Scores";
			this->label3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// button3
			// 
			this->button3->Anchor = System::Windows::Forms::AnchorStyles::None;
			this->button3->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button3->Location = System::Drawing::Point(225, 353);
			this->button3->MaximumSize = System::Drawing::Size(225, 36);
			this->button3->MinimumSize = System::Drawing::Size(150, 24);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(150, 24);
			this->button3->TabIndex = 21;
			this->button3->Text = L"Get XML Data";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MainForm::button3_Click);
			// 
			// gane_mode_panel
			// 
			this->gane_mode_panel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->gane_mode_panel->Controls->Add(this->two_mode_button);
			this->gane_mode_panel->Controls->Add(this->bot_mode_button);
			this->gane_mode_panel->Controls->Add(this->mode_label);
			this->gane_mode_panel->Location = System::Drawing::Point(38, 361);
			this->gane_mode_panel->Name = L"gane_mode_panel";
			this->gane_mode_panel->Size = System::Drawing::Size(374, 230);
			this->gane_mode_panel->TabIndex = 27;
			// 
			// two_mode_button
			// 
			this->two_mode_button->Location = System::Drawing::Point(70, 152);
			this->two_mode_button->Name = L"two_mode_button";
			this->two_mode_button->Size = System::Drawing::Size(225, 35);
			this->two_mode_button->TabIndex = 2;
			this->two_mode_button->Text = L"Two players Mode";
			this->two_mode_button->UseVisualStyleBackColor = true;
			this->two_mode_button->Click += gcnew System::EventHandler(this, &MainForm::two_mode_button_Click);
			// 
			// bot_mode_button
			// 
			this->bot_mode_button->Location = System::Drawing::Point(72, 81);
			this->bot_mode_button->Name = L"bot_mode_button";
			this->bot_mode_button->Size = System::Drawing::Size(223, 41);
			this->bot_mode_button->TabIndex = 1;
			this->bot_mode_button->Text = L"Bot Mode";
			this->bot_mode_button->UseVisualStyleBackColor = true;
			this->bot_mode_button->Click += gcnew System::EventHandler(this, &MainForm::bot_mode_button_Click);
			// 
			// mode_label
			// 
			this->mode_label->AutoSize = true;
			this->mode_label->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 30, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->mode_label->Location = System::Drawing::Point(15, 11);
			this->mode_label->Name = L"mode_label";
			this->mode_label->Size = System::Drawing::Size(337, 58);
			this->mode_label->TabIndex = 0;
			this->mode_label->Text = L"Choose Mode";
			// 
			// cancel_load
			// 
			this->cancel_load->Location = System::Drawing::Point(90, 216);
			this->cancel_load->Name = L"cancel_load";
			this->cancel_load->Size = System::Drawing::Size(163, 22);
			this->cancel_load->TabIndex = 3;
			this->cancel_load->Text = L"Cancel";
			this->cancel_load->UseVisualStyleBackColor = true;
			this->cancel_load->Click += gcnew System::EventHandler(this, &MainForm::cancel_load_Click);
			// 
			// MainForm
			// 
			this->ClientSize = System::Drawing::Size(600, 600);
			this->ControlBox = false;
			this->Controls->Add(this->gane_mode_panel);
			this->Controls->Add(this->load_panel);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->scores_panel);
			this->Controls->Add(this->game_size_panel);
			this->Controls->Add(this->quit);
			this->Controls->Add(this->top_players);
			this->Controls->Add(this->load_game);
			this->Controls->Add(this->gamename);
			this->Controls->Add(this->maintext);
			this->Controls->Add(this->start_new);
			this->Controls->Add(this->owrname);
			this->Controls->Add(this->getxmldata_button);
			this->Controls->Add(this->xml_panel);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MinimumSize = System::Drawing::Size(500, 500);
			this->Name = L"MainForm";
			this->SizeGripStyle = System::Windows::Forms::SizeGripStyle::Hide;
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Main Menu";
			this->game_size_panel->ResumeLayout(false);
			this->game_size_panel->PerformLayout();
			this->scores_panel->ResumeLayout(false);
			this->scores_panel->PerformLayout();
			this->xml_panel->ResumeLayout(false);
			this->xml_panel->PerformLayout();
			this->load_panel->ResumeLayout(false);
			this->load_panel->PerformLayout();
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->gane_mode_panel->ResumeLayout(false);
			this->gane_mode_panel->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

//quit game
	private: System::Void quit_Click(System::Object^ sender, System::EventArgs^ e) {
		if (MessageBox::Show("Are you sure you want to quit?", "Quit", MessageBoxButtons::YesNo, MessageBoxIcon::Warning) == System::Windows::Forms::DialogResult::Yes) {
			Application::Exit();
		}
	}

//start game button
	private: System::Void start_new_Click(System::Object^ sender, System::EventArgs^ e) {
		if (xml_check->Checked && !(xmllistBox->Items->Count == 0)) { start_game(sender, e); }
		else {
			xmllistBox->Items->Clear();
			game_size_panel->Show();
			game_size_panel->Location = System::Drawing::Point(150, 250);
		}
	
	}

//check validity of dimentions and starts the game
	public: System::Void start_game(System::Object^ sender, System::EventArgs^ e) {

		if (height < 4 || width < 4 || height >20 || width >20) {
			MessageBox::Show("Invalid dimensions", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		else {
			game_size_panel->Hide();
			
			gane_mode_panel->Show();/**
			Board B;
			Player P1, P2;
			B.width = 0;
			MainForm::Visible = false;
			GameForm^ gameform = gcnew GameForm(height, width,B,P1,P2);
			gameform->ShowDialog();
			if (!(gameform->Visible)) { MainForm::Visible = true; }
			*/
		}
	}

//start game from size panel
	private: System::Void ok_game_size_Click(System::Object^ sender, System::EventArgs^ e) {
		
		try {
			height = System::Convert::ToInt16(h_box->Text);
			width = System::Convert::ToInt16(w_box->Text);
		}
		catch (...) {
			height = 9;
			width = 7;
		}
		start_game(sender,e);
	}

//cancel size panel
	private: System::Void cancel_game_size_Click(System::Object^ sender, System::EventArgs^ e) {
		game_size_panel->Hide();
		
	}

//textboxs only accepts digits
	private: System::Void h_box_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if (!Char::IsDigit(e->KeyChar) && e->KeyChar != 0x08) {
			e->Handled = true;
		}
	}
	private: System::Void w_box_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if (!Char::IsDigit(e->KeyChar) && e->KeyChar != 0x08) {
			e->Handled = true;
		}
	}
	private: System::Void scores_count_box_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
		if (!Char::IsDigit(e->KeyChar) && e->KeyChar != 0x08) {
			e->Handled = true;
		}
	}
//reading xml files
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		xmllistBox->Items->Clear();
		xml_panel->Visible = true;
		OpenFileDialog^ openfiledialog = gcnew OpenFileDialog;
		XmlTextReader^ reader;
		if(openfiledialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			try {
				reader = gcnew XmlTextReader(openfiledialog->FileName);
				readxml(reader);
			}
			catch (...) {
				if (errors == 2) {
					xmllistBox->Items->Clear();
					reader = gcnew XmlTextReader("default.xml");
					readxml(reader);
					MessageBox::Show("3 corrupted files in a row. the default configurations are now loaded.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
					errors = 0;
				}
				else {
					MessageBox::Show("corrupted file", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
					xmllistBox->Items->Clear();
					errors++;
				}
			}
	}
}

private: System::Void top_players_Click(System::Object^ sender, System::EventArgs^ e) {
	scores_panel->Show();
	scores_panel->Location = System::Drawing::Point(150, 250);
}
private: System::Void scores_cancel_Click(System::Object^ sender, System::EventArgs^ e) {
	scores_panel->Hide();
}
private: System::Void scores_ok_Click(System::Object^ sender, System::EventArgs^ e) {
	if (xml_check->Checked && !(xmllistBox->Items->Count == 0)) { loadhighscores(sender, e); }
	else {
		try {
			Highscores = System::Convert::ToInt16(scores_count_box->Text);
		}
		catch (...) {
			Highscores = 10;
		}
		loadhighscores(sender, e);
	}
}
	public: System::Void loadhighscores(System::Object^ sender, System::EventArgs^ e) {

		if (Highscores < 4 ) {
			MessageBox::Show("Invalid input", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
		else {
			scores_panel->Hide();
			MainForm::Visible = false;
			Board B;
			Player P1, P2;
			B.width = 0;
			GameForm^ gameform = gcnew GameForm(height, width, B, P1, P2);
			gameform->ShowDialog();
			if (!(gameform->Visible)) { MainForm::Visible = true; }
		}
	}

private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void load_game_Click(System::Object^ sender, System::EventArgs^ e) {
	/**
	Board B;
	Player P1, P2;
	LoadGame(&B, &P1, &P2, &turns,"games_struct.txt","G1\n");
	
	MainForm::Visible = false;
	GameForm^ gameform = gcnew GameForm(height, width, B, P1, P2);
	gameform->ShowDialog();
	if (!(gameform->Visible)) { MainForm::Visible = true; }
	game_size_panel->Hide();*/
	load_panel->Show();

}
private: System::Void two_mode_button_Click(System::Object^ sender, System::EventArgs^ e) {
	gane_mode_panel->Hide();
	Board B;
	Player P1, P2;
	B.width = 0;
	B.mode = 0;
	MainForm::Visible = false;
	GameForm^ gameform = gcnew GameForm(height, width, B, P1, P2);
	gameform->ShowDialog();
	if (!(gameform->Visible)) { MainForm::Visible = true; }
}
private: System::Void bot_mode_button_Click(System::Object^ sender, System::EventArgs^ e) {
	if (width > 10 || height > 10) {
		MessageBox::Show("Sorry bot can't play in big boards ", "Warning", MessageBoxButtons::OK, MessageBoxIcon::Warning);
	}
	else {

		gane_mode_panel->Hide();
		Board B;
		Player P1, P2;
		B.width = 0;
		B.mode = 1;
		MainForm::Visible = false;
		GameForm^ gameform = gcnew GameForm(height, width, B, P1, P2);
		gameform->ShowDialog();
		if (!(gameform->Visible)) { MainForm::Visible = true; }

	}
}
private: System::Void cancel_load_Click(System::Object^ sender, System::EventArgs^ e) {
	load_panel->Hide();
}
};

}
