#include <gtest.h>
#include <Table.h>
/*
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

TEST(Ordered_Table_, can_create_ordered_table)
{
	ASSERT_NO_THROW(Ordered_Table<Polinom> t);
}

TEST(Ordered_Table_, can_create_ordered_table_with_custom_max_size)
{
	ASSERT_NO_THROW(Ordered_Table<Polinom> t(17));
}

TEST(Ordered_Table_, can_push_elem_to_ordered_table)
{
	Ordered_Table<Polinom> t;
	Polinom p;
	string s = "-xy";
	p.create_pol(s);
	ASSERT_NO_THROW(t.key_push(123, p));
}

TEST(Ordered_Table_, cant_push_elem_with_same_key)
{
	Ordered_Table<Polinom> t;
	Polinom p;
	string s = "-xy";
	p.create_pol(s);
	t.key_push(123, p);
	ASSERT_ANY_THROW(t.key_push(123, p));
}

TEST(Ordered_Table_, can_push_elem_to_additional_ordered_table)
{
	Ordered_Table<Polinom> t;
	Polinom p;
	string s = "-xy";
	p.create_pol(s);
	for (int i = 1; i <= 10; i++)
		t.key_push(i, p);
	ASSERT_NO_THROW(t.key_push(11, p));
}

TEST(Ordered_Table_, cant_push_elem_with_same_key_to_additional_order)
{
	Ordered_Table<Polinom> t;
	Polinom p;
	string s = "-xy";
	p.create_pol(s);
	for (int i = 1; i <= 13; i++)
		t.key_push(i, p);
	ASSERT_ANY_THROW(t.key_push(12, p));
}

TEST(Ordered_Table_, can_repack_table)
{
	Ordered_Table<Polinom> t;
	Polinom p;
	string s = "-xy";
	p.create_pol(s);
	for (int i = 1; i <= 15; i++)
		t.key_push(i, p);
	ASSERT_NO_THROW(t.key_push(16, p));
}

TEST(Ordered_Table_, can_find_elem_on_ordered_table_without_additional_table)
{
	Ordered_Table<Polinom> t;
	Polinom p;
	string s = "-xy";
	p.create_pol(s);
	t.key_push(123, p);
	ASSERT_NO_THROW(t.key_find(123));
}

TEST(Ordered_Table_, can_find_elem_on_ordered_table_with_additional_table)
{
	Ordered_Table<Polinom> t;
	Polinom p;
	string s = "-xy";
	p.create_pol(s);
	for (int i = 1; i <= 11; i++)
		t.key_push(i, p);
	ASSERT_NO_THROW(t.key_find(7));
}

TEST(Ordered_Table_, can_find_elem_on_ordered_table_after_repacking)
{
	Ordered_Table<Polinom> t;
	Polinom p;
	string s = "-xy";
	p.create_pol(s);
	for (int i = 1; i <= 15; i++)
		t.key_push(i, p);
	s = "-xy-y";
	p.create_pol(s);
	t.key_push(16, p);
	s = "-xy";
	Polinom p1;
	p1.create_pol(s);
	EXPECT_EQ(true, p1 == t.key_find(3));
}

TEST(Ordered_Table_, can_delete_elem_from_table)
{
	Ordered_Table<Polinom> t;
	Polinom p;
	string s = "-xy";
	p.create_pol(s);
	for (int i = 1; i <= 5; i++)
		t.key_push(i, p);
	ASSERT_NO_THROW(t.key_delete(3));
}

TEST(Ordered_Table_, can_delete_elem_from_additional_table)
{
	Ordered_Table<Polinom> t;
	Polinom p;
	string s = "-xy";
	p.create_pol(s);
	for (int i = 1; i <= 13; i++)
		t.key_push(i, p);
	ASSERT_NO_THROW(t.key_delete(12));
}

TEST(Ordered_Table_, can_repack_table_after_deleting_an_elem)
{
	Ordered_Table<Polinom> t;
	Polinom p;
	string s = "-xy";
	p.create_pol(s);
	for (int i = 1; i <= 15; i++)
		t.key_push(i, p);
	t.key_delete(8);
	t.key_delete(13);
	t.key_push(16, p);
	ASSERT_NO_THROW(t.key_push(17, p));
}
TEST(Ordered_Table_, cant_find_deleted_elem)
{
	Ordered_Table<Polinom> t;
	Polinom p;
	string s = "-xy";
	p.create_pol(s);
	for (int i = 1; i <= 15; i++)
		t.key_push(i, p);
	t.key_delete(8);
	t.key_delete(13);
	t.key_push(16, p);
	t.key_push(17, p);
	ASSERT_ANY_THROW(t.key_find(8));
}

TEST(Ordered_Table_, can_save_table_to_file)
{
	Ordered_Table<Polinom> t;
	Polinom p;
	string s = "-xy";
	p.create_pol(s);
	for (int i = 15; i >= 1; i--)
		t.key_push(i, p);
	string s1 = "C:\\Users\\Tom\\Desktop\\Polinom_test5.txt";
	ASSERT_NO_THROW(t.push_table_to_file(s1));
}

TEST(Ordered_Table_, can_get_table_from_file)
{
	Ordered_Table<Polinom> t;
	string s1 = "C:\\Users\\Tom\\Desktop\\Polinom_test5.txt";
	t.get_table_from_file(s1);
	ASSERT_NO_THROW(t.push_table_to_file(s1));
}
 */
TEST(Hash_Table_, can_create_hash)
{
	ASSERT_NO_THROW(Hash_Table<Polinom> t);
}

TEST (Hash_Table_, can_create_hash_with_custom_size)
{
	ASSERT_NO_THROW(Hash_Table<Polinom> t(25));
}
TEST(Hash_Table_, can_push_elem_to_hash_table)
{
	Hash_Table<Polinom> t;
	Polinom p;
	string s = "-xy";
	p.create_pol(s);
	ASSERT_NO_THROW(t.key_push(123, p));
}
TEST(Hash_Table_, can_push_elem_to_hash_table_t_2)
{
	Hash_Table<Polinom> t;
	Polinom p;
	string s = "-xy";
	p.create_pol(s);
	for (int i = 1; i <= 10; i++)
		t.key_push(i, p);
	ASSERT_NO_THROW(t.key_push(11, p));
}
TEST(Hash_Table_, can_delete_elem_from_table)
{
	Hash_Table<Polinom> t;
	Polinom p;
	string s = "-xy";
	p.create_pol(s);
	for (int i = 1; i <= 5; i++)
		t.key_push(i, p);
	ASSERT_NO_THROW(t.key_delete(3));
}
TEST(Hash_Table_, can_find_elem)
{
	Hash_Table<Polinom> t;
	Polinom p;
	string s = "-xy";
	p.create_pol(s);
	for (int i = 1; i <= 2; i++)
		t.key_push(i, p);
	s = "-xyz";
	p.create_pol(s);
	t.key_push(3, p);
	Polinom find;
	find = t.key_find(3);
	ASSERT_NO_THROW(find.print());
}