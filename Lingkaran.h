#pragma once

class Lingkaran {
protected : 
	int lebarpusat, tinggipusat, a;
	float sudut, x, y;

public:
	Lingkaran();
	Lingkaran(int lebarpusat, int tinggipusat);
	void gambar_L(int lebarpusat, int tinggipusat);
};