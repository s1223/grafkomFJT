#pragma once

class Lingkaran {
protected : 
	const double phi = 3.141592653589793;
	int jari2, titik, lebarpusat, tinggipusat, a;
	float sudut, x, y;

public:
	Lingkaran();
	Lingkaran(int jari2, int titik, int lebarpusat, int tinggipusat);
	void gambar_L(int jari2, int titik, int lebarpusat, int tinggipusat);
};