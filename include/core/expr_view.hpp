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

#ifndef _THALIAC_CORE_EXPR_VIEW_
#define _THALIAC_CORE_EXPR_VIEW_

#include <ostream>

#include "core/expr.hpp"

namespace thalia::core {
  class expr_view
    : public expr_visitor<std::ostream&, std::ostream&> {
    public:
      expr_view(const node<expr>& root)
        : expr_visitor<std::ostream&, std::ostream&>(root) {}

      friend std::ostream& operator<<(std::ostream& os, expr_view& view) {
        return view(os);
      }

    protected:
      std::ostream& visit(
        const node<expr_data_type>& root,
        std::ostream& os
      ) override;
      std::ostream& visit(
        const node<expr_id>& root,
        std::ostream& os
      ) override;
      std::ostream& visit(
        const node<expr_base_lit>& root,
        std::ostream& os
      ) override;
      std::ostream& visit(
        const node<expr_paren>& root,
        std::ostream& os
      ) override;
      std::ostream& visit(
        const node<expr_cast>& root,
        std::ostream& os
      ) override;
      std::ostream& visit(
        const node<expr_unary>& root,
        std::ostream& os
      ) override;
      std::ostream& visit(
        const node<expr_binary>& root,
        std::ostream& os
      ) override;
      std::ostream& visit(
        const node<expr_assign>& root,
        std::ostream& os
      ) override;
  };
}

#endif // _THALIAC_CORE_EXPR_VIEW_

