//Name: Huzaifa Nasir
//Roll No: 22I-1053
//Section: A
#pragma once
#include<iostream>
#include<string>
#include<sstream>
#include<iomanip>
using namespace std;


struct AssigneeNode {
    string first;
    string last;
    string address;
    string dob;
    string assigneeID;
    int color;  //red =1 and black=0
    AssigneeNode* parent;
    AssigneeNode* left;
    AssigneeNode* right;
};

struct TaskNode {
    int taskid;
    string description;
    int priority;
    string assigneeid;
    int color;  
    TaskNode* parent;
    TaskNode* left;
    TaskNode* right;
    bool completed;
};

class taskManagementSystem {
public:
    TaskNode* RootTask;
    AssigneeNode* RootAssignee;
     int counter = 1;
     bool templl; 
     bool temprr; 
     bool templr; 
     bool temprl; 

 taskManagementSystem(){
     RootTask = NULL;
     RootAssignee = NULL;
 }
 

 void displaybyID(stringstream& result, const string& id) {
     AssigneeNode* temp = NULL;
     temp = RootAssignee;

     for (; temp != NULL;) 
     {
         if (temp->assigneeID == id) 
         {
             result << "Name: " <<
                 temp->first <<
                 " " << temp->last <<
                 ", Address: " <<
                 temp->address <<
                 ", DOB: " << 
                 temp->dob <<
                 ", Assignee ID: " <<
                 temp->assigneeID <<endl;
             return;
         }
         else if (id < temp->assigneeID)
         {
             temp = temp->left;
         }
         else 
         {
             temp = temp->right;
         }
     }

 }

 void addAssignee(string fname, string lname, string addr, string DOB) {
     AssigneeNode* temp = NULL;
     temp= creation(fname, lname, addr, DOB);
     insertion(temp);
 }
 AssigneeNode* creation(string fname,string lname, string ADDress,string DOB) {
     AssigneeNode* temp = NULL;
     temp= new AssigneeNode;
     temp->first = fname;
     temp->last = lname;
     temp->address = ADDress;
     temp->dob = DOB;
     temp->assigneeID = generation();
     temp->color = 1; 
     temp->parent = NULL;
     temp->left = NULL;
     temp->right = NULL;

     return temp;
 }
 string generation() {
     stringstream temp;
     if (counter <= 9) 
     {
         temp << "A" << setw(3) << setfill('0') << counter;
     }
     else 
     {
         temp << "A" << setw(3) << setfill('0') << counter;
     }
     counter++;
     return temp.str();
 }

 void insertion(AssigneeNode* node) {
     if (RootAssignee ==  NULL) 
     {
         RootAssignee = new AssigneeNode();
         RootAssignee = node;

         RootAssignee->color = 0; 
     }
     else 
     {
         RootAssignee = helperInsert(RootAssignee, node);
         RootAssignee->color = 0; 
     }
     //deletion(node);
 }

 AssigneeNode* helperInsert(AssigneeNode* root, AssigneeNode* node) {
     bool flag;
     flag= false;

     if (root == NULL) 
     {
         return node;
     }

     if (node->assigneeID < root->assigneeID) 
     {
         root->left = helperInsert(root->left, node);
         if (root->left != NULL)
         {
             root->left->parent = RootAssignee;
         }
         if (root != this->RootAssignee) 
         {
             if (root->color == 1 
                 && (root->left != NULL  && root->left->color == 1))
             {
                 flag = true;
             }
         }
     }
     else 
     {
         root->right = helperInsert(root->right, node);
         if (root->right != NULL){
             root->right->parent = RootAssignee;
         }
         if (root != this->RootAssignee) 
         {
             if (root->color == 1 &&
                 (root->right != NULL && root->right->color == 1))
             {
                 flag = true;
             }
         }
     }

     if (templl==true) 
     {
         root = LeftRotate(root);
         if (root != NULL) 
         {
             root->color = 0;
             if (root->left != NULL) {
                 root->left->color = 1;
             }
         }
         templl = false;
     }
     else if (temprr == true)
     {
         root = RightRotate(root);
         if (root != NULL) 
         {
             root->color = 0;
             if (root->right != NULL)
             {
                 root->right->color = 1;
             }
         }
         temprr = false;
     }
     else if (temprl == true)
     {
         if (root != NULL &&
             root->right != NULL)
         {
             root->right = RightRotate(root->right);
             if (root->right != NULL) 
             {
                 root->right->parent = root;
                 root = LeftRotate(root);
                 if (root != NULL) 
                 {
                     root->color = 0;
                     if (root->left != NULL)
                     {
                         root->left->color = 1;
                     }
                 }
             }
         }
         temprl = false;
     }
     else if (templr == true)
     {
         if (root != NULL && root->left != NULL) 
         {
             root->left = LeftRotate(root->left);
             if (root->left != NULL) 
             {
                 root->left->parent = root;
                 root = RightRotate(root);
                 if (root != NULL) 
                 {
                     root->color = 0;
                     if (root->right != NULL)
                     {
                         root->right->color = 1;
                     }
                 }
             }
         }
         templr = false;
     }

     
     if (flag==true) 
     {
         if (root != NULL &&
             root->parent != NULL) 
         {
             if (root->parent->right == root) 
             {
                 if (root->parent->left == NULL ||
                     (root->parent->left != NULL &&
                         root->parent->left->color == 0)) 
                 {
                     if (root->left != NULL &&
                         root->left->color == 1)
                     {
                         temprl = true;
                     }
                     else if (root->right != NULL &&
                         root->right->color == 1)
                     {
                         templl = true;
                     }
                 }
                 else 
                 {
                     if (root->parent->left != NULL)
                     {
                         root->parent->left->color = 0;
                     }
                     if (root != NULL)
                     {
                         root->color = 0;
                     }
                     if (root->parent != this->RootAssignee)
                     {
                         root->parent->color = 1;
                     }
                 }
             }
             else 
             {
                 if (root->parent->right == NULL ||
                     (root->parent->right != NULL &&
                         root->parent->right->color == 0)) 
                 {
                     if (root->left != NULL &&
                         root->left->color == 1)
                     {
                         temprr = true;
                     }
                     else if (root->right != NULL &&
                         root->right->color == 1)
                     {
                         templr = true;
                     }
                 }
                 else 
                 {
                     if (root->parent->right != NULL)
                     {
                         root->parent->right->color = 0;
                     }
                     if (root != NULL)
                     {
                         root->color = 0;
                     }
                     if (root->parent != this->RootAssignee)
                     {
                         root->parent->color = 1;
                     }
                 }
             }
         }
         flag = false;
     }

     return root;
     //deletion(root);

 }
 AssigneeNode* LeftRotate(AssigneeNode* node) {
     if (node == NULL)
     {
         return NULL;
     } 

     AssigneeNode* temp = NULL;
     temp= node->right;
     if (temp == NULL)
     {
         return node;
     }
     AssigneeNode* temp2 = NULL;
     temp2= temp->left;
     temp->left = node;
     node->right = temp2;
     node->parent = temp;
     if (temp2 != NULL)
     {
         temp2->parent = node;
     }
     return temp;
 }

 AssigneeNode* RightRotate(AssigneeNode* node) {
     AssigneeNode* temp = NULL;
     temp= node->left;
     if (temp == NULL)
     {
         return node;
     }
     AssigneeNode* temp2 = NULL;
     temp2= temp->right;
     temp->right = node;
     node->left = temp2;
     node->parent = temp;
     if (temp2 != NULL)
     {
         temp2->parent = node;
     }
     return temp;
 }


 void inOrderTraversalDisplayByName(AssigneeNode* node,stringstream& result, const string& fname, const string& lname) {
     if (node != NULL) 
     {
         inOrderTraversalDisplayByName(node->left, result, fname, lname);

         if (node->first == fname &&
             node->last == lname) 
         {
             result << "Name: "
                 << node->first <<
                 " " << node->last <<
                 ", Address: " <<
                 node->address <<
                 ", DOB: " <<
                 node->dob <<
                 ", Assignee ID: " <<
                 node->assigneeID << endl;
         }

         inOrderTraversalDisplayByName(node->right, result, fname, lname);
     }
 }

 void displaybyname(stringstream& result, const string& fname, const string& lname) {
     inOrderTraversalDisplayByName(RootAssignee, result, fname, lname);
 }


 void addTask(int id, const string& des, int lvl, const string& id2) {
     RootTask = addTaskHelper(RootTask, id, des, lvl, id2);
 }
 TaskNode* addTaskHelper(TaskNode* node, int id, const string& des, int lvl, const string& assigneeid) {
     if (node == NULL) 
     {
         TaskNode* temp = NULL;
         temp= new TaskNode;
         temp->taskid = id;
         temp->description = des;
         temp->priority = lvl;  
         temp->assigneeid = assigneeid;
         temp->left = NULL;
         temp->completed = false;
         temp->parent = NULL;
         temp->right = NULL;
         temp->color = 1; 
         return temp;
     }

     if (id < node->taskid) 
     {
         node->left = addTaskHelper(node->left, id, des, lvl, assigneeid);
     }
     else if (id > node->taskid)
     {
         node->right = addTaskHelper(node->right, id, des, lvl, assigneeid);
     }

     return node;
 }


 void AssigneeWithNoTask(stringstream& temp) {
     HelperAssigneeWithNoTask(RootAssignee, RootTask, temp);
 }

 void HelperAssigneeWithNoTask(AssigneeNode* assignee, TaskNode* task, stringstream& temp) {
     if (assignee != NULL) 
     {
         HelperAssigneeWithNoTask(assignee->left, task, temp);

         if (!isAssigneeWithTasks(task, assignee->assigneeID)) 
         {
             temp << "Name: " <<
                 assignee->first <<
                 " " << assignee->last << 
                 ", Address: " << 
                 assignee->address <<
                 ", DOB: "<<
                 assignee->dob<<
                 ", Assignee ID: "<<
                 assignee->assigneeID<<endl;
         }

         HelperAssigneeWithNoTask(assignee->right, task, temp);
     }
 }

 bool isAssigneeWithTasks(TaskNode* node, const string& id) {
     if (node == NULL) 
     {
         return false;
     }

     if (id < node->assigneeid) 
     {
         return isAssigneeWithTasks(node->left, id);
     }
     else if (id > node->assigneeid)
     {
         return isAssigneeWithTasks(node->right, id);
     }
     else 
     {
         return true;
     }
 }

 void ShiftTask(const string& source, const string& destination) {
     RootTask = shiftTaskHelper(RootTask, source, destination);
 }

 TaskNode* shiftTaskHelper(TaskNode* node, const string& source, const string& destination) {
     if (node == NULL)
     {
         return NULL;
     }

     if (node->assigneeid == source) 
     {
         node->assigneeid = destination;
     }

     node->left = shiftTaskHelper(node->left, source, destination);
     node->right = shiftTaskHelper(node->right, source, destination);

     return node;
 }
 void printTaskQueue(stringstream& result) {
     HelperPrintTaskQueue(RootTask, result);
 }

 void HelperPrintTaskQueue(TaskNode* node, stringstream& result) {
     if (node != NULL) 
     {
         HelperPrintTaskQueue(node->right, result);
         if (!node->completed) 
         {
             string temp="";
             temp= getbyID(node->assigneeid);
             result << "Task ID: " <<
                 node->taskid << 
                 ", Description: " <<
                 node->description
                 << ", Priority: " <<
                 node->priority <<
                 ", Assignee: " <<
                 temp << " (" <<
                 node->assigneeid << ")"<<endl;
         }
         HelperPrintTaskQueue(node->left, result);
     }
 }
 string getbyID(const string& id) {
     AssigneeNode* temp = NULL;
     temp= findByID(RootAssignee, id);

     if (temp != NULL) 
     {
         return temp->first ;
     }
     
 }

 AssigneeNode* findByID(AssigneeNode* node, const string& id) {
     for (; node != NULL && 
         node->assigneeID != id;) 
     {
         if (id < node->assigneeID)
         {
             node = node->left;
         }
         else 
         {
             node = node->right;
         }
     }

     return node;
 }


 void DeleteAssignee(const string& id) {
     RootAssignee = deleteAssigneeHelper(RootAssignee, id);
     RootTask = deleteTasksForAssignee(RootTask, id);
     if (RootAssignee != NULL)
     {
         RootAssignee->color = 0; 
     }
     deletion(RootAssignee);
     
 }

void deletion(AssigneeNode*& val) {
    AssigneeNode* temp = NULL;
    for (; val != NULL &&
        val != RootAssignee &&
        val->color == 0;) 
    {
        if (val == val->parent->left) 
        {
            temp = val->parent->right;
            if (temp != NULL &&
                temp->color == 1)
            {
                temp->color = 0;
                val->parent->color = 1;
                LeftRotate(val->parent);
                temp = val->parent->right;
            }

            if (temp != NULL && 
                temp->left != NULL &&
                temp->right != NULL &&
                temp->left->color == 0 &&
                temp->right->color == 0)
            {
                temp->color = 1;
                val = val->parent;
            } else 
            {
                if (temp != NULL && 
                    temp->right != NULL &&
                    temp->right->color == 0) 
                {
                    if (temp->left != NULL) 
                    {
                        temp->left->color = 0;
                    }
                    temp->color = 1;
                    RightRotate(temp);
                    temp = val->parent->right;
                }

                if (temp != NULL)
                {
                    temp->color = val->parent->color;
                }
                if (val->parent != NULL)
                {
                    val->parent->color = 0;
                }
                if (temp != NULL && 
                    temp->right != NULL) 
                {
                    temp->right->color = 0;
                }
                if (val->parent != NULL)
                {
                    LeftRotate(val->parent);
                }
                val = RootAssignee;
            }
        } 
        else 
        {
            temp = val->parent->left;
            if (temp != NULL && 
                temp->color == 1) 
            {
                temp->color = 0;
                val->parent->color = 1;
                RightRotate(val->parent);
                temp = val->parent->left;
            }

            if (temp != NULL && 
                temp->right != NULL && 
                temp->left != NULL &&
                temp->right->color == 0 &&
                temp->left->color == 0)
            {
                temp->color = 1;
                val = val->parent;
            } 
            else
            {
                if (temp != NULL && 
                    temp->left != NULL && 
                    temp->left->color == 0) 
                {
                    if (temp->right != NULL) 
                    {
                        temp->right->color = 0;
                    }
                    temp->color = 1;
                    LeftRotate(temp);
                    temp = val->parent->left;
                }

                if (temp != NULL)
                {
                    temp->color = val->parent->color;
                }
                if (val->parent != NULL) 
                {
                    val->parent->color = 0;
                }
                if (temp != NULL && temp->left != NULL) 
                {
                    temp->left->color = 0;
                }
                if (val->parent != NULL) 
                {
                    RightRotate(val->parent);
                }
                val = RootAssignee;
            }
        }
    }
    if (val != NULL) 
    {
        val->color = 0;
    }
}




 AssigneeNode* deleteAssigneeHelper(AssigneeNode* node, const string& id) {
     if (node == NULL)
     {
         return NULL;
     }

     if (id < node->assigneeID) 
     {
         node->left = deleteAssigneeHelper(node->left, id);
     }
     else if (id > node->assigneeID) 
     {
         node->right = deleteAssigneeHelper(node->right, id);
     }
     else 
     {
         if (hasTasksAssignedHelper(id, RootTask)==true)
         {
             return node;
         }

         AssigneeNode* temp;
         temp= NULL;
         if (node->left == NULL)
         {
             temp = node->right;
             delete node;
             return temp;
         }
         else if (node->right == NULL)
         {
             temp = node->left;
             delete node;
             return temp;
         }

         temp = findMinAssignee(node->right);

         node->first = temp->first;
         node->last = temp->last;
         node->address = temp->address;
         node->dob = temp->dob;

         node->right = deleteAssigneeHelper(node->right, temp->assigneeID);
     }
     deletion(RootAssignee);
     return node;
 }


 AssigneeNode* findMinAssignee(AssigneeNode* node) {
     AssigneeNode* temp = NULL;
     temp = node;

     for (; temp->left != NULL;) 
     {
         temp = temp->left;
     }

     return temp;
 }

 TaskNode* deleteTasksForAssignee(TaskNode* node, const string& id) {
     if (node == NULL) 
     {
         return NULL;
     }

     node->left = deleteTasksForAssignee(node->left, id);
     node->right = deleteTasksForAssignee(node->right, id);

     if (node->assigneeid == id)
     {
         delete node;
         return NULL;
     }

     return node;
 }
 bool hasTasksAssignedHelper(const string& id, TaskNode* node) {
     if (node == NULL) 
     {
         return false;
     }

     if (node->assigneeid == id) 
     {
         return true;
     }

     return hasTasksAssignedHelper(id, node->left) || hasTasksAssignedHelper(id, node->right);
 }

 bool hasTasksAssigned(const string& id) {
     return hasTasksAssignedHelper(id, RootTask);
 }
 void inOrderTraversalDisplayAssignee(AssigneeNode* node,stringstream& result) {
     if (node != NULL) 
     {
         inOrderTraversalDisplayAssignee(node->left, result);

         result << "Name: " << 
             node->first <<
             " " << node->last <<
             ", Address: " << 
             node->address << 
             ", DOB: " << 
             node->dob << 
             ", Assignee ID: "
             << node->assigneeID << endl;

         inOrderTraversalDisplayAssignee(node->right, result);
     }
 }

 void DisplayAssignee(stringstream& result) {
     inOrderTraversalDisplayAssignee(RootAssignee, result);
 }


 void AssigneeInOrder(stringstream& result) {
     inOrderTraversalDisplay(RootAssignee, result);
 }

 void inOrderTraversalDisplay(AssigneeNode* node, stringstream& result) {
     if (node != NULL) 
     {
         inOrderTraversalDisplay(node->left, result);

         result << node->assigneeID 
             << " (" <<
             (node->color == 0 ? "black" : "red") 
             << ")"<<endl;

         inOrderTraversalDisplay(node->right, result);
     }
 }


 TaskNode* searchByID(int id, TaskNode* node) {
     if (node == NULL ||
         node->taskid == id) 
     {
         return node;
     }

     if (id < node->taskid) 
     {
         return searchByID(id, node->left);
     }
     else 
     {
         return searchByID(id, node->right);
     }
 }

 void updateTaskPriority(int id, int res) {
     TaskNode* temp = NULL;
         temp= searchByID(id, RootTask);

     if (temp != NULL) 
     {
         temp->priority = res;
     }
 }
 void findHighestPriorityTask(stringstream& result) const {
     if (RootTask != NULL) {
         TaskNode* highestPriorityTask = findHighestPriorityTaskHelper(RootTask);

         findAssigneesWithSamePriority(RootTask, highestPriorityTask->priority, result);
     }
 }

 void findAssigneesWithSamePriority(TaskNode* node, int priority, stringstream& result) const {
     if (node != NULL) {
         findAssigneesWithSamePriority(node->left, priority, result);

         if (node->priority == priority) {
             result << "Highest Priority Task: Task ID: " <<
                 node->taskid << ", Description: " <<
                 node->description << ", Priority: " <<
                 node->priority << ", Assignee: " <<
                 getAssigneeName(node->assigneeid) << " (" <<
                 node->assigneeid << ")"<<endl;
         }

         findAssigneesWithSamePriority(node->right, priority, result);
     }
 }

 string getAssigneeName(const string& assigneeid) const {
     AssigneeNode* temp = findByID(RootAssignee, assigneeid);
     if (temp != NULL) {
         return temp->first ;
     }
     return "";
 }

 AssigneeNode* findByID(AssigneeNode* node, const string& id) const {
     for (; node != NULL && node->assigneeID != id;) {
         if (id < node->assigneeID) {
             node = node->left;
         }
         else {
             node = node->right;
         }
     }
     return node;
 }

 TaskNode* findHighestPriorityTaskHelper(TaskNode* node) const {
     for (; node->left != NULL;) 
     {
         node = node->left;
     }
     return node;
 }

 void findTasksByAssigneeHelper(TaskNode* node, const string& id, stringstream& result) {
     if (node != NULL) 
     {
         findTasksByAssigneeHelper(node->left, id, result);
         findTasksByAssigneeHelper(node->right, id, result);
         if (node->assigneeid == id) 
         {
             result << "Task ID: " 
                 << node->taskid <<
                 ", Description: " <<
                 node->description
                 << ", Priority: " <<
                 node->priority <<
                 ", Assignee: " <<
                 getbyID(node->assigneeid) << 
                 " (" << node->assigneeid << ")"<<endl;
         }
         
     }
 }

 void findTasksByAssignee(const string& id, stringstream& result) {
     result << "Tasks Assigned to \"" <<
         getbyID(id) <<
         " (" << id << ")\":"<<endl;
     findTasksByAssigneeHelper(RootTask, id, result);
 }



 int countTotalTasksHelper(TaskNode* root)  {
     if (root == NULL) 
     {
         return 0;
     }

     return 1 + countTotalTasksHelper(root->left) + countTotalTasksHelper(root->right);
 }

 void countTotalTasks(stringstream &result) {
     result << "Total Tasks in the System: "<< countTotalTasksHelper(RootTask)<<endl;
     
 }
 void PrintTreeInOrder(TaskNode* node,stringstream& result) {
     if (node != NULL) 
     {
         PrintTreeInOrder(node->left, result);

         result << "" << 
             node->taskid << " (" <<
             (node->color == 0 ? "black" : "red") 
             << ")"<<endl;

         PrintTreeInOrder(node->right, result);
     }
 }

 void PrintTreeInorder(stringstream& result) {
     PrintTreeInOrder(RootTask, result);
 }
 void deleteTask(int id) {
     RootTask = deleteTaskHelper(RootTask, id);
 }

 TaskNode* deleteTaskHelper(TaskNode* node, int id) {
     if (node == NULL) 
     {
         return node;
     }

     if (id > node->taskid) 
     {
         node->right = deleteTaskHelper(node->right, id);

     }
     else if (id < node->taskid) 
     {
         node->left = deleteTaskHelper(node->left, id);
     }
     else 
     {
         if (node->left == NULL)
         {
             TaskNode* temp = NULL;
             temp= node->right;
             delete node;
             return temp;
         }
         else if (node->right == NULL)
         {
             TaskNode* temp2 = NULL;
                 temp2= node->left;
             delete node;
             return temp2;
         }

         TaskNode* temp3 = NULL;
         temp3= MinVal(node->right);
         node->taskid = temp3->taskid;
         node->priority = temp3->priority;
         node->assigneeid = temp3->assigneeid;
         node->description = temp3->description;
         node->right = deleteTaskHelper(node->right, temp3->taskid);
     }

     return node;
 }

 TaskNode* MinVal(TaskNode* node) {
     TaskNode* temp = NULL;
     temp= node;
     for (; temp && temp->left != NULL;) {
         temp = temp->left;
     }
     return temp;
 }

 void searchTasksByPriorityRange(int minimum, int maximum,stringstream& result) {
     result << "Tasks within Priority Range (" << minimum << " to " << maximum << "):"<<endl;
     searchTasksByPriorityRangeHelper(RootTask, minimum, maximum, result);
 }

 void searchTasksByPriorityRangeHelper(TaskNode* node, int minimum, int maximum, stringstream& res) {
     
     if (node != NULL) 
     {
         searchTasksByPriorityRangeHelper(node->left, minimum, maximum, res);
         searchTasksByPriorityRangeHelper(node->right, minimum, maximum, res);
         if (node->priority >= minimum &&
             node->priority <= maximum) {
             res << "Task ID: " <<
                 node->taskid << 
                 ", Description: " 
                 << node->description
                 << ", Priority: " <<
                 node->priority <<
                 ", Assignee: " << 
                 getbyID(node->assigneeid) <<
                 " (" << node->assigneeid << ")"<<endl;
         }
            
     }
 }
 void completeTask(int temp) {
     RootTask = completeTaskHelper(RootTask, temp);
 }

 TaskNode* completeTaskHelper(TaskNode* node, int id) {
     if (node == NULL) 
     {
         return node;
     }

     if (id > node->taskid) 
     {
         node->right = completeTaskHelper(node->right, id);
     }
     else if (id < node->taskid) 
     {
         node->left = completeTaskHelper(node->left, id);
     }
     else
     {
         node->completed = true;
        
     }

     return node;
 }
 void displayCompletedTasks(stringstream& temp) {
     temp << "Completed Tasks:"<<endl;
     displayCompletedTasksHelper(RootTask, temp);
 }

 void displayCompletedTasksHelper(TaskNode* node, stringstream& temp) {
     if (node != NULL) 
     {
         displayCompletedTasksHelper(node->left, temp);
         displayCompletedTasksHelper(node->right, temp);
         if (node->completed) 
         {
             temp << "Task ID: " <<
                 node->taskid << 
                 ", Description: " <<
                 node->description
                 << ", Priority: " <<
                 node->priority <<
                 ", Assignee: " <<
                 getbyID(node->assigneeid) <<
                 " (" << node->assigneeid << ")"<<endl;
         }
     }
 }
};