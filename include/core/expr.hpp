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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE:. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef _THALIAC_CORE_EXPR_
#define _THALIAC_CORE_EXPR_

#include "core/token.hpp"
#include "core/node.hpp"

namespace thalia::core {
  enum class expr_type {
    DataType,
    Id,
    BaseLit,
    Paren,
    Cast,
    Unary,
    Binary,
    Assign
  };

  struct expr {
    expr_type _type;

    expr(expr_type type)
      : _type(type) {}
  };

  struct expr_data_type: expr {
    const token value;

    expr_data_type(const token& value)
      : expr(expr_type::DataType)
      , value(value) {}
  };

  struct expr_id: expr {
    const token value;

    expr_id(const token& value)
      : expr(expr_type::Id)
      , value(value) {}
  };

  struct expr_base_lit: expr {
    const token value;

    expr_base_lit(const token& value)
      : expr(expr_type::BaseLit)
      , value(value) {}
  };

  struct expr_paren: expr {
    const node<expr> value;

    expr_paren(const node<expr>& value)
      : expr(expr_type::Paren)
      , value(value) {}
  };

  struct expr_cast: expr {
    const node<expr> type;
    const node<expr> value;

    expr_cast(
      const node<expr>& type,
      const node<expr>& value
    ) : expr(expr_type::Cast)
      , type(type)
      , value(value) {}
  };

  struct expr_unary: expr {
    const token oper;
    const node<expr> value;

    expr_unary(
      const token& oper,
      const node<expr>& value
    ) : expr(expr_type::Unary)
      , oper(oper)
      , value(value) {}
  };

  struct expr_binary: expr {
    const token oper;
    const node<expr> lhs;
    const node<expr> rhs;

    expr_binary(
      const token& oper,
      const node<expr>& lhs,
      const node<expr>& rhs
    ) : expr(expr_type::Binary)
      , oper(oper)
      , lhs(lhs)
      , rhs(rhs) {}
  };

  struct expr_assign: expr {
    const token oper;
    const node<expr> target;
    const node<expr> value;

    expr_assign(
      const token& oper,
      const node<expr>& target,
      const node<expr>& value
    ) : expr(expr_type::Assign)
      , oper(oper)
      , target(target)
      , value(value) {}
  };

  template <typename R, typename P>
  class expr_visitor {
    protected:
      expr_visitor(const node<expr>& node)
        : _node(node) {}

    public:
      R operator()(P payload) {
        switch (_node->_type) {
          case expr_type::DataType:
            return visit((const node<expr_data_type>&)_node, payload);
          case expr_type::Id:
            return visit((const node<expr_id>&)_node, payload);
          case expr_type::BaseLit:
            return visit((const node<expr_base_lit>&)_node, payload);
          case expr_type::Paren:
            return visit((const node<expr_paren>&)_node, payload);
          case expr_type::Cast:
            return visit((const node<expr_cast>&)_node, payload);
          case expr_type::Unary:
            return visit((const node<expr_unary>&)_node, payload);
          case expr_type::Binary:
            return visit((const node<expr_binary>&)_node, payload);
          case expr_type::Assign:
            return visit((const node<expr_assign>&)_node, payload);
        }
      }

    protected:
      virtual R visit(const node<expr_data_type>&, P) = 0;
      virtual R visit(const node<expr_id>&, P) = 0;
      virtual R visit(const node<expr_base_lit>&, P) = 0;
      virtual R visit(const node<expr_paren>&, P) = 0;
      virtual R visit(const node<expr_cast>&, P) = 0;
      virtual R visit(const node<expr_unary>&, P) = 0;
      virtual R visit(const node<expr_binary>&, P) = 0;
      virtual R visit(const node<expr_assign>&, P) = 0;

    private:
      const node<expr> _node;
  };
}

#endif // _THALIAC_CORE_EXPR_

