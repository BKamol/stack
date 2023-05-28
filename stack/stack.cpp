#include <fstream>
#include <iostream>
#include <string>

using namespace std;

struct elem
{
    char data;
    elem* next;
};
typedef elem* stack;

stack create_stack()
{
    stack top = NULL;
    return top;
}

bool isEmpty(stack top)
{
    return top == NULL;
}

void push(stack &top, char el)
{
    stack p = new elem;
    p->data = el;
    p->next = top;
    top = p;
}

int pop(stack &top)
{
    if (isEmpty(top))
    {
        cout << "Empty stack" << endl;
        return -228;
    }
    stack p = top;
    top = top->next;

    int data = p->data;
    delete p;

    return data;
}

int peek(stack top)
{
    if (isEmpty(top))
    {
        cout << "Empty stack" << endl;
        return -228;
    }
    return top->data;
}

int len(stack top)
{
    if (isEmpty(top)) return 0;
    int k = 0;
    while (top != NULL)
    {
        k++;
        top = top->next;
    }
    return k;
}

void print_stack(stack top)
{
    while (top != NULL)
    {
        cout << top->data << ' ';
        top = top->next;
    }
    cout << endl;
}

stack read_formula(string file_name)
{
    ifstream in(file_name);

    stack formula = create_stack();
    char symbol;
    char min;
    char max;
    char func;
    stack q;

    while (in >> symbol)
    {
        push(formula, symbol);
        if (symbol == ')')
        {
            for (int i = 1; i <= 6; i++)
            {
                q = formula;
                formula = formula->next;
                if (i == 1) min = formula->data;
                if (i == 3) max = formula->data;
                if (i == 5) func = formula->data;
                delete q;
            }

            if (func == 'm' && min <= max) push(formula, min);
            if (func == 'm' && max <= min) push(formula, max);
            if (func == 'M' && max >= min) push(formula, max);
            if (func == 'M' && min >= max) push(formula, min);
        }
    }
    

    in.close();

    return formula;
}

int main()
{
    //stack s = create_stack();
    //for (int i = 1; i <= 10; i++) push(s, i);
    //print_stack(s);

    //cout << peek(s) << endl;
    //print_stack(s);

    stack formula = read_formula("formula.txt");
    print_stack(formula);

}
