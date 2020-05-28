#pragma once
#ifndef __Table_H__
#define __Table_H__
#include <Polinom.h>
#include <vector>
#include <fstream>
#include <ctime>


using std::ios;
using std::ifstream;
using std::ofstream;
using std::srand;
using std::rand;

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
	bool operator!=(Val_Collum &rigth)
	{
		return (key != rigth.key);
	}
	bool operator==(Val_Collum &rigth)
	{
		return (key == rigth.key);
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
template <class ValType>
class Ordered_Table : public Table<ValType>
{
private:
	int *flag;
	int *obl_flag;
	int size_with_del;
	Val_Collum<ValType> *obl_table;
	int cur_size_obl_table;
	void repacking() // доделать
	{
		if (size_with_del + cur_size_obl_table >= max_size)
			max_size = 10 + max_size * 1.5;
		Val_Collum<ValType> *end_table = new Val_Collum<ValType>[max_size];
		int *end_flag = new int[max_size];
		int i_cur_t = 0;
		int i_obl_t = 0;
		int i_end_t = 0;
		while ((i_cur_t < size_with_del) && (i_obl_t < cur_size_obl_table))
		{
			if (flag[i_cur_t] == 1)
			{
				i_cur_t++;
			}
			else if (obl_flag[i_obl_t] == 1)
			{
				i_obl_t++;
			}
			else if (table[i_cur_t] < obl_table[i_obl_t])
			{
				end_table[i_end_t] = table[i_cur_t];
				end_flag[i_end_t] = 0;
				i_end_t++;
				i_cur_t++;
			}
			else
			{
				end_table[i_end_t] = obl_table[i_obl_t];
				end_flag[i_end_t] = 0;
				i_end_t++;
				i_obl_t++;
				cur_size++;
			}
		}
		while (i_cur_t < size_with_del)
		{
			if (flag[i_cur_t] == 1)
			{
				i_cur_t++;
			}
			else
			{
				end_table[i_end_t] = table[i_cur_t];
				end_flag[i_end_t] = 0;
				i_end_t++;
				i_cur_t++;
			}
		}
		while (i_obl_t < cur_size_obl_table)
		{
			if (obl_flag[i_obl_t] == 1)
			{
				i_obl_t++;
			}
			else
			{
				end_table[i_end_t] = obl_table[i_obl_t];
				end_flag[i_end_t] = 0;
				i_end_t++;
				i_obl_t++;
				cur_size++;
			}
		}
		cur_size_obl_table = 0;
		size_with_del = cur_size;
		delete[] flag;
		delete[] table;
		table = end_table;
		flag = end_flag;
	}
	void push_in_obl(Val_Collum<ValType> &inp)
	{
		if (cur_size_obl_table == 5)
		{
			repacking();
		}
		int i = 0;
		while ((i < cur_size_obl_table) && (inp > obl_table[i]))
			i++;
		if (inp.key == obl_table[i].key)
			throw 1;
		int j = cur_size_obl_table - 1;
		while (j >= i)
		{
			obl_table[j + 1] = obl_table[j];
			obl_flag[j + 1] = obl_flag[j];
			j--;
		}
		obl_table[i] = inp;
		obl_flag[i] = 0;
		cur_size_obl_table++;
	}
public:
	Ordered_Table() : Table()
	{
		flag = new int[15];
		obl_table = new Val_Collum<ValType>[5];
		obl_flag = new int[5];
		size_with_del = 0;
		cur_size_obl_table = 0;
	}
	Ordered_Table(int inp_size) : Table(inp_size)
	{
		if (inp_size < 10)
		{
			max_size = 10;
			delete[] table;
			table = new Val_Collum<ValType>[10];
		}
		flag = new int[max_size];
		obl_table = new Val_Collum<ValType>[5];
		obl_flag = new int[5];
		size_with_del = 0;
		cur_size_obl_table = 0;
	}
	~Ordered_Table()
	{
		if (max_size != 0)
			delete[] flag;
		delete[] obl_flag;
	}
	ValType key_find(int inp_key)
	{
		if (cur_size == 0)
			throw 1;
		int left = 0;
		int rigth = size_with_del - 1;
		int midle = (rigth - left) / 2 + left;
		while ((rigth >= left) && (inp_key != table[midle].key))
		{
			if (inp_key < table[midle].key)
			{
				rigth = midle - 1;
				midle = (rigth - left) / 2 + left;
			}
			else
			{
				left = midle + 1;
				midle = (rigth - left) / 2 + left;
			}
		}
		if (rigth >= left)
			return table[midle].val;
		int i = 0;
		while (i < cur_size_obl_table)
		{
			if (inp_key == obl_table[i].key)
				return obl_table[i].val;
			i++;
		}
		throw 1;
	}
	void key_push(int inp_key, ValType inp_val) // доделать
	{
		Val_Collum<ValType> inp_col = { inp_key, inp_val };
		if ((size_with_del < 10))
		{
			if (size_with_del == 0)
			{
				table[0] = inp_col;
				flag[0] = 0;
				size_with_del++;
				cur_size++;
			}
			else
			{
				int i = 0;
				while ((i < size_with_del) && (inp_key > table[i].key))
				{
					i++;
				}
				if (inp_key == table[i].key)
					throw 1;
				int j = size_with_del - 1;
				while (j >= i)
				{
					table[j + 1] = table[j];
					flag[j + 1] = flag[j];
					j--;
				}
				table[i] = inp_col;
				flag[i] = 0;
				size_with_del++;
				cur_size++;
			}
		}
		else
		{
			push_in_obl(inp_col);
		}
	}
	void key_delete(int inp_key)
	{
		if (cur_size == 0)
			throw 1;
		int left = 0;
		int rigth = size_with_del - 1;
		int midle = (rigth - left) / 2 + left;
		while ((rigth >= left) && (inp_key != table[midle].key))
		{
			if (inp_key < table[midle].key)
			{
				rigth = midle - 1;
				midle = (rigth - left) / 2 + left;
			}
			else
			{
				left = midle + 1;
				midle = (rigth - left) / 2 + left;
			}
		}
		if (rigth >= left)
		{
			flag[midle] = 1;
			return;
		}
		int i = 0;
		while (i < cur_size_obl_table)
		{
			if (inp_key == obl_table[i].key)
			{
				obl_flag[i] = 1;
				return;
			}
			i++;
		}
		throw 1;
	}
	void get_table_from_file(string s)
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
		flag = new int[max_size];
		int i = 0;
		cur_size = 0;
		size_with_del = 0;
		while (!file.eof())
		{
			getline(file, collum);
			Val_Collum<ValType> obl;
			obl.get_from_string(collum);
			key_push(obl.key, obl.val);
			i++;
		}
		cur_size_obl_table = 0;
		file.close();
	}
	void push_table_to_file(string s)
	{
		repacking();
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
};
template <class ValType>
class Hash_Table : public Table<ValType>
{
private:
	int a;
	int b;
	int p;
	int size_hash;
	List<Val_Collum<ValType>> *hash_t;
	int find_prime_numb(int m)
	{
		bool fl = true;
		while (fl)
		{
			fl = false;
			m++;
			for (int i = 2; i < sqrt(m) + 2; i++)
			{
				if (m % i == 0)
				{
					fl = true;
					break;
				}
			}
			if (!fl)
				return m;
		}
	}
	void create_hash()
	{
		if (hash_t != NULL)
			delete[] hash_t;
		if (max_size == 0)
			throw 1;
		size_hash = max_size * max_size;
		hash_t = new List<Val_Collum< ValType > >[size_hash];
		srand(time(NULL));
		a = rand() % 35 + 1;
		b = rand() % 35 + 1;
		p = find_prime_numb(max_size);
		for (int i = 0; i < cur_size; i++)
		{
			int numb = ((a * table[i].key + b) % p) % size_hash;
			hash_t[numb].push_front(table[i]);
		}
	}
	Node<Val_Collum<ValType>>* key_find_prev(int inp_key, int numb)
	{
		Node<Val_Collum <ValType> > *step = hash_t[numb].get_head();
		if (step == NULL)
			return NULL;
		if (step->node == NULL)
			return NULL;
		while (step->node != NULL)
		{
			if (step->node->val.key == inp_key)
			{
				return step;
			}
			step = step->node;
		}
		return NULL;
	}
public:
	Hash_Table() : Table()
	{
		hash_t = NULL;

		create_hash();
	}
	Hash_Table(int size) : Table(size)
	{
		hash_t = NULL;
		create_hash();
	}
	~Hash_Table()
	{
		if (hash_t != NULL)
			delete[] hash_t;
	}
	void key_push(int inp_key, ValType inp_val)
	{
		if (cur_size == max_size)
		{
			repacking();
			if (max_size + 20 > sqrt(2 * size_hash))
				create_hash();
		}
		table[cur_size].key = inp_key;
		table[cur_size].val = inp_val;
		int numb = ((a * table[cur_size].key + b) % p) % size_hash;
		hash_t[numb].push_front(table[cur_size]);
		cur_size++;
	}
	
	void key_delete(int inp_key)
	{
		int i;
		for (i = 0; (i < cur_size) && (inp_key != table[i].key); i++);
		if (i == cur_size)
			throw 1;
		cur_size--;
		int numb = ((a * inp_key + b) % p) % size_hash;
		Node<Val_Collum<ValType>> *step = key_find_prev(inp_key, numb);
		if (step == NULL)
		{
			if (hash_t[numb].get_head() == NULL)
				throw 1;
			else
				hash_t[numb].pop_front();
		}
		else
			hash_t[numb].remove(step);
	}
	
	ValType key_find(int inp_key)
	{
		int numb = ((a * inp_key + b) % p) % size_hash;
		Node<Val_Collum<ValType>> *step = key_find_prev(inp_key, numb);
		if (step == NULL)
		{
			if (hash_t[numb].get_head() == NULL)
				throw 1;
			else if (hash_t[numb].get_head()->val.key == inp_key)
				return hash_t[numb].get_head()->val.val;
			else throw 1;
		}
		else
		{
			return step->node->val.val;
		}
	}
};
#endif;