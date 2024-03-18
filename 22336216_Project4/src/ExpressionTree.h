#pragma once
#include <iostream>
#include <string>
#include <ctype.h>
#include <math.h>
#include <cmath>
#include <Windows.h>
#include <vector>
#include <unordered_map>
#include <stack>
#include <limits.h>
#include <queue>
using namespace std;



struct TreeNode {
	string word;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : word(""), left(nullptr), right(nullptr) {}
	TreeNode(string x) : word(x), left(nullptr), right(nullptr) {}
	TreeNode(string x, TreeNode* left, TreeNode* right) : word(x), left(left), right(right) {}
};

unordered_map<int, TreeNode*> roots;
unordered_map<int, TreeNode*> copyroots;

void Cls();
bool isValidString(string tmp);
TreeNode* ReadExpr(string prestr);
void Assign(TreeNode* root, string v, double c);
string WriteExpr(TreeNode* root);
double Value(TreeNode* root);
TreeNode* Compound(string p, TreeNode* root1, TreeNode* root2);
TreeNode* Copy(TreeNode* root);
bool isNumeric(string str);
void Merge(TreeNode* root);
TreeNode* Derivative(TreeNode* root, const string& variable);

bool isValidString(string tmp) {
	if (tmp == "") return false;
	for (size_t i = 0; i < tmp.size(); ++i) {
		char ch = tmp[i];
		if (!(isalnum(ch) || ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^')) {
			// 如果字符不是字母、数字，也不是指定的运算符，也不是三角函数的名称，则字符串不符合要求
			if (ch == 's' && i + 2 < tmp.size() && tmp[i + 1] == 'i' && tmp[i + 2] == 'n') {
				i += 2; // 跳过sin的两个字符
			}
			else if (ch == 'c' && i + 2 < tmp.size() && tmp[i + 1] == 'o' && tmp[i + 2] == 's') {
				i += 2; // 跳过cos的两个字符
			}
			else if (ch == 't' && i + 2 < tmp.size() && tmp[i + 1] == 'a' && tmp[i + 2] == 'n') {
				i += 2; // 跳过tan的两个字符
			}
			else {
				return false;
			}
		}
	}
	// 字符串符合要求
	return true;
}

void Cls() {
	int i = 0;
	cout << "|----------------------------------------------------------------------------------|" << endl;
	cout << "|----------------------------------表达式树生成器----------------------------------|" << endl;
	cout << "|-------------------------------------------------------22336216 陶宇卓------------|" << endl;
	cout << endl << "|--------------------------------------状态栏--------------------------------------|";
	for (auto x : copyroots) {
		cout << endl << "|--Ex" << i << ":" << WriteExpr(x.second);
		i++;
	}
	cout << endl << "|----------------------------------------------------------------------------------|" << endl << endl;
}

TreeNode* Copy(TreeNode* root) {
	if (root == nullptr) {
		return nullptr;
	}

	TreeNode* newRoot = new TreeNode(root->word);
	newRoot->left = Copy(root->left);
	newRoot->right = Copy(root->right);

	return newRoot;
}




//++//+*3^*3*2^x2x6

/**/


TreeNode* ReadExpr(string prestr) {
	prestr.erase(std::remove_if(prestr.begin(), prestr.end(), [](char c) { return std::isspace(static_cast<unsigned char>(c)); }), prestr.end());
	if (!isValidString(prestr)) return nullptr;
	stack<TreeNode*> postfix;
	int i = 0;
	for (i = prestr.size() - 1; i >= 0; i--) {
		if (isalnum(prestr[i])) {
			TreeNode* newnode = new TreeNode(string(1,prestr[i]));
			postfix.push(newnode);
		}
			if (prestr[i] == '+' || prestr[i] == '-' || prestr[i] == '*' || prestr[i] == '/' || prestr[i] == '^') {
				if (postfix.size() < 2) break;
				TreeNode* leftn = postfix.top(); postfix.pop();
				TreeNode* rightn = postfix.top(); postfix.pop();
				TreeNode* newnode = new TreeNode(string(1, prestr[i]), leftn, rightn);
				postfix.push(newnode);
			}
			if (prestr[i] == 'n' && i - 2 >= 0 && prestr[i - 1] == 'i' && prestr[i - 2] == 's') {
				postfix.pop();
				if (postfix.size() < 1) break;
				TreeNode* leftn = postfix.top(); postfix.pop();
				TreeNode* newnode = new TreeNode("sin", leftn, nullptr);
				postfix.push(newnode);
				i = i - 2;
			}
			if (prestr[i] == 's' && i - 2 >= 0 && prestr[i - 1] == 'o' && prestr[i - 2] == 'c') {
				postfix.pop();
				if (postfix.size() < 1) break;
				TreeNode* leftn = postfix.top(); postfix.pop();
				TreeNode* newnode = new TreeNode("cos", leftn, nullptr);
				postfix.push(newnode);
				i = i - 2;
			}
			if (prestr[i] == 'n' && i - 2 >= 0 && prestr[i - 1] == 'a' && prestr[i - 2] == 't') {
				postfix.pop();
				if (postfix.size() < 1) break;
				TreeNode* leftn = postfix.top(); postfix.pop();
				TreeNode* newnode = new TreeNode("tan", leftn, nullptr);
				postfix.push(newnode);
				i = i - 2;
			}
		
	}
	if (i == -1) return postfix.top();
	else return nullptr;
	
}

void printTree(TreeNode* root, int indent = 0) {
	if (root == nullptr) {
		return;
	}

	// 输出右子树，右子树在上方，所以缩进增加
	printTree(root->right, indent + 4);

	// 输出当前节点
	for (int i = 0; i < indent; ++i) {
		std::cout << " ";
	}
	std::cout << root->word << std::endl;

	// 输出左子树
	printTree(root->left, indent + 4);
}


string WriteExpr(TreeNode* root) {
	if (!root) return "";
	if (root->word == "+" || root->word == "-" || root->word == "*" || root->word == "/" || root->word == "^" ) {
		return "(" + WriteExpr(root->left) + root->word + WriteExpr(root->right) + ")";
	}	
	if (root->word == "sin" || root->word == "cos" || root->word == "tan") {
		return root->word + "(" + WriteExpr(root->left) + ")";
	}
	return root->word;
}

void Assign(TreeNode* root, string v, double c) {
	if (root == nullptr) {
		return;
	}

	// 如果当前节点是变量节点，并且与给定的变量v相等，则替换为c
	if (root->word == v) {
		root->word = to_string(c); // 将整数转换为字符
	}

	// 递归处理左子树和右子树
	Assign(root->left, v, c);
	Assign(root->right, v, c);
}

double Value(TreeNode* root) {//后序遍历求值
	if (root == nullptr) {
		return 0.0;
	}
	if (root->word.size() == 1 && isalpha(atoi(root->word.c_str()))) {
		return 0.0;
	}
	// 如果节点是操作符
	if (root->word == "+" || root->word == "-" || root->word == "*" || root->word == "/" || root->word == "^" || root->word == "sin" || root->word == "cos" || root->word == "tan") {
		double leftValue = Value(root->left);
		double rightValue = Value(root->right);

		// 根据操作符进行相应的运算
		if (root->word == "+")
			return leftValue + rightValue;
		if (root->word == "-")
			return leftValue - rightValue;
		if (root->word == "*")
			return leftValue * rightValue;
		if (root->word == "/") {
			// 避免除以0的情况
			if (rightValue != 0) {
				return leftValue / rightValue;
			}
			else {
				cout << "ERROR!" << endl;
				return 0; // 返回一个默认值
			}
		}
		if (root->word == "^") {
			if (leftValue == 0 && rightValue == 0) {
				return 1;
			}
			return pow(leftValue, rightValue);
		}
		if (root->word == "sin")
			return sin(leftValue);
		if (root->word == "cos")
			return cos(leftValue);
		if (root->word == "tan")
			return tan(leftValue);
	}
	else {
		// 如果节点是数字，直接返回其值
		return (double)stoi(root->word); // 假设表达式树中的数字都是单个数字字符
	}
	return 0;
}

TreeNode* Compound(string p, TreeNode* root1, TreeNode* root2) {
	TreeNode* compoundRoot = new TreeNode(p, root1, root2);
	return compoundRoot;
}

void Init() {
	roots.clear();
	copyroots.clear();
}

TreeNode* Derivative(TreeNode* root, const string& variable) {
	if (root == nullptr) {
		return nullptr;
	}

	// 如果节点是变量节点，且变量名匹配，导数为 1
	if (root->word.size() == 1 && root->word == variable)
		return new TreeNode("1");

	

	// 如果节点是操作符节点
	if (root->word == "+") {
		TreeNode* leftDerivative = Derivative(root->left, variable);
		TreeNode* rightDerivative = Derivative(root->right, variable);
		return new TreeNode("+", leftDerivative, rightDerivative);
	}
	else if (root->word == "-") {
		TreeNode* leftDerivative = Derivative(root->left, variable);
		TreeNode* rightDerivative = Derivative(root->right, variable);
		return new TreeNode("-", leftDerivative, rightDerivative);
	}
	else if (root->word == "*") {
		TreeNode* left = new TreeNode("*", Derivative(root->left, variable), root->right);
		TreeNode* right = new TreeNode("*", root->left, Derivative(root->right, variable));
		return new TreeNode("+", left, right);
	}
	else if (root->word == "/") {//答辩 
		TreeNode* numerator = new TreeNode("-", new TreeNode("*", Derivative(root->left, variable), root->right),
			new TreeNode("*", root->left, Derivative(root->right, variable)));
		TreeNode* denominator = new TreeNode("^", root->right, new TreeNode("2"));
		return new TreeNode("/", numerator, denominator);
	}
	else if (root->word == "^") {
		if (root->left->word == variable) {
			TreeNode* exponent = new TreeNode("-", root->right, new TreeNode("1"));
			TreeNode* base = new TreeNode("^", root->left, root->right);
			TreeNode* product = new TreeNode("*", exponent, base);
			return product;
		}
		else {
			TreeNode* base = new TreeNode("^", root->left, root->right);
			TreeNode* lnBase = new TreeNode("ln", root->left, nullptr);
			TreeNode* exponent = new TreeNode("*", root->right, lnBase);
			TreeNode* powerRule = new TreeNode("*", base, exponent);
			return powerRule;
		}
	}
	// 其他操作符的处理可以扩展 但是不会（
	if (root->word != variable)
		return root;

	return nullptr;
}

bool isNumeric(string str) {
	for (char ch : str) {
		if (!std::isdigit(ch)) {
			return false;
		}
	}
	return true;
}

void Merge(TreeNode* root) {
	if (root == nullptr) {
		return ;
	}
	cout << isNumeric(root->word) << endl;
	if (isNumeric(root->word)) return ;
	Merge(root->left);
	Merge(root->right);

	// 如果当前节点的左右子树都是常数，则将当前节点的值替换为它们的计算结果
	if (root->left && root->right && isNumeric(root->left->word) && isNumeric(root->right->word)) {
		int leftValue = stoi(root->left->word);
		cout << leftValue << endl;
		int rightValue = stoi(root->right->word);
		cout << rightValue << endl;
		if (root->word == "+") {
			root->word = to_string(leftValue + rightValue);
		}
		else if (root->word == "-") {
			root->word = to_string(leftValue - rightValue);
		}
		else if (root->word == "*") {
			root->word = to_string(leftValue * rightValue);
		}
		else if (root->word == "/") {
			if (rightValue == 0) return;
			root->word = to_string(leftValue / rightValue);
		}
		else if (root->word == "^") {
			root->word = to_string(pow(leftValue,rightValue));
		}

		// 清空左右子树，将当前节点设为叶子节点
		if (root->left) delete root->left;
		if (root->right)delete root->right;
		root->left = nullptr;
		root->right = nullptr;
	}

	return ;
}