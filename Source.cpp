#include <iostream>
using namespace std;
#include "BinaryTree.h"
#include "BinaryTreeChartT.h"
#include <string>

string removeDuplicate(string str)
{
	// Used as index in the modified string
	int index = 0;

	// Traverse through all characters
	for (int i = 0; i < str.length(); i++) {

		// Check if str[i] is present before it  
		int j;
		for (j = 0; j < i; j++)
			if (str[i] == str[j])
				break;

		// If not present, then add it to
		// result.
		if (j == i)
			str[index++] = str[i];
	}

	return str;
}

int main() {

	BSTCT i;
	/*char ch;
	string str;
	while (ch != '\n') {
		ch = cin.get();
		str.append(to_string(ch));
		i.Insert(ch);
	}*/
	i.Insert('h');
	i.Insert('o');
	i.Insert('i');
	i.Insert('p');
	i.Insert('p');
	i.Insert('p');
	i.Insert('t');
	i.Insert('a');
	cout << i;
	//i.removeAllNotUnique();
	//cout << i << endl;
	i.postOrder();
	



}