/* Дано бинарное дерево. В узлах бинарного дерева хранятся слова.
 Определить поддерево максимальной длины, в качестве ключа используется
 целое число. В найденном поддереве найти слово минимальной длины.*/


#include <iostream>
#include <queue>
#include <climits>
#include <algorithm>

struct Node {
    int key;
    std::string word;
    Node* left;
    Node* right;

    Node() {}
    Node(int _key, std::string _word) : key(_key), word(_word), left(nullptr), right(nullptr) {}
};

Node* createNode(int key, std::string word) {
    Node* newNode = new Node;
    newNode->key = key;
    newNode->word = word;
    newNode->left = nullptr;
    newNode->right = nullptr;
    return newNode;
}

Node* insertNode(Node* root, int key, std::string word) {
    if (root == nullptr) {
        return createNode(key, word);
    }

    if (key < root->key) {
        root->left = insertNode(root->left, key, word);
    } else {
        root->right = insertNode(root->right, key, word);
    }

    return root;
}

int maxDepth(Node* root); // Function prototype

Node* findMaxSubtree(Node* root, int& maxLength) {
    if (root == nullptr) {
        return nullptr;
    }

    int leftLength = maxDepth(root->left);
    int rightLength = maxDepth(root->right);

    if (leftLength + rightLength > maxLength) {
        maxLength = leftLength + rightLength;
        return root;
    }

    Node* leftSubtree = findMaxSubtree(root->left, maxLength);
    Node* rightSubtree = findMaxSubtree(root->right, maxLength);

    if (leftSubtree) {
        return leftSubtree;
    } else {
        return rightSubtree;
    }
}

std::string findMinWord(Node* root) {
    if (root == nullptr) {
        return "";
    }

    std::queue<Node*> q;
    q.push(root);
    std::string minWord = root->word;

    while (!q.empty()) {
        Node* current = q.front();
        q.pop();

        if (current->word.length() < minWord.length()) {
            minWord = current->word;
        }

        if (current->left) {
            q.push(current->left);
        }
        if (current->right) {
            q.push(current->right);
        }
    }

    return minWord;
}

int maxDepth(Node* root) {
    if (root == nullptr) {
        return 0;
    }

    int leftDepth = maxDepth(root->left);
    int rightDepth = maxDepth(root->right);

    return std::max(leftDepth, rightDepth) + 1;
}




int main() {
    // Создание бинарного дерева и вставка узлов
    Node* root = nullptr;
    root = insertNode(root, 5, "apple");
    root = insertNode(root, 3, "banana");
    root = insertNode(root, 8, "orange");
    root = insertNode(root, 2, "pear");
    root = insertNode(root, 6, "grape");
    root = insertNode(root, 1, "kiwi");
    root = insertNode(root, 4, "melon");

    // Поиск поддерева максимальной длины
    int maxLength = 0;
    Node* maxSubtree = findMaxSubtree(root, maxLength);

    // Вывод исходного дерева
    std::cout << "Исходное бинарное дерево:\n";
    std::cout << "   5\n";
    std::cout << "  / \\\n";
    std::cout << " 3   8\n";
    std::cout << "/ \\ / \\\n";
    std::cout << "2 4 6\n";
    std::cout << "/\n";
    std::cout << "1\n\n";

    // Вывод поддерева максимальной длины
    std::cout << "Поддерево максимальной длины:\n";
    std::cout << "   " << maxSubtree->key << "\n";
    std::cout << "  / \\\n";
    if (maxSubtree->left) {
        std::cout << " " << maxSubtree->left->key;
    } else {
        std::cout << "  ";
    }
    if (maxSubtree->right) {
        std::cout << "   " << maxSubtree->right->key << "\n";
    } else {
        std::cout << "   \n";
    }
    std::cout << "\n";

    // Поиск слова минимальной длины в поддереве
    std::string minWord = findMinWord(maxSubtree);

    // Вывод результата
    std::cout << "Слово минимальной длины в поддереве: " << minWord << "\n";

    return 0;
}
