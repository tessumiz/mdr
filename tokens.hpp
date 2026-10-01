#pragma once

#include "incl/types.hpp"


enum class TokenType : u8 {
    // types (u8, i32, i64, f32, f64)
    Byte, Int, Long,
    Float, Double,
    Str, Map, List,  // set is omitted; just use the map
    Dyn,  // the apple of the eye...

    // ops
    Plus, Minus, Star, Slash,
    Band, Bor, Bxor, Bnot,
    And, Or, Not,
    Assign, PlusAssign, MinusAssign, Incr, Decr,  // +=, -=, ++, -- supported
    Eq, Neq, Lt, Leq, Gt, Geq,
    In, Nin, Is,

    // kwds
    If, Elif,
    Match, Underscore,  // _ can be else or match default
    For, While, Loop, Break, Skip,
    Fall,  // experimental; falling through any scope
    Fn, Give, Implies,  // Implies is ->
    Cls, Static, Inherit, Mix,

    // punct
    LParen, RParen, LBrace, RBrace, LBrack, RBrack,
    Comma, Dot, 
    Indent, Dedent, Newline, EndOfFile  // EOF is a used macro
};


struct SrcSpan { u32 st, len; };

// not gonna use string_view; const char* will be repeated per token otherwise
struct Token {
    TokenType type;
    SrcSpan meta{};

    bool operator==(TokenType type) const {
        return this->type == type;
    }
};