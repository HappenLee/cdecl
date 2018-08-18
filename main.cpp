#include <iostream>
#include <stack>

using namespace std;

enum type_tag {IDENTIFIER,QUALIFIER,TYPE,POINTER,LPAREN,LBRACKET,RPAREN,RBRACKET};

struct token {
    type_tag type;
    string content;
};

token this_t;
stack<token> token_stack;

void classify(token &t) {
    if(t.content == "const") {
        t.content = "read-only";
        t.type = QUALIFIER;
        return;
    }

    if(t.content == "volatile") {
        t.type = QUALIFIER;
        return;
    }
    if(t.content == "void") {
        t.type = TYPE;
        return;
    }
    if(t.content == "char") {
        t.type = TYPE;
        return;
    }
    if(t.content == "signed") {
        t.type = TYPE;
        return;
    }
    if(t.content == "unsigned") {
        t.type = TYPE;
        return;
    }
    if(t.content == "short") {
        t.type = TYPE;
        return;
    }
    if(t.content == "int") {
        t.type = TYPE;
        return;
    }
    if(t.content == "long") {
        t.type = TYPE;
        return;
    }
    if(t.content == "float") {
        t.type = TYPE;
        return;
    }
    if(t.content == "double") {
        t.type = TYPE;
        return;
    }
    if(t.content == "struct") {
        t.type = TYPE;
        return;
    }
    if(t.content == "union") {
        t.type = TYPE;
        return;
    }
    if(t.content == "enum") {
        t.type = TYPE;
        return;
    }

    t.type = IDENTIFIER;
    return;
}

void gettoken() {
    this_t.content = "";
    char ch = ' ';
    while((ch = getchar()) == ' ');

    if(isalnum(ch)) {
        do {
            this_t.content += ch;
        } while(isalnum(ch = getchar()));

        ungetc(ch,stdin);
        classify(this_t);
        return;
    }

    if(ch == '*') {
        this_t.content = "pointer to ";
        this_t.type = POINTER;
    }

    if(ch == '[') {
        this_t.type = LBRACKET;
    }

    if(ch == '(') {
        this_t.type = LPAREN;
    }

    if(ch == ')') {
        this_t.type = RPAREN;
    }
    if(ch == ']') {
        this_t.type = RBRACKET;
    }

}

void read_to_first_identifer() {
    gettoken();
    while (this_t.type != IDENTIFIER) {
        token_stack.push(this_t);
        gettoken();
    }

    cout << this_t.content + " is ";
    gettoken();
}

void deal_with_arrays() {
    while (this_t.type == LBRACKET) {
        cout << "array ";
        gettoken();
        if(isdigit(this_t.content[0])) {
            printf("0....%d of ",atoi(this_t.content.c_str()) - 1);
            gettoken();
        }

        gettoken();
    }
}

void deal_with_function_args() {
    while(this_t.type != RPAREN) {
        gettoken();
    }
    gettoken();

    cout << "function returning ";
}

void deal_with_pointers() {
    while(token_stack.top().type == POINTER) {
        cout << token_stack.top().content;
        token_stack.pop();
    }
}

void deal_with_declarator(){
    switch (this_t.type) {
        case LBRACKET:deal_with_arrays();break;
        case LPAREN:deal_with_function_args();
    }

    deal_with_pointers();

    while(!token_stack.empty()) {
        if(token_stack.top().type == LPAREN) {
            token_stack.pop();
            gettoken();
            deal_with_declarator();
        } else {
            cout << token_stack.top().content + " ";
            token_stack.pop();
        }
    }

}

int main() {
    read_to_first_identifer();
    deal_with_declarator();
    return 0;
}