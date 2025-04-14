/*
    node is unbalanced when abs(height of right subtree - height of left subtree) > 1, the bracket quantity is also called balance factor.
    a node is right heavy if balance factor is +1, if -1 then its left heavy, if 0 then its perfectly balanced.
    
    type of rotation (rotation to be perfomed if you find any unbalanced node when u recurse back after inserting):
    1. if a node is right heavy and its right child is not left heavy then do a left rotation.
    2. if a node is left heavy and its left child is not right heavy then do a right rotation.
    3. if a node is right heavy and its right child is left heavy, then perform a right rotation on right child and then do a left rotation on the node.
    4. if a node is left heavy and its left child is right heavy then do a left rotation on left child and then a right rotation on node.

    3 and 4 point can be easily visualised, reason been that it will still be unbalanced beacause there was already some one sided heavyness at the child
    node been rotated.
*/

/*
    Regarding duplicate keys, the std::map doesn't have duplicate keys.
    Moreover duplicate keys make search redundat. For ex, if I assume that a node, go to its left
    branch when key < node.key and go to right branch when key >= node.key. However during rotations,
    it is possible that duplicae keys come on the left branch, which were initially in the right branch.
    Hence, need to look at both the branches.

    So all depends on use case and storing duplicate keys makes no sense. Rather we can store a count
    But in this case, I will not store count.
*/
class avl {
    private:
        struct node {
            int value;
            int height; // height of the tree with this node as parent node
            node* left;
            node* right;
        };
        node* ROOT = NULL;
        node* rotate(node* root, int dir) { //  returns the updated parent node, -1 represents left while +1 right rotation
            node* updated_root;
            if(dir == -1) {
                updated_root = root->right;
                node* updated_root_left_child = updated_root->left;
                updated_root->left = root;
                root->right = updated_root_left_child;
            } else {
                updated_root = root->left;
                node* updated_root_right_child = updated_root->right;
                updated_root->right = root;
                root->left = updated_root_right_child;
            }
            return updated_root;
        }
        node* balance(node* root) { // returns the updated parent node
            int lh = 0, rh = 0;
            int rc_rh = 0, rc_lh = 0;
            int lc_rh = 0, lc_lh = 0;
            if(root->left != NULL) {
                lh = root->left->height;
                if(root->left->left != NULL) lc_lh = root->left->left->height;
                if(root->left->right != NULL) lc_rh = root->left->right->height;
            }
            if(root->right != NULL) {
                rh = root->right->height;
                if(root->right->left != NULL) rc_lh = root->right->left->height;
                if(root->right->right != NULL) rc_rh = root->right->right->height;
            }
            int bf = rh - lh; // here bf is the balance factor;
            int rc_bf = rc_rh - rc_lh; // here bf is the balance factor;
            int lc_bf = lc_rh - lc_lh; // here bf is the balance factor;
            if(bf <= 1) return root;
            // here we need to check the four conditions that we discussed at top
            node* updated_root;
            if(bf > 0) {
                if(rc_bf < 0){
                    root->right = rotate(root->right, +1);
                }
                updated_root = rotate(root, -1);
            } else {
                if(lc_bf > 0) {
                    root->left = rotate(root->left, -1);
                }
                updated_root = rotate(root, +1);
            }
            return updated_root;
        }
        node* insert(node* root, int value) {
            if(root == NULL) {
                node* a = new node;
                a->height = 0;
                a->left = NULL;
                a->right = NULL;
                a->value = value;
                return a;
            }
            if(value < root->value) {
                root->left = insert(root->left, value);
                root->height = max(root->height, root->left->height + 1);
            } else {
                root->right = insert(root->right, value);
                root->height = max(root->height, root->right->height + 1);
            }
            // perform balancing after each insertion
            return balance(root);
            // return root;
        }
        bool find(node* root, int value) {
            if(root == NULL) return false;
            if(root->value == value) return true;
            if(value < root->value) return find(root->left, value);
            else return find(root->right, value);
        }

        void inorder(node* root) {
            if(root == NULL) return;
            inorder(root->left);
            cout << root->value << " ";
            inorder(root->right);
            return;
        }
        // there are not duplicates, perform a simple dfs 
        node* del(node* root, int value, int flag) {
            if(root == NULL) return NULL;
            if(value == root->value) flag = 1;
            if(flag) {
                int temp;
                int is_leaf = 1;
                if(root->left != NULL) {
                    is_leaf = 0;
                    temp = root->left->value;
                    root->left = del(root->left, value, flag);
                } else if(root->right != NULL){
                    is_leaf = 0;
                    temp = root->right->value;
                    root->right = del(root->right, value, flag);
                }
                if(is_leaf){
                    // delete it from memory, : todo
                    delete root;
                    return NULL;
                } else {
                    root->value = temp;
                }
            } else {
                if(value < root->value) {
                    root->left = del(root->left, value, flag);
                } else {
                    root->right = del(root->right, value, flag);
                }
            }
            //update the heights
            int lh = 0, rh = 0;
            if(root->left != NULL) lh = root->left->height;
            if(root->right != NULL) rh = root->right->height;
            root->height = max(lh, rh);
            root->height += (root->right != NULL || root->left != NULL);
            return balance(root);
        }
    public:
        avl() {
        }

        void insert(int value) {
            if(!find(value)) // dont insert duplicates, another way is store count. (TBD)
                ROOT = insert(ROOT, value);
        }

        void del(int value) {
            ROOT = del(ROOT, value, 0);
        }

        bool find(int value) { // dfs type search, just return the first occurence
            return find(ROOT, value);
        }

        void inorder() {
            inorder(ROOT);
            cout << "\n";
        }
}