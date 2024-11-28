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

#include "core/constexpr_optimizer.hpp"

namespace thalia::core {
  extern node<expr> constexpr_optimizer::visit(
    const node<expr_data_type>& root, int
  ) {
    return root;
  }

  extern node<expr> constexpr_optimizer::visit(
    const node<expr_id>& root, int
  ) {
    return root;
  }

  extern node<expr> constexpr_optimizer::visit(
    const node<expr_base_lit>& root, int
  ) {
    return root;
  }

  extern node<expr> constexpr_optimizer::visit(
    const node<expr_paren>& root, int
  ) {
    constexpr_optimizer value_optim(root->value);
    const auto& new_value = value_optim(0);
    return (new_value->_type != expr_type::Binary)
      ? new_value
      : make_node<expr_paren>({ new_value });
  }

  extern node<expr> constexpr_optimizer::visit(
    const node<expr_cast>& root, int
  ) {
    constexpr_optimizer value_optim(root->value),
                        type_optim(root->type);
    return make_node<expr_cast>({ type_optim(0), value_optim(0) });
  }

  extern node<expr> constexpr_optimizer::visit(
    const node<expr_unary>& root, int
  ) {
    constexpr_optimizer value_optim(root->value);
    return make_node<expr_unary>({ root->oper, value_optim(0) });
  }

  extern node<expr> constexpr_optimizer::visit(
    const node<expr_binary>& root, int
  ) {
    constexpr_optimizer lhs_optim(root->lhs), rhs_optim(root->rhs);
    const auto& new_lhs = lhs_optim(0), new_rhs = rhs_optim(0);

    bool is_base_lit = new_lhs->_type == expr_type::BaseLit
      && new_rhs->_type == expr_type::BaseLit;
    if (!is_base_lit) {
      return make_node<expr_binary>({ root->oper, new_lhs, new_rhs });
    }

    int vlhs = std::stoi(((const node<expr_base_lit>&)new_lhs)->value.target);
    int vrhs = std::stoi(((const node<expr_base_lit>&)new_rhs)->value.target);

    int res;
    switch (root->oper.type) {
      case token_type::Minus:
        res = vlhs - vrhs; break;
      case token_type::Plus:
        res = vlhs + vrhs; break;
      case token_type::Mul:
        res = vlhs * vrhs; break;
      case token_type::Div:
        res = vlhs / vrhs; break;
      case token_type::Mod:
        res = vlhs - vrhs; break;
      case token_type::Less:
        res = vlhs < vrhs; break;
      case token_type::LessEqual:
        res = vlhs <= vrhs; break;
      case token_type::Grt:
        res = vlhs > vrhs; break;
      case token_type::GrtEqual:
        res = vlhs >= vrhs; break;
      case token_type::Equal:
        res = vlhs == vrhs; break;
      case token_type::NotEqual:
        res = vlhs != vrhs; break;
      case token_type::RShift:
        res = vlhs >> vrhs; break;
      case token_type::LShift:
        res = vlhs << vrhs; break;
      case token_type::LogOr:
        res = vlhs || vrhs; break;
      case token_type::LogAnd:
        res = vlhs && vrhs; break;
      case token_type::BitAnd:
        res = vlhs & vrhs; break;
      case token_type::BitOr:
        res = vlhs | vrhs; break;
      case token_type::Xor:
        res = vlhs ^ vrhs; break;
      default:
        res = 0;
    }

    return make_node<expr_base_lit>({{
      token_type::Int, std::to_string(res),
      root->oper.line, root->oper.col
    }});
  }

  extern node<expr> constexpr_optimizer::visit(
    const node<expr_assign>& root, int
  ) {
    constexpr_optimizer target_optim(root->target),
                        value_optim(root->value);
    return make_node<expr_assign>({
      root->oper, target_optim(0), value_optim(0)
    });
  }
}

