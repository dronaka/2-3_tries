#include "Header.h"

struct node *insert(struct node *p, int k)
{
	if (!p) return new node(k);
	if (p->is_leaf()) p->insert_to_node(k);
	else if (k <= p->key[0]) insert(p->first, k);
	else if ((p->size == 1) || ((p->size == 2) && k <= p->key[1])) insert(p->second, k);
	else insert(p->third, k);

	return split(p);
}

struct node *split(struct node *item)
{
	if (item->size < 3) return item;
	struct node *x = new node(item->key[0], item->first, item->second, nullptr, nullptr, item->parent);
	struct node *y = new node(item->key[2], item->third, item->fourth, nullptr, nullptr, item->parent);

	if (x->first) x->first->parent = x;
	if (x->second) x->second->parent = x;
	if (y->first) y->first->parent = y;
	if (y->second) y->second->parent = y;

	if (item->parent)
	{
		item->parent->insert_to_node(item->key[1]);

		if (item->parent->first == item) item->parent->first = nullptr;
		else if (item->parent->second == item) item->parent->second = nullptr;
		else if (item->parent->third == item) item->parent->third = nullptr;

		if (item->parent->first == nullptr) {
			item->parent->fourth = item->parent->third;
			item->parent->third = item->parent->second;
			item->parent->second = y;
			item->parent->first = x;
		}
		else if (item->parent->second == nullptr) {
			item->parent->fourth = item->parent->third;
			item->parent->third = y;
			item->parent->second = x;
		}
		else {
			item->parent->fourth = y;
			item->parent->third = x;
		}
		node *tmp = item->parent;
		delete item;
		return tmp;
	}
	else {
        x->parent = item;   // “ак как в эту ветку попадает только корень,
        y->parent = item;   // то мы "родителем" новых вершин делаем раздел€ющийс€ элемент.
        item->become_node2(item->key[1], x, y);
        return item;
    }
}
	
struct node *search(node *p, int k)
{
	if (!p) return nullptr;

	if (p->find(k)) return p;

	if (k < p->key[0]) return search(p->first, k);
	else if (p->size == 2 && k < p->key[1] || p->size == 1) return search(p->second, k);
	else if (p->size == 2) return search(p->third, k);
}

struct node *search_min(node *p) 
{
	if (!p) return p;

	if (!(p->first)) return p;
	else return search_min(p->first);
}

struct node *remove(node *p, int k) { 
	node *item = search(p, k); 

	if (!item) return p;

	node *min = nullptr;
	if (item->key[0] == k) min = search_min(item->second); 
	else min = search_min(item->third);

	if (min) { 
		int &z = (k == item->key[0] ? item->key[0] : item->key[1]);
		item->swap(z, min->key[0]);
		item = min; 
	}

	item->remove_from_node(k); 
	return fix(item); 
}