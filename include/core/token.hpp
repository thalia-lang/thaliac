/* Copyright (C) 2024 Stan Vlad <vstan02@protonmail.com>
 *
 * This file is part of Thalia.
 *
 * Thalia is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef _THALIAC_CORE_TOKEN_
#define _THALIAC_CORE_TOKEN_

#include <cstddef>
#include <string>
#include <ostream>

namespace thalia::core {
	enum class token_type {
    Int,
    Id,

    Void,
    I8,
    I16,
    I32,
    I64,

    Use,
    Global,
    Local,
    Return,
    While,
    If,
    Else,
    Mut,
    Def,

    Cast,
    Minus,
    Plus,
    Mul,
    Div,
    Mod,
    Less,
    LessEqual,
    Grt,
    GrtEqual,
    Equal,
    NotEqual,
    RShift,
    LShift,
    LogNot,
    LogOr,
    LogAnd,
    BitNot,
    BitAnd,
    BitOr,
    Xor,
    Assign,
    MinusAssign,
    PlusAssign,
    MulAssign,
    DivAssign,
    ModAssign,
    AndAssign,
    OrAssign,
    XorAssign,
    RshAssign,
    LshAssign,
    LParen,
    RParen,
    LBrace,
    RBrace,
    LBracket,
    RBracket,
    Comma,
    Semi,
    Colon,

    Eof
  };

	struct token {
		const token_type type;
		const std::string target;
		const std::size_t line;
		const std::size_t col;

		token(token_type type, std::string target, std::size_t line, std::size_t col)
			: type(type)
			, target(target)
			, line(line)
			, col(col) {}

		token(token_type type, std::size_t line, std::size_t col)
			: type(type)
			, target()
			, line(line)
			, col(col) {}

		token(token_type type, std::string target)
			: type(type)
			, target(target)
			, line(1)
			, col(0) {}

		token(token_type type = token_type::Eof)
			: type(type)
			, target()
			, line(1)
			, col(0) {}
	};

  std::ostream& operator<<(std::ostream& os, const token& tkn);
}

#endif // _THALIAC_CORE_TOKEN_

