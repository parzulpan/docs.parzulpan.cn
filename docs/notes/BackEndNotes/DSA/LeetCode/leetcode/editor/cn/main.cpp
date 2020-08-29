#include "base-tree.h"

int main(int argc, char *argv[]) {

    cout << "pan: run main success." << endl;

    vector<int> levelOrderVector{1, 2, 3, -9999, 5, 35};

    BaseTree baseTree;

    TreeNode* root = baseTree.createTreeFromLevelOrderVector(levelOrderVector, levelOrderVector.size());
//    TreeNode* root = baseTree.createTreeFromLevelOrderVector(levelOrderVector);

    baseTree.levelOrderTraversal(root);
    cout << endl;
    baseTree.preOrderTraversal(root);
    cout << endl;
    baseTree.inOrderTraversal(root);
    cout << endl;
    baseTree.postOrderTraversal(root);
    cout << endl;
    cout << "pan: traversal success." << endl;

    return 0;
}