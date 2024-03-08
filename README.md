# Red-Black-Trees in C++
This is an implementation of Red-Black Trees in C++, designed for use in managing tasks and assignees in a task management system. Red-Black Trees are a type of self-balancing binary search tree, ensuring logarithmic time complexity for insertion, deletion, and search operations.
Note:
This implementation may contain some errors that need to be addressed. Please review the code and make necessary corrections before use.
Features
Task Management: Add, delete, and update tasks with priorities and assignees.
Assignee Management: Add, delete, and update assignees with their personal information.
Task Assignment: Assign tasks to assignees and track task completion status.
Priority Queue: Retrieve tasks based on priority levels.
Tree Visualization: Display the Red-Black Tree for tasks in sorted order.
Usage
Adding Assignees: Use the addAssignee method to add new assignees with their personal information.
taskManagementSystem tms;
tms.addAssignee("John", "Doe", "123 Street, City", "01/01/2000");
Adding Tasks: Use the addTask method to add new tasks with a description, priority level, and assignee ID.
tms.addTask(1, "Implement feature XYZ", 2, "A001");
Deleting Assignees: Use the DeleteAssignee method to remove an assignee and their associated tasks from the system.
tms.DeleteAssignee("A001");
Updating Task Priority: Use the updateTaskPriority method to change the priority of a task.
tms.updateTaskPriority(1, 3);
Displaying Assignees: Use the DisplayAssignee method to print a list of all assignees in the system.
stringstream result;
tms.DisplayAssignee(result);
cout << result.str();
Finding Tasks by Priority Range: Use the searchTasksByPriorityRange method to find tasks within a specified priority range.
stringstream result;
tms.searchTasksByPriorityRange(1, 3, result);
cout << result.str();
Completing Tasks: Use the completeTask method to mark a task as completed.
tms.completeTask(1);
Displaying Completed Tasks: Use the displayCompletedTasks method to print a list of completed tasks.
stringstream result;
tms.displayCompletedTasks(result);
cout << result.str();
Note:
This implementation may contain some errors that need to be addressed. Please review the code and make necessary corrections before use.
