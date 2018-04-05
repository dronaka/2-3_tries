#pragma once
#ifndef HEADER.H
#define HEADER.H

struct node {
private:
	int size;      // ���������� ������� ������
	int key[3];
	node *first;   // *first <= key[0];
	node *second;  // key[0] <= *second < key[1];
	node *third;   // key[1] <= *third < key[2];
	node *fourth;  // kye[2] <= *fourth.
	node *parent; //��������� �� �������� ����� ��� ����, ������ ��� ����� ����� ����� �������� ��� ��������

	bool find(int k) { // ���� ����� ���������� true, ���� ���� k ��������� � �������, ����� false.
		for (int i = 0; i < size; ++i)
			if (key[i] == k) return true;
		return false;
	}

	void swap(int &x, int &y) {
		int r = x;
		x = y;
		y = r;
	}

	void sort2(int &x, int &y) {
		if (x > y) swap(x, y);
	}

	void sort3(int &x, int &y, int &z) {
		if (x > y) swap(x, y);
		if (x > z) swap(x, z);
		if (y > z) swap(y, z);
	}

	void sort() { // ����� � �������� ������ ���� �������������
		if (size == 1) return;
		if (size == 2) sort2(key[0], key[1]);
		if (size == 3) sort3(key[0], key[1], key[2]);
	}

	void insert_to_node(int k) {  // ��������� ���� k � ������� (�� � ������)
		key[size] = k;
		size++;
		sort();
	}

	void remove_from_node(int k) { // ������� ���� k �� ������� (�� �� ������)
		if (size >= 1 && key[0] == k) {
			key[0] = key[1];
			key[1] = key[2];
			size--;
		}
		else if (size == 2 && key[1] == k) {
			key[1] = key[2];
			size--;
		}
	}

	void become_node2(int k, node *first_, node *second_) {  // ������������� � 2-�������.
		key[0] = k;
		first = first_;
		second = second_;
		third = nullptr;
		fourth = nullptr;
		parent = nullptr;
		size = 1;
	}

	bool is_leaf() { // �������� �� ���� ������; �������� ������������ ��� ������� � ��������.
		return (first == nullptr) && (second == nullptr) && (third == nullptr);
	}

public:
	// ��������� ������ ����� ������� ������ � ����� ������
	node(int k) : size(1), key{ k, 0, 0 }, first(nullptr), second(nullptr),
		third(nullptr), fourth(nullptr), parent(nullptr) {}

	node(int k, node *first_, node *second_, node *third_, node *fourth_, node *parent_) :
		size(1), key{ k, 0, 0 }, first(first_), second(second_),
		third(third_), fourth(fourth_), parent(parent_) {}

	friend node *split(node *item); // ����� ��� ���������� ������� ��� ������������;
	friend node *insert(node *p, int k); // ������� � ������;
	friend node *search(node *p, int k); // ����� � ������;
	friend node *search_min(node *p); // ����� ������������ �������� � ���������; 
	friend node *merge(node *leaf); // ������� ������������ ��� ��������;
	friend node *redistribute(node *leaf); // ����������������� ����� ������������ ��� ��������;
	friend node *fix(node *leaf); // ������������ ����� �������� ��� ����������� ������� ������ (���������� merge ��� redistribute) 
	friend node *remove(node *p, int k); // �������� ����� �� ������;
};

#endif // !HEADER.H
