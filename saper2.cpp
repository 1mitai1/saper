#include <string.h>
#include <iostream>
#include <ctime>
#include <SFML/Graphics.hpp>
#include <locale>
#include <sstream>
#include <fstream>


using namespace std;
using namespace sf;

class game
{
protected:
	int bomb_number;
	int size;
	int lose;
	int game_time;
public:
	int get_size()
	{
		return size;
	}
	game()
	{
		bomb_number = 0;
		size = 0;
		lose = 0;
		game_time = 0;
	}
	game(int b)
	{
		size = 15;
		bomb_number = b;
		lose = 0;
		game_time = 0;
	}
	friend class miner;

};

class cell : public game
{
public:
	bool bomb;
	int bombs;
	int open;
public:
	cell() :game()
	{
		bomb = 0;
		bombs = 0;
		open = 0;
	}
};

class field :public game
{
protected:
	cell** game_field;
	int** field_gr;
public:
	field()
	{
		game_field = nullptr;
		field_gr = nullptr;
	}
	field(int b) :game(b)
	{
		game_field = new cell * [size];
		for (int i = 0; i < size; i++)
		{
			game_field[i] = new cell[size];
		}
		field_gr = new int* [size];
		for (int i = 0; i < size; i++)
		{
			field_gr[i] = new int[size];
		}
		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				field_gr[i][j] = 10;
	}
	void show_bomb()
	{
		cout << endl;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				cout << " " << game_field[i][j].bomb << " ";
			}
			cout << endl;
		}
	}
	void show_bombs()
	{
		cout << endl;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				cout << " " << game_field[i][j].bombs << " ";
			}
			cout << endl;
		}
	}
	void show_open()
	{
		cout << endl;
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				cout << " " << game_field[i][j].open << " ";
			}
			cout << endl;
		}
	}
};
void open(cell** field, int** f, int i, int j);
class miner :public field
{
	int x;
public:
	miner()
	{
		x = 0;
	}
	miner(int b) :field(b)
	{
		x = bomb_number;
	}
	void miner_field()
	{
		while (x != 0)
		{
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					fflush(stdin);
					int t_f = rand() % 100;
					if (t_f < 15 && game_field[i][j].bomb == 0)
					{
						game_field[i][j].bomb = 1;
						x--;
						t_f = 0;
						if (x == 0)
							break;
					}
					if (x == 0)
						break;
				}
				if (x == 0)
					break;
			}
			if (x == 0)
				break;
		}
	}
	void bomo_around()
	{

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (i == 0 && j == 0)
				{
					if (game_field[i][j + 1].bomb == 1)
						game_field[i][j].bombs++;
					if (game_field[i + 1][j + 1].bomb == 1)
						game_field[i][j].bombs++;
					if (game_field[i + 1][j].bomb == 1)
						game_field[i][j].bombs++;
				}
				if (i == 0 && j == size - 1)
				{
					if (game_field[i + 1][j].bomb == 1)
						game_field[i][j].bombs++;
					if (game_field[i + 1][j - 1].bomb == 1)
						game_field[i][j].bombs++;
					if (game_field[i][j - 1].bomb == 1)
						game_field[i][j].bombs++;
				}

				if (i == size - 1 && j == size - 1)
				{
					if (game_field[i - 1][j].bomb == 1)
						game_field[i][j].bombs++;
					if (game_field[i - 1][j - 1].bomb == 1)
						game_field[i][j].bombs++;
					if (game_field[i][j - 1].bomb == 1)
						game_field[i][j].bombs++;
				}
				if (i == size - 1 && j == 0)
				{
					if (game_field[i - 1][j].bomb == 1)
						game_field[i][j].bombs++;
					if (game_field[i - 1][j + 1].bomb == 1)
						game_field[i][j].bombs++;
					if (game_field[i][j + 1].bomb == 1)
						game_field[i][j].bombs++;
				}
				if (i == 0 && j > 0 && j < size - 1)
				{
					if (game_field[i + 1][j].bomb == 1)
						game_field[i][j].bombs++;
					if (game_field[i + 1][j + 1].bomb == 1)
						game_field[i][j].bombs++;
					if (game_field[i][j + 1].bomb == 1)
						game_field[i][j].bombs++;
					if (game_field[i][j - 1].bomb == 1)
						game_field[i][j].bombs++;
					if (game_field[i + 1][j - 1].bomb == 1)
						game_field[i][j].bombs++;
				}
				if (i == size - 1 && j > 0 && j < size - 1)
				{
					if (game_field[i][j + 1].bomb == 1)
						game_field[i][j].bombs++;
					if (game_field[i][j - 1].bomb == 1)
						game_field[i][j].bombs++;
					if (game_field[i - 1][j + 1].bomb == 1)
						game_field[i][j].bombs++;
					if (game_field[i - 1][j - 1].bomb == 1)
						game_field[i][j].bombs++;
					if (game_field[i - 1][j].bomb == 1)
						game_field[i][j].bombs++;
				}
				if (j == size - 1 && i > 0 && i < size - 1)
				{
					if (game_field[i - 1][j].bomb == 1)
						game_field[i][j].bombs++;
					if (game_field[i - 1][j - 1].bomb == 1)
						game_field[i][j].bombs++;
					if (game_field[i][j - 1].bomb == 1)
						game_field[i][j].bombs++;
					if (game_field[i + 1][j - 1].bomb == 1)
						game_field[i][j].bombs++;
					if (game_field[i + 1][j].bomb == 1)
						game_field[i][j].bombs++;
				}
				if (j == 0 && i > 0 && i < size - 1)
				{
					if (game_field[i - 1][j].bomb == 1)
						game_field[i][j].bombs++;
					if (game_field[i - 1][j + 1].bomb == 1)
						game_field[i][j].bombs++;
					if (game_field[i][j + 1].bomb == 1)
						game_field[i][j].bombs++;
					if (game_field[i + 1][j + 1].bomb == 1)
						game_field[i][j].bombs++;
					if (game_field[i + 1][j].bomb == 1)
						game_field[i][j].bombs++;
				}
				if (j != 0 && i != 0 && j != size - 1 && i != size - 1)
				{
					if (game_field[i - 1][j].bomb == 1)
						game_field[i][j].bombs++;
					if (game_field[i - 1][j + 1].bomb == 1)
						game_field[i][j].bombs++;
					if (game_field[i][j + 1].bomb == 1)
						game_field[i][j].bombs++;
					if (game_field[i + 1][j + 1].bomb == 1)
						game_field[i][j].bombs++;
					if (game_field[i + 1][j].bomb == 1)
						game_field[i][j].bombs++;
					if (game_field[i + 1][j - 1].bomb == 1)
						game_field[i][j].bombs++;
					if (game_field[i][j - 1].bomb == 1)
						game_field[i][j].bombs++;
					if (game_field[i - 1][j - 1].bomb == 1)
						game_field[i][j].bombs++;
				}
			}
		}
	}

};

int win(cell** field)
{
	int x = 0;
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (field[i][j].open == 0 && field[i][j].bomb == 0)
				x++;
		}
	}
	if (x == 0)
		return 1;
	else return 0;
}
int win_menu(RenderWindow& window, int time);
class gameplay :public miner
{
	Image cellimage, fieldimage, buttonimage;
	Texture cellT, fieldT, button;
	Sprite cell, Field, Mbutton;
	Event event;
public:
	gameplay()
	{

	}
	gameplay(int b) :miner(b)
	{
		cellimage.loadFromFile("images/cell2.png");
		cellT.loadFromImage(cellimage);
		cell.setTexture(cellT);
		fieldimage.loadFromFile("images/field.png");
		fieldT.loadFromImage(fieldimage);
		Field.setTexture(fieldT);
		Field.setPosition(0, 0);
		button.loadFromFile("images/key.png");
		Mbutton.setTexture(button);
		Mbutton.setTextureRect(IntRect(72, 0, 72, 36));
		Mbutton.setPosition(370, 25);
	}
	int game(RenderWindow& window)
	{
		Clock clock;
		Clock gametimeclock;
		int gametime = 0;
		while (window.isOpen())
		{
			int w = win(game_field);
			float time = clock.getElapsedTime().asMicroseconds();
			if(lose==0 && w==0)gametime = gametimeclock.getElapsedTime().asSeconds();
			clock.restart();
			time = time / 800;
			Vector2i pos = Mouse::getPosition(window);
			int x = pos.x;
			int y = pos.y;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();
				if (event.type == Event::MouseButtonPressed)
				{
					if (event.key.code == Mouse::Left && x > 22 && y > 91 && x < 501 && y < 569)
					{
						if (game_field[(x - 32) / 32][(y - 91) / 32].bomb == 0)
						{

							game_field[(x - 32) / 32][(y - 91) / 32].open = 1;
							field_gr[(x - 32) / 32][(y - 91) / 32] = game_field[(x - 32) / 32][(y - 91) / 32].bombs;
							if (game_field[(x - 32) / 32][(y - 91) / 32].bombs == 0)
							{
								open(game_field, field_gr, (x - 32) / 32, (y - 91) / 32);
							}
						}
						else
						{
							lose = 1;
							for (int i = 0; i < size; i++)
							{
								for (int j = 0; j < size; j++)
								{
									field_gr[i][j] = game_field[i][j].bombs;
									if (game_field[i][j].bomb == 1)
										field_gr[i][j] = 9;

								}
							}
						}
					}
					else if (event.key.code == Mouse::Right)
					{
						if (field_gr[(x - 32) / 32][(y - 91) / 32] == 10)
							field_gr[(x - 32) / 32][(y - 91) / 32] = 11;
						else
							if (field_gr[(x - 32) / 32][(y - 91) / 32] == 11)
								field_gr[(x - 32) / 32][(y - 91) / 32] = 10;
					}
					if (event.key.code == Mouse::Left && x > 370 && y > 25 && x < 442 && y < 61)
					{
						return 1;
					}
				}
			}
			window.clear();
			stringstream a;
			string Time;
			a << gametime;
			a >> Time;
			Font font;
			font.loadFromFile("text2.ttf");
			Text time_text("", font, 35);
			Text win_text("", font, 35);
			time_text.setOutlineColor(Color::Black);
			time_text.setFillColor(Color::Black);
			win_text.setOutlineColor(Color::Black);
			win_text.setFillColor(Color::Black);
			time_text.setString(Time);
			time_text.setPosition(30, 20);
			win_text.setString("WIN!!!");
			win_text.setPosition(210, 20);
			window.draw(Field);
			window.draw(time_text);
			window.draw(Mbutton);
			for (int i = 0; i < size; i++)
			{
				for (int j = 0; j < size; j++)
				{
					cell.setTextureRect(IntRect(field_gr[i][j] * 32, 0, 32, 32));
					cell.setPosition(i * 32 + 23, j * 32 + 91);
					window.draw(cell);
				}
			}
			if (w == 1)
			{
				win_menu(window, gametime);
				return 1;
			}
			window.display();
		}
	}

};
void open(cell** field,int **f, int i, int j)
{
	int size = 15;
	if ( i > 0 && field[i - 1][j].bomb == 0 && field[i - 1][j].open==0)
	{
		field[i - 1][j].open = 1;
		f[i - 1][j] = field[i-1][j].bombs;
		if (field[i - 1][j].bombs == 0)
			open(field, f, i - 1, j);
	}
	if (i>0 && j<size-1  && field[i - 1][j + 1].bomb == 0 && field[i - 1][j + 1].open == 0)
	{
		field[i - 1][j+1].open = 1;
		f[i - 1][j+1] = field[i - 1][j + 1].bombs;
		if (field[i - 1][j + 1].bombs == 0)
			open(field, f, i - 1, j + 1);
	}
	if (j<size-1 && field[i][j + 1].bomb == 0 && field[i][j + 1].open == 0)
	{
		field[i][j+1].open = 1;
		f[i][j + 1] = field[i][j + 1].bombs;
		if (field[i][j + 1].bombs == 0)
			open(field, f, i, j + 1);
	}
	if ( i<size-1 && j<size-1 && field[i + 1][j + 1].bomb == 0 && field[i + 1][j + 1].open == 0)
	{
		field[i + 1][j+1].open = 1;
		f[i + 1][j + 1] = field[i + 1][j + 1].bombs;
		if (field[i + 1][j + 1].bombs == 0)
			open(field, f, i + 1, j + 1);
	}
	if (i<size-1 && field[i + 1][j].bomb == 0 && field[i + 1][j].open == 0)
	{
		field[i + 1][j].open = 1;
		f[i + 1][j] = field[i + 1][j].bombs;
		if (field[i + 1][j].bombs == 0)
			open(field, f, i + 1, j);
	}
	if (i<size-1 && j>1 && field[i + 1][j - 1].bomb == 0 && field[i + 1][j-1].open == 0)
	{
		field[i + 1][j-1].open = 1;
		f[i + 1][j - 1] = field[i + 1][j - 1].bombs;
		if (field[i + 1][j - 1].bombs == 0)
			open(field, f, i+ 1, j-1);
	}
	if (j>0 && field[i][j - 1].bomb == 0 && field[i][j - 1].open == 0)
	{
		field[i][j-1].open = 1;
		f[i][j - 1] = field[i][j - 1].bombs;
		if (field[i][j - 1].bombs == 0)
			open(field, f, i , j-1);
	}
	if (i>0 && j> 0 && field[i - 1][j - 1].bomb == 0 && field[i - 1][j - 1].open == 0)
	{
		field[i - 1][j-1].open = 1;
		f[i - 1][j - 1] = field[i - 1][j - 1].bombs;
		if (field[i - 1][j - 1].bombs == 0)
			open(field, f, i - 1, j - 1);
	}
}

void inter_text(String name, int size, int time);

int win_menu(RenderWindow& window, int time)
{
	string text = "";
	String text2 = " ";
	Font font;
	font.loadFromFile("text2.ttf");
	Texture menuim;
	Sprite menus;
	menuim.loadFromFile("images/menu.png");
	menus.setTexture(menuim);
	menus.setPosition(0, 0);
	RectangleShape rectangle(Vector2f(300.f, 50.f));
	rectangle.setPosition(113, 300); 
	rectangle.setFillColor(Color::White);
	Text win_text("", font, 25);
	win_text.setOutlineColor(Color::Black);
	stringstream times;
	times << time;
	string T;
	times >> T;
	win_text.setFillColor(Color::Black);
	win_text.setString(L"              Победа!\n      Ваше время: " + T + L"\nВведите свое имя.");
	win_text.setPosition(127, 200);
	int activ = 0, size=0;
	Text name("", font, 35);
	name.setOutlineColor(Color::White);
	name.setFillColor(Color::White);
	name.setPosition(115,300);
	while (window.isOpen())
	{
		Vector2i pos = Mouse::getPosition(window);
		int x = pos.x;
		int y = pos.y;
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::MouseButtonPressed)
			{
				if (event.key.code == Mouse::Left && x > 113 && y > 300 && x < 413 && y < 350)
				{
					if (activ == 0)
					{
						rectangle.setFillColor(Color(80, 80, 80));
						activ = 1;
					}
					else
					{
						rectangle.setFillColor(Color::White);
						activ = 0;
					}

				}
			}
			if (event.type == Event::TextEntered && activ==1)
			{
				if (event.text.unicode == '\b')
				{
					if (size > 0)
					{
						size--;
						text2.erase(size+1, 1);
					}
				}
				if (event.text.unicode != '\b' && event.text.unicode != 13 && size < 10)
				{
					text2 += event.text.unicode;
					cout << event.text.unicode << endl;
					size++;
				}
				if (event.text.unicode == 13)
				{
					if (size > 0)
					{
						inter_text(text2, size, time);
						return 0;
					}
				}
			}

		}
		window.clear();
		window.draw(menus);
		window.draw(rectangle);
		name.setString(text2);
		window.draw(name);
		window.draw(win_text);
		window.display();

	}
}


void inter_text(String name,int size,int time)
{
	int* Name = new int[size];
	ifstream fin;
	fin.open("record.txt");
	int sizef = 0, sizestr = 0, time1[3] = {0,0,0}, pos = 0;
	string NAME, tmp, j1[3] = {"-","-","-"}, j2 = "";
	stringstream ss;
	ss << size;
	NAME = ss.str();
	ss.str("");
	NAME += ' ';
	for (int i = 0; i < size; i++)
	{
		Name[i] = name[i + 1];
		ss<< Name[i];
		NAME = NAME + ss.str() + " ";
		ss.str("");

	}
	ss.str("");
	ss << time;
	tmp = ss.str();
	NAME += tmp;
	cout << NAME;
	int i = 0;
	while (!fin.eof())
	{
		fin >> sizestr;
		for (int q = 0; q < sizestr + 1; q++)
		{
			getline(fin, j2, ' ');
			/*cout << j1;*/
		}
		fin >> time1[i];
		i++;
	}
	i = 0;
	fin.seekg(2, ios::beg);
	while (!fin.eof() && i!=3)
	{
		cout << "es"<<i;
		getline(fin, j1[i], '\n');
		cout << j1[i];
		i++;
	}
	for (int k = 0; k < 3; k++)
	{
		cout << j1[k];
	}
	for (int j = 0; j < 3; j++)
	{
		if (j1[j] == "-")
		{
			j1[j] == NAME;
			break;
		}
		if (time1[j] > time)
		{
			for (int k = 2; k > j; k--)
			{
				j1[k] = j1[k - 1];
			}
			j1[j] = NAME;
			break;
		}
		
	}
	for (int k = 0; k < 3; k++)
	{
		cout << j1[k];
	}
	ofstream fout;
	fout.open("record.txt");
	for (int k = 0; k < 3; k++)
	{
		fout << "\n" << j1[k];
	}
		fout.close();
	fin.close();
}
String out_text(int number)
{
	String name="";
	String tmp=" ";
	string nd;
	int n;
	int size;
	ifstream fin;
	fin.open("record.txt");
	if (fin.is_open())
	{
		int j = 0;
		while(!fin.eof() && j<3)
		{

				fin >> size;
				for (int i = 0; i < size; i++)
				{
					fin >> n;
					tmp[0] = n;
					name += tmp;
				}
				getline(fin, nd);
				name = name + nd + '\n' + '\n';
				j++;
		}
	}
	return name;
}

class Menu
{
	//Textbox textbox;
	Image cellimage, fieldimage, buttonimage;
	Texture cellT, fieldT, buttonT, menuim, button;
	Sprite cell, Field, start, easy, hard, menus, Gbutton, Rbutton, Ybutton, Hbutton,Mbutton;
	Event event;
	View view;
	Font font;
public:
	int b;
public:
	Menu()
	{
		cellimage.loadFromFile("images/cell2.png");
		cellT.loadFromImage(cellimage);
		cell.setTexture(cellT);
		fieldimage.loadFromFile("images/field.png");
		fieldT.loadFromImage(fieldimage);
		Field.setTexture(fieldT);
		Field.setPosition(0, 0);
		menuim.loadFromFile("images/menu.png");
		menus.setTexture(menuim);
		menus.setPosition(0, 0);
		button.loadFromFile("images/key.png");
		Gbutton.setTexture(button);
		Gbutton.setTextureRect(IntRect(0, 0, 71, 35));
		Gbutton.setPosition(228, 200);
		Mbutton.setTexture(button);
		Mbutton.setTextureRect(IntRect(72, 0, 72, 36));
		Mbutton.setPosition(228, 200);
		Rbutton.setTexture(button);
		Rbutton.setTextureRect(IntRect(0, 36, 101, 36));
		Rbutton.setPosition(213, 250);
		Ybutton.setTexture(button);
		Ybutton.setTextureRect(IntRect(0, 72, 86, 36));
		Ybutton.setPosition(220, 200);
		Hbutton.setTexture(button);
		Hbutton.setTextureRect(IntRect(86, 72, 106, 36));
		Hbutton.setPosition(210, 250);
		font.loadFromFile("CyrilicOld.TTF");
	}
	int menu(RenderWindow& window)
	{
		Font font;
		font.loadFromFile("text2.ttf");
		int M = 1;
		while (window.isOpen())
		{

			Vector2i pos = Mouse::getPosition(window);
			int x = pos.x;
			int y = pos.y;
			if (M == 1) {
				while (window.pollEvent(event))
				{
	/*				textbox.input(event);*/

					if (event.type == Event::Closed)
						window.close();
					if (event.type == Event::MouseButtonPressed)
						if (event.key.code == Mouse::Left)
						{
							cout << "x-" << x << "y" << y << endl;
							if (x > 228 && x < 299 && y>200 && y < 235)
								M = 2;
							if (x > 213 && x < 314 && y>250 && y < 286)
								M = 3;
						}

				}
				window.clear();
				window.draw(menus);
				window.draw(Gbutton);
				window.draw(Rbutton);
				window.display();
			}
			if (M == 2)
			{
				while (window.pollEvent(event))
				{
					if (event.type == Event::Closed)
						window.close();
					if (event.type == Event::MouseButtonPressed)
						if (event.key.code == Mouse::Left)
						{
							if (x > 228 && x < 299 && y>200 && y < 235)
							{
								b = 5;
								return 2;
							}
							if (x > 228 && x < 299 && y>250 && y < 285)
							{
								b = 30;
								return 2;
							}
						}
				}
				window.clear();
				window.draw(menus);
				window.draw(Ybutton);
				window.draw(Hbutton);
				window.display();
			}
			if (M == 3)
			{
				Text name("", font, 25);
				name.setOutlineColor(Color::Black);
				name.setFillColor(Color::Black);
				name.setPosition(180, 250);
				name.setString(out_text(1));
				while (window.pollEvent(event))
				{
					if (event.type == Event::Closed)
						window.close();
					if (event.type == Event::MouseButtonPressed)
						if (event.key.code == Mouse::Left)
						{
							if (x > 228 && x < 299 && y>200 && y < 235)
							{
								b = 2;
								return 1;
							}
						}
				}
				window.clear();
				window.draw(menus);
				window.draw(name);
				window.draw(Mbutton);
				window.display();
			}
		}

		return 0;
	}
};


int main()
{
	setlocale(LC_ALL, "Rus");
	srand(time(NULL));
	/*HWND hConsole = GetConsoleWindow();
	ShowWindow(hConsole, SW_HIDE);*/
	RenderWindow window(VideoMode(526, 594), "saper");
	/*FreeConsole();*/

	int M = 1;
	Menu me;
	while (window.isOpen())
	{
		switch (M)
		{
		case 1:
		/*	sort_record();*/
			M = me.menu(window);
			break;
		case 2:
			gameplay g(me.b);
			g.miner_field();
			g.bomo_around();
			M = g.game(window);

		}
	}

	/*g.drow_field();*/
	return 0;
}