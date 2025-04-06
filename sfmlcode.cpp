#include <sfml\Graphics.hpp> 
#include<iostream>
#include<fstream>
using namespace std;
void setbead(sf::CircleShape beads[5][5], int row, int col) 
{
	beads[row][col].setRadius(20);
	beads[row][col].setOutlineThickness(3);
	beads[row][col].setPosition(45 + col * 145, 50 + row * 140);
}
void Greenbead(sf::CircleShape beads[5][5], int row, int col) 
{
	setbead(beads, row, col);
	beads[row][col].setOutlineColor(sf::Color::Yellow);
	beads[row][col].setFillColor(sf::Color::Green);
}
void Bluebead(sf::CircleShape beads[5][5], int row, int col) 
{
	setbead(beads, row, col);
	beads[row][col].setOutlineColor(sf::Color::Cyan);
	beads[row][col].setFillColor(sf::Color::Blue);
}
void Emptybead(sf::CircleShape beads[5][5], int row, int col) 
{
	setbead(beads, row, col);
	beads[row][col].setOutlineColor(sf::Color::Transparent);
	beads[row][col].setFillColor(sf::Color::Transparent);
}
void beadshadow(sf::CircleShape beads[5][5], int row, int col)
{
	if (beads[row][col].getOutlineColor() == sf::Color::Transparent)
		beads[row][col].setFillColor(sf::Color(255, 0, 255, 120));
}
void checkbead(sf::CircleShape beads[5][5], int sRow, int sCol, int rDiff, int cDiff, sf::Color turnColor)
{
	if (beads[sRow + rDiff][sCol + cDiff].getOutlineColor() == sf::Color::Transparent)
		beads[sRow + rDiff][sCol + cDiff].setFillColor(sf::Color(255, 0, 255, 120));
	else if (beads[sRow + rDiff][sCol + cDiff].getFillColor() == turnColor) {

		if (sRow + 2 * rDiff < 5 && sRow + 2 * rDiff >= 0 && sCol + 2 * cDiff < 5 && sCol + 2 * cDiff >= 0)
		{
			beadshadow(beads, sRow + 2 * rDiff, sCol + 2 * cDiff);
		}
	}
}
void selectedbead(sf::CircleShape beads[5][5], int row, int col, int turn) {//tell valid moves
	sf::Color turnColor;
	if (turn == 1)
		turnColor = sf::Color::Blue;
	else
		turnColor = sf::Color::Green;
	if (row + 1 < 5 && col + 1 < 5 && (5 * row + col) % 2 == 0) checkbead(beads, row, col, 1, 1, turnColor);
	if (row - 1 >= 0 && col - 1 >= 0 && (5 * row + col) % 2 == 0) checkbead(beads, row, col, -1, -1, turnColor);
	if (row + 1 < 5 && col - 1 >= 0 && (5 * row + col) % 2 == 0) checkbead(beads, row, col, 1, -1, turnColor);
	if (row - 1 >= 0 && col + 1 < 5 && (5 * row + col) % 2 == 0) checkbead(beads, row, col, -1, 1, turnColor);
	if (row + 1 < 5) checkbead(beads, row, col, 1, 0, turnColor);
	if (col + 1 < 5) checkbead(beads, row, col, 0, 1, turnColor);
	if (row - 1 >= 0) checkbead(beads, row, col, -1, 0, turnColor);
	if (col - 1 >= 0) checkbead(beads, row, col, 0, -1, turnColor);

}
void check(sf::CircleShape beads[5][5]) {
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (beads[i][j].getFillColor() == sf::Color(255, 0, 255, 120)) {
				beads[i][j].setFillColor(sf::Color::Transparent);
			}
		}
	}
}
void move(sf::CircleShape beads[5][5], int sr, int sc, int dr, int dc) {//moving from one position to other
	if (dr == 2 + sr || dr == sr - 2 || dc == 2 + sc || dc == sc - 2) {
		int mr = (sr + dr) / 2;
		int mc = (sc + dc) / 2;
		beads[mr][mc].setFillColor(sf::Color::Transparent);
		beads[mr][mc].setOutlineColor(sf::Color::Transparent);
	}
	sf::Color temp = beads[sr][sc].getFillColor();
	sf::Color temp2 = beads[sr][sc].getOutlineColor();
	beads[dr][dc].setFillColor(temp);
	beads[dr][dc].setOutlineColor(temp2);
	beads[sr][sc].setFillColor(sf::Color::Transparent);
	beads[sr][sc].setOutlineColor(sf::Color::Transparent);
}
void beadvalue(sf::CircleShape beads[5][5], int turn) {
	ofstream file;
	file.open("GAME.txt");
	if (turn == 1) {
		file << '1';
	}
	else {
		file << '2';
	}
	file << '\n';
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (beads[i][j].getFillColor() == sf::Color::Green) {
				file << 'G' << '/';
			}
			else if (beads[i][j].getFillColor() == sf::Color::Blue) {
				file << 'B' << '/';
			}
			else {
				file << 'E' << '/';
			}
		}
		file << '\n';
	}
	file.close();
}
void getfile(sf::CircleShape beads[5][5], int& turn) {
	ifstream filer;
	filer.open("GAME.txt");
	char c;
	filer >> c;
	if (c == '1') {
		turn = 1;
	}
	else
	{
		turn = 2;
	}
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			filer >> c;
			if (c == 'G') {
				Greenbead(beads, i, j);
			}
			else if (c == 'B') {
				Bluebead(beads, i, j);
			}
			else
			{
				Emptybead(beads, i, j);
			}
			filer >> c;
		}
	}
	filer.close();

}
bool checkwin(sf::CircleShape beads[5][5], int turn) {
	sf::Color oppcolor;
	if (turn == 1) {
		oppcolor = sf::Color::Blue;
	}
	else if (turn == 2) {
		oppcolor = sf::Color::Green;
	}
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (beads[i][j].getFillColor() == oppcolor) {
				return false;
			}
		}
	}
	return true;
}
int main()
{
	sf::RenderWindow window(sf::VideoMode(700, 700), "My First Game", sf::Style::Close | sf::Style::Titlebar);
	sf::Font font;
	if (!font.loadFromFile("font.ttf"));

	sf::Text one;
	one.setFont(font);
	one.setCharacterSize(60);
	one.setString("  1");
	one.setFillColor(sf::Color::Green);
	one.setOutlineThickness(3);
	one.setOutlineColor(sf::Color::Magenta);
	one.setStyle(sf::Text::Bold);
	one.setPosition(50, 15);
	sf::Text two;
	two.setFont(font);
	two.setCharacterSize(60);
	two.setString("2");
	two.setFillColor(sf::Color::Blue);
	two.setOutlineThickness(3);
	two.setOutlineColor(sf::Color::Magenta);
	two.setStyle(sf::Text::Bold);
	two.setPosition(120, 15);
	sf::Text intro;
	intro.setFont(font);
	intro.setCharacterSize(60);
	intro.setString("BEADS GAME");
	intro.setFillColor(sf::Color::Magenta);
	intro.setOutlineThickness(2);
	intro.setOutlineColor(sf::Color::White);
	intro.setStyle(sf::Text::Bold);
	intro.setPosition(190, 15);


	sf::Text end;
	end.setFont(font);
	end.setCharacterSize(30);
	end.setFillColor(sf::Color::White);
	end.setString(" Game By:- Eman Aamir ");
	end.setOutlineThickness(2);
	end.setOutlineColor(sf::Color::Magenta);
	end.setPosition(140, 650);

	sf::RectangleShape Continue;
	Continue.setSize(sf::Vector2f(400, 80));
	Continue.setOutlineColor(sf::Color::White);
	Continue.setFillColor(sf::Color::Green);
	Continue.setOutlineThickness(5);
	Continue.setPosition(150, 200);
	sf::Text Con;
	Con.setFont(font);
	Con.setCharacterSize(40);
	Con.setFillColor(sf::Color::Magenta);
	Con.setString("CONTINUE");
	Con.setStyle(sf::Text::Bold);
	Con.setPosition(250, 220);


	sf::RectangleShape Newgame;
	Newgame.setSize(sf::Vector2f(400, 80));
	Newgame.setOutlineColor(sf::Color::White);
	Newgame.setFillColor(sf::Color::Green);
	Newgame.setOutlineThickness(5);
	Newgame.setPosition(150, 300);
	sf::Text Ng;
	Ng.setFont(font);
	Ng.setCharacterSize(40);
	Ng.setFillColor(sf::Color::Magenta);
	Ng.setString("NEW GAME");
	Ng.setStyle(sf::Text::Bold);
	Ng.setPosition(240, 320);

	sf::RectangleShape Exit;
	Exit.setSize(sf::Vector2f(400, 80));
	Exit.setOutlineColor(sf::Color::White);
	Exit.setFillColor(sf::Color::Magenta);
	Exit.setOutlineThickness(5);
	Exit.setPosition(150, 400);
	sf::Text e;
	e.setFont(font);
	e.setCharacterSize(40);
	e.setFillColor(sf::Color::White);
	e.setString("EXIT");
	e.setStyle(sf::Text::Bold);
	e.setPosition(300, 420);

	sf::Text textturn;//show turn
	textturn.setFont(font);
	textturn.setCharacterSize(24);
	textturn.setFillColor(sf::Color::White);
	textturn.setStyle(sf::Text::Bold | sf::Text::Underlined);
	textturn.setPosition(250, 10);

	sf::RectangleShape winnerboard;
	winnerboard.setSize(sf::Vector2f(500, 70));
	winnerboard.setOutlineColor(sf::Color::White);
	winnerboard.setFillColor(sf::Color::Black);
	winnerboard.setOutlineThickness(5);
	winnerboard.setPosition(100, 450);
	sf::Text textwin;
	textwin.setFont(font);
	textwin.setCharacterSize(40);
	textwin.setFillColor(sf::Color::White);
	textwin.setStyle(sf::Text::Bold | sf::Text::Underlined);
	textwin.setPosition(120, 460);

	sf::CircleShape beads[5][5];
	int turn = 1;
	textturn.setString("Green's Turn !");
	int menu = 0;
	bool checkfile = true;
	bool exit = false;
	ifstream file;
	file.open("GAME.txt");
	if (file)
	{
		checkfile = true;
	}
	else
	{
		checkfile = false;
	}
	for (int row = 0; row < 5; row++) {
		for (int col = 0; col < 5; col++) {
			if (row < 2) {
				Greenbead(beads, row, col);
			}
			else if (row > 2) {
				Bluebead(beads, row, col);
			}
			else if (col < 2) {
				Greenbead(beads, row, col);
			}
			else if (col > 2) {
				Bluebead(beads, row, col);
			}
			else {
				Emptybead(beads, row, col);
			}
		}
	}
	file.close();
	sf::Texture imageSource2;
	if (!imageSource2.loadFromFile("Best.jpg")) {
		return 0;
	}
	sf::Sprite imageSprite2;
	imageSprite2.setTexture(imageSource2);
	float centerX2 = window.getSize().x / 2.0f;
	float centerY2 = window.getSize().y / 2.0f;
	float imageX2 = centerX2 - imageSprite2.getLocalBounds().width / 2.0f;
	float imageY2 = centerY2 - imageSprite2.getLocalBounds().height / 2.0f;
	imageSprite2.setPosition(imageX2, imageY2);

	sf::Texture imageSource;
	if (!imageSource.loadFromFile("texture1.jpg")) {
		return 0;
	}
	sf::Sprite imageSprite;
	imageSprite.setTexture(imageSource);
	float centerX = window.getSize().x / 2.0f;
	float centerY = window.getSize().y / 2.0f;
	float imageX = centerX - imageSprite.getLocalBounds().width / 2.0f;
	float imageY = centerY - imageSprite.getLocalBounds().height / 2.0f;
	imageSprite.setPosition(imageX, imageY);

	sf::Texture imageSource3;
	if (!imageSource3.loadFromFile("2.jpg")) {
		return 0;
	}
	sf::Sprite imageSprite3;
	imageSprite3.setTexture(imageSource3);
	float centerX3 = window.getSize().x / 2.0f;
	float centerY3 = window.getSize().y / 2.0f;
	float imageX3 = centerX3 - imageSprite3.getLocalBounds().width / 2.0f;
	float imageY3 = centerY3 - imageSprite3.getLocalBounds().height / 2.0f;
	imageSprite3.setPosition(imageX3, imageY3);

	int fromrow = -1;
	int fromcol = -1;
	int frow = -1;
	int crow = -1;
	bool outputimagesprite2 = true;
	while (window.isOpen())
	{
		sf::Event even;
		while (window.pollEvent(even))
		{
			switch (even.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseButtonPressed:
				if (menu == 0) {
					if (Continue.getGlobalBounds().contains(even.mouseButton.x, even.mouseButton.y)) {
						if (checkfile) {

							getfile(beads, turn);
							menu = 1;
						}
						else
						{
							cout << "error";
						}
					}
					if (Newgame.getGlobalBounds().contains(even.mouseButton.x, even.mouseButton.y)) {
						menu = 1;
					}
					if (Exit.getGlobalBounds().contains(even.mouseButton.x, even.mouseButton.y)) {
						exit = true;
					}

				}
				else if (menu == 1)
				{
					for (int row = 0; row < 5; row++) {
						for (int col = 0; col < 5; col++) {
							if (beads[row][col].getGlobalBounds().contains(even.mouseButton.x, even.mouseButton.y)) {
								if (fromrow != -1 && fromcol != -1 && beads[row][col].getFillColor() == sf::Color(255, 0, 255, 120)) {

									move(beads, fromrow, fromcol, row, col);
									if (checkwin(beads, turn)) {
										menu = 2;
										if (turn == 1) {
											textwin.setString("!! Green is The Winner!!");
										}
										else {
											textwin.setString("!! Blue is The Winner !!");
										}
										break;
									}
									fromrow = -1;
									fromcol = -1;
									if (turn == 1) {
										turn = 2;
										textturn.setString("Blue's turn!!");
									}
									else {
										turn = 1;
										textturn.setString("Green's turn!!");
									}
								}
								if (beads[row][col].getOutlineColor() == sf::Color::Yellow && turn == 1 || beads[row][col].getOutlineColor() == sf::Color::Cyan && turn == 2) {
									check(beads);
									selectedbead(beads, row, col, turn);
									fromrow = row;
									fromcol = col;
								}
								else
								{
									fromrow = -1;
									fromcol = -1;
									check(beads);
								}
							}
						}
						if (menu == 2)
							break;
					}
				}
				break;
			}
		}
		window.clear();
		if (outputimagesprite2) {
			window.draw(imageSprite2);
		}
		else {
			window.draw(imageSprite);
		}
		window.draw(end);
		if (menu == 0) {
			window.draw(one);
			window.draw(two);
			window.draw(intro);
			window.draw(Continue);
			window.draw(Con);
			window.draw(Newgame);
			window.draw(Ng);
			window.draw(Exit);
			window.draw(e);

		}
		else if (menu == 1) {
			for (int row = 0; row < 5; row++) {
				for (int col = 0; col < 5; col++) {
					window.draw(beads[row][col]);
				}
			}
			window.draw(textturn);
		}
		else if (menu == 2) {
			window.draw(imageSprite3);
			window.draw(winnerboard);
			window.draw(textwin);
		}
		window.display();
		if (exit) {
			window.close();
			break;
		}
		if (menu == 1 && outputimagesprite2) {
			outputimagesprite2 = false;
		}
	}
	beadvalue(beads, turn);
	return 0;
}