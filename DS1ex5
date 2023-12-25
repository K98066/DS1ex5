#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits>
#include <sstream>
#include <iomanip>

class Pokemon {
public:
    int id;
    std::string name;
    std::string type1;
    std::string type2;
    int hp;
    int attack;
    int defense;

    Pokemon(int id, const std::string& name, const std::string& type1, const std::string& type2,
            int total, int hp, int attack, int defense)
        : id(id), name(name), type1(type1), type2(type2), hp(hp), attack(attack), defense(defense) {}
};

class TreeNode {
public:
    Pokemon* data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(Pokemon* data) : data(data), left(NULL), right(NULL) {}
    ~TreeNode() {
        delete data;
    }
};

class BinarySearchTree {
private:
    TreeNode* root;
    int treeHeight;

    void insertNode(TreeNode*& node, Pokemon* data) {
        if (node == NULL) {
            node = new TreeNode(data);
        } else if (data->hp >= node->data->hp) {
            insertNode(node->right, data);
        } else {
            insertNode(node->left, data);
        }
    }

    int calculateHeight(TreeNode* node) {
        if (node == NULL) {
            return 0;
        } else {
            int leftHeight = calculateHeight(node->left);
            int rightHeight = calculateHeight(node->right);
            return 1 + std::max(leftHeight, rightHeight);
        }
    }

    TreeNode* findLeftmostNode(TreeNode* node) {
        while (node->left != NULL) {
            node = node->left;
        }
        return node;
    }

    TreeNode* findRightmostNode(TreeNode* node) {
        while (node->right != NULL) {
            node = node->right;
        }
        return node;
    }
    
        
    void printHeapHelper(TreeNode* root, int a) const {
    	// a equal data number
    	if (root) {
        	std::cout << std::left << '[' << a << std::setw(6) << ']' << std::setw(8) << root->data->id << std::setw(32) << root->data->name << std::setw(16) << root->data->type1
			<< std::setw(8) << root->data->hp << std::setw(8) << root->data->attack << std::setw(8) << root->data->defense << std::endl;
			a++;
        	printHeapHelper(root->left, a);
        	printHeapHelper(root->right, a);
    	}
	}

public:
    BinarySearchTree() : root(NULL), treeHeight(0) {}

    void insert(Pokemon* data) {
        insertNode(root, data);
    }

    int getHeight() {
        treeHeight = calculateHeight(root);
        return treeHeight;
    }

    Pokemon* getLeftmost() {
        TreeNode* leftmostNode = findLeftmostNode(root);
        return leftmostNode->data;
    }

    Pokemon* getRightmost() {
        TreeNode* rightmostNode = findRightmostNode(root);
        return rightmostNode->data;
    }

    void printHeap() const {
        printHeapHelper(root, 1);
    }
};

void heapify(std::vector<Pokemon*>& pokemonList, int index) {
    int max_index = index;
    int left_child = 2 * index + 1;
    int right_child = 2 * index + 2;
    int size = pokemonList.size();

    if (left_child < size && pokemonList[left_child]->hp > pokemonList[max_index]->hp) {
        max_index = left_child;
    }

    if (right_child < size && pokemonList[right_child]->hp > pokemonList[max_index]->hp) {
        max_index = right_child;
    }

    if (max_index != index) {
        std::swap(pokemonList[index], pokemonList[max_index]);
        heapify(pokemonList, max_index);
    }
}

void heapRebuild(std::vector<Pokemon*>& pokemonList) {
    // Convert the array into a max heap based on hp values
    for (int i = pokemonList.size() / 2 - 1; i >= 0; --i) {
        heapify(pokemonList, i);
    }
}



int main() {
	int command;
    std::vector<Pokemon*> pokemonList;
    int id, total, hp, attack, defense;
    std::string name, type1, type2;
    BinarySearchTree bst;

	while (true) {
		std::cout << "\n";
    	std::cout << "***** Pokemon Tree and Heap *****\n";
    	std::cout << "* 0. Quit                       *\n";
    	std::cout << "* 1. Read a file to build BST   *\n";
    	std::cout << "* 2. Transform it into Max Heap *\n";
    	std::cout << "*********************************\n";
    	std::cout << "Input a choice(0, 1, 2): ";
    	std::cin >> command;
		
		if (command == 0) {
			return 0;
		}
		else if (command == 1) {
			std::cout << "\nInput a file number [0:quit]:";
			
    		std::string fileName;
    		// 從使用者輸入中讀取檔案編號
    		std::cin >> fileName;

    		// 組合檔案名稱	 ex:"input401.txt"
			fileName = "input" + fileName + ".txt";

    		// 步驟1
    		std::cout << std::left << std::setw(8) << '\0' << std::setw(8) << '#' << std::setw(32) << "Name"
			<< std::setw(16) << "Type 1" << std::setw(8) << "HP" << std::setw(8) << "Attack" << std::setw(8) << "Defense" << std::endl;

    		// 讀取檔案
			std::ifstream inputFile(fileName);
			if (!inputFile.is_open()) {
		   	 std::cerr << "Error opening file." << std::endl;
			    return 1;
			}
	
			// 忽略第一列欄位名稱
			std::string header;
			std::getline(inputFile, header);
		
		
			// 讀取資料並建立 Pokemon 物件
			while (inputFile >> id >> name >> type1 >> type2 >> total >> hp >> attack >> defense) {
			    // 這裡只讀取前七項資料，忽略剩餘的 
			    
		  		Pokemon* newPokemon = new Pokemon(id, name, type1, type2, total, hp, attack, defense);
		 		pokemonList.push_back(newPokemon);
		 		
		    	// 忽略剩餘行尾
		    	inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	
		    	// 步驟1
		    	std::cout << std::left << '[' << pokemonList.size() << std::setw(6) << ']' << std::setw(8) << id << std::setw(32) << name << std::setw(16) << type1 << std::setw(8)
              	<< hp << std::setw(8) << attack << std::setw(8) << defense << std::endl;
			}

    		inputFile.close();

	    	// 步驟2
	   		for (Pokemon* pokemon : pokemonList) {
	    	    bst.insert(pokemon);
    		}

    		// 步驟3
    		int height = bst.getHeight();
    		Pokemon* leftmost = bst.getLeftmost();
    		Pokemon* rightmost = bst.getRightmost();

    		// 輸出樹高、最左側和最右側節點對應的資料
    		std::cout << "\nHP tree height = " << height << std::endl;
    		
    		std::cout << "Leftmost node:" << std::endl;    		
    		std::cout << std::left << std::setw(8) << '\0' << std::setw(8) << '#' << std::setw(32) << "Name"
			<< std::setw(16) << "Type 1" << std::setw(8) << "HP" << std::setw(8) << "Attack" << std::setw(8) << "Defense" << std::endl;
    		
    		std::cout << std::left << '[' << leftmost->id << std::setw(6) << ']' << std::setw(8) << leftmost->id << std::setw(32) << leftmost->name << std::setw(16) << leftmost->type1 << std::setw(8)
              << leftmost->hp << std::setw(8) << leftmost->attack << std::setw(8) << leftmost->defense << std::endl;
              
    		std::cout << "Rightmost node:" << std::endl;
    		std::cout << std::left << std::setw(8) << '\0' << std::setw(8) << '#' << std::setw(32) << "Name"
			<< std::setw(16) << "Type 1" << std::setw(8) << "HP" << std::setw(8) << "Attack" << std::setw(8) << "Defense" << std::endl;
   			std::cout << '[' << rightmost->id << std::setw(6) << ']' << std::setw(8) << rightmost->id  << std::setw(32) << rightmost->name << std::setw(16) << rightmost->type1 << std::setw(8)
              << rightmost->hp << std::setw(8) << rightmost->attack << std::setw(8) << rightmost->defense << std::endl;
              
		}
		if (command == 2) {
		    // Call heapRebuild to convert the Pokemon array to a heap based on hp values
   			heapRebuild(pokemonList);

    		// Display the resulting heap
    		std::cout << std::left << std::setw(8) << '\0' << std::setw(8) << '#' << std::setw(32) << "Name"
			<< std::setw(16) << "Type 1" << std::setw(8) << "HP" << std::setw(8) << "Attack" << std::setw(8) << "Defense" << std::endl;
    		bst.printHeap();
    		
    		// 步驟3
    		int height = bst.getHeight();
    		Pokemon* leftmost = bst.getLeftmost();
    		Pokemon* rightmost = bst.getRightmost();

    		// 輸出樹高、最左側和最右側節點對應的資料
    		
    		std::cout << "HP tree height = " << height << std::endl;
    		
    		std::cout << "Leftmost node:" << std::endl;    		
    		std::cout << std::left << std::setw(8) << '\0' << std::setw(8) << '#' << std::setw(32) << "Name"
			<< std::setw(16) << "Type 1" << std::setw(8) << "HP" << std::setw(8) << "Attack" << std::setw(8) << "Defense" << std::endl;
    		
    		std::cout << std::left << '[' << leftmost->id << std::setw(6) << ']' << std::setw(8) << leftmost->id << std::setw(32) << leftmost->name << std::setw(16) << leftmost->type1 << std::setw(8)
              << leftmost->hp << std::setw(8) << leftmost->attack << std::setw(8) << leftmost->defense << std::endl;
              
    		std::cout << "Buttom:" << std::endl;
    		std::cout << std::left << std::setw(8) << '\0' << std::setw(8) << '#' << std::setw(32) << "Name"
			<< std::setw(16) << "Type 1" << std::setw(8) << "HP" << std::setw(8) << "Attack" << std::setw(8) << "Defense" << std::endl;
   			std::cout << '[' << rightmost->id << std::setw(6) << ']' << std::setw(8) << rightmost->id  << std::setw(32) << rightmost->name << std::setw(16) << rightmost->type1 << std::setw(8)
              << rightmost->hp << std::setw(8) << rightmost->attack << std::setw(8) << rightmost->defense << std::endl;
		} 
		
    	// 釋放記憶體
    	for (Pokemon* pokemon : pokemonList) {
        	delete pokemon;
    	}

	}	
}
