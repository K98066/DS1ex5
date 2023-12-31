//  DS1ex5  27  11020117林子皓  11020134呂宗凱 

#include <iostream>
#include <vector>
#include <string.h>
#include <fstream>
#include <limits>
#include <sstream>
#include <iomanip>
#include <cctype>
#include <cmath>

class Pokemon
{
public:
	int num;
    int id;
    std::string name;
    std::string type1;
    std::string type2;
    int hp;
    int attack;
    int defense;

    Pokemon(int num, int id, const std::string &name, const std::string &type1, const std::string &type2,
            int total, int hp, int attack, int defense)
        : num(num), id(id), name(name), type1(type1), type2(type2), hp(hp), attack(attack), defense(defense) {}
};

class TreeNode
{
public:
    Pokemon *data;
    TreeNode *left;
    TreeNode *right;

    TreeNode(Pokemon *data) : data(data), left(NULL), right(NULL) {}
    ~TreeNode()
    {
        delete data;
    }
};

class BinarySearchTree
{
private:
    TreeNode *root;
    int treeHeight;

    void insertNode(TreeNode *&node, Pokemon *data)
    {
        if (node == NULL)
        {
            node = new TreeNode(data);
        }
        else if (data->hp >= node->data->hp)
        {
            insertNode(node->right, data);
        }
        else
        {
            insertNode(node->left, data);
        }
    }

    int calculateHeight(TreeNode *node)
    {
        if (node == NULL)
        {
            return 0;
        }
        else
        {
            int leftHeight = calculateHeight(node->left);
            int rightHeight = calculateHeight(node->right);
            return 1 + std::max(leftHeight, rightHeight);
        }
    }

    TreeNode *findLeftmostNode(TreeNode *node)
    {
        while (node->left != NULL)
        {
            node = node->left;
        }
        return node;
    }

    TreeNode *findRightmostNode(TreeNode *node)
    {
        while (node->right != NULL)
        {
            node = node->right;
        }
        return node;
    }

    void printHeapHelper(TreeNode *root, int a) const
    {
        // a equal data number
        if (root)
        {
            std::cout << std::left << '[' << a << std::setw(6) << ']' << std::setw(8) << root->data->id << std::setw(32) << root->data->name << std::setw(16) << root->data->type1
                    << std::setw(8) << root->data->hp << std::setw(8) << root->data->attack << std::setw(8) << root->data->defense << std::endl;
            a++;
            printHeapHelper(root->left, a);
            printHeapHelper(root->right, a);
        }
    }

    void clearTree(TreeNode* node) {
        if (node != nullptr) {
            clearTree(node->left);
            clearTree(node->right);
            delete node; // TreeNode 的解構子會刪除 data
            node = nullptr;
        }
    }

public:
    BinarySearchTree() : root(NULL), treeHeight(0) {}
    ~BinarySearchTree() {
        clearTree(root); // 清除整棵樹
    }

    void insert(Pokemon *data)
    {
        insertNode(root, data);
    }

    int getHeight()
    {
        treeHeight = calculateHeight(root);
        return treeHeight;
    }

    Pokemon *getLeftmost()
    {
        TreeNode *leftmostNode = findLeftmostNode(root);
        return leftmostNode->data;
    }

    Pokemon *getRightmost()
    {
        TreeNode *rightmostNode = findRightmostNode(root);
        return rightmostNode->data;
    }

    void printHeap() const
    {
        printHeapHelper(root, 1);
    }
};

void heapify(std::vector<Pokemon*>& pokemons, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && pokemons[left]->hp > pokemons[largest]->hp) {
        largest = left;
    }

    if (right < n && pokemons[right]->hp > pokemons[largest]->hp) {
        largest = right;
    }

    if (largest != i) {
        std::swap(pokemons[i], pokemons[largest]);
        heapify(pokemons, n, largest);
    }
}

void buildMaxHeapFromBottom(std::vector<Pokemon*>& pokemons) {
    int n = pokemons.size();

    // Start from the last non-leaf node and heapify all nodes in reverse order
    for (int i = n / 2 - 1; i >= 0; --i) {
        heapify(pokemons, n, i);
    }
}

void rebuildHeap(std::vector<Pokemon*>& pokemons) {
    buildMaxHeapFromBottom(pokemons);
}

int calculateTreeHeight(int n) {
    // Height of a heap with n nodes is ceil(log2(n + 1)) - 1
    return static_cast<int>(std::ceil(std::log2(n + 1))) - 1;
}

void printLeftmostNode(const Pokemon* leftmost) {
    std::cout << std::left << '[' << leftmost->num << std::setw(6) << ']' << std::setw(8) << leftmost->id << std::setw(32) << leftmost->name << std::setw(16) << leftmost->type1
        << std::setw(8) << leftmost->hp << std::setw(8) << leftmost->attack << std::setw(8) << leftmost->defense << std::endl;
}

void printBottomNode(const Pokemon* bottomNode) {
    std::cout << std::left << '[' << bottomNode->num << std::setw(6) << ']' << std::setw(8) << bottomNode->id << std::setw(32) << bottomNode->name << std::setw(16) << bottomNode->type1
        << std::setw(8) << bottomNode->hp << std::setw(8) << bottomNode->attack << std::setw(8) << bottomNode->defense << std::endl;
}


int main()
{
	std::vector<Pokemon*> pokemon_arr; 
    int command;
    int arr_num = 0;
    std::vector<Pokemon*> pokemonList;
    int num;
    int id, total, hp, attack, defense;
    std::string name, type1, type2, namep;
    BinarySearchTree bst;
    char c;

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
            for (Pokemon* pokemon : pokemonList) {
                delete pokemon;
                pokemon = nullptr;
            }
            return 0;
        } else if (command == 1) {
            std::cout << "\nInput a file number [0:quit]:";

            std::string fileName;
            // 從使用者輸入中讀取檔案編號
            std::cin >> fileName;

            // 組合檔案名稱	 ex:"input501.txt"
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
            while (true)
            {
                // 這裡只讀取前七項資料，忽略剩餘的
                inputFile >> id >> name >> type1;
				
				if(type1 == "Mime") {
					name = name + " " + type1;
					inputFile >> type1;
				}
				inputFile >> type2;
                
                if (!isdigit(type2[0])) {
                	inputFile >> total >> hp >> attack >> defense;
				}
				else {
					inputFile >> hp >> attack >> defense;
					total = 0;
				}
				
				 // 任務二的資料陣列 
                Pokemon *add_pokemon = new Pokemon(num, id, name, type1, type2, total, hp, attack, defense);
                pokemon_arr.push_back(add_pokemon);				
				
				num = pokemonList.size()+1;
                Pokemon *newPokemon = new Pokemon(num, id, name, type1, type2, total, hp, attack, defense);
                                
                pokemonList.push_back(newPokemon);

                // 忽略剩餘行尾
                inputFile.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                
                if (!inputFile) {
					break;
				}

                // 步驟1
                std::cout << std::left << '[' << pokemonList.size() << std::setw(6) << ']' << std::setw(8) << id << std::setw(32) << name << std::setw(16) << type1 << std::setw(8)
                        << hp << std::setw(8) << attack << std::setw(8) << defense << std::endl;

            }
			
            inputFile.close();

            // 步驟2
            for (Pokemon *pokemon : pokemonList) {
                bst.insert(pokemon);
            }

            // 步驟3
            int height = bst.getHeight();
            Pokemon *leftmost = bst.getLeftmost();
            Pokemon *rightmost = bst.getRightmost();

            // 輸出樹高、最左側和最右側節點對應的資料
            std::cout << "\nHP tree height = " << height << std::endl;

            std::cout << "Leftmost node:" << std::endl;
            std::cout << std::left << std::setw(8) << '\0' << std::setw(8) << '#' << std::setw(32) << "Name"
                    << std::setw(16) << "Type 1" << std::setw(8) << "HP" << std::setw(8) << "Attack" << std::setw(8) << "Defense" << std::endl;

            std::cout << std::left << '[' << leftmost->num << std::setw(6) << ']' << std::setw(8) << leftmost->id << std::setw(32) << leftmost->name << std::setw(16) << leftmost->type1 << std::setw(8)
                    << leftmost->hp << std::setw(8) << leftmost->attack << std::setw(8) << leftmost->defense << std::endl;

            std::cout << "Rightmost node:" << std::endl;
            std::cout << std::left << std::setw(8) << '\0' << std::setw(8) << '#' << std::setw(32) << "Name"
                    << std::setw(16) << "Type 1" << std::setw(8) << "HP" << std::setw(8) << "Attack" << std::setw(8) << "Defense" << std::endl;
            std::cout << '[' << rightmost->num << std::setw(6) << ']' << std::setw(8) << rightmost->id << std::setw(32) << rightmost->name << std::setw(16) << rightmost->type1 << std::setw(8)
                    << rightmost->hp << std::setw(8) << rightmost->attack << std::setw(8) << rightmost->defense << std::endl;
        }
        if (command == 2) {
            // Call heapRebuild to convert the Pokemon array to a heap based on hp values
            rebuildHeap(pokemon_arr);

            // Display the resulting heap
            std::cout << std::left << std::setw(8) << '\0' << std::setw(8) << '#' << std::setw(32) << "Name"
                    << std::setw(16) << "Type 1" << std::setw(8) << "HP" << std::setw(8) << "Attack" << std::setw(8) << "Defense" << std::endl;
            
            int a = 1;
            for (const auto& pokemon : pokemon_arr) {
        		std::cout << std::left << '[' << a << std::setw(6) << ']' << std::setw(8) << pokemon->id << std::setw(32) << pokemon->name << std::setw(16) << pokemon->type1
                    << std::setw(8) << pokemon->hp << std::setw(8) << pokemon->attack << std::setw(8) << pokemon->defense << std::endl;
                a++;
    		}

            // 步驟3
            int treeHeight = calculateTreeHeight(pokemon_arr.size());

            // 輸出樹高、最左側和最右側節點對應的資料

            std::cout << "HP tree height = " << treeHeight << std::endl;

            std::cout << "Leftmost node:" << std::endl;
            std::cout << std::left << std::setw(8) << '\0' << std::setw(8) << '#' << std::setw(32) << "Name"
                    << std::setw(16) << "Type 1" << std::setw(8) << "HP" << std::setw(8) << "Attack" << std::setw(8) << "Defense" << std::endl;

            printLeftmostNode(pokemon_arr.front());

            std::cout << "Buttom:" << std::endl;
            std::cout << std::left << std::setw(8) << '\0' << std::setw(8) << '#' << std::setw(32) << "Name"
                    << std::setw(16) << "Type 1" << std::setw(8) << "HP" << std::setw(8) << "Attack" << std::setw(8) << "Defense" << std::endl;
            printBottomNode(pokemon_arr.back());
        }
    }
}
