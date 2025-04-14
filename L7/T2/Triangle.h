#pragma once

class Triangle : public Figure {
protected:
	unsigned a, b, c, A, B, C;

public:
	Triangle(unsigned a, unsigned b, unsigned c, unsigned A, unsigned B, unsigned C);
	void print_info() const override;

	unsigned get_a() const;
	unsigned get_b() const;
	unsigned get_c() const;
	unsigned get_A() const;
	unsigned get_B() const;
	unsigned get_C() const;
};