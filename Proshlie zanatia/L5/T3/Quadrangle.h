#pragma once

class Quadrangle : public Figure {
protected:
	unsigned a, b, c, d, A, B, C, D;

public:
	Quadrangle(unsigned a, unsigned b, unsigned c, unsigned d, unsigned A, unsigned B, unsigned C, unsigned D);
	void print_info() const override;

	unsigned get_a() const;
	unsigned get_b() const;
	unsigned get_c() const;
	unsigned get_d() const;
	unsigned get_A() const;
	unsigned get_B() const;
	unsigned get_C() const;
	unsigned get_D() const;
};