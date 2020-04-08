#include <gtest.h>
#include <Table.h>

TEST(Val_Collum_, can_create_collum)
{
	ASSERT_NO_THROW(Val_Collum<Polinom> col);
}

TEST(Val_Collum_, can_create_collum_with_Polinom)
{
	int key = 13424;
	string s = "-x";
	Polinom p(s);
	ASSERT_NO_THROW(Val_Collum<Polinom> col(key, p));
}

TEST(Val_Collum_, can_do_operation_equal)
{
	int key = 13423;
	string s = "-xy";
	Polinom p(s);
	Val_Collum<Polinom> col1(key, p);
	Val_Collum<Polinom> col2;
	ASSERT_NO_THROW(col2 = col1);
}

TEST(Table_, can_get_table_from_file)
{
	Table<Polinom> tab;
	string s = "C:\\Users\\Tom\\Desktop\\Polinom_test2.csv";
	ASSERT_NO_THROW(tab.get_table_from_file(s));
}

TEST(Table_, can_save_table_to_file)
{
	Table<Polinom> tab;
	string s = "C:\\Users\\Tom\\Desktop\\Polinom_test2.csv";
	tab.get_table_from_file(s);
	s = "C:\\Users\\Tom\\Desktop\\Polinom_test4.csv";
	tab.push_table_to_file(s);
	ASSERT_NO_THROW(tab.get_table_from_file(s));
}

TEST(Unordered_Table_, can_find_something_on_table_from_file)
{
	Unordered_Table<Polinom> tab;
	string s = "C:\\Users\\Tom\\Desktop\\Polinom_test2.csv";
	tab.get_table_from_file(s);
	string p_s = "xyz";
	Polinom p(p_s);
	EXPECT_EQ(true, (p == tab.key_find(126)));
}

TEST(Unordered_Table_, can_create_table)
{
	ASSERT_NO_THROW(Unordered_Table<Polinom> t);
}

TEST(Unordered_Table_, can_create_table_with_custom_size)
{
	ASSERT_NO_THROW(Unordered_Table<Polinom> t(25));
}

TEST(Unordered_Table_, can_get_current_size)
{
	Unordered_Table<Polinom> t(25);
	EXPECT_EQ(0, t.get_cur_size());
}

TEST(Unordered_Table_, can_get_max_size)
{
	Unordered_Table<Polinom> t(25);
	EXPECT_EQ(25, t.get_max_size());
}

TEST(Unordered_Table_, can_push_elem)
{
	Unordered_Table<Polinom> t(10);
	int key = 13423;
	string s = "-xy";
	Polinom p(s);
	ASSERT_NO_THROW(t.key_push(key, p));
}

TEST(Unordered_Table_, can_change_cur_size_after_pushing)
{
	Unordered_Table<Polinom> t(10);
	int key = 13423;
	string s = "-xy";
	Polinom p(s);
	t.key_push(key, p);
	EXPECT_EQ(1, t.get_cur_size());
}

TEST(Unordered_Table_, can_repack_table)
{
	Unordered_Table<Polinom> t(1);
	int key = 13423;
	string s = "-xy";
	Polinom p(s);
	t.key_push(key, p);
	ASSERT_NO_THROW(t.key_push(key, p));
}

TEST(Unordered_Table_, can_change_max_size_after_repacking)
{
	Unordered_Table<Polinom> t(1);
	int key = 13423;
	string s = "-xy";
	Polinom p(s);
	t.key_push(key, p);
	t.key_push(key, p);
	EXPECT_EQ(11, t.get_max_size());
}

TEST(Unordered_Table_, can_find_elem_from_table)
{
	Unordered_Table<Polinom> t(10);
	int key = 13423;
	string s = "-xy";
	Polinom p(s);
	t.key_push(key, p);
	key++;
	t.key_push(key, p);
	ASSERT_NO_THROW(t.key_find(13423));
}

TEST(Unordered_Table_, can_delete_elem_from_table)
{
	Unordered_Table<Polinom> t(10);
	int key = 13423;
	string s = "-xy";
	Polinom p(s);
	t.key_push(key, p);
	key++;
	t.key_push(key, p);
	ASSERT_NO_THROW(t.key_delete(13423));
}

TEST(Unordered_Table_, cant_delete_elem_with_wrong_key)
{
	Unordered_Table<Polinom> t(10);
	int key = 13423;
	string s = "-xy";
	Polinom p(s);
	t.key_push(key, p);
	key++;
	t.key_push(key, p);
	ASSERT_ANY_THROW(t.key_delete(13));
}

TEST(Unordered_Table_, can_change_cur_size_after_deleting_elem)
{
	Unordered_Table<Polinom> t(10);
	int key = 13423;
	string s = "-xy";
	Polinom p(s);
	t.key_push(key, p);
	key++;
	t.key_push(key, p);
	t.key_delete(13423);
	EXPECT_EQ(1, t.get_cur_size());
}
