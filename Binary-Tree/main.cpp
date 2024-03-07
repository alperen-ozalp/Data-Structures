
#include <iostream>
#include <fstream>
#include <sstream>

#include <string>
#include <queue>
#include <stack>
using namespace std;

class Employee {
    private:
 
        int id;
        int salary;
        int department;
        friend class TreeNode;
    public:

        Employee();
        ~Employee(){}
        void set_id(int);
        void set_salary(int);
        void set_department(int);
        int get_id();
        int get_salary();
        int get_department();
};
Employee::Employee(){
    this->id= 0;
    this->salary= 0;
    this->department= 0;
}
void Employee::set_id(int id) {
    this->id = id;
}
void Employee::set_salary(int salary) {
    this->salary = salary;
}
void Employee::set_department(int department) {
    this->department = department;
}
int Employee::get_id() {
    return this->id;
}
int Employee::get_salary() {
    return this->salary;
}
int Employee::get_department() {
    return this->department;
}

class TreeNode{
    private:
        Employee* employee;
        TreeNode* left; //left child
        TreeNode* right;   //right child
    public:
        TreeNode(Employee*);
        ~TreeNode(){}

        void set_employee(Employee*);
        void set_left(TreeNode*);
        void set_right(TreeNode*); 

        TreeNode* get_left();
        TreeNode* get_right();
        Employee* get_employee();

};
TreeNode::TreeNode(Employee* employee){
    this->employee = employee;
    this->left = NULL;
    this->right = NULL;
}
Employee* TreeNode::get_employee(){
    return this->employee;
}
void TreeNode::set_employee(Employee* employee){
    this->employee = employee;
}
void TreeNode::set_left(TreeNode* left){
    this->left = left;
}
void TreeNode::set_right(TreeNode* right){
    this->right = right;
}

TreeNode* TreeNode::get_left(){
    return this->left;
}
TreeNode* TreeNode::get_right(){
    return this->right;;
}



class BinaryTree{
    private:
        TreeNode* root;
        friend class TreeNode;
    public:

        BinaryTree();
        ~BinaryTree();
        void insert(Employee* employee);
        void remove(int id);
        Employee* search(int id);
        int getHeight();
        void printToFile(ofstream &output_file);
        void printToConsole();

        TreeNode* min(TreeNode* node);
        TreeNode* max_id(TreeNode* node);

        Employee* update(int id,int salary,int department);
        
        TreeNode* get_root() ;
        void pre_order(TreeNode*);
        void in_order(TreeNode*);
};              
BinaryTree::~BinaryTree(){
}
BinaryTree::BinaryTree(){
    this->root=NULL;
}

TreeNode* BinaryTree::get_root()  {
    return this->root;
}
void BinaryTree::insert(Employee* employee){

    TreeNode* newemployee = new TreeNode(employee);
    if (root==NULL){
        root=newemployee;
    }
    else{
        TreeNode* temp = root;
        while(true){
            if (employee->get_id() > temp->get_employee()->get_id() ){
                if (temp->get_right()==nullptr){
                    temp->set_right(newemployee);
                    break;
                }
                else{
                    temp = temp->get_right(); 
                }
            }
            else{
                if(temp->get_left()==nullptr) {
                    temp->set_left(newemployee);
                    break;
                }
                else{
                    temp=temp->get_left();
                }
            }
        }
    }
    
}

void BinaryTree::remove(int id){

    TreeNode* temp = root;
    if (search(id)==NULL){
        cout<< "ERROR: An invalid ID to delete\n";
    }
    else { 
        while(true){
        if(temp->get_employee()->get_id()==id){
        
        if(temp->get_left()==NULL && temp->get_right()==NULL){
            root=NULL;
            delete root;
            break;
        }

        else{
            TreeNode* mintemp = min(temp->get_right());
            int minId = mintemp->get_employee()->get_id();
            Employee* tempe = mintemp->get_employee();
            remove(minId);
            temp->set_employee(tempe);
         
            break;
            }
        }

        //right subtree
        else if(temp->get_employee()->get_id()<id){
            if (temp->get_right()->get_employee()->get_id()!=id)
                temp = temp->get_right();

            else if (temp->get_right()->get_employee()->get_id()==id){
                
                if (temp->get_right()->get_right()==NULL && temp->get_right()->get_left() == NULL){
                    //no child delete
                    delete temp->get_right();
                    temp->set_right(NULL);
                    break;
                }
                else if (temp->get_right()->get_left()==NULL){
                    //one child delete
                    TreeNode* temp2 = temp->get_right()->get_right();
                    delete temp->get_right();
                    temp->set_right(temp2);
                    break;
                }
                
                else if (temp->get_right()->get_right()==NULL){
                    //one child delete
                    TreeNode* temp2 = temp->get_right()->get_left();
                    delete temp->get_right();
                    temp->set_right(temp2);
                    break;
                }
                else {
                    //two child delete
                        TreeNode* mintemp = min(temp->get_right()->get_right());
                        int minId = mintemp->get_employee()->get_id();
                        Employee* tempe = mintemp->get_employee();
                        remove(minId);
                        temp->get_right()->set_employee(tempe);
                        break;
                    }
                
            }
        }
        //left subtree
        else if (temp->get_employee()->get_id()>id){

            if (temp->get_left()->get_employee()->get_id()!=id)
                temp = temp->get_left();

            else if (temp->get_left()->get_employee()->get_id()==id){

                if (temp->get_left()->get_left()==NULL && temp->get_left()->get_right() == NULL){
                    delete temp->get_left();
                    temp->set_left(NULL);
                    break;
                }
                else if (temp->get_left()->get_left()==NULL){
                    //one child delete
                    TreeNode* temp2 = temp->get_left()->get_right();
                    delete temp->get_left();
                    temp->set_left(temp2);
                    break;

                }

                else if (temp->get_left()->get_right()==NULL){
                    //one child delete
                    TreeNode* temp2 = temp->get_left()->get_left();
                    delete temp->get_left();
                    temp->set_left(temp2);
                    break;
                }
                else {
                    //two child delete
                        TreeNode* mintemp = min(temp->get_left()->get_right());
                        int minId = mintemp->get_employee()->get_id();
                        Employee* tempe = mintemp->get_employee();
                        remove(minId);
                        temp->get_left()->set_employee(tempe);
                        break;
                    }
                
            } 
        }
        
        
    }


}
}

Employee* BinaryTree::update(int id,int salary,int department){

    if (search(id)==NULL){
        cout<<"ERROR: An invalid ID to update\n";
        return 0;
    }
    Employee* tempe;

    tempe=search(id);
    tempe->set_id(id);
    tempe->set_salary(salary);
    tempe->set_department(department);
    return tempe;

}

TreeNode* BinaryTree::min(TreeNode* node) {
    
    while (node->get_left() != NULL) {
        node = node->get_left();
    }
    return node;
}
TreeNode* BinaryTree::max_id(TreeNode* node) {
    
    while (node->get_right() != NULL) {
        node = node->get_right();
    }
    return node;
}

Employee* BinaryTree::search(int id){

        TreeNode* temp = root;
        while (true){
            
            if (temp==NULL){
                return NULL;
                break;
            }

            else if ( temp->get_employee()->get_id()==id){
            
                return temp->get_employee();
                break;
            }   
            else{
                if (temp->get_employee()->get_id()>id){
                    temp = temp->get_left();
                }
                else {
                    temp = temp->get_right();
                }
            }
        }
}

int BinaryTree::getHeight(){
    int H = 0;  
    if (root==NULL){
        return H;
    }
    else{
    queue<TreeNode*> q;  

    q.push(root);  
    q.push(NULL);  
    while(!q.empty()){  
        TreeNode* temp = q.front();  
        q.pop();  

        if(temp == NULL){  
            H++;  
        }  

        if(temp != NULL){  
            if(temp->get_left()!=NULL){  
                q.push(temp->get_left());  
            }  
            if(temp->get_right()!=NULL){  
                q.push(temp->get_right());  
            }  
        }  

        else if(!q.empty()){  
            q.push(NULL);  
        }  
    }  
    return H;  
    }
}  

void BinaryTree::pre_order(TreeNode* root){
    
    if (root!=NULL){
        cout << root->get_employee()->get_id()<<";";
        cout << root->get_employee()->get_salary()<<";";
        cout << root->get_employee()->get_department()<<"\n";

        pre_order(root->get_left());
        pre_order(root->get_right());
    }
    
}
void BinaryTree::in_order(TreeNode* root){
    
    if (root!=NULL){
        in_order(root->get_left());
        
        root->get_employee()->get_id() ;
        root->get_employee()->get_salary();
        root->get_employee()->get_department() ;

        in_order(root->get_right());
    }
    
}

void BinaryTree::printToFile(ofstream &output_file){

    if (!output_file.is_open()) {
        cout << "Failed to open the output CSV file." << endl;
        return;
    }

    stack<TreeNode*> nodeStack;

    while (root != nullptr || !nodeStack.empty()) {
        while (root != nullptr) {
            nodeStack.push(root);
            root = root->get_left();
        }

        root = nodeStack.top();
        nodeStack.pop();

        output_file << root->get_employee()->get_id() << ";";
        output_file << root->get_employee()->get_salary() << ";";
        output_file << root->get_employee()->get_department() << "\n" ;


        root = root->get_right();
    }
    output_file.close();
    

}
void BinaryTree::printToConsole(){
    
    pre_order(get_root());
}
void deleteTree(TreeNode* root) {
    TreeNode* temp = root;
    if (temp != nullptr) {
        delete root->get_employee(); 
        delete root;  
        deleteTree(root->get_left());
        deleteTree(root->get_right());
    }
}
int main(int argc, char** argv){
    BinaryTree* T = new BinaryTree;
    ifstream inputfile(argv[1]);
    if (!inputfile.is_open()) {
        cerr << "Failed to open the CSV file." << endl;
        return 1;
    }
    int id, salary, department;
    string line;
    getline(inputfile,line);

     while (getline(inputfile, line)) {
        istringstream ss(line);
        string field;
        Employee* e = new Employee;

        if (getline(ss, field, ';'))
            id = stoi(field);
        if (getline(ss, field, ';'))
            salary = stoi(field);
        if (getline(ss, field, ';'))
            department = stoi(field);
            
        e->set_id(id);
        e->set_salary(salary);
        e->set_department(department);

        T->insert(e);
        
    }
    inputfile.close();
    string operation;

    ifstream operationfile(argv[2]);
    if (!operationfile.is_open()) {
        cerr << "Failed to open the CSV file." << endl;
        return 1;
    }
    string line2;
    while (getline(operationfile, line2)) {
        istringstream ss(line2);
        string field2;
        int newsalary, newdepartment, idToUpdate, idToDelete;

        if(getline(ss, field2, ';'))
            operation = field2;
        if (operation == "PRINT" || operation == "PRINT\r") {
            cout << "P\n";
            T->printToConsole();
        }
        else if (operation == "DELETE" || operation == "DELETE\r") {
            getline(ss, field2, ';');
            idToDelete = stoi(field2);
            T->remove(idToDelete);
            
        }
        else if (operation == "UPDATE" || operation == "UPDATE\r") {
            getline(ss, field2, ';');
            idToUpdate = stoi(field2);
            getline(ss, field2, ';');
            newsalary = stoi(field2);
            getline(ss, field2, ';');
            newdepartment = stoi(field2);
            T->update(idToUpdate,newsalary,newdepartment);            
        }
        else if (operation == "HEIGHT" || operation == "HEIGHT\r") {
            int H = T->getHeight();
            cout << "H ";
            cout << H << "\n";
        }
        
        else if (operation == "ADD" || operation == "ADD\r") {
            getline(ss, field2, ';');
            newsalary = stoi(field2);
            getline(ss, field2, ';');
            newdepartment = stoi(field2);
            Employee* newemp = new Employee;
            newemp->set_id(T->max_id(T->get_root())->get_employee()->get_id()+1);
            newemp->set_salary(newsalary);
            newemp->set_department(newdepartment);
            T->insert(newemp);
        }
    }

    operationfile.close();
       
    ofstream output("output.csv");
    output << "Employee_ID;Salary;Department\n";
    T->printToFile(output);

    deleteTree(T->get_root());
    delete T;
    
    return 0;

    
} 