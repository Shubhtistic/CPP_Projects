#pragma once
#include <vector>
#include <string>
#include <nlohmann/json.hpp>
#include <fstream>

class todo_data_type
{
    std::string title{"No title Given"};
    std::string description{"No description Given"};
    bool completed{false};
    int unique_id;

public:
    void set_title(const std::string &t) { title = t; }
    void set_description(const std::string &d) { description = d; }
    void set_id(int &m_id) { unique_id = m_id; }
    int return_id() const { return unique_id; }

    void set_status(bool status) { completed = status; }

    bool is_completed() const { return completed; }
    void set_completed() { completed = true; }
    void set_pending() { completed = false; }
    std::string show_title() const { return title; }
    std::string show_description() const { return description; }
};
class manager
{

    std::vector<todo_data_type> task_vector;
    int new_id = 1;

public:
    manager();

    void emplace_task(std::string &title, std::string &description);

    void emplace_task(int id, std::string &title, std::string &description, bool status);

    void erase_task(const int &id);
    void mark_complete(const int &id);
    void mark_pending(const int &id);

    std::string return_title(const int &id) const;
    std::string return_description(const int &id) const;
    bool return_status(const int &id) const;

    void set_new_title(const int &id, std::string &new_title);
    void set_new_description(const int &id, std::string &new_desc);
    bool valid_id(const int &id) const;
    bool is_empty() const;
    int id_count() const;

    const std::vector<todo_data_type> &get_all_tasks() const;

    // file i/o
    void save_to_file() const;
    void load_from_file();

    ~manager();
};
