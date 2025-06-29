#include <bits/stdc++.h>
using namespace std;


bool applyOperator(bool a, bool b, char op)
{
    if (op == '&')
        return a & b;
    if (op == '|')
        return a | b;
    if (op == '^')
        return a ^ b;
    return false;
}


int precedence(char op)
{
    if (op == '!')
        return 3;
    if (op == '&')
        return 2;
    if (op == '^')
        return 1;
    if (op == '|')
        return 0;
    return -1;
}


vector<string> tokenize(string expr)
{
    vector<string> tokens;
    for (size_t i = 0; i < expr.size(); i++)
    {
        char c = expr[i];
        if (isalpha(c))
        {
            tokens.push_back(string(1, c));
        }
        else if (c == '!' || c == '&' || c == '|' || c == '^' || c == '(' || c == ')')
        {
            tokens.push_back(string(1, c));
        }
    }
    return tokens;
}


bool evaluateExpression(const vector<string> &tokens, map<char, bool> &values)
{
    stack<bool> operands;
    stack<char> operators;

    for (const string &token : tokens)
    {
        if (token.size() == 1 && isalpha(token[0]))
        {
            operands.push(values[token[0]]);
        }
        else if (token == "!")
        {
            operators.push('!');
        }
        else if (token == "&" || token == "|" || token == "^")
        {
            while (!operators.empty() && precedence(operators.top()) >= precedence(token[0]))
            {
                char op = operators.top();
                operators.pop();
                bool b = operands.top();
                operands.pop();
                if (op == '!')
                {
                    operands.push(!b);
                }
                else
                {
                    bool a = operands.top();
                    operands.pop();
                    operands.push(applyOperator(a, b, op));
                }
            }
            operators.push(token[0]);
        }
        else if (token == "(")
        {
            operators.push('(');
        }
        else if (token == ")")
        {
            while (!operators.empty() && operators.top() != '(')
            {
                char op = operators.top();
                operators.pop();
                bool b = operands.top();
                operands.pop();
                if (op == '!')
                {
                    operands.push(!b);
                }
                else
                {
                    bool a = operands.top();
                    operands.pop();
                    operands.push(applyOperator(a, b, op));
                }
            }
            operators.pop();
        }
    }

    while (!operators.empty())
    {
        char op = operators.top();
        operators.pop();
        bool b = operands.top();
        operands.pop();
        if (op == '!')
        {
            operands.push(!b);
        }
        else
        {
            bool a = operands.top();
            operands.pop();
            operands.push(applyOperator(a, b, op));
        }
    }

    return operands.top();
}


vector<string> generateMinterms(const string &expr)
{
    vector<string> tokens = tokenize(expr);
    vector<char> variables;
    map<char, bool> values;

    for (char c : expr)
    {
        if (isalpha(c) && values.find(c) == values.end())
        {
            variables.push_back(c);
            values[c] = false;
        }
    }

    
    sort(variables.begin(), variables.end());

    int numVars = variables.size();
    vector<string> minTerms;

    for (int i = 0; i < (1 << numVars); i++)
    {
        for (int j = 0; j < numVars; j++)
        {
            values[variables[j]] = (i & (1 << (numVars - j - 1))) != 0;
        }

        if (evaluateExpression(tokens, values))
        {
            string binaryStr;
            for (int j = 0; j < numVars; j++)
            { // Correct order
                binaryStr += values[variables[j]] ? '1' : '0';
            }
            minTerms.push_back(binaryStr);
        }
    }

    return minTerms;
}


vector<string> generateMaxTerms(const string &expr)
{
    vector<string> tokens = tokenize(expr);
    vector<char> variables;
    map<char, bool> values;

    for (char c : expr)
    {
        if (isalpha(c) && values.find(c) == values.end())
        {
            variables.push_back(c);
            values[c] = false;
        }
    }

   
    sort(variables.begin(), variables.end());

    int numVars = variables.size();
    vector<string> allTerms, minTerms, maxTerms;

    for (int i = 0; i < (1 << numVars); i++)
    {
        for (int j = 0; j < numVars; j++)
        {
            values[variables[j]] = (i & (1 << (numVars - j - 1))) != 0;
        }

        string binaryStr;
        for (int j = 0; j < numVars; j++)
        { 
            binaryStr += values[variables[j]] ? '1' : '0';
        }
        allTerms.push_back(binaryStr);

        if (evaluateExpression(tokens, values))
        {
            minTerms.push_back(binaryStr);
        }
    }

    
    set<string> minTermSet(minTerms.begin(), minTerms.end());
    for (const string &term : allTerms)
    {
        if (minTermSet.find(term) == minTermSet.end())
        {
            maxTerms.push_back(term);
        }
    }

    return maxTerms;
}

class AkersArray
{
private:
    vector<string> row, column;
    vector<vector<int>> Aarr;
    vector<int> inputs;

public:
    AkersArray(vector<string> minterms, vector<string> maxterms, vector<int> input)
    {
        row = minterms;
        column = maxterms;
        Aarr = vector<vector<int>>(minterms.size(), vector<int>(maxterms.size(), 0));
        inputs = input;
    }

    void construct()
    {
        for (int i = 0; i < Aarr.size(); i++)
        {
            for (int j = 0; j < Aarr[i].size(); j++)
            {
                string minterm = row[i];
                string maxterm = column[j];

                for (int k = 0; k < minterm.size(); k++)
                {
                    if (minterm[k] == '1' && maxterm[k] == '0')
                    {
                        Aarr[i][j] = inputs[k];
                        break;
                    }
                    else if (minterm[k] == '0' && maxterm[k] == '1')
                    {
                        Aarr[i][j] = (inputs[k] == 1 ? 0 : 1);
                        break;
                    }
                }
            }
        }
    }

    void display()
    {
        cout << "Akers Array Matrix:\n";
        for (int i = 0; i < Aarr.size(); i++)
        {
            for (int j = 0; j < Aarr[i].size(); j++)
            {
                cout << Aarr[i][j] << " ";
            }
            cout << endl;
        }
    }

    int solve()
    {
        int i = 0, j = 0;
        while (i < row.size() && j < column.size())
        {
            if (Aarr[i][j] == 1)
            {
                j++;
            }
            else
            {
                i++;
            }
        }
        return (i < row.size()) ? 1 : 0;
    }
};

int main()
{
    string expression;
    cout << "Enter Boolean Expression: ";
    getline(cin, expression); // enter like a&b | b&c | c&a you can use () also

    vector<string> minterms = generateMinterms(expression);
    vector<string> maxterms = generateMaxTerms(expression);

    sort(minterms.begin(), minterms.end());
    sort(maxterms.begin(), maxterms.end());

    cout << "Minterms: ";
    for (const auto &m : minterms)
        cout << m << " ";
    cout << endl;

    cout << "Maxterms: ";
    for (const auto &m : maxterms)
        cout << m << " ";
    cout << endl;

    vector<int> inputs = {0, 1, 0}; // Example inputs

    AkersArray akers(minterms, maxterms, inputs);
    akers.construct();
    akers.display();
    cout << "Solution: " << akers.solve() << endl;

    return 0;
}
