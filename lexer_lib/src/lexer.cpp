#include "lexer.h"
#include <set>
using namespace std;
using Lexem = pair<string, string>;

set<string> keywords = {"int", "float", "string", "char", "if", "else", "for", "while", "out", "in", "return", "switch", "default", "case"};

Lexer::Lexer(std::istream &streamline) : streamline{streamline} {
    cache = streamline.get();
}
Lexer::~Lexer(){}

void Lexer::findLexem(vector<Container> graph, Lexem &lexem) {
    Container startedge = {"", false, false, 0, ""};
    for (auto edge: graph) {
        if (edge.cache == "digit"){
            if (isdigit(cache)){
                startedge = edge;
                break;
            }
        }
        else if (edge.cache == "letter"){
            if (isalpha(cache) or cache == '_') {
                startedge = edge;
                break;
            }
        }
        else if (edge.cache == "eof") {
            if (cache == -1) {
                startedge = edge;
                break;
            }
        }
        else if (edge.cache[0] == cache) {
            startedge = edge;
            break;
        }
        else if (edge.cache == "default") {
            startedge = edge;
        }
    }
    if (startedge.save) {
        buffer.push_back(cache);
    }
    if (startedge.read) {
        cache = streamline.get();
    }
    if (startedge.need_to_clear){
        buffer.clear();
    }
    if (!startedge.lexem.empty() and startedge.lexem != "keyword or id") {
        lexem.first = startedge.lexem;
        lexem.second = buffer;
        buffer.clear();
    } else if (startedge.lexem == "keyword or id") {
        if (keywords.count(buffer)) {
//            lexem.first = "kw" + buffer;
//            lexem.second = "";
            lexem.first = "kw" + buffer;
        } else {
            lexem.first = "id";
            lexem.second = buffer;
        }
        buffer.clear();
    }
    state = startedge.nextState;
}
Lexem Lexer::nextLexem(){
    Lexem lexem;
    while (lexem.first.empty()){
        findLexem(LexemMachine[state], lexem);
    }
    return lexem;
}
