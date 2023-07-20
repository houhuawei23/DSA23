#include "binary_tree.h"

int main() {
	char str[500];
	string ss;

	getline(cin, ss);
	strcpy(str, ss.c_str());

	BTNode* root = NULL;

	CreateTree(root, str);

	DispTree(root);
	cout << endl;

	cout << getHeight(root) << endl;

	return 0;
} 