#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <utility>
#include <vector>

std::ofstream problem("problem.pddl"), domain("domain.pddl");

enum GRID_TYPE {
  PCMAN,
  G_RED,
  G_BLUE,
  G_GREEN,
  PORTAL,
  ICE,
  WALL,
  WHITE_SPACE,
  F_RED,
  F_BLUE,
  F_GREEN,
  COIN
};

GRID_TYPE to_type(char c) {
  switch (c) {
  case 'P':
    return GRID_TYPE::PCMAN;
  case 'R':
    return GRID_TYPE::G_RED;
  case 'G':
    return GRID_TYPE::G_GREEN;
  case 'B':
    return GRID_TYPE::G_BLUE;
  case ' ':
    return GRID_TYPE::WHITE_SPACE;
  case 'I':
    return GRID_TYPE::ICE;
  case 'O':
    return GRID_TYPE::PORTAL;
  case '#':
    return GRID_TYPE::WALL;
  case '*':
    return GRID_TYPE::COIN;
  }
  return GRID_TYPE::COIN;
}

std::vector<std::vector<GRID_TYPE>> matrix;

void create_predicates(int i, int j) {
  if (matrix[i][j] == GRID_TYPE::WALL)
    return;
  if (matrix[i][j] == GRID_TYPE::F_RED) {
    domain << "\t\t(red_fruit_at_" << i << "-" << j << ")\n";
  } else if (matrix[i][j] == GRID_TYPE::F_BLUE) {
    domain << "\t\t(blue_fruit_at_" << i << "-" << j << ")\n";
  } else if (matrix[i][j] == GRID_TYPE::F_GREEN) {
    domain << "\t\t(green_fruit_at_" << i << "-" << j << ")\n";
  }
  domain << "\t\t(pac_at_" << i << "-" << j << ")\n";
  domain << "\t\t(red_at_" << i << "-" << j << ")\n";
  domain << "\t\t(blue_at_" << i << "-" << j << ")\n";
  domain << "\t\t(green_at_" << i << "-" << j << ")\n";
}
void create_actions(int i, int j) {
  // pacman
  if (matrix[i][j] == GRID_TYPE::WALL || matrix[i][j] == GRID_TYPE::ICE)
    return;

  if (matrix[i][j] == GRID_TYPE::COIN) // COIN
    return;

  // fruta

  int row_size = matrix.size(), column_size = matrix[i].size();

  // MOVE ACTIONS
  // -> top
  if (i > 0 && matrix[i - 1][j] != GRID_TYPE::WALL) {
    // action move up
    std::cout << "GENERATING UP in " << i << "-" << j << std::endl;
    // ice
    if (matrix[i - 1][j] == GRID_TYPE::ICE) {
      std::cout << "ice up " << i << "-" << j << std::endl;
      int m = 2;
      while (matrix[i - m++][j] == GRID_TYPE::ICE) {
        std::cout << "gelo sequencial\n";
      };
      m--;
      if (matrix[i - m][j] == GRID_TYPE::WALL) {
        // (total_cost)*2
        std::cout << "Gelo com parede\n";
        std::cout << "Custo: " << (m - 1) * 2 << std::endl;
        // actions de passar pelo gelo sem fantasma
        domain << "\n\n\t(:action n-ice-wall-" << i << "-" << j << "\n";
        domain << "\t:parameters ()\n";

        domain << "\t:precondition (and";
        // red
        for (int ices = 1; ices < m; ices++)
          domain << "\n\t\t(red_at_" << i - ices << "-" << j << ")";
        // domain << ")\n";
        // blue
        for (int ices = 1; ices < m; ices++)
          domain << "\n\t\t(blue_at_" << i - ices << "-" << j << ")";
        // green
        for (int ices = 1; ices < m; ices++)
          domain << "\n\t\t(green_at_" << i - ices << "-" << j << ")";
        domain << ")";
        domain << "\n\t:effect (increase_cost ....)";
        domain << ")";
        // actions de matar pelo gelo com parede
        // red
        domain << "\n\n\t(:action n-kill-ice-wall-red-" << i << "-" << j
               << "\n";
        domain << "\t:parameters () \n";
        domain << "\t:precondition (and (with_red_fruit) (or ";
        for (int ices = 1; ices < m; ices++) {
          domain << "(red_at_" << i - ices << "-" << j << ") ";
        }
        domain << ")";
        for (int ices = 1; ices < m; ices++) {
          domain << " (not (blue_at_" << i - ices << "-" << j << ")) ";
          domain << "(not (green_at_" << i - ices << "-" << j << "))";
        }
        domain << ")";
        domain << "\n\t:effect (increase_cost ....))";
        // blue
        domain << "\n\n\t(:action n-kill-ice-wall-blue-" << i << "-" << j
               << "\n";
        domain << "\t:parameters ( ) \n";
        domain << "\t:precondition (and (with_blue_fruit) (or ";
        for (int ices = 1; ices < m; ices++) {
          domain << "(blue_at_" << i - ices << "-" << j << ") ";
        }
        domain << ")";
        for (int ices = 1; ices < m; ices++) {
          domain << " (not (green_at_" << i - ices << "-" << j << ")) ";
          domain << "(not (red_at_" << i - ices << "-" << j << "))";
        }
        domain << ")";
        domain << "\n\t:effect (increase_cost ....))";
        // green
        domain << "\n\n\t(:action n-kill-ice-wall-green-" << i << "-" << j
               << "\n";
        domain << "\t:parameters ( ) \n";
        domain << "\t:precondition (and (with_green_fruit) (or ";
        for (int ices = 1; ices < m; ices++) {
          domain << "(green_at_" << i - ices << "-" << j << ") ";
        }
        domain << ")";
        for (int ices = 1; ices < m; ices++) {
          domain << " (not (blue_at_" << i - ices << "-" << j << ")) ";
          domain << "(not (red_at_" << i - ices << "-" << j << "))";
        }
        domain << ")";
        domain << "\n\t:effect (increase_cost ....))";
      } else if (matrix[i - m][j] == GRID_TYPE::PORTAL) {
        std::cout << "Gelo com portal\n";
      }
    }
    // portal
    else if (matrix[i - 1][j] == GRID_TYPE::PORTAL) {
      std::cout << "portal move" << i << "-" << j << std::endl;
    } else {
      // nao tem parede, nem gelo, nem portal
      // fazer actions para mover, comer fruta, matar fantasma
      domain << "\n\n\t(:action n-move-" << i << "-" << j; // MOVER CIMA
      domain << "\n\t:parameters ( )";
      domain << "\n\t:precondition (and ";
      domain << "(pac_at_" << i << "-" << j << ") ";
      domain << "(not (red_at_" << i - 1 << "-" << j << ")) ";
      domain << "(not (blue_at_" << i - 1 << "-" << j << ")) ";
      domain << "(not (green_at_" << i - 1 << "-" << j << ")) ";
      domain << "(not (red_fruit_at_" << i - 1 << "-" << j << ")) ";
      domain << "(not (blue_fruit_at_" << i - 1 << "-" << j << ")) ";
      domain << "(not (green_fruit_at_" << i - 1 << "-" << j << ")))";
      domain << "\n\t:effect (and (not (pac_at_" << i << "-" << j << ")) ";
      domain << "(pac_at_" << i - 1 << "-" << j << "))) ";

      // MATAR RED CIMA
      domain << "\n\n\t(:action n-kill-red-" << i << "-" << j;
      domain << "\n\t:parameters ( ) \n";
      domain << "\t:precondition (and (red_at_" << i - 1 << "-" << j << ") ";
      domain << "(not (blue_at_" << i - 1 << "-" << j << ")) ";
      domain << "(not (green_at_" << i - 1 << "-" << j << ")) ";
      domain << "(pac_at_" << i << "-" << j << ") ";
      domain << "(with_red_fruit))";
      domain << "\n\t:effect (and (not (pac_at_" << i << "-" << j << ")) ";
      domain << "(pac_at_" << i - 1 << "-" << j << ") ";
      domain << "(not (red_at_" << i - 1 << "-" << j << ")) ";
      domain << "(not (red_is_alive)) ";
      domain << "(not (with_red_fruit))))";
      // MATAR BLUE CIMA
      domain << "\n\n\t(:action n-kill-blue-" << i << "-" << j;
      domain << "\n\t:parameters ( ) \n";
      domain << "\t:precondition (and (blue_at_" << i - 1 << "-" << j << ") ";
      domain << "(not (red_at_" << i - 1 << "-" << j << ")) ";
      domain << "(not (green_at_" << i - 1 << "-" << j << ")) ";
      domain << "(pac_at_" << i << "-" << j << ") ";
      domain << "(with_blue_fruit))";
      domain << "\n\t:effect (and (not (pac_at_" << i << "-" << j << ")) ";
      domain << "(pac_at_" << i - 1 << "-" << j << ") ";
      domain << "(not (blue_at_" << i - 1 << "-" << j << ")) ";
      domain << "(not (blue_is_alive)) ";
      domain << "(not (with_blue_fruit))))";
      // MATAR GREEN CIMA
      domain << "\n\n\t(:action n-kill-green-" << i << "-" << j;
      domain << "\n\t:parameters ( ) \n";
      domain << "\t:precondition (and (green_at_" << i - 1 << "-" << j << ") ";
      domain << "(not (red_at_" << i - 1 << "-" << j << ")) ";
      domain << "(not (blue_at_" << i - 1 << "-" << j << ")) ";
      domain << "(pac_at_" << i << "-" << j << ") ";
      domain << "(with_green_fruit))";
      domain << "\n\t:effect (and (not (pac_at_" << i << "-" << j << ")) ";
      domain << "(pac_at_" << i - 1 << "-" << j << ") ";
      domain << "(not (green_at_" << i - 1 << "-" << j << ")) ";
      domain << "(not (green_is_alive)) ";
      domain << "(not (with_green_fruit))))";
    }
  }
  // -> right
  if (j < column_size - 1 && matrix[i][j + 1] != GRID_TYPE::WALL) {
    std::cout << "action right " << i << "-" << j << std::endl;
    // ice
    if (matrix[i][j + 1] == GRID_TYPE::ICE) {
      std::cout << "ice right " << i << "-" << j << std::endl;
      int m = 2;
      while (matrix[i][j + m++] == GRID_TYPE::ICE) {
        std::cout << "gelo sequencial\n";
      };
      m--;
      if (matrix[i][j + m] == GRID_TYPE::WALL) {
        // (total_cost)*2
        std::cout << "Gelo com parede\n";
        std::cout << "Custo: " << (m - 1) * 2 << std::endl;
      } else if (matrix[i][j + m] == GRID_TYPE::PORTAL) {
        std::cout << "Gelo com portal\n";
      }
    }
    // portal
    else if (matrix[i][j + 1] == GRID_TYPE::PORTAL) {
      std::cout << "portal move" << i << "-" << j << std::endl;
    }
    // red ghost
    // std::cout << "kill red ghost right" << i << "-" << j << std::endl;
    // blue ghost
    // std::cout << "kill blue ghost right" << i << "-" << j << std::endl;
    // green ghost
    // std::cout << "kill green ghost right" << i << "-" << j << std::endl;
  }
  // -> bottom
  if (i < row_size - 1 && matrix[i + 1][j] != GRID_TYPE::WALL) {
    std::cout << "action bottom " << i << "-" << j << std::endl;
    // ice
    if (matrix[i + 1][j] == GRID_TYPE::ICE) {
      std::cout << "ice up " << i << "-" << j << std::endl;
      int m = 2;
      while (matrix[i + m++][j] == GRID_TYPE::ICE) {
        std::cout << "gelo sequencial\n";
      };
      m--;
      if (matrix[i + m][j] == GRID_TYPE::WALL) {
        // (total_cost)*2
        std::cout << "Gelo com parede\n";
        std::cout << "Custo: " << (m - 1) * 2 << std::endl;
      } else if (matrix[i + m][j] == GRID_TYPE::PORTAL) {
        std::cout << "Gelo com portal\n";
      }
    }
    // portal
    else if (matrix[i + 1][j] == GRID_TYPE::PORTAL) {
      std::cout << "portal move" << i << "-" << j << std::endl;
    }
    // red ghost
    // std::cout << "kill red ghost bottom" << i << "-" << j << std::endl;
    // blue ghost
    // std::cout << "kill blue ghost bottom" << i << "-" << j << std::endl;
    // green ghost
    // std::cout << "kill green ghost bottom" << i << "-" << j << std::endl;
  }
  // -> left
  if (j > 0 && matrix[i][j - 1] != GRID_TYPE::WALL) {
    std::cout << "action left " << i << "-" << j << std::endl;
    // ice
    if (matrix[i][j - 1] == GRID_TYPE::ICE) {
      std::cout << "ice right " << i << "-" << j << std::endl;
      int m = 2;
      while (matrix[i][j - m++] == GRID_TYPE::ICE) {
        std::cout << "gelo sequencial\n";
      };
      m--;
      if (matrix[i][j - m] == GRID_TYPE::WALL) {
        // (total_cost)*2
        std::cout << "Gelo com parede\n";
        std::cout << "Custo: " << (m - 1) * 2 << std::endl;
      } else if (matrix[i][j - m] == GRID_TYPE::PORTAL) {
        std::cout << "Gelo com portal\n";
      }
    }
    // portal
    else if (matrix[i][j - 1] == GRID_TYPE::PORTAL) {
      std::cout << "portal move" << i << "-" << j << std::endl;
    }
    // red ghost
    // std::cout << "kill red ghost left" << i << "-" << j << std::endl;
    // blue ghost
    // std::cout << "kill blue ghost left" << i << "-" << j << std::endl;
    // green ghost
    // std::cout << "kill green ghost left" << i << "-" << j << std::endl;
  }
  std::cout << std::endl;
}

int main(void) {

  {
    std::cout << " ";
    for (int i = 0; i < 9; i++)
      std::cout << i;
    std::cout << std::endl;
    std::string line;
    int j = 0;
    while (std::getline(std::cin, line) && !line.empty()) {
      std::cout << j++ << line << std::endl;
      std::vector<GRID_TYPE> temp;
      for (std::string::iterator it = line.begin(); it != line.end(); it++) {
        temp.push_back(to_type(*it));
      }
      matrix.push_back(temp);
    }
  }

  // problem = fopen("problem.pddl", "w");
  // domain = fopen("domain.pddl", "w");
  domain << "(define (domain pacman_mojificado)\n";
  domain << "\t(:predicates \n";
  domain << "\t\t(red_is_alive)\n";
  domain << "\t\t(blue_is_alive)\n";
  domain << "\t\t(green_is_alive)\n";
  // Predicates
  {
    int i = 0, j = 0;
    for (const auto &row : matrix) {
      for (const auto &elem : row)
        create_predicates(i, j++);
      i++;
      j = 0;
    }
  }
  domain << "\t)";

  // Actions
  {
    int i = 0, j = 0;
    for (const auto &row : matrix) {
      for (const auto &elem : row)
        create_actions(i, j++);
      i++;
      j = 0;
    }
  }
  domain << "\n)";
  /*
  std::cout << "MAPA: \n";
  for (const auto& row : matrix) {
      for (const auto& elem : row) {
          std::cout << elem << ' ';
      }
      std::cout << std::endl;
  }*/

  return 0;
}
