#include <iostream>
#include <utility>
using namespace std;
enum Color
{
	BLACK,
	RED
};

template <class K, class V>
struct RBNode
{
	pair<K, V> _value;
	Color _color;
	RBNode<K, V>* _parent;
	RBNode<K, V>* _left;
	RBNode<K, V>* _right;

	RBNode(const pair<K, V>& value = pair<K,V>())
		:_value(value)
		, _color(RED)
		, _parent(nullptr)
		, _left(nullptr)
		, _right(nullptr)
	{}
};

template <class K, class V>
class RBTree
{
public:
	typedef RBNode<K, V> Node;

	RBTree()
		:_header(new Node)
	{
		_header->_left = _header->_right = _header;
	}

	bool insert(const pair<K, V>& val)
	{
		//空树
		if (_header->_parent == nullptr)
		{
			//创建第一个根节点
			Node* root = new Node(val);
			//根节点为黑色
			root->_color = BLACK;

			_header->_parent = root;
			root->_parent = _header;

			_header->_left = root;
			_header->_right = root;

			return true;
		}
		//非空树
		Node* cur = _header->_parent;
		Node* parent = nullptr;
		while (cur)
		{
			parent = cur;
			//按照key值进行比较： pair.first
			if (cur->_value.first == val.first)
				return false;
			if (cur->_value.first < val.first)
				cur = cur->_right;
			else
				cur = cur->_left;
		}

		cur = new Node(val);
		if (parent->_value.first < val.first)
			parent->_right = cur;
		else
			parent->_left = cur;

		cur->_parent = parent;

		//调整： 修改颜色, 旋转
		while (cur != _header->_parent && cur->_parent->_color == RED)
		{
			Node* p = cur->_parent;
			Node* g = p->_parent;
			if (g->_left == p)
			{
				Node* u = g->_right;
				if (u && u->_color == RED)
				{
					//修改颜色
					u->_color = p->_color = BLACK;
					g->_color = RED;
					//继续向上查看
					cur = g;
				}
				else
				{
					//u不存在/u存在且为黑
					if (cur == p->_right)
					{
						RotateL(p);
						swap(cur, p);
					}
					//cur在p的左边,右旋
					RotateR(g);
					//修改颜色
					p->_color = BLACK;
					g->_color = RED;

					break;
				}
			}
			else
			{
				Node* u = g->_left;
				if (u && u->_color == RED)
				{
					//修改颜色
					u->_color = p->_color = BLACK;
					g->_color = RED;
					//继续向上查看
					cur = g;
				}
				else
				{
					//u不存在/u存在且为黑
					if (cur == p->_left)
					{
						RotateR(p);
						swap(cur, p);
					}
					//cur在p的左边,右旋
					RotateL(g);
					//修改颜色
					p->_color = BLACK;
					g->_color = RED;

					break;
				}
			}
		}

		//根颜色置为黑色
		_header->_parent->_color = BLACK;
		//更新_header的左，有
		_header->_left = leftMost();
		_header->_right = rightMost();
		return true;
	}

	Node* leftMost()
	{
		Node* cur = _header->_parent;
		while (cur && cur->_left)
			cur = cur->_left;
		return cur;
	}

	Node* rightMost()
	{
		Node* cur = _header->_parent;
		while (cur && cur->_right)
			cur = cur->_right;
		return cur;
	}

	void RotateR(Node* parent)
	{
		Node* subL = parent->_left;
		Node* subLR = subL->_right;

		subL->_right = parent;
		parent->_left = subLR;

		if (subLR)
			subLR->_parent = parent;

		if (parent == _header->_parent)
		{
			_header->_parent = subL;
			subL->_parent = _header;
		}
		else
		{
			Node* g = parent->_parent;
			subL->_parent = g;
			if (g->_left == parent)
				g->_left = subL;
			else
				g->_right = subL;
		}

		parent->_parent = subL;

	}

	void RotateL(Node* parent)
	{
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		subR->_left = parent;
		parent->_right = subRL;

		if (subRL)
			subRL->_parent = parent;

		if (parent == _header->_parent)
		{
			_header->_parent = subR;
			subR->_parent = _header;
		}
		else
		{
			Node* g = parent->_parent;
			subR->_parent = g;
			if (g->_left == parent)
				g->_left = subR;
			else
				g->_right = subR;
		}
		parent->_parent = subR;

	}

	void inorder()
	{
		_inorder(_header->_parent);
		cout << endl;
	}
	void _inorder(Node* root)
	{
		if (root)
		{
			_inorder(root->_left);
			cout << root->_value.first << " ";
			_inorder(root->_right);
		}
	}

private:
	Node* _header;
};

void testRBTree()
{
	RBTree<int, int>  rbt;
	rbt.insert(make_pair(1, 1));
	rbt.insert(make_pair(2, 1));
	rbt.insert(make_pair(3, 1));
	rbt.insert(make_pair(4, 1));
	rbt.insert(make_pair(5, 1));
	rbt.insert(make_pair(0, 1));
	rbt.insert(make_pair(9, 1));
	rbt.insert(make_pair(8, 1));
	rbt.insert(make_pair(7, 1));
	rbt.insert(make_pair(6, 1));
	rbt.inorder();
}


int main()
{
	testRBTree();
	return 0;
}