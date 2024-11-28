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

#include "core/expr_view.hpp"

namespace thalia::core {
  extern std::ostream& expr_view::visit(
    const node<expr_data_type>& root,
    std::ostream& os
  ) {
    return os << root->value;
  }

  extern std::ostream& expr_view::visit(
    const node<expr_id>& root,
    std::ostream& os
  ) {
    return os << root->value;
  }

  extern std::ostream& expr_view::visit(
    const node<expr_base_lit>& root,
    std::ostream& os
  ) {
    return os << root->value;
  }

  extern std::ostream& expr_view::visit(
    const node<expr_paren>& root,
    std::ostream& os
  ) {
    expr_view value_view(root->value);
    return os << '(' << value_view << ')';
  }

  extern std::ostream& expr_view::visit(
    const node<expr_cast>& root,
    std::ostream& os
  ) {
    expr_view value_view(root->value), type_view(root->type);
    return os << "&(" << type_view << ')' << value_view;
  }

  extern std::ostream& expr_view::visit(
    const node<expr_unary>& root,
    std::ostream& os
  ) {
    expr_view value_view(root->value);
    return os << root->oper << value_view;
  }

  extern std::ostream& expr_view::visit(
    const node<expr_binary>& root,
    std::ostream& os
  ) {
    expr_view lhs_view(root->lhs), rhs_view(root->rhs);
    return os << lhs_view << ' ' << root->oper << ' ' << rhs_view;
  }

  extern std::ostream& expr_view::visit(
    const node<expr_assign>& root,
    std::ostream& os
  ) {
    expr_view target_view(root->target), value_view(root->value);
    return os << target_view << ' ' << root->oper << ' ' << value_view;
  }
}

