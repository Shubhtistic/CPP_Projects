
#include "console.h"
#include <iostream>
#include <limits>
#include <cstdlib>

    void
    console::add_a_task()
{
    std::string title, description;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    std::cout << "Please enter a title for the task: ";
    std::getline(std::cin, title);
    std::cout << "Now, enter a description: ";
    std::getline(std::cin, description);
    if (title.empty())
    {
        title = "Untitled Task";
    }
    if (description.empty())
    {
        description = "No description provided.";
    }
    todo_list.emplace_task(title, description);
    std::cout << "Success! Your new task has been added with ID: " << todo_list.id_count() - 1 << std::endl;
}

void console::remove_a_task()
{
    if (todo_list.is_empty())
    {
        std::cout << "The to-do list is currently empty. There's nothing to remove.\n";
    }
    else
    {
        while (true)
        {
            int id;
            std::cout << "Please enter the ID of the task you'd like to delete: ";
            std::cin >> id;

            if (std::cin.fail())
            {
                std::cout << "Oops! That wasn't a number.\n";
                std::cout << "Would you like to try again? (y/n): ";

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
                std::cout << "The following task will be permanently deleted:\n"
                          << "Title: '" << todo_list.return_title(id) << "'\n";
                std::cout << "Are you sure you want to delete this task? (y/n): ";
                char choice;
                std::cin >> choice;
                if (choice == 'y' || choice == 'Y')
                {
                    todo_list.erase_task(id);
                    std::cout << "The task has been successfully deleted.\n";
                    break;
                }
                else
                {
                    break;
                }
            }
            else
            {
                std::cout << "Sorry, no task was found with that ID. Would you like to try a different ID? (y/n): ";
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
                    std::cout << "Exiting task removal.\n";
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
        std::cout << "Please enter the ID of the task to mark as complete: ";
        int id;
        std::cin >> id;
        if (std::cin.fail())
        {
            std::cout << "Oops! Please enter a valid number for the ID.\n";
            std::cout << "Would you like to try again? (y/n): ";

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
                std::cout << "The task with ID " << id << " ('" << todo_list.return_title(id) << "') is already marked as complete.\n";
                break;
            }
            else
            {
                std::cout << "You are about to mark the following task as complete:\n"
                          << "Title: " << todo_list.return_title(id) << std::endl;
                std::cout << "Are you sure? (y/n): ";
                char choice;
                std::cin >> choice;
                if (choice == 'y' || choice == 'Y')
                {
                    todo_list.mark_complete(id);
                    std::cout << "Great! The task has been marked as complete.\n";
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
            std::cout << "Sorry, that ID is invalid.\n";
            std::cout << "Would you like to try again? (y/n): ";

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
                std::cout << "Returning to the main menu.\n";
                break;
            }
        }
    }
}

void console::set_as_pending()
{
    while (true)
    {
        std::cout << "Please enter the ID of the task to mark as pending: ";
        int id;
        std::cin >> id;
        if (std::cin.fail())
        {
            std::cout << "Oops! Please enter a valid number for the ID.\n";
            std::cout << "Would you like to try again? (y/n): ";

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
                std::cout << "The task with ID " << id << " ('" << todo_list.return_title(id) << "') is already marked as pending.\n";
                break;
            }
            else
            {
                std::cout << "You are about to mark the following task as pending:\n"
                          << "Title: " << todo_list.return_title(id) << std::endl;
                std::cout << "Are you sure? (y/n): ";
                char choice;
                std::cin >> choice;
                if (choice == 'y' || choice == 'Y')
                {
                    todo_list.mark_pending(id);
                    std::cout << "Okay, the task has been marked as pending.\n";
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
            std::cout << "Sorry, that ID is invalid.\n";
            std::cout << "Would you like to try again? (y/n): ";

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
                std::cout << "Returning to the main menu.\n";
                break;
            }
        }
    }
}

void console::print_pending_tasks() const
{
    if (todo_list.is_empty())
    {
        std::cout << "Your to-do list is empty! ✨\n";
    }
    else
    {
        bool found_pending = false;
        std::cout << "--- Pending Tasks ---\n\n";
        const auto &all_tasks = todo_list.get_all_tasks();
        for (const auto &task : all_tasks)
        {
            if (task.is_completed() == false)
            {
                found_pending = true;
                std::cout << "ID:          " << task.return_id() << "\n";
                std::cout << "Title:       " << task.show_title() << "\n";
                std::cout << "Description: " << task.show_description() << "\n";
                std::cout << "Status:      Pending\n";
                std::cout << "---------------------\n";
            }
        }
        if (!found_pending)
        {
            std::cout << "Great job! You have no pending tasks.\n";
        }
    }
}

void console::print_all_tasks() const
{
    if (todo_list.is_empty())
    {
        std::cout << "Your to-do list is empty! ✨\n";
    }
    else
    {
        std::cout << "--- All Tasks ---\n\n";
        const auto &all_tasks = todo_list.get_all_tasks();
        for (const auto &task : all_tasks)
        {
            std::cout << "ID:          " << task.return_id() << "\n";
            std::cout << "Title:       " << task.show_title() << "\n";
            std::cout << "Description: " << task.show_description() << "\n";
            if (task.is_completed() == false)
            {
                std::cout << "Status:      Pending\n";
            }
            else
            {
                std::cout << "Status:      Completed\n";
            }
            std::cout << "---------------------\n";
        }
    }
}

void console::view_or_edit()
{
    if (todo_list.is_empty())
    {
        std::cout << "Your to-do list is empty, so there's nothing to view or edit.\n";
    }
    else
    {
        while (true)
        {
            std::cout << "Please enter the ID of the task you want to view or edit: ";
            int id;
            std::cin >> id;
            if (std::cin.fail())
            {
                std::cout << "That wasn't a valid number. Would you like to try again? (y/n): ";
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
                std::string new_title, new_desc;
                std::cout << "\n--- Viewing Task " << id << " ---\n";
                std::cout << "Current Title: " << todo_list.return_title(id) << "\n";
                std::cout << "Current Description: " << todo_list.return_description(id) << "\n\n";

                std::cout << "Would you like to edit the title? (y/n): ";
                char choice;
                std::cin >> choice;
                if (choice == 'y' || choice == 'Y')
                {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Please enter the new title: ";
                    std::getline(std::cin, new_title);

                    if (!new_title.empty())
                    {
                        todo_list.set_new_title(id, new_title);
                    }
                    else
                    {
                        std::cout << "No new title was entered. The original title remains unchanged.\n";
                    }
                }

                std::cout << "Would you like to edit the description? (y/n): ";
                char choice2;
                std::cin >> choice2;

                if (choice2 == 'y' || choice2 == 'Y')
                {
                    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                    std::cout << "Please enter the new description: ";
                    std::getline(std::cin, new_desc);
                    if (!new_desc.empty())
                    {
                        todo_list.set_new_description(id, new_desc);
                    }
                    else
                    {
                        std::cout << "No new description was entered. The original description remains unchanged.\n";
                    }
                }
                std::cout << "Returning to the main menu.\n";
                break;
            }
            else
            {
                std::cout << "Sorry, that's not a valid ID.\n";
                std::cout << "Would you like to try again? (y/n): ";
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
        std::cout << "\n--- Main Menu ---\n";
        std::cout << "1. Add a new task\n";
        std::cout << "2. Remove a task\n";
        std::cout << "3. View or edit a task\n";
        std::cout << "4. Mark a task as complete\n";
        std::cout << "5. Mark a task as pending\n";
        std::cout << "6. List pending tasks\n";
        std::cout << "7. List all tasks\n";
        std::cout << "8. Exit the program\n";
        std::cout << "Please enter your choice: ";

        int choice;
        std::cin >> choice;

        if (std::cin.fail())
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter a number between 1 and 8.\n";
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
