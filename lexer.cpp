#include <string>
#include <string_view>
#include <vector>
#include <unordered_map>

#include "tokens.hpp"


class Lexer {
public:
    Lexer(const std::string& src) : src(src) { lex(); }

    std::string_view get_meta(Token token) {
        return { src.data() + token.meta.st, token.meta.len };
    }


private:
    inline static const std::unordered_map<std::string_view, TokenType> kwds = {
        {"byte", TokenType::Byte},
        {"int", TokenType::Int},
        {"long", TokenType::Long},
        {"float", TokenType::Float},
        {"double", TokenType::Double},

        {"str", TokenType::Str},
        {"map", TokenType::Map},
        {"list", TokenType::List},

        {"dyn", TokenType::Dyn},

        {"if", TokenType::If},
        {"ef", TokenType::Elif},

        {"match", TokenType::Match},
        {"_", TokenType::Underscore},

        {"for", TokenType::For},
        {"while", TokenType::While},
        {"loop", TokenType::Loop},
        {"break", TokenType::Break},
        {"skip", TokenType::Skip},

        {"fall", TokenType::Fall},

        {"fn", TokenType::Fn},
        {"give", TokenType::Fn},

        {"cls", TokenType::Cls},
        {"static", TokenType::Static},
        {"mix", TokenType::Mix}
    };


    const std::string& src;
    std::vector<Token> tokens;

    int pos;

    inline char peek(int off = 0) {
        return (pos + off < src.size()) ? src[pos + off] : '\0';
    }

    inline char advance() {
        return (pos < src.size()) ? src[pos++] : '\0';
    }

    inline void emit(TokenType token, SrcSpan meta = {}) {
        tokens.push_back({ token, meta });
    }


    void lex() {
        
    }

    void scan() {
        int  curs = pos;
        char c = advance();
        char p = peek();

        switch (c) {
            case ' ':
                break;


            case '+':
                if (p == '=') {
                    advance();
                    emit(TokenType::PlusAssign);
                } else if (p == '+') {
                    advance();
                    emit(TokenType::Incr);
                } else {
                    emit(TokenType::Plus);
                }
                break;


            case '-':
                if (p == '=') {
                    advance();
                    emit(TokenType::MinusAssign);
                } else if (p == '-') {
                    advance();
                    emit(TokenType::Decr);
                } else if (p == '>') {
                    advance();
                    emit(TokenType::Implies);
                } else {
                    emit(TokenType::Minus);
                }
                break;
            

            case '*':
                emit(TokenType::Star);
                break;
            
            case '/':
                emit(TokenType::Slash);
                break;

            case '&':
                if (p == '&') {
                    advance();
                    emit(TokenType::And);
                } else {
                    emit(TokenType::Band);
                }
                break;

            case '|':
                if (p == '|') {
                    advance();
                    emit(TokenType::Or);
                } else {
                    emit(TokenType::Bor);
                }
                break;

            case '^':
                emit(TokenType::Bxor);
                break;

            case '~':
                emit(TokenType::Bnot);
                break;

            case '!':
                if (p == '=') {
                    advance();
                    emit(TokenType::Neq);
                } else {
                    emit(TokenType::Not);
                }
                break;

            case '=':
                if (p == '=') {
                    advance();
                    emit(TokenType::Eq);
                } else {
                    emit(TokenType::Assign);
                }
                break;

            case '<':
                if (p == '=') {
                    advance();
                    emit(TokenType::Leq);
                } else if (p == '-') {
                    advance();
                    emit(TokenType::Inherit);
                } else {
                    emit(TokenType::Lt);
                }
                break;

            case '>':
                if (p == '=') {
                    advance();
                    emit(TokenType::Geq);
                } else {
                    emit(TokenType::Gt);
                }
                break;

            case '(':
                emit(TokenType::LParen);
                break;

            case ')':
                emit(TokenType::RParen);
                break;

            case '{':
                emit(TokenType::LBrace);
                break;

            case '}':
                emit(TokenType::RBrace);
                break;

            case '[':
                emit(TokenType::LBrack);
                break;

            case ']':
                emit(TokenType::RBrack);
                break;

            case ',':
                emit(TokenType::Comma);
                break;

            case '.':
                emit(TokenType::Dot);
                break;

            
            default:
                // kwds/lits
                break;
        }
    }
};