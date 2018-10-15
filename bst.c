/* Binary search trees */
#include <stdio.h>
#include <stdlib.h>
struct tree_node {
    struct tree_node* left;
    struct tree_node* right;
    int val;
};

typedef struct tree_node node;
node* root = NULL;
void addNode(node* sub_root, int val) {
    if(val > sub_root->val) {
        if(sub_root->right == NULL) {
            sub_root->right = (node*)malloc(sizeof(node));
            sub_root->right->right = NULL;
            sub_root->right->left = NULL;
            sub_root->right->val = val;
        } else {
        	addNode(sub_root->right, val);
        }
    } else {
        if(sub_root->left == NULL) {
            sub_root->left = (node*)malloc(sizeof(node));
            sub_root->left->right = NULL;
            sub_root->left->left = NULL;
            sub_root->left->val = val;
        } else {
        	addNode(sub_root->left, val);
        }
    }
}
void preorder(node* root) {
  if(!root) {
      return;
  }
  printf("%d ",root->val);
  if(root->left) {
      preorder(root->left);
  }
  if(root->right) {
      preorder(root->right);
  } 
}

void inorder(node* root) {
  if(!root) {
      return;
  }
  if(root->left) {
      preorder(root->left);
  }
  printf("%d ",root->val);
  if(root->right) {
      preorder(root->right);
  }
}

void postorder(node* root) {
  if(!root) {
      return;
  }
  if(root->left) {
      preorder(root->left);
  }
  if(root->right) {
      preorder(root->right);
  }
    printf("%d ",root->val);
}
void printTree() {
    printf("Inorder: \n");
    inorder(root);
    printf("\n");
    printf("Preorder: \n");
    preorder(root);
    printf("\n");
    printf("Postorder: \n");
    postorder(root);
    printf("\n");
}
void find(node* root, node** find_node, int val) {

    if(root->val > val) {
        if (root->left) {
        	find(root->left, find_node, val);
        }
    } else if (root->val < val) {
        if(root->right) {
    	find(root->right, find_node, val);
        }
    } else {
        printf("Found %d\n", val);
        *find_node= root;
    }
    return;
}
node* find_inorder_successor (node* sub_root) {
	printf("Here with val:%d\n", sub_root->val);
    if(sub_root->left == NULL) {
        return sub_root;
    }
    return find_inorder_successor(sub_root->left);
}

node* del(node* sub_root, int val){
	
  if (sub_root == NULL) {
      return sub_root;
  }
  printf("subroot = %d\n", sub_root->val);
  if (sub_root->val >val) {
      sub_root->left = del(sub_root->left, val);
  } else if(sub_root->val <val) {
      sub_root->right = del(sub_root->right, val);	
  } else {
      if(sub_root->left == NULL) {
        	node* next_level_right = sub_root->right;
        	free(sub_root);
        	return next_level_right;
      } else if (sub_root->right == NULL) {
      	node* next_level_left = sub_root->left;
      	free(sub_root);
            return next_level_left;
      } else {
            printf("Now subroot = %d\n", sub_root->val);
            node* inorder_successor = find_inorder_successor(sub_root->right);
            sub_root->val = inorder_successor->val;
            sub_root->right = del(sub_root->right, inorder_successor->val);
      }
  }
  return sub_root;
}
int main(void) {
    root = (node*)malloc(sizeof(node));
    root->left = NULL;
    root->right = NULL;
    root->val = 7;
    addNode(root, 5);
    addNode(root, 5);
    addNode(root, 8);
    printTree();
    node* find_node = NULL;
    find(root, &find_node, 8);
    if(!find_node) {
        printf("%d not Found\n", 8);	
    }
    find_node = NULL;
    find(root, &find_node, 5);
    if(!find_node) {
        printf("%d not Found\n", 5);	
    }
    root = del(root, 7);
    /*root = del(root, 5);
    root = del(root, 7);
    root = del(root, 8);*/
    printTree();
    return 0;
}
