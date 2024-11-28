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

#include <cstdlib>
#include <iostream>
#include <ostream>
#include <string>

#include "core/expr.hpp"
#include "core/node.hpp"
#include "core/token.hpp"
#include "core/expr_view.hpp"
#include "core/constexpr_optimizer.hpp"

extern int main() {
  using namespace thalia;

  auto iast = core::make_node<core::expr_binary>({
    { core::token_type::Plus, "-" },
    core::make_node<core::expr_id>({
      { core::token_type::Id, "x" }
    }),
    core::make_node<core::expr_paren>({
      core::make_node<core::expr_binary>({
        { core::token_type::Plus, "+" },
        core::make_node<core::expr_base_lit>({
          { core::token_type::Int, "23" }
        }),
        core::make_node<core::expr_base_lit>({
          { core::token_type::Int, "54" }
        })
      })
    })
  });

  core::constexpr_optimizer optr(iast);
  auto oast = optr(0);

  core::expr_view view1(iast), view2(oast);
  std::cout << view1 << '\n' << view2 << '\n';
  return 0;
}

