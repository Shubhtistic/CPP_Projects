#include "console.h"
#include <iostream>
#include <limits>
#include <cstdlib>

void console::add_a_task()
{
    std::string title, description;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Enter the title of the task: ";
    std::getline(std::cin, title);
    std::cout << "Enter the description of the task: ";
    std::getline(std::cin, description);
    if (title.empty())
    {
        title = "No Title given For this Task";
    }
    if (description.empty())
    {
        description = "No Description Given";
    }
    todo_list.emplace_task(title, description);
    std::cout << "Added New Task Successfuly With Task ID: " << todo_list.id_count() - 1 << std::endl;
}

void console::remove_a_task()
{
    if (todo_list.is_empty())
    {
        std::cout << "Currently there are no Tasks\nExited";
    }
    else
    {
        while (true)
        {
            int id;
            std::cout << "Enter the ID number of the Task you want to delete\n";
            std::cin >> id;

            if (std::cin.fail())
            {
                std::cout << "You have Not Entered an Number!!\n";
                std::cout << "You want to try again? Enter y for 'Yes', Any other key means 'No'\n";

                char choice;
                std::cin >> choice;
                if (choice == 'y' || choice == 'Y')
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    continue;
                }
                else
                {
                    break;
                }
            }

            else if (todo_list.valid_id(id))
            {
                std::cout << "The Task With Ttite: '";
                std::cout << todo_list.return_title(id);
                std::cout << "' will be deleted\n";
                std::cout << "Enter y for 'Yes' & Any other key for 'No'\n";
                char choice;
                std::cin >> choice;
                if (choice == 'y' || choice == 'Y')
                {
                    todo_list.erase_task(id);
                    std::cout << "The Task Has Been Deleted!!\n";
                    break;
                }
                else
                {
                    break;
                }
            }
            else
            {
                std::cout << "Any Task With this ID does Not exist You want to Enter ID again\nEnter y for 'Yes' &  Press any other key for 'No'\n";
                char choice;
                std::cin >> choice;
                if (choice == 'y' || choice == 'Y')
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    continue;
                }
                else
                {
                    std::cout << "Goodbye!!\n";
                    break;
                }
            }
        }
    }
}

void console::set_as_complete()
{
    while (true)
    {
        std::cout << "Enter the Task ID of task to be Completed\n";
        int id;
        std::cin >> id;
        if (std::cin.fail())
        {
            std::cout << "You D-d Not Enter a Numbered ID!!\n";
            std::cout << "You want to try again? Enter y for 'Yes', Any other key means 'No'\n";

            char choice;
            std::cin >> choice;
            if (choice == 'y' || choice == 'Y')
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            else
            {
                break;
            }
        }

        else if (todo_list.valid_id(id))
        {
            if (todo_list.return_status(id) == true)
            {
                std::cout << "The task with ID NO. " << id << " & Title: '" << todo_list.return_title(id) << "'\n";
                std::cout << "Is already Set as Completed\n";
                break;
            }

            else
            {
                std::cout << "The Title of task you want to set as complete\nTitle: " << todo_list.return_title(id) << std::endl;

                std::cout << "\nAre You Sure? Enter y for 'yes' and any other key for 'No'\n";
                char choice;
                std::cin >> choice;
                if (choice == 'y' || choice == 'y')
                {
                    todo_list.mark_complete(id);

                    std::cout << "The Task Now Has Been Set as Completed\n";
                    break;
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
            std::cout << "You Entered a wrong ID!!\n";
            std::cout << "You want to try again? Enter y for 'Yes', Any other key means 'No'\n";

            char choice;
            std::cin >> choice;
            if (choice == 'y' || choice == 'Y')
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            else
            {
                std::cout << "Goodbye!!\n";
                break;
            }
        }
    }
}

void console::set_as_pending()
{
    while (true)
    {
        std::cout << "Enter the Task ID of task to be Set as Pending\n";
        int id;
        std::cin >> id;
        if (std::cin.fail())
        {

            std::cout << "You Did Not Enter a Numbered ID!!\n";
            std::cout << "You want to try again? Enter y for 'Yes', Any other key means 'No'\n";

            char choice;
            std::cin >> choice;
            if (choice == 'y' || choice == 'Y')
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }
            else
            {
                break;
            }
        }

        else if (todo_list.valid_id(id))
        {
            if (todo_list.return_status(id) == false)
            {
                std::cout << "The task with ID NO. " << id << " & Title: ";
                std::cout << todo_list.return_title(id);
                std::cout << "\nIs already Set as Pending\n";
                break;
            }

            else if (todo_list.valid_id(id))
            {
                std::cout << "The Title of task you want to set as Pending\nTitle: " << todo_list.return_title(id);

                std::cout << "\nAre You Sure? Enter y for 'yes' and any other key for 'No'\n";
                char choice;
                std::cin >> choice;
                if (choice == 'y' || choice == 'y')
                {
                    todo_list.mark_pending(id);

                    std::cout << "The Task Now Has Been Set as Pending!!\n";
                    break;
                }
                else
                {
                    break;
                }
            }
        }
        else
        {
            std::cout << "You Entered a wrong ID!!\n";
            std::cout << "You want to try again? Enter y for 'Yes', Any other key means 'No'\n";

            char choice;
            std::cin >> choice;
            if (choice == 'y' || choice == 'Y')
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                continue;
            }

            else
            {
                std::cout << "Goodbye!!\n";
                break;
            }
        }
    }
}

void console::print_pending_tasks() const
{
    if (todo_list.is_empty())
    {
        std::cout << "OOPS! it looks there are no Tasks Currently -_-\n";
    }
    else
    {
        bool found_pending = false;
        std::cout << "=====================================================\n";
        const auto &all_tasks = todo_list.get_all_tasks();
        for (const auto &task : all_tasks)
        {
            if (task.is_completed() == false)
            {

                found_pending = true;
                std::cout << "ID: " << task.return_id() << "\n";
                std::cout << "Title: " << task.show_title() << "\n";
                std::cout << "Description: " << task.show_description() << "\n";
                std::cout << "Task: Pending(Not Completed)\n";
                std::cout << "\n";
                std::cout << "===============================================\n";
            }
        }
        if (!found_pending)
        {
            std::cout << "There are no pending tasks.\n";
        }
    }
}

void console::print_all_tasks() const
{
    if (todo_list.is_empty())
    {
        std::cout << "OOPS! it looks there are no Tasks Currently -_-\n";
    }
    else
    {
        std::cout << "=====================================================\n";
        const auto &all_tasks = todo_list.get_all_tasks();
        for (const auto &task : all_tasks)
        {

            std::cout << "ID: " << task.return_id() << "\n";
            std::cout << "Title: " << task.show_title() << "\n";
            std::cout << "Description: " << task.show_description() << "\n";
            if (task.is_completed() == false)
            {

                std::cout << "Task: Pending(Not Completed)\n";
            }
            else
            {
                std::cout << "Task: Completed -_-\n";
            }

            std::cout << "\n";
            std::cout << "===============================================\n";
        }
    }
}

void console::view_or_edit()
{
    if (todo_list.is_empty())
    {
        std::cout << "Oops! Looks Like there is no Task to View Or Edit\n";
        std::cout << "\n=====================================================\n";
    }
    else
    {
        while (true)
        {
            std::cout << "Enter the ID Of the Task To be Edited or Previewed\n";
            std::cout << "==========================================================\n";
            int id;
            std::cin >> id;
            if (std::cin.fail())
            {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                std::cout << "You Did not enter Numbered ID, Do you Want to try Again\nEnter y for 'Yes' & Any other key to to say 'No'\n";
                char choice;
                std::cin >> choice;
                if (choice == 'y' || choice == 'Y')
                {
                    continue;
                }
                else
                {
                    break;
                }
            }
            else if (todo_list.valid_id(id))
            {
                std::string new_title, new_desc;
                std::cout << "The Title of the task is: " << todo_list.return_title(id) << "\n";

                std::cout << "\nThe Description of the task is: " << todo_list.return_description(id) << "\n";

                std::cout << "Do You want to edit the Task Title\n If 'yes' enter y or any other key to decline\n";
                char choice;
                std::cin >> choice;
                if (choice == 'y' || choice == 'Y')
                {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Please Enter new Title Below\n";
                    std::getline(std::cin, new_title);

                    if (new_title.empty() != true)
                    {
                        todo_list.set_new_title(id, new_title);
                    }
                    else
                    {
                        std::cout << "You didnt Enter anything Old Title Remains\n";
                    }
                }

                std::cout << "Do You want to edit the Task Description\n If 'yes' enter y or any other key to decline\n";
                char choice2;
                std::cin >> choice2;

                if (choice2 == 'y' || choice2 == 'Y')
                {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Please Enter new Description Below\n";
                    std::getline(std::cin, new_desc);
                    if (new_desc.empty() != true)
                    {
                        todo_list.set_new_description(id, new_desc);
                        break;
                    }
                    else
                    {
                        std::cout << "You didnt Enter anything Old Description Remains\n";
                        break;
                    }
                }
                else
                {
                    std::cout << "Exited from Editing\n";
                    break;
                }
            }
            else
            {
                std::cout << "Not an valid ID NUMBER -_-\n";

                std::cout << "Do you Want to try Again\nEnter y for 'Yes' & Any other key to to say 'No'\n";
                char choice;
                std::cin >> choice;
                if (choice == 'y' || choice == 'Y')
                {
                    std::cin.clear();
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    continue;
                }
                else
                {
                    break;
                }
            }
        }
    }
}

void console::start_console()
{
    while (true)
    {
        std::cout << "Enter 1 to Add a Task\n";
        std::cout << "Enter 2 to Remove a Task\n";
        std::cout << "Enter 3 to View or Edit to see specific task\n";
        std::cout << "Enter 4 to Mark a Task as Complete\n";
        std::cout << "Enter 5 to Mark a Task as Pending\n";
        std::cout << "Enter 6 to Print Pending Tasks\n";
        std::cout << "Enter 7 to Print all Tasks\n";
        std::cout << "Enter 8 to Exit the Program\n";

        int choice;
        std::cin >> choice;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number between 1 and 7.\n";
            continue;
        }
        else if (choice > 8 || choice < 1)
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number between 1 and 8.\n";
            continue;
        }

        switch (choice)
        {
        case 1:
            add_a_task();
            break;
        case 2:
            remove_a_task();
            break;

        case 3:
            view_or_edit();
            break;
        case 4:
            set_as_complete();
            break;
        case 5:
            set_as_pending();
            break;
        case 6:
            print_pending_tasks();
            break;
        case 7:
            print_all_tasks();
            break;
        case 8:
            std::cout << "Exiting the program. Goodbye!\n";
            return;
        }
    }
}