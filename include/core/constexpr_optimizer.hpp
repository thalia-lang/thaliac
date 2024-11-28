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

#ifndef _THALIAC_CORE_CONSTEXPR_OPTIMIZER_
#define _THALIAC_CORE_CONSTEXPR_OPTIMIZER_

#include "core/expr.hpp"

namespace thalia::core {
  class constexpr_optimizer
    : public expr_visitor<node<expr>, int> {
    public:
      constexpr_optimizer(const node<expr>& root)
        : expr_visitor<node<expr>, int>(root) {}

    protected:
      node<expr> visit(const node<expr_data_type>& root, int) override;
      node<expr> visit(const node<expr_id>& root, int) override;
      node<expr> visit(const node<expr_base_lit>& root, int) override;
      node<expr> visit(const node<expr_paren>& root, int) override;
      node<expr> visit(const node<expr_cast>& root, int) override;
      node<expr> visit(const node<expr_unary>& root, int) override;
      node<expr> visit(const node<expr_binary>& root, int) override;
      node<expr> visit(const node<expr_assign>& root, int) override;
  };
}

#endif // _THALIAC_CORE_CONSTEXPR_OPTIMIZER_

