#pragma once
#include "BinaryTree.h"
#include <windows.h> 
struct Tuple {
	char W;
	int cnt;
	bool operator<(Tuple& t) {
		return W < t.W;
	}
	bool operator==(Tuple& t) {
		return W == t.W;
	}
	bool operator>(Tuple& t) {
		return W > t.W;
	}
	friend ostream& operator<<(ostream& os, Tuple& t) {
		return os << t.W;
	}
};

class BSTCT : public BinaryTree<Tuple> {
protected:
	void Insert(TreeNode*& node, Tuple elem) {
		if (node == nullptr) {
			node = new TreeNode{ elem, 1, nullptr, nullptr };
		}
		else if (elem < node->data) {
			Insert(node->left, elem);
		}
		else if (elem > node->data) {
			Insert(node->right, elem);
		}
		else {
			node->data.cnt++;
		}
		balance(node);

	};

	virtual void print(TreeNode* node, ostream& os) const {
		/*int levels = (root->height)-1;
		int width = getWidth(root->height);
		for (int i = 0; i < width / 2; i++) {
			os << "\t";
		}
		os << node->data;
		for (int i = 0; i < width / 2; i++) {
			os << "\t";
		}
		os << endl;*/
		//самые нижние по одному табу,
		//  
		if (node) {
			if (node->data.cnt > 1) {
				HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
				SetConsoleTextAttribute(hConsole, 2);
				os << node->data << "  ";
				SetConsoleTextAttribute(hConsole, 15);
			}
			else {
				os << node->data << "  ";
			}
			print(node->left, os);
			print(node->right, os);
		}

	}
	void display(TreeNode* node, int space, ostream& os) const {
		if (node == nullptr) {
			return;
		}
		space += 10;
		display(node->right, space, os);
		os << endl;
		for (int i = 10; i < space; i++)
			os << " ";
		if (node->data.cnt > 1) {
			HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
			SetConsoleTextAttribute(hConsole, 2);
			os << node->data << "  ";
			SetConsoleTextAttribute(hConsole, 15);
		}
		else {
			os << node->data << endl;
		}
		display(node->left, space, os);
	}

	void removeAllNotUnique(TreeNode*& node) {
		if (node) {
			if (node->data.cnt > 1) {
				remove(node);
			}
			removeAllNotUnique(node->left);
			removeAllNotUnique(node->right);
			balance(node);
		}
	}
public:
	BSTCT(): BinaryTree(){

	}
	void Insert(char elem) {
		Insert(root, Tuple{ elem, 1 });
	};
	void removeAllNotUnique() {
		removeAllNotUnique(root);
	}
	friend ostream& operator<<(ostream& os, const BSTCT& tree) {
		//os << tree.print(tree.root);
		tree.display(tree.root, 0, os);
		return os;
	}
};