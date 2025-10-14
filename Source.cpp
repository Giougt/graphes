#include <iostream>
#include <vector>


struct Arete {
	int x, y, poids;
};

int main() {
	std::vector<Arete> tableau;

	Arete a;
	a.x = 1;
	a.y = 2;
	a.poids = 10;

	Arete b;
	b.x = 1;
	b.y = 3;
	b.poids = 20;

	Arete c;
	c.x = 2;
	c.y = 4;
	c.poids = 30;

	Arete d;
	d.x = 3;
	d.y = 2;
	d.poids = 40;

	Arete e;
	e.x = 4;
	e.y = 3;
	e.poids = 50;

	Arete f;
	f.x = 4;
	f.y = 5;
	f.poids = 60;

	Arete g;
	g.x = 5;
	g.y = 3;
	g.poids = 70;

	Arete h;
	h.x = 5;
	h.y = 4;
	h.poids = 80;


	tableau.push_back(a);
	tableau.push_back(b);
	tableau.push_back(c);
	tableau.push_back(d);
	tableau.push_back(e);
	tableau.push_back(f);
	tableau.push_back(g);
	tableau.push_back(h);

	for (const Arete& e : tableau) {
		std::cout << "De " << e.x << " a " << e.y << " avec poids " << e.poids << "\n";
	}
	
}
