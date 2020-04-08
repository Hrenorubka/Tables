#pragma once
#ifndef __Polinom_H__
#define __Polinom_H__
/*
Polynomial view : "coef"x^power/y^power/z^power-"coef"x^power/y^power/z^power etc
Examples: 3x^4, y^4x-3z^3, 4, x^7yx
If power >9, when you enter power, you get error
*/
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include "List.h"

using std::cout;
using std::vector;
using std::cin;
using std::string;
using std::queue;



struct Power
{
	int xyz;
	Power()
	{
		xyz = -1;
	}
	Power(int inp_x, int inp_y, int inp_z)
	{
		if ((inp_x > 9) || (inp_x < 0) || (inp_y > 9) || (inp_y < 0) || (inp_z > 9) || (inp_z < 0))
			throw 1;
		xyz = inp_x * 100 + inp_y * 10 + inp_z;
	}
	Power(int inp_xyz)
	{
		if ((inp_xyz < 0) || (inp_xyz > 999))
			throw 1;
		xyz = inp_xyz;
	}
	Power(const Power &inp)
	{
		xyz = inp.xyz;
	}
	bool operator<(Power &inp)
	{
		return (xyz < inp.xyz);
	}
	bool operator>(Power &inp)
	{
		return (xyz > inp.xyz);	
	}
	bool operator<=(Power &inp)
	{
		return (xyz <= inp.xyz);
	}
	bool operator>=(Power &inp)
	{
		return (xyz >= inp.xyz);
	}
	bool operator!=(Power &inp)
	{
		return (xyz != inp.xyz);
	}
	bool operator==(Power &inp)
	{
		return (xyz == inp.xyz);
	}
	bool operator==(int inp)
	{
		return (xyz == inp);
	}
	Power& operator=(Power inp)
	{
		xyz = inp.xyz;
		return *this;
	}
	Power& operator=(int inp)
	{
		if (inp > 999)
		{
			xyz = 999;
			return *this;
		}
		xyz = inp;
		return *this;
	}
	Power operator+(Power &inp)
	{

		Power obl;
		obl.xyz = xyz + inp.xyz;
		return obl;
	}
	friend std::ostream& operator<<(std::ostream& out, Power &inp)
	{
		int obl = inp.xyz;
		int z = obl % 10;
		obl = obl / 10;
		int y = obl % 10;
		obl = obl / 10;
		int x = obl % 10;
		if ((x == 0) && (y == 0) && (z == 0))
			return out;
		if (x != 0)
			out << "x^" << x;
		if (y != 0)
			out << "y^" << y;
		if (z != 0)
			out << "z^" << z;
		return out;
	}

};

struct Monom
{
	Power power;
	double coef;
	Monom()
	{
		power = -1;
		coef = 0;
	}
	Monom(int inp_pow, double inp_coef)
	{
		power = inp_pow;
		coef = inp_coef;
	}
	Monom(Power inp_pow, double inp_coef)
	{
		power = inp_pow;
		coef = inp_coef;
	}
	Monom(const Monom &cop)
	{
		power = cop.power;
		coef = cop.coef;
	}
	bool operator<(Monom &comp)
	{
		return (power < comp.power);
	}
	bool operator>(Monom &comp)
	{
		return (power > comp.power);
	}
	bool operator<=(Monom &comp)
	{
		return (power <= comp.power);
	}
	bool operator>=(Monom &comp)
	{
		return (power >= comp.power);
	}
	bool operator==(Monom &rigth)
	{
		return ((coef == rigth.coef) && (power == rigth.power));
	}
	bool operator!=(Monom &rigth)
	{
		return !((*this) == rigth);
	}
	Monom &operator=(Monom inp)
	{
		power = inp.power;
		coef = inp.coef;
		return *this;
	}
	Monom operator*(double rigth)
	{
		Monom obl;
		obl.power = power;
		obl.coef = coef * rigth;
		return obl;
	}
	Monom operator*(Monom &rigth)
	{
		Monom comp;
		comp.coef = coef * rigth.coef;
		comp.power = power + rigth.power;
		return comp;
	}
	friend Monom operator*(double left, Monom &rigth)
	{
		Monom obl;
		obl.power = rigth.power;
		obl.coef = rigth.coef * left;
		return obl;
	}
	friend std::ostream& operator<<(std::ostream& out, Monom &inp)
	{

		if (inp.coef > 0)
			out << '+' << inp.coef << inp.power;
		else
			out << inp.coef << inp.power;
		return out;
	}
};

class Polinom : public List<Monom>
{
private:
	void str_to_coef_and_power(string &s, vector<double> &coef, vector<int> &power)
	{
		queue<int> cur_x;
		queue<int> cur_y;
		queue<int> cur_z;
		string cur_coef;
		int i = 0;
		if (s[i] != '-')
			s = '+' + s;
		while (i <= s.length())
		{
			step_find_coef_and_save(s, i, cur_x, cur_y, cur_z, cur_coef, coef, power);
		}

	}
	void step_find_coef_and_save(string &s, int &i, queue<int> &cur_x, queue<int> &cur_y, queue<int> &cur_z, string &cur_coef, vector<double> &coef, vector<int> &power)
	{
		if ((s[i] == '+') || (s[i] == '-'))
		{
			if (cur_coef.size() == 1)
				throw 1;
			if ((cur_coef.empty()) && (cur_x.empty()) && (cur_x.empty()) && (cur_x.empty()))
			{
				cur_coef.push_back(s[i]);
			}
			else
			{
				coef.push_back(converter_stack_coef_to_double(cur_coef));
				power.push_back(converter_power_to_int(cur_x, cur_y, cur_z));
				cur_coef.push_back(s[i]);
			}
			i++;
		}
		else if (((s[i] >= (int) '0') && (s[i] <= (int) '9')) || (s[i] == '.'))
		{
			cur_coef.push_back(s[i]);
			i++;
		}
		else if (s[i] == 'x')
		{
			i++;
			if (cur_coef.length() == 1)
				cur_coef.push_back('1');
			step_find_power(s, i, cur_x);
		}
		else if (s[i] == 'y')
		{
			i++;
			if (cur_coef.size() == 1)
				cur_coef.push_back('1');
			step_find_power(s, i, cur_y);
		}
		else if (s[i] == 'z')
		{
			i++;
			if (cur_coef.size() == 1)
				cur_coef.push_back('1');
			step_find_power(s, i, cur_z);
		}
		else if (s[i] == '\0')
		{
			if (cur_coef.size() == 1)
				throw 1;
			coef.push_back(converter_stack_coef_to_double(cur_coef));
			power.push_back(converter_power_to_int(cur_x, cur_y, cur_z));
			i++;
		}
		else
		{
			throw 1;
		}
	}
	void step_find_power(string &s, int &i, queue<int> &stack_of_cur_power)
	{
		if (s[i] == '^')
		{
			stack_of_cur_power.push(-12);
			i++;
			step_deteminate_power(s, i, stack_of_cur_power);
		}
		else if ((s[i] == '+') || (s[i] == '-') || (s[i] == '\0') || (s[i] == 'x') || (s[i] == 'y') || (s[i] == 'z'))
		{
			stack_of_cur_power.push(1);
		}
		else
		{
			throw 1;
		}
	}
	void step_deteminate_power(string &s, int &i, queue<int> &stack_of_cur_power)
	{
		if ((s[i] >= (int) '1') && (s[i] <= (int) '9'))
		{
			if (stack_of_cur_power.front() == -12)
				stack_of_cur_power.pop();
			stack_of_cur_power.push(s[i] - (int) '0');
			i++;
			step_deteminate_power(s, i, stack_of_cur_power);
		}
		else if ((s[i] == '+') || (s[i] == '-') || (s[i] == '\0') || (s[i] == 'x') || (s[i] == 'y') || (s[i] == 'z'))
		{
			if (stack_of_cur_power.front() == -12)
				throw 1;
		}
		else
			throw 1;
	}
	int converter_power_to_int(queue<int> &x, queue<int> &y, queue<int> &z)
	{
		int obl_x = 0;
		int obl_y = 0;
		int obl_z = 0;
		while (!x.empty())
		{
			obl_x = obl_x + x.front();
			x.pop();
		}
		while (!y.empty())
		{
			obl_y = obl_y + y.front();
			y.pop();
		}
		while (!z.empty())
		{
			obl_z = obl_z + z.front();
			z.pop();
		}
		if ((obl_x > 9) || (obl_y > 9) || (obl_z > 9))
			throw 1;
		int sum = obl_x * 100 + obl_y * 10 + obl_z;
		return sum;
	}
	double converter_stack_coef_to_double(string &coef)
	{
		double obl_coef = stod(coef);
		coef.clear();
		return obl_coef;
	}
	void push_front(Monom &val)
	{
		Node<Monom> *inp_node = new Node<Monom>(val);
		inp_node->node = head_node->node;
		head_node->node = inp_node;
		size++;
	}
	void push_back(Monom &val)
	{
		Node<Monom> *inp_node = new Node<Monom>(val);
		if (size == 0)
		{
			push_front(val);
			return;
		}
		Node<Monom> *obl = head_node;
		int i = 0;
		while (i < size)
		{
			i++;
			obl = obl->node;
		}
		inp_node->node = obl->node;
		obl->node = inp_node;
		size++;
	}
	void push_back(Monom &val, Node<Monom> *last)
	{
		Node<Monom> *inp_node = new Node<Monom>(val);
		inp_node->node = last->node;
		last->node = inp_node;
		size++;
	}
public:
	Polinom() : List()
	{
		Node<Monom> *first = new Node<Monom>;
		head_node = first;
		head_node->node = head_node;
	}
	Polinom(const Polinom &p_cop)
	{
		size = p_cop.size;
		Node<Monom> *first = new Node<Monom>;
		head_node = first;
		head_node->node = head_node;
		Node<Monom> *step_cop = p_cop.head_node->node;
		Node<Monom> *step_orig = head_node;
		while (step_cop != p_cop.head_node)
		{
			Node<Monom> *obl = new Node<Monom>(step_cop->val);
			obl->node = step_orig->node;
			step_orig->node = obl;
			step_cop = step_cop->node;
			step_orig = step_orig->node;
		}
	}
	Polinom(string &s)
	{
		Node<Monom> *first = new Node<Monom>;
		head_node = first;
		head_node->node = head_node;
		create_pol(s);
	}
	~Polinom()
	{
		Node<Monom> *obl = head_node;
		int i = 0;
		while (obl->node != head_node)
			obl = obl->node;
		obl->node = NULL;
		size++;
	}
	void push(Monom &val)
	{
		if (size == 0)
		{
			push_front(val);
			return;
		}
		Node<Monom> *step_next = head_node->node;
		Node<Monom> *step_prev = head_node;
		while ((step_next != head_node) && (step_next->val < val))
		{
			step_next = step_next->node;
			step_prev = step_prev->node;
		}
		if (step_next->val.power == val.power)
		{

			step_next->val.coef = step_next->val.coef + val.coef;
			if (step_next->val.coef == 0)
			{
				remove(step_prev);
				size--;
			}
			return;
		}
		Node<Monom> *inp_node = new Node<Monom>(val);
		inp_node->node = step_next;
		step_prev->node = inp_node;
		size++;
	}
	void pop_front()
	{
		if (size == 0)
			throw 1;
		Node<Monom> *bad_elem = head_node->node;
		head_node = bad_elem->node;
		delete bad_elem;
		size--;
	}
	void pop_back()
	{
		if (size == 0)
			throw 1;
		if (size == 1)
		{
			pop_front();
			return;
		}
		Node<Monom> *obl = head_node;
		int i = 0;
		while (i < size - 1)
		{
			i++;
			obl = obl->node;
		}
		Node<Monom> *bad_elem = obl->node;
		obl->node = bad_elem->node;
		delete bad_elem;
		size--;
	}
	void print()
	{
		if (head_node == head_node->node)
		{
			cout << "0\n";
			return;
		}
		Node<Monom> *step_head = head_node->node;
		while (step_head != head_node)
		{
			cout << step_head->val;
			step_head = step_head->node;
		}
		cout << '\n';
	}
	Polinom &operator=(const Polinom inp)
	{
		Node<Monom> *prev = head_node;
		Node<Monom> *next = head_node->node;
		while (prev != next)
		{
			prev->node = next->node;
			delete next;
			next = prev->node;
		}
		size = inp.size;
		Node<Monom> *step_inp = inp.head_node->node;
		Node<Monom> *step_this = head_node;
		while (step_inp != inp.head_node)
		{
			Node<Monom> *obl = new Node<Monom>(step_inp->val);
			obl->node = step_this->node;
			step_this->node = obl;
			step_inp = step_inp->node;
			step_this = step_this->node;
		}
		return *this;
	}
	Polinom operator+(const Polinom &p)
	{
		Polinom sum;
		Node<Monom> *last_node_sum = sum.head_node;
		Node<Monom> *step_first = head_node->node;
		Node<Monom> *step_second = p.head_node->node;
		while ((step_first != head_node) && (step_second != p.head_node))
		{
			if (step_first->val.power == step_second->val.power)
			{
				Monom obl;
				obl.coef = step_first->val.coef + step_second->val.coef;
				if (obl.coef != 0)
				{
					obl.power = step_first->val.power;
					sum.push_back(obl, last_node_sum);
					last_node_sum = last_node_sum->node;
				}
				step_first = step_first->node;
				step_second = step_second->node;
			}
			else if (step_first->val.power > step_second->val.power)
			{
				
				sum.push_back(step_second->val, last_node_sum);
				step_second = step_second->node;
				last_node_sum = last_node_sum->node;
			}
			else if (step_first->val.power < step_second->val.power)
			{
				sum.push_back(step_first->val, last_node_sum);
				step_first = step_first->node;
				last_node_sum = last_node_sum->node;
			}
		}
		while (step_first != head_node)
		{
			sum.push_back(step_first->val, last_node_sum);
			last_node_sum = last_node_sum->node;
			step_first = step_first->node;
		}
		while (step_second != p.head_node)
		{
			sum.push_back(step_second->val, last_node_sum);
			last_node_sum = last_node_sum->node;
			step_second = step_second->node;
		}
		return sum;
	}
	Polinom operator*(const Polinom &p)
	{
		Polinom compos;
		if ((head_node == head_node->node) || (p.head_node == p.head_node->node))
			return compos;
		Node<Monom> *step_left = head_node->node;
		Node<Monom> *step_rigth = p.head_node->node;
		while (step_left != head_node)
		{
			step_rigth = p.head_node->node;
			while (step_rigth != p.head_node)
			{
				Monom obl;
				obl = step_left->val * step_rigth->val;
				compos.push(obl);
				step_rigth = step_rigth->node;
			}
			step_left = step_left->node;
		}
		return compos;
	}
	Polinom operator*(double x)
	{
		Polinom compos;
		Node<Monom> *step = head_node->node;
		while (step != head_node)
		{
			Monom obl;
			obl = step->val * x;
			compos.push(obl);
			step = step->node;
		}
		return compos;
	}
	friend Polinom operator*(double x, Polinom &p)
	{
		return p * x;
	}
	Polinom operator-(Polinom &p)
	{
		Polinom dif;
		dif = *this + (-1)*p;
		return dif;
	}
	Monom find(int pos)
	{
		Node<Monom> *obl_step = head_node->node;
		int i = 0;
		if (pos >= size)
			throw 1;
		while (i < pos)
		{
			if (obl_step->node == NULL)
				throw 1;
			obl_step = obl_step->node;
			i++;
		}
		return obl_step->val;

	}
	bool operator==(const Polinom &rigth)
	{
		Node<Monom> *step_first = head_node->node;
		Node<Monom> *step_second = rigth.head_node->node;
		while ((step_first != head_node) && (step_second != rigth.head_node))
		{
			if (step_first->val != step_second->val)
				return false;
			step_first = step_first->node;
			step_second = step_second->node;
		}
		return ((step_first == head_node) && (step_second == rigth.head_node));
	}
	bool operator!=(const Polinom &rigth)
	{
		return !((*this) == rigth);
	}
	void create_pol(string &s)
	{
		vector<double> coef;
		vector<int> power;
		str_to_coef_and_power(s, coef, power);
		for (int i = 0; i < coef.size(); i++)
		{
			Monom obl;
			obl.coef = coef[i];
			obl.power = power[i];
			push(obl);
		}
	}
};



#endif