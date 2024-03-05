#include "lexer.h"
#include <fstream>
#include <iomanip>
#include <stack>

using Lexem = std::pair<std::string, std::string>;


int main() {
    Lexem lexem;
    std::fstream streamline(R"(C:\Users\ivukhov\source\repos\miniClex\code.txt)");
    Lexer lexer(streamline);
    while (true) {
        lexem = lexer.nextLexem();
        std::cout << "{ \"" << lexem.first << "\", \"" << lexem.second << "\" }" << std::endl;
        if (lexem.first == "error" or lexem.first == "end") {
            break;
        }
    }
}
