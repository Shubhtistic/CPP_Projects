#include "todo_header.h"

class console
{
    manager todo_list;

public:
    void start_console();

    void add_a_task();
    void remove_a_task();
    void view_or_edit();

    void set_as_complete();
    void set_as_pending();

    void print_pending_tasks() const;
    void print_all_tasks() const;
};