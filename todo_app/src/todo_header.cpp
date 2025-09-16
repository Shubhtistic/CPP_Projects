
#include <iostream>
#include "todo_header.h"
#include <stdexcept>
#include <fstream>

using json = nlohmann::json;

void manager::save_to_file() const
{
    json json_array;

    for (const auto &task : task_vector)
    {
        json j_task;
        j_task["ID"] = task.return_id();
        j_task["Title"] = task.show_title();
        j_task["Description"] = task.show_description();
        j_task["Completion Status"] = task.is_completed();
        json_array.push_back(j_task);
    }
    std::ofstream my_file("my_tasks.json");

    if (!my_file)
    {
        std::cerr << "Coudn't save the file,Unknown Error Occured!!!\n";
        return;
    }
    my_file << json_array.dump(4);
}

void manager::load_from_file()
{
    int id_count = 0;
    std::ifstream my_file("my_tasks.json");
    if (!my_file)
    {
        return;
    }
    try
    {
        json json_array = json::parse(my_file);
        for (const auto j_task : json_array)
        {
            int id = j_task.at("ID");
            std::string title = j_task.at("Title");
            std::string description = j_task.at("Description");
            bool status = j_task.at("Completion Status");
            emplace_task(id, title, description, status);
            id_count = std::max(id_count, id);
        }
        new_id = id_count + 1;
    }

    catch (const std::exception &e)
    { // the json will throw an std::exception object
        std::cerr << e.what() << "\n";
    }
}

manager::manager()
{
    load_from_file();
}
manager::~manager()
{
    save_to_file();
}

void manager::emplace_task(std::string &title, std::string &description)
{
    todo_data_type new_task;
    int new_temp_id = new_id;

    new_task.set_title(title);
    new_task.set_description(description);
    new_task.set_id(new_temp_id);
    task_vector.push_back(new_task);
    new_id = new_temp_id + 1;
}

void manager::emplace_task(int id, std::string &title, std::string &description, bool status)
// overloaded function to load from file
{
    todo_data_type new_task;
    new_task.set_title(title);
    new_task.set_description(description);
    new_task.set_status(status);
    new_task.set_id(id);
    task_vector.push_back(new_task);
}

void manager::erase_task(const int &id)
{

    for (int i = 0; i < task_vector.size(); ++i)
    {
        if (id == task_vector[i].return_id())
        {
            task_vector.erase(task_vector.begin() + i);
            break;
        }
    }
}

void manager::mark_complete(const int &id)
{
    for (int i = 0; i < task_vector.size(); ++i)
    {
        if (task_vector[i].return_id() == id)
        {
            task_vector[i].set_completed();
            break;
        }
    }
}

void manager::mark_pending(const int &id)
{
    for (int i = 0; i < task_vector.size(); ++i)
    {
        if (task_vector[i].return_id() == id)
        {
            task_vector[i].set_pending();
            break;
        }
    }
}

std::string manager::return_title(const int &id) const
{
    std::string temp;

    for (int i = 0; i < task_vector.size(); ++i)
    {
        std::string temp;
        if (task_vector[i].return_id() == id)
        {
            temp = task_vector[i].show_title();
            break;
        }
    }
    return temp;
}

std::string manager::return_description(const int &id) const
{
    std::string temp;
    for (int i = 0; i < task_vector.size(); ++i)
    {
        if (task_vector[i].return_id() == id)
        {
            temp = task_vector[i].show_description();
            break;
        }
    }
    return temp;
}

bool manager::return_status(const int &id) const
{
    for (int i = 0; i < task_vector.size(); ++i)
    {
        if (task_vector[i].return_id() == id)
        {
            return task_vector[i].is_completed();
            break;
        }
    }
    return false;
}

void manager::set_new_title(const int &id, std::string &new_title)
{
    for (int i = 0; i < task_vector.size(); ++i)
    {
        if (task_vector[i].return_id() == id)
        {
            task_vector[i].set_title(new_title);
            break;
        }
    }
}

void manager::set_new_description(const int &id, std::string &new_desc)
{
    for (int i = 0; i < task_vector.size(); ++i)
    {
        if (task_vector[i].return_id() == id)
        {
            task_vector[i].set_description(new_desc);
        }
    }
}

bool manager::valid_id(const int &id) const
{
    for (int i = 0; i < task_vector.size(); ++i)
    {
        if (task_vector[i].return_id() == id)
        {
            return true;
        }
    }
    return false;
}

bool manager::is_empty() const
{
    bool temp = false;
    if (task_vector.empty())
        temp = true;
    return temp;
}

const std::vector<todo_data_type> &manager::get_all_tasks() const
{
    return task_vector;
}

int manager::id_count() const
{
    return new_id;
}
