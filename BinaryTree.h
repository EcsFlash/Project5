#pragma once
template <typename T>
class BinaryTree {
protected:
	struct TreeNode {
		T data;
		int height;
		TreeNode* left;
		TreeNode* right;
	};
	TreeNode* root;

	int Height(TreeNode* node)
	{
		return node ? node->height : 0;
	}

	bool isEmpty()
	{
		if (root == nullptr) {
			return true;
		}
		else {
			return false;
		}
	}
	void commitHeight(TreeNode* node)
	{
		if (!node)
		{
			return;
		}
		int left = Height(node->left);
		int right = Height(node->right);
		node->height = (left > right ? left : right) + 1;
	}

	int Bfactor(TreeNode* node)
	{
		return  Height(node->right) - Height(node->left);
	}
	void RightRotation(TreeNode*& p)
	{

		TreeNode* q = p->left;
		p->left = q->right;
		q->right = p;
		commitHeight(p);
		commitHeight(q);
		p = q;
	}

	void LeftRotation(TreeNode*& p)
	{
		TreeNode* q = p->right;
		p->right = q->left;
		q->left = p;
		commitHeight(p);
		commitHeight(q);
		p = q;
	}

	void balance(TreeNode*& p)
	{
		commitHeight(p);
		int bfactor = Bfactor(p);
		if (bfactor == 2)
		{
			if (Bfactor(p->right) < 0)
				RightRotation(p->right);
			LeftRotation(p);
		}

		if (bfactor == -2)
		{
			if (Bfactor(p->left) > 0)
				LeftRotation(p->left);
			RightRotation(p);
		}
	}

	virtual void Insert(TreeNode*& node, T elem) {
		if (node == nullptr) {
			node = new TreeNode{ elem, 1, nullptr, nullptr };
		}
		else if (elem < node->data) {
			Insert(node->left, elem);
		}
		else {
			Insert(node->right, elem);
		}
		balance(node);

	}
	T findDelMin(TreeNode*& node) {
		if (node->left) {
			return findDelMin(node->left);
		}
		else {
			T result = node->data;
			TreeNode* temp = node;
			node = node->right;
			delete temp;
			temp = nullptr;
			return result;
		}
		balance(node);
	}
	void clear(TreeNode*& node)
	{
		if (node != nullptr)
		{
			clear(node->left);
			clear(node->right);
			delete node;
			node = nullptr;
		}
	}
	int getWidth(int height) const {
		if (height == 1) {
			return 1;
		}
		return 2 * getWidth(height - 1);
	}
	
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
		if (node) {
			os << node->data << "  ";
			print(node->left, os);
			print(node->right, os);
		}
		
	}
	void postOrder(TreeNode* node){
		if (node) {
			postOrder(node->left);
			postOrder(node->right);
			cout << node->data << "  ";
		}
	}
public:
	BinaryTree() {
		root = nullptr;
	}
	~BinaryTree() {
		clear();
	}

	virtual void Insert(T elem) {
		Insert(root, elem);
	}
	bool isOnlyRoot() const {
		return root && !root->left && !root->right;
	}

	T findDelMin() {
		return findDelMin(root);
	}
	void clear() {
		return clear(root);
	}

	friend ostream& operator<<(ostream& os, const BinaryTree<T>& tree) {
		//os << tree.print(tree.root);
		tree.print(tree.root, os);
		return os;
	}
	void remove(TreeNode*& node) {
		if (node) {
			if (!node->left && node->right) {
				TreeNode* temp = node;
				node = node->right;
				delete temp;
			}
			else if (node->left && !node->right) {
				TreeNode* temp = node;
				node = node->left;
				delete temp;
			}
			else if (!node->left && !node->right) {
				delete node;
				node = nullptr;
			}
			else if (node->left && node->right) {
				TreeNode* temp = node;
				TreeNode* succ = node->left;
				while (succ->right != nullptr) {
					succ = succ->right;
				}
				succ->right = node->right;
				node = succ;
				delete temp;
			}
			balance(node);
		}
	}
	void postOrder() {
		postOrder(root);
	}
};
