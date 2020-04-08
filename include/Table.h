#pragma once
#ifndef __Table_H__
#define __Table_H__
#include <Polinom.h>
#include <vector>
#include <fstream>

using std::ios;
using std::ifstream;
using std::ofstream;

template <class ValType>
struct Val_Collum
{
	int key;
	ValType val;
	Val_Collum()
	{
		key = -1;
	}
	Val_Collum(int inp_key, ValType inp_val)
	{
		key = inp_key;
		val = inp_val;
	}
	Val_Collum(const Val_Collum &cop)
	{
		key = cop.key;
		val = cop.val;
	}
	Val_Collum& operator=(const Val_Collum &inp)
	{

		key = inp.key;
		val = inp.val;
		return *this;
	}
	void get_from_string(string s)
	{
		int i = 0;
		string obl;
		while ((i < s.length()) && (s[i] != ';'))
		{
			obl = obl + s[i];
			i++;
		}
		if (i >= s.length())
			throw 1;
		i++;
		key = stoi(obl);
		obl.clear();
		while (i < s.length())
		{
			obl = obl + s[i];
			i++;
		}
		val.create_pol(obl);
	}
	bool operator<(Val_Collum &rigth)
	{
		return (key < rigth.key);
	}
	bool operator>(Val_Collum &rigth)
	{
		return (key > rigth.key);
	}
};

template <class ValType>
class Table
{
protected:
	int cur_size;
	int max_size;
	Val_Collum<ValType> *table;
	virtual void repacking()
	{
		max_size = 10 + max_size * 1.5;
		Val_Collum<ValType> *obl_table = new Val_Collum<ValType>[max_size];
		for (int i = 0; i < cur_size; i++)
		{
			obl_table[i] = table[i];
		}
		delete[] table;
		table = obl_table;
	}
public:
	Table()
	{
		max_size = 15;
		cur_size = 0;
		table = new Val_Collum<ValType>[15];
	}
	Table(int inp_size)
	{
		max_size = inp_size;
		cur_size = 0;
		table = new Val_Collum<ValType>[max_size];
	}
	~Table()
	{
		if (max_size != 0)
			delete[] table;
	}
	virtual void key_push(int inp_key, ValType inp_p) {}
	virtual void key_delete(int inp_key) {}
	virtual ValType key_find(int inp_key)
	{
		throw 1;
	}
	virtual void get_table_from_file(string s)
	{
		ifstream file;
		file.open(s);
		if (!file.is_open())
			return;
		string collum;
		getline(file, collum);
		if (max_size != 0)
			delete[] table;
		max_size = stoi(collum) + 10;
		table = new Val_Collum<ValType>[max_size];
		int i = 0;
		while (!file.eof())
		{
			getline(file, collum);
			table[i].get_from_string(collum);
			i++;
		}
		cur_size = i;
		file.close();
	}
	virtual void push_table_to_file(string s)
	{
		ofstream file;
		file.open(s, ios::trunc);
		if (!file.is_open())
			throw 1;
		file << cur_size << '\n';
		for (int i = 0; i < cur_size - 1; i++)
			file << table[i].key << ';' << table[i].val.convert_to_string() << '\n';
		file << table[cur_size - 1].key << ';' << table[cur_size - 1].val.convert_to_string();
		file.close();
	}
	virtual ValType find_max()
	{
		throw 1;
	}
	virtual ValType find_min()
	{
		throw 1;
	}
	int get_cur_size()
	{
		return cur_size;
	}
	int get_max_size()
	{
		return max_size;
	}
};

template <class ValType>
class Unordered_Table : public Table<ValType>
{
public:
	Unordered_Table() : Table() {}
	Unordered_Table(int inp_size) : Table(inp_size) {}
	void key_push(int inp_key, ValType inp_val)
	{
		if (cur_size == max_size)
		{
			repacking();
		}
		table[cur_size].key = inp_key;
		table[cur_size].val = inp_val;
		cur_size++;
	}
	void key_delete(int inp_key)
	{
		int i;
		for (i = 0; (i < cur_size) && (inp_key != table[i].key); i++);
		if (i == cur_size)
			throw 1;
		cur_size--;
		Val_Collum<ValType> obl = table[cur_size];
		table[cur_size] = table[i];
		table[i] = obl;
	}
	ValType key_find(int inp_key)
	{
		int i;
		for (i = 0; (i < cur_size) && (inp_key != table[i].key); i++);
		if (i == cur_size)
			throw 1;
		return table[i].val;
	}

};
#endif