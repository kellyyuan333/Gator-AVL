#include <iostream>
#include <string>
#include <queue>
#include <sstream>
#include <regex>

using namespace std;

/* Note: 
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope. 
*/

class AVLTree
{
	private:
		class Node //Amanpreet Kapoor Trees Powerpoint, slide 31
		{
			public:
			string name;
			string id;
			int height;
			Node* left;
			Node* right;
			Node(string theName, string theId) : name(theName), id(theId), height(1), left(nullptr), right(nullptr) {}
		};
		Node* root = nullptr; //initialize root pointer
		Node* insertHelper(Node* root, string theName, string theId) //helper function for insert using recursion
		{
			if (root == nullptr)
			{
				cout << "successful" << endl;
				return new Node(theName, theId);
			}
			if (theId < root->id)
			{
				root->left = insertHelper(root->left, theName, theId);
			}
			else
			{
				root->right = insertHelper(root->right, theName, theId);
			}
			root->height = calculateHeight(root); //update height
			if (balanceFactor(root) == 2 && balanceFactor(root->left) == 1) //left-left case
			{
				root = rotateRight(root);
			}
			else if (balanceFactor(root) == -2 && balanceFactor(root->right) == -1) //right-right case
			{
				root = rotateLeft(root);
			}
			else if (balanceFactor(root) == -2 && balanceFactor(root->right) == 1) //right-left case
			{
				root = rotateRightLeft(root);
			}
			else if (balanceFactor(root) == 2 && balanceFactor(root->left) == -1) //left-right case
			{
				root = rotateLeftRight(root);
			}
			return root;
		}
		Node* rotateLeft(Node* root) //Amanpreet Kapoor Balanced Trees Powerpoint, slide 14
		{
			Node* grandchild = root->right->left;
			Node* newParent = root->right;
			newParent->left = root;
			root->right = grandchild;
			return newParent;
		}
		Node* rotateRight(Node* root)
		{
			Node* grandchild = root->left->right;
			Node* newParent = root->left;
			newParent->right = root;
			root->left = grandchild;
			return newParent;
		}
		Node* rotateRightLeft(Node* root)
		{
			root->right = rotateRight(root->right); //perform right rotation first
			Node* newParent = rotateLeft(root); //perform left rotation next
			return newParent;
		}
		Node* rotateLeftRight(Node* root)
		{
			root->left = rotateLeft(root->left); //perform left rotation first
			Node* newParent = rotateRight(root); //perform right rotation next
			return newParent;
		}
		int calculateHeight(Node* root) //used to get balance factor
		{
			int height = 0;
			int leftSubtree;
			int rightSubtree;
			if (root == nullptr)
			{
				return 0;
			}
			else
			{
				leftSubtree = calculateHeight(root->left);
				rightSubtree = calculateHeight(root->right);
			}
			height = max(leftSubtree, rightSubtree) + 1; //height is the maximum height of the left subtree or the right subtree + 1 since we started at 0
			return height;
		}
		int balanceFactor(Node* root) //used to determine if rotations are necessary, and which type of rotation to execute
		{
			int bf = 0;
			if (root == nullptr)
			{
				return 0;
			}
			else
			{
				bf = calculateHeight(root->left) - calculateHeight(root->right); //balance factor = height of left subtree - height of right subtree
				return bf;
			}
		}
		void traverseIds(Node* root, vector<string>& ids) //used to check if id is already in the tree
		{
			if (root == nullptr) 
			{
				return;
			}
			ids.push_back(root->id); //preorder traversal to get all ids
			traverseIds(root->left, ids);
			traverseIds(root->right, ids);
		}
		bool validInput(Node* root, string theName, string theId) //tests if inputted name and id satisfy the data constraints
		{
			vector<string> ids; //id must be unique
			traverseIds(root, ids);
			for (long long unsigned int i = 0; i < ids.size(); i++)
			{
				if (ids[i] == theId)
				{
					cout << "unsuccessful" << endl;
					return false;
				}
			}
			if (theId.length() != 8) //id must be 8 digits
			{
				cout << "unsuccessful" << endl;
				return false;
			}
			for (char digit : theId) //id must be a valid number
			{
				if (!isdigit(digit))
				{
					cout << "unsuccessful" << endl;
					return false;
				}
			}
			for (long long unsigned int i = 0; i < theName.length(); i++) //name must be a valid word
			{
				char letter = theName[i];
				if (!isalpha(letter) && letter != ' ')
				{
					cout << "unsuccessful" << endl; 
					return false;
				}
			}
			return true;
		}
		void resetRoot() //deletes root and sets it to child or null if child does not exist
		{
			cout << "successful" << endl;
			delete root;
		}
		Node* removeHelper(Node* node, string theId) //helper function for remove using recursion
		{
			if (node == nullptr)
			{
				return node;
			}
			if (node->left != nullptr && stoi(theId) < stoi(node->id))
			{
				node->left = removeHelper(node->left, theId);
			}
			else if (node->right != nullptr && stoi(theId) > stoi(node->id))
			{
				node->right = removeHelper(node->right, theId);
			}
			else //theId = node->id
			{
				if (node->left == nullptr) //no left child
				{
					if (node == root)
					{
						Node* temp = node->right;
						resetRoot();
						root = temp;
						return root;
					}
					else
					{
						Node* temp = node->right;
						cout << "successful" << endl;
						node = nullptr;
						delete node;
						return temp;
					}
				}
				else if (node->right == nullptr) //no right child
				{
					if (node == root)
					{
						Node* temp = node->left;
						resetRoot();
						root = temp;
						return root;
					}
					else
					{
						Node* temp = root->left;
						cout << "successful" << endl;
						node = nullptr;
						delete node;
						return temp;
					}
				}
				else //both left and right children exist
				{
					Node* succ = node->right;
					while (succ->left != nullptr) //find inorder successor
					{
						succ = succ->left;
					}
					node->name = succ->name;
					node->id = succ->id;
					node->height = succ->height;
					node->right = removeHelper(node->right, succ->id);
				}
			}
			return node;
		}
		void traverseInorder(Node* root, vector<string>& names) //Amanpreet Kapoor Trees Powerpoint, slide 52
		{
			if (root == nullptr) 
			{
				return;
			}
			traverseInorder(root->left, names);
			names.push_back(root->name);
			traverseInorder(root->right, names);
		}
		void traversePreorder(Node* root, vector<string>& names) //Amanpreet Kapoor Trees Powerpoint, slide 52
		{
			if (root == nullptr) 
			{
				return;
			}
			names.push_back(root->name);
			traversePreorder(root->left, names);
			traversePreorder(root->right, names);
		}
		void traversePostorder(Node* root, vector<string>& names) //Amanpreet Kapoor Trees Powerpoint, slide 52
		{
			if (root == nullptr) 
			{
				return;
			}
			traversePostorder(root->left, names);
			traversePostorder(root->right, names);
			names.push_back(root->name);
		}
		bool searchNameHelper(Node* root, string theName, bool found) //helper function for searchName using recursion
		{
			if (root == nullptr)
			{
				return found;
			}
			if (root->name == theName)
			{
				cout << root->id << endl;
				found = true;
			}
			if (searchNameHelper(root->left, theName, found))
			{
				found = true;
			}
			if (searchNameHelper(root->right, theName, found))
			{
				found = true;
			}
			return found;
		}
		Node* searchIdHelper(Node* root, string theId) //helper function for searchId using recursion
		{
			if (root == nullptr)
			{
				return nullptr;
			}
			if (stoi(theId) == stoi(root->id))
			{
				return root;
			}
			if (root->left != nullptr && stoi(theId) < stoi(root->id))
			{
				return searchIdHelper(root->left, theId);
			}
			else if (root->right != nullptr && stoi(theId) > stoi(root->id))
			{
				return searchIdHelper(root->right, theId);
			}
			return nullptr;
		}
		vector<string> printIdsInorder() //used for catch testing
		{
			vector<string> ids;
			traverseIdsInorder(root, ids);
			if (ids.size() == 0)
			{
				return ids;
			}
			for (long long unsigned int i = 0; i < ids.size() - 1; i++) 
			{
				cout << ids[i] << ", ";
			}
			cout << ids.back() << endl; //print last name with not comment and go to the next line
			return ids;
		}
		void traverseIdsInorder(Node* root, vector<string>& ids) //gets all the ids of the nodes in inorder order
		{
			if (root == nullptr) 
			{
				return;
			}
			traverseIdsInorder(root->left, ids);
			ids.push_back(root->id); //inorder traversal to get all ids
			traverseIdsInorder(root->right, ids);
		}
		void deleteTree(Node* root) //used for destructor to delete all nodes and handle memory
		{
			if (root == nullptr)
			{
				return;
			}
			else
			{
				deleteTree(root->left);
				deleteTree(root->right);
				delete root;
			}
		}
	public:
		Node* insert(string theName, string theId) //Amanpreet Kapoor Trees Powerpoint, slide 34
		{
			theName.erase(std::remove(theName.begin(), theName.end(), '\"' ), theName.end()); // https://stackoverflow.com/questions/5674374/remove-double-quotes-from-a-string-in-c
			if (!validInput(root, theName, theId)) //name and id must satsify the constraints
			{
				return root;
			}
			root = insertHelper(root, theName, theId); //call helper function
			return root;
		}
		void searchId(string theId)
		{
			Node* result = searchIdHelper(root, theId); //call helper function
			if (result != nullptr)
			{
				cout << result->name << endl;
			}
			else
			{
				cout << "unsuccessful" << endl; //id not found in the tree
			}
		}
		Node* remove(string theId, ostream& os = cout)
		{
			if (searchIdHelper(root, theId) == nullptr) //id must be in the tree
			{
				os << "unsuccessful" << endl;
				return root;
			}
			return removeHelper(root, theId); //call helper function
		}
		void searchName(string theName, ostream& os = cout)
		{
			theName.erase(std::remove(theName.begin(), theName.end(), '\"' ), theName.end()); // https://stackoverflow.com/questions/5674374/remove-double-quotes-from-a-string-in-c
			bool theFound = false;
			bool result = searchNameHelper(root, theName, theFound); //call helper function
			if (!result)
			{
				os << "unsuccessful" << endl; //name not found in the tree
			}
		}
		vector<string> printInorder()
		{
			vector<string> names;
			traverseInorder(root, names); //get all the names of the nodes in inorder order
			if (names.size() == 0)
			{
				return names;
			}
			for (long long unsigned int i = 0; i < names.size() - 1; i++) 
			{
				cout << names[i] << ", ";
			}
			cout << names.back() << endl; //print last name with not comment and go to the next line
			return names;
		}
		vector<string> printPreorder()
		{
			vector<string> names;
			traversePreorder(root, names); //get all the names of the nodes in preorder order
			if (names.size() == 0)
			{
				return names;
			}
			for (long long unsigned int i = 0; i < names.size() - 1; i++) 
			{
				cout << names[i] << ", ";
			}
			cout << names.back() << endl; //print last name with not comment and go to the next line
			return names;
		}
		vector<string> printPostorder()
		{
			vector<string> names;
			traversePostorder(root, names); //get all the names of the nodes in postorder order
			if (names.size() == 0)
			{
				return names;
			}
			for (long long unsigned int i = 0; i < names.size() - 1; i++) 
			{
				cout << names[i] << ", ";
			}
			cout << names.back() << endl; //print last name with not comment and go to the next line
			return names;
		}
		void printLevelCount()
		{
			if (root == nullptr) //tree has no nodes
			{
				cout <<  "0" << endl;
				return;
			}
			int levelCount = 1;
			queue<Node*> q;
			q.push(root);
			Node* level = root; //push the root onto the queue to indicate the separation between levels
			q.push(level);
			bool firstIteration = true;
			while (!q.empty())
			{
				Node* node = q.front();
				q.pop();
				if (node == level && !firstIteration)
				{
					q.push(level); //adds a root pointer to the queue after the current level is traversed
					if (q.front() == level)
					{
						break; //if you see two levels, then you have reached end of queue
					}
					levelCount++;
				}
				if (firstIteration) //since we use a root pointer to indicate levels, the first iteration will be different
				{
					if (node->left != nullptr)
					{
						q.push(node->left);
					}
					if (node->right != nullptr)
					{
						q.push(node->right);
					}
				}
				else
				{
					if (node->left != nullptr && node != level)
					{
						q.push(node->left);
					}
					if (node->right != nullptr && node != level)
					{
						q.push(node->right);
					}
				}
				firstIteration = false;
			}
			cout << levelCount << endl;
		}
		Node* removeInorder(long long unsigned int n, ostream& os = cout)
		{
			vector<string> ids;
			string targetId;
			traverseIdsInorder(root, ids); //get all the names of the nodes in inorder order
			if (n >= ids.size()) //the nth node does not exist
			{
				os << "unsuccessful" << endl;
				return root;
			}
			else
			{
				targetId = ids[n]; //get target id
				Node* result = remove(targetId); //remove target node
				return result;
			}
		}
		~AVLTree() //destructor
		{
			deleteTree(root);
		}
};

int main()
{
	int numLines;
	cin >> numLines; //get number of lines that will be inputted
	cin.ignore();
	string str;
	AVLTree tree; //create tree
    for (int i = 0; i < numLines; i++)
	{
		getline(cin, str);
        istringstream function(str); // https://cplusplus.com/reference/sstream/stringstream/
        string call; //determines which function to call
        function >> call;
        if (call == "insert") 
		{
            string name;
            string id;
			string skip;
			getline(getline(function, skip, '"'), name, '"'); // https://stackoverflow.com/questions/33072293/reading-quoted-string-in-c
            function >> id;
			tree.insert(name, id); //call insert function
        } 
		else if (call == "remove") 
		{
            string id;
            function >> id;
            tree.remove(id); //call remove function
        } 
		else if (call == "search")
		{
			string arg;
			function >> arg;
			bool num = true;
			for (char digit : arg) //determines if input is a number or not
			{
				if (!isdigit(digit))
				{
					num = false;
				}
			}
			if (num) //if input is a number
			{
				tree.searchId(arg); //call searchId function
			}
			else //if input is not a number
			{
				tree.searchName(arg); //call searchName function
			}
        } 
		else if (call == "printInorder") 
		{
            tree.printInorder(); //call printInorder function
        } 
		else if (call == "printPreorder") 
		{
            tree.printPreorder(); //call printPreorder function
        } 
		else if (call == "printPostorder") 
		{
            tree.printPostorder(); //call printPostorder function
        } 
		else if (call == "printLevelCount") 
		{
        	tree.printLevelCount(); //call printLevelCount function
        } 
		else if (call == "removeInorder") 
		{
            int n;
            function >> n;
            tree.removeInorder(n); //call removeInorder function
        } 
		else
		{
			cout << "unsuccessful" << endl;
		}
    }
	return 0;
}
